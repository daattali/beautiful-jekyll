---
layout: single
title: 데코레이터 사전 개념과 데코레이터 활용 (first class function, closure, decorator)
tags: [decorator, first class function, decorator]
categories: python
---

## 사전개념
데코레이터를 이해하기 위해서는 아래 두 가지 개념이 선행되어야 한다.
### 1. First Class Function
 프로그래밍 언어에서 함수를 다른 변수와 동일하게 다룰 경우 First class function을 가졌다고 표현할 수 있다. 이 경우,
- 함수가 함수를 반환할 수 있다.
- 변수에 할당이 가능하다.
- 다른 함수의 인수로 제공될 수 있다.
```python
def square(x):
    return x * x
def get_func(func):
    if func == "square":
        return square  # 함수가 함수를 반환할 수 있다.
    else :
        return lambda x : x
sqf = get_func("square") # 변수에 할당이 가능 하다.
_list = [1,2,3,4,5]
square_list = map(sqf, _list) # 다른 함수의 인수로 제공될 수 있다.
print(sum(square_list))
```
### 2. Closer
퍼스트클래스 함수를 지원하는 언어의 네임 바인딩 기술이며, 어떤 함수를 함수 자신이 가지고 있는 환경과 함께 저장한 레코드이다. 
함수가 가진 프리변수를 클로저가 만들어지는 환경에 맵핑하여 주는 역할을 한다.

```python
def outer_func():
    message = "HI"
    
    def inner_func():
        print(message)

    return inner_func()
outer_func()
# out
# Hi
```
   
   
message는 inner_func 함수 블럭 내에서 정의되지 않았지만, inner_func에서 사용되었으므로 프리변수라고 부른다.   
inner_func의 ()를 없애고 다시 실행할 경우, Hi는 출력되지 않는다.
```python
def outer_func():
    message = "HI"
    
    def inner_func():
        print(message)

    return inner_func
my_func = outer_func()
```
   
   
이 상태에서 my_func()를 추가하면, Hi message가 출력된다.
```python
my_func()
#out
# Hi
```
   
   
이미 outer_func 함수는 호출이 끝났음에도 불구하고 outer_func의 로컬 변수(inner_func의 프리변수)인 message가 참조되었으며,
이는 클로저에 의해 프리변수 값을 어딘가에 저장했기 때문이다.   
dir(my_func)을 이용해 my_func 내의 네임 스페이스를 확인해보면, __closure__ 를 확인할 수 있다.

## 데코레이터
아래와 같이 closure를 이용해, 기존 함수가 호출되기 전에 해당 함수 이름을 출력하는 기능을 추가할 수 있는 wrapper 함수를 만든다고 하자.
```python
def decorator_function(original_function):
    def wrapper_function():
        print(f'call func : {original_function.__name__}')
        return original_function()

    return wrapper_function


def display_1():
    print('display_1')


def display_2():
    print('display_2')


display_1 = decorator_function(display_1)  # 1
display_2 = decorator_function(display_2)  # 2

display_1()
print()
display_2()
```
위와 같은 처리 방법은 데코레이터를 이용해 간소화할 수 있다.
```python
def decorator_function(original_function):
    def wrapper_function():
        print(f'call {original_function.__name__}')
        return original_function()

    return wrapper_function

@decorator_function
def display_1():
    print('display_1')
''
@decorator_function
def display_2():
    print('display_2')


display_1()
display_2()
```
   
   
만약 데코레이터를 추가할 함수에 임의의 인자가 있다면 아래와 같이 데코레이터 함수를 변경하여 해결 가능하다.
```python
def decorator_function(original_function):
    def wrapper_function(*args, **kwargs):
        print(f'call {original_function.__name__}')
        return original_function(*args, **kwargs)
    return wrapper_function


@decorator_function
def display():
    print('display.')


@decorator_function
def display_info(name, age):
    print(f'display_info({name}, {age}).')


display()
print()
display_info('John', 25)
```

복수의 데코레이터를 사용하기 위한 방법 (wraps) 등은 아래 decorator 정리 블로그 참고.

## @ 참고

[first class function 정리 블로그](https://schoolofweb.net/blog/posts/%ED%8C%8C%EC%9D%B4%EC%8D%AC-%ED%8D%BC%EC%8A%A4%ED%8A%B8%ED%81%B4%EB%9E%98%EC%8A%A4-%ED%95%A8%EC%88%98-first-class-function/)   
[closure 정리 블로그](https://schoolofweb.net/blog/posts/%ED%8C%8C%EC%9D%B4%EC%8D%AC-%ED%81%B4%EB%A1%9C%EC%A0%80-closure/)   
[decorator 정리 블로그](https://schoolofweb.net/blog/posts/%ED%8C%8C%EC%9D%B4%EC%8D%AC-%EB%8D%B0%EC%BD%94%EB%A0%88%EC%9D%B4%ED%84%B0-decorator/)
