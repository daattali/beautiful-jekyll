---
layout: post
title: PE016-Power-digit-sum
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-19
# 2018-06-21-Python-Project-Euler-PE018-Maximum-path-sum-I.md
---



## Problem PE016-Power-digit-sum
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

!(small)[/img/2018-06-21-trig/small.png]

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

!(big)[/img/2018-06-21-trig/big.png]

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)



## Đề bài
Đứng từ đỉnh của tam giác, bắt đầu di chuyển xuống dưới, giá trị nào cho tổng với giá trị trước đó lớn hơn sẽ được ưu tiên di chuyển vào.

!(small)[/img/2018-06-21-trig/small.png]

Với ví dụ này: 3 + 7 + 4 + 9 = 23.

Hãy tìm tổng lớn nhất của đường đi với tam giác lớn dưới đây:
!(big)[/img/2018-06-21-trig/big.png]





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
