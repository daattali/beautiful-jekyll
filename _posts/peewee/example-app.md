---
title: Peewee中文文档【三】：应用实例
date: 2017-07-06 11:22:02
updated: 2017-07-06 11:22:02
tags: [peewee, python, orm]
categories: 
 - 开发语言
 - Python
 - peewee
copyright: true
---

我们创建了一个类twitter的站点。这个app的源码可以在examples/twitter文件夹找到。或者你也可以通过访问此app的 [ github地址 ](https://github.com/coleifer/peewee/tree/master/examples/twitter)
来查看源码。另外还有一个博客应用的例子可能更合你的胃口。

这个应用例子使用了非常容易入门的flask框架。如果你没有安装flask，你需要执行下面的命令来安装使用flask：

>$ pip install flask

## 运行示例

![这里写图片描述](https://img-blog.csdn.net/20170706110746526)

在确认flask安装成功后，cd命令进入到twitter应用文件夹然后执行脚本：

>$ python run_example.py

这个站点可以通过地址： `http://localhost:5000/` 访问

##  深入代码

为了简单起见，所有实例代码都被包含在单个模块中:examples/twitter/app.py.有关peewee构建更大flask应用程序的指南，请查看结构化Flask[ 应用程序 ](http://charlesleifer.com/blog/structuring-flask-apps-a-how-to-for-those-coming-from-django/) 。

###  模型

在流行的web框架django的精神下，peewee使用声明式模型定义。如果你不熟悉django，那么这个想法是你为每个表声明一个模型类，然后模型类定义一个或者多个对应与表的列的字段属性。对类twitter应用而言，她只有三个模型：

**User:**  
它代表一个账户，储存用户名和密码，用来当作唯一标识符的电子邮件地址和指明账户创建时间的日期字段。  
**Relationship:**  
它是一个实用模型，包含关联User模型和关注信息的两个外键。  
**Message:**  
类似于推文。Message模型包含推文内容，发表时间，发送人（User表外键）。

如果你喜欢UML（译者注：Unified Modeling Language 标准建模语言），下面是表格和对应关系：

![这里写图片描述](https://img-blog.csdn.net/20170706111116795)

为了创建这些模型，我们需要实例化SqliteDatabase对象。然后我们定义我们的模型类，并将列指定为类的Field实例。

```python
# 创建一个peewee数据库实例 - 我们的模型将使用这个数据库来保存信息
database = SqliteDatabase(DATABASE)

# 模型定义 - 标准“模式”是定义一个基础模型类，它指定要使用哪个数据库。
# 然后任何子类将自动地使用正确的存储。
class BaseModel(Model):
    class Meta:
        database = database

# 这个User模型以声明式指定其字段（或列），就像django。
class User(BaseModel):
    username = CharField(unique=True)
    password = CharField()
    email = CharField()
    join_date = DateTimeField()

    class Meta:
        order_by = ('username',)

# 这个模型包含User表的两个外键 - 它本质上允许我们在用户之间创建多对多的关系。
# 通过联结不同的字段查询，我们可以看出用户关注了谁和谁关注了此用户。
class Relationship(BaseModel):
    from_user = ForeignKeyField(User, related_name='relationships')
    to_user = ForeignKeyField(User, related_name='related_to')

    class Meta:
        indexes = (
            # 在from-user/to-user指定唯一的多列索引.
            (('from_user', 'to_user'), True),
        )

# 一个绝对简单的一对多关系:一个用户有0或者n条信息，通过外键暴露。
# 因为我们没有指定，所以用户的信息将作为特殊属性User.message_set访问。
class Message(BaseModel):
    user = ForeignKeyField(User)
    content = TextField()
    pub_date = DateTimeField()

    class Meta:
        order_by = ('-pub_date',)
```

{: .box-info}
我们创建一个简单地定义将要使用的数据库的BaseModel类。所有其他继承这个类的Models都将使用这个正确的数据库连接。



Peewee支持许多不同的字段类型，它们对应数据库引擎普遍支持的不同列类型。  
在python类型与数据库用使用的类型之间的转换是透明的，允许你在你的应用里使用下列类型：

* String(unicode或者其他) 
* Integers，floats，Decimal numbers 
* Boolean值 
* Dates，times和datetimes 
* None（NULL） 
* Binary data 

### 创建表

为了开始使用models，我们需要先创建表。这是一次性操作，可以通过交互解释器快速的完成。我们可以创建一个小的帮助函数来完成这一点：

```python
def create_table():
    database.connect()
    database.create_tables([User,Relationship,Message])
```

在实例应用旁的文件夹打开python shell，然后执行下列命令：

>$ from app import *
>$ create_tables()



{: .box-info} 
如果你遇到ImportError，表示你flask和peewee都没有安装或者安装不正确。点击 [ 安装与测试 ](https://www.nothinghere.cn/peewee/installation/)



每一个Model都有一个create_table()类方法，它在数据库里运行 create
Table的SQL语句。这个方法会创建表，包括所有的字段，外键约束，索引和序列。通常你只需要做一次，然后一个新的model就新增成功了。

Peewee提供了一个有用的方法Databse.creata_tables(),它解决了model之间的相互依赖，并在各自的model上调用create_table()方法。


{: .box-info}

创建表后添加字段将要求你删除表并重新创建表，或者使用ALTER TABLE查询手动添加列。  
或者，你可以通过python使用schema migrations（参考章节schema migrations）扩展来修改你的数据库模式。

你也可以使用database.create_tables([User, …], True)，这样peewee就会在你创建表之前先检查表是否已存在。



### 建立数据库连接

你可能已经注意到上述Model代码中，类是基于名为Meta的基础模型来设置数据库属性。Peewee允许每一个model指定它使用的数据库。你可以指定许多Meta选项来控制模型的行为。  
下面是一个peewee习惯:

```python
DATABASE = 'tweeoee.db'
# 创建一个数据库实例，可以管理连接和执行查询
databse=SqliteDatabase(DATABASE, threadlocals= True)
```
当在开发一个web应用的时候，通常情况下都开在请求开始的时候打开连接，在返回了结果的时候关闭连接。你应该始终明确地管理你的连接。举例来说：假如你使用连接池，那么只有在你调用connect()和close()方法的时候连接才会正确的回收。

我们会告诉flask，在请求响应周期内，我们需要创建一个数据库连接。Flask提供了一些方便的装饰器来达到这一点：

```python
@app.before_request
def before_request():
    database.connect()

@app.after_request
def after_request(response):
    database.close()
    return response
```

{: .box-info}

Peewee使用线程本地存储来管理连接状态，所以该模式可以与多线程WSGI服务器一起使用。



### 进行查询

在用户模型里有一些实例方法封装了一些用户特定的功能：

* following():这个用户关注了谁？
* followers():谁关注了这个用户？

这些方法的实现很相似，但是在sql的JOIN和WHERE子句内有很重要的区别。

```python
def following(self):
    # 通过Relationship表查询其他用户
    return (User
            .select()
            .join(Relationship, on=Relationship.to_user)
            .where(Relationship.from_user == self))

def followers(self):
    return (User
            .select()
            .join(Relationship, on=Relationship.from_user)
            .where(Relationship.to_user == self))
```

### 创建新的对象

当一个新的用户想加入站点时，我们需要确保用户的用户名是可用的才创建一条新的User记录。查看join()视图，我们可以看到我们的应用尝试通过Model.create()来创建新的用户。我们唯一约束定义了User.username字段，所以如果这个用户名已经被使用，会引发一个IntegrityError.

```python
try:
    with database.transaction():
        # 尝试创建用户，因为唯一性约束，如果用户名已被使用，则数据库会引发
        # 一个IntegrityError.
        user = User.create(
            username=request.form['username'],
            password=md5(request.form['password']).hexdigest(),
            email=request.form['email'],
            join_date=datetime.datetime.now()
        )

    # 通过设置会话变量来将用户标记为“已验证”
    auth_user(user)
    return redirect(url_for('homepage'))

except IntegrityError:
    flash('That username is already taken')
```

当用户想要关注谁的时候，我们使用相同的方法。为表示关注关系，我们在Relationship表创建一行来指出谁关注了谁。因为在from_user和to_user有唯一索引，所以我们可以确保不会以相同的行结束：

```python
user = get_object_or_404(User, username=username)
try:
    with database.transaction():
        Relationship.create(
            from_user=get_current_user(),
            to_user=user)
    except IntegrityError:
        pass
```

### 执行子查询

如果你已经登陆且在twitter主页，你可以看到你关注的人发送的推文。为了实现这一点，我们可以使用一个子查询：

```python
message = Message.select().where(Message.user << user.following())
```

这些代码对应下列的SQL查询语句：

```sql
SELECT t1."id", t1."user_id", t1."content", t1."pub_date"
FROM "message" AS t1
WHERE t1."user_id" IN (
    SELECT t2."id"
    FROM "user" AS t2
    INNER JOIN "relationship" AS t3
        ON t2."id" = t3."to_user_id"
    WHERE t3."from_user_id" = ?
)
```

### 其他有趣的主题

示例app内还有一些其他巧妙的东西，值得一提。

支持结果分页是在一个名为object_list的简单函数（在Django中被推论后）实现的。该函数由返回对象列表的所有视图使用。 

```python
def object_list(template_name, qr, var_name='object_list', **kwargs):
    kwargs.update(
        page=int(request.args.get('page', 1)),
        pages=qr.count() / 20 + 1 )
    kwargs[var_name] = qr.paginate(kwargs['page'])
    return render_template(template_name, **kwargs)
```

简单的身份验证系统使用login_required装饰器。第一个函数在用户成功登陆的时候简单的添加了用户的数据到目前的会话里。装饰器login_required可以用于包装视图函数，检查会话是否被验证如果没有重定向到登陆页面。

```python
def auth_user(user):
    session['logged_in'] = True
    session['user'] = user
    session['username'] = user.username
    flash('You are logged in as %s' % (user.username))

def login_required(f):
    @wraps(f)
    def inner(*args, **kwargs):
        if not session.get('logged_in'):
            return redirect(url_for('login'))
        return f(*args, **kwargs)
return inner
```
  
返回404响应而不是在数据库找不到对象时抛出异常。

```python
def get_object_or_404(model, *expressions):
    try:
        return model.get(*expressions)
    except model.DoesNotExist:
        abort(404)
```

## 更多例子

在peewee [ 示例文件 ](https://github.com/coleifer/peewee/blob/master/examples/)内有许多示例，包括：

* 使用flask和peewee框架开发的blog [ 应用示例 ](https://github.com/coleifer/peewee/tree/master/examples/blog) ，也可以看 [ 这里 ](http://charlesleifer.com/blog/how-to-make-a-flask-blog-in-one-hour-or-less/) 。 

* 一个加密的 [ 命令行日记 ](https://github.com/coleifer/peewee/blob/master/examples/diary.py) ，这里是你可能会喜欢的随附 [ 博文 ](http://charlesleifer.com/blog/dear-diary-an-encrypted-command-line-diary-with-python/) 。 

* web服务分析工具（有点象精简版的Google Analytics），请查看随附的 [ 博文 ](http://charlesleifer.com/blog/saturday-morning-hacks-building-an-analytics-app-with-flask/) 。

{: .box-info}

喜欢这些代码片段，还想看更多吗？检出[flask-peewee](https://github.com/coleifer/flask-peewee)，一个flask插件，为你的peewee模型提供类似django管理员的接口，RESTfull api，身份验证或者更多。


