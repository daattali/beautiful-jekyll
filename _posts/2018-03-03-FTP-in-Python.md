---
layout: post
title: Xây dựng một ứng dụng FTP sử dụng ftplib
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-03-FTP/bia_FTP.png
tags: [Python, lap-trinh, programming-language, Pythonista]
categories: [Dev-Python]
date: 2018-03-03
---


**FTP**: Một giao thức khá phổ biến (trước năm 2010), được nhiều lập trình viên sử dụng cho việc lưu trữ file, lưu trữ dữ liệu. 

Để xây dựng một FTP Server, trên Windows rất dễ, sử dụng FileZilla Server: 
https://quantrimang.com/huong-dan-thiet-lap-ftp-server-ca-nhan-bang-filezilla-84531

Với Ubuntu, cần thực  hiện theo hướng dẫn:
https://help.ubuntu.com/lts/serverguide/ftp-server.html

hoặc

https://www.digitalocean.com/community/tutorials/how-to-set-up-vsftpd-for-a-user-s-directory-on-ubuntu-16-04



FTP Server: 
- Lưu trữ file
- Quản lý user/password
- Phân quyền truy nhập
- Cung cấp kết nối qua một cổng bất kỳ (default: 21):
    + Kết nối nặc danh.
    + Kết nối định danh: user/password.
    
FTP Client: 
- Chương trình trên máy người dùng, sử dụng để kết nối đến FPT Server

Trong Python, muốn kết nối FTP, sử dụng thư viện ftplib

```Python
from ftplib import FTP

ftp = FTP("127.0.0.1")
ftp.login(user='itplus', passwd = 'itplus')

ftp.welcome
# TODO