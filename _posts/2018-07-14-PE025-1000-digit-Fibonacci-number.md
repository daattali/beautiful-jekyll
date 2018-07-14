---
layout: post
title: PE025-1000-digit-Fibonacci-number
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-07-14
# 2018-07-14-PE025-1000-digit-Fibonacci-number.md
---
Hãy tìm số thứ tự của số Fibonacci đầu tiên có 1000 chữ số


## Problem PE025-1000-digit-Fibonacci-number
The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

```
F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
```

The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?


## Đề bài
Dãy số Fibonacci được tạo thành bởi công thức:

>Fn = Fn−1 + Fn−2 

Trong đó F1 = 1 và F2 = 1. Dưới đây là 12 số Fibonacci đầu tiên:


```
F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
```

Ta thấy F12 là số Fibonacci đầu tiên có 3 chữ số. 

Hãy tìm số thứ tự của số Fibonacci đầu tiên có 1000 chữ số

## Phân tích đề bài:
Dãy số Fibonacci thì quen thuộc với các lập trình viên rồi. Nhưng số có 1000 chữ số thì nó thành "số lớn" rồi. 

>Với Python thì số lớn không thành vấn đề nhưng với các ngôn ngữ lập trình khác cũng "căng"

Sau nguyên 1 ngày suy nghĩ cách giải quyết bài toán này mà không làm được theo cách nào hiệu quả hơn (mặc dù trên công thức toán học là có), tôi đành phải quay về giải quyết bằng cách "trâu bò".

>"Trâu bò" cũng phải có tính toán một chút.
Vấn đề đầu tiên đó là thế nào là số có 1000 chữ số ?

Với số có n = 3 chữ số --> cận dưới là 100 = 10^2 --> 10 ^ (n-1)

Với số có n = 4 chữ số --> cận dưới là 1000 = 10^3 --> 10 ^ (n-1)
...
Với số có n = 1000 chữ số --> cận dưới là 10 ^ (n-1) --> 10 ^ 999

Chúng ta sẽ đặt một vòng lặp để khi nào số fi3 bắt đầu lớn hơn 10 ^ 999 thì dừng lại.

```Python


LIMIT_NUMBER = 1000


def find_fibonacci_number():
    fi_1 = 1
    fi_2 = 1
    fi_3 = fi_1 + fi_2
    limit = 10 ** (LIMIT_NUMBER - 1)
    index = 3
    while fi_3 <= limit:
        fi_2, fi_1 = fi_3, fi_2
        fi_3 = fi_2 + fi_1
        index += 1
    return index


```

Kết quả của bài toán:
```
Nguyens-MBP:PE-025 vinh.nguyenquang$ python3 1000_digit_fibonacci_number.py 
The first term in the fibonnaci sequence to have more than 1000 digits is term number: 4782 
elapsed time: 0.000904083251953125s

```

Nếu có ai tò mò số 1.000 chữ số này là số nào thì đây là đáp án:

```
1070066266382758936764980584457396885083683896632151665013235203375314520604694040621889147582489792657804694888177591957484336466672569959512996030461262748092482186144069433051234774442750273781753087579391666192149259186759553966422837148943113074699503439547001985432609723067290192870526447243726117715821825548491120525013201478612965931381792235559657452039506137551467837543229119602129934048260706175397706847068202895486902666185435124521900369480641357447470911707619766945691070098024393439617474103736912503231365532164773697023167755051595173518460579954919410967778373229665796581646513903488154256310184224190259846088000110186255550245493937113651657039447629584714548523425950428582425306083544435428212611008992863795048006894330309773217834864543113205765659868456288616808718693835297350643986297640660000723562917905207051164077614812491885830945940566688339109350944456576357666151619317753792891661581327159616877487983821820492520348473874384736771934512787029218636250627816
```

## Một số vấn đề rút ra từ bài toán.

Ở đoạn này:

`limit = 10 ** (LIMIT_NUMBER - 1)`

Nếu sử dụng math.pow(x,y) có sẵn của Python, ta sẽ thu được kết quả khá buồn:
```
Traceback (most recent call last):

limit = math.pow(10, LIMIT_NUMBER - 1)
OverflowError: math range error
```


Đoạn tiếp theo
`while fi_3 <= limit:`

Tại sao không sử dụng: `while len(fi_3) <= 1000:`

Câu trả lời đó là nếu dùng `len(fi_3)`, mỗi lần đến đoạn này trình thông dịch phải 1 lần "hỏi" cái fi_3 có độ dài là bao nhiêu --> Tốn kha khá thời gian với cái này

Source-code:
[PE-025](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-025)
