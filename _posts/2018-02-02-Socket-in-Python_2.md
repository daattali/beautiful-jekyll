---
layout: post
title: Xây dựng một ứng dụng socket Server - Client đơn giản (phần 2)
# subtile: Hãy viết code như một Pythonista
image: /img/2018-02-01-Socket/SC.png
tags: [Python, lap-trinh, programming-language, Pythonista]
categories: [Dev-Python]
date: 2018-02-02
---

**Ví dụ** đơn giản về lập trình socket-client trong Python

**Server**: 
- Liên tục lắng nghe client kết nối đến. 
- Khi có client kết nối đến, in ra thông tin địa chỉ IP của client và trả về một đoạn text cho client.
- Server dừng lại và tắt khi client_count == 2. (có thể thay đổi số này)

**Client**: 
- Kết nối đến server.
- nhận thông điệp trả về từ server.
- in ra màn hình thông điệp đó.

# Listing code:

```Python
# Server.py

import socket
# Create a socket object
s = socket.socket()
# Get local machine name
host = socket.gethostname()
# Reserve a port for your service.
port = 1312
# Bind to the port
s.bind((host, port))
# Now wait for client connection.
s.listen(5)
print('start listen client connection...')
# stop when count == 2
count = 0
while True:
    # Establish connection with client.
    c, addr = s.accept()
    print('Got connection from', addr)
    print("Send response to client")
    c.send('Thank {} for connecting'.format(':'.join([str(item) for item in addr])))
    # Close the connectionne
    c.close()
    count += 1
    if count == 2:
        break
s.close()
```


```Python
import socket
# Create a socket object
s = socket.socket()
# Get local machine name
host = socket.gethostname()
# Reserve a port for your service.
port = 1312

s.connect((host, port))
# print respone from server
print('respone from server: {}'.format(s.recv(1024)))
# Close the socket when done
s.close
```

# Demo:
![socket.png](/img/2018-02-01-Socket/demo.png)