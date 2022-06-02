---
layout: single
title: 파일 입출력을 위한 파이썬 함수 (open, close, write, read..)
tags: [python library, open, close, write, read, seek]
categories: python
---

파이썬에서 파일 입출력을 위해, 파일을 여는 open과 close 내장함수를 포함한 여러 함수가 지원된다.   


## open 함수

open함수는 아래와 같다.
```python
open(file, mode='r', buffering=- 1, encoding=None, errors=None, newline=None, closefd=True, opener=None)
```
mode에는 아래와 같은 옵션을 줄 수 있다.
![img.png](../../img.png)
  
encoding에서는 여러 옵션을 줄 수 있고, cp949를 줄 수도 있다.
```python
    with open(path, 'r', encoding='cp949') as f:
		rls = f.readlines()
```


  



## *with open 문법
open함수를 호출한 후 자원반환을 위해 close를 불러와야 하는데, 이를 with문을 이용해 블록이 끝날 때 자동으로 처리할 수 있다.
```python
with open('file.md') as f:
	print(f.readline(), end="")
```
## @참고
파일입출력 참고 블로그 : https://blockdmask.tistory.com/454  
인코딩 문제 : https://pgh268400.tistory.com/296