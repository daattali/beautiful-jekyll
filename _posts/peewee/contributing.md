---
title: Peewee中文文档 -【五】：贡献
date: 2017-07-06 12:09:57
updated: 2017-07-06 12:09:57
tags: [peewee, Python, orm]
categories: 
 - 开发语言
 - Python
 - peewee
copyright: true
---


为了持续改善，peewee需要象你这样的开发者的帮助。无论是贡献补丁，提交bug报告，还是仅仅提交或者回答一个问题，你都是在帮助peewee成为更好的库。在这个文档中，我会描述一些你可以提交帮助的方法。


## 补丁

你有一个新功能的想法，或者是想改进笨重的API。在编码并提交拉取请求之前，请在github上打开一个新的问题，描述你提出的更改。这不一定是正常的只是描述你想做什么，为什么。

当你已经准备好，你可以提交你的拉取请求并进行更改。成功的补丁应该包含：

* 单元测试； 
* 文档，代码文档或者通用 [ API文档 ](http://peewee.readthedocs.io/en/latest/peewee/api.html#api) ； 
* 代码风格与peewee代码库里的其他部分相符。 

##  缺陷

如果你发现了一个缺陷，请检查一下是否已经被 [ 其他人提交 ](https://github.com/coleifer/peewee/issues/)。如果没有请 [ 提交 ](https://github.com/coleifer/peewee/issues/new)
在github上。你提供越多的信息，我们便修复得越快。所以请尝试提交bug包含以下内容：

* Traceback和错误信息（请 [ 格式化你的代码 ](https://help.github.com/articles/markdown-basics/) ！） 
* 你的相关代码或者代码重现这个error 
* peewee版本：python -c “from peewee import version ; print( version )”
* 你使用的数据库 

如果你在代码里发现了一个缺陷并提交失败的测试用例，很敬佩你，你是个英雄。

##  问题

如果你对peewee有什么问题，我推荐你下面的方法：

* 在StackOverflow上提问。我几乎每天都会在SO上查看新的关于peewee的问题并尝试去回答它们。这也有益于保留问题和答案供其他人找到。 
* 使用IRC提问，连接freenode加入peewee频道。我总是回答问题，但是可能需要一些时间才能找到答案。 
* 在邮件列表里提问， [ https://groups.google.com/group/peewee-orm ](https://groups.google.com/group/peewee-orm)
