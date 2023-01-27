---
title: 执行sh脚本提示“[[ not found”解决方案，bash和sh的区别
date: 2020-05-11 20:10:00
updated: 2020-05-11 20:10:00
tags: ['shell','linux','sh','bash']
categories: 
 - OS
 - Linux
---

# 背景

笔记本买回来自带windows10，然后由于好奇心重，又给它折腾装上了ubuntu（本来是想支持国产deepin，奈何问题太多）。万恶之源开始，ubuntu很多常用软件没法直接用apt安装，安装完微信，使用微信一会儿会自动退出登录，无奈卸载。但问题是：非dpkg/apt/snap方式安装，卸载也不知道怎么卸载，于是查找 wechat关键字，找到一个 wechat.sh。

## 解决

### 查看脚本

部分help代码如下

```sh
help(){
  echo "wechat [-h] [-i] [-f] [-c] [--start|start] [--remove] [--instance]"
  echo "  -h, --help            Show help"
  echo "  -i, --install         Install this script to system"
  echo "  -f, --force           Force install or reinstall"
  echo "  -c, --clean           Clean all wechat container"
  echo "      --start           Start wechat"
  echo "      --update          Update script"
  echo "      --remove          Remove this script"
  echo "      --instance        Create a instance wechat container, you can create more then one using this option"
  return 0
}
```

### 执行脚本

>$ ./wechat.sh --remove

没有任何反应。。。看了下remove函数的代码，应该会把 wechat.sh文件给删除的，但是文件依然还在，可以断定执行未成功

```sh
remove(){
  [ -e ~/.local/bin/wechat.sh ] && rm -f ~/.local/bin/wechat.sh\
  && echo "remove ~/.local/bin/wechat.sh"

  [ -e ~/.local/bin/wechat ] && rm -f ~/.local/bin/wechat

  [ -e ~/.local/share/icons/hicolor/256x256/apps/WINE_WECHAT.png ] \
  && rm -f ~/.local/share/icons/hicolor/256x256/apps/WINE_WECHAT.png\
  && echo "remove ~/.local/share/icons/hicolor/256x256/apps/WINE_WECHAT.png"


  [ -e /home/$(whoami)/.local/share/applications/Wechat.desktop ] \
  && rm -f /home/$(whoami)/.local/share/applications/Wechat.desktop\
  && echo "remove ~/.local/share/applications/Wechat.desktop"

  return 0
}
```

### 调试脚本

>$ sh -x ./wechat.sh --remove

提示如图

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200511200113864.png)

第148行代码如下

```sh
 while [[ $# > 0 ]];do
```

### 问题解决

修改执行方式
before：
>$ sh wechat.sh

after：
>$ bash wechat.sh

注意： 查看.sh脚本的时候一定要看第一行, `wechat.sh` 的第一行：

```sh
#!/usr/bin/env bash
```

要区分两种情况 ```#!/bin/bash``` 或者是 ```#!/bin/sh``` 

## bash vs sh

### 什么是sh

sh(或Shell命令语言)是由POSIX标准描述的一种编程语言。它有很多实现(ksh88, dash，…)。bash也可以被认为是sh的实现(请参阅下面的内容)。
因为sh是规范，不是实现，`/bin/sh` 是在大部分POSIX系统上实际实现的符号连接（or 硬链接）。

### 什么是bash

bash是兼容sh的一种实现（虽然在几年之前被视为POSIX标准），但随着时间流逝，它需要更多的扩展。这里面的一些扩展会改变有效的POSIX shell脚本的行为，所以bash本身不是有效的POSIX shell。然后它是POSIX shell语言的方言。
bash 可以执行`--posix `切换，使得它更加的兼容POSIX，同时也尝试通过调用sh来模仿POSIX。

### sh=bash？

长期以来，在大部分GNU/Linux系统上，`/bin/sh`都是指向`/bin/bash`。结果，几乎可以忽略两者之间的区别了。 但是这种情况最近开始改变。

在`/bin/sh`不指向`/bin/bash`（在某些情况下甚至都不存在`/bin/bash`）的系统中，一些常见的例子是：
1.现代的debian和ubuntu系统上，sh默认是dash的符号链接
2.Busybox，它通常在Linux系统引导时作为initramfs的一部分运行。它使用了ash shell实现。
3.BSDs，以及通常所有非linux系统。OpenBSD 使用`pdksh`，Korn shell的后代。FreeBSD的sh是原始UNIX Bourne shell的后代。Solaris有它自己的`sh`但长期以来都不是与POSIX兼容的，是一种`Heirloom`项目提供的一个开源实现。

### 如何找到`/bin/sh`在我们系统上的指向

`/bin/sh`的复杂之处是：它可以是符号链接也可以是硬链接。
如果是符号链接，可以通过如下方式：

>% file -h /bin/sh
/bin/sh: symbolic link to bash

如果是硬链接，可以尝试：
>% find -L /bin -samefile /bin/sh
/bin/sh
/bin/bash

实际上`-L`标志同时包括符号链接和硬链接，但是这种方法的缺点是它不是可移植的，POSIX不需要find来支持`-samefile`选项，尽管GNU `find`和FreeBSD `find`都支持它。

### Shebang

>在计算领域中，Shebang（也称为Hashbang）是一个由井号和叹号构成的字符序列#!，其出现在文本文件的第一行的前两个字符。

最终，通过在脚本的第一行编写Shebang来决定使用sh还是bash：
比如使用sh
>#!/bin/sh

又或者使用/bin/bash如果可用（如果不可用会失败并带上错误信息）
>#!/bin/bash

当然你也可以选择另外一个实现，比如
>#!/bin/dash

### 到底用哪个

在我的脚本里，倾向于使用sh有以下原因：

1. 它是标准的
2. 非常简单并且易学
3. 便携并且跨POSIX系统，即使碰巧没有bash，也需要有sh

使用bash也有优点。它的特性使编程更加方便，并且类似于用其他现代编程语言进行编程。这些包括作用域局部变量和数组之类的东西。纯`sh`是一种非常简约的编程语言。

## 参考

[string-comparison-in-bash-not-found](https://stackoverflow.com/questions/12230690/string-comparison-in-bash-not-found)
[difference-between-sh-and-bash](https://stackoverflow.com/questions/5725296/difference-between-sh-and-bash)
