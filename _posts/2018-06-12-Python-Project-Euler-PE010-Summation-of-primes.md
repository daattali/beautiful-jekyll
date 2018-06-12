---
layout: post
title: PE010 Summation-of-primes
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-12
# 2018-06-12-Python-Project-Euler-PE010-Summation-of-primes
---
Tìm tổng các số nguyên tố nhỏ hơn 2 triệu.


## Problem 10: Summation-of-primes
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.



## Đề bài
Các số nguyên tố nhỏ hơn 10 có tổng là:  2 + 3 + 5 + 7 = 17.

Hãy tìm tổng các số nguyên tố nhỏ hơn 2 triệu.

## Phân tích đề bài:
Bài toán này, tôi mất 2 ngày để tìm hiểu cách làm tối ưu nhưng càng làm càng...làm thời gian chạy chương trình tăng lên.

Cuối cùng lại quay về cách làm "trâu bò".


```Python

import math

UPPER_LIMIT = 2000000


def is_prime(number):
    if number <= 1:
        return False
    elif number <= 3:
        return True
    elif not number % 2:
        return False
    max_range = int(math.sqrt(number)) + 1
    for counter in range(3, max_range, 2):
        if not number % counter:
            return False
    return True


def calc_summation_of_primes():
    sum_of_prime = 2
    number = 3
    while number <= UPPER_LIMIT:
        if is_prime(number):
            sum_of_prime += number
        number += 2
    return sum_of_prime


if __name__ == "__main__":
    import time
    start = time.time()
    ##
    result = calc_summation_of_primes()
    ##
    done = time.time()
    elapsed = done - start
    print("Prime sum of all primes below {} is {}".format(UPPER_LIMIT, result))
    print("elapsed time: {}s".format(elapsed))


```

Thời gian chạy trên máy của tôi:
```
Nguyens-MacBook-Pro:PE-010 vinh.nguyenquang$ python3 summation_of_primes.py
Prime sum of all primes below 2000000 is 142913828922
elapsed time: 6.484667062759399s

```

Buồn thật, bài PE đầu tiên có thời gian chạy > 1s.

Source-code:
[PE-010](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-010)
