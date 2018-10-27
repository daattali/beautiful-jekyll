---
layout: post
title: Python-tricks
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Python-tip, Python-trick]
categories: [Python-trick]
date: 2018-07-20
# 2018-07-14-PE025-1000-digit-Fibonacci-number.md
---
Một số "trick" về Python mà một lập trình viên Python nên biết

## Dùng Assert in Python — An Example

Một ví dụ nhỏ về sử dụng Assert trong Python: 

> Cho một sản phẩm và số % discount (giảm giá) của sản phẩm dưới dạng thập phân (10% = 0.1, 20% = 0.2, ...). Hãy tính ra giá của sản phẩm sau khi giảm.

Với đề bài như trên thì output của trường hợp nhập vào discount không hợp lệ thì raise lên một exception chứ không được phép trả về một con số. Lập trình viên phải handle được exception này.

```Python

```


```Python
def apply_discount(product, discount):
    price = int(product['price'] * (1.0 - discount)) 
    assert 0 <= price <= product['price']
    return price
```



```
shoes = {'name': 'Fancy Shoes', 'price': 14900}
apply_discount(shoes, 0.25)
11175

apply_discount(shoes, 2.0)
Traceback (most recent call last):
    File "<input>", line 1, in <module> apply_discount(prod, 2.0)
    File "<input>", line 4, in apply_discount assert 0 <= price <= product['price']
AssertionError
```
