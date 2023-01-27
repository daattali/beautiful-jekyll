---
title: microsoft visual c++ 14.0 is required问题解决办法
date: 2017-10-12 15:41:44
tags: ['pip出错','c++14']
categories: 
 - 开发语言
 - Python
---


# 背景

安装pymssql， 执行命令pip install pymssql时出错：

>error: Microsoft Visual C++ 14.0 is required. Get it with "Microsoft Visual C++ Build Tools": http://landinghub.visualstudio.com/visual-cpp-build-tools

# 解决

## 方法1

### step1.手动下载whl文件

点[这里](http://www.lfd.uci.edu/~gohlke/pythonlibs/)搜索您要下载的库。

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTgwMTI2MTk1MDE0ODQy)

{: .box-info}
下载哪一个呢?

- cp后接python版本， 请与你的python版本对应
- win32，标识32位架构，适用于32位系统
- 后接`_amd64`指64位架构，适用于64位系统



### step2. 执行pip install xxx

>$ pip3 install C:\Users\chenjun\Desktop\pymssql-2.1.3-cp36-cp36m-win32.whl

## 方法2

因为提示需要c++ 14.0，下载14.0.

 1. 点击[此处](https://pan.baidu.com/s/1R-u3AJtA4nSGQi83cNAiug)进入下载（提取码：07oe）。
 2. 解压安装（可能比较花时间）
 3. 安装完毕再次执行pip install xx
