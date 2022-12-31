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
一   
## internet协议栈
- 应用层：源用户和源应用到目标用户或目标应用之间传输**报文(message)**
- 表示层：
- 会话层：
- 传输层：源进程到目标进程间传输**报文段(segment)**
- 网络层：从源主机到目标主机（多个相邻网络节点）传输**分组（packet）或数据报(datagram)**
- 链路层：在相邻网络节点上传输数据**帧(frame)**
- 物理层：在线路上传输**比特(bit)**

{: .box-note}
链路层和物理层一般在网卡中。  
交换机只有链路层和物理层，路由器有网络层、链路层、物理层  
{: .box-note}
tcp/ip协议没有表示层和会话层，ISO/OSI有标识层和会话层  
一   
## 网络架构
- C/S
- P2P
一   
## 分层通信的问题点：
### 进程标示和寻址
- IP
- TCP、UDP
- 端口
### 应用层传给传输层的信息(标识进程地址)
- SDU：发送的数据
- 源信息:IP+TCP(UDP)端口
- 目标信息:对方的IP+TCP(UDP)端口

每次都发数据过于冗余，所以有了Socket。  
Socket(套接字)是一个整数(相当于一个key)，应用层将这个整数传给传输层。传输层通过Socket值查询表获得TCP的四元组(源IP、源端口、目标IP、目标端口)或UDP的二元组(本机IP、本机端口)。  
TCP协议需要给传输层传输Socket值和SDU(传输数据)  
UDP协议需要给传输层Socket值、SDU、目标ip和目标端口  

{: .box-note}
Socket只有本地有效。

### 使用传输层提供的服务实现应用
- 应用层协议
  定义如何交换报文
    - 格式和语法
    - 字段语义
    - 动作和次序
- 应用程序需要传输层的服务
  - 数据丢失率
  - 延迟
  - 吞吐
  - 安全性

## Web and Http
url ==> 协议名://用户:密码@主机名/资源路径:端口  
Waiting Socket：等待请求的Socket。请求来后新建Socket，Waiting Socket任然等待。  

- HTTP1.0非持久HTTP：发送完数据后关闭TCP连接
- HTTP1.1持久HTTP：发送完数据后连接不去除,后续不再进行TCP连接。
  - pipeline（流水线方式）：并行
  - 非pipeline：串行
 
 

## 术语：
 - RTT(round trip time)：往返时间
 
[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2022-12-31-computerInternet.md)
       
