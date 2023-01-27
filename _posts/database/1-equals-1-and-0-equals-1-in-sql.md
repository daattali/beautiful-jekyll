---
title: sql where 1=1和 0=1 的作用
date: 2017-09-21 12:08:03
tags: ['sql','where1-1','where0-1']
categories: 
 - 数据库
 - MySQL
---

where 1=1; 这个条件始终为True，在不定数量查询条件情况下，1=1可以很方便的规范语句。

# 不用where  1=1  在多条件查询中的困扰

举个例子，如果您做查询页面，并且，可查询的选项有多个，同时，还让用户自行选择并输入查询关键词，那么，按平时的查询语句的动态构造，代码大体如下：

```
string MySqlStr=”select * from table where”；

if(Age.Text.Lenght>0)
{
　　MySqlStr=MySqlStr+“Age=“+“'Age.Text'“；
}

if(Address.Text.Lenght>0)
{
　　MySqlStr=MySqlStr+“and Address=“+“'Address.Text'“；
}
```
　　①种假设

　　如果上述的两个IF判断语句，均为True，即用户都输入了查询词，那么，最终的MySqlStr动态构造语句变为：

　　MySqlStr=”select * from table where Age='18'  and Address='云南省文山州广南县小波吗村'”


　　可以看得出来，这是一条完整的正确的SQL查询语句，能够正确的被执行，并根据数据库是否存在记录，返回数据。

　　②种假设

　　如果上述的两个IF判断语句不成立，那么，最终的MySqlStr动态构造语句变为：

　　MySqlStr=”select * from table where“

　　现在，我们来看一下这条语句，由于where关键词后面需要使用条件，但是这条语句根本就不存在条件，所以，该语句就是一条错误的语句，肯定不能被执行，不仅报错，同时还不会查询到任何数据。

　　上述的两种假设，代表了现实的应用，说明，语句的构造存在问题，不足以应付灵活多变的查询条件。

# 使用 where  1=1  的好处


　　假如我们将上述的语句改为：
```
　　string MySqlStr=”select * from table where  1=1 ”；


　　if(Age.Text.Lenght>0)
　　{
　　　　MySqlStr=MySqlStr+“and Age=“+“'Age.Text'“；
　　}

　　if(Address.Text.Lenght>0)
　　{
　　　　MySqlStr=MySqlStr+“and Address=“+“'Address.Text'“；
　　}
```
　　现在，也存在两种假设

## 1种假设

　　如果两个IF都成立，那么，语句变为：

　　MySqlStr=”select * from table where  1=1 and Age='18'  and Address='云南省文山州广南县小波吗村'”，很明显，该语句是一条正确的语句，能够正确执行，如果数据库有记录，肯定会被查询到。


## 2种假设

　　如果两个IF都不成立，那么，语句变为：

　　MySqlStr=”select * from table where 1=1”，现在，我们来看这条语句，由于where 1=1 是为True的语句，因此，该条语句语法正确，能够被正确执行，它的作用相当于：MySqlStr=”select * from table”，即返回表中所有数据。

　　言下之意就是：如果用户在多条件查询页面中，不选择任何字段、不输入任何关键词，那么，必将返回表中所有数据；如果用户在页面中，选择了部分字段并且输入了部分查询关键词，那么，就按用户设置的条件进行查询。

　　说到这里，不知道您是否已明白，其实，where 1=1的应用，不是什么高级的应用，也不是所谓的智能化的构造，仅仅只是为了满足多条件查询页面中不确定的各种因素而采用的一种构造一条正确能运行的动态SQL语句的一种方法。

where 1=0; 这个条件始终为false，结果不会返回任何数据，只有表结构，可用于快速建表

"SELECT * FROM strName WHERE 1 = 0"; 该select语句主要用于读取表的结构而不考虑表中的数据，这样节省了内存，因为可以不用保存结果集。  

create table newtable as select * from oldtable where 1=0;  创建一个新表，而新表的结构与查询的表的结构是一样的。

---
声明:
**转载出自 [sql where 1=1和 0=1 的作用](http://www.cnblogs.com/junyuz/archive/2011/03/10/1979646.html)**

---