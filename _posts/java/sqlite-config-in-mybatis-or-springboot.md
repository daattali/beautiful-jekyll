---
title: mybatis generator(或者springboot)配置sqlite
date: 2018-10-18 09:15:00
tags: ['mybatis','mybatis generator','sqlite']
categories: 
 - 开发语言
 - Java
 - Mybatis
---

# mybatis 配置

在配置好url后使用generator，不是提示sqlite文件不符合要求，就是告警`[WARNING] Table configuration with catalog null, schema null, and table application did not resolve to any tables` , 结果是没有任何文件生成。

我的sqlite.db是放置在项目的resources目录底下的，MG一直找不到这个文件。

搜索很久，也都一一尝试，还是失败告终。最后使用最原始的方式，以项目根目录作为起始点，写入sqlite.db的文件路径，生成成功。

`假设`： .db文件是放置于resources路径下

```xml
<!-- 数据库配置文件的url是不能直接拷贝过来用的，需要把&换成'&amp;' -->
<jdbcConnection driverClass="org.sqlite.JDBC"
            connectionURL="jdbc:sqlite::resource:sqlite.db"
            userId="${jdbc.username}"
            password="${jdbc.password}">
</jdbcConnection>
```

url按此写法可以生成成功，如有其他方式欢迎留言

驱动使用上述class文件，maven引入配置:

```xml
 <dependency>
     <groupId>org.xerial</groupId>
     <artifactId>sqlite-jdbc</artifactId>
     <version>3.25.2</version>
 </dependency>
```

帐号密码根据实际情况填写，如果没有帐号密码，可以填写为`""`


# springboot applicaiton.properities配置

`假设`： .db文件是放置于resources路径下

    jdbc.url=jdbc:sqlite::resource:env.db
    jdbc.username=
    jdbc.password=
    jdbc.driver=org.sqlite.JDBC

如果是resources其他路径，比如resources/sqlite，请相应做修改: jdbc:sqlite::resource:sqlite/env.db

# 注意 

特别注意 

{% note danger %}
项目的配置文件夹名为 `resources`（IDEA创建java项目时默认都是这个名字），但是配置项里面的是`resource`，不要写错了！
{% endnote %}
