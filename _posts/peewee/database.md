---
title: Peewee中文文档【六】：数据库管理
date: 2017-08-28 18:30:10
updated: 2017-08-28 18:30:10
tags: [peewee, Python, orm]
categories: 
 - 开发语言
 - Python
 - peewee
copyright: true
---

本章节介绍了如何使用Peewee执行与数据库相关的典型任务。在本文档中，我们将使用以下示例模型：

```python
from peewee import *

class User(Model):
    username = CharField(unique=True)

class Tweet(Model):
    user = ForeignKeyField(User, related_name='tweets')
    message = TextField()
    created_date = DateTimeField(default=datetime.datetime.now)
    is_published = BooleanField(default=True)
```

## 创建数据库连接和数据库表

虽然在使用数据库之前明确的连接它不是必须的，但明确的管理数据库连接是很好的做法。这样如果连接失败，则可以在连接步骤期间捕获异常，而不是稍候执行查询的任意时间。此外，如果您使用连接池，实际上有必要调用connect()和close()来确保连接被正常回收。

对于web应用，您通常会在启动请求时打开连接，并在发送响应时将其关闭：

```python
database = SqliteDatabase('my_app.db')

def before_request_handler():
    database.connect()

def after_request_handler():
    database.close()
```

{: .box-info}
有关配置多个流程web框架的连接钩子的示例，请参阅添加请求钩子部分。

有关高级连接管理技术，请参阅高级连接管理部分。
{% endnote %}  

为了将此数据库同您的模型一起使用，在内部Meta类设置database属性：

```python
class MyModel(Model):
    some_field = CharField()

    class Meta:
        database = database
```

**好习惯** ：定义一个基础模型指明你想用的数据库对象，然后所有你的模型都继承它：

```python
database = SqliteDatabase('my_app.db')

class BaseModel(Model):
    class Meta:
        database = database

class User(BaseModel):
    username = CharField()

class Tweet(BaseModel):
    user = ForeignKeyField(User, related_name='tweets')
    message = TextField()
    # etc, etc
```

{: .box-info} 
请记得在你的模型类里指定数据库，否则peewee将会使用默认名为’peewee.db’的数据库
{% endnote %}

### Vendor-specific参数

部分数据库驱动在被初始化的时候可以接收特殊参数。Peewee会传递一些无法识别的参数给数据库驱动，而不是容纳所有的这些参数。  
例如，通常在使用Postgresql创建连接时需要指定 ` host ` , ` user ` 和 ` password `
。这些都不是标准的peewee数据库参数，所以在创建连接时它们将会被传递给 ` psycopg2 ` :

```python
db = PostgresqlDatabase(
    'database_name',  # peewee需要的参数.
    user='postgres',  # 将会直接传递给psycopg2.
    password='secret',  # 同上.
    host='db.mysite.com',  # 同上.
)
```

另外的一个例子，pymysql数据库驱动可以接收 ` charset ` 参数，但是它不是标准的peewee数据库参数。为设置这个值，只需要将 ` charset ` 同其他值一起传递:

```python
db = MySQLDatabase('database_name', user='www-data',charset='utf8mb4')
```

有关可用参数，请参阅数据库驱动文档：

* Postgresql: [ psycopg2 ](http://initd.org/psycopg/docs/module.html#psycopg2.connect)
* MySQL: [ MySQLdb ](http://mysql-python.sourceforge.net/MySQLdb.html#some-mysql-examples)
* MySQL: [ pymysql ](https://github.com/PyMySQL/PyMySQL/blob/f08f01fe8a59e8acfb5f5add4a8fe874bec2a196/pymysql/connections.py#L494-L513)
* SQLite: [ sqlite3 ](https://docs.python.org/2/library/sqlite3.html#sqlite3.connect)
