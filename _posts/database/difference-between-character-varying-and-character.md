---
title: postgresql数据库character varying和character区别
date: 2018-07-03 17:43:00
tags: ['postgre字符集']
categories: 
 - 数据库
 - PostgreSQL
---

|Name|Description|
|--|--|
|character varying(n), varchar(n)|变长，有长度限制|
|character(n), char(n)|定长，不足补空白|
|text|变长，无长度限制|

SQL 定义了两种基本的字符类型：character varying(n) 和 character(n) ，这里的 n 是一个正整数。两种类型都可以存储最多 n 个字符的字符串。试图存储更长的字符串到这些类型的字段里会产生一个错误，除非超出长度的字符都是空白，这种情况下该字符串将被截断为最大长度。这个看上去有点怪异的例外是 SQL 标准要求的。如果要存储的字符串比声明的长度短，类型为 character 的数值将会用空白填满；而类型为 character varying 的数值将只是存储短些的字符串。

如果我们明确地把一个数值转换成 character varying(n) 或 character(n) ，那么超长的数值将被截断成 n 个字符，且不会抛出错误。这也是 SQL 标准的要求。

**varchar(n) 和 char(n) 分别是 character varying(n) 和 character(n)的别名**，没有声明长度的 character 等于 character(1) ；如果不带长度说明词使用 character varying，那么该类型接受任何长度的字符串。后者是 PostgreSQL 的扩展。

另外，PostgreSQL 提供 text 类型，它可以存储任何长度的字符串。尽管类型 text 不是 SQL 标准，但是许多其它 SQL 数据库系统也有它。

character 类型的数值物理上都用空白填充到指定的长度 n 并且以这种方式存储和显示。不过，填充的空白在是无语意的。在比较两个 character 值的时候，填充的空白都不会被关注，在转换成其它字符串类型的时候，character 值里面的空白会被删除。请注意，在 character varying 和 text 数值里，结尾的空白是有语意的。

这些类型的存储需求是 4 字节加上实际的字符串，如果是 character 的话再加上填充的字节。长的字符串将会自动被系统压缩，因此在磁盘上的物理需求可能会更少些。长的数值也会存储在后台表里面，这样它们就不会干扰对短字段值的快速访问。不管怎样，允许存储的最长字符串大概是 1GB 。允许在数据类型声明中出现的 n 的最大值比这还小。修改这个行为没有什么意义，因为在多字节编码下字符和字节的数目可能差别很大。如果你想存储没有特定上限的长字符串，那么使用 text 或没有长度声明词的 character varying ，而不要选择一个任意长度限制。

【提示】这三种类型之间没有性能差别，只不过是在使用 character 的时候增加了存储尺寸。虽然在某些其它的数据库系统里，character(n) 有一定的性能优势，但在 PostgreSQL 里没有。在大多数情况下，应该使用 text 或 character varying 。


参考：[pg 8.2.23文档](https://www.postgresql.org/docs/8.2/static/datatype-character.html)