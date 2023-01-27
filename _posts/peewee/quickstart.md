---
title: Peewee中文文档【二】：快速开始
date: 2017-07-06 10:52:21
updated: 2017-07-06 10:52:21
tags: [peewee, Python, orm]
categories:
 - 开发语言
 - Python
 - peewee
copyright: true
---

本文简要介绍了peewee的主要特性。本指南涵盖：

  * Model Definition - 模型定义 
  * Storing data - 数据存储 
  * Retrieving Data - 数据检索 

{: .box-info}
如果你想要一个更形象的例子，那么有一个更详细的教程，使用peewee和flask框架创建一个“twitter”风格的网络应用程序。


我强烈建议您打开一个交互式shell会话并运行代码，这样你会对输入查询更有感觉。

## 模型定义

模型类，字段实例和模型实例对应数据库概念：

事物  |  对应  
---|---  
模型类  |  数据库表  
字段实例  |  数据库表的列  
模型实例  |  数据据库表的行  
  
当使用peewee开始一个项目，通常最好通过定义一个或者多个模型类开始你的数据模型。

```python
from peewee import *
db = SqliteDatabase('people.db')

class Person(Model):

    name = CharField()
    birthday = DateField()
    is_relative = BooleanField() 
    class Meta:

        database = db #  这个模型使用 "people.db"数据库
```

{: .box-info}
请注意我们命名我们的模型为Person而不是People。这个惯例你应该遵守：虽然这张表包含许多people，我们总是使用单数形式命名该类。



有许多字段类型适合储存各种数据类型。peewee处理pythonic值与数据库值之间的转换，所以你可以在您的代码里放心使用python类。这会变得更加有趣，当你用外键建立两个模型之间的关系时。这在peewee很容易做到：

```python
class Pet(Model):

owner = ForeignKeyField(Person, related_name='pets')
name = CharField()
animal_type = CharField()

    class Meta:
        database = db # 这个模型使用"people.db"数据库
```
现在我们已经有了自己的模型，让我们连接数据库。虽然明确的打开数据库连接不是必须的，但这是一个很好的做法，因为它会立即显示数据库连接的任何错误，而不是稍候执行第一个查询时的任意时间。当你完成了（你的操作）后关闭连接也是很好的做法，例如：一个web应用在接收到请求后会打开连接，在发送了返回结果后会关闭连接。

>$ db.connect()

我们开始通过在数据库内创建表来存储数据。这会创建表包含适当的列，索引，序列和外键限制：

>$ db.create_tables([Person, Pet])

##  存储数据

让我们开始用一些人来填充数据库。我们将会使用save() 和create() 方法来添加和更新表的记录。

>$ from datetime import date
>$ uncle_bob = Person(name='Bob', birthday=date(1960, 1, 15), is_relative=True)
>$ uncle_bob.save() # bob 现在被存储在数据库内

1

{: .box-info}
当我们执行call()时，被修改行的数量会返回。



有也可以通过调用create()方法来添加一个人，它会返回一个类实例：

>$ grandma = Person.create(name='Grandma', birthday=date(1935, 3, 1), is_relative=True)
>$ herb = Person.create(name='Herb', birthday=date(1950, 5, 5), is_relative=False)

想要更新一行，请修改模型实例并调用save()来保存更改。下面我们将要修改Grandma的名字并将修改保存在数据库：

>$ grandma.name = 'Grandma L.'
    
>$ grandma.save()  #  在数据库更新Grandma的名字
    
1

现在我们已经存储了三个人在数据库里，让我们给他们一些宠物。Grandma不喜欢在家里养动物，所以她一个也没有，但是Herb是一个动物爱好者：

>$ bob_kitty = Pet.create(owner=uncle_bob, name='Kitty', animal_type='cat')
>$ herb_fido = Pet.create(owner=herb, name='Fido', animal_type='dog')
>$ herb_mittens = Pet.create(owner=herb, name='Mittens', animal_type='cat')
>$ herb_mittens_jr = Pet.create(owner=herb, name='Mittens Jr', animal_type='cat')

经过漫长的一生，Mittens生病并且死去。我们需要将它从数据库中删除：

>$ herb_mittens.delete_instance()
    
1

{: .box-info}
delete_instance()返回值是数据库删除的行数



Bob叔叔发现太多的动物死在了Herb家，所以他领养了Fido：


>$ herb_fido.owner = uncle_bob
>$ herb_fido.save()
>$ bob_fido = herb_fido # 为了更清晰重命名我们的变量

## 数据检索

我们的数据库真正的实力在于如何让我们通过查询来检索数据。关系数据库非常适合进行临时查询。

### 获取单条记录

让我们从数据库来检索Grandma的记录。为了从数据库获取单条记录，使用SelectQuery.get():

>$ grandma = Person.select().where(Person.name == 'Grandma L.').get()

我们也可以使用等效的简写Model.get():

>$ grandma = Person.get(Person.name == 'Grandma L.')

