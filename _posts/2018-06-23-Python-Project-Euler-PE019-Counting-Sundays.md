---
layout: post
title: PE019-Counting-Sundays
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-08-ProjectEuler/PE.png
tags: [Python, Project-Euler]
categories: [Project-Euler]
date: 2018-06-23
# 2018-06-23-Python-Project-Euler-PE019-Counting-Sundays.md
---
Hãy tìm tổng lớn nhất của đường đi với tam giác lớn

## Problem PE019-Counting-Sundays
You are given the following information, but you may prefer to do some research for yourself.
```
* 1 Jan 1900 was a Monday.
* Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    And on leap years, twenty-nine.
* A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
```

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?



## Đề bài
Từ 1/1/1901 đến 21/12/2000 có bao nhiêu ngày chủ nhật là ngày đầu tiên trong tháng.


## Phân tích đề bài:

Để xác định ngày đầu tiên trong tháng có phải là ngày chủ nhật hay không có giải thuật khá hay của Judas nhưng ... tôi thấy không cần thiết phải bỏ ra quá nhiều thời gian để làm vậy (đúng hơn là sau khi làm project [lịch âm lịch Việt nam](https://github.com/quangvinh86/Flask-LunarSolar) xong tôi thấy mệt mỏi với mấy cái "thời gian"). 

Với Python hoặc với bất kỳ ngôn ngữ lập trình nào đều có các function so sánh ngày tháng năm. Vậy chúng ta có thể "trâu bò" mà dùng.

```Python

import datetime


def count_sundays():
    return sum(1 for y in range(1901, 2001)
               for m in range(1, 13)
               if datetime.date(y, m, 1).weekday() == 6)


if __name__ == "__main__":
    import time
    start = time.time()
    result = count_sundays()
    done = time.time()
    print("Have {} sundays on the 1st of a month from 1901 to 2001".format(result))
    elapsed = done - start
    print("elapsed time: {}s".format(elapsed))


```
Thời gian chạy bài toán

```
Have 171 sundays on the 1st of a month from 1901 to 2001
elapsed time: 0.0005667209625244141s

```

Source-code:
[PE-019](https://github.com/quangvinh86/python-projecteuler/tree/master/PE-019)
