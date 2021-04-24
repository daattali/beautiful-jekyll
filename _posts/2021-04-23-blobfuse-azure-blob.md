---
layout: post
title:  "토이 프로젝트 안되나요? - 늦은 건가?"
date:   2021-04-23 11:15:00 +0900
author: Changbae Bang
tags: [azure, blob, blobfuse, 장애대응, 잘지내죠, webOS, ]
---

# 역사는 반복되고...
  
역시나....

근 한달 반만에 다시 글을 올려 봅니다.

원래는 또 면접에 관한 글을 쓰려고 했다가... 면접을 잘 봤던 것도 아니고 굳이 저 말고도 혹세 무민의 상황에도 의리를 가지고 업계에 좋은 소리를 하시는 분들이 많기때문에 글을 폐기하였습니다.

그리고 다시 본업(?)으로 돌아와서 Azure 에 대한 글을 써봅니다.

Azure 의 저변이 확대 되길 바랍니다.

아... 나름 좋은데....ㅎㅎㅎ
  
  

# Blobfuse 는 뭔가요?
  
지난 포스트에서 Blob 을 편하게 사용할 수 있는 NFS 를 다뤄봤습니다.

이것과 비슷하지만 조금 다른 것이 하나 있어서 다시 들고 나와봤습니다.

Blob FUSE 라는 것인데 짧게 이야기 하면 Linux 만을 위한 것이고 Linux 에 깔아쓸 수 있는 페키지이며 깔면 Blob Storage 를 Mount 해서 사용할 수 있는 것인데 이게 나름 오픈소스 입니다.

`I Love Linux` 잊지 않으셨죠?

사실 아래 포스트가 더 설명을 잘하고 있습니다.  

[공식 블로그 포스트](https://azure.microsoft.com/ko-kr/blog/linux-fuse-adapter-for-blob-storage/)

글쓰신 분 보면 신기하게 MS 있다고 AWS 갔다가 다시 오셨네요..  MS 도 재입사가 잘 되나 싶기도 한데 무튼 설명 잘 해놓으셨습니다. 영어로...

요약하면 FUSE 라는 것이 있고 이것 기반으로 Blob Storage Adapter 를 낸 것입니다. MS 에서 Linux 를 야심차게 사랑하고 있는 것을 보여주는 예가 될 것도 같습니다.

(하지만... 저는 이곳에서 윈도우즈의 끝이 어디인지 보고 있습니다... OS 에 대한 생각이 시간이 지날 수록 오락가락해집니다.)


# 안되는건 없나요?
뭐 왠만하면 기능이 다 되는데, 제약 사항이 있습니다.

그중 가장 아쉬운 것은 `symbolic link` 입니다.

이거 지원 안됩니다. 되면 정말 킹왕짱이겠지만... 뭐 원하시면 오픈소스니까 PR 을 만들어서 올려볼 수도 있습니다.

```
Unimplemented file system operations in blobfuse may break your existing application. Symbolic links, file permissions, flags, and POSIX file locking operations are currently not implemented.
```

아... 아래 말은 정말 어렵습니다. 쓰라는 건가?

read only 로 써야 하나 싶긴 한데... 작은 파일들을 사용해보면 그렇게 심하게 밀리지는 않습니다.  
정신건강을 위해서 오버라이팅을 하지 말라 정도인데 저는 소규모로 써봐서 그런가 크게 어려움은 못느겼습니다.  
```
Updating an existing file is an expensive operation as blobfuse downloads the entire file to the local disk before it can modify the contents.
```

아직 Blob 에 대한 동시 작업을 해보지 않아서 아래 제약사항도 크게 피눈물을 겪어보지 않았습니다.  
보면 알아서 diff 해서 머지하지는 않을 테니까.. 결국 쓸 때 잘 써야(읽기 전용이니?) 인가 싶지만 그래도 뭐 그럭저럭 쓸만 했습니다.

```
You can mount blobfuse from multiple nodes, however there is no synchronization between nodes regarding writes to Blob storage. Do not use blobfuse for concurrent writes.
```

제약만 적다보니까 팀킬이 되었는데... 그러고 싶은 것은 아니고.. 사실 `symbolic link` 가 안된다는 것을 강조하고 싶었는데 쓰는 김에 조금 더 제약 사항을 써봤습니다. 
  
  
# 어떻게 쓰나요?
  
까는 방법은 간단합니다.
[공식 안내 문서](https://github.com/Azure/azure-storage-fuse/wiki/1.-Installation)


Ubuntu 기준으로

```
wget https://packages.microsoft.com/config/ubuntu/<ubuntu version 16.04 or 18.04 or 20.04>/packages-microsoft-prod.deb

## For Ubuntu 16.04 your command will be below
## wget https://packages.microsoft.com/config/ubuntu/16.04/packages-microsoft-prod.deb

sudo dpkg -i packages-microsoft-prod.deb
sudo apt-get update

sudo apt-get install blobfuse fuse
```

하면 됩니다.

근데 오픈 소스 아닙니까?

빌드해서 쓸 수도 있습니다.

웹오에스에서도 쓸 수 있다는 것이겠죠...

잘지내죠 webOS?
  
  
# 더 편하게 쓰려면?
  
이렇게 일단 설치 해 놓으면 blob 을 로컬에서 슉슉 작업 할 수 있습니다. 또한 `/etc/fstab` 에다가 작업을 걸어 놓으면 부팅하면서 자동으로 mount 할 수 있습니다.

[공식 안내 문서](https://github.com/Azure/azure-storage-fuse/wiki/2.-Configuring-and-Running#persisting)


```
/<path_to_blobfuse>/mount.sh </path/to/desired/mountpoint> fuse _netdev
```

이렇게 걸어 놓으면 짠 하고 나옵니다.
  

# 그런데말입니다 Azure VM 에서 쓸때 말입니다.
  
Azure VM 을 쓸 때는 약간 더 제약이 있습니다.

VM Start 할 때 제약이 있는데요...

이게 VM Start 를 하면 _netdev 시점 이후에도 ssd 가 없는 경우가 있습니다. 나름 lazy binding 이 되는 건데... 덕분에 blobfuse 가 Restart 후에는 마운트가 안되는 현상이 있더라구요...

물론 뭐 reboot 를 하면 다시 착 올라옵니다. 이 때는 ssd 할당이 되어 있어서 _netdev 시점에 mnt 가 확인이 됩니다.


그래서 말입니다..

빡빡하게 체크를 하려면 `mnt` 마운트 상태도 확인해서 붙이면 됩니다.

```
/<path_to_blobfuse>/mount.sh </path/to/desired/mountpoint> fuse _netdev, x-systemd.requires-mounts-for=/mnt
```

만세 다만  `/etc/fstab` 건드렸다가 부팅 안되서 난리 일으키고 싶지 않다고 하신다면.. `/etc/rc.local` 같이 부팅 하고 나서 처리하셔도 됩니다.

Azure VM 부팅안되면 망한거 아닌가? 하실 수도 있는데.. 그 정도는 나름 다시 살릴 수 있는 길 정도는 있습니다.

Serial Console 을 사용하면 죽은 VM 다시 살살 살려 볼 수 있습니다.

[공식 번역된 문서](https://docs.microsoft.com/ko-kr/troubleshoot/azure/virtual-machines/linux-virtual-machine-cannot-start-fstab-errors#use-the-serial-console)

그럼 모두 성~~불~~에저 하십시오!!

P.S. I miss webOS.
