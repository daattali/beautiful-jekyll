---
title: 解决Windows10英文版中文字体难看、时大时小、中文比英文小等问题
date: 2020-05-19 22:39:00
tags: ['windows','英文版windows','修改字体']
categories: 
 - OS
 - Windows
---

安装好Windows10英文版，可是中文字体却非常难看，不是Windows10中文版默认的`微软雅黑`。并且还会存在`中文字体时大时小`，`中文字体比英文字体小`的情况。

英文版中文字体默认如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200519222705715.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Ftb3Njbg==,size_16,color_FFFFFF,t_70)

中文字体太小的问题：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200525104207671.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200525104207674.png)


修改后的中文字体显示如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200519223557945.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Ftb3Njbg==,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200525111014391.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200525111014395.png)


如何处理：

 1. 打开注册表编辑器（Win+R，输入【regedit】回车）
 2. HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\FontLink\SystemLink
 3. 依次找到Segoe UI，Tahoma，Microsoft Sans Serif
 4. 双击Segoe UI找到 `MSYH.TTC,Microsoft YaHei UI,128,96` `MSYH.TTC,Microsoft YaHei UI`
 5. 剪切然后放在配置的最前面。如图X和图Y所示
 6. 双击Tahoma，Microsoft Sans Serif找到`MSYH.TTC,Microsoft YaHei UI` 删掉
 7. 在配置最前面添加 `MSYH.TTC,Microsoft YaHei UI,128,96` `MSYH.TTC,Microsoft YaHei UI`
 8. 保存后重启电脑

图X：
![图X](https://img-blog.csdnimg.cn/20200519222825365.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Ftb3Njbg==,size_16,color_FFFFFF,t_70)

修改之后
图Y：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200519222825369.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Ftb3Njbg==,size_16,color_FFFFFF,t_70)

参考
http://blog.sina.com.cn/s/blog_58c506600101dd01.html