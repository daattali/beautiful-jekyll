---
layout: post
title: Cách code Python như một lập trình viên chuyên nghiệp
subtile: Python coding like a Pythonista
image: /img/2017-06-10-coding-style/CodingBia.png
tags: [Python, lap-trinh, programming-language, pep8, Pythonista]
categories: [Dev-Python]
date: 2017-06-10
---

>Dựa trên kinh nghiệm cá nhân và tham khảo từ bài viết [https://www.python.org/dev/peps/pep-0008/](https://www.python.org/dev/peps/pep-0008/)

![codeblock](/img/2017-06-10-coding-style/python.ico) Sử dụng tiếng Anh tối đa trong khi đặt tên hoặc ghi chú

![codeblock](/img/2017-06-10-coding-style/python.ico) Cách ghi chú trong code python
- Ghi chú cho một dòng code dùng 

```
    # Ghi chú: Sau dấu # là 1 khoảng trắng sau đó bắt dầu dòng ghi chú
```

- Ghi chú cho 1 đoạn code dùng 3 dấu ' hoặc "

```
    '''Đây là ghi chú nhiều dòng.
    '   Nên bắt đầu ghi chú từ vị trí đầu tiên
    '''
```

![codeblock](/img/2017-06-10-coding-style/python.ico) Cách thức sử dụng khoảng trắng

- Sau dấu mở ngoặc và trước dấu đóng ngoặc không có khoảng trắng.
Ví dụ:

```
    # NO: 
    spam( ham[ 1 ], { eggs: 2 } )

    # YES:
    spam(ham[1], {eggs: 2})
```

- Trong một biểu thức, đặt dấu 01 dấu space quanh các toán tử + - * / = và dấu , 

```
    # YES:
    def calcute_distance(xA, yA, xB, yB):
        distance = math.sqrt((xB - xA) ** 2 + (yB - yA) ** 2)
        print(distance)
```

```
    # NO:
    def calcute_distance(xA,yA,xB,yB):
        distance        = math.sqrt((xB-xA)**2+(yB-yA)**2)
        print(distance)
```

Trường hợp sau dấu , là dấu ), ưu tiên dấu )

```
    # Yes: 
    foo = (0,)
    # No:
    bar = (0, )
```

Tham khảo: [https://www.python.org/dev/peps/pep-0008/#whitespace-in-expressions-and-statements](https://www.python.org/dev/peps/pep-0008/#whitespace-in-expressions-and-statements)

- Khi gọi đến một phương thức dấu () phải ở ngay cạnh tên phương thức.

ví dụ:

```
    # YES:
    calcute_distance(xA, xB, yA, yB)
```

```
    # NO:
    calcute_distance     (xA, xB, yA, yB)
```

![codeblock](/img/2017-06-10-coding-style/python.ico) Cách thức đặt tên: 
Đặt tên gợi nhớ tối đa đến chức năng, nhiệm vụ của biến, hàm

- Tên biến là danh từ, viết thường, nếu có trên 2 từ, nối nhau bằng _
        
        ví dụ: input_number, input_data, input_string

- Tên function là động từ, viết thường, nếu có trên 2 từ, nối nhau bằng _
        
        ví dụ: display_result, calculate_double
- Tên lớp: Sử dụng Cách thức CapWords. 
        
        ví dụ: MyClass, BankAccount,...

- Các biến toàn cục (Global) đặt tên theo Cách thức UPCASE

ví dụ: 

```
    PI = 3.14
```

Tham khảo:  [https://www.python.org/dev/peps/pep-0008/#naming-conventions](https://www.python.org/dev/peps/pep-0008/#naming-conventions)

![codeblock](/img/2017-06-10-coding-style/python.ico) Số lượng ký tự trên một dòng

Số lượng ký tự trên một dòng không vượt quá 79 ký tự (kể cả khoảng trắng). Pythonista đề xuất giới hạn trong khoảng 72 ký tự.


Tham khảo:[https://www.python.org/dev/peps/pep-0008/#maximum-line-length](https://www.python.org/dev/peps/pep-0008/#maximum-line-length)

Nếu dòng code của bạn quá dài, hãy sử dụng việc nối dòng bằng \

Ví dụ: 
```
with open('/path/to/some/file/you/want/to/read') as file_1, \
     open('/path/to/some/file/being/written', 'w') as file_2:
    file_2.write(file_1.read())
```

Nếu trong dòng có biểu thức sử dụng (), [], có thể thực hiện xuống dòng bằng cách dòng dưới thụt vào sau dấu ( hoặc [

```
if (this_is_one_thing and
    that_is_another_thing):
    do_something()
```

Nếu trong dòng có các toán tử, và dòng dài, cần phải format lại, thực hiện giữ toán hạng đầu tiên ở dòng trên và đưa toán tử & toán hạng tiếp theo cho xuống dòng dưới.

Ví dụ: 
```
    # NO
    income = (gross_wages +
            taxable_interest +
            (dividends - qualified_dividends) -
            ira_deduction -
            student_loan_interest)
```

```
    # YES
    income = (gross_wages
            + taxable_interest
            + (dividends - qualified_dividends)
            - ira_deduction
            - student_loan_interest)
```
Tham khảo: [https://www.python.org/dev/peps/pep-0008/#should-a-line-break-before-or-after-a-binary-operator](https://www.python.org/dev/peps/pep-0008/#should-a-line-break-before-or-after-a-binary-operator)

![codeblock](/img/2017-06-10-coding-style/python.ico) Cách thức thụt dòng: Code block in python

Sau khi khai báo 1 function, 1 vòng lặp, một câu kiểm tra điều kiện, dòng lệnh tiếp theo của khối lệnh (là tập lệnh con) sẽ thụt vào so với dòng trên 4 khoảng trắng (lưu ý hạn chế dùng tab)
ví dụ:

![codeblock](/img/2017-06-10-coding-style/coding_block.png)

Tham khảo: 
[https://www.python.org/dev/peps/pep-0008/#indentation](https://www.python.org/dev/peps/pep-0008/#indentation)

![codeblock](/img/2017-06-10-coding-style/python.ico) Cách thức phân chia các khối bằng blank-line:

- Giữa 2 phương thức: cách nhau bằng 1 blank-line
- Giữa lớp và phương thức: Cách nhau bằng 2 blank-line



![codeblock](/img/2017-06-10-coding-style/python.ico) Xóa bỏ những khoảng trống không cần thiết
- Kết thúc 1 dòng không có những khoảng trắng
- Giữa các phương thức và phương thức, phương thức và lớp yêu cầu là blank line. Hãy xóa các khoảng trắng trong blank-line.


**_Udating...._**