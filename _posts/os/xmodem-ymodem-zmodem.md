---
title: 平时使用的Lszrz到底是什么协议？说说Xmodem/Ymodem/Zmodem
date: 2020-04-30 08:44:02
tags: ['Xmodem','Ymodem','Zmodem']
categories: 
 - 计算机基础
---

# XMODEM, YMODEM, and ZMODEM

由于平时使用rz/sz较多，r/s好理解，一个send一个receive。但是由不太清楚`z`是什么意思，故有此文。
`sx/rx`, `sb/rb` (b=batch)和`sz/rz`分别实现了xmodem，ymodem和zmodem文件传输协议。

Xmodem(1977 Ward Christensen )->Ymodem(1985 Chuck Forsberg )->Zmodem(1986 Chuck Forsberg)

先有Xmodem，后逐渐演化成Ymodem，但是Ymodem还是不够快速缺点也多，再后来便发展为Zmodem，也就是我们日常工作中使用相当多的文件传输协议之一。

## Xmodem

广泛使用的文件传输协议之一。最初的Xmodem协议使用128字节包和简单的`校验和`方式做为错误检测。随后改进为Xmodem-CRC，使用更加安全的循环冗余校验（Cyclic Redundancy Check ）方式作为错误检测。Xmodem协议总是尝试优先使用`CRC`，如果发送方未收到使用`CRC`方式的请求消息，接收方则会切换为`校验和`方式继续请求传输。

### 校验和方式

**包结构**

| byte1                | byte2    | byte3          | bytes 4~131=128bytes | byte132  |
| -------------------- | -------- | -------------- | -------------------- | -------- |
| SOH(Start of Header) | block no | 255-(block no) | data packet          | checksum |

打个比方，发一次文件需要分5块（block），那么block no 是从1到5，又假设这5块的数据包分别是d1~d5，那么checksum=sum(d1+d2+d3+d4+d5)/256 , 这里`/`是取模。

接收方如何知道某一块是不是最后一块？

以上述例子，在第5块发送完成后，紧接着会发送一个EOT（End of Transmission）标记字符，该字符是以单个字节单独发送。

#### 传输过程

![checksum](https://img-blog.csdnimg.cn/20200430083810685.png)


### CRC方式

 **包结构**

| byte1 | byte2    | byte3          | bytes 4~131=128bytes | bytes132~133 |
| ----- | -------- | -------------- | -------------------- | ------------ |
| SOH   | block no | 255-(block no) | data packet          | CRC-16       |

CRC方式在原有checksum的基础上，由一个字节更新为两个字节的CRC，相对于checksum更加安全。CRC循环冗余校验也属于校验和的一种，但是在严格意义上不属于`和`而是属于`除`

### Xmodem-1K

**包结构**

| byte1 | byte2    | byte3          | bytes 4~1027=1024bytes | bytes1028~1029 |
| ----- | -------- | -------------- | ---------------------- | -------------- |
| STX   | block no | 255-(block no) | data packet            | CRC-16         |

Xmodem-1K本质上是Xmodem-CRC，只是data packet长度增加为1024bytes（1K），然后第1个字节由`SOH`更新为`STX`。在其他系统和BBS上它也被成为`Ymodem`，`XMODEM-1K`最初是`Chuck Forsberg`在其YMODEM协议中对XMODEM进行的众多改进之一。 Forsberg建议，各种改进是可选的，希望软件作者能够实现尽可能多的改进。 相反，他们通常只实现了最低限度的最低要求，导致大量的半兼容实现，并最终从名称“ YMODEM”拆分为“ XMODEM-1K”和各种YMODEM。 

## Ymodem

Ymodem是`Chuck Forsberg`对Xmodem的改进，但Ymodem的命名由Xmodem的原始作者`Ward Christensen`给出。Ymodem本质上是`Xmodem-1K`，它允许在同一个`会话(session)`里同时进行多文件传输。 在某些系统上，它被列为`Ymodem Batch`。

**包结构**

Ymodem在Xmodem基础上发展，沿用了`TeLink`协议的添加空头块的做法，也就是增加`block 0`。该block标识即将发送文件的`文件名`，`文件大小`和`文件创建时间戳`，如下：

| byte1 | byte2 | byte3 | bytes 4~131=128bytes   | bytes132~133 |
| ----- | ----- | ----- | ---------------------- | ------------ |
| SOH   | 0x00  | 0xFF  | 文件名 文件大小 时间戳 | CRC-16       |

Ymodem的`block n`结构（非第0块）， data packet既可以是128位也可以是1024位，可以通过命令控制

| byte1 | byte2    | byte3          | bytes 4~131=128bytes | bytes132~133 |
| ----- | -------- | -------------- | -------------------- | ------------ |
| SOH   | block no | 255-(block no) | data packet          | CRC-16       |

| byte1 | byte2    | byte3          | bytes 4~1027=1024bytes | bytes1028~1029 |
| ----- | -------- | -------------- | ---------------------- | -------------- |
| STX   | block no | 255-(block no) | data packet            | CRC-16         |

### 传输过程

Ymodem允许在同一个会话(session)内同时传输多个文件，以下以多文件为例展示传输过程，单个文件类似。

**以128位传输**

![128](https://img-blog.csdnimg.cn/20200430084119157.png)



**以1K传输**


![1K](https://img-blog.csdnimg.cn/2020043008413488.png)


### Ymodem-g

YMODEM-g是Ymodem的变体，是一种流协议，以连续流的形式发送和接收1K数据包，直到指示需要停止为止。 在发送下一个数据包之前，它不需要等待接收到`ACK`。 该协议比YMODEM更快，因为没有在数据包之间引入延迟，但是没有纠正错误的能力。 如果任何块传输失败，则取消整个文件的传输。

## Zmodem

随着网络速度加快，已有的x/ymodem协议速度已经跟不上时代的步伐。Zmodem应运而生，它采用窗口滑动机制，Zmodem有两个最重要的特征：`高效`，`提供崩溃恢复`。

### 高效

只要接收方没有发现错误便允许发送方不停的发送数据包，而无需`发送方`接收`接收方`的`ACK`标记(因为可能会有延迟或者错误发生)。允许连续发送的数据包数量称之为`窗口`，在大部分Zmodem的实现协议中采用2~16个包的数量。

### 崩溃恢复

如果Zmodem传输被取消或者因为某种原因被干扰，该稍候可以恢复传输，并且无需重新发送之前的内容。



## 参考
http://web.cecs.pdx.edu/~rootd/catdoc/guide/TheGuide_226.html#SEC237
https://en.wikipedia.org/wiki/XMODEM
https://en.wikipedia.org/wiki/YMODEM
https://en.wikipedia.org/wiki/ZMODEM
