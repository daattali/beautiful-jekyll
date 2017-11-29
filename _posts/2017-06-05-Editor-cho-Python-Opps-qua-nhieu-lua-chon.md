---
layout: post
title: Lựa chọn IDE & Editor tool để lập trình Python
# subtile: Hãy viết code như một Pythonista
image: img/2017-06-05-IDE/Bia.jpg
tags: [Python, lap-trinh, program-language, ide, Pythonista]
categories: [Dev-Python]
date: 2017-06-05
---

IDE (Integrated development environment -Môi trường phát triển tích hợp sẵn) & Editor tool cho ngôn ngữ lập trình python quá là phong phú luôn.

1. IDE
- Có thể sử dụng ngay chính built-in của python trong hệ điều hành bằng cách mở terminal/cmd và gõ **python** hoặc **python3**
- Hoặc sử dụng IDLE của python. IDLE này được cài đặt trực tiếp lên máy.

2. Editor tool: Những cuộc tranh cãi không bao giờ chấm dứt về việc nên dùng Editor tool nào. 

**[Pycharm](https://www.jetbrains.com/pycharm/)**: Ứng cử viên số 1 cho vị trí best editor for Python

![Pycharm](/img/2017-06-05-IDE/Pycharm.jpg)

Ưu điểm: Sử dụng nhanh, hỗ trợ tốt cho Python thuần và các framework của python (Khi new project có thể chọn sẵn template là các framwork). Chức năng nhắc lệnh, thay đổi code, format code, Interpreter tuyệt vời

Nhược điểm: Khởi động chậm, ngốn RAM kinh khủng. Mỗi file .py mở ra là pycharm tự động gọi sẵn 1 tiến trình để thông dịch file.

Phân loại: 
- Hỗ trợ hệ điều hành Window và Linux. 
- Có 2 bản Community (free/hạn chế nhiều chức năng) và Professional (mất phí 199$/year)

**[Sublime text](https://www.sublimetext.com/)**: Editor all in one. Hỗ trợ đa ngôn ngữ, đa nền tảng, chỉ cần cài các package plugin vào là ngon lành.

![Sublimetext](/img/2017-06-05-IDE/sublimetext.jpg)


Ưu điểm: Nhẹ, dễ dùng, phần search, replace nhanh/gọn, hỗ trợ nhiều ngôn ngữ, nền tảng khác nhau.

Nhược điểm: 
- Việc cài package plugin tuy đơn giản nhưng đôi khi lỗi là ..."mò mẫm" mỏi mệt.
- ST Bắt đầu được ông chủ mang ra thương mại hóa.
- Chỉ quản lý project dạng multi folder 

**[Visual studio code](https://code.visualstudio.com/)**: Sản phẩm miễn của Microsoft đưa ra cho cộng đồng opensource.

![VisualStudioCode](/img/2017-06-05-IDE/Bia.jpg)

Ưu điểm: 
- Có ông lớn M$ đứng sau nên cộng đồng các lúc càng lớn. Các request từ DEV để thay đổi phần mềm được M$ đáp ứng nhanh chóng.
- Đa nền tảng, hỗ trợ nhiều ngôn ngữ chỉ cần cài đặt các package từ extension. Số lượng extensison trong "kho" có rất nhiều. 
- Cấu hình thay đổi shortcut key đơn giản.
- Cho phép quản lý dạng project với nhiều thư mục (cập nhật mới tháng 11 - 2017)
- Tương đối nhẹ và ngốn RAM ít hơn Pycharm

Nhược điểm: 
- Phần search/replace vẫn còn hơi "tù".

**[Jupyter notebook](http://jupyter.org/)**: Đây là một editor dùng trong giảng dạy, demo, trao đổi kết quả.
![Jupyter notebook](/img/2017-06-05-IDE/jupyter.png)
Ưu điểm:
- Có thể xuất toàn bộ code, kết quả ra cùng một file pdf,...
- Sử dụng webbrower nên hỗ trợ đa nền tảng.
- Thuận tiện cho việc sử dụng để demo kết quả, vẽ đồ thị,...

Nhược điểm:
- Code đơn lẻ, không code thành module hoặc class được.
- Chế độ nhắc lệnh không có (hoặc rất tệ)
- Không có chuyện replace code trong Jupyter, chỉ có thể sửa trực tiếp từng dòng.


**Other:** Ngoài các tool trên còn có các tool khác như:
- VIM, ECMAS: Dùng cho các devops sau khi học xong ubuntu hoặc Linux sẽ chuyển sang học và lập trình bằng VIM
- Eclipse: Hỗ trợ tốt Java, không hõ trợ Python nhiều)
- Spyder, Atom,....

------------------------------
Cá nhân tôi là một fanboy của Visual Studio nên tôi chắc chắn sẽ chọn VSC.
Ở một bài viết nào đó tôi sẽ nói ra các ưu điểm của phần mềm này.
Chúng các bạn chọn đúng editor tool cho mình. 
