---
title: python-Error Message-'float' object cannot be interpreted as an integer
date: 2017-10-23 17:32:18
updated: 2017-10-23 17:32:18
tags: ['python', '除法']
categories: 
 - 开发语言
 - Python
---

# 背景

因为需要通过模拟回调，所以自己写了一段脚本来获取数据库内的数据，然后通知给应用。代码在py2运行得好好的，结果copy在py3上面就报错。

出问题的代码如下：

```python
batch = 200
for x in range(len(order_numbers) / batch + 1):
	# do something
```

`order_numbers` 是订单列表。脚本主要的功能是分批次回调，一个批次200. 报错信息的意思是：float类型不能解释为int类型 。 奇怪得很，py2都好好的，到py3就不行 。


# 问题解决

为什么range内的数据是float呢 ？

怀疑`/`在py2跟py3之间有差别，搜了一下，的确是有差别。请看下面的用法：

python2
> C:\Users\chenjun>python
Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 27 2016, 15:24:40) [MSC v.1500 64 bit (
AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
\>>> 0/200 + 1
1
\>>> 1/200 + 1
1

python3
> C:\Users\chenjun>python3
Python 3.6.1 (v3.6.1:69c0db5, Mar 21 2017, 17:54:52) [MSC v.1900 32 bit (Intel)]
 on win32
Type "help", "copyright", "credits" or "license" for more information.
\>>> 0/200 + 1
1.0
\>>> 1/200 + 1
1.005

在python2，`/`只留下了整数部分，去掉了小数，是int型。
在python3里，`/`的结果是真正意义上的除法，结果是float型。所以便出现了Error Message: 'float' object cannot be interpreted as an integer。 

---

多谢 `@冲动的MJ` 的回复： python3中用双`//`就可以了
