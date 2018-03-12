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

ftp = FTP("host-ip")
ftp.login(user='xxxx', passwd = 'xxx')

```





    '230 Logged on'



```python
# Thông số của FTP Server
ftp.welcome
```




    '220-FileZilla Server 0.9.60 beta\n220-written by Tim Kosse (tim.kosse@filezilla-project.org)\n220 Please visit https://filezilla-project.org/'




```python
# Đóng kết nối
ftp.close
```



```python
# Hiển thị tên thư mục hiện tại
ftp.pwd()
```




    '/'




```python
# Liệt kê các thư mục/file trong thư mục kết nối đến
print(ftp.retrlines('LIST'))
```

    -rw-r--r-- 1 ftp ftp          11234 Mar 09 21:39 Doc1.docx
    drwxr-xr-x 1 ftp ftp              0 Mar 09 23:21 Folder1
    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:26 Folder2
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:49 sample.ipynb
    226 Successfully transferred "/"
    


```python
type(ftp.retrlines('LIST'))
```

    -rw-r--r-- 1 ftp ftp          11234 Mar 09 21:39 Doc1.docx
    drwxr-xr-x 1 ftp ftp              0 Mar 09 23:21 Folder1
    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:26 Folder2
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:49 sample.ipynb
    




    str




```python
# Di chuyển đến thư mục khác:
ftp.cwd("Folder1")
```




    '250 CWD successful. "/Folder1" is current directory.'




```python
print(ftp.retrlines('LIST'))
```

    -rw-r--r-- 1 ftp ftp          11234 Mar 09 21:39 Doc1.docx
    drwxr-xr-x 1 ftp ftp              0 Mar 09 23:21 Folder1
    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:26 Folder2
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:49 sample.ipynb
    226 Successfully transferred "/"
    


```python
# Di chuyển về thư mục trước đó.
ftp.cwd("..")
```




    '200 CDUP successful. "/" is current directory.'




```python
# Tạo thư mục mới
ftp.mkd("NewFolder")

```




    '/NewFolder'




```python
# Xóa thư mục 
ftp.rmd("NewFolder")
```




    '250 Directory deleted successfully'




```python
# Kiểm tra dung lương file --> Byte
ftp.size("Doc1.docx")
```




    11234




```python
# Xóa file:
ftp.delete("Doc1.docx")
print(ftp.retrlines('LIST'))
```

    drwxr-xr-x 1 ftp ftp              0 Mar 09 23:21 Folder1
    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:26 Folder2
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:49 sample.ipynb
    226 Successfully transferred "/"
    


```python
ftp.close
```




    <bound method FTP.close of <ftplib.FTP object at 0x000001A51BE9CE48>>



**Upload file:**
- Điều kiện file upload ở cùng hoặc sâu hơn vị trí đặt file code python.
- Muốn upload đến thư mục nào đó thì thực hiện kết nối đến thư mục đó trên server




```python
from ftplib import FTP
ftp = FTP("192.168.14.188")
ftp.login(user='itplus', passwd = 'itplus')
ftp.cwd("Folder1")
print("before upload\n", ftp.retrlines("LIST"))
file_stream = open("sample_10_3.ipynb","rb")         # read file to send to byte
ftp.storbinary("{CMD} {FileName}".
               format(CMD="STOR",FileName="sample_10_3.ipynb"),
               file_stream)     # send the file
file_stream.close()                     
print("after upload\n", ftp.retrlines("LIST"))
ftp.close
```

    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:31 Folder3
    -rw-r--r-- 1 ftp ftp           6174 Mar 09 21:32 New t.xlsx
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:50 sample.ipynb
    before upload
     226 Successfully transferred "/Folder1"
    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:31 Folder3
    -rw-r--r-- 1 ftp ftp           6174 Mar 09 21:32 New t.xlsx
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:50 sample.ipynb
    -rw-r--r-- 1 ftp ftp           1085 Mar 10 18:59 sample_10_3.ipynb
    after upload
     226 Successfully transferred "/Folder1"
    




    <bound method FTP.close of <ftplib.FTP object at 0x000001F61ADBEDD8>>



**Download file:**
- Muốn download về đâu, trỏ đến thư mục đó trước
- Kết nối vào FTP server và thực hiện download


```python
ftp = FTP("192.168.14.188")
ftp.login(user='itplus', passwd = 'itplus')
ftp.cwd("Folder1")
print("before upload\n", ftp.retrlines("LIST"))
file_path = "New t.xlsx"
file_name = "New t.xlsx"
file_stream = open(file_path,"wb")         # read file to send to byte
ftp.retrbinary('RETR {}'.format(file_name),
               file_stream.write, 1024)
file_stream.close()                     
print("Download OK")
ftp.close
```

    drwxr-xr-x 1 ftp ftp              0 Mar 09 21:31 Folder3
    -rw-r--r-- 1 ftp ftp           6174 Mar 09 21:32 New t.xlsx
    -rw-r--r-- 1 ftp ftp           1085 Mar 09 21:50 sample.ipynb
    -rw-r--r-- 1 ftp ftp           1085 Mar 10 18:59 sample_10_3.ipynb
    before upload
     226 Successfully transferred "/Folder1"
    Download OK
    




    <bound method FTP.close of <ftplib.FTP object at 0x000001F61AFE65F8>>


