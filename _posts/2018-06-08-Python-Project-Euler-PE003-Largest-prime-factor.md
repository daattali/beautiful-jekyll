---
layout: post
title: PE-003 Largest prime factor
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-08
---
Tìm ước số nguyên tố lớn nhất của 600851475143

## Problem 3: Largest prime factor

```
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
```


## Đề bài
Số 13195 là tích của các số nguyên tố: 5, 7, 13 và 29. 
Hãy tìm các ước số là số nguyên tố lớn nhất của số 600851475143 ?


## Phân tích đề bài:
Đầu bài có phần số nguyên tố, như vậy chúng ta phải viết một function kiểm tra một số có phải là số nguyên tố hay không. 

### Số nguyên tố:
Số nguyên tố là số chỉ chia hết cho 1 và chính nó.
Cách đơn giản nhất để kiểm tra number có phải là số nguyên tố không là tạo một nhóm các số từ 2 đến number // 2 + 1 (chia lấy phần nguyên). Nếu number không chia hết cho 1 số nào đó trong nhóm đó --> number là số nguyên tố.

Nhưng cách này chưa phải hiệu quả nhất trong việc kiểm tra một số có phải là số nguyên tố không. Ta có thể thu gọn tập số kiểm tra bằng cách tạo ra một nhóm từ 2 đến căn bậc hai của number + 1.

Ví dụ: 
Kiểm tra số nguyên tố của 36.
36 có các ước số là 2, 3, 6, 9, 18.
căn bậc hai của 36 là 6. --> Chỉ cần kiểm tra từ 2 --> 6 là đủ.

```Python
# prime.py
import math


def is_prime(number):
    if number <= 1:
        return False
    for index in range(2, int(math.sqrt(number)) + 1):
        if not number % index:
            return False
    return True

```


## Cách giải "trâu bò"
Khi đã có phương án tối ưu cho tìm kiếm số nguyên tố, chúng ta sẽ đi giải tiếp bài toán.

Đầu tiên ta sẽ phải xây dựng 1 tập hợp các số từ 2 đến 600851475143,
Với mỗi number trong tập hợp này, nếu 600851475143 chia hết cho number, 
Kiểm tra xem number có phải là số nguyên tố không. 
Nếu là số nguyên tố, so sánh với 1 biến để kiểm tra xem có phải là số lớn nhất không, swap hai số cho nhau nếu cần.

```Python
# bruteforce_pe003.py
from prime import is_prime

VICTIM_NUMBER = 600851475143


def find_largest_prime_factor_by_bruteforce():
    largest_prime_factor = 0
    for number in range(2, VICTIM_NUMBER):
        if not VICTIM_NUMBER % number:
            if is_prime(number):
                if largest_prime_factor < number:
                    largest_prime_factor = number
    return largest_prime_factor


if __name__ == "__main__":
    import time
    print("bruteforce largest_prime_factor result:")
    start = time.time()
    print(find_largest_prime_factor_by_bruteforce())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))


```



Cách làm này thật khủng khiếp về thời gian. Máy tính của tôi tự động kill chương trình này
```
Nguyens-MacBook-Pro:PE-003 vinh.nguyenquang$ python bruteforce_pe003.py
bruteforce largest_prime_factor result:
Killed: 9
```

Có thể các bạn nghi ngờ solution hoặc code của bạn bị sai, hãy thay VICTIM_NUMBER = 13195.
```
bruteforce largest_prime_factor 13195 result:
29
elapsed time: 0.00131297111511s

```
Thời gian chạy cũng không nhanh lắm. Bảo sao khi VICTIM_NUMBER = 600851475143 lại treo.


Tương tự bài toán tính toán số nguyên tố, ta chỉ cần cho vòng lặp thứ nhất cán mức căn bậc hai của VICTIM_NUMBER là đủ.

Áp dụng vào bài toán này, ta sẽ có:

```Python
mport math
from prime import is_prime

VICTIM_NUMBER = 600851475143


def find_largest_prime_factor_by_bruteforce():
    largest_prime_factor = 0
    for number in range(2, int(math.sqrt(VICTIM_NUMBER)) + 1):
        if not VICTIM_NUMBER % number and is_prime(number):
            if largest_prime_factor < number:
                    largest_prime_factor = number
    return largest_prime_factor


if __name__ == "__main__":
    import time
    print("bruteforce largest_prime_factor {} result:".format(VICTIM_NUMBER))
    start = time.time()
    print(find_largest_prime_factor_by_bruteforce())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))
```


```
Nguyens-MacBook-Pro:PE-003 vinh.nguyenquang$ python3 bruteforce_pe003.py
bruteforce largest_prime_factor 600851475143 result:
6857
elapsed time: 0.10058188438415527s

```


## Áp dụng toán học vào giải bài toán PE-003:

Nếu không muốn máy tính treo đơ đơ, bạn phải tìm một phương án khác.
Ở đây ta thấy nếu lật ngược phép lặp từ VICTIM_NUMBER đến 2, sau đó nếu tìm thấy 1 giá trị number là ước số, gán VICTIM_NUMBER thành thương của VICTIM_NUMBER // number.
Kết 

```Python
import math

VICTIM_NUMBER = 600851475143


def find_largest_prime_factor_by_math():
    number = VICTIM_NUMBER
    while True:
        prime_factor = find_smallest_prime_factor(number)
        if prime_factor < number:
            number = number // prime_factor
        else:
            return prime_factor


def find_smallest_prime_factor(number):
    for index in range(2, int(math.sqrt(number) + 1)):
        if not number % index:
            return index
    return number


if __name__ == "__main__":
    import time
    print("math largest_prime_factor {} result:".format(VICTIM_NUMBER))
    start = time.time()
    print(find_largest_prime_factor_by_math())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))
```

```
Nguyens-MacBook-Pro:PE-003 vinh.nguyenquang$ python math_pe003.py
math largest_prime_factor 600851475143 result:
6857
elapsed time: 0.0238881111145s

```

## Kết luận:
Thời gian chạy từ ~ về 0.10058188438415527s rồi lại về 0.0238881111145s, xứng đáng để chúng ta thực hiện tối ưu.


Source-code:
[PE-003](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-003)
