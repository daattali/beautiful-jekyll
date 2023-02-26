---
layout: post
title:  "Python Decorators"
date:   2021-12-26 13:11:00 PM
categories: Python
---

Decorators are used extensively in Python and various frameworks like Flask/Django or Logging modules etc

There are 3 steps to creating decorators.

1) Create the decorator, which takes the function that you want to decorate as a parameter. 
2) Create a wrapper function which will take the same parameters as the function that you want to decorate.
3) Decorate the function that you want to decorate with your decorator.

Example ::

```python
def decorator(func):
    def wrapper(*args, **kwargs):
        print(f"args is {args}")
        print(f"kwargs is {kwargs}")
        func(*args, **kwargs)
    return wrapper

@decorator
def Test(a,k=1):
    return a * k

Test(10,k=20)  
```