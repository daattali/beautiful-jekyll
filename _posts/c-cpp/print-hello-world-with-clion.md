---
title: Clion运行hello world
date: 2019-03-19 18:03:45
tags: ['clion','c','c++','helloworld']
categories: 
 - 开发语言
 - C/C++
---

# 前提

你已经配置好clion的Toolchians环境

>>如果配置Toolchains环境有任何问题， 还请查看我的另外一篇文章《[clion以及cygwin的安装与配置](https://blog.csdn.net/amoscn/article/details/88656010)》。


# 创建项目

- new project -> 选择C executable
- 填写项目存放路径
- OK

点击运行 即可！

# 注意事项

1. 创建项目的时候，一定要选择 `executable` 而不要选择`library`
2. 如果万一选择了`library`， 将`.c`文件内的函数名改为`main` . 


> 很简单是吧 ? 可是，不熟悉的人也会折腾老半天，比如说我！！！