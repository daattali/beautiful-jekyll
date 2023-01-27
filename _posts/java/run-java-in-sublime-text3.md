---
title: Sublime text3添加java编译运行环境
date: 2019-07-25 11:29:00
updated: 2019-07-25 11:29:00
tags: ['sublime','java']
categories: 
 - OS
 - Windows
---

## 前提

1. 安装好JDK
2. 安装好Sublime text3

## 开始

- 新建Build System
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190725111738643.png)
- 将默认的内容删掉，添加如下内容

`注意`：
path是你的jdk安装路径, 记得修改成对应的

```json
{
    "cmd": ["javac", "-encoding" , "utf-8", "$file_name", "&&", "java", "$file_base_name"],
    "file_regex": "^[ ]*File \"(...*?)\", line ([0-9]*)",
    "path": "C:\\Program Files\\Java\\jdk1.8.0_171\\bin\\",
    "selector": "source.java",
    "shell": true,
    "encoding":"cp936"
}
```

- ctrl + S 保存，命名为 javaC.sublime-build
- 将Build System修改为 `javaC` - 也就是我们上一步添加的， 如下图
- 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190725112551460.png)
- 编写HelloWorld.java文件 ，填写如下内容

```java
public class HelloWorld {
   /* 第一个Java程序.  
    * 它将打印字符串 Hello World
    */
    public static void main(String[] args) {
       System.out.println("Hello World"); // 打印 Hello World
    }
}
```
- ctrl + shift + b, 完成

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190725112749241.png)
