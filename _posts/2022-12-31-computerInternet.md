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
{: .box-note}  

## 网络架构
- C/S
- P2P

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
{: .box-note}

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

web缓存
  - 条件get：is-modified-since：在这个时间段后更新则返回全部信息，否则返回304
 
 
## DNS系统

###总体思路
- 分层命名
- 分布式数据库
- 运行在UDP的53端口
- 有13个根名字服务器

### 目的
- 实现IP和域名的转换
- 主机别名（域名）到规范名字（某个数据中心某个机柜某个刀片服务器）的转换
- 负载均衡

### DNS命名空间
- 顶级域
 - 通用generic(.com,.edu)
 - 国家countries(.cn,.us)
- 若干子域
 
 {: .box-note}   
 如：.edu.cn是中国教育网，cn是顶级域名，edu是cn域管理下的教育域   
 {: .box-note}   
 
 顶级域(TLD)服务器维护对应子域的命名服务器资源  
 资源(resource records)信息：
 - Domain Name:域名
 - TTL：存活时间（权威为长期，缓存为2天）
 - Class：对于Internet,值为IN
 - Value：数字、域名或ASCII串
 - Type
   - A：name为主机、value为IP地址
   - CNAME：Name为规范名字的别名（如规范名字 www.ibm.com 的规范名字为servereast.back2.ibm.com）
   - NS：name为域名，Value为域名的权威服务器的域名
   - MX：value为对应邮件服务器的名字


## CDN

CDN解决互联网杀手级应用（视频）

### 部署策略
- Enter Deep  
在遍及全球的ISP中部署服务器集群来深入到ISP接入网中。目标是靠近端用户，通过减少端用户到CDN集群之间的链路长度和路由器数量，从而改善用户请求时延。但管理、维护这一堆集群的成本很高。
- Bring Home  
这种方式被许多CDN公司采用。通过在少量关键位置建造大型集群来邀请周边ISP访问。不是将集群放在ISP中，通常放在IXP中（因特网交换点）。这种设计维护和管理开销更低，但牺牲了部分端用户的体验。

 {: .box-note}   
 - 获取到manifest中的ip后按策略从最近的CDN服务器获取数据
 - 域名解析的重定向
 {: .box-note}   

## socket套接字编程

## 术语：
 - RTT(round trip time)：往返时间
 - 互联网角色：
  - ISP：网络服务提供商
  - ICP：应用服务提供商
  - CDN：网络内容加速提供商
[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2022-12-31-computerInternet.md)
       
