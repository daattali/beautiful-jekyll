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

### 总体思路
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
 获取到manifest中的ip后按策略从最近的CDN服务器获取数据
 {: .box-note}   

## socket套接字编程

### Socket类型
- TCP：可靠字节流服务  
- UDP：不可靠服务  

### TCP套接字编程
#### 过程：
1. 服务器运行
2. 创建socket
3. socket绑定到本地的ip，端口（welcome socket）
4. connection socket（阻塞等待）接受其他主机的连接（本地ip、端口，目标ip、端口）

1. 服务器创建welcome socket
2. 服务器bind：建立将wlecome socket和sad绑定
3. 服务器创建connect socket（等于welcome socket，并阻塞等待来自客户端的请求）
4. 客户端创建client socket
5. 客户端：bind（操作系统自动捆绑client socket和sad）
6. 客户端：connect（阻塞等待服务器端响应sad）
7. 服务器中阻塞的connect socket（第3步）绑定客户端的ip和端口后，响应数据给客户端
8. 客户端write:通过client socket发送数据给服务器
9. 服务端read：通过socket读取报文段
10. 服务端write：通过socket回写数据
11. 服务端：通过socket的read读取回写数据
12. 服务端close：socket close，服务器回到3

#### 数据对象
- sockaddr_in(sad):
  - sin_family: 地址簇
  - sin_port: 端口簇
  - sin_addr: ip地址
  - sin_zero: 对齐

- host_ent
  - *h_name: 主机域名
  - **h_alias: 域名别名
  - h_length: 长度
  - **h_address: ip地址

### UDP socket 编程
#### 过程
1. 服务端建立server socket：
2. 服务器bind：将server socket 绑定本地的ip和端口
3. 服务器recvfrom：阻塞等待客户端发送信息（socket，内容，来源）
4. 客户端建立client socket：
5. 客户端bind：将socket绑定本地ip和端口
6. 客户端sendto
7. 服务器解除阻塞，处理数据，在sendto（发送给来源）
8. 客户端在read
9. 服务端直接close server socket

 {: .box-note}   
 UDP不用握手，也没有welcome socket和connection socket之分
 - {: .box-note}   

## 网络安全

四个特性
- 机密性
- 认证
- 报文完整性
- 访问控制和服务的可用性

网络威胁
- 窃听
- 插入
- 伪装
- 劫持
- 拒绝服务

### 加密方式
- 对称加密：加密密钥和解密密钥一样，有key分发的问题
  - 替换密码（暴力破解）
  - 对称密钥密码（key分发危险）
  - DES加密密钥（能破解，后门可能）
  - 分组成串技术
  - AES（DES加密强度的亿万倍）
  - 密码块链
- 非对称加密：客户端公钥加密，服务器私钥解密
  - RSA密钥
    - 选择两个超级大的质数p、q,发送信息m
    - n = p * q,z=(p-1) * (q-1)
    - e 与 z 互素
    - d 使得 (ed-1) 能被z整除
    - 加密密钥是 (n,e) 解密密钥是 (n,d)
    - 加密密文c=(m的e次方) 求余n
    - 解密密文m=(c的d次方) 求余n  
    例如
    - 例如，p=5,q=7
    - 那么n=35,z=24,e=5,d=29
    - 那么(n,e)=(35,5) (n,d)=(35,9)
    - 假设原本的内容m是12
    - 那么加密的内容c=(m 的e次方) 求余n=(12的5次方)求余35=17
    - 那么解密的内容m=(c 的d次方) 求余n=(17的29次方)求余35=12

### 认证
 - 使用对称或非对称加密来验证身份（会有中间人截获加密解密公钥）

### 报文完整性

数字签名
- 可验证性：接收方
- 不可伪造性：发送方
- 不可抵赖性：第三方

数字签名：报文m计算出报文摘要，然后加密摘要作为数字签名。
- 多对一的映射
- 固定长度
- 正向计算容易反向计算苦难

散列函数算法：
- MD5散列函数
- SHA-1

### 可信赖中介

-KDC：对称加密体系的可信赖中心
-CA:非对称加密体系的可信赖中心

KDC：前提信任一个密钥中心
- A TO ADC : K_A_KDC+(A,B)                        :用A与KDC的密钥加密，需要与B交流
- KDC TO A : K_A_KDC+(R1,K_B_KDC+(A,R1))          :KDC用与A的密钥加密(KDC生成AB间的密钥R1，B的密钥加密A与R1的捆绑关系)
- A TO B   : K_A_KDC-(K_A_KDC+(R1,K_B_KDC+(A,R1))):A与KDC的密钥解出KDC发的R1和K_B_KDC+(A,B)，并将K_B_KDC+(A,R1)发给B
- B TO A   : K_B_KDC-(K_B_KDC+(A,R1))             :B用自己与KDC的密钥解出公共密钥R1，和发信人A，确定是A发的，防止伪造，并使用R1加密与A沟通

CA：前提是拿到认证中心的公钥



## 术语：
 - RTT(round trip time)：往返时间
 - 互联网角色：
  - ISP：网络服务提供商
  - ICP：应用服务提供商
  - CDN：网络内容加速提供商  


[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2022-12-31-computerInternet.md)
       
