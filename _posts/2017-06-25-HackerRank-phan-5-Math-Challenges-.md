---
layout: post
title: Hackerrank - phần 5-Math-Challenges
subtile: Python coding like a Pythonista
image: /img/2017-06-15-HackerRank/Hackerrank1.png
tags: [Python, lap-trinh, program-language, hacker-rank]
categories: [Dev-Python]
date: 2017-06-25
---

Bài tập phần 5: Một vài thử thách sử dụng thư viện Math của Python. [Math-Challenges](https://www.hackerrank.com/domains/python/py-math) 

Ghi chú: Phần này nhiều hình ảnh vẽ các tam giác, mô tả công thức... Vì vậy chỉ dẫn link đến hackerrank
# Math-Challenges


## [Ex5_1 Polar Coordinates](https://www.hackerrank.com/challenges/polar-coordinates/problem)
hình ảnh & mô tả xem tại link trên hackerrank.com: https://www.hackerrank.com/challenges/polar-coordinates/problem

**Yêu cầu:**
Cho số phức z = x + yj. Hãy chuyển số phức sang các tọa độ polar

**Input Format**

A single line containing the complex number . Note: complex() function can be used in python to convert the input as a complex number.

**Constraints**

Given number is a valid complex number

**Output Format**

Output two lines: 
The first line should contain the value of .r 
The second line should contain the value of Phi

**Sample Input**
```
  1+2j

```

**Sample Output**

```
 2.23606797749979 
 1.1071487177940904

```

**Note:** The output should be correct up to 3 decimal places.

<hr>
**Code:**



```python
import cmath

def convert_polar_coordinates(complex_number):
    print("{:.3f}\n{:.3f}".format(*cmath.polar(complex_number)))

if __name__ == '__main__':
    complex_number = complex(input())
    convert_polar_coordinates(complex_number)

```

    1+2j
    2.236
    1.107
    

## [Ex5_2: Find Angle MBC](https://www.hackerrank.com/challenges/find-angle/problem)
Mô tả bài toán xem tại link: https://www.hackerrank.com/challenges/find-angle/problem

**Yêu cầu:**

Cho giá trị 2 cạnh vuồng AB, BC. M là trung điểm AC. Hãy tính góc MBC.

**Sample Input**

10
10

**Sample Output**

45°

<hr>
**Code:**


```python
import math

if __name__ == '__main__':
    AB, BC = float(input()), float(input())
    print(str(int(round(math.degrees(math.atan2(AB, BC)))))+'°')
```

    10
    10
    45°
    

## [Ex5_3: Triangle Quest 2](https://www.hackerrank.com/challenges/triangle-quest-2/problem)
Mô tả bài toán xem tại link:https://www.hackerrank.com/challenges/triangle-quest-2/problem

Yêu cầu: In ra tam giác Pascal như yêu cầu

**Input Format**

A single line of input containing the 0 < integer < 10.


**Output Format**

Print the palindromic triangle of size  as explained above.

**Sample Input**

```
5

```

**Sample Output**

```
1
121
12321
1234321
123454321

```

<hr>
**Code**



```python
if __name__ == '__main__':
    for i in range(1, int(input()) + 1):
        print(((10**i-1)//9)**2)
    # print((''.join([str(index) for index in range(1,i+1)])).strip() + (''.join([str(jndex) for jndex in range(i-1, 0, -1)]).strip()))

```

    5
    1
    121
    12321
    1234321
    123454321
    


## [Ex5_4: Mod Divmod](https://www.hackerrank.com/challenges/python-mod-divmod/problem) 

Yêu cầu: 
Đọc vào a, b (Mỗi số trên một dòng). In ra màn hình kết quả:

Dòng 1: Phần nguyên a/b
Dòng 2: Phần dư a%b
Dòng 3: divmod(a,b)

<hr>
**Code:**



```python
def print_result(a, b):
    print(a // b)
    print(a % b)
    print(divmod(a, b))

if __name__ == '__main__':
    a, b = int(input()), int(input()) 
    print_result(a, b)

```

    117
    10
    11
    7
    (11, 7)
    

## [Ex5_5: Power - Mod Power](https://www.hackerrank.com/challenges/python-power-mod-power/problem)

Yêu cầu:
Đọc vào 3 số a,b,m (mỗi số trên một dòng). In ra màn hình kết quả:

Dòng 1: pow(a,b)

Dòng 2: pow(a,b,m)

<hr>
**Code**:



```python
#!/usr/bin/env python3

def print_result(a, b, m):
    print(pow(a, b))
    print(pow(a, b, m))

if __name__ == '__main__':
    a, b, m = int(input()), int(input()), int(input())
    print_result(a, b, m)

```

    10
    17
    5
    100000000000000000
    0
    

## [Exx5_6: Integers Come In All Sizes](https://www.hackerrank.com/challenges/python-integers-come-in-all-sizes/problem)

**Yêu cầu:**

Đọc vào 4 số a, b, c, d  (mỗi số trên một dòng).

Tính và in ra màn hình a ^ b + c ^ d

**Sample Input**

9
29
7
27

**Sample Output**

4710194409608608369201743232  




```python
def print_result(a, b, c, d):
    print(pow(a, b) + pow(c, d))


if __name__ == '__main__':
    a, b, c, d = int(input()), int(input()), int(input()), int(input())
    print_result(a, b, c, d)

```

    10
    11
    12
    13
    107093205379072
    

## [Ex5_7: Triangle Quest](https://www.hackerrank.com/challenges/python-quest-1/problem)

**Yêu cầu**:

In ra tam giác như yêu cầu

**Sample Input**

5

**Sample Output**

1
22
333
4444


<hr>
**Code**


```python
if __name__ == '__main__':
    for i in range(1, int(input())): #More than 2 lines will result in 0 score. Do not leave a blank line also
        print((10**(i)//9)*i)

```

    5
    1
    22
    333
    4444
    
