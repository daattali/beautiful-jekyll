---
layout: post
title: PE016-Power-digit-sum
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-19
# 2018-06-19-Python-Project-Euler-PE016-Power-digit-sum.md
---
Tính tổng các chữ số của 2 ^ 10000?


## Problem PE016-Power-digit-sum
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?

## Đề bài
2^15 = 32768 và tổng các chữ số của nó là: 3 + 2 + 7 + 6 + 8 = 26

Tính tổng các chữ số của số 2 ^ 10000?


## Phân tích đề bài:
Đầu bài dễ hiểu quá mức rồi. 

Đầu tiên là tính 2 ^ 10000 rồi convert số sang dạng chuỗi và cộng lại :) 




```Python
import math


def calc_power_digit_sum(power):
    numbers = int(math.pow(2, power))
    # print(numbers)
    return sum([int(number) for number in str(numbers)])


if __name__ == "__main__":
    import time
    start = time.time()
    power = 1000
    result = calc_power_digit_sum(power)
    done = time.time()
    print("The sum digits of 2^{} is: {}".format(power, result))
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))

```

Thời gian chạy trên máy của tôi:
```
The sum digits of 2^1000 is: 1366
elapsed time: 0.00020003318786621094s

```




Source-code:
[PE-016](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-016)
