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


**Ghi chú:** 
- Với các thư mục sâu hơn, có thể sử dụng cách đơn giản hơn chút. ví dụ ảnh để ở thư mục img thì đường dẫn sẽ là
`
![](img/Ex.png)
`

- Mẹo nhỏ thì như vậy, nhưng về lâu về dài thì nên học cách sử dụng LATEX.
[Latex on markdown](https://medium.com/pymi/bi%E1%BB%83u-di%E1%BB%85n-c%C3%B4ng-th%E1%BB%A9c-to%C3%A1n-trong-latex-tr%C3%AAn-jupyter-notebook-5e1f521f062c)
