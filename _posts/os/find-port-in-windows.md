---
title: windows查看端口使用进程
date: 2017-12-12 13:11:41
tags: ['windows','findstr','taskkill','netstat']
categories: 
 - OS
 - Windows
---

# 查看端口进程

比如现在端口1099被占用，我想知道是什么进程占用

>λ netstat -ano | findstr "1099"

  TCP    0.0.0.0:1099           0.0.0.0:0              LISTENING       6900
  TCP    [::]:1099              [::]:0                 LISTENING       6900
  TCP    [::1]:1099             [::1]:50272            TIME_WAIT       0
  TCP    [::1]:1099             [::1]:50273            TIME_WAIT       0
  TCP    [::1]:1099             [::1]:50274            TIME_WAIT       0
  TCP    [::1]:1099             [::1]:50275            TIME_WAIT       0
  TCP    [::1]:1099             [::1]:50279            TIME_WAIT       0

现在知道pid是6900了，再看6900是什么进程

>λ tasklist |findstr "6900"
java.exe                      6900 Console                    1    528,236 K

# 杀掉进程

>λ taskkill /PID 6900 /F
想了解更多taskkill命令可以是用taskkill /?
