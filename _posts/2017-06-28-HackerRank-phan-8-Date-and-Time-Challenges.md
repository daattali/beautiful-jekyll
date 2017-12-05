---
layout: post
title: Hackerrank - phần 8-Date and Time-Challenges
subtile: Python coding like a Pythonista
image: /img/2017-06-15-HackerRank/Hackerrank1.png
tags: [Python, lap-trinh, program-language, hacker-rank]
categories: [Dev-Python]
date: 2017-06-28
---


Bài tập phần 8: Một vài thử thách sử dụng thư viện Date-Time của Python. [Date and Time](https://www.hackerrank.com/domains/python/py-date-time)

## [Ex8_1: Calendar Module](https://www.hackerrank.com/challenges/calendar-module/problem)


**Calendar Module**

The calendar module allows you to output calendars and provides additional useful functions for them.

class calendar.TextCalendar([firstweekday])

This class can be used to generate plain text calendars.

**Sample Code**
```Python
>>> import calendar
>>> 
>>> print calendar.TextCalendar(firstweekday=6).formatyear(2015)
                                  2015

      January                   February                   March
Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa
             1  2  3       1  2  3  4  5  6  7       1  2  3  4  5  6  7
 4  5  6  7  8  9 10       8  9 10 11 12 13 14       8  9 10 11 12 13 14
11 12 13 14 15 16 17      15 16 17 18 19 20 21      15 16 17 18 19 20 21
18 19 20 21 22 23 24      22 23 24 25 26 27 28      22 23 24 25 26 27 28
25 26 27 28 29 30 31                                29 30 31

       April                      May                       June
Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa
          1  2  3  4                      1  2          1  2  3  4  5  6
 5  6  7  8  9 10 11       3  4  5  6  7  8  9       7  8  9 10 11 12 13
12 13 14 15 16 17 18      10 11 12 13 14 15 16      14 15 16 17 18 19 20
19 20 21 22 23 24 25      17 18 19 20 21 22 23      21 22 23 24 25 26 27
26 27 28 29 30            24 25 26 27 28 29 30      28 29 30
                          31

        July                     August                  September
Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa
          1  2  3  4                         1             1  2  3  4  5
 5  6  7  8  9 10 11       2  3  4  5  6  7  8       6  7  8  9 10 11 12
12 13 14 15 16 17 18       9 10 11 12 13 14 15      13 14 15 16 17 18 19
19 20 21 22 23 24 25      16 17 18 19 20 21 22      20 21 22 23 24 25 26
26 27 28 29 30 31         23 24 25 26 27 28 29      27 28 29 30
                          30 31

      October                   November                  December
Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa      Su Mo Tu We Th Fr Sa
             1  2  3       1  2  3  4  5  6  7             1  2  3  4  5
 4  5  6  7  8  9 10       8  9 10 11 12 13 14       6  7  8  9 10 11 12
11 12 13 14 15 16 17      15 16 17 18 19 20 21      13 14 15 16 17 18 19
18 19 20 21 22 23 24      22 23 24 25 26 27 28      20 21 22 23 24 25 26
25 26 27 28 29 30 31      29 30                     27 28 29 30 31

```

**Task**

You are given a date. Your task is to find what the day is on that date.

**Input Format**

A single line of input containing the space separated month, day and year, respectively, in   format.

**Constraints**

**Output Format**

Output the correct day in capital letters.

**Sample Input**

> 08 05 2015


**Sample Output**

> WEDNESDAY


**Explanation**

The day on August th  was WEDNESDAY.


<hr>
**Code:**


```python
#!/usr/bin/env python3
import calendar

WEEKDAY = ["MONDAY", "TUEDAY", "WEDNESDAY"]

def find_weekday(input_date):
    date_sep = input_date.split()
    print(calendar.day_name[calendar.weekday(int(date_sep[2]), int(date_sep[0]), int(date_sep[1]))].upper())

if __name__ == '__main__':
    input_date = input() #mm dd yyyy
    find_weekday(input_date)
```

    06 22 2017
    THURSDAY
    

## [Ex8_2: Time Delta](https://www.hackerrank.com/challenges/python-time-delta/problem)

You are given 2 timestamps in the format given below:

Day dd Mon yyyy hh:mm:ss +xxxx

Here +xxxx represents the time zone. Your task is to print the absolute difference (in seconds) between them.

**Input Format**

The first line contains , the number of testcases. 
Each testcase contains  lines, representing time  and time .

**Constraints**

Input contains only valid timestamps
.year <= 3000

**Output Format**

Print the absolute difference (t1-t2) in seconds.

**Sample Input 0**

2
Sun 10 May 2015 13:54:36 -0700
Sun 10 May 2015 13:54:36 -0000
Sat 02 May 2015 19:54:36 +0530
Fri 01 May 2015 13:54:36 -0000

**Sample Output 0**

25200
88200

**Explanation 0**

In the first query, when we compare the time in UTC for both the time stamps, we see a difference of 7 hours. which is 7*3600 seconds or 25200 seconds.

Similarly, in the second query, time difference is 5 hours and 30 minutes for time zone adjusting for that we have a difference of 1 day and 30 minutes. Or 24 * 3600 + 30 * 60 = 88200


<hr>
**Code:**



```python
#!/usr/bin/env python3
from datetime import datetime

def time_delta(t1, t2):
    j1 = t1.split()
    j2 = t2.split()
    s1 = j1[0]+":"+j1[1]+":"+j1[2]+":"+j1[3]+":"+j1[4]+":"+j1[5]
    s2 = j2[0]+":"+j2[1]+":"+j2[2]+":"+j2[3]+":"+j2[4]+":"+j2[5]
    FMT = '%a:%d:%b:%Y:%H:%M:%S:%z'
    tdelta = datetime.strptime(s2, FMT) - datetime.strptime(s1, FMT)
    return int(abs(tdelta.total_seconds()))


if __name__ == "__main__":
    t = int(input().strip())
    for a0 in range(t):
        t1 = input().strip()
        t2 = input().strip()
        delta = time_delta(t1, t2)
        print(delta)

```

    2
    Sun 10 May 2015 13:54:36 -0700
    Sat 02 May 2015 19:54:36 +0530
    714600
    Fri 01 May 2015 13:54:36 -0000
    Sun 10 May 2015 13:54:36 -0000
    777600
    
