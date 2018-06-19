---
layout: post
title: PE-007 10001st prime
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-10
---
Tìm số nguyên tố thứ 10001?

## Problem 7: 10001st prime

```
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
```


## Đề bài
6 số nguyên tố đầu tiên là: 2, 3, 5, 7, 11 và 13.
Số thứ 6 là 13.

Hãy tìm số nguyên tố thứ 10001 ?



## Phân tích đề bài:
Như bài PE-003, chúng ta đã có định nghĩa và cách tìm số nguyên tố 

Bài toán này chỉ cần 1 biến index để đánh dấu số nguyên tố thứ bao nhiêu và 1 biến number cho vào vòng lặp và thực hiện tăng dần là có thể giải quyết được bài toán.

Điều khủng khiếp ở bài toán này chính là con số index =  10001 không hề nhỏ.

Buồn là...tôi chưa có cách nào để giải quyết bài toán này ngoài việc "vét cạn" bằng vòng lặp. Nhưng chúng ta sẽ thực hiện bằng cách dựa vào tư duy: Số nguyên tố luôn là số lẻ, và chúng ta bắt đầu từ số 3, số tiếp theo sẽ là 5, 7....


```
UPPER_LIMIT = 10001


def is_prime(number):
    if number <= 1:
        return False
    if number == 2:
        return True
    counter = 3
    while counter * counter <= number:
        if number % counter:
            counter += 2
        else:
            return False
    return True


def find_10001st_prime_number():
    counter = 2
    prime_number = 3
    while counter < UPPER_LIMIT:
        prime_number += 2
        if is_prime(prime_number):
            counter += 1
    return prime_number

```

Thời gian chạy cho bài toán này khá ổn:
```
Nguyens-MacBook-Pro:PE-007 vinh.nguyenquang$ python 10001st_prime_number.py 
find_10001st_prime_number of result:
104743
elapsed time: 0.188479185104s

```

Source-code:
[PE-007](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-007)
