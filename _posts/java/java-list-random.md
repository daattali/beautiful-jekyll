---
title: Java List随机取值
date: 2018-04-24 16:43:00
tags: ['java','list','随机']
categories: 
 - 开发语言
 - Java
---

## 在0~List长度中随机取

```java
public static void main(String[] args) {

    List<String> list = Arrays.asList("a","b","c");
    // 随机从0和List长度中获取索引
    int index = (int) (Math.random()* list.size());
    System.out.println(list.get(index));
}
```

## Collections打乱顺序

```java
public static void main(String[] args) {

    List<String> list = Arrays.asList("a","b","c");
    // shuffle 打乱顺序 
    Collections.shuffle(list);
    System.out.println(list.get(0));
}
```