---
layout: post
title: PE-004 Largest palindrome product
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-09
---
Tìm số đối xứng lớn nhất là tích của các số có 3 chữ số.

## Problem 4: Largest palindrome product

```
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
```


## Đề bài
Số palindromic được định nghĩa là số "đối xứng". Đó là viết xuôi hay viết ngược đều cho ra chung một kết quả. 
Số đối xứng lớn nhất được tạo bởi tích của số có 2 chữ số là 9009 = 91 * 99.
Hãy tìm palindromic number lớn nhất được tạo từ 2 số có 3 chữ số.


## Phân tích đề bài:
Đề bài rất dễ hiểu, tìm số palindromic number được tạo từ tích của 2 số có 3 chữ số. Chỉ cần làm 2 vòng lặp quét từ 100-999 sau đó tính tích của 2 số này và kiểm tra kết quả có phải là số palindromic number không.
Nếu làm theo cách này --> (999 - 100 + 1) * (999 - 100 + 1) = 810000 lần duyệt và kiểm tra kết quả.


Cách thứ 2 là tạo ra các palindromic number sau đó kiểm tra xem có phải là tích của các số có 3 chữ số không.

100 * 100 = 10.000

999 * 999 = 998.001

10.000 < palindromic_number < 998.001 906.609

### Tạo ra các palindromic_number như thế nào ? 
Trong giải dữ liệu trên thì palindromic_number lớn nhất là 997799, số nhỏ nhất là 11111.

997799 được tạo từ 997, 111111 được tạo từ 111. Như vậy chỉ cần duyệt các số từ 997 đến 111 và tạo ra các palindromic_number.

Với Python việc này khá đơn giản. 

```Python
def make_palindrome_number(first_half):
    return int(str(first_half) + str(first_half)[::-1])

```

### Kiểm tra một số palin có là tích của 2 chữ số có 3 chữ số không.

Với mỗi số palin, thực hiện lấy ra number thuộc vòng lặp từ 100 đến 999.

Nếu palindromic_number chia hết cho number thì kiểm tra palindromic_number // number có trong khoảng 100 đến 999 không. 

## Code


```Python
def make_palindrome_number(first_half):
    return int(str(first_half) + str(first_half)[::-1])


def check_3_digit_numbers_product(palin):
    for number in range(999, 99, -1):
        if not palin % number:
            temp_number = palin // number
            if 100 <= temp_number <= 999:
                return True
    return False


def find_largest_palindrome_product():
    for first_half in range(997, 110, -1):
        palin = make_palindrome_number(first_half)
        if check_3_digit_numbers_product(palin):
            return palin
    return None


if __name__ == "__main__":
    import time
    print("Find_largest_palindrome_product result:")
    start = time.time()
    print(find_largest_palindrome_product())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))


```

Thời gian chạy bài toán:

```
Nguyens-MacBook-Pro:PE-004 vinh.nguyenquang$ python largest_palindrome_product.py
Find_largest_palindrome_product result:
906609
elapsed time: 0.00604486465454s

```
## Kết luận:

Bài toán này tôi không trình bày phần làm "trâu bò" nữa, chỉ tập trung vào xử lý làm sao cho kết quả được tốt nhất.

Các bài toán sau cũng sẽ đi vào hướng này.



Source-code:
[PE-004](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-004)
