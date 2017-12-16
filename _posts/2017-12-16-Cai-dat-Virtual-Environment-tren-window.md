---
layout: post
title: Cài dặt và sử dụng Virtual Environemt trong Window
image: /img/2017-12-12-Jekyll/create_jekyll_blog.jpg
tags: [Python, lap-trinh, program-language, Python-tips]
categories: [Dev-Python]
date:   2017-12-16

---
**Virtual Environemt là phần không nên thiếu với các lập trình viên Python. Có phần này, chúng ta có thể sử dụng cùng lúc nhiều phiên bản của nhiều thư viên khác nhau :)**

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

(7 step)
1. Make a Virtual Environment (VE)
Tạo một VE có tên venv

```
mkvirtualenv venv
```

Cần lưu ý tùy theo hệ điều hành và phiên bản đã cài mà tên VE sẽ nằm ở chỗ khác với mong muốn (khác với Ubuntu). Ví dụ bên dưới

![VE1](/img/2017-12-16-VE/VE1.png)




2. Connect our project with our Environment & Set Project Directory

Tạo một thư mục trùng tên với VE để làm thư mục chứa project

kết nối đến project bằng cách thực hiện các lệnh cd cd, sau đó thực hiện

```
setprojectdir .
```

3. Deactivate

thực hiện lệnh:
```
deactivate
```

4. Workon
Bật lại VE sau khi tắt

Đứng từ thư mục project, thực hiện
```
workon HelloWold
```


Pip Install
Flask!


9. reactive VE (Trùng với workon)

Vào thư mục đã tạo từ bước 1 (tạo từ pip)
```
cd venv
scripts\activate
```
