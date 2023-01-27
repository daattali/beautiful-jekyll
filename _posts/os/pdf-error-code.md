---
title: 多种方式100%完美解决从PDF复制文字后乱码问题
date: 2020-07-14 15:49:00
tags: ['乱码','PDF']
categories: 
 - OS
 - Windows
---

## 背景

需要从PDF复制文字出来**做笔记**，可是谁知道PDF通过adobe打开后复制出来后是乱码，如下图所示： （再次感谢guide哥整理的[文档](https://snailclimb.gitee.io/javaguide/)）

![乱码.gif](https://i.loli.net/2020/09/25/jlbkAvMLPdBh2qp.gif)

## 解决
尝试过`安装字体`，可惜没卵用。

### 方法1-CAJViewer打开
用该软件打开后复制，可以完美复制，但是有个`小问题`，如下文内容中
**“比较消耗资源”** 实际上是一行，

但是会显示为
**“比较消耗资
源.....”**

![CAJViewer.gif](https://i.loli.net/2020/09/25/Shp8YT6j3QaxwIV.gif)

### 方法2-PDF转为PPT
步骤：（Adobe）

 1. 选择文件
 2. 导出
 3. 选择PPT

导出为PPT再次复制文字，如图：
但是也有个`小问题`，如下文内容中
**“比较消耗资源”** 实际上是一行，

但是会显示为
**“比较消耗资 源.....”**   换行处`多了一个空格`

![PPT.gif](https://i.loli.net/2020/09/25/JKXf6HTb1xYcAyh.gif)

**如果有更好的方法解决乱码问题，还望不吝指出。**