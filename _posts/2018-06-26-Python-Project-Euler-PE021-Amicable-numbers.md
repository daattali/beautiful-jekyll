---
layout: post
title: PE021-Amicable-numbers
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-26
# 2018-06-26-Python-Project-Euler-PE021-Amicable-numbers.md
---
Tìm tổng các số Amicable-pair nhỏ hơn 100000


## Problem PE021-Amicable-numbers
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.




## Đề bài
d(n) được định nghĩa là tổng của các ước số của số n (không kể số n)

Nếu d(a) = b và d(b) = a và a != b --> a và b được gọi là một cặp amicable-pair. Mỗi số a, b được gọi là amicable-number.

Với ví dụ: 220 có các ước số:  1, 2, 4, 5, 10, 11, 20, 22, 44, 55, 110

d(220) = 284. 

Các ước số 284 là 1, 2, 4, 71, 142.

d(284) = 220.

--> 220 và 284 được gọi là cặp amicable-pair.

Tính tổng các số amicable nhỏ hơn 10000.


## Phân tích đề bài:

Bài toán này gồm các phần riêng rẽ:
- Tính ra các ước số của 1 số number.
- Tính ra tổng các ước số d(number).
- Tính ra các ước số của tổng d(d(number))
- Nếu d(number) == d(d(number)) -->  number & d(number) 
- Tính tổng các số number, d(number) lại.

Với phần tìm các ước số, dưới đây là một cách làm khá hay:

```Python

def get_divisor_numbers(number):
    sqrt_of_number = int(math.sqrt(number))
    list_divisor = [1]
    if number == sqrt_of_number * sqrt_of_number:
        list_divisor.append(sqrt_of_number)
        sqrt_of_number -= 1
    for index in range(2, sqrt_of_number):
        if number % index == 0:
            list_divisor.append(number)
            list_divisor.append(number // index)
    return list_divisor
```

Nếu làm cách "trâu bò" sẽ mất khá nhiều thời gian, tôi đưa ra một cách ... nhanh hơn một chút đó là đặt "cache". 

"Cache" gồm có: 
- Cache cho phần tính tổng các ước số.
- Cache cho phần danh sách các số amicable


```Python
import math

LIMIT_NUMBER = 100000
sum_divisor_dict = {}


def get_sum_divisor_numbers(number):
    if number in sum_divisor_dict:
        return sum_divisor_dict[number]
    sqrt_of_number = int(math.sqrt(number))
    sum_total = 1
    if number == sqrt_of_number * sqrt_of_number:
        sum_total += sqrt_of_number
        sqrt_of_number -= 1
    for index in range(2, sqrt_of_number):
        if number % index == 0:
            sum_total += index + number // index
    sum_divisor_dict[number] = sum_total
    return sum_total


def is_amicable_pairs(number):
    sum_number = get_sum_divisor_numbers(number)
    if number == get_sum_divisor_numbers(sum_number) and number != sum_number:
        return True, number, sum_number
    else:
        return False, 0, 0


def get_sum_amicable_pair_numbers():
    list_amicable_pairs = []
    for number in range(5, LIMIT_NUMBER + 1):
        if number not in list_amicable_pairs:
            result = is_amicable_pairs(number)
            if result[0]:
                list_amicable_pairs.append(result[1])
                list_amicable_pairs.append(result[2])
    return sum(list_amicable_pairs)


if __name__ == "__main__":
    import time
    start = time.time()
    result = get_sum_amicable_pair_numbers()
    done = time.time()
    print("The largest sum of all amicable pairs less than {}: {}".format(LIMIT_NUMBER, result))
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))



```
Thời gian chạy bài toán

```
The largest sum of all amicable pairs less than 100000: 852810
elapsed time: 1.5143499374389648s

```

Chỉ hơn 1s cho bài toán này. Cũng không tệ lắm nhỉ :D


Source-code:
[PE-021](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-021)
