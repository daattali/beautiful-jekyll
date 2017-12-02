---
layout: post
title: Đưa ảnh vào Jupyter notebook với markdown style
subtile: Python coding like a Pythonista
image: /img/2017-12-01-Tips/quicktip.jpg
tags: [Python, lap-trinh, program-language, Python-tips]
categories: [Dev-Python]
date: 2017-12-01
---

Tôi đang viết một cái TUT nhỏ bằng Jupyter notebook. Tự nhiên gặp phải vấn đề...có cái công thức toán học dài quá, nếu dùng LATEX thì lại phải học LATEX.



Tôi muốn đưa ảnh này lên notebook của tôi 
![](/img/2017-12-01-Tips/Ex.png)

Đường dẫn đến thư mục chứa notebook mà tôi đang sử dụng: 

trên window: 
`
C:\Users\Admin\Test.ipynb
`
đường dẫn tương ứng trên web:

http://localhost:8888/notebooks/test.ipynb


Đừng lo lắng vì đã làm đủ mọi cách đưa ảnh lên notebook mà không được.
Hãy làm theo hướng dẫn sau: (áp dụng với window, linux chưa thử)

Copy ảnh cần hiển thiện vào thư mục:  

`
C:\Users\Admin\Ex.png
`

Trên jupyter notebook:

`
![](notebooks/Ex.png)
`

Kết quả: 

![](/img/2017-12-01-Tips/Ex.png)
