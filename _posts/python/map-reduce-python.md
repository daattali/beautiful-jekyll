---
title: Python函数式编程—map()、reduce()
date: 2017-08-23 15:07:26
updated: 2017-08-23 15:07:26
tags: ['python','函数式编程','reduce','map','函数']
categories: 
 - 开发语言
 - Python
---

原文出自：[Python函数式编程——map()、reduce()](http://www.pythoner.com/46.html)

# map()

格式：map( func, seq1[, seq2...] )

Python函数式编程中的map()函数是将func作用于seq中的每一个元素，并用一个列表给出返回值。如果func为None，作用同zip()。

当seq只有一个时，将func函数作用于这个seq的每个元素上，得到一个新的seq。下图说明了只有一个seq的时候map()函数是如何工作的（本文图片来源：《Core Python Programming (2nd edition)》）。

![这里写图片描述](http://img.blog.csdn.net/20170823145742999)

可以看出，seq中的每个元素都经过了func函数的作用，得到了func(seq[n])组成的列表。

下面举一个例子进行说明。假设我们想要得到一个列表中数字%3的余数，那么可以写成下面的代码。

```python
# 使用map
print map( lambda x: x%3, range(6) )  # [0, 1, 2, 0, 1, 2]
 
# 使用列表解析
print [x%3 for x in range(6)]  # [0, 1, 2, 0, 1, 2]
```
这里又和上次的filter()一样，使用了列表解析的方法代替map执行。那么，什么时候是列表解析无法代替map的呢？

原来，当seq多于一个时，map可以并行地对每个seq执行如下图所示的过程：
![这里写图片描述](http://img.blog.csdn.net/20170823145916710)

也就是说每个seq的同一位置的元素在执行过一个多元的func函数之后，得到一个返回值，这些返回值放在一个结果列表中。

下面的例子是求两个列表对应元素的积，可以想象，这是一种可能会经常出现的状况，而如果不是用map的话，就要使用一个for循环，依次对每个位置执行该函数。

```python
# Python函数式编程之map使用（多个seq）
print map( lambda x, y: x * y, [1, 2, 3], [4, 5, 6] )  # [4, 10, 18]
```

上面是返回值是一个值的情况，实际上也可以是一个元组。下面的代码不止实现了乘法，也实现了加法，并把积与和放在一个元组中。
```python
# Python函数式编程之map使用（多个seq）
print map( lambda x, y: ( x * y, x + y), [1, 2, 3], [4, 5, 6] )  # [(4, 5), (10, 7), (18, 9)]
```

还有就是上面说的func是None的情况，它的目的是将多个列表相同位置的元素归并到一个元组，在现在已经有了专用的函数zip()了。

```python
# Python函数式编程之map使用（func为None）
print map( None, [1, 2, 3], [4, 5, 6] )  # [(1, 4), (2, 5), (3, 6)]
 
print zip( [1, 2, 3], [4, 5, 6] )  # [(1, 4), (2, 5), (3, 6)]
```

需要注意的是，不同长度的多个seq是无法执行map函数的，会出现类型错误。

# reduce()

格式：reduce( func, seq[, init] )

reduce函数即为化简，它是这样一个过程：每次迭代，将上一次的迭代结果（第一次时为init的元素，如没有init则为seq的第一个元素）与下一个元素一同执行一个二元的func函数。在reduce函数中，init是可选的，如果使用，则作为第一次迭代的第一个元素使用。

简单来说，可以用这样一个形象化的式子来说明：

```python
reduce( func, [1, 2,3] ) = func( func(1, 2), 3)
```

下面是reduce函数的工作过程图：
![reduce工作过程图](http://img.blog.csdn.net/20170823150441130)

举个例子来说，阶乘是一个常见的数学方法，Python中并没有给出一个阶乘的内建函数，我们可以使用reduce实现一个阶乘的代码。
```python
# Python函数式编程之reduce使用
n = 5
print reduce(lambda x, y: x * y, range(1, n + 1))  # 120
```

那么，如果我们希望得到2倍阶乘的值呢？这就可以用到init这个可选参数了。

```python
# Python函数式编程之reduce使用
m = 2
n = 5
print reduce( lambda x, y: x * y, range( 1, n + 1 ), m )  # 240
```

# 参考文献
[1] Lammel R. Google’s MapReduce programming model – Revisited[J]. Science of Computer Programming, 2008,70(1):208-237.
[2] Hadoop[EB/OL]. http://hadoop.apache.org.