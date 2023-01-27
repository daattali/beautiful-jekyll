---
title: Intellij IDEA无法使用lombok解决方法
date: 2017-08-30 20:30:20
tags: ['lombok','data','IDEA']
categories: 
 - 开发语言
 - Java
 - IDEA
---

# Maven依赖

```xml
<!-- https://mvnrepository.com/artifact/org.projectlombok/lombok -->
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <version>1.16.18</version>
    <scope>provided</scope>
</dependency>
```

# @Data用法

大家可以参考我的另外一篇文章《[【lombok】@Data](https://blog.csdn.net/amoscn/article/details/87172633)》，其实用法还比较简单。@Data可以替代Setter和Getter，省去许多时间。

## 不使用@Data

```java
public class Person{
    private String name;
    private String age;
    private String sex;
	
	public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name= name;
    }
	// 其他字段省略
}
```

## 使用@Data

```java
import lombok.Data;
@Data
public class Person{
	private String name;
	private String age;
	private String sex;
}
```

但是呢？new一个Person类，再给person set name或者set age或者set sex时竟然会显示红色。表示@Data并没有生效。

# 解决办法

1. File - > setting - > plugins
2. 点击Browse Repositories输入lombok
3. 点击安装
4. 重启IDEA
