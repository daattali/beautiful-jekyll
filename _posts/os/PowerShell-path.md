---
title: 【PowerShell】命令行输出和添加系统环境变量
date: 2020-09-17 22:04:00
updated: 2020-09-17 22:04:00
tags: ['shell','powershell','windows10']
categories: 
 - OS
 - Windows
---

## 查看某系统变量

Q：如何使用Windows PowerShell查看我的环境变量Path，其中存在哪些文件夹以及它们显示的顺序？

A：使用  $ env  并获取Path变量的值  。默认情况下，它显示为连续的字符串，可能有点难以阅读。命令如下：
>$ env：path


但是，如果使用  –split  运算符在分号处断开字符串，则可读性更高：

>$ env：path -split“;”

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200917220352686.png)
其他
比如：查看系统
>$ env:os

比如：系统几核CPU
>$ env:NUMBER_OF_PROCESSORS

`注意`：查看的这些环境变量，一定是在环境变量里面存在的，又或者你本人添加过的。

## 修改环境变量

首先理解一个事情：在Windows上，可以在三个范围内定义环境变量：

 1. 系统级别（Machine）
 2. 用户级别（User）
 3. 会话级别（Process），**也就是关掉powershell就失效**， 此变量列表是从父进程继承的，并且是根据Machine和User范围中的变量构造的。

### 用户&系统&会话级别
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200917224006450.png)
图示中：·`用户变量`对应用户级别作用域，`系统变量`对应系统级别作用域。

在原有的环境变量基础上新增，并且指定作用域（用户 or 系统 or 会话），一条命令搞定：
>$ addPath='c:\add\you\path\here'; $target='User' ; $path = [Environment]::GetEnvironmentVariable('Path', $target); $newPath = $path + ';' + $addPath; [Environment]::SetEnvironmentVariable("Path", $newPath, $target)

注意：

 1. `$addPath` 等号后面接你要加的路径
 2. `$target` 等号后面接作用域，`Machine`（系统级别） / `User`（用户级别） / `Process`（会话级别） 三选一，前两个修改后会及时生效，且关闭powershell会话任然有效。
 3. 其他地方不需要修改，直接执行即可

### 会话级别修改-方法2
添加新的环境变量
>$ env:amostest="amos for test desc"

在已有的环境变量里添加
>$ env:path+=";c:\your_path"

## 参考
[About Environment Variables](https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_environment_variables?view=powershell-7)
[EnvironmentVariableTarget Enum](https://docs.microsoft.com/en-us/dotnet/api/system.environmentvariabletarget?view=netcore-3.1)