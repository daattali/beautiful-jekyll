---
title: 【lombok】val - final型局部变量
date: 2019-01-17 00:23:41
updated: 2019-01-17 00:23:41
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---


## 概述

您可以使用`val`作为局部变量声明的类型，而不用实际编写该类型。执行此操作时，将从初始化表达式推断出类型。该本地变量也将成为`final`型变量。此功能仅适用于局部变量和foreach循环，而不适用于类属性(field)。初始化表达式是必需的。

`val`实际上是一种"类型"，在`lombok`包中作为一个真正的类存在。您必须导入它才能使val工作（或使用`lombok.val`作为类型）。在本地变量声明中存在这种类型会触发添加`final`关键字以及复制初始化表达式的类型，该类型会覆盖"伪"`val`类型。

一般情况下我们申明final Java类型，总是需要这么写:

```java
//  列表
ArrayList<String> example = new ArrayList<>();
//  map
Map<String, Integer> map = new HashMap<>(12);
//  Java对象
JavaBean bean = new JavaBean();
```

又或者说，我们需要将其申明为不可变对象，则又需要加上 `final` . 但是，有了val， 我们不再需要这么麻烦！  

先引入maven坐标

    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <version>1.18.4</version>
        <scope>provided</scope>
    </dependency>

## val示例

```java
package com.amos;

import lombok.val;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.stream.Stream;

public class ValExample {

    public void example() {
        //  val -> final List<String>
        val example = new ArrayList<String>();
        example.add("Hello, World!");
        //  val -> final String
        val foo = example.get(0);
        System.out.println(foo.toLowerCase());

        // val -> final Map<Integer, String>
        val map = new HashMap<Integer, String>();
        map.put(0, "zero");
        map.put(5, "five");
        // val -> final Map.Entry<Integer, String>
        for (val entry : map.entrySet()) {
            System.out.printf("%d: %s\n", entry.getKey(), entry.getValue());
        }

        // val -> final Person
        val person = new Person();
        person.setName("amos");
        person.setAge(22);
        System.out.println(person);

        // val -> final String[]
        val strings = new String[]{
                "中国", "唐伯虎", "美人鱼"
        };
        // val -> final String
        val str = "美人鱼";

        val foundStr = Stream.of(strings).filter(s -> s.equals(str)).findAny().orElse("null");
        System.out.println(foundStr);
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
    val abc = "hello world";
}
```

**不可用** 于指定方法的入参类型

```java
public class example{
    public void fun(val xyz){
        //  bala bala
    }
}
```
