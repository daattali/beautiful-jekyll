---
title: RabbitMQ常用命令和常见配置信息
date: 2017-11-03 14:58:30
updated: 2017-11-03 14:58:30
tags: ['erlang','rabbitmq','rabbitMQ命令']
categories: 
 - 中间件
 - RabbitMQ
---

## 一些基本的管理命令

- 一步启动Erlang node和Rabbit应用：

>$ ./rabbitmq-server

- 在后台启动Rabbit node：

>$ ./rabbitmq-server -detached

- 关闭整个节点（包括应用）：

>$ ./rabbitmqctl stop


### 怎样仅仅关闭应用而不关闭整个节点

因为rabbitmq-server一起启动了节点和应用，它预先设置RabbitMQ应用为standalone模式。要将一个节点加入到现有的集群中，你需要停止这个应用并将节点设置为原始状态，然后就为加入集群准备好了。如果使用./rabbitmqctl stop，应用和节点都将被关闭。所以，

- 仅仅关闭应用

>$ ./rabbitmqctl stop_app

- 启动应用

>$ ./rabbitmqctl start_app

## 管理

Rabbitmq服务器的主要通过rabbitmqctl和rabbimq-plugins两个工具来管理，以下是一些常用功能。

### 服务器启动与关闭

- 启动

>$ rabbitmq-server –detached

- 关闭

>$ rabbitmqctl stop

若单机有多个实例，则在rabbitmqctlh后加–n 指定名称

### 插件管理

- 开启某个插件
>$ rabbitmq-plugins enable xxx
- 关闭某个插件
>$ rabbitmq-plugins disable xxx

注意：重启服务器后生效。

### virtual_host管理

- 新建virtual_host
  
>$ rabbitmqctladd_vhost  xxx

- 撤销virtual_host

>$ rabbitmqctl  delete_vhost xxx

### 用户管理

- 新建用户
>$ rabbitmqctl add_user xxxpwd

- 删除用户
> rabbitmqctl delete_user xxx

- 改密码:
>$ rabbimqctlchange_password {username} {newpassword}

- 设置用户角色：
>$ rabbitmqctlset_user_tags {username} {tag ...}

Tag可以为 administrator,monitoring, management

### 权限管理

权限设置：set_permissions [-pvhostpath] {user} {conf} {write} {read}
|参数|释义|
|:---|:---|
|Vhostpath|Vhost路径|
|user|用户名|
|Conf |一个正则表达式match哪些配置资源能够被该用户访问|
|Write|一个正则表达式match哪些配置资源能够被该用户读|
|Read|一个正则表达式match哪些配置资源能够被该用户访问|

### 获取服务器状态信息

- 服务器状态：

>$ rabbitmqctl status

- 队列信息：

>$ rabbitmqctl list_queues[-p vhostpath] [queueinfoitem ...]

queueinfoitem可以为：name，durable，auto_delete，arguments，messages_ready，messages_unacknowledged，messages，consumers，memory

- Exchange信息：

>$ rabbitmqctllist_exchanges[-p vhostpath] [exchangeinfoitem ...]

exchangeinfoitem有：name，type，durable，auto_delete，internal，arguments.

- Binding信息：

>$ rabbitmqctllist_bindings[-p vhostpath] [bindinginfoitem ...]       

Bindinginfoitem有：source_name，source_kind，destination_name，destination_kind，routing_key，arguments

- Connection信息：

>$ rabbitmqctllist_connections [connectioninfoitem ...]

Connectioninfoitem有：recv_oct，recv_cnt，send_oct，send_cnt，send_pend等。

- Channel信息：

>$ rabbitmqctl  list_channels[channelinfoitem ...]

Channelinfoitem有consumer_count，messages_unacknowledged，messages_uncommitted，acks_uncommitted，messages_unconfirmed，prefetch_count，client_flow_blocked

部分内容参考自：http://blog.csdn.net/mlks_2008/article/details/18988301

## rabbitmq配置

一般情况下，RabbitMQ的默认配置就足够了。如果希望特殊设置的话，有两个途径：

### 环境变量的配置文件 

`rabbitmq-env.conf`，这个文件的位置是确定和不能改变的，位于：/etc/rabbitmq目录下（这个目录需要自己创建）。

```conf
RABBITMQ_NODE_PORT=                       //端口号
HOSTNAME=                                 //主机名
RABBITMQ_NODENAME=mq 
RABBITMQ_CONFIG_FILE=                     //配置文件的路径
RABBITMQ_MNESIA_BASE=/rabbitmq/data       //需要使用的MNESIA数据库的路径
RABBITMQ_LOG_BASE=/rabbitmq/log           //log的路径
RABBITMQ_PLUGINS_DIR=/rabbitmq/plugins    //插件的路径
```
具体的列表见：http://www.rabbitmq.com/configure.html#define-environment-variables

### 配置信息的配置文件 

`rabbitmq.config`，这是一个标准的erlang配置文件。它必须符合erlang配置文件的标准。它既有默认的目录，也可以在rabbitmq-env.conf文件中配置。

**注意：这两个文件默认是没有的，如果需要必须自己创建。**

文件的内容详见：http://www.rabbitmq.com/configure.html#config-items

文章转载自：[goalkiller](http://blog.csdn.net/tengdazhang770960436/article/details/50009849)
