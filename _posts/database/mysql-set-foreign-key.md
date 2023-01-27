---
title: Mysql删除表提示Cannot truncate a table referenced in a foreign key constraint解决办法
date: 2017-09-01 19:10:49
tags: ['mysql','删除表','truncate','删除外键约束','启动外键约束']
categories: 
 - 数据库
 - MySQL
---

# 背景
因为测试过程中，几套环境都是用的同一个库，数据有点冲突，需要删库。
执行truncate table xxx时提示：
[Err] 1701 -Cannot truncate a table referenced in a foreign key constraint ....


# 解决办法

- 删除之前先执行

删除外键约束

> SET foreign_key_checks = 0

- 删除完之后再执行 

启动外键约束
> SET foreign_key_checks = 1