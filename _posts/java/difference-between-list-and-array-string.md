---
title: Java中数组和List的区别
date: 2018-05-26 14:31:53
tags: ['数组', 'List']
categories: 
 - 开发语言
 - Java
---


# 区别

## 存储对象

- 数组可以是任意Java对象，包括基础数据类型，比如int，long，double等：`int[]`，`long[]`, `double[]`
- List是Java接口，任何实现它的类可以自行实现方法。而且它是泛型集合，泛型一定要是Java类，也就是说`List<T>`中，T不可能是基础数据类型，`List<int>` ，`List<long>` 这样子的用法是错误的

## 容量

- 数组定长，长度不可变
- List非定长，长度可变。建议在使用的时候`指定初始长度`，比如ArrayList，指定初始长度=2的n次方。就算最开始并不知道最终List长度是多少，能给出一个初步估计的长度，对性能提升也是有效的，因为减少中间扩容的次数

## 性能

- 随机访问和迭代，数组比List快

## 维度

- 数组支持多维
- List只是一维，当然你可以在List中插入数组实现多维

## 内存分布

- 数组在JVM内存分布是连续的
- List在JVM内存分布不要求连续

## 相互转换

- 数组转List：使用 Arrays.asList(array) 进行转换
- List转数组：使用 List 自带的 toArray() 方法
