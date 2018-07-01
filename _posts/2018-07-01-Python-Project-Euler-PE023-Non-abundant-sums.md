---
layout: post
title: PE023-Non-abundant-sums
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-07-01
# 2018-06-26-Python-Project-Euler-PE023-Non-abundant-sums
---
Tìm tổng các số nhỏ hơn 28123 không được biểu diễn bởi 2 số abundant.


## Problem PE023-Non-abundant-sums
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.


## Đề bài
Một perfect number là một số mà tổng các ước số của nó bằng chính số đó. 

Ví dụ với số 28 là một perfect number: 1 + 2 + 4 + 7 + 14 = 28.

Một số n được gọi là deficient (khuyết thiếu) nếu tổng các ước số nhỏ hơn n.

Và gọi là abundant (dồi dào) nếu tổng các ước số lớn hơn n.

Số 12 là abundant number nhỏ nhất. 12 có tổng các ước số 1 + 2 + 3 + 4 + 6 = 16.

Số nhỏ nhất có thể viết bằng tổng của 2 số abundant là 24.

Bằng các phân tích toán học, người ta đã chỉ ra rằng tất cả các số nguyên lớn hơn 28123 có thể viết bằng tổng hai số abundant. 

Tìm tổng của tất cả các số nguyên dương mà không thể được viết là tổng của hai số abundant.






## Phân tích đề bài:

Bài toán này có thể tách thành các phần: 
- Tìm tất cả các số dồi dào nhỏ hơn 28123
- Tạo và đánh dấu tất cả các số có thể được tạo thành tổng của hai số dồi dào
- Tính tổng tất cả các số không được đánh dấu



Với phần tìm các ước số, dưới đây là một cách làm khá hay:

1. Đầu tiên là tìm các số dồi dào nhỏ hơn 28123

Như định nghĩa bên trên thì số dồi dào là số có tổng các ước số lớn hơn số đó.

Như vậy chúng ta phải tìm tổng các ước số của số đó trước. 


```Python

def get_sum_divisor_numbers(number):
    if number in sum_divisor_dict:
        return sum_divisor_dict[number]
    sqrt_of_number = int(math.sqrt(number))
    sum_total = 1
    if number == sqrt_of_number * sqrt_of_number:
        sum_total += sqrt_of_number
        sqrt_of_number -= 1
    for index in range(2, sqrt_of_number + 1):
        if number % index == 0:
            sum_total += index + number // index
    sum_divisor_dict[number] = sum_total
    return sum_total
```

Sau đó kiểm tra xem số đó có phải là abundant number không

```Python

def is_abundant_number(number):
    sum_number = get_sum_divisor_numbers(number)
    if number < sum_number:
        return True
    else:
        return False
```

2. Tìm tất cả các số abundant nhỏ hơn 28123

```Python

def get_all_abundant_number():
    bundant_numbers = []
    for number in range(12, LIMIT_NUMBER + 1):
        if is_abundant_number(number):
            bundant_numbers.append(number)
    return bundant_numbers

```


3. Tìm các số là tổng của 2 số abundant và các số còn lại.
Để tìm tất cả các số là tổng của 2 số abundant, tạo 2 vòng lặp duyệt các số trong danh sách bundant_numbers.

Do chúng ta có giới hạn đầu trên là LIMIT_NUMBER = 28123 nên chúng ta có thể giảm số vòng lặp bằng cách kiểm tra cho tổng 2 số nhỏ hơn LIMIT_NUMBER.

Để tìm các số < LIMIT_NUMBER và không phải là tổng của 2 số abundant, tôi đưa ra một cách là xây dựng một danh sách các số từ 0 đến LIMIT_NUMBER. Sau đó nếu số nào là tổng 2 số abundant thì chuyển giá trị trong danh sách theo vị trí index thành 0.

Cuối cùng ta thu được một list các số thoả mãn yêu cầu.

```Python

def find_sum_all_non_abundant_sums():
    bundant_numbers = get_all_abundant_number()
    limit_numbers = [index for index in range(0, LIMIT_NUMBER + 1)]
    for number_1 in bundant_numbers:
        for number_2 in bundant_numbers:
            if number_1 + number_2 <= LIMIT_NUMBER:
                limit_numbers[number_1 + number_2] = 0
            else:
                break
    return sum(limit_numbers)
```



```
Thời gian chạy bài toán

```
The sum of all numbers below 28123 that cannot be written as the sum of two abundant numbers is 4179871
elapsed time: 4.60374903678894s


```

Thời gian chạy vẫn nhỏ hơn 60s. Có lẽ cũng chưa cần phải tối ưu tiếp.



Source-code:
[PE-023](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-023)
