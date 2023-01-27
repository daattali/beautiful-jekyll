---
title: JMeter总结【1】连接各种数据库配置
date: 2017-07-11 18:42:00
tags: ['mysql','jmeter','数据库','postgresql','sqlserver']
categories: 
 - 软件测试
 - 测试工具
---

# postgresql
 
 1. 添加jdbc connection configuration；
 2. Variable Name：名字随意取，但是在建立JDBC Request的时候会用到；
 3. Database URL：
```
jdbc:postgresql://host:5432/DatabaseName?characterEncoding#UTF-8
```
 4. JDBC Driver class：org.postgresql.Driver
 5. Username：数据库用户名
 6. Password：数据库密码


**备注：**
pg数据库驱动下载地址：[点这里](https://jdbc.postgresql.org/download.html)

----------


# MySQL

 1. 添加jdbc connection configuration；
 2. Variable Name：名字随意取，但是在建立JDBC Request的时候会用到；
 3. Database URL：
```
jdbc:mysql://host:3306/DatabaseName
```
 4. JDBC Driver class：org.gjt.mm.mysql.Driver【老版本驱动不推荐】  或者 com.mysql.jdbc.Driver【推荐】
 5. Username：数据库用户名
 6. Password：数据库密码


**备注：**
MySQL数据库驱动下载地址：[点这里](https://dev.mysql.com/downloads/connector/j/)


----------


# SQL Server

 1. 添加jdbc connection configuration；
 2. Variable Name：名字随意取，但是在建立JDBC Request的时候会用到；
 3. Database URL：
```
jdbc:sqlserver://localhost:1433;DatabaseName=你的数据库名
```
 4. JDBC Driver class：com.microsoft.sqlserver.jdbc.SQLServerDriver
 5. Username：数据库用户名
 6. Password：数据库密码


**备注：**
SQL Server数据库驱动下载地址：[点这里](https://www.microsoft.com/en-us/download/details.aspx?displaylang=en&id=11774)


----------


# SQLite

 1. 添加jdbc connection configuration；
 2. Variable Name：名字随意取，但是在建立JDBC Request的时候会用到；
 3. Database URL：请注意，**db文件需要放在 jmeter/bin目录下**
```
jdbc:sqlite:databasename.db
```
 4. JDBC Driver class：org.sqlite.JDBC
 5. Username：数据库用户名（可能无帐号密码，就留空）
 6. Password：数据库密码（可能无帐号密码，就留空）


**备注：**
SQLite数据库驱动下载地址：[点这里](http://download.csdn.net/download/u012388993/9850445)


----------


# Oracle

 1. 添加jdbc connection configuration；
 2. Variable Name：名字随意取，但是在建立JDBC Request的时候会用到；
 3. Database URL：
```
jdbc:oracle:thin:@127.0.0.1:1521:DatabaseName
```
 4. JDBC Driver class：oracle.jdbc.driver.OracleDriver
 5. Username：数据库用户名
 6. Password：数据库密码


**备注：**
Orcale数据库驱动下载地址：[点这里](http://www.oracle.com/technetwork/apps-tech/jdbc-112010-090769.html)


----------

**JMeter添加jar的方法：选其一即可**

 - 点击测试计划，测试计划最下方的add directory or jar to classpath，添加上下载的jar；
 - 将下载的jar文件放置于apache-jmeter-3.0\lib\ext目录内；
 - 将下载的jar文件放置于apache-jmeter-3.0\lib目录内；