---
layout: single
title: 파일에 대한 고수준 연산을 지원하는 파이썬 라이브러리 (shutil)
tags: [python library, shutil, 파일이동, 파일복사, 이름변경]
categories: python_lib
---
shutil 라이브러리는 파일 및 파일들에 대한 고수준 연산(이동,삭제,복사 등)을 지원한다.

## 1.모듈 설치
```
import shutil
```

## 2.기능
### 1 파일이동, 이름변경 : shutil.move(src, dst, copy_function=copy2)
src 파일 또는 폴더를 dst 폴더로 이동한다. dst 폴더가 없는 경우 새로 폴더를 생성한다.   
ex)   
shutil.move('test.csv','test_folder')      
   
이름을 변경할 수도 있다.
ex)
shutil.move('test.csv','test2.txt')
### 2 파일복사 : shutil.copy(src, dst, *, follow_symlinks=True)
**파일** src를 파일이나 디렉터리 dst에 복사한다. src와 dst는 path 객체나 문자열이어야 한다.
ex)   
shutil.copy('test.csv','test_folder')

* copy2를 사용할 경우 파일 메타 데이터 보존도 한다. (파일 생성 시간, 수정 시간 등)    
shutil.copy2('test.csv','test_folder')

### 3 폴더복사 : shutil.copytree(src, dst, symlinks=False, ignore=None, copy_function=copy2, ignore_dangling_symlinks=False, dirs_exist_ok=False)
**폴더** src를  폴더 dst에 복사한다.   
ex)   
shutil.copytree('test','test2')

다만 폴더를 복사하려는 데, 상위 폴더가 만들어 있지 않을 경우, os.makedirs를 사용하면 없는 폴더까지 만들어준다.

## @참고
[shutil](https://docs.python.org/ko/3/library/shutil.html)