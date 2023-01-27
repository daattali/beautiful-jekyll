---
title: Appium环境安装步骤
date: 2017-07-12 10:59:09
tags: ['Appium安装','appium环境配置','JDK安装','androidSDK']
categories: 
 - 软件测试
 - 测试工具
---

#JDK安装

 1. 下载JDK，[地址](http://www.oracle.com/technetwork/java/javase/downloads/index.html)
 2. 下载完成，一步一步点击完成安装（路径可以自行更改）
 3.  右键计算机 - 属性 - 高级系统设置 - 高级 - 环境变量
 4.  系统变量：新建JAVA_HOME，输入变量值JDK的安装目录（我的是C:\Program Files\Java\jdk1.8.0_66）
 5. 系统变量：找到Path，点击编辑，在最后加上%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin;（注意：原来Path的变量值末尾有没有;号，如果没有，先输入；号再输入上面的代码）
 6. 系统变量：新建CLASSPATH变量，变量值填写 .;%JAVA_HOME%\lib;%JAVA_HOME%\lib\tools.jar（注意最前面有一点）
 7. 检查是否安装成功：打开cmd面板，输入java -version，如果有显示java版本等信息则表示成功，如果提示java不是内部或者外部命令，则需要再检查一遍安装过程。

# Android SDK安装

 1. 下载Android SDK，[地址](https://www.baidu.com/link?url=n8D8L5BiGZGOp1Wjv2ylq48-PYsynST3sJa8a3KiFlZUyVffJlCb_PLsKMl3-XzBbUOwBg7wNPiqoOeQ1uHra_cAy-Efz8aEYGNVK2kqzP3&wd=&eqid=a22a5b0d000004cd0000000659658a54)
 2. 解压下载的文件
 3. 系统变量新建ANDROID_HOME ，变量值  G:\adt-bundle-windows-x86-20130917\sdk
 4. 系统变量新建ANDROID_PLATFORM_TOOLS ，变量值 G:\adt-bundle-windows-x86-20130917\sdk\platform-tools
 5. 系统变量新建ANDROID_TOOLS，变量值 G:\adt-bundle-windows-x86-20130917\sdk\tools
 6. 最后系统变量：找到PATH变量，添加（很重要，一定要3个都添加）：;%ANDROID_HOME%;%ANDROID_PLATFORM_TOOLS%;%ANDROID_TOOLS%

# 安装nodejs
1. 下载nodejs，[地址](http://nodejs.cn/download/)
2. 一步一步点击完成安装

# 安装Appium
1. 下载Appium，[地址](http://appium.io/)
2. 一步一步点击完成安装

# 验证安装
1. 打开CMD面板
2. 输入appium-doctor，如果提示如图表示安装成功，如果不是便需要再检查步骤。
![这里写图片描述](http://img.blog.csdn.net/20170712105719056?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYW1vc2Nu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)