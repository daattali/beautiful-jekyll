---
layout: post
title: Lập trình hướng đối tượng với Python
image: /img/2017-06-01-Python/python.png
tags: [Python, lap-trinh, programming-language, Python-tips]
categories: [Dev-Python]
date:   2018-01-01

---
**Lập trình hướng đối tượng (object-oriented programming - OOP)** là một kỹ thuật lập trình được xây dựng dựa trên việc mô hình hóa các đối tượng trong một chương trình.

OOP có lợi ích trong việc tăng năng suất lao động trong ngành lập trình (chia nhỏ bài toán ra thành các nhóm khác nhau để nhiều người cùng làm), đơn giản hóa độ phức tạp khi thực hiện debug lỗi cũng như mở rộng phần mềm bằng cách cho phép lập trình viên tạo ra các thực thể con và thao tác trên chúng mà không cần sửa lại các thực thể đã có sẵn.

Do là kỹ thuật lập trình nền OOP có mặt trong rất nhiều các ngôn ngữ lập trình: C++, Java, C#, VB.NET, Python, Ruby, PHP,...

Về cơ bản các đặc điểm chung của Kỹ thuật lập trình OOP đều giống nhau, chỉ khác là cách lập trình viên biểu diễn nó trong các dòng lệnh.

Trong OOP có các khái niệm cơ bản sau đây:
- Trừu tượng (Abstraction)
- Đa hình (Polymorphism)
- Đóng gói (Encapsulation)
- Kế thừa (Inheritance)
- Đối tượng: Thực thể của một nhóm nào đó có chung các đặc điểm tĩnh và động. 
- Lớp: Khuôn mẫu của các đối tượng. 

Ví dụ: Trong Python, các kiểu dữ liệu `list, tuple, dictionary, string, int…` đều là các lớp. 
Khi thực hiện naming và binding (đặt tên và gán giá trị), các name sẽ được thực hiện khởi tạo kiểu dữ liệu.

## Python Objects:
Tất cả mọi thứ trong Python đều là các đối tượng của một class nào đó.  

```Python
import sys
 
def function(): pass
 
print (type(1))
print (type(""))
print (type([]))
print (type({}))
print (type(()))
print (type(object))
print (type(function))
print (type(sys))
```

Output:
```
<class 'int'>
<class 'str'>
<class 'list'>
<class 'dict'>
<class 'tuple'>
<class 'type'>
<class 'function'>
<class 'module'>
Từ khóa class
```

Với ví dụ trên, ta thấy function() có kiểu là `function`, số có kiểu `int`,...

## class keyword

Trong ví dụ trên, các lớp mà chúng ta kiểm tra bằng hàm type là các lớp có sẵn trong Python. Khi chúng ta muốn định nghĩa một lớp cho riêng mình thì chúng ta dùng từ khóa class. 

ột lớp có thể hiểu là một bản thiết kế để tạo ra một thực thể (mà chúng ta gọi là đối tượng). Một đối tượng là một thực thể được xây dựng từ một bản thiết kế đó (mà chúng ta gọi là lớp). Ví dụ chúng ta định nghĩa lớp Dog, và Hulk là một đối tượng của Dog 😀

Ví dụ có một class sau, được định nghĩa Dog là lớp (mới khai báo prototype). hulk là một đối tượng của lớp này

```Python
class Dog:
   pass
 
hulk = Dog()
 
print (type(hulk))

```
> Main.Dog

```Python
print (type(fr))
print (type(First))
```

```
> 
```
