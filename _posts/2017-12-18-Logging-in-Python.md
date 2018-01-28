---
layout: post
title: Sử dụng logging trong Python
# subtile: Hãy viết code như một Pythonista
image: /img/2018-01-28-LOGGING/logger.png
tags: [Python, lap-trinh, programming-language, Pythonista]
categories: [Dev-Python]
date: 2018-01-28
---


**Logging**: Kỹ thuật đặt các output dữ liệu tại các vị trí khác nhau trong code. Mục đích để lấy dữ liệu cần lưu ý trong quá trình chương trình chạy

Mục đích để lấy dữ liệu cần lưu ý trong quá trình chương trình chạy.
Thực hiện phân tích các notification để đưa ra cảnh báo cho quản trị ứng dụng.


Thói quen "xấu" của lập trình viên là thường thực hiện "in" ra giá trị tại mỗi bước thực hiện. 

Hoặc trong mỗi đoạn lệnh Exception lại thực hiện in ra màn hình lỗi. 


Kết thúc mỗi giai đoạn của dự án, LTV phải thực hiện xóa hoặc thực hiện "rào" đoạn mã lệnh print.
Hậu quả: 
- Lãng phí thời gian.
- Làm xấu mã nguồn.
- Mất đồng bộ hoặc gây ra lỗi ngớ ngẩn liên quan đến font chữ của terminal

Hãy thay đổi thói quen bằng cách sử dụng logging.

Logging có các lợi điểm như sau:
- Tạo ra các message bao gồm cả timestamp
- Sẵn có các loglevel: Info, Warning, Debug, Error.
- Có thể chọn đặt log lên màn hình console hoặc ghi ra file.
- Dễ dàng thực hiện on/off tiến trình đặt log
- Phân chia file log thành nhiều đoạn theo dung lượng, theo thời gian.



```python
import logging

```


```python
# basic logging: Set log and print to console
logging.basicConfig(format='%(asctime)s - %(levelname)s - %(message)s', level=logging.DEBUG)
logging.debug('This is a debug log message.')
logging.info('This is a info log message.')
logging.warning('This is a warning log message.')
logging.error('This is a error log message.')
logging.critical('This is a critical log message.')

```

Log - Level: DEBUG - INFO - WARNING - ERROR - CRITICAL


```python
# Đặt log và đưa vào 1 file:
import logging
logging.basicConfig(filename='log_filename.txt', format='%(asctime)s - %(levelname)s - %(message)s')
logging.debug('This is a debug log message.')
logging.info('This is a info log message.')
logging.warning('This is a warning log message.')
logging.error('This is a error log message.')
logging.critical('This is a critical log message.')

```

Nhược điểm của phương pháp logging là khi đã import logging vào thì không thay đổi được level

--> Sử dụng các đối tượng của logging để xử lý vấn đề này

https://docs.python.org/3/library/logging.handlers.html




```python
# Ví dụ 3: In ra màn hình + ghi vào file.

import logging
from logging import FileHandler
from logging import StreamHandler
from logging import Formatter

logger = logging.getLogger('mylog')
formatter = Formatter('%(asctime)s - %(levelname)s - %(message)s')

# file handles
file_handler = FileHandler('log_filename.txt')
file_handler.setLevel(logging.CRITICAL)
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)

# stream handles
stream_handler = StreamHandler()
stream_handler.setLevel(logging.CRITICAL)
stream_handler.setFormatter(formatter)
logger.addHandler(stream_handler)

logger.debug('This is a debug log message.')
logger.info('This is a info log message.')
logger.warning('This is a warning log message.')
logger.error('This is a error log message.')
logger.critical('This is a critical log message.')


```

File log lớn quá gây khó khăn cho việc đọc log --> tách file log thành nhiều file khác nhau theo kích thước hoặc thời gian



```python
# Ví dụ 4: Tách log thành các file log theo kích thước
import logging
from logging.handlers import RotatingFileHandler
from logging import Formatter

formatter = Formatter('%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger('RotatingFileHandler')
handler = RotatingFileHandler('log_filename.txt', maxBytes=2, backupCount=10)
handler.setFormatter(formatter)
handler.setLevel(logging.DEBUG)
logger.addHandler(handler)

for index in range(1000):
    logger.debug('This is a debug log message.')
    logger.info('This is a info log message.')
    logger.warning('This is a warning log message.')
    logger.error('This is a error log message.')
    logger.critical('This is a critical log message.')


```


```python
# Ví dụ 5: Tách log thành các file log theo thời gian
import logging
from logging.handlers import TimedRotatingFileHandler
from logging import Formatter

formatter = Formatter('%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger('RotatingFileHandler')
# tách file hàng ngày vào 0h
handler = TimedRotatingFileHandler('time_log_file.txt', when="midnight", interval=1)
handler.setFormatter(formatter)
handler.setLevel(logging.DEBUG)
logger.addHandler(handler)

```

`when` trong TimedRotatingFileHandler có thể nhận các giá trị sau:
- second (s)
- minute (m)
- hour (h)
- day (d)
- w0-w6 (weekday, 0=Monday)
- midnight

Ứng dụng logging trong code: 
- Khi thực hiện code, đặt level của log là DEBUG, khi triển khai sửa lại Level là INFO --> bỏ qua level DEBUG không thực hiện in ra màn hình hoặc in ra log.

- Nếu không cần đến logging --> tắt chế độ ghi log:
```Python
logger.disabled = True
```

Bật lại chế độ ghi log
```Python
logger.disabled = False
```

