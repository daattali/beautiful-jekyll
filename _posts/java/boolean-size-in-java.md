---
title: Java中boolean类型占几个字节，你知道吗？
date: 2019-07-26 17:21:00
updated: 2019-07-26 17:21:00
tags: ['java','JVM','boolean','字节']
categories: 
 - 开发语言
 - Java
---

# 背景

最近在复盘Java基础知识，看到基础数据类型这一章节，有一张图片是这样的。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190726115810420.png)

比较好奇，为什么其他类型都有字节标识，唯独boolean没有，不是只占用`1bit ~ 1位`的吗 ？

## 找答案

{% tabs docment %}
<!-- tab 疯狂Java讲义（3版） -->
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190726120442810.png)

一个boolean类型占用8位 = 1字节
<!-- endtab -->
<!-- tab Java官网 -->
[Primitive Data Types](https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html)

>boolean: The boolean data type has only two possible values: true and false. Use this data type for simple flags that track true/false conditions. This data type represents one bit of information, but its "size" isn't something that's precisely defined.

解释一下：

>布尔数据类型只有两个可能的值：true和false。 将此数据类型用于跟踪真/假条件的简单标志。 此数据类型表示一位信息，但其“大小”`不是精确定义`的内容。
<!-- endtab -->
<!-- tab jdk specs -->
[jdk specs文档](https://docs.oracle.com/javase/specs/#22909)
我对比了jdk8， jdk11 和 jdk12 对于boolean类型的说明是完全一样的，故只贴出jdk12的图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190726165133195.png)

翻译一下：
>虽然Java虚拟机定义了一个`boolean`类型，但它只为它提供了非常有限的支持。没有Java虚拟机指令专门用于对`boolean`值的操作。相反，Java编程语言中对`boolean`值进行操作的表达式被编译为使用Java虚拟机`int`数据类型的值。 
>Java虚拟机直接支持`boolean`数组。它的newarray指令可以创建`boolean`数组。使用`byte`数组指令baload和bastore访问和修改类型为`boolean`的数组。
>在Oracle的Java虚拟机实现中，Java编程语言中的`boolean`数组被编码为Java虚拟机`byte`数组，每个布尔元素使用8位。 
>Java虚拟机使用1表示`boolean`数组组件的true，0表示false。其中Java编程语言布尔值由编译器映射到Java虚拟机类型int的值，编译器必须使用相同的编码。
<!-- endtab -->
{% endtabs %}

## 结论

1. `boolean类型`被编译为int类型，等于是说JVM里占用字节和int完全一样，int是4个字节，于是boolean也是`4字节`
2. `boolean数组`在Oracle的JVM中，编码为byte数组，每个boolean元素占用`8位`=`1字节`
3. （待考证）boolean数组在非Oracle JVM里面，占用字节数`也许不是1字节`
