---
title: Java - hashCode与equals之间的联系
date: 2020-10-03 11:30:20
updated: 2020-10-03 11:30:20
tags: ['hashCode','equals']
categories:
 - 开发语言
 - Java
---

# 问题

1. Q1 - hashCode()相同，则equals()也一定为true?
2. Q2 - <font color=red> equals()为true，hashCode()也不一定相同 ？ </font>
3. Q3 - hashCode()返回的是对象的内存地址吗？

第三个问题是从csdn上面偶尔看到，看得人挺懵的!!!



下面细细道来：

## equals()

equals方法在非null对象引用实现对等关系：

{% blockquote Java8 API https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#method.detail java.lang.Object#equals %}

- It is reflexive: for any non-null reference value x, x.equals(x) should return true.
- It is symmetric: for any non-null reference values x and y, x.equals(y) should return true if and only if y.equals(x) returns true.
- It is transitive: for any non-null reference values x, y, and z, if x.equals(y) returns true and y.equals(z) returns true, then x.equals(z) should return true.
- It is consistent: for any non-null reference values x and y, multiple invocations of x.equals(y) consistently return true or consistently return false, provided no information used in equals comparisons on the objects is modified.

For any non-null reference value x, x.equals(null) should return false.

The equals method for class Object implements the most discriminating possible equivalence relation on objects; that is, for any non-null reference values x and y, this method returns true if and only if x and y refer to the same object (x == y has the value true).

Note that it is generally necessary to override the hashCode method whenever this method is overridden, so as to maintain the general contract for the hashCode method, which states that equal objects must have equal hash codes.

{% endblockquote %}
<br>
我们可以得出以下结论：

1. 性质：（以下对象均指非空引用）
  - 反身性： x.equals(x) 应该返回true
  - 对称性：当且仅当 y.equals(x) 返回true时， x.equals(y) 才返回true
  - 可传递性：如果 x.equals(y) 返回true，而 y.equals(z) 返回true，则 x.equals(z) 应该返回true
  - 一致性：如果未修改对象equals方法中比较使用的信息，则多次调用x.equals(y)始终返回true或始终返回false
2. 对于任何非空引用 x，x.equals(null) 应该返回false
3. 有必要在重写equals方法时重写hashCode方法

## hashCode()

hashCode返回的是对象哈希码值，是一个integer数值。只有在使用hash表的时候，hashCode才发挥它真正的作用。

Object类里hashCode方法的契约：

{% blockquote Java8 API https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#method.detail java.lang.Object#hashCode %}

- Whenever it is invoked on the same object more than once during an execution of a Java application, the hashCode method must consistently return the same integer, provided no information used in equals comparisons on the object is modified. This integer need not remain consistent from one execution of an application to another execution of the same application.
- If two objects are equal according to the equals(Object) method, then calling the hashCode method on each of the two objects must produce the same integer result.
- It is not required that if two objects are unequal according to the equals(java.lang.Object) method, then calling the hashCode method on each of the two objects must produce distinct integer results. However, the programmer should be aware that producing distinct integer results for unequal objects may improve the performance of hash tables.

{% endblockquote %}
<br>
我们可以得出以下结论：

- hashCode生成的数值是根据对象需要比较的字段计算得来，假如说某类有x,y,z三个filed（字段），若z可以不被计入比较，则是否相等可以只判断实例之间的x,y是否一致即可
- 同一个对象，在JVM运行期间，它的hashCode方法必定返回相同的整数
- 同一个对象，在JVM生命周期①和生命周期②里，①和②的hashCode方法返回不用保持一致
- 若 ` a.equals(b) ` = true，则 ` a.hashCode() ` 与 ` b.hashCode() ` 两者返回的整数一定相等
- 若 ` a.equals(b) ` = false，则 ` a.hashCode() ` 与 ` b.hashCode() ` 两者返回的整数，不需要不同。也就是说：<font color=red>若equals为false，hashCode可以相等</font>
- `优秀`的程序员应该做到：为不相等的对象生成不同的整数结果，因为这可能会提高哈希表的性能

红色字体部分便可以回答最初提到问题Q1：答案是`否定`的。

根据第四点：我们可以得出问题Q2的答案： 答案是`否定`的。也就是说：equals为true，hashCode一定相等。

针对Q2，若是你<font color=red>违反Object的契约</font>:

- 覆写equals方法，一直返回true;
- 或者为同一个对象每一次调用返回不同的hashCode
 
那么Q2的答案就是`肯定`的，但是得出这个答案的前提是：违反Object契约。

针对Q3： hashCode是否是内存地址？ 
{% blockquote Java8 API https://docs.oracle.com/javase/8/docs/api/java/lang/Object.html#method.detail java.lang.Object#hashCode %}

As much as is reasonably practical, the hashCode method defined by class Object does return distinct integers for distinct objects. (This is typically implemented by converting the internal address of the object into an integer, but this implementation technique is not required by the Java™ programming language.)

{% endblockquote %}
<br>
上文提到：通常是通过将对象的内部地址转换为整数来实现，但是Java编程语言不需要此实现技术。

- Java不需要该实现技术，所以肯定hashCode不是内存地址
- 再次因为：`通常`是通过内存地址转换整数，言外之意是其他语言可能采用的是将内存地址转为整数，所以对于Java而言hashCode也不是内存地址，而对于其他语言来说：也并非内存地址，而是通过内存地址转换而成的整数

## 总结

1. Q1 - hashCode()相同，则equals()也一定为true? A: 不一定
2. Q2 - <font color=red>equals()为true，hashCode()也不一定相同 ？ </font> A: 一定相同
3. Q3 - hashCode()返回的是对象的内存地址吗？ A: 不是
