---
layout: post
title: python technique : f-string
subtitle: Literal String Interpolation
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [f-string, Literal String Interpolation]
---
F-string은 문자열에 f또는 F 접두어를 붙이고 표현식을 {expression} 형태로 작성해
문자열에 파이썬 표현식의 값을 그대로 삽입할 수 있도록 한다.

아래 예시처럼, 선택 포맷 지정자가 표현식 뒤에 올 수 있다.
```python
from math import pi
print(f"Pi is approximately {pi:.3f}.")
# out: Pi is approximately 3.142.
table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}
```

: 열을 맞출 때, f-string 표현식 뒤에 정수를 전달하면 필드의 최소 문자 폭을 맞출 수 있다.
```python
for name, phone in table.items():
    print(f'{name:10} ==> {phone:10d}')
""" 
out:
Sjoerd     ==>       4127
Jack       ==>       4098
Dcab       ==>       7678
"""
```



## @ 참고
[PEP 문서](https://peps.python.org/pep-0498/)  
[7.1.1 포맷 문자열 리터럴](https://docs.python.org/ko/3/tutorial/inputoutput.html)   
[포맷 문자열의 명세 방법](https://docs.python.org/ko/3/library/string.html#formatspec)