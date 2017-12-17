---
layout: post
title: Cài đặt và sử dụng Virtual Environment trong Windows
image: /img/2017-06-01-Python/python.png
tags: [Python, lap-trinh, program-language, Python-tips]
categories: [Dev-Python]
date:   2017-12-16

---
**Virtual Environment là phần không nên thiếu với các lập trình viên Python. Có phần này, chúng ta có thể sử dụng cùng lúc nhiều phiên bản của nhiều thư viên khác nhau :)**

Ví dụ như hôm trước mới có Django 2.0, tôi muốn khám phá nó nhưng không muốn ảnh hưởng đến các project đang có (chạy bản 1.11). 

Hoặc tôi là người mới với Django chẳng hạn, nếu tôi gõ 

```
pip install django
```

Vậy là tôi cài luôn bản 2.0 ra máy của tôi :( nhưng nhu cầu hiện tại của tôi lại là 1.11 vì các tutorial hiện tại đều dùng 1.11 là tối đa và 2.0 chưa có cả document.

Giải pháp để xử lý như nào ???
Là một lập trình viên Python, bạn sẽ dễ dàng sử dụng với Virtual Environemt. 
Nói nôm na là bạn sẽ xây dựng một môi trường ảo mới hoàn toàn, với ... 0 thư viện được cài và dùng gì thì cài thêm.

# Các bước cài đặt:

Cài đặt qua 4 bước như sau: 

1. Cài đặt Python
2. Cài đặt pip (nếu chưa có)
3. Cài dặt Virtual Environemt

Mở cmd, thực hiện lệnh:

```
pip install virtualenv
```

Chờ cài đặt xong sẽ có thông báo: Successfully installed virtualenv-xx

4. Cài đặt Install virtualenvwrapper-win

Gõ tiếp vào màn hình cmd:

```
pip install virtualenvwrapper-win
```

Chờ cài đặt xong sẽ có thông báo: Successfully installed virtualenvwrapper-win-1.2.5

# Sử dụng


1. Make a Virtual Environment (VE)
Tạo một VE có tên venv

```
mkvirtualenv venv
```

Cần lưu ý tùy theo hệ điều hành và phiên bản đã cài mà tên VE sẽ nằm ở chỗ khác với mong muốn (khác với Ubuntu). Ví dụ bên dưới

![VE1](/img/2017-12-16-VE/VE1.png)

Cần nhớ đường dẫn này để còn mở lại environment sau này


2. Connect our project with our Environment & Set Project Directory

Tại thư mục muốn lưu trữ project, tạo một thư mục trùng tên với VE vừa tạo ở bước 1 để làm thư mục chứa code project

kết nối đến project bằng cách thực hiện lệnh cd, sau đó thực hiện

```
setprojectdir .
```

Sau lệnh này, vị trí của thư mục trên windows mà các bạn trỏ đến sẽ được map với environment được tạo ở thư mục phần 1.

3. Deactivate

thực hiện lệnh:
```
deactivate
```

4. Workon
Bật lại VE sau khi tắt

Đứng từ thư mục project (ở mục 2), thực hiện

```
workon HelloWold
```


5. Pip Install
* Thực hiện install các gói cần thiết với project bằng cửa sổ cmd đang kích hoạt VE như bình thường.

Công việc install thật mất thời gian, vì thế Python cung cấp cho lập trình viên cách nhanh nhất là copy từ environment này sang các environment khác.
* Export các gói đang sử dụng ra file requirement.txt

Từ environment đang sử dụng
```
pip freeze > requirements.txt
```
Ta thu được file requirements.txt của environment đang sử dụng.

Khi tạo ra một environment khác, ta thực hiện install các gói trong file requirements.txt:

```
pip install -r requirements.txt
```



Ngoài lề: 
**reactivate VE (Trùng với workon)**

Vào thư mục đã tạo từ bước 1 (tạo từ mkvirtualenv), sau đó thực hiện lệnh sau để activate VE

```
scripts\activate
```
