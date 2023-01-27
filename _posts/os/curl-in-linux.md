---
title: Linux下使用curl Post文件 & 入参
date: 2019-07-15 17:29:00
updated: 2019-07-15 17:29:00
tags: ['linux','curl文件','post']
categories: 
 - OS
 - Linux
---

搜了一下，大部分要么是只post参数，要么是只post文件的。同时post（表单入参 + 文件）好像没有，特记录一下。

通过Postman上传文件示例:


![postman上传文件示例.png](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/curl-in-linux/8rG6hkXFHJxQiNO.png)
对应的linux下`curl post`文件命令:

>$ curl -H "Content-Type:multipart/form-data" -F "requestNo=123" -F "source=1" -F "reqData={\"userNo\":\"123456\"}" -F "file=@/your/path/Pictures.zip" http://192.168.100.100:80/service/uploadFiles > post.log

`-H` 指定hearders, 在该示例下可以省略
`-F` 指定入参，特别是form表单入参，挨个传
`-F "file=@..."` @后接文件的路径
`> post.log` 将日志信息打印在当前路径的post.log里面
