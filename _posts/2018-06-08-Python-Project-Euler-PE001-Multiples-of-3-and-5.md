---
layout: post
title: PE-001 Multiples of 3 and 5
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-08
---

## Problem 1: Multiples of 3 and 5
>If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23. 
>Find the sum of all the multiples of 3 or 5 below 1000.


## Đề bài
Liệt kê các số tự nhiên nhỏ hơn 10 mà chia hết cho 3 hoặc 5 ta thu được danh sách: 3, 5, 6, 9.
Tổng của chúng là 23.
Hãy tính tổng của các số chia hết cho 3 hoặc 5 nhỏ hơn 1000.

## Cách giải "trâu bò"
Đọc đầu bài ta có thể tư duy ra giải một cách "nhanh nhất" đó là tạo một vòng lặp từ 3 đến 999, sau đó tìm ra các số chia hết cho 3 hoặc 5, cộng dồn lại là xong.

Cách làm này không hề sai, có điều nếu đích đến tăng lên thành 1 triệu, 2 triệu,.... thì thời gian chạy bài toán sẽ tăng lên khá nhiều.


Dưới đây là script giải bài toán này bằng 2 cách.
**Cách 1: ** Dùng vòng lặp thông thường, lặp và giải bài toán.
**Cách 2: ** Sử dụng list-comprehension để giải bài toán.

```Python


def multiples_3_or_5_v1():
    sum_all = 0
    for number in range(3, 1000):
        if not number % 3 or not number % 5:
            sum_all += number
    return sum_all


def multiples_3_or_5_v2():
    return sum([number for number in range(3, 1000) if not number % 3 or not number % 5])

```




```Python

if __name__ == "__main__":
    import time
    print("multiples_3_or_5_v1 result:")
    start = time.time()
    print(multiples_3_or_5_v1())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))

    print("multiples_3_or_5_v2 result:")
    start = time.time()
    print(multiples_3_or_5_v2())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))


```

```bash
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.000223875045776s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000221967697144s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.000187158584595s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000138998031616s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.00016188621521s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000149965286255s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.000159978866577s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000149965286255s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.000187873840332s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000144004821777s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.00017786026001s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000148057937622s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ 
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python bruteforce_pe001.py 
multiples_3_or_5_v1 result:
233168
elapsed time: 0.000209093093872s
multiples_3_or_5_v2 result:
233168
elapsed time: 0.000150918960571s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ 
```
>Sau nhiều lần chạy bài toán, thời gian chạy v2 luôn nhỏ hơn v1.
> Liệu đây có phải lý do mà các "pythonista" luôn đề nghị mọi người dùng cách sử dụng tối đa list-comprehension


## Áp dụng toán học vào giải bài toán PE-001:
Độ phức tạp của bài toán nằm ở đoạn so sánh và vòng lặp:
```if not number % 3 or not number % 5:```
Đề thời gian giải bài toán nhanh hơn, ta nên tìm cách giảm số lượt so sánh và giảm số lượng phần tử trong vòng lặp.

Nếu áp dụng toán học vào tư duy bài toán này, ta thấy phép tính tổng trên là tổng các số chia hết cho 3 và tổng các số chia hết cho 5 sau đó loại trừ đi tổng các số chia hết cho 15. 
(Do chia hết cho 15 sẽ chia hết cho 3 và 5, đồng nghĩa với việc xuất hiện 2 lần các số chia hết cho 15)

```sum_all = sum_divisble_by(3) + sum_divisble_by(5) - sum_divisble_by(15)```

cách thức sum_divisble_by(number) thực hiện như thế nào?

`sum_divisble_by(3)` sẽ thực hiện tính tổng các số chia hết cho 3 từ 3 đến 999: 
3+6+9+12+…+999 = 3 * (1+2+3+4+…+333)

`sum_divisble_by(5)` sẽ thực hiện tính tổng các số chia hết cho 5 từ 5 đến 995:
5+10+15+20+…+995 = 5 * (1+2+3+4+…+199)

Ta có công thức toán học tính tổng các số liên tiếp:
1+2+3+4+…+N = (N*(N+1)/2)

```sum_divisble_by(number) = number * (N*(N+1)/2)```

Bài toán tiếp theo sẽ là tính ra N với mỗi number truyền vào. Từ kết quả phía trên, ta thấy 
333 = 999//3
199 = 999//5
--> N = max_number // number (phép chia lấy phần nguyên)

```sum_divisble_by(number, max_number) = number * ((max_number//number)*((max_number//number)+1)/2)```


```Python
def sum_divisble_by(number, max_number):
    return number * (max_number // number) * (max_number // number + 1) / 2


def multiples_3_or_5():
    return sum_divisble_by(3, 999) + sum_divisble_by(5, 999) - sum_divisble_by(15, 999)


def sum_divisble_by(number, max_number):
    return number * (max_number // number) * (max_number // number + 1) / 2


def multiples_3_or_5():
    return sum_divisble_by(3, 999) + sum_divisble_by(5, 999) - sum_divisble_by(15, 999)


if __name__ == "__main__":
    import time
    print("math multiples_3_or_5 result:")
    start = time.time()
    print(multiples_3_or_5())
    done = time.time()
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))

```

Thời gian thực hiện 

```
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python math_pe001.py
math multiples_3_or_5 result:
233168
elapsed time: 1.00135803223e-05s
Nguyens-MacBook-Pro:PE-001 vinh.nguyenquang$ python math_pe001.py
math multiples_3_or_5 result:
233168
elapsed time: 1.00135803223e-05s

```

So với giải pháp "trâu bò" thì thời gian này ngắn hơn rất nhiều

Source-code:
[PE-001 Multiples of 3 and 5](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-001)
