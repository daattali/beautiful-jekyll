---
title: Windows系统配置python2和python3共存
date: 2018-08-27 16:53:33
tags: ['python环境变量','py2','py3','python23共存']
categories: 
 - 开发语言
 - Python
---

# 下载python2 python3

下载地址自己google，下载后建议安装到c盘根目录。

也就是说，在c盘根目录下，同时有c:\Python27 和 c:\Python36

# 设置环境变量

打开cmd面板输入命令:

## 设置py2

>$ C:\Users\admin> path=%path%;c:\Python27

## 设置py3
>$ C:\Users\admin> path=%path%;c:\Python36

# 修改python文件名

- 修改py2文件内的文件名，以达到输入python2即可进入python2环境
- 将Python27文件夹内的python.exe改为python2.exe
- 将Python27文件夹内的pythonw.exe改为pythonw2.exe

![这里写图片描述](https://img-blog.csdn.net/2018082716522641)

- 修改py3文件内的文件名，以达到输入python3 或者 python即可进入python3环境
- 将Python36文件夹内的python.exe复制再粘贴，粘贴到同目录下，改名为python3.exe
- 将Python36文件夹内的pythonw.exe复制再粘贴，粘贴到同目录下，改名为pythonw3.exe

![这里写图片描述](https://img-blog.csdn.net/20180827165241730)