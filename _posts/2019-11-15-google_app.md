---
layout: post
title: Webapp with Google Ecosystem
subtitle:  
tags: [Google Ecosystem, other]
---


**"Không biết thì hỏi Google"** bao lâu nay Google đã đi vào đời sông của chúng ta như một phần không thể thiếu như vậy. 
Chúng ta vẫn ngày ngày sử dụng các tiện ích của anh Google và bản thân tôi luôn cảm thấy biết ơn vì điều đó, Gmail, 
Drive, Youtube, Google Spreadsheet...


<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcQTGz_pqXbWaool5DAii_NGXjKo1NTtrNA5-vUrgc4pJPuhHCUV&usqp=CAU" width="500" />


Nhưng hệ sinh thái Google cho chúng ta nhiều hơn thế Chúng ta có thể tự build cho mình một Webapp trên nền tảng Google Ecosystem. Các bạn không nghe lầm đâu, chính là 1 webapp như quản lý phòng khách sạn, quản lý quán cafe hoàn toàn miễn phí và rất đơn giản.

Chuyện là trước đây vài năm mình có tìm kiếm một công cụ nhanh gọn, miễn phí để xây dựng 1 ứng dụng quả lý đơn giản cho mình như quản lý chi tiêu, quản lý cửa hàng nhỏ, điều đầu tiên mình nghĩ tới là  Excel VBA. Với Excel thì quá đơn giản để thực hiện những ý tưởng của mình cộng với VBA thì như hổ thêm cánh, thế là ứng dụng cơ bản ra đời. Nhưng ngay sau đó mình nhận ra một điều vô cùng bất tiện là khi mình không mang theo laptop thì không thể sử dụng ứng dụng, đó là lúc mình nghĩ mình cần 1 Webapp.

Sau khi tìm kiếm trên mạng 1 hồi thì cuối cùng giải pháp từ chính cái anh mà mình đang dùng để tìm kiếm - Google. Với công thức gồm có **Google Spreadsheet** + **Google Apps Script** + **Google Data studio** mình đã build Webapp vượt qua mong đợi của mình về cả tính năng và giao diện.

**Google Spreadsheet** thì chắc các bạn ai cũng biết rồi mình sẽ không giới thiệu nữa. 

**Google Apps Script** là công cụ viết mã kịch bản của Google sử dụng ngôn ngữ Javascript nó giống như VBA của excel vậy.

**Google Data studio** là công cụ BI google, tuy rằng không lâu đời như các công cụ BI khác nhưng nó có tính tương thích cao vì cùng một nhà với các công cụ trên. Do vậy build dashboard, report bằng google data studio phải nói là tuyệt cú mèo



## Ý tưởng Một web app đơn giản

Google Apps Script cho phép chúng ta dễ dàng xây dựng front-end cho web bằng định dạng html, css và javascripts, phần front-end như vật đã rất đảm bảo. Nhưng vì mục tiêu của chúng ta là xâp dựng 1 web app nên phần back-end và cơ sở dữ liệu là không thể thiếu. 
Do quy mô và chức năng của web app rất nhỏ nên google sheets hoàn toàn có thể đáp ứng là cơ sở dữ liệu. Ngoài ra Google Spreadsheet sẽ giúp ta tính toán các chức năng và nhiệm vụ cơ bản, kết hợp với javascript thì coi như nhiệm vụ back-end có thể hoàn thành 
Vì cơ sở dữ liệu xây dựng trên Google Spreadsheet nên việc xây dựng Dashboard, report trên Google Data studio là rất dễ dàng. Ta hoàn toàn có thể nhúng các kết quả từ Google Data studio vào web app của mình để làm phong phú thêm chức năng. 
Với ý tưởng đơn giản như vậy mình đã cho ra đời rất nhiều ứng dụng web app, có đủ chức năng thêm, xóa, sửa, reports phục vụ cho bản thân và những người bạn của mình.

# Các ứng dụng:

1. Ứng dụng chi tiêu cá nhân :  

Thực hiên việc gi chép các phát sinh chi tiêu , thống kê các chi tiêu và đặt ngân sách chi tiêu

![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/google_app_0.png)

2. Ứng dụng chi tiêu chung 

Mình từng ở chung cùng 3 bạn nữa hồi đại học nên có rất nhiều khoản chi tiêu chung, do vậy mình làm ứng dụng để thực hiện các chức năng phân bổ công nợ cho mỗi người và gửi mail tự động nhắc nợ mỗi cuối tuần.

![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/google_app_1.png)


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/google_app_2.png)

