---
title: Python函数（function）与方法（method）区别
date: 2017-08-10 18:07:46
updated: 2017-08-10 18:07:46
tags: ['python', '函数', '方法']
categories: 
 - 开发语言
 - Python
---

一直以来都以为函数和方法是一个东西，平时区分也不是很详细，后来一搜索发现自己平时叫法是错的。

先看一段代码

```python
def fun():
    pass
print fun
```

结果如下：

<function fun at 0x00000000022BC3C8>

可以看出:
单独定义的一个function是function，它是一个函数。我个人的理解是，在class外部定义的可执行函数，都是函数。

再看另外一段代码
```python
#  coding:utf-8

class Apple:

    def fun1(self):
        return 'normal'

    @staticmethod
    def fun2():

        return 'staticmethod'

    @classmethod
    def fun3(cls):

        return 'classmethod'

print Apple.fun1
print Apple.fun2
print Apple.fun3

print "-"*80

apple = Apple()
print apple.fun1
print apple.fun2
print apple.fun3
```

结果如下:

* * *
&lt;unbound method Apple.fun1>  
&lt;function fun2 at 0x00000000021DC4A8>  
&lt;bound method classobj.fun3 of &lt;class __main__.Apple at 0x0000000001D8C768>>  
\-------------------------------------------------------------------------------------  
&lt;bound method Apple.fun1 of &lt;__main__.Apple instance at 0x00000000021DAE08>>  
&lt;function fun2 at 0x00000000021DC4A8>  
&lt;bound method classobj.fun3 of &lt;class __main__.Apple at 0x0000000001D8C768>>  
* * *

可以看出:

* 在class内定义的普通方法，如fun1，因为它是要面向将来实例化对象的，其实它就是一个实例方法。它属于method，是一个方法。
* 在class内定义的静态方法，如fun2，它与任何对象都没有联系，等同于是在class外定义的function，它属于函数。
* 在class内定义的类方法，如fun3，它第一个参数必须是cls，它与class本身是绑定关系，它属于方法。

简单总结：

1. 与类和实例无绑定关系的function都属于函数（function）；
2. 与类和实例有绑定关系的function都属于方法（method）。

