---
layout: post
title: PE-006 Sum square difference
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-09
---
Tính hiệu của bình phương của tổng các số tự nhiên và tổng bình phương của các số đó.

## Problem 6: Sum square difference

```
The sum of the squares of the first ten natural numbers is,

1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
```


## Đề bài
Tổng của bình phương 10 số tự nhiên đầu tiên: 

1^2 + 2^2 + ... + 10^2 = 385

Bình phương của tổng 10 số tự nhiên đầu tiên:

(1 + 2 + ... + 10)^2 = 55^2 = 3025

Hiệu của chúng là: 3025 - 385 = 2640.

Với cách làm trên, hãy tính với 100 số tự nhiên đầu tiên.



## Phân tích đề bài:
Bài toán rất dễ để làm với vòng lặp từ 1 đến 100 và tính 2 tổng.

với N = 100 thì thời gian chạy khá ngắn.
Nhưng N = 1.000.000 thì thời gian chạy sẽ rất khủng khiếp.

Như ở bài PE-001, chúng ta đã có công thức tính tổng các số tự nhiên liên tiếp từ 1 - N là: N(N+1)/2.

Việc cần làm tiếp theo là tính tổng bình phương các số. Nếu đã từng học môn đại số, chúng ta sẽ biết đến công thức:

![https://trans4mind.com/personal_development/mathematics/series/sumSquaresNatNumbersFormulae.gif
](https://trans4mind.com/personal_development/mathematics/series/sumSquaresNatNumbersFormulae.gif)

Công thức này được chứng minh và giải thích tại trang: [sumNaturalSquares](https://trans4mind.com/personal_development/mathematics/series/sumNaturalSquares.htm)


Áp dụng 2 công thức trên vào bài toán của chúng ta:

```Python


def find_sum_square_difference(number=100):
    sum_number = number * (number + 1) / 2
    sum_square = number * (number + 1) * (2 * number + 1) / 6
    return sum_number * sum_number - sum_square

```

Kết quả thực thi:

```
Nguyens-MacBook-Pro:PE-006 vinh.nguyenquang$ python3 sum_square_difference.py
find_sum_square_difference of 100 result:
25164150.0
elapsed time: 3.981590270996094e-05s
Nguyens-MacBook-Pro:PE-006 vinh.nguyenquang$ python3 sum_square_difference.py
find_sum_square_difference of 1000000 result:
2.5000016666641667e+23
elapsed time: 9.608268737792969e-05s

```


## Kết luận:
Toán học thật là tuyệt vời, nếu biết các công thức toán học, ta không phải thực hiện các bài toán "vét cạn" bằng vòng lặp nữa.



Source-code:
[PE-006](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-006)
