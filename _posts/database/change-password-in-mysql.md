---
title: mysql 修改密码（版本不一致修改指令有差异）
date: 2018-09-19 18:01:10
tags: ['修改密码','mysql']
categories:
 - 数据库 
 - MySQL
---

# 确定mysql版本

## 使用数据库连接工具查询

可以使用dataGrip 或者 navicat

1. 新建查询
2. select version();
查询结果:
> 5.7.18-log

## 登陆mysql查询
>[root@www bin]# ./mysql -uroot -p
Enter password:
（省略）
mysql> select version();
+------------+
| version()  |
+------------+
| 5.7.18-log |
+------------+
1 row in set (0.00 sec)

# 修改密码
## 版本说明

>使用select * from mysql.user 查询便知


1. mysql 5.7版本前，user表保存密码的字段是password 
2. mysql 5.7版本后，user表保存密码的字段是authentication_string
## 执行修改
5.7版本后
>update mysql.user set authentication_string=password('123456')
and password_last_changed = now()
where user = 'root';
>FLUSH PRIVILEGES;

5.7版本前
>update mysql.user set password=password('123456') where user = 'root';
>FLUSH PRIVILEGES;


# 啰嗦一句

网上大部分文章都是指5.7版本前的修改指令，没有写明版本，或者是因为文章写得太久了，未维护。针对此问题，查询解决办法的时候一定要带上自己的版本号，遇到的具体问题，才能更快速的解决问题。