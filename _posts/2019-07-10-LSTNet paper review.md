---
layout: post
title: LSTNet Paper Review
subtitle: Paper from SIGIR 2018, Modeling Long- and Short-Term Temporal Patterns with Deep Neural Networks
tags: [Paper Review, DeepLearning]
---

#### 一、概述
[Modeling Long- and Short-Term Temporal Patterns with Deep Neural Networks (LSTNet)](http://nyc.lti.cs.cmu.edu/yiming/Publications/lai-sigir18.pdf)

这篇是发表在SIGIR2018的一篇文章（2017发在了Arxiv上），主要内容就是一个用于做时序预测的复合网络结构。
时序预测没什么好说的，也是一个相对久远的任务了。
经典一元模型有AR、MA、ARCH、ARMA（ARIMA）等等，也有多元时序回归预测VARMA，以及非线性时序回归预测。
LSTM提出后，基于其可存贮序列数据的历史信息的特性，也有很多人做RNN（多为LSTM和GRU）网络模型在时序预测方面的研究。
~~***但是RNN的模型做时序预测，过于依赖预测值前一天的值。***~~
#### 二、关于本文
文章提出的模型，主要就是先用CNN来提取短期多元（窗口内）信息，然后将CNN提取的处理后序列信息扔进RNN（这里用的是GRU）和Skip-RNN，最后将 CNN + RNN + （SKIP |ATT）  输出的结果与AR的结果做一个拼接Merge，作为最后的输出。
#### 三、LSTNet
##### CNN Component
正常的CNN 序列处理，就和做CNN文本处理一样，Conv1D模型，多个卷积核做卷积操作，最后作为RNN层的训练数据。
激活函数RELU。

![](http://imgsrc.baidu.com/forum/pic/item/ee1ce6cd7b899e5183977efc4ca7d933c9950d27.jpg)

![CNN Component](http://imgsrc.baidu.com/forum/pic/item/a86ba9773912b31b01ad88c18818367ad8b4e178.jpg)

##### RNN Component

正常的一层GRU ， 激活函数RELU。

![GRU](http://imgsrc.baidu.com/forum/pic/item/5164b9014a90f603de71d9af3712b31bb251ed78.jpg)


##### Skip - RNN Component
p是设置跳跃的间隔距离
![Recurrent-skip Component](http://imgsrc.baidu.com/forum/pic/item/02d5c895d143ad4b423002288c025aafa50f0626.jpg)

![Recurrent-skip Component](http://imgsrc.baidu.com/forum/pic/item/2de5738da977391203e7c089f6198618347ae278.jpg)

##### Attention Component

![Attention](http://imgsrc.baidu.com/forum/pic/item/5032b31c8701a18b3b2a57a7902f07082a38fe78.jpg)

H^R,t 是隐层（上一层RNN）的matrix，h是Hmatrix中的column
即H = [h t-q, ... , h t-1] 
αt就是得到的注意力矩阵，将Ht * αt 得到注意力加权过的新的隐层序列。

![ht](http://imgsrc.baidu.com/forum/pic/item/f5958bd4b31c87011a77f70e297f9e2f0508ff78.jpg)
最后一个window 的隐层向量使用简单的线性投影得到。

##### AR Component

![AR](http://imgsrc.baidu.com/forum/pic/item/e81c828ba61ea8d3a42e30ec990a304e241f5834.jpg)

##### LSTNet Architecture

![](http://imgsrc.baidu.com/forum/pic/item/d8a978f0f736afc3e6127b8dbd19ebc4b6451226.jpg)

##### 目标函数

在大多数预测任务中，都把最小均方误差做为默认的损失函数。而在LSTNet中，使用绝对误差作为目标函数。
![](http://imgsrc.baidu.com/forum/pic/item/7082034f78f0f73631e008e90455b319eac41326.jpg)

##### 优化策略
SGD & Adam

#### 四、评测任务

***Baseline***
![](http://imgsrc.baidu.com/forum/pic/item/9941d933c895d1433f9ba0cb7df0820258af074b.jpg)
![](http://imgsrc.baidu.com/forum/pic/item/49bed109b3de9c829f69bd676281800a18d84334.jpg)
![](http://imgsrc.baidu.com/forum/pic/item/0aefb3de9c82d158838e1d598e0a19d8bd3e4234.jpg)
##### 4.5 Main Results
![image.png](http://imgsrc.baidu.com/forum/pic/item/637fa9014c086e06da697aa30c087bf408d1cb78.jpg)

  ***Reference：***
[Original Paper (LSTNet)](http://nyc.lti.cs.cmu.edu/yiming/Publications/lai-sigir18.pdf)
[Open Source Code By Author](https://github.com/laiguokun/LSTNet)





