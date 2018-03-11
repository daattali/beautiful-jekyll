---
layout: post
title: Xây dựng một ứng dụng socket server - client đơn giản (phần 1)
# subtile: Hãy viết code như một Pythonista
image: /img/2018-02-01-Socket/SC.png
tags: [Python, lap-trinh, programming-language, Pythonista]
categories: [Dev-Python]
date: 2018-02-01
---


**Lập trình socket**: Là kỹ thuật lập trình xây dựng ra các phần mềm cho phép chúng ta kết nối các máy tính để thực hiện truyền tải và nhận dữ liệu thông qua mạng.

Ví dụ: Các chương trình chat messager, teamviewer nội bộ chính là một ví dụ về lập trình client - server.

# ĐỊNH NGHĨA SOCKET
Socket là một giao diện lập trình ứng dụng mạng (network application interface). Thông qua giao diện này, lập trình viên có thể thực hiện lập trình điều khiển, truyền dữ liệu giữa các máy tính có kết nối mạng với nhau. 

## Giao thức (protocol)
Socket sử dụng hai giao thức chính để truyền dữ liệu 
- Stream Socket: Dựa trên giao thúc TCP ( Tranmission Control Protocol). Hai máy tính sẽ thực hiện truyền dữ liệu khi đã có kết nối được xác thực. Cơ chế này tương đối an toàn nhờ vào cơ chế quản lý gói tin.
- Datagram Socket: Dựa trên giao thức UDP ( User Datagram Protocol). việc truyền dữ liệu không yêu cầu có sự thiết lập kết nối giữa 2 quá trình. Dữ liệu được truyền qua UDP không được tin cậy. Tuy nhiên việc truyền bản tin đi nhanh nên vẫn được áp dụng trong lập trình game, hoặc tin nhắn không quan trọng.

## Port
Với mỗi ứng dụng socket được mở trên máy chủ hoặc máy client sẽ được gắn cho mình một port, port này chính là đầu mối phân biệt các ứng dụng nếu trên server có nhiều ứng dụng socket cùng chạy.

Ví dụ: 
Chương trình chat nội bộ đang mở ở port 5005 trên máy của bạn. Khi có 1 bản tin gửi đến máy của bạn ở port 5005 --> bản tin đó sẽ được định hướng về ứng dụng chat đang mở trên port 5005.

**Stream socket** (TCP) sẽ được định dang bởi 1 địa chỉ IP và một port

Ví dụ: 127.0.0.1:5005

# Ứng dụng Client – Server
Chương trình phần mềm được chia riêng rẽ 2 phần client (chạy trên máy khách), server (chạy trên máy chủ), chúng giao tiếp với nhau bằng giao thức stream socket hoặc datagram socket.

 Quy trình hoạt động của ứng dụng Server – Client như sau: 
 
  **Server** có nhiệm vụ của là lắng nghe, chờ đợi kết nối từ Client trên địa chỉ IP của mình với PORT được quy định sẵn. 
  
  Khi client gởi dữ liệu tới Server thì nó phải giải quyết một công việc là nhận dữ liệu đó -> xử lý -> trả kết quả lại cho Client.

  **Client** là ứng dụng được phục vụ, nó chỉ nhận yêu cầu từ người dùng và gởi truy vấn lên server và chờ đợi kết quả từ Server

## Sơ đồ cơ chế thực hiện của giao thức TCP:
![socket.png](/img/2018-02-01-Socket/tcp2.jpg)



## Sơ đồ cơ chế thực hiện của giao thức UDP:
![socket.png](/img/2018-02-01-Socket/udp2.jpg)


Note: Phần 2 sẽ hướng dẫn các bạn viết một ứng dụng client - server đơn giản.
