---
title: 【lombok】var - 无忧的局部变量
date: 2019-01-17 00:22:41
updated: 2019-01-17 00:22:41
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
copyright: true
---

## 概述

`var`的工作原理与`val`完全相同，但局部变量不会标记为final。

该类型仍然推断初始化表达式，并且任何重新的赋值都是合法的（因为变量不再是final类型），但不会再查找以确定适当的类型（我个人的理解是: 已推导出最接近的某个类型，然后又重新赋值，但不会再重新推导出另一个合适类型）。

例如:<code>var x = "Hello"; x = Color.RED; </code>不起作用; x的类型将被最先推断为`java.lang.String`，因此，`x = Color.RED`赋值将失败。如果x的类型被推断为`java.lang.Object`，则此段代码将能被编译，但这不是`var`的工作原理。

一般情况下我们申明非final Java类型，总是需要这么写:

```java
//  列表
ArrayList<String> example = new ArrayList<>();
//  map
Map<String, Integer> map = new HashMap<>(12);
//  java对象
JavaBean bean = new JavaBean();
```

但是，有了var， 我们不再需要这么麻烦！  
先引入maven坐标

    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <version>1.18.4</version>
        <scope>provided</scope>
    </dependency>


## var示例

```java 
package com.amos;

import lombok.var;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.stream.Stream;

public class VarExample {

    public void example() {
        //  var ->  List<String>
        var example = new ArrayList<String>();
        example.add("Hello, World!");
        //  var ->  String
        var foo = example.get(0);
        System.out.println(foo.toLowerCase());

        // var ->  Map<Integer, String>
        var map = new HashMap<Integer, String>();
        map.put(0, "zero");
        map.put(5, "five");
        // var ->  Map.Entry<Integer, String>
        for (var entry : map.entrySet()) {
            System.out.printf("%d: %s\n", entry.getKey(), entry.getValue());
        }

        // var ->  Person
        var person = new Person();
        person.setName("amos");
        person.setAge(22);
        System.out.println(person);

        // var ->  Integer[]
        var integers = new Integer[]{
                1 , 2 , 3
        };
        // var ->  Integer
        var num = 2;
        var foundNum = Stream.of(integers).filter(s -> s.equals(num)).findAny().orElse(0);
        System.out.println(foundNum);
    }

    public static class Person {
        private String name;
        private int age;

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getAge() {
            return age;
        }

        public void setAge(int age) {
            this.age = age;
        }

        @Override
        public String toString() {
            return "Person{" +
                    "name='" + name + '\'' +
                    ", age=" + age +
                    '}';
        }
    }
}
```

## 不可用场景

**不可用** 于java类的属性(field)

```java
public class example{
    var abc  = "hello world";
}
```

**不可用** 于指定方法的入参类型

```java
public class example{
    public void fun(var xyz){
        // bala bala
    }
}
```
