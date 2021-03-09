---
layout: post
title:  "Azure Blob 에서 NFS 사용하기"
date:   2021-03-03 01:00:00 +0900
author: Changbae Bang
tags: [azure, blob, nfs, 장애대응, ]
---

거의 일년 반만에 다시 글을 올려 봅니다.

회사를 옮기게 되고 덕분에 OS 도 갈아타게 되었습니다.
개인 맥북 프로(2014년)가 있긴 한데, 잘 열어 보지 않게 되네요.
한번 싹 정리를 하고 다시 사용을 한다고 하지만 게으름에 정리를 못하고 있습니다.
음악 녹음용으로 산건데... 음악도 안하고... 뭐 그렇네요.

사실 맥북 프로의 어마무시한 장점은 키라이트라고 생각합니다.
저는 애들을 키우면서 밤에 공부하거나 밤에 이렇게 글을 쓰는데...
지금 HP 엘리트북은 그런 기능은 없습니다.
뭐 터치 모니터라서 팬으로 그림을 그릴 수 있는 장점이 있긴 하지만요

아.. 이 이야기를 하려는 것은 아닌데..
회사를 옮기게 된 덕에 AWS 에서 Azure 를 사용하게 되었습니다.

# Storage 를 편하게 하는 NFS
아무래도 Cloud 를 사용하면서 제일 먼저 사용할 수 있을 기능은 Storage 라고 생각합니다.
얼마나 편하게 사용할 수 있는 옵션을 주는 지가 중요하다고 생각합니다.

만약 엄청 느린 Web UI 에 파일은 하나씩만 올릴 수 있는 Cloud Storage 라면...
생각만 해도 아찔합니다.

당연히 REST API 지원도 해야하고 여러 옵션들을 주면 좋을 것이라고 생각합니다.

그 중에서 NFS 는 좋은 옵션이라고 생각합니다.
물론 파일을 한번에 왕창 올리는 경우, 관리 이슈가 조금 덜한 경우에 좋은 옵션이겠죠?

# Azure 의 NFS 지원
Azure 의 Storage 는 NFS 를 지원합니다.

**NetApp** 과 Azure 는 좋은 관계를 가지고 있습니다.
NetApp 솔루션을 통해서 Azure 에서 NFS Storage 를 사용할 수 있습니다.  

[공식 안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-netapp-files/azure-netapp-files-create-volumes)

NetApp 도 있지만 Azure 자체적으로 NFS 를 사용할 수 있습니다.
**Azure File** 은 NFS 및 다른 프로토콜을 사용하여 파일을 관리하기 좋은 솔루션입니다.  

[공식 안내 문서](https://docs.microsoft.com/ko-kr/azure/storage/files/storage-files-how-to-create-nfs-shares?tabs=azure-portal)

Azure File 도 있지만 오늘 이야기 하고 싶은 기능은 **Azure Blob** 입니다.

Azure Blob 은 가장 기본적은 Azure Storage 기능입니다.
Azure Blob Storage 를 사용하면 기본적으로 저장 공간으로 사용할 수도 있습니다.
동영상 등 미디어를 저장하는 용도나 로그등을 저장하는 용도로도 사용할 수 있습니다.
그리고 빅데이터 분석 전용 Storage 로도 사용할 수 있습니다.

그리고 Static Web Site 를 구축할 수도 있으며 CDN을 쉽게 연결할 수도 있습니다.

기능 뿐만 아니라 관리도 수월합니다. REST API 및 여러 언어의 SDK 를 제공하고 있고 NFS 나 Blobfuse 와 같은 다양한 방식으로 Storage 를 관리할 수 있습니다. Storage Explorer 라는 툴로도 관리가 가능합니다. 

게다가 저렴도 합니다.(지극히 개인적인 생각입니다.)

소개가 길었습니다. 이러한 Blob Storage 도 NFS 를 지원합니다.  

[공식 안내 문서](https://docs.microsoft.com/ko-kr/azure/storage/blobs/network-file-system-protocol-support)
  
Azure 서비스들을 아래와 같이 정리해볼 수 있을 것 같습니다.    

서비스 | 지원
---:|---:
Azure Blob | NFSv3
Azure File | NFS 4.1
Azure NetApp Files | NFSv3 및 NFSv 4.1  
  


# 제약 사항
Azure Blob 의 NFS 기능은 아직 `Preview` 기능입니다.
사용자들이 미리 사용하고 피드백을 받는 단계라서 다소 사용에 불안정한 요소가 있을 수 있습니다.
그렇다고 매일 장애가 나는 그런 서비스를 말하는 것은 아닙니다.
수시로 개발된 기능이 업데이트 되기에 서비스가 불안할 수 있을 뿐 다른 상용 서비스에 준하는 퀄리티를 살짝 기대해볼 수도 있습니다.

어쨌든 그래서 사용을 하다보면 mount point 가 연결되지 않을 수 있습니다.

이 경우 mount point refresh 가 필요합니다.
(물론 Network 상의 문제로 연결이 되지 않는 것을 이야기 하는 것이 아닙니다.)
`umount` & `mount` 를 하여 새롭게 mount 를 하면 무리 없이 사용할 수 있습니다.

종종 `df` 를 사용하여 mount point 가 사라진 경우, `mount` 를 사용하여 목록을 확인하여 mount point 를 재확인하여 `umount` 를 할 수 있습니다.


# 마치며
Azure 의 Preview 기능중 Blob 의 NFS 및 Blobfuse 는 사용을 극대화 해줄 수 있는 기능이라고 생각합니다. 다만 Preview 라 중간중간 손이 가긴 하지만 아주 작은 방법으로 문제를 처리하여 사용할 수 있습니다.