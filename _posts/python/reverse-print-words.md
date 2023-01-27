---
title: Python倒序打印一句英语
date: 2016-04-09 13:45:47
updated: 2016-04-09 13:45:47
tags: ['倒序']
categories: 
 - 开发语言
 - Python
---


看到一个面试题 要求是倒序打印一句英语
例如'this is a book' 转成 'book a is this' 要考虑空间

写法①
```python
str = 'this is a book'
list = list(str)

a = []
b = ''

for i in range(0,len(list)):

    a.append(list[i])
    if list[i] == ' ':
        b =  ' ' + ''.join(a[0:-1]) + b
        a=[]

    if i == (len(list)-1) :
        b =  ''.join(a) +b
print b
```

写法②

```python
def descStr():

    str = 'this is a book'
    str = str.split(' ') #['this', 'is', 'a', 'book']
    list = []

    n = -1
    for i in str:
        list.insert(n,i)
        n=n-1

    print ' '.join(list)

descStr()
```


写法③

```python
# coding:utf-8
string = "what's your name"
s1 = string.split()
s2 = s1[::-1]
```
