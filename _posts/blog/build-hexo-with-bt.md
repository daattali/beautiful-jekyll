---
title: 使用宝塔在云服务器上搭建Hexo博客全记录
date: 2020-09-30 9:50:00
tags: ['Hexo','自建博客', '宝塔']
categories: 
 - 博客
 - Hexo
---

# 前提

- 一台云服务器（阿里云/腾讯云/华为云等等）
- 一个域名（阿里域名/腾讯域名等）且已经备案
- 熟悉基本的linux命令
- 懂点英文

# 安装宝塔

`假设`你已经登录进了云服务器，如果不懂如何操作，请google一下。

## 安装
{: .box-info}
 之所以使用宝塔，因为它可以帮你节省很多不必要的麻烦，并且有很多一键式操作。

{: .box-default}
 宝塔Linux面板系统兼容性：Centos8.x > Centos7.x > Ubuntu18.04 > Debian10 > Ubuntu 20.04 > 其它系统


{% tabs install %}
<!-- tab Centos -->
>$ yum install -y wget && wget -O install.sh http://download.bt.cn/install/install_6.0.sh && sh install.sh
<!-- endtab -->
<!-- tab Ubuntu/Deepin -->
>$ wget -O install.sh http://download.bt.cn/install/install-ubuntu_6.0.sh && sudo bash install.sh
<!-- endtab -->
<!-- tab Debian -->
>$ wget -O install.sh http://download.bt.cn/install/install-ubuntu_6.0.sh && bash install.sh
<!-- endtab -->
<!-- tab Fedora -->
>$ wget -O install.sh http://download.bt.cn/install/install_6.0.sh && bash install.sh
<!-- endtab -->
{% endtabs %}

我选择的是centos，所以后面的操作都是基于centos，且全程以`root`用户操作。

ssh登录到远程云服务器，输入`上面对应系统的命令`之后，输入`y`，等待全程自动安装完，依赖你的网速，快的话5分钟，慢的话可能需要20分钟，别急，磨刀不误砍柴工。

![安装宝塔.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/安装宝塔.png)

完成之后的页面显示如下：
![宝塔安装完成.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/宝塔安装完成.png)


## 登录宝塔

>内网面板地址: http://192.168.21.16:8888/ec9c1774
>username: cnng3xne
>password: 6410b524

浏览器打开，输入上面的地址，访问面板并输入账号密码。
![宝塔登录面板](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/访问面板.png)
登录之后，勾选协议，然后它会自动弹出安装选项，勾选nignx
![nginx安装](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/安装nginx.png)
然后就静静等待安装完成，该过程可能会有点久
![等待完成](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/等待完成.png)

安装完成之后，宝塔要求你输入手机账号密码，没关系，咱注册一个，然后登录

# 安装hexo

## 安装nodejs/npm

### 直接通过面板安装
在`宝塔面板`，点击到左侧栏的`软件商店`，搜索node，找到`PM2管理器`，点击安装

### 通过命令安装

{% tabs install_node %}
<!-- tab 通用 -->
Node 官网已经把 linux 下载版本更改为已编译好的版本了，我们可以直接下载解压后使用：

>$ wget https://nodejs.org/dist/v12.18.4/node-v12.18.4-linux-x64.tar.xz    // 下载 
>$ tar xf  node-v12.18.4-linux-x64.tar.xz        // 解压 
>$ cd node-v12.18.4-linux-x64/                  // 进入解压目录 
>$ ./bin/node -v                               // 执行node命令 查看版本 

v12.18.4

解压文件的 bin 目录底下包含了 node、npm 等命令，我们可以使用 ln 命令来设置软连接：

>$ ln -s /usr/software/nodejs/bin/npm   /usr/local/bin/  
>$ ln -s /usr/software/nodejs/bin/node   /usr/local/bin/ 

<!-- endtab -->
<!-- tab Centos<code>源码文件</code> -->
1.进入[node官方网站](https://nodejs.org/en/download/)

2.选择二进制64位，右键复制url
![nodejs安装包.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/nodejs安装包.png)

3.下载
>$ cd /usr/local/src  
>$ wget https://nodejs.org/dist/v12.18.4/node-v12.18.4.tar.gz

4.解压
>$ cd node-v12.18.4  
>$ ./configure --prefix=/usr/local/node/v12.18.4 

5.编译安装
>$ make 
>$ make install 

6.配置node_home,并设置环境变量
编辑环境变量配置文件 ： 
>$ vim /etc/profile 

然后添加

    #set for nodejs
    export NODE_HOME=/usr/local/node/v12.18.4
    export PATH=$NODE_HOME/bin:$PATH

shift+zz 或者 :wq 保存， 使配置生效，输入
>$ source /etc/profile 
<!-- endtab -->
<!-- tab Ubuntu<code>git源码</code> -->
以下部分我们将介绍在 Ubuntu Linux 下使用源码安装 Node.js 。其他的 Linux 系统，如 Centos 等类似如下安装步骤。

在 Github 上获取 Node.js 源码：

>$ sudo git clone https://github.com/nodejs/node.git
Cloning into 'node'...

修改目录权限：

>$ sudo chmod -R 755 node

使用 ./configure 创建编译文件，按步骤来：

>$ cd node 
>$ sudo ./configure 
>$ sudo make 
>$ sudo make install 

查看 node 版本：

>$ node --version
v12.18.4

<!-- endtab -->
{% endtabs %}

验证是否安装成功：node -v, 如果有打印正确的node版本，则表示安装成功，如果报错，则可能是哪一步出错了，检查一下。

## 安装hexo

所有必备的应用程序安装完成后，即可使用 npm 安装 Hexo。

>$ npm install -g hexo-cli

进阶安装和使用

对于熟悉 npm 的进阶用户，可以仅局部安装 hexo 包。

>$ npm install hexo

## 生成静态文件

在你远程服务器某处新建文件夹，命名随意取(比如我的就是`for-tutorial`)

>$ mkdir for-tutorial 
>$ cd for-tutorial/ 
>$ hexo init 

完成之后，hexo的初始化项目包就下载完成，依然在该目录`for-tutorial`下，执行安装npm依赖包命令：
>$ npm install 

安装完成之后，执行生成静态文件的命令：
>$ hexo g 

生成的静态文件在你当前目录的`public`文件夹里，比如我的就是`/data/hexo/for-tutorial/public`

## 用nginx运行静态文件

进入宝塔面板，选择网站，点击添加站点
![添加站点.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/添加站点.png)

根目录选择上面的public： /data/hexo/for-tutorial/public， 点击提交，此时你访问该域名实际时不可能能成功的，因为还没有将域名解析到你的云服务器的IP上。

# 域名解析+开放端口


## 域名解析

进入你购买域名服务商的域名控制台，比如我的是：阿里域名

添加解析记录：
![解析域名.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/解析域名.png)

## 放开端口

进入你所购买的云服务器管理页面

![安全组配置.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/安全组配置.png)


放开443和80

![开放端口.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/开放端口.png)


再访问你的域名看看，是不是可以正常的显示hexo初始化页面，如下：
![完美的构建成功.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/完美的构建成功.png)

## 启动https

在宝塔面板，选择你刚才新建的网站，选择`SSL`，添加提交，等待完成，再使用https访问看看

访问https://tutorial.nothinghere.cn/ ，已经可以成功的显示为安全链接。

![https添加成功.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/build-hexo-with-bt/https添加成功.png)

