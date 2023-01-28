---
title: Peewee中文文档【一】：安装与测试
date: 2017-07-06 10:21:15
tags: [peewee, Python, orm]
categories: 
 - 开发语言
 - Python
 - peewee
copyright: true
---

第一次尝试翻译英语技术文档，比较具有挑战性。本来是计划和同事一起翻译，但是因为人事变故，只剩下我一个人在继续。如果您发现翻译有任何不当的地方，请及时地指正。如果你觉得文档翻译得还不错，对您有帮助，麻烦您点个赞或者给个好评。

截至译者翻译开始，peewee最新版本号为:2.10.1。英文文档传送门： [ 点此 ](http://peewee.readthedocs.io/en/latest/index.html) 。

更新: 日期 ~ 2020-10-07 ， 新版本为：3.13.3

## 安装 

{% tabs install %}
<!-- tab pip -->
大部分的用户想要通过pip简单的安装托管在PyPI的最新版本:

>$ pip install peewee

Peewee包含两个可以被编译的C扩展库：

* Speedups她包含通过Cython重新实施的各种各样方法，如果你安装了Cython那么她可以自动被添加到库。 
* Sqlite extensions她包含Cypthon

SQlite日期操作函数的实现，正则运算，和全文搜索排序算法。这个模块可以通过命令build_sqlite_ext添加。
<!-- endtab -->
<!-- tab git -->
这个项目托管在https://github.com/coleifer/peewee，所以你可以通过git安装:

>$ git clone https://github.com/coleifer/peewee.git
>$ cd peewee
>$ python setup.py install

如果你想在git checkout里添加SQLite extension，你可以运行

>$ python setup.py build_sqlite_ext -i

{: .box-info}

在一些系统上，你可能需要运行下面的命令来安装peewee
>$ sudo python setup.py install 。

<!-- endtab -->
{% endtabs %}

## 测试是否安装成功

你可以通过执行测试套件来测试你的安装是否正常。

>$ setup.py test  # 或者执行:python runtests.py

默认情况下，测试套件是通过SQLite来运行，而playhouse扩展测试却没有运行。要查看运行测试可用选项可以用过执行：

>$ python runtests.py --help

## 可选依赖关系

{: .box-info}

为使用peewee，你不需要任何额外的标准库，因为大部分的python发布版本都支持SQLite的编译。你可以通过在python控制台执行命令`import sqlite3`来测试。如果你想使用其他的数据库，有许多`DB-API 2.0-compatible`驱动，比如MySQL的`pymysql`和postgres的`psycopg2`。


* [Cypthon](http://cython.org/): 用于在使用SQLite时公开其他功能，并以高效的方式实现诸如搜索结果排名之类的功能。由于生成的C文件包含在软件包分发中，因此不再需要Cython使用C扩展名
* [apsw](https://github.com/rogerbinns/apsw): 可选的绑定SQLite第三方库，比标准库pysqlite具有更高的性能和更多更加清晰的语义，与`APSWDatabase`配合使用。
* [gevent](http://www.gevent.org/): `SqliteQueueDatabase`的可选依赖项（尽管它可以很好地与线程配合使用）
* [BerkeleyDB](http://www.oracle.com/technetwork/database/database-technologies/berkeleydb/downloads/index.html): 与peewee一起使用可以编译一个SQLite前端。编译可能很棘手，所以可以看[这里说明](http://charlesleifer.com/blog/updated-instructions-for-compiling-berkeleydb-with-sqlite-for-use-with-python/)。
* 最后，如果您使用Flask框架，则可以使用辅助程序扩展模块

## 关于SQLite扩展的说明

Peewee包括两个特定于SQLite的C扩展，这些扩展为SQLite数据库用户提供了附加功能并提高了性能。Peewee将尝试提前确定是否已安装SQLite3，并且仅当系统上有SQLite共享库时才构建SQLite扩展。

但是，如果在尝试安装Peewee时收到类似以下的错误，则可以通过设置NO_SQLITE环境变量来显式禁用SQLite C扩展的编译。

>fatal error: sqlite3.h: No such file or directory

显式禁用SQLite扩展的情况下安装Peewee的方法：

>$ NO_SQLITE = 1 python setup.py install
