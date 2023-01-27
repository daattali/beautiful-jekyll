---
title: sql server三种不同的赋值方法
date: 2019-04-08 16:30:00
tags: ['sql server','declare']
categories: 
 - 数据库
 - mssql
---

## 使用set关键字

```sql
declare @variable int 
set @variable = <value>
```
## 使用select语法

```sql
select @variable = <column or expression> from <tableName>
```

## 申明的同时赋值

```sql
declare @variable int = <value>
```

value 可以直接赋值 ，也可以是表达式.

举例
```sql
declare @t datetime = (select getdate())
select @t
```