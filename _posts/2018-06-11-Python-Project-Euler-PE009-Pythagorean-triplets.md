---
layout: post
title: PE-009 Pythagorean-triplets
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-11
# 2018-06-11-Python-Project-Euler-PE009-Pythagorean-triplets
---
Tìm tích của 3 số là cạnh của tam giác py-ta-go có tổng bằng 1000.


## Problem 9: Pythagorean-triplets

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.

Find the product abc.



## Đề bài
Định lý Pythago về tam giác vuông có 3 cạnh a, b, c thoả mãn a < b < c như sau: a^2 + b^2 = c^2

Ví dụ: tam giác vuông có 3 cạnh 3 < 4 < 5 >> 3 ^2 + 4 ^ 2 = 5 ^2

Hãy tính của các cạnh trong tam giác vuông có tổng 3 cạnh là 1000.

## Phân tích đề bài:

Định lý Py-tha-go, được học sinh ở Việt Nam tiếp cận từ cấp 2 trong môn hình học. 

Với bài toán này, cách đơn giản nhất là duyệt 2 vòng lặp, vòng lặp lặp 1 từ 1 - 1000 để lấy a, vòng lặp 2 từ a đến (1000 - a) để lấy b, c = 1000 - a - b.

Sau đó kiểm tra a^2 + b^2 = c^2 thì lấy ra a, b, c.


Theo như một số tài liệu toán học thì Mr Euclid có cách làm khá hay để giải quyết vòng lặp 2 lần để giải quyết bài toán này. Cách làm khá hay nhưng...đọc lòng vòng quá, không hiểu được nên... đành quay lại tối ưu cách làm "trâu bò" vậy.

Đầu tiên là a < b < c --> a < a + m < a + n (n > m)

a + b + c = sum_triple --> 3 * a + m + n = sum_triple --> a = (sum_triple - m - n)/3

Như vậy vòng lặp thứ 1 đã giảm xuống 1 khoảng khá lớn chỉ còn từ 1 đến sum_triple // 3

a + b + c = sum_triple --> a + 2 * b + n = sum_triple --> b = (sum_triple - a - n) / 2

Vòng lặp thứ 2 giảm xuống tiếp từ a đến sum_triple // 2


```Python
def find_pythagorean_triplets(sum_triple):
    for a in range(1, int(sum_triple // 3)):
        for b in range(a, int(sum_triple // 2)):
            c = sum_triple - a - b
            if a * a + b * b == c * c:
                return (a, b, c), a * b * c
    return None, None


if __name__ == "__main__":
    import time
    sum_triple = 1000
    start = time.time()
    result = find_pythagorean_triplets(sum_triple)
    print("The Pythagorean triple is {},  the sum is {} , the product is {}".format(result[0], sum_triple, result[1]))
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))

```

Thời gian chạy cho bài toán giảm xuống khá nhiều:
```
The Pythagorean triple is (200, 375, 425),  the sum is 1000 , the product is 31875000
elapsed time: 0.02037191390991211s

```

Source-code:
[PE-009](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-009)
