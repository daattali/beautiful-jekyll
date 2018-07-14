---
layout: post
title: PE024-Lexicographic-permutations
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-07-01
# 2018-07-10-PE024-Lexicographic-permutations
---
Số hoán vị từ thứ một triệu của các chữ số 0, 1, 2, 3, 4, 5, 6, 7, 8 và 9 là gì?


## Problem PE024-Lexicographic-permutations
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

## Đề bài
Một phép hoán vị là một cách sắp xếp theo thứ tự của các đối tượng. 

Ví dụ, 3124 là một hoán vị có thể có của các chữ số 1, 2, 3 và 4. 

Nếu tất cả các hoán vị được liệt kê bằng số hoặc theo thứ tự bảng chữ cái, chúng ta gọi nó là thứ tự từ điển. Các hoán vị từ vựng của 0, 1 và 2 là:

012 021 102 120 201 210

Hãy tìm số hoán vị từ thứ hai triệu của các chữ số 0, 1, 2, 3, 4, 5, 6, 7, 8 và 9 là gì?


## Phân tích đề bài:
Phép toán hoán vị khá quen thuộc với học sinh cấp 3. Trước đây, đề thi toán khối B/D năm nào cũng có. 

Để giải quyết bài toán này, chúng ta chỉ cần đặt 1 list chứa các số từ 0 - 9. Sau đó lần lượt swap các số theo thứ tự từ điển, mỗi số được sinh ra sẽ được tính là 1 đơn vị. Khi nào đặt đến 2.000.000 thì dừng lại. 

Cách làm này khá kinh hoàng :|

Dở lại công thức tìm số lượng hoán vị, nếu ta có N số khác nhau thì có N! hoán vị.

Ở đây chúng ta có 10 số --> 10! = 3.628.800

Nếu đặt 0 là số đầu tiên và dùng 9 số đằng sau để tạo hoán vị --> có 9! = 362.880 số được tạo ra.

Tiếp tục đặt số 1 thay thế cho số 0 ở đầu, chúng ta tiếp tục có 9! = 362.880 số hoán vị được tạo ra.
...

```
0* : 0 - 362880
1* : 362881 - 725760
2* : 725761 - 1088640
```
Như danh sách trên thì số thứ 1 triệu sẽ nằm trong nhóm 2*

Ta thấy số thứ 725761 theo thứ tự từ điển là: 2013456789

Từ vị trí 725.761 đến 1.000.000 cần qua 274.239 hoán vị.

Loại bỏ số 2 ở đầu và thêm 1 số tiếp theo đi, chúng ta còn 8 số thiết lập hoán vị. Mỗi số ở vị trí thứ 2 sẽ tạo ra được 8! = 40320 hoán vị.

274239//40320 = 6

--> Cần 6 lần thay đổi vị trí số thứ 2 để đạt được vị trí ~ 1.000.000

.....

Cứ làm như vậy chúng ta sẽ lần lượt ra được kết quả. 


```Python


import math

LIMIT_NUMBER = 1000000


def find_millionth_lexicographic_permutation():
    perm = [_ for _ in range(0, 10)]
    numbers = [str(_) for _ in range(0, 10)]
    count = len(perm)
    perm_num = ""
    remain = LIMIT_NUMBER - 1

    for index in range(1, 10):
        step = remain // math.factorial(count - index)
        remain = remain % math.factorial(count - index)
        perm_num = perm_num + numbers[step]
        numbers.pop(step)
        if remain == 0:
            break

    for item in numbers:
        perm_num += item

    return perm_num


```

Kết quả của bài toán:
```
Nguyens-MBP:PE-024 vinh.nguyenquang$ python3 millionth_lexicographic_permutation.py
The 1000000st lexicographic permutation is: 2783915460
elapsed time: 2.47955322265625e-05s

```

Con số về thời gian khá ấn tượng

Source-code:
[PE-023](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-023)
