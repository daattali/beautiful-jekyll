---
layout: post
title: Bắt đầu lại với Python
image: img/2017-06-01-Python/python.png
tags: [Python, lap-trinh, program-language]
categories: [Dev-Python]
date: 2017-06-01
---


**Bước khởi đầu lần thứ 2 với ngôn ngữ lập trình Python**

## Lựa chọn Python ? 

Thời gian gần đây, bị stress công việc ở Viettel, một số thứ không được như mong muốn. Nhân sự, chế độ, áp lực công việc,...chỉ là thứ yếu, khéo xoay chuyển thì vẫn đáp ứng được, nhưng sức khỏe càng ngày càng đi xuống. Không đủ nhân sự, team-leader cũng phải đi trực như nhân viên. Trực xuyên đêm đến sáng mà không được ngủ, sáng ra thì lại họp, giao việc, báo cáo,...Buổi tối, về đến nhà thì liên tục có trouble ở các đất nước có múi giờ lệch. Không có thời gian ngủ, nghỉ ngơi lại sức, không có thời gian chăm sóc gia đình, chơi với con...

Stress thì phải tìm cách xả stress. Trong những đêm trực dài dằng dặc, cách giết thời gian hiệu quả nhất là code, code để không còn stress, code để biết rằng mình vẫn còn làm việc đúng đam mê. Code gì đây ? VB.NET, C# thì đã giao hết cho nhân viên phát triển tiếp. Java thì đã có nguyên một đội gần 200 mem làm rồi. Thử lên google, search "top 10 programming languages 2017" --> mở index đầu tiên luôn: 
https://hackernoon.com/top-10-programming-languages-in-2017-2f22e918fbfd

![TOP10](/img/2017-06-01-Python/top10.png)

Python à, món "thịt trăn" có vẻ ngon đấy. Từ cuối năm 2015 đến giờ liên tục hỗ trợ, training cho đội Core IP làm việc với món Python này. Code ngắn gọn, dễ học, dễ áp dụng, thư viện thì nhiều, cộng đồng hỗ trợ mạnh. Mình chưa học sâu về ngôn ngữ này, toàn làm đến đâu thì search google đến đấy. Mấy cái đã làm được liên quan giao thức HTTP/FTP/TCP-IP đội Core IP áp dụng vào công việc ngon lành phết. Để thử áp dụng vào mạng Core Network switch thay thế các phần mềm cũ của mình xem thế nào.


## Cài đặt Python.

Trên trang chủ của Python hiện tại đang có 2 version để sử dụng: Python 2 và Python3. Đọc News thì thấy Python2 đến năm 2020 sẽ không hỗ trợ nữa. Từ trước đến giờ toàn code Python2 do trên ubuntu và các linux distro mặc định đã có sẵn Python2. Nhưng thôi, giờ học lại nghiêm chỉnh thì học Python3 cho nó mới :))

Cài đặt:

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
https://www.python.org/downloads/source/

**Trên Window**

Vào link này để download bản Python 3.6.x mới nhất:
https://www.python.org/downloads/

Install như các phần mềm thông thường. Nhớ chọn "Add path" ở bước đầu tiên.


### Cài bộ Anaconda
Funny: Anaconda hình như là "siêu trăn" thì phải.
Đúng như tên gọi của nó, package Anaconda chứa phần lớn các thư viện "hịn" nhất của Python, người dùng phần lớn sẽ không phải cài thêm thư viện nữa
- Thích hợp cho việc học & làm việc ở môi trường offline (có policy chặn hết các loại kết nối internet)
- Thích hợp cho cả những "tay ngang" muốn học Python để tối ưu hóa công việc của mình.

**Download**
https://www.anaconda.com/download/

Có đầy đủ các bản cho Window/Linux/MacOS. 
Bản nào cũng có cả hướng dẫn install luôn
- Linux: https://docs.anaconda.com/anaconda/install/linux
- Window: https://docs.anaconda.com/anaconda/install/windows
- MacOS: https://docs.anaconda.com/anaconda/install/mac-os

