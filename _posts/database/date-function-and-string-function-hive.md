---
title: Hive常用函数（日期函数/字符串函数）
date: 2019-06-03 01:36:48
tags: ['hive','Hive时间','Hive字符串']
categories: 
 - 数据库
 - Hive
---

# Hive 日期函数

| **Date Function**                                            | **Description**                                              | Example                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| current_timestamp()                                          | 返回当前系统的日期和时间， Hadoop Hive中是没有now()函数的.   | `2020-04-15 18:00:04`                                        |
| current_date()                                               | 返回当前系统的日期.                                          | `2020-04-15`                                                 |
| add_months(timestamp date, int months)                       | 添加月份数值到指定的日期或者时间戳.                          | add_months('2019-10-10', 1) returns `2019-11-10`<br />add_months('2019-10-10 10:10:10', 1) returns `2019-11-10` |
| to_date(timestamp date)                                      | 将时间戳转换为date数据格式                                   | to_date(CURRENT_TIMESTAMP) returns `2020-04-24`              |
| date_add(timestamp startdate, int days)                      | 添加天数到指定的日期或时间戳. Hive的date_add函数不支持间隔数据类型. 并且时间部分会自动省略 | date_add('2019-10-10', 1) returns `2019-10-11`<br />date_add('2019-10-10 10:10:10', 1)  returns `2019-10-11` |
| date_sub(timestamp startdate, int days)                      | 在指定的日期或时间戳上减去对应的天数.                        | date_sub('2019-10-12', 1) returns `2019-10-11`<br />date_sub('2019-10-12 10:10:10', 1)  returns `2019-10-11` |
| datediff(timestamp enddate, timestamp startdate)             | 返回两个时间戳或者日期数据之间的日期差，enddate-startdate    | datediff('2019-12-21','2019-12-20') returns `1`              |
| from_unixtime(bigint unixtime[, string format])              | 将秒数转换为指定格式的时间                                   | from_unixtime(0, 'yyyy-MM-dd HH:mm:ss')  returns `1970-01-01 00:00:00` |
| month(timestamp date), minute(timestamp date), hour(timestamp date), day(timestamp date), second(timestamp date) | 从时间戳获取到month, minutes, hours, days, seconds.          |                                                              |
| trunc(timestamp, string unit)                                | 从指定的时间戳或者日期内剥离年或者月，返回年月日，看例子     | desc function extended trunc; -- 可查看trunc命令<br />trunc( , 'YYYY'/'YEAR'/'YY') :` 2020-1-1` 今年第一天<br />trunc( , 'MM'/'MON'/'MONTH') : `2020-4-1` 这个月第一天 |
| unix_timestamp()                                             | 以默认时区获取当前时间戳.                                    | `1,587,716,247`                                              |
| unix_timestamp(string date)                                  | 将时间字符串 yyyy-MM-dd HH:mm:ss 转为时间戳.                 | unix_timestamp('2020-03-03 10:20:30') `1,583,202,030`        |
| from_utc_timestamp(timestamp, string timezone)               | 将指定的UTC时间戳以指定的时区转换为日期/时间                 | from_utc_timestamp(1587716907000, 'Asia/Shanghai') `2020-04-25 00:28:27` |


# Hive字符串函数

**ASCII( string str )**

返回字符串第一个字符的ascii码.

```
Example1: ASCII('hadoop') returns 104
Example2: ASCII('A') returns 65
```


**CONCAT( string str1, string str2... )**

CONCAT 函数连接所有字符串.

```
Example: CONCAT('hadoop','-','hive') returns 'hadoop-hive'
```


**CONCAT_WS( string delimiter, string str1, string str2... )**

与CONCAT函数类似. 在拼接的字符串str1，str2... 中接入分隔符.

```
Example: CONCAT_WS('-','hadoop','hive') returns 'hadoop-hive'
```


**FIND_IN_SET( string search_string, string source_string_list )**

在`source_string_list`中寻找`search_string`，返回第一次匹配的位置。`source_string_list`应该使用逗号隔开，如果`search_string`包含逗号则返回0。

```
Example: FIND_IN_SET('ha','hao,mn,hc,ha,hef') returns 4
```


**LENGTH( string str )**

字符串长度，亦即字符个数.

```
Example: LENGTH('hive') returns 4
```


**LOWER( string str ), LCASE( string str )**

字符串转小写.

```
Example: LOWER('HiVe') returns 'hive'
```


**LPAD( string str, int len, string pad )**

指定字符串长度，不够的位置左边以`pad`填充

```
Example: LPAD('hive',6,'v') returns 'vvhive'
```


**LTRIM( string str )**

字符串左侧空格全部删除

```
Example: LTRIM('   hive') returns 'hive'
```


**REPEAT( string str, int n )**

将指定的字符串重复n次.

```
Example: REPEAT('hive',2) returns 'hivehive'
```


**RPAD( string str, int len, string pad )**

指定字符串长度，不够的位置右边以`pad`填充

```
Example: RPAD('hive',6,'v') returns 'hivevv'
```


**REVERSE( string str )**

字符串翻转

```
Example: REVERSE('hive') returns 'evih'
```


**RTRIM( string str )**

移除字符串最后的空格.

```
Example: LTRIM('hive   ') returns 'hive'
```


**SPACE( int number_of_spaces )**

返回相应数量个空格字符

```
Example: SPACE(4) returns '    '
```


**SPLIT( string str, string pat )**

以`pat`模式分割字符串，并返回字符串数组。`pat`模式可以指定为正则表达式.

```
Example: SPLIT('hive:hadoop',':') returns ["hive","hadoop"]
```


**SUBSTR( string source_str, int start_position [,int length] ), SUBSTRING( string source_str, int start_position [,int length] )**

俩函数作用一致，从字符串首位（从1计数）截取固定长度的字符串，若长度未给出，则直到字符串最末尾.

```
Example1: SUBSTR('hadoop',4) returns 'oop'
Example2: SUBSTR('hadoop',4,2) returns 'oo'
```


**TRIM( string str )**

移除字符串前部和后部空格.

```
Example: TRIM('   hive   ') returns 'hive'
```


**UPPER( string str ), UCASE( string str )**

字符串中的字母全部转大写.

```
Example: UPPER('HiVe') returns 'HIVE'
```