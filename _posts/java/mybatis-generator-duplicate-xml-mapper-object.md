---
title: MyBatis Generator生成重复xml/Mapper对象解决方案
date: 2019-11-26 17:12:00
updated: 2019-11-26 17:12:00
tags: ['MBG','mybatis']
categories: 
 - 开发语言
 - Java
 - Mybatis
---

## 背景

配置版本信息
MBG：1.3.7
MYSQL 驱动：8.0.15

出问题的`table`标签配置如下:

```java
<table tableName="account" domainObjectName="Account"
       modelType="flat"
       enableCountByExample="false"
       enableUpdateByExample="false"
       enableDeleteByExample="false"
       enableSelectByExample="false"
       selectByExampleQueryId="false">
    <property name="useActualColumnNames" value="false"/>
</table>
```


执行MBG后，告警提示：
>[WARNING] Table Configuration account matched more than one table (abc..account,xyz..account)

说明该数据库连接下有两个库`abc`, `xyz`，里面都有account表，需要指定是用哪一个库，于是我在table标签里面添加上`schema="abc"`，再次执行MBG提示：

>[INFO] Saving file AccountMapper.xml
>[INFO] Saving file AccountMapper.xml
>[INFO] Saving file Account.java
>[INFO] Saving file AccountMapper.java
>[INFO] Saving file Account.java
>[INFO] Saving file AccountMapper.java

说明在table里面添加`schema`属性后，指定使用哪一个库压根就没有成功，依然会生成重复的文件。

## 解决

搜索了很久..... 查询各个配置还是得不到解决，最后尝试将`schema`修改为`catalog`后再次执行，只生成了一次文件，没有再重复，问题解决

```java
<table catalog="abc" tableName="account" domainObjectName="Account"
       modelType="flat"
       enableCountByExample="false"
       enableUpdateByExample="false"
       enableDeleteByExample="false"
       enableSelectByExample="false"
       selectByExampleQueryId="false">
    <property name="useActualColumnNames" value="false"/>
</table>
```