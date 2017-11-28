---
layout: post
title: Cài đặt Python
image: img/2017-06-01-Python/python.png
tags: [Python, lap-trinh, program-language]
categories: [Dev-Python]
date: 2017-06-02
---


Trên trang chủ của Python hiện tại đang có 2 version để sử dụng: Python 2 và Python3. Đọc News thì thấy Python2 đến năm 2020 sẽ không hỗ trợ nữa. Từ trước đến giờ toàn code Python2 do trên ubuntu và các linux distro mặc định đã có sẵn Python2. Nhưng thôi, giờ học lại nghiêm chỉnh thì học Python3 cho nó mới :))


## Cài đặt Python.

### Cài đặt python mặc định


**Trên Ubuntu**

Kiểm tra version (mặc định có Python2): 
```
python --version
```

Cài đặt từ Repo:
```
sudo apt update

sudo apt install python3.6
```

Kiểm tra kết quả cài đặt
```
python --version
```

Ngoài ra còn cách install qua PPA, install từ package được download từ trang chủ
[https://www.python.org/downloads/source/](https://www.python.org/downloads/source/)

**Trên Window**

Vào link này để download bản Python 3.6.x mới nhất:
[https://www.python.org/downloads/](https://www.python.org/downloads/)

Install như các phần mềm thông thường. Nhớ chọn "Add path" ở bước đầu tiên.



Mặc định Python có rất ít các package. Sau này, khi dùng đến package nào thì mới install qua Pip. --> Lựa chọn tối ưu cho các lập trình viên chuyên nghiệp.

### Cài bộ Anaconda
Funny: Anaconda hình như là "siêu trăn" thì phải.
Đúng như tên gọi của nó, Anaconda chứa phần lớn các thư viện "hịn" nhất của Python, người dùng gần như sẽ không phải cài thêm thư viện nữa
- Thích hợp cho việc học & làm việc ở môi trường offline (có policy chặn hết các loại kết nối internet)
- Thích hợp cho cả những "tay ngang" muốn học Python để tối ưu hóa công việc của mình.
- Anaconda hỗ trợ tối đa datasciense, rất nhiều video training từ bootcamp được anaconda cung cấp miễn phí.

**Download**
[https://www.anaconda.com/download/](https://www.anaconda.com/download/)

Có đầy đủ các bản cho Window/Linux/MacOS. 
Bản nào cũng có cả hướng dẫn install luôn
- Linux: [https://docs.anaconda.com/anaconda/install/linux](https://docs.anaconda.com/anaconda/install/linux)
- Window: [https://docs.anaconda.com/anaconda/install/windows](https://docs.anaconda.com/anaconda/install/windows)
- MacOS: [https://docs.anaconda.com/anaconda/install/mac-os](https://docs.anaconda.com/anaconda/install/mac-os)

## Kiểm tra kết quả cài đặt.

Sau khi cài đặt xong, mở terminal/cmd và gõ:
```
python --version
```

Nếu hiển thị ra Python phiên bản bao nhiêu --> đã cài đặt thành công.

## Gõ dòng lệnh đầu tiên.

Sau khi cài đặt xong, tận hưởng thành quả của mình một chút nhỉ :)

Trên terminal/cmd, gõ:

```
python
```

Màn hình sẽ ra dấu nhắc >>> để chúng ta gõ lệnh, phía trên là các thông tin về phiên bản của python đã được cài đặt và chọn làm mặc định.

Tiếp tục gõ

```
print("Hello Python")
```

Màn hình ra kết quả: Hello Python

Vậy là bạn đã thành công với chương trình đầu tiên bằng Python.

Để thoát ra khỏi màn hình chờ nhập lệnh của Python, hãy gõ 

```
exit()
```


Note: 
Nếu màn hình không ra thì sao ? --> Hãy nhìn lên phiên bản, có lẽ bạn đang ở Python2.

Hãy thoát khỏi màn hình nhập lệnh và quay trở về màn hình terminal/cmd và gõ:

```
Python3
```
