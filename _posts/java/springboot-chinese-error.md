---
title: springboot使用.properties文件注解读入@Value中文乱码问题
date: 2018-11-29 16:22:09
tags: ['spring','配置乱码','前端乱码']
categories: 
 - 开发语言
 - Java
---

## 问题背景
使用springMVC，后端给前端返回的中文为乱码。最初以为是后端编码与前端编码不一致，后加入log调试发现是因为使用@value注入的时候，读取到application.properties文件就是乱码。

## 解决办法

### 1.指定application文件的编码格式
此方法未验证，借鉴此处 《[CarryDiu的博客](https://blog.csdn.net/weixin_41987553/article/details/82958811)》
### 2.修改application文件的编码格式
此方法验证成功，完美解决问题。借鉴此处《[heart_java的博客](https://blog.csdn.net/qq_29447481/article/details/78285646)》

- 将application.properties文件所有内容copy出来保存
- 修改application.preperties文件编码为utf-8
- 将第一步保存的内容重新粘贴到application.properties里面

IDEA修改application文件编码截图：重要部分标红
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181129162122680.png)