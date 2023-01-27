---
title: 不同语言/环境下的日期格式，获取当前日期/时间
date: 2018-08-24 11:36:11
tags: ['java','时间','当前日期','当前时间']
categories: 
 - 开发语言
 - Java
---

## linux shell

查看当前日期 & 当前时间

>$ date

Fri Aug 24 09:04:22 CST 2018

>$ date +%Y%m%d

20180824

>$ date +%Y-%m-%d

2018-08-24
>$ date '+%Y/%m/%d %H:%M:%S'

2018/08/24 09:05:52

还有另外一种看当前日期的命令，当前日期是24日，24日高亮

>$ cal
     August 2018    
Su Mo Tu We Th Fr Sa
          1  2  3  4
 5  6  7  8  9 10 11
12 13 14 15 16 17 18
19 20 21 22 23 24 25
26 27 28 29 30 31

## windows dos

>$ echo %time%

9:15:47.88

>$ echo %date%

2018/08/24 周五

>$ echo %date:~0,10% %time:~0,8%

2018/08/24  9:17:18

**简单解释一下：**

- date, time 都是系统变量
- :~0.10% 截取字符前10位，索引从0开始不包括10

## Java

在此以官方java.time.* 库为例

```java
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DatetimeTest {

    public static void main(String[] args) {

        // DateTimeFormatter.ISO_DATE_TIME       -  2018-08-24T10:57:30.29
        // DateTimeFormatter.ISO_LOCAL_DATE_TIME -  2018-08-24T10:57:30.29
        // DateTimeFormatter.ISO_DATE            -  2018-08-24
        // DateTimeFormatter.ISO_LOCAL_DATE      -  2018-08-24
        // DateTimeFormatter.BASIC_ISO_DATE      -  20180824
        // DateTimeFormatter.ISO_LOCAL_TIME      -  11:10:29.218
        // DateTimeFormatter.ISO_TIME            -  11:10:29.218
        // DateTimeFormatter.ISO_ORDINAL_DATE    -  2018-236  年份 - 第几天
        // DateTimeFormatter.ISO_WEEK_DATE       -  2018-W34-5  年份 - 第几周 - 周几
        //DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyyMMddHHmmss");
        DateTimeFormatter formatter = DateTimeFormatter.ISO_LOCAL_DATE_TIME;
        String now = LocalDateTime.now().format(formatter);
        System.out.println(now);
    }
}
```
