---
title: Idea执行assert false未生效问题处理
date: 2019-01-25 11:26:23
updated: 2019-01-25 11:26:23
tags: ['断言','assert无效']
categories: 
 - 开发语言
 - Java
---

# 问题背景

在某个方法里添加了assert false来主动抛出异常，但是很奇怪的时，执行到这段代码却没有堆栈抛出。

## 测试assert false

```java
package com.amos.learn.util;

import org.junit.Test;

public class AssertTest {

    @Test
    public void testAssert() {
        assert false;
        System.out.println("junit");

    }

    public static void main(String[] args) {
        assert false;
        System.out.println("main");
    }
}
```

## 执行testAssert方法

>java.lang.AssertionError at com.amos.learn.util.AssertTest.testAssert(AssertTest.java:9)

## 执行main方法

>junit
Process finished with exit code 0

奇怪的是，`assert false;`在main方法里竟然没有生效。

# 解决问题

## 对比两次java执行命令

在idea内点击run的时候，Run面板可以看到各自的java执行命令

{% tabs run %}
<!-- tab junit -->
>"C:\Program Files\Java\jdk1.8.0_171\bin\java.exe" `-ea` -Didea.test.cyclic.buffer.size=1048576 "此处省略编码/代理/jar包等等" com.intellij.rt.execution.junit.JUnitStarter -ideVersion5 -junit4 com.amos.learn.util.AssertTest,testAssert
<!-- endtab -->
<!-- tab main -->
>"C:\Program Files\Java\jdk1.8.0_171\bin\java.exe" -Didea.test.cyclic.buffer.size=1048576 "此处省略编码/代理/jar包等等" com.intellij.rt.execution.junit.JUnitStarter -ideVersion5 -junit4 com.amos.learn.util.AssertTest
<!-- endtab -->
{% endtabs %}

从上两次的执行命令可以看出，junit有加入`-ea`选项，这个是什么呢？

打开cmd/powershell面板，输入`java -help`，往下面翻，可以看到有这么一段命令解释（默认显示的中文解释）：

    -ea[:<程序包名称>...|:<类名>]
    -enableassertions[:<程序包名称>...|:<类名>]
                  按指定的粒度启用断言
    -da[:<程序包名称>...|:<类名>]
    -disableassertions[:<程序包名称>...|:<类名>]
                  按指定的粒度禁用断言
    -esa | -enablesystemassertions
                  启用系统断言
    -dsa | -disablesystemassertions
                  禁用系统断言
<br>
jvm在执行class文件的时候，默认是没有启动指定粒度/系统断言的。所以如果想在非@Test方法（或着其他断言方法内）启动断言，得在jvm命令里添加上 ' -ea ' 。

## IDEA解决方式

既然知道问题的根源，那么我们只需要跟着步骤走即可。

打开IDEA，主菜单RUN -> Edit configurations -> VM options:添加`-ea`，问题搞定。

## 参考

XiufengWu - [java使用assert断言时不起作用的解决办法](https://blog.csdn.net/xiufengwu/article/details/78108954)
