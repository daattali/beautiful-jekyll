---
title: python解惑之：整数比较
date: 2017-07-11 20:18:04
updated: 2017-07-11 20:18:04
tags: ['python','整数比较']
categories: 
 - 开发语言
 - Python
---

**申明转载出处：**
微信公众号：[Python之禅](http://mp.weixin.qq.com/s/MLj8Ol7QYKv4DpQ1yPJJOg)

在 Python 中一切都是对象，毫无例外整数也是对象，对象之间比较是否相等可以用 ==，也可以用 is。 ==和 is操作的区别是：

>is比较的是两个对象的id值是否相等，也就是比较俩对象是否为同一个实例对象，是否指向同一个内存地址。

>==比较的是两个对象的内容是否相等，默认会调用对象的 __eq__()方法。

清楚 is和 ==的区别之后，对此也许你有可能会遇到下面的这些困惑，于是就有了这样一篇文章，试图把Python中一些隐晦的东西趴出来，希望对你有一定的帮助。

我们先来看两段代码：

片段一：

```
>>> a = 256
>>> b = 256
>>> a == b
True
>>>
```


片段二：

```
>>> a = 256
>>> b = 256
>>> a is b
True
>>>
```

在交互式命令行执行上面两段代码，代码片段一中的 a==b返回 True很好理解，因为两个对象的值都是256，对于片段二， a is b也返回True，这说明a和b是指向同一个对象的，可以检查一下他们的id值是否相等：

```
>>> id(a)
8213296
>>> id(b)
8213296
>>> 
```

结果证明他俩的确是同一个对象，指向的是同一个内存地址。那是不是所有的整数对象只要两个对象的值（内容）相等，它们就是同一个实例对象呢？换句话说，对于整数对象只要 ==返回 True， is操作也会返回 True吗？带着这个问题来看下面这两段代码：

片段一：

```
>>> a = 257
>>> b = 257
>>> a == b
True
>>>
```

片段二：

```
>>> a = 257
>>> b = 257
>>> a is b
False
>>>
```

对于257， a is b返回的竟然是False，结果可能在你的意料之中，也有可能出乎你的意料，但不管怎么，我们还是要刨根问底，找出问题的真相。

## 解惑一

出于对性能的考虑，Python内部做了很多的优化工作，对于整数对象，Python把一些频繁使用的整数对象缓存起来，保存到一个叫 small_ints的链表中，在Python的整个生命周期内，任何需要引用这些整数对象的地方，都不再重新创建新的对象，而是直接引用缓存中的对象。Python把这些可能频繁使用的整数对象规定在范围[-5, 256]之间的小对象放在 small_ints中，但凡是需要用些小整数时，就从这里面取，不再去临时创建新的对象。因为257不再小整数范围内，因此尽管a和b的值是一样，但是他们在Python内部却是以两个独立的对象存在的，各自为政，互不干涉。

弄明白第一个问题后，我们继续在Python交互式命令行中写一个函数，再来看下面这段代码：

片段一：

```
>>> c = 257
>>> def foo():
...     a = 257
...     b = 257
...     print a is b
...     print a is c
... 
>>> foo()
True
False
```

呃，什么情况，是的，你没看错，片段一中的这段代码 a、b 值都是257的情况下，出现了 a is b返回 True，而 a is c 返回的 False，a、b、c的值都为257，为什么会出现不同的结果呢？这对于刚刚好不容易建立起来的认知就被彻底否决了吗，那这段代码中究竟发生了什么？难道解惑一中的结论是错误的吗？

## 解惑二

  A Python program is constructed from code blocks. A block is a piece of Python program text that is executed as a unit. The following are blocks: a module, a function body, and a class definition. Each command typed interactively is a block. A script file (a file given as standard input to the interpreter or specified as a command line argument to the interpreter) is a code block. A script command (a command specified on the interpreter command line with the ‘-c‘ option) is a code block. structure-of-a-program

为了弄清楚这个问题，我们有必要先理解程序代码块的概念。
Python程序由代码块构成，代码块作为程序的一个最小基本单位来执行。一个模块文件、一个函数体、一个类、交互式命令中的单行代码都叫做一个代码块。在上面这段代码中，由两个代码块构成， c = 257作为一个代码块，函数 foo作为另外一个代码块。Python内部为了将性能进一步的提高，凡是在一个代码块中创建的整数对象，如果存在一个值与其相同的对象于该代码块中了，那么就直接引用，否则创建一个新的对象出来。Python出于对性能的考虑，但凡是不可变对象，在同一个代码块中的对象，只有是值相同的对象，就不会重复创建，而是直接引用已经存在的对象。因此，不仅是整数对象，还有字符串对象也遵循同样的原则。所以 a is b就理所当然的返回 True了，而 c和 a不在同一个代码块中，因此在Python内部创建了两个值都是257的对象。为了验证刚刚的结论，我们可以借用 dis模块从字节码的角度来看看这段代码。

```
>>> import dis
>>> dis.dis(foo)
  2           0 LOAD_CONST               1 (257)
              3 STORE_FAST               0 (a)
  3           6 LOAD_CONST               1 (257)
              9 STORE_FAST               1 (b)
  4          12 LOAD_FAST                0 (a)
             15 LOAD_FAST                1 (b)
             18 COMPARE_OP               8 (is)
             21 PRINT_ITEM          
             22 PRINT_NEWLINE       
  5          23 LOAD_FAST                0 (a)
             26 LOAD_GLOBAL              0 (c)
             29 COMPARE_OP               8 (is)
             32 PRINT_ITEM          
             33 PRINT_NEWLINE       
             34 LOAD_CONST               0 (None)
             37 RETURN_VALUE
```

可以看出两个257都是从常量池的同一个位置 co_consts[1]获取的。

## 总结

一番长篇大论之后，得出两点结论：

 1. 小整数对象[-5,256]是全局解释器范围内被重复使用，永远不会被GC回收；
 2. 同一个代码块中的不可变对象，只要值是相等的就不会重复创建新的对象。

似乎这些知识点对日常的工作一点忙也帮不上，因为你根本不会用 is来比较两个整数对象的值是否相等。那为什么还要拿出来讨论呢？嗯，程序员学知识，不应该浅尝辄止，要充分发挥死磕到底的精神。