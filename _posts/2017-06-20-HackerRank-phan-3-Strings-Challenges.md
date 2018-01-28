---
layout: post
title: Hackerrank - phần 3-String-Challenges
subtile: Python coding like a Pythonista
image: /img/2017-06-15-HackerRank/Hackerrank1.png
tags: [Python, lap-trinh, programming-language, hacker-rank]
categories: [Dev-Python]
date: 2017-06-20
---

Bài tập phần 3: Một vài thử thách sử dụng String của Python. [String-Challenges](https://www.hackerrank.com/domains/python/py-strings) 


# Strings-Challenges

## [Ex3_1: sWAP cASE](https://www.hackerrank.com/challenges/swap-case/problem) 
Cho một chuỗi S. Yêu cầu thực hiện chuyển định dạng chữ của chuỗi S.
Nếu chữ cái viết hoa --> chuyển thành chữ thường và ngược lại.

Ví dụ:
```
Www.HackerRank.com → wWW.hACKERrANK.COM
Pythonist 2 → pYTHONIST 2

```



<hr>
Code here: 
<hr>


```python
def swap_single_char(single_char):
    if single_char.islower():
        return single_char.upper()
    else:
        return single_char.lower()

def swap_case(input_string):
    return ''.join([ swap_single_char(single_char) for single_char in input_string])

```


```python
if __name__ == '__main__':
    # s = input()
    s = "Www.HackerRank.com"
    result = swap_case(s)
    print(result)
```

    wWW.hACKERrANK.COM
    

## [Ex3_2: String Split and Join](https://www.hackerrank.com/challenges/python-string-split-and-join/problem)
Trong Python, một chuỗi có thể chia nhỏ theo các delimiter (dấu phân cách)

**Example:**

```Python
>>> a = "this is a string"
>>> a = a.split(" ") # a is converted to a list of strings. 
>>> print a
['this', 'is', 'a', 'string']

```
Nối lại các chuỗi cũng đơn giản:

```Python
>>> a = "-".join(a)
>>> print a
this-is-a-string 

```
Yêu cầu: Viết một function thực hiện chia chuỗi theo dấu space và nối lại chúng bằng dấu -

>this is a string   

>this-is-a-string



<hr>
Code here: 
<hr>


```python
def split_and_join(line):
    # write your code here
    return '-'.join(line.split())
```


```python
if __name__ == '__main__':
    # line = input()
    line = "write your code here"
    result = split_and_join(line)
    print(result)
```

    write-your-code-here
    

## [Ex3_3: What's Your Name?](https://www.hackerrank.com/challenges/whats-your-name/problem)

Nhập tên và họ của một người trên hai dòng khác nhau. Thực hiện in ra màn hình dòng chứ:

```
Hello **firstname** **lastname**! You just delved into python.
```


<hr>
Code here: 
<hr>


```python
def print_full_name(first_name, last_name):
    print("Hello {} {}! You just delved into python.".format(first_name, last_name))


if __name__ == '__main__':
    first_name = input()
    last_name = input()
    print_full_name(first_name, last_name)
```

    Quang
    Vinh
    Hello Quang Vinh! You just delved into python.
    

## [Ex3_4: Mutations](https://www.hackerrank.com/challenges/python-mutations/problem)

Chúng ta đã biết lists là mutable (có thể thay đổi) và tuples là immutable (không thể thay đổi).
Hãy tiếp tục tìm hiểu kỹ thông qua các ví dụ dưới đây.

Bạn có một chuỗi là immutable và bạn cần phải làm gì đó để thay đổi được nó.

> string = "abracadabra"

You can access an index by:

> print string[5]
> a

Điều gì sẽ xảy ra nếu bạn muốn gán một giá trị?

```python
>>> string[5] = 'k' 
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'str' object does not support item assignment

```

Làm thế nào bạn sẽ tiếp cận này?
- Một giải pháp là chuyển đổi chuỗi sang một danh sách và sau đó thay đổi giá trị.

```Python
>>> string = "abracadabra"
>>> l = list(string)
>>> l[5] = 'k'
>>> string = ''.join(l)
>>> print string
abrackdabra

```
- Cách tiếp cận khác là cắt chuỗi và nối lại.

```Python
>>> string = string[:5] + "k" + string[6:]
>>> print string
abrackdabra
```

**Yêu cầu:**
Đọc vào một chuỗi và vị trí, ký tự cần thay thế.
Thực hiện thay thế dữ liệu.

**Input:**
```
abracadabra
5 k
```

**Output:**
abrackdabra


<hr>
Code here: 
<hr>


```python
def mutate_string(_string, _position, _character):
    temp_list = list(_string)
    temp_list[_position] = _character
    return ''.join(temp_list)
```

# [Ex3_5: Find a string](https://www.hackerrank.com/challenges/find-a-string/problem)
Đọc vào 2 chuỗi, chuỗi chính - chuỗi con. Tìm số lần xuất hiện của chuỗi con trong chuỗi chính (tính từ trái qua phải)

**Input:**

```
ABCDCDC
CDC

```

**Output:**
```
2
```


<hr>
Code here: 
<hr>


```python
def count_substring(string, sub_string):
    # Fastest
    return sum([1 for i in range(0, len(string)) if string[i:i+len(sub_string)] == sub_string])
    # explain: List comprehesion like codes
    # summ = 0
    # for (i in range(len(string)))
    # if (string[i:i+len(sub_string)] == sub_string))
    #     summ += 1


if __name__ == '__main__':
    # string = input().strip()
    # sub_string = input().strip()
    string = ("In this challenge, the user enters a string and a substring."
              "You have to print the number of times that the substring "
              "occurs in the given string")
    sub_string = "string"
    count = count_substring(string, sub_string)
    print(count)

```

    4
    


# [Ex3_6: String Validators](https://www.hackerrank.com/challenges/string-validators/problem)

Python chứa nhiều hàm built-in cho phép thực hiện xác thực các dữ liệu.
Có thể kiểm tra xem một chuỗi có chứa: ký tự abc, số,...

**str.isalnum() **
This method checks if all the characters of a string are alphanumeric (a-z, A-Z and 0-9).
```Python

>>> print 'ab123'.isalnum()
True
>>> print 'ab123#'.isalnum()
False

```

**str.isalpha() **
This method checks if all the characters of a string are alphabetical (a-z and A-Z).

```Python
>>> print 'abcD'.isalpha()
True
>>> print 'abcd1'.isalpha()
False
```

**str.isdigit() **
This method checks if all the characters of a string are digits (0-9).
```Python
>>> print '1234'.isdigit()
True
>>> print '123edsd'.isdigit()
False
```

**str.islower() **
This method checks if all the characters of a string are lowercase characters (a-z).
```Python
>>> print 'abcd123#'.islower()
True
>>> print 'Abcd123#'.islower()
False
```

**str.isupper() **
This method checks if all the characters of a string are uppercase characters (A-Z).
```Python
>>> print 'ABCD123#'.isupper()
True
>>> print 'Abcd123#'.isupper()
False
```

### Yêu cầu
Nhận đầu vào là một chuỗi, in ra màn hình kết quả nếu chuỗi có chứa các điều kiện sau: 
alphanumeric characters, alphabetical characters, digits, lowercase and uppercase characters.

In the first line, print True if  has any alphanumeric characters. Otherwise, print False. 
In the second line, print True if  has any alphabetical characters. Otherwise, print False. 
In the third line, print True if  has any digits. Otherwise, print False. 
In the fourth line, print True if  has any lowercase characters. Otherwise, print False. 
In the fifth line, print True if  has any uppercase characters. Otherwise, print False.

<hr>
Code here: 
<hr>


```python

def validate_string(input_string):
    # alphanumeric
    print(any([sg_char.isalnum() for sg_char in input_string]))
    # alphabetical
    print(any([sg_char.isalpha() for sg_char in input_string]))
    # Digits
    print(any([sg_char.isdigit() for sg_char in input_string]))
    # lowercase
    print(any([sg_char.islower() for sg_char in input_string]))
    #uppcase
    print(any([sg_char.isupper() for sg_char in input_string]))


if __name__ == '__main__':
    # s = input()
    s = "1q2w3e4r@A"
    validate_string(s)

```

    True
    True
    True
    True
    True
    


## [EX3_7: Text Alignment](https://www.hackerrank.com/challenges/text-alignment/problem)
Trong Python, một chuỗi có thể canh trái, canh phải hoặc canh giữa.

**.ljust(width)**

This method returns a left aligned string of length width.
```

>>> width = 20
>>> print 'HackerRank'.ljust(width,'-')
HackerRank----------  

```

**.center(width)**

This method returns a centered string of length width.

```
>>> width = 20
>>> print 'HackerRank'.center(width,'-')
-----HackerRank-----

```

**.rjust(width)**

This method returns a right aligned string of length width.

```
>>> width = 20
>>> print 'HackerRank'.rjust(width,'-')
----------HackerRank
```

### Yêu cầu:
Nhập vào 1 số và in ra màn hình logo Hackerrank (H) theo như ví dụ.
**Input:**

```
5

```

**Output:**
```
    H    
   HHH   
  HHHHH  
 HHHHHHH 
HHHHHHHHH
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHHHHHHHHHHHHHHHHHHHHHH   
  HHHHHHHHHHHHHHHHHHHHHHHHH   
  HHHHHHHHHHHHHHHHHHHHHHHHH   
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
  HHHHH               HHHHH             
                    HHHHHHHHH 
                     HHHHHHH  
                      HHHHH   
                       HHH    
                        H 
```
<hr>
<b>Code here</b>: 
<hr>


```python
#!/usr/bin/env python3

def print_hackkerrank_logo(thickness, c):
    #Replace all ______ with rjust, ljust or center.
    #Top Cone
    for i in range(thickness):
        print((c*i).rjust(thickness-1)+c+(c*i).ljust(thickness-1))
    #Top Pillars
    for i in range(thickness+1):
        print((c*thickness).center(thickness*2)+(c*thickness).center(thickness*6))
    #Middle Belt
    for i in range((thickness+1)//2):
        print((c*thickness*5).center(thickness*6))
    #Bottom Pillars
    for i in range(thickness+1):
        print((c*thickness).center(thickness*2)+(c*thickness).center(thickness*6))
    #Bottom Cone
    for i in range(thickness):
        print(((c*(thickness-i-1)).rjust(thickness)+c+(c*(thickness-i-1)).ljust(thickness)).rjust(thickness*6))


if __name__ == '__main__':
    # thickness = input()
    thickness = 5
    c = "H"
    print_hackkerrank_logo(thickness, c)

```

        H    
       HHH   
      HHHHH  
     HHHHHHH 
    HHHHHHHHH
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHHHHHHHHHHHHHHHHHHHHHH   
      HHHHHHHHHHHHHHHHHHHHHHHHH   
      HHHHHHHHHHHHHHHHHHHHHHHHH   
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
      HHHHH               HHHHH             
                        HHHHHHHHH 
                         HHHHHHH  
                          HHHHH   
                           HHH    
                            H     
    



## [Ex3_8: Text Wrap](https://www.hackerrank.com/challenges/text-wrap/problem)
Thư viện textwrap cung cấp hai phương thức: wrap(), fill(). Với cách hoạt động như sau:

textwrap.wrap(): Chia một đoạn văn bản (chuỗi) thành các dòng khác nhau với độ dài là width (mặc định 70). Cách chia dựa trên dấu space. Kết quả trả về là một list.
Lưu ý: Nếu đọc được witdh ký tự nhưng đoạn cuối cùng chưa đọc hết một từ --> chuỗi trả về sẽ lùi lại, trả về từ vị trí khoảng trắng gần nhất.

ví dụ: 

```Python
>>> import textwrap
>>> string = "This is a very very very very very long string."
>>> print textwrap.wrap(string,8)
['This is', 'a very', 'very', 'very', 'very', 'very', 'long', 'string.'] 
>>> print([(value, len(value)) for value in textwrap.wrap(string, 8)])
[('This is', 7), ('a very', 6), ('very', 4), ('very', 4), ('very', 4), ('very', 4), ('long', 4), ('string.', 7)]

```
Giải thích: 
"This is " --> đoạn này có 8 ký tự, sau khi striP() --> còn 7 ký tự.
"a very v" --> đoạn này có 8 ký tự nhưng ký tự tiếp theo không phải khoảng trắng --> thụt lại đến vị trí khoảng trắng gần nhất. --> a very
"very ver" --> đoạn này có 8 ký tự nhưng ký tự tiếp theo không phải khoảng trắng --> thụt lại đến vị trí khoảng trắng gần nhất.  --> very


textwrap.fill(): tương tự như wrap(), phương thức fill() sẽ thực hiện trả về một chuối chứa các dòng.
Có thể hiểu như này cho nhanh fill() = "\n.joint(wrap()).

Ví dụ: 
```Python
>>> import textwrap
>>> string = "This is a very very very very very long string."
>>> print textwrap.fill(string,8)
This is
a very
very
very
very
very
long
string.
```

```Python
>>textwrap.fill(string,8) == "\n".join(textwrap.wrap(string, 8))
True
```

### Yêu cầu đề bài: 
Cho một chuỗi S và một số n. Thực hiện wrap chuỗi S thành một chuỗi khác như ví dụ: 

**Input:**
```
ABCDEFGHIJKLIMNOQRSTUVWXYZ
4

```

**Output:**

```
ABCD
EFGH
IJKL
IMNO
QRST
UVWX
YZ  
```

<hr>
<b>Code here</b>: 
<hr>


```python
#!/usr/bin/env python3
import textwrap

def wrap(string, max_width):
    return '\n'.join(textwrap.wrap(string, max_width))


if __name__ == '__main__':
    # S = input()
    # in = int(input())
    S = "bscnksbcjscksbcjksbckjdscsbdcbsdkjbcsdjcbsdjkcbsdkjbckjdsbjksd"
    n = 9
    print(wrap(S, n))
```

    bscnksbcj
    scksbcjks
    bckjdscsb
    dcbsdkjbc
    sdjcbsdjk
    cbsdkjbck
    jdsbjksd
    

## [Ex3_8: Designer Door Mat](https://www.hackerrank.com/challenges/designer-door-mat/problem)

Tôi ghét nhất loại vẽ ra những cái hình như thế này :(
Và tôi không muốn tốn thời gian để làm nó. Các bạn đọc yêu cầu từ hackerrank và code để giải ở dưới đây:

```
N, M = map(int,input().split()) # More than 6 lines of code will result in 0 score. Blank lines are not counted.
pattern = [('.|.'*(2*i + 1)).center(M, '-') for i in range(N//2)]
print('\n'.join(pattern + ['WELCOME'.center(M, '-')] + pattern[::-1]))

```
<hr>
<b>Code here</b>: 
<hr>


```python
N, M = map(int,input().split()) # More than 6 lines of code will result in 0 score. Blank lines are not counted.
pattern = [('.|.'*(2*i + 1)).center(M, '-') for i in range(N//2)]
print('\n'.join(pattern + ['WELCOME'.center(M, '-')] + pattern[::-1]))


```

    7 21
    ---------.|.---------
    ------.|..|..|.------
    ---.|..|..|..|..|.---
    -------WELCOME-------
    ---.|..|..|..|..|.---
    ------.|..|..|.------
    ---------.|.---------
    

 ## [Ex3_10: String Formatting](https://www.hackerrank.com/challenges/python-string-formatting/problem) 
Cho một số tự nhiên N, in ra màn hình các số từ 1 đến n theo các loại:
1. Decimal
2. Octal
3. Hexadecimal (capitalized - định dạng 4 số đầy đủ, thêm 0 phía trước)
4. Binary

Mỗi số in ra trên một dòng. Format mỗi số được in ra có độ dài bằng độ dài của số N ở dạng nhị phân và dấu cách.

**Input:**

```
17
```



```
    1     1     1     1
    2     2     2    10
    3     3     3    11
    4     4     4   100
    5     5     5   101
    6     6     6   110
    7     7     7   111
    8    10     8  1000
    9    11     9  1001
   10    12     A  1010
   11    13     B  1011
   12    14     C  1100
   13    15     D  1101
   14    16     E  1110
   15    17     F  1111
   16    20    10 10000
   17    21    11 10001

```
<hr>
<b>Code here</b>: 
<hr>


```python
#!/usr/bin/env python3

def print_formatted(input_number):
    width = len(bin(input_number)[2:])
    for i in range(1, input_number + 1):
        print (str(i).rjust(width,' '),str(oct(i)[2:]).rjust(width,' '),str(hex(i)[2:].upper()).rjust(width,' '),str(bin(i)[2:]).rjust(width,' '),sep=' ')


if __name__ == '__main__':
    # n = input()
    n = 17
    print_formatted(n)

```

        1     1     1     1
        2     2     2    10
        3     3     3    11
        4     4     4   100
        5     5     5   101
        6     6     6   110
        7     7     7   111
        8    10     8  1000
        9    11     9  1001
       10    12     A  1010
       11    13     B  1011
       12    14     C  1100
       13    15     D  1101
       14    16     E  1110
       15    17     F  1111
       16    20    10 10000
       17    21    11 10001
    


## [Ex3_11](https://www.hackerrank.com/challenges/alphabet-rangoli/problem)

Lại một bài in chữ kỳ dị. 

Với một số n, --> tìm tương ứng trong bảng mã ascii, chữ thường.
In ra hình với dạng: a ở trung tâm và các chữ khác xung quanh như sau:
```
#size 3

----c----
--c-b-c--
c-b-a-b-c
--c-b-c--
----c----

#size 5

--------e--------
------e-d-e------
----e-d-c-d-e----
--e-d-c-b-c-d-e--
e-d-c-b-a-b-c-d-e
--e-d-c-b-c-d-e--
----e-d-c-d-e----
------e-d-e------
--------e--------

#size 10

------------------j------------------
----------------j-i-j----------------
--------------j-i-h-i-j--------------
------------j-i-h-g-h-i-j------------
----------j-i-h-g-f-g-h-i-j----------
--------j-i-h-g-f-e-f-g-h-i-j--------
------j-i-h-g-f-e-d-e-f-g-h-i-j------
----j-i-h-g-f-e-d-c-d-e-f-g-h-i-j----
--j-i-h-g-f-e-d-c-b-c-d-e-f-g-h-i-j--
j-i-h-g-f-e-d-c-b-a-b-c-d-e-f-g-h-i-j
--j-i-h-g-f-e-d-c-b-c-d-e-f-g-h-i-j--
----j-i-h-g-f-e-d-c-d-e-f-g-h-i-j----
------j-i-h-g-f-e-d-e-f-g-h-i-j------
--------j-i-h-g-f-e-f-g-h-i-j--------
----------j-i-h-g-f-g-h-i-j----------
------------j-i-h-g-h-i-j------------
--------------j-i-h-i-j--------------
----------------j-i-j----------------
------------------j------------------

```

<hr>
<b>Code here</b>: 
<hr>


```python
import string

def print_rangoli(size):
    alpha = string.ascii_lowercase
    my_list = ['-'.join((alpha[i:n][::-1] + alpha[i:n][1:]).center(2*size-1,"-")) for i in range(n)]
    print('\n'.join(my_list[::-1] + my_list[1:]))


if __name__ == '__main__':
    # n = input()
    n = 5
    print_rangoli(n)

```

    --------e--------
    ------e-d-e------
    ----e-d-c-d-e----
    --e-d-c-b-c-d-e--
    e-d-c-b-a-b-c-d-e
    --e-d-c-b-c-d-e--
    ----e-d-c-d-e----
    ------e-d-e------
    --------e--------
    

## [Ex3_12 Capitalize!](https://www.hackerrank.com/challenges/capitalize/problem)

Cho bạn một chuỗi S, hãy viết hoa từng chữ trong S.
Ghi chú: Chỉ viết hoa chữ cái đầu tiên của chữ.

**Input:**
hello word

**Output**
Hello Word

<hr>
<b>Code here</b>: 
<hr>


```python
def capitalize(string):
    return ' '.join([sub.capitalize() for sub in string.split(" ")])


if __name__ == '__main__':
    # string = input()
    string = "1 w 2 r 3g"
    capitalized_string = capitalize(string)
    print(capitalized_string)

```

    1 W 2 R 3g
    
