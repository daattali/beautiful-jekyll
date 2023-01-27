---
title: Python静态方法（staticmethod）和类方法（classmethod）区别
date: 2017-08-10 23:07:59
updated: 2017-08-10 23:07:59
tags: ['python','静态方法','类方法','区别']
categories: 
 - 开发语言
 - Python
---

因为对方法和函数两者概念有些混淆，所以研究了一下，总结文章点[Python函数（function）与方法（method）区别](https://www.nothinghere.cn/python/different-between-function-and-methond/)。后来顺带把静态方法和类方法也摸索了一下，稍微有了一些感觉。

直接上代码:
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

print "-"*80

apple1 = Apple()
print apple1.fun1
print apple1.fun2
print apple1.fun3
```

运行结果:

```
<unbound method Apple.fun1>
<function fun2 at 0x00000000022FC4A8>
<bound method classobj.fun3 of <class __main__.Apple at 0x0000000001E7C768>>
--------------------------------------------------------------------------------
<bound method Apple.fun1 of <__main__.Apple instance at 0x00000000022FAE08>>
<function fun2 at 0x00000000022FC4A8>
<bound method classobj.fun3 of <class __main__.Apple at 0x0000000001E7C768>>
--------------------------------------------------------------------------------
<bound method Apple.fun1 of <__main__.Apple instance at 0x00000000022FAE48>>
<function fun2 at 0x00000000022FC4A8>
<bound method classobj.fun3 of <class __main__.Apple at 0x0000000001E7C768>>
```

1. 普通方法传入的第一个参数必须是self（当然也可以不用self，官方要求尽量用self），self是指实例对象本身；
2. 静态方法无需传参；
3. 类方法传入的第一个参数必须是class，是指类本身。

---
对比结果1，5，9行
fun1通过class调用时，它是未绑定的方法，而实例化apple和apple1之后，它属于绑定的方法，且实例化后的apple和apple1内存地址不同，因为它们属于不同的实例对象。

---
对比结果2，6，10行
静态方法fun2通过class调用或者通过实例化后的对象调用，是没有任何区别的，全部都是指向同一块内存地址。可以简单的理解成静态方法与类或者实例没有任何关系，一旦调用后，它的内存地址即确定。

---
对比结果3，7，11行
类方法fun3通过class调用或者通过实例化后的对象调用，是没有任何区别的，全部都是指向同一块内存地址。为什么？因为实例化对象apple和apple1调用类方法fun3传入的第一个参数是类本身Apple，也就是说apple.fun3 = apple1.fun3 = Apple.fun3。

---

**区别总结：**

1. 静态方法装饰器下定义的方法属于函数（function）；
2. 类方法装饰器下定义的方法属于方法（method）；
3. 静态方法无需传入任何参数；
4. 类方法传入的第一个参数必须是class本身cls；
5. 静态方法与类方法一旦被调用，内存地址即确定。通过类调用和通过实例化对象调用的结果完全一样。