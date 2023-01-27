---
title: clion以及cygwin的安装与配置
date: 2019-03-19 11:07:57
tags: ['clion','cygwin']
categories: 
 - 开发语言
 - C/C++
---

## 背景

需要学习数据结构，而数据结构的书籍又是基于C语言的. C语言基础不咋地, 所以得多动手, 动手又得有工具。平时用IDEA用的比较多，jetbrains这家公司的全家桶的确非常好用，所以就考虑到了Clion.

> 安装完clion, 还需要安装Toolchiains. 搜索半天, 都是推荐安装MinGw, 结果下载了之后只是一个下载工具, 还有一堆其他依赖需要安装. 安装过程也是纠结, 过一会报一个下载失败的错误, 还得手动dismiss，不然他就不动了！上班期间哪有那么多空去点啊！

改策略, 安装cygwin!!!, 一大推文章, 靠谱的没几个!  最后还是折腾成功，特整理安装过程如下:


最后成功的样子:
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190319101645543.png)

## 安装clion
该过程比较简单,  访问[clion官网](https://www.jetbrains.com/clion/download)，点击下载exe(或者其他系统, 和其他格式)，下载完成之后就是一步一步点next, clion的安装过程除了安装路径可以自由更改，其他过程完全可以默认，这里我就不贴图片了（而且我也没有截图！！）. 


## 安装cygwin
进入cygwin的[官网下载页面](https://cygwin.com/install.html), 根据你的电脑的位数自由选择对应的下载版本.  

下载完`setup-x86_64.exe`之后（注意该`steup.exe`文件的位置，后面要用），打开一直默认 - 下一步，直到`【Choose A Download Site】`界面。

需要注意的是，因为默认没有163的镜像，镜像地址需要手动添加 `http://mirrors.163.com/cygwin`，该镜像对大陆用户来说很快。如图：
![Choose A Download Site](https://img-blog.csdnimg.cn/20190319102841184.png)

选择镜像后，进入到`【Select Packages】`页面,  搜索 gcc-core、gcc-g++、make、gdb、binutils，cmake （如果漏掉也没关系，后面会提到），只需要等待下载完成即可, 完成安装. 

## Clion配置cygwin
各种字体，风格等，这里略过，我这里只提一下Toolchians的配置

- 打开clion
- 进入设置 Build, Execution, Deployment -> Toolchians
- 点击添加， Environment处选择Cygwin，然后选择刚才安装的路径
- 搞定

> 假如有某一个或者多个依赖，Clion提示没有安装，请参考下一个步骤的方法完成安装。
> 我的便是提示Debugger没有安装, 提示需要安装gdb! 

## cygwin安装其他exe

这里需要注意，我们需要依赖上面【安装cygwin】步骤下载的`setup-x86_64.exe`文件来安装。

怎么找到对应exe文件的名字呢 ？ 打开163镜像[release目录](http://mirrors.163.com/cygwin/x86_64/release/)，搜索你要的文件， 我便搜索 gdb, 找到的有好几个，那我便知道了对应的名字直接是`gdb`(最开始我输入的是GDB, 有问题)

- 打开cmd面板，或者cygwin也可以
- 进入到上述`setup-x86_64.exe`文件的路径下，我的是`C:\Users\chenjun\Downloads>`
- 输入`setup-x86_64.exe -q -P gdb` 直至完成

看图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190319110331833.png)


## 参考

感谢作者，部分参考文章如下:

[ming_514 -《clion以及cygwin的安装还有clion的环境配置》](https://blog.csdn.net/qq_36819130/article/details/78668249)
