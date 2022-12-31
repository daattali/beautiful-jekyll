---
layout: post
title: 计算机网络
subtitle: 计算机网络
gh-repo: daattali/beautiful-jekyll
gh-badge: [star, fork, follow]
tags: [test]
comments: true
---

[中科大郑烇、杨坚全套《计算机网络（自顶向下方法 第7版，James F.Kurose，Keith W.Ross）》课程](https://www.bilibili.com/video/BV1JV411t7ow)

- internet协议栈
  - 应用层：源用户和源应用到目标用户或目标应用之间传输**报文(message)**
  - 表示层：
  - 会话层：
  - 传输层：源进程到目标进程间传输**报文段(segment)**
  - 网络层：从源主机到目标主机（多个相邻网络节点）传输**分组（packet）或数据报(datagram)**
  - 链路层：在相邻网络节点上传输数据**帧(frame)**
  - 物理层：在线路上传输**比特(bit)**

 ![Alt](https://github.com/wurara/wurara.github.io/tree/master/assets/img/computerInternet)
 
 tips:
 - 链路层和物理层一般在网卡中
 - tcp/ip协议没有表示层和会话层，ISO/OSI有标识层和会话层
 - 交换机只有链路层和物理层，路由器有网络层、链路层、物理层
 
[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2022-13-31-computerInternet.md)
