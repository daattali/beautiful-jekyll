---
layout: post
title: Hướng dẫn cài đặt phần mềm Visual Studio Code
# subtile: Hãy viết code như một Pythonista
image: img/2017-06-06-VSC/VSCBia.jpg
tags: [Python, lap-trinh, program-language, visual-studio-code, Pythonista]
categories: [Dev-Python]
date: 2017-06-06
---


**[Visual studio code](https://code.visualstudio.com/)**: Sản phẩm miễn của Microsoft đưa ra cho cộng đồng opensource. Được M$ đưa ra để thực hiện đưa .NET Core mono đến với Linux, OSX. Các lập trình viên có thể sử dụng nó để lập trình C# trên Linux hoặc OSX.

![VisualStudioCode](/img/2017-06-06-VSC/VSCBia.jpg)


**Ưu điểm:**
- Có ông lớn M$ đứng sau nên cộng đồng các lúc càng lớn. Các request từ DEV để thay đổi phần mềm được M$ đáp ứng nhanh chóng.
- Đa nền tảng, hỗ trợ nhiều ngôn ngữ chỉ cần cài đặt các package từ extension. Số lượng extensison trong "kho" có rất nhiều. 
- Cấu hình thay đổi shortcut key đơn giản.
- Cho phép quản lý dạng project với nhiều thư mục (cập nhật mới tháng 11 - 2017)
- Tương đối nhẹ và ngốn RAM ít hơn Pycharm
- Hỗ trợ GIT, Terminal

**Nhược điểm:**
- Phần xử lý text: find, replace chưa được thông minh lắm.
- Hiện tại chưa có select column 


# Cài đặt phần mềm:
**Download** Từ trang chủ hoặc trang download của VSC, theo đúng phiên bản của hệ điều hành: 

[https://code.visualstudio.com/Download](https://code.visualstudio.com/Download)

[https://code.visualstudio.com/](https://code.visualstudio.com/)

![VisualStudioCode](/img/2017-06-06-VSC/VSC1.png)

![VisualStudioCode](/img/2017-06-06-VSC/VSC2.png)


**Cài đặt**
Cài đặt trên window: Tiến hành cài đặt như cài đặt phần mềm bình thường.

Cài đặt trên linux:
- Mở termial tại thư mục chứa file .deb download về


`
sudo dpkg -i code_1.18.1-1510857349_amd64.deb
`
Sau đó chạy thêm lệnh để đảm bảo install thành công: 
`
sudo apt-get install -f
`


Ví dụ phiên bản hiện tại là file code_1.18.1-1510857349_amd64.deb

**Sử dụng**
Với người dùng mới, M$ cung cấp một số video hướng dẫn cách sử dụng:

[https://code.visualstudio.com/docs/getstarted/introvideos](https://code.visualstudio.com/docs/getstarted/introvideos)

Video khá chi tiết, _**nên xem**_

**Cài đặt Extensison**
Để lập trình Python, cần cài một số extension sau:

![VisualStudioCode](/img/2017-06-06-VSC/VSC3.png)

**Chạy thử đoạn code python bằng VSC**

Chạy 1 dòng code:

`
print("Hello world!")
`

![VisualStudioCode](/img/2017-06-06-VSC/VSC4.png)
