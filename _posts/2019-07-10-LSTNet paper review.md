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

![](https://upload-images.jianshu.io/upload_images/10029502-5baf1b0fb7bdedc1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![CNN Component](https://upload-images.jianshu.io/upload_images/10029502-e61f3e35e3bbc607.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### RNN Component

正常的一层GRU ， 激活函数RELU。

![GRU](https://upload-images.jianshu.io/upload_images/10029502-3ea21eca3f525d80.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


##### Skip - RNN Component
p是设置跳跃的间隔距离
![Recurrent-skip Component](https://upload-images.jianshu.io/upload_images/10029502-f3ae60c8ecfe351a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![Recurrent-skip Component](https://upload-images.jianshu.io/upload_images/10029502-2720315585321ec9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### Attention Component

![Attention](https://upload-images.jianshu.io/upload_images/10029502-9452de9aba564b36.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

H^R,t 是隐层（上一层RNN）的matrix，h是Hmatrix中的column
即H = [h t-q, ... , h t-1] 
αt就是得到的注意力矩阵，将Ht * αt 得到注意力加权过的新的隐层序列。

![ht](https://upload-images.jianshu.io/upload_images/10029502-b545761d79584d2b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
最后一个window 的隐层向量使用简单的线性投影得到。

##### AR Component

![AR](https://upload-images.jianshu.io/upload_images/10029502-6c7b9526585518ea.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### LSTNet Architecture

![](https://upload-images.jianshu.io/upload_images/10029502-53ec561bfa816784.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 目标函数

在大多数预测任务中，都把最小均方误差做为默认的损失函数。而在LSTNet中，使用绝对误差作为目标函数。
![](https://upload-images.jianshu.io/upload_images/10029502-781004dd58b519fd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 优化策略
SGD & Adam

#### 四、评测任务

***Baseline***
![](https://upload-images.jianshu.io/upload_images/10029502-41fb526b7dcc38a4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/10029502-8891d94bb0cd4c14.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/10029502-6fe2986629c4343d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
##### 4.5 Main Results
![image.png](https://upload-images.jianshu.io/upload_images/10029502-c2873e3c1d767052.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  ***Reference：***
[Original Paper (LSTNet)](http://nyc.lti.cs.cmu.edu/yiming/Publications/lai-sigir18.pdf)
[Open Source Code By Author](https://github.com/laiguokun/LSTNet)





