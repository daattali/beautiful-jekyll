---
layout: post
title: Hướng dẫn cài đặt và sử dụng jupyter notebook
# subtile: Hãy viết code như một Pythonista
image: img/2017-06-06-jupyter/jupyterBia.png
tags: [Python, lap-trinh, program-language, jupyter-notebook, Pythonista]
categories: [Dev-Python]
date: 2017-06-06
---


![notebook](/img/2017-06-06-jupyter/Jupyter.png)

[Jupyter notebook](http://jupyter.org/): Ứng dụng web mã nguồn mở cho phép bạn tạo, thực thi và chia sẻ các tài liệu chứa mã nguồn, phương trình, hình ảnh đồ họa và các kết quả sau khi chạy chương trình.
Jupyter notebook được sử dụng nhiều trong data analysis, mô phỏng số liệu, thống kê, modeling, machine learning, AI và nhiều hơn nữa.

Jupyter notebook hỗ trợ rất nhiều ngôn ngữ lập trình:  Python, R, Julia, and Scala,...
Đặc biệt với Big Data, Spark được tích hợp sẵn.

Ngoài ra có hẳn một cộng đồng người dùng hỗ trợ, chia sẻ các bản notebook của mình về các giải pháp xử lý bài toán thú vị.


## Dùng thử Jupyter notebook

[![https://try.jupyter.org/](/img/2017-06-06-jupyter/tryJupyter.png)](https://try.jupyter.org/)


![notebook](/img/2017-06-06-jupyter/tryJupyter1.png)

Editor của Jupyter notebook hỗ trợ các định dạng khác nhau

![notebook](/img/2017-06-06-jupyter/tryJupyter2.png)

Dùng thử jupyter notebook

![notebook](/img/2017-06-06-jupyter/Jupyter1.png)
![notebook](/img/2017-06-06-jupyter/Jupyter2.png)
![notebook](/img/2017-06-06-jupyter/Jupyter3.png)
![notebook](/img/2017-06-06-jupyter/Jupyter4.png)
![notebook](/img/2017-06-06-jupyter/Jupyter5.png)


## Cài đặt Jupyter trên máy tính

**Nếu bạn đã cài đặt bản full WinPython**

JupyterNotebook.exe ở ngay trong thư mục bạn đã cài đặt.


**Nếu bạn cài đặt Python bằng bộ cài đặt anaconda**

Để khởi động Jupyter Notebook, bạn chỉ cần mở terminal\cmd và gõ:

`
jupyter notebook
`

**Nếu bạn cài đặt Python từ trang chủ**

Mở terminal\cmd và gõ:

Python3:
`
python3 -m pip install --upgrade pip
python3 -m pip install jupyter
`

Python2:

`
python -m pip install --upgrade pip
python -m pip install jupyter
`


Sau khi cài đặt thì thực hiện mở jupyter notebook để hưởng thành quả:

`
jupyter notebook
`


Để kết thúc việc sử dụng jupyter notebook trên máy tính, nhấn Ctrl + C và Enter (với ubuntu thì chỉ cần Ctrl +C)