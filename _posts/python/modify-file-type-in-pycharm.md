---
title: pycharm/idea修改file type
date: 2017-12-13 19:18:47
tags: ['pycharm','filetypes']
categories: 
 - 开发语言
 - Python
---

# 原因

添加一个文件 config.ini, 理论上说该文件会以ini文件格式打开，但是不知道咋的手贱用Text格式打开了。

.ini正确打开方式

![这里写图片描述](http://img.blog.csdn.net/20171213191209867)



.Text正确打开方式

![这里写图片描述](http://img.blog.csdn.net/20171213191230334)

手贱操作后的样子

![这里写图片描述](http://img.blog.csdn.net/20171213191314059)

# 解决

File - Setting - Editor - File Types

![这里写图片描述](http://img.blog.csdn.net/20171213191553532)

搜索Text，然后选中，找到config_alpha.ini然后删掉，搞定！！！！

![这里写图片描述](http://img.blog.csdn.net/20171213191753942)
