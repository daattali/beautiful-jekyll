---
layout: post
title: Đọc file text có encoding là unicode
subtile: Python coding like a Pythonista
image: /img/2017-12-10-Read-unicode-text-file-by-python/Unicodelogo.gif
tags: [Python, lap-trinh, program-language, Python-tips]
categories: [Dev-Python]
date: 2017-12-10
---

Unicode hay biểu diễn tiếng Việt vẫn luôn là ác mộng với các lập trình viên. Làm thế nào để đọc một file nội dung bên trong là tiếng việt mà không bị lỗi ?

Các bạn sẽ nói: Python3 hỗ trợ unicode tự động rồi còn gì. Chuẩn luôn. Nhưng đây là những gì mà tôi đã gặp khi lập trình Python3 đọc file trên Window.


Nội dung file text: --> Filetext.txt
```
Xin chào
Tôi là file text
Tạm biệt
```


Đoạn code Python đọc ra nội dung file này:

```Python
my_file = open('E:\\Filetext.txt','r')
string = my_file.read()
print(string)
my_file.close()
```
Và đây là những thứ mà tôi nhận được:

```
ÿþXin chào

Tôi là file text

T¡m biÇt


```

File của chúng ta sử dụng UTF-8 đúng không? Vậy dùng encoding='utf-8' làm tham số xem sao nhé.

```Python
my_file = open('E:\\Filetext.txt','r', encoding='utf-8')
string = my_file.read()
print(string)
my_file.close()
```

```
---------------------------------------------------------------------------
UnicodeDecodeError                        Traceback (most recent call last)
<ipython-input-2-ec70efdf7a39> in <module>()
      1 my_file = open('E:\\Filetext.txt','r', encoding='utf-8')
----> 2 string = my_file.read()
      3 print(string)
      4 my_file.close()

C:\ProgramData\Anaconda3\lib\codecs.py in decode(self, input, final)
    319         # decode input (taking the buffer into account)
    320         data = self.buffer + input
--> 321         (result, consumed) = self._buffer_decode(data, self.errors, final)
    322         # keep undecoded input until the next call
    323         self.buffer = data[consumed:]

UnicodeDecodeError: 'utf-8' codec can't decode byte 0xff in position 0: invalid start byte
```

Như này là như nào ??? giờ phải làm sao đây ???
Sau một hồi search google thì đây là cách giải quyết

```Python
my_file = open('E:\\Filetext.txt','r', encoding='utf-16')
string = my_file.read()
print(string)
my_file.close()
```

```
Xin chào
Tôi là file text
Tạm biệt
```