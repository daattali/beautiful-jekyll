---
layout: post
title: python library : tarfile
subtitle: 파일 압축풀기를 위한 파이썬 라이브러리
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [python library, tarfile, 파일 압축, 압축 해제, tar]
---
##  CLI로 작업
### 새 tar 아카이브 만들기 : -c
tarfile을 실행하고 -c 뒤에 아카이브 이름을 지정하고 포함해야 하는 파일 또는 디렉터리를 나열.
```commandline
python -m tarfile -c monty.tar spam.txt eggs.txt   # files
python -m tarfile -c monty.tar life-of-brian_1979/ # directory
```
### tar 아카이브 추출 : -e
-e 옵션으로 현재 디렉토리에 tar 아카이브를 추출하거나, 뒤에 이름을 전달해 다른 디렉토리로 추출.
```commandline
python -m tarfile -e monty.tar            # 현재 디렉토리
python -m tarfile -e monty.tar other-dir/ # 다른 디렉토리
```

### tar 아카이브 파일 목록 확인 : -l
tar 아카이브에 있는 파일 목록 확인.
```commandline
python -m tarfile -l monty.tar
```

## python 예시
### tar 아카이브를 현재 작업 디렉터리에 추출
```python
import tarfile
tar = tarfile.open("sample.tar.gz")
tar.extractall()
tar.close()
```

### 리스트 대신 제너레이터 함수를 사용해 TarFile.extractall()로 tar 아카이브의 부분집합을 추출
```python
import os
import tarfile

def py_files(members):
    for tarinfo in members:
        if os.path.splitext(tarinfo.name0)[1] == ".py":
            yield tarinfo

tar = tarfile.open("sample.tar.gz")
tar.extractall(members=py_files(tar))
tar.close()
```

### 파일명 리스트로 압축되지 않은 tar 아카이브를 만드는 방법:
```python
import tarfile
tar = tarfile.open("sample.tar", "w")
for name in ["foo", "bar", "quux"]:
    tar.add(name)
tar.close()
```
```python
# with 문을 사용한 같은 예제
import tarfile
with tarfile.open("sample.tar", "w") as tar:
    for name in ["foo", "bar", "quux"]:
        tar.add(name)
```


## @참고
[참고 블로그](https://velog.io/@changdaeoh/pythonfiledownloadfromurl)    
[공식 문서](https://docs.python.org/ko/3/library/tarfile.html)
