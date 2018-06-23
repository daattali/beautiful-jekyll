---
layout: post
title: PE020-Sum-of-Digits-in-100!
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-23
# 2018-06-23-Python-Project-Euler-PE020-Sum-of-Digits-in-100gt
---



## Problem PE020-Sum-of-Digits-in-100!
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!



## Đề bài
n! = n × (n − 1) × ... × 3 × 2 × 1

Ví dụ: 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800

Tổng các chữ số của số 10! là: 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Hãy tính tổng các chữ số của số 100!



## Phân tích đề bài:

Đề bài cũng khá rõ ràng, tính giai thừa sau đó tính tổng các chữ số của kết quả.



```Python

import math

NUMBER = 100


def sum_number_factorial():
    factorial_number = math.factorial(NUMBER)
    return sum(int(index) for index in str(factorial_number))


```
Thời gian chạy bài toán

```
sum_all digit in factorial of 100 is 648
elapsed time: 0.000347137451171875s

```

Source-code:
[PE-020](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-020)
