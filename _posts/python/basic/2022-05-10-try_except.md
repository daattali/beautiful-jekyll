---
layout: single
title: try-except 예외처리
tags: [try-except]
categories: python
---

try-except는 파이썬 예외 처리 시 사용할 수 있다.    
## 문법
```python
try: 
    # 실행내용
    raise Exception("에러테스트") # 에러 발생시키기
except:
    # 에러 발생 시 분기
else : 
    # 예외가 발생하지 않았을 때 분기
finally:
    # 예외와 상관없이 실행
```
  
  
## 에러 만들기
Exception을 상속해 만들 수 있다.
```python
class CustomException(Exception):
    def __init__(self):
        super().__init__('error message')
```
  
  
## 디버깅을 위한 에러 출력 예시
예외처리 시, 에러 내용을 출력하고 싶으면 아래를 참고한다.
```python
try:
    raise TypeError("Hello, World!")  # line 2
except Exception as e:
    print(
        type(e).__name__,          # TypeError
        __file__,                  # /tmp/example.py
        e.__traceback__.tb_lineno,
        e
    )
```

## @ 참고
[에러와 처리 방법에 대한 공식 문서](https://docs.python.org/ko/3/tutorial/errors.html)