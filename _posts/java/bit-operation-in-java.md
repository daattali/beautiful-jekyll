---
title: Java位运算^,^=,|,|=,&,&=简述
date: 2019-01-02 17:51:57
tags: ['位运算']
categories: 
 - 开发语言
 - Java
---


今天突然看到`java`的类库`java.util.regex.Pattern` 里，第1344行内有这么一句

```java
flags |= UNICODE_CASE
```

比较懵，不知道`|=`是什么意思。

# 解惑
## | 与 |=

>| 运算  0|1=1, 1|0=1, 0|0=0, 1|1=1
a|=b 即是将 a|b 的值重新赋值给 a

```java
int a = 0b0101;
int b = 0b1100;
a |= b;
System.out.println(a);
System.out.println(0b1101);
```

a最终的结果便是 `0b1101`，**至于怎么得到的，可以看描述的内容，自己算一遍，加深印象（下面也是）。**

## ^ 与 ^|

>^ 运算  0^1=1, 1^0=1, 0^0=0, 1^1=0
a^=b 即是将 a^b 的值重新赋值给 a

```java
  a = 0b0101;
  b = 0b1100;
  a ^= b;
  System.out.println(a);
  System.out.println(0b1001);
```
a的结果=`0b1001`

## & 与 &|

>& 运算  0&1=0, 1&0=0, 0&0=0, 1&1=1
a&=b 即是将 a&b 的值重新赋值给 a

```java
 a = 0b0101;
 b = 0b1100;
 a &= b;
 System.out.println(a);
 System.out.println(0b0100);
```

a的结果=`0b0100`

## << , >> 与 >>>

### <<运算

><< 运算 位运算 左移xx位
a<<b 将a的二进制左移b位，右边空位补0
a<<=b  即 a = a<<b , a = a * Math.pow(2, b)

a << b 实际上是将a的二进制位左移b位，空位补0。怎么算呢 ？ 简单想一下，假如说a是一个十进制数，左移2位，是不是将a \* （10的二次方），左移3位是不是将a \* （10的三次方） ?  
那么放在二进制数a上，a=`0b11000111` , 左移b位，b= `3` , 于是`0b11000111`左移3位后 = `0b11000111000` 

正数的情况:

```java
 int a = 199;
 int b = 3;
 System.out.println(Integer.toBinaryString(a));
 System.out.println(Integer.toBinaryString(a<<b));
```

>11000111
11000111000

 负数的情况

```java
 int a = -199;
 int b = 3;
 System.out.println(Integer.toBinaryString(a));
 System.out.println(Integer.toBinaryString(a<<b));
```

>11111111111111111111111100111001
11111111111111111111100111001000

### >>运算

>\>> 运算 位运算 右移xx位
a>>b 将a的二进制右移b位，即a的二进制减位。若a是负数，则左边空位补1，若a是正数，则左边空位补0

负数的情况:

```java
 int a = -199;
 int b = 3;
 System.out.println(Integer.toBinaryString(a));
 System.out.println(Integer.toBinaryString(a>>b));
```
>11111111111111111111111100111001
11111111111111111111111111100111

正数的情况:

```java
int a = 199;
int b = 3;
System.out.println(Integer.toBinaryString(a));
System.out.println(Integer.toBinaryString(a>>b));
```

>11000111
11000

### >>>运算

>\>>> 运算 位运算 无符号右移xx位
a>>>b 将a的二进制右移b位，即a的二进制减位。不管a是正数还是负数，左边空位一律补0

无符号右移运算，看上一小节`>>`是需要区分正数负数的，而`>>>`是不需要分正数和负数的。也就是说不管被位运算的数是正数还是负数，都是减位操作，左边空位一律补0。

正数的情况:

```java
   int a = 199;
   int b = 3;
   System.out.println(Integer.toBinaryString(a));
   System.out.println(Integer.toBinaryString(a>>>b));
```

>11000111
11000

负数的情况:

```java
   int a = -199;
   int b = 3;
   System.out.println(Integer.toBinaryString(a));
   System.out.println(Integer.toBinaryString(a>>>b));
```

>11111111111111111111111100111001
11111111111111111111111100111
