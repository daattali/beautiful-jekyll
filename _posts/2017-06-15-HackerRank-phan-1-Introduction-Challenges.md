---
layout: post
title: Hackerrank - phần 1- Introduction Challenges
subtile: Python coding like a Pythonista
image: /img/2017-06-15-HackerRank/Hackerrank1.png
tags: [Python, lap-trinh, program-language, hacker-rank]
categories: [Dev-Python]
date: 2017-06-15
---

Bài tập phần 1: Một vài thử thách cơ bản của Python: [Link gốc](https://www.hackerrank.com/domains/python/py-introduction)


# [Ex2_ControlFlow](https://www.hackerrank.com/challenges/py-if-else/problem)

Nhận đầu vào là một số nguyên n: 1 <= n <= 100
Viết chương trình in ra màn hình:
- Nếu n là số lẻ, in ra Weird
- Nếu n là số chẵn và nằm trong khoảng 2 -5, in ra Not Weird
- Nếu n là số chẵn và nằm trong khoảng 6 - 20, in ra Weird
- Nếu n là số chẵn và lớn hơn 20, in ra Not Weird



```python
def solve(input_data):
    '''
    ' params: number
    ' rtype: string
    '''
    if input_data % 2 or 6 <= input_data <= 20:
        return "Weird"
    else:
        return "Not Weird"

```


```python
def main():
    import random as rd
    for input_number in [rd.randint(1,100) for _ in range(10)]:
        print(input_number, solve(input_number))

```


```python
# test result
main()
```

    35 Weird
    32 Not Weird
    89 Weird
    17 Weird
    63 Weird
    50 Not Weird
    7 Weird
    56 Not Weird
    73 Weird
    48 Not Weird
    

# [Ex3_Arithmetic_Operators](https://www.hackerrank.com/challenges/python-arithmetic-operators/problem)

Nhận đầu vào là 2 số tự nhiên và in ra 3 dòng với điều kiện:
- Dòng thứ nhất chứa tổng của 2 số.
- Dòng thứ hai chứa hiệu của 2 số (số thứ 1 trừ số thứ 2)
- Dòng thứ ba chứa tích của hai số.



```python
def solve(first_input, second_input):
    '''
    ' params: two number
    ' rtype: none
    '''
    print(first_input + second_input)
    print(first_input - second_input)
    print(first_input * second_input)
    return None

```


```python
def main():
    first_input = 3
    second_input = 2
    solve(first_input, second_input)

```


```python
main()
```

    5
    1
    6
    

# [ Ex4_Division](https://www.hackerrank.com/challenges/python-division/problem)

Nhận đầu vào là 2 số tự nhiên và in ra hai dòng:
- Dòng đầu là số nguyên của phép chia a//b
- Dòng thứ hai là số thực của phép chia a/b

Ghi chú: không làm tròn hoặc format lại số.



```python
def solve(first_input, second_input):
    '''
    ' params: two number
    ' rtype: none
    '''
    print(first_input // second_input)
    print(first_input / second_input)
    return None

```


```python
def main():
    first_input = 4
    second_input = 3
    solve(first_input, second_input)
```


```python
main()

```

    1
    1.3333333333333333
    

# [Ex5_Loops](https://www.hackerrank.com/challenges/python-loops/problem)
Nhận đầu vào là một số tự nhiên N ( 1<= N <= 20). i là các giá trị thỏa mãn 0 <= i < N.
In ra màn hình các số bình phương của i. Mỗi số trên 1 dòng.


```python

def solve(input_number):
    '''
    ' params: number
    ' rtype: none
    '''
    for index in range(input_number):
        print(index ** 2)
    return None


```


```python
def main():
    input_number = 5
    solve(input_number)

if __name__ == "__main__":
    main()
```

    0
    1
    4
    9
    16
    

# [Ex6_Function](https://www.hackerrank.com/challenges/write-a-function/problem)
Chúng ta thường có thêm một ngày 29/2 sau mỗi 4 năm. Ngày này gọi là ngày nhuận.
Theo lịch Gregorian điều kiện để 1 năm có ngày nhuận như sau:
- Một năm chia hết cho 4 sẽ là năm nhuận trừ trường hợp ngoại lệ:
    - Nếu năm đó chia hết cho 100 nhưng không chia hết cho 400 thì không phải năm nhuận
    - Nếu năm đó chia hết cho 100 và chia hết cho 400 thì là năm nhuận
Ví dụ: 
Năm 1800, 1900, 2100, 2200, 2300 và 2500 không phải là năm nhuận vì chia hết cho 4 nhưng không chia hết cho 400
Năm 2400, 2000 là năm nhuận vì chia hết cho 400.

Viết một function nhận đầu vào là một năm, kiểm tra xem năm đó là năm nhuận hay không.



```python
def is_leap(year):
    leap = False
    if not year % 400:
        leap = True
    elif (not year % 4) and (year % 100):
        leap = True
    return leap
```


```python

def main():
    print(is_leap(2000))
    print(is_leap(1800))
    print(is_leap(2100))
    print(is_leap(1996))

if __name__ == "__main__":
    main()

```

    True
    False
    False
    True
    

# [Ex7_Print_Function](https://www.hackerrank.com/challenges/python-print/problem)
Nhận đầu vào là một số nguyên.
In ra màn hình các số nguyên từ 1 đến N trên cùng một dòng.
Ví dụ: N = 3 --> in ra màn hình 123




```python

def print_number(input_number):
    print(''.join([str(x) for x in range(1, input_number + 1)]))


```


```python
def main():
    input_number = 10
    print_number(input_number)


if __name__ == "__main__":
    main()
```

    12345678910
    