### 记录列表

让我们列出表内的所有人:

>$for person in Person.select():
...     print person.name, person.is_relative
...
Bob True
Grandma L. True
Herb False

让我们列出所有的猫和他们的主人的名字:

>$ query = Pet.select().where(Pet.animal_type == 'cat')
>$ for pet in query:
...     print pet.name, pet.owner.name
...
Kitty Bob
Mittens Jr Herb

上面的查询有一个很大的问题：因为我们访问了pet.owner.name但是我们没有在原始的查询里选择这个值，所以peewee将不得不执行一个额外的查询来检索宠物的主人。这种行为被称为N+1，通常应该被避免。

我们可以通过选择Pet和Person并且添加一个join来避免额外的查询。

>$ query = (Pet
...          .select(Pet, Person)
...          .join(Person)
...          .where(Pet.animal_type == 'cat'))
>$ for pet in query:
...     print pet.name, pet.owner.name
...
Kitty Bob
Mittens Jr Herb

让我们获取到Bob所有的宠物：

>$ for pet in Pet.select().join(Person).where(Person.name == 'Bob'):
...     print pet.name
...
Kitty
Fido

我们可以在这儿做另外一件很酷的事来获取Bob的宠物。因为我们已经有一个对象来代表Bob，我们可以这样做：

>$ for pet in Pet.select().where(Pet.owner == uncle_bob):
...     print pet.name

我们通过添加一个order_by子句来确保这些按照字母顺利排列:


>$ for pet in Pet.select().where(Pet.owner == uncle_bob).order_by(Pet.name):
...     print pet.name
...
Fido
Kitty

我们列出所有的人，从年轻到年长：

>$ for person in Person.select().order_by(Person.birthday.desc()):
...     print person.name, person.birthday
...
Bob 1960-01-15
Herb 1950-05-05
Grandma L. 1935-03-01

我们列出所有人和他们宠物的一些信息：

>$ for person in Person.select():
...     print person.name, person.pets.count(), 'pets'
...     for pet in person.pets:
...         print '    ', pet.name, pet.animal_type
...
Bob 2 pets
    Kitty cat
    Fido dog
Grandma L. 0 pets
Herb 1 pets
Mittens Jr cat

我们再次遇到N+1查询行为的典型例子。我们可以通过执行join并聚合记录来避免这种情况：

>$ subquery = Pet.select(fn.COUNT(Pet.id)).where(Pet.owner == Person.id)
>$ query = (Person
...          .select(Person, Pet, subquery.alias('pet_count'))
...          .join(Pet, JOIN.LEFT_OUTER)
...          .order_by(Person.name)) 

>$ for person in query.aggregate_rows():  # 注意 `aggregate_rows()`的调用.
...     print person.name, person.pet_count, 'pets'
...     for pet in person.pets:
...         print '    ', pet.name, pet.animal_type
...
Bob 2 pets
        Kitty cat
        Fido dog
Grandma L. 0 pets
Herb 1 pets
        Mittens Jr cat

即使我们分别创建了子查询，但是实际上只有一个查询被执行。

最后，我们做一次复杂的查询。获取生日不满足下列条件的人：

* 在1940年前（grandma） 
* 在1959年后（bob） 

>$ d1940 = date(1940, 1, 1)
>$ d1960 = date(1960, 1, 1)
>$ query = (Person
...          .select()
...          .where((Person.birthday < d1940) | (Person.birthday > d1960)))
...
>$ for person in query:
...     print person.name, person.birthday
...
Bob 1960-01-15
Grandma L. 1935-03-01

我们做一个相反的查询，这些人的生日在1940年到1960年之间：

>$ query = (Person
...          .select()
...          .where((Person.birthday > d1940) & (Person.birthday < d1960)))
...
>$ for person in query:
...     print person.name, person.birthday
...
Herb 1950-05-05

最后一个查询。将使用sql函数来查找名字首字母以大写G或者小写g开头的人：

>$ expression = (fn.Lower(fn.Substr(Person.name, 1, 1)) == 'g')
>$ for person in Person.select().where(expression):
...     print person.name
...
Grandma L.

我们完成了数据库操作，让我们来关闭连接：

>$ db.close()

这些仅仅是基础，你可以根据需要使你的查询变得复杂。

所有的其他sql子句也可以用。例如：

* group_by() 
* having() 
* limit() and offset() 

查看有关查询（译者注：第八章）的文档以获取更多信息。

## 使用现有数据库

如果你已经有一个数据库，你可以通过使用一个模型生成器pwiz来自动生成peewee模型。例如，如果我拥有一个名字叫做charles_blog的postgresql数据库，我可以这样执行：

>$ python -m pwiz -e postgresql charles_blog > blog_models.py

## 接下来

这是快速开始。如果你想查看一个完整的web应用，请查看 [ 应用实例 ](https://www.nothinghere.cn/peewee/example-app/) 。
