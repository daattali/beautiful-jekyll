---
layout: post
title: PE014-Longest-Collatz-sequence
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-18
# 2018-06-18-Python-Project-Euler-PE014-Longest-Collatz-sequence
---
Tìm số nhỏ hơn 1 triệu có độ dài chuỗi Collatz lớn nhất.


## Problem 14:Longest-Collatz-sequence
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.


## Đề bài
Đây là bài toán có tên "chuỗi Collatz", dựa trên thuật toán là: Cho một số khởi đầu, số tiếp theo trong chuỗi được tính như sau
```
n -> n/2 (nếu n là số chẵn)
n -> 3n + 1 (nếu n là số lẻ)

```

Chuỗi sẽ dừng lại đến khi gặp được số tiếp theo là số 1.

Theo lý thuyết trên thì mọi số tự nhiên đều có thể biểu diễn thành chuỗi Collatz.

Ví dụ: Lấy số đầu tiên là 13 thì chuỗi Collatz là:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

Tổng số phần tử của chuỗi là 10 phần tử. 10 được gọi là độ dài của chuỗi.

Yêu cầu: Tìm số nhỏ hơn 1 triệu có độ dài chuỗi Collatz lớn nhất.


## Phân tích đề bài:
Với đề bài này, nếu làm một cách "trâu bò", bài toán sẽ giải quyết như sau:
- Đặt 1 vòng lặp từ 1 đến 1.000.000. Lấy ra từng number là số đầu tiên của chuỗi Collatz.
- Thực hiện theo thuật toán Collatz để lấy ra độ dài chuỗi.


```Python
def count_collatz_sequence(number):
    count = 1
    while number != 1:
        if number % 2:
            number = 3 * number + 1
        else:
            number = number // 2
        count += 1
    return count
```

Tôi đã từng làm cách này và kết quả thực hiện ra mất khoảng 10' gì đó --> Rất cần 1 phương pháp tối ưu bài toán. Nghĩ đến phương pháp thường dùng trong tối ưu truy vấn database hoặc truy nhập web là phương pháp đặt "cache".

Để ý đến chuỗi Collatz với số 13.
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1 : 10 terms
26 -> 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1 : 11 terms

Collatz(26) = Collatz(13) + 1

Nếu ta lưu trữ Collatz(13) thì đến khi tìm Collatz(26) chỉ cần gọi ra và + 1. Như vậy có khả năng sẽ giảm thiểu 

```Python
UPPER_LITMIT = 1000000


def find_longest_collatz_sequence():
    count_cache = {1: 1, 2: 2}
    max_lenght = 2
    max_lenght_number = 2
    for sequence in range(3, UPPER_LITMIT + 1):
        lenght = 1
        number = sequence
        while number != 1:
            if number % 2:
                number = 3 * number + 1
            else:
                number = number // 2
            if number in count_cache:  # count_cache[number] != -1:
                lenght += count_cache[number]
                break
            lenght += 1
        count_cache[sequence] = lenght
        if max_lenght < lenght:
            max_lenght = lenght
            max_lenght_number = sequence
    return max_lenght_number, max_lenght


if __name__ == "__main__":
    import time
    start = time.time()
    result = find_longest_collatz_sequence()
    done = time.time()
    print("The starting number {} produces a sequence of {}".format(*result))
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))
```

Thời gian chạy trên máy của tôi:
```
The starting number 837799 produces a sequence of 525
elapsed time: 1.7523188591003418s

```




Source-code:
[PE-014](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-014)
