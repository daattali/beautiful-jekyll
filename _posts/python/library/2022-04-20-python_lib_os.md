---
layout: post
title: python library (os)
subtitle: 운영체제 인터페이스를 지원하는 파이썬 라이브러리
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [python library, os]
---
## 현재 파일 또는 폴더의 경로 출력
### 파일의 절대 경로 출력
__file__은 현재 열려있는 파일의 위치와 이름을 가지고 있는 문자열 변수이다.   
os.path.abspath(__file__)   
   
### 파일의 상대 경로 출력   
os.path.realpath(__file__)   
  
### 폴더의 경로 출력
1. os.getcwd()
getcwd 함수는 **현재 작업하고 있는 디렉터리**를 문자열로 반환함.  
    
2. os.path.dirname(os.path.realpath(__file__))   
   
3. os.path.dirname(os.path.abspath(__file__))   

path.dirname 함수는 매개변수로 전달된 경로의 디렉터리를 문자열로 반환.

 


## 폴더 생성
```python
import os
path = './dir/sub'
os.mkdir(path)
```

## @참고
[파이썬 공식문서](https://docs.python.org/ko/3/library/os.html)