---
layout: post
title: PE-005 Smallest multiple
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-09
---
Tìm bội số chung nhỏ nhất của các số từ 1 - 20.

## Problem 5: Smallest multiple

```
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
```


## Đề bài
2520 là bội số chung nhỏ nhất của các số từ 1-10. 
Hãy tìm bội số chung nhỏ nhất của các số từ 1-20


## Phân tích đề bài:
Bội số là số chia hết cho 1 số. Bội số chung của {n} số là số chia hết cho tất cả các số trong {n}
Đề bài rất dễ để đưa ra cách giải quyết "trâu bò", chỉ việc đặt 1 phép toán tăng dần số smallest_multiple_number và thực hiện phép kiểm tra smallest_multiple_number đồng thời chia hết cho các số từ 1-20.

```Python
def is_divided_multi_number(number, max_div):
    for div in range(2, max_div + 1):
        if number % div:
            return False
    return True


def find_smallest_multiple_number_v1():
    smallest_multiple_number = 1
    while True:
        smallest_multiple_number += 1
        if is_divided_multi_number(smallest_multiple_number, 20):
            break
    return smallest_multiple_number

```

Cách làm đơn giản nhưng thời gian ra đáp án khá tệ.

```
Nguyens-MacBook-Pro:PE-005 vinh.nguyenquang$ python smallest_multiple_number.py
find_smallest_multiple_number_v1 result:
232792560
elapsed time: 162.805028915s

```

Tiếp tục tối ưu bài toán, ta thấy giá trị 20 là giá trị lớn nhất của các số bị chia --> thay vì tăng số lên 1 sau mỗi vòng lặp, ta có thể tăng lên thành 20. 

```Python

def find_smallest_multiple_number_v2():
    smallest_multiple_number = 0
    while True:
        smallest_multiple_number += 20
        if is_divided_multi_number(smallest_multiple_number, 20):
            break
    return smallest_multiple_number
```

```
Nguyens-MacBook-Pro:PE-005 vinh.nguyenquang$ python smallest_multiple_number.py
find_smallest_multiple_number_v2 result:
232792560
elapsed time: 10.7491838932s

```

Thời gian chạy đã khá hơn nhưng vẫn chưa phải best-solution.

## Áp dụng tư duy toán học vào giải quyết bài toán PE-005
Như bài toán PE-003, ta thấy mỗi số không phải là số nguyên tố đều có thể là tích của các số nguyên khác.

Ở phép toán kiểm tra chia hết, ta để ý số chia hết cho 6 sẽ chia hết cho 2 và 3 => Thay vì kiểm tra chia hết cho 2,3, 6 chỉ cần kiểm tra chia hết cho 6.
Tương tự, 18 chia hết cho 2, 3, 6, 9 => Kiểm tra chia hết cho 18 thay vì kiểm tra chia hết cho 2, 3, 6, 9.

Vấn đề cần đặt ra là làm thế nào để tìm ra 18 ?

Ta sẽ đi đến bài toán ước số chung lớn nhất (UCNN) giữa 2 số. 
Ví dụ 2 * 3  = 6 --> UCNN(6, 6) = 1.
UCNN(6, 9) = 3. ==> 18 = (6 // 3) * 9 = 18

Trong Python, tìm UCNN ta có thể sử dụng thư viện `math`:

```Python
>>> import math
>>> math.gcd(6,9)
3

```

Mã nguồn thay thế cho vòng lặp khủng khiếp phía trên

```Python

import math


def find_smallest_multiple_number_v3():
    smallest_multiple_number = 2
    for number in range(3, 21):
        smallest_multiple_number = number * smallest_multiple_number // math.gcd(smallest_multiple_number, number)
    return smallest_multiple_number

```


```
Nguyens-MacBook-Pro:PE-005 vinh.nguyenquang$ python3 smallest_multiple_number.py
find_smallest_multiple_number_v3 result:
232792560
elapsed time: 4.100799560546875e-05s
```

Kết quả thật tốt đúng không?


## Kết luận:
Vòng lặp là tác nhân gây ra việc tăng thời gian thực hiện của code. Nếu giảm thiểu được vòng lặp, thời gian thực hiện sẽ ít đi.

162.805028915s  ==> 10.7491838932s ==>  4.100799560546875e-05s




Source-code:
[PE-005](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-005)
