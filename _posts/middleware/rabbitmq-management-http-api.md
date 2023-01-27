---
title: RabbitMQ Management HTTP API 译文
date: 2018-08-16 18:28:00
updated: 2018-08-16 18:28:00
tags: ['rabbitMQ api']
categories: 
 - 中间件
 - RabbitMQ
---

# 介绍

除了此帮助页面之外，所有URIs都只提供application/json类型的资源，并且需要HTTP基本身份验证（使用标准rabbitMQ用户数据库）。默认用户是guest/guest。

许多URIs需要虚拟主机的名字作为路径的一部分，因为名字只能唯一地标识虚拟主机中的对象。由于默认虚拟主机名为“/”，因此需要将其编码为“%2f”。

PUTing资源然后创建它，你发送的json对象必须包含某些必填的keys(如下文档)和其他可选的keys，其他的keys会被忽略。未传入必填keys会导致错误发生。

由于绑定在AMQP中没有名称或者id，所有我们根据它的所有属性来合成绑定。由于在一般情况下很难预测这个名称，您还可以通过POSTing到工厂URI来创建绑定。请看下面的示例。

需要URIs返回的是数组。然后URIs可以添加`sort`和`sort_reverse`查询参数。`sort`允许你选择一个主键来排序，`sort_reverse`会在设置为true时倒序排序。排序参数可以包含由点分格的子字段，这便允许您按照列表项的嵌套参数来进行排序，但不允许您使用多字段排序。请看下面的示例。

您还可以使用列参数限制每个项返回的信息，这是一个用逗号分隔的子字段列表，由点分隔。请看下面的示例。

大部分GET查询返回每个对象的多个字段。具体请查看 http://ip:port/doc/stats.html (译者注：将ip,port换成rabbitMQ对应的)

# 示例

一些用于windows和unix的简单示例，使用命令行工具`curl`:

- 获取虚拟主机列表

{% tabs host-list %}
<!-- tab Windows -->
>$ curl -i -u guest:guest http://localhost:15672/api/vhosts
<!-- endtab -->
<!-- tab Unix -->
>$ curl -i -u guest:guest http://localhost:15672/api/vhosts
<!-- endtab -->
{% endtabs %}

>HTTP/1.1 200 OK
Server: MochiWeb/1.1 WebMachine/1.10.0 (never breaks eye contact)
Date: Mon, 16 Sep 2013 12:00:02 GMT
Content-Type: application/json
Content-Length: 30

>[{"name":"/","tracing":false}]

- 获取channels列表，越早发布越前展示，限制信息项如下：

{% tabs channels-list %}
<!-- tab Windows -->
>$ curl -i -u guest:guest "http://localhost:15672/api/channels?sort=message_stats.publish_details.rate&sort_reverse=true&columns=name,message_stats.publish_details.rate,message_stats.deliver_get_details.rate"
<!-- endtab -->
<!-- tab Unix -->
>$ curl -i -u guest:guest 'http://localhost:15672/api/channels?sort=message_stats.publish_details.rate&sort_reverse=true&columns=name,message_stats.publish_details.rate,message_stats.deliver_get_details.rate'
<!-- endtab -->
{% endtabs %}

>HTTP/1.1 200 OK
Server: MochiWeb/1.1 WebMachine/1.10.0 (never breaks eye contact)
Date: Mon, 16 Sep 2013 12:01:17 GMT
Content-Type: application/json
Content-Length: 219
Cache-Control: no-cache

>[{"message_stats":{"publish_details":{"rate" ... (remainder elided)

- 创建新的虚拟主机

{% tabs vhost-list %}
<!-- tab Windows -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XPUT http://localhost:15672/api/vhosts/foo
<!-- endtab -->
<!-- tab Unix -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XPUT http://localhost:15672/api/vhosts/foo
<!-- endtab -->
{% endtabs %}

>HTTP/1.1 204 No Content
Server: MochiWeb/1.1 WebMachine/1.10.0 (never breaks eye contact)
Date: Mon, 16 Sep 2013 12:03:00 GMT
Content-Type: application/json
Content-Length: 0

{% note info %} 
备注：您必须指定`application/json`作为mime类型；
备注：在上传的json对象中不需要对象的名称，因为它被包含在URIs里。作为虚拟主机除了名字无其他属性，这意味着您完全不需要指定请求body。
{% endnote %}

- 在默认虚拟主机创建新的exchange:

{% tabs vhost-list %}
<!-- tab Windows -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XPUT -d"{""type"":""direct"",""durable"":true}" http://localhost:15672/api/exchanges/%2f/my-new-exchange
<!-- endtab -->
<!-- tab Unix -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XPUT -d'{"type":"direct","durable":true}' http://localhost:15672/api/exchanges/%2f/my-new-exchange
<!-- endtab -->
{% endtabs %}

>HTTP/1.1 204 No Content
Server: MochiWeb/1.1 WebMachine/1.10.0 (never breaks eye contact)
Date: Mon, 16 Sep 2013 12:04:00 GMT
Content-Type: application/json
Content-Length: 0

- 删除exchange：

{% tabs host-list %}
<!-- tab Windows -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XDELETE http://localhost:15672/api/exchanges/%2f/my-new-exchange
<!-- endtab -->
<!-- tab Unix -->
>$ curl -i -u guest:guest -H "content-type:application/json" -XDELETE http://localhost:15672/api/exchanges/%2f/my-new-exchange
<!-- endtab -->
{% endtabs %}

>HTTP/1.1 204 No Content
Server: MochiWeb/1.1 WebMachine/1.10.0 (never breaks eye contact)
Date: Mon, 16 Sep 2013 12:05:30 GMT
Content-Type: application/json
Content-Length: 0

# 参考
{% note info %} 
译者注：路径列标红的字段表示需要传入对应的数据
{% endnote %}

|GET|PUT|DELETE|POST|路径|描述|
|x|-|-|-|/api/overview|描述整个系统的各种信息|
|x|x|-|-|/api/cluster-name|rabbitMQ集群的名字|
|x|-|-|-|/api/nodes|rabbitMQ集群节点列表|
|x|-|-|-|/api/nodes/name|rabbitMQ集群指定节点，添加'?memory=true'获取内存统计信息|
|x|-|-|-|/api/extensions|扩展插件管理列表|
|x|-|-|x|/api/definitions/api/all-configuration (已弃用)|服务定义 - exchanges，queues，绑定关系，用户，虚拟主机，权限管理和参数。所有一切除了messages(译者注：消息体)。Post以上传已存在的定义集合。注意：- 所有的定义都被合并，任何已存在的定义都不可被修改- 冲突会导致错误- 发生错误时，您将得到部分定义集,为了方便，您可以通过浏览器上传文件到这个URI(比如您可以使用multipart/form-data或application/json)，这个情况下，可以以form字段名为'file'的文件来上传|
|x|-|-|-|/api/connections|所有开放的连接列表|
|x|-|x|-|/api/connections/name|具体的连接。DELETEing会关闭此连接，可选的头'X-Reason'在删除时提供原因|
|x|-|-|-|/api/connections/name/channels|列出次连接对应的channels|
|x|-|-|-|/api/channels|所有开放channels列表|
|x|-|-|-|/api/channels/channel|具体channel信息|
|x|-|-|-|/api/exchanges|所有exchange列表|
|x|-|-|-|/api/exchanges/vhost|指定虚拟主机的所有exchange列表|
|x|x|x|-|/api/exchanges/vhost/name|指定虚拟主机的exchange. PUT以新增exchange，你需要以下参数：{"type":"direct","auto_delete":false,"durable":true,"internal":false,"arguments":[]}type必填，其他可选|
|x|-|-|-|/api/exchanges/vhost/name/bindings/source|以此作为来源exchange的绑定列表|
|x|-|-|-|/api/exchanges/vhost/name/bindings/destination|以此作为目的地exchange的绑定列表|
|-|-|-|x|/api/exchanges/vhost/name/publish|给此队列发消息，需要以下body：{"properties":{},"routing_key":"my key","payload":"my body","payload_encoding":"string"}所有的key都是必填，payload_encoding key可以是'string'(payload将以utf-8编码)或者'base64'(payload将以base64编码)如果消息发送成功，返回如下:{"routed": true}若消息发送至少一个队列成功则routed将会是true。请注意，HTTP API中的发布/获取路径用于注入测试消息、诊断信息等——它们没有实现可靠的传递，因此应该将其视为系统管理员的工具，而不是用于消息传递的通用API。 |
|x|-|-|-|/api/queues|所有queues列表|
|x|-|-|-|/api/queues/vhost|指定虚拟主机的所有queue列表|
|x|-|-|-|/api/queues/vhost/name|指定虚拟主机指定队列名具体信息。为PUT新增队列，您可以使用:{"auto_delete":false,"durable":true,"arguments":[],"node":"rabbit@smacmullen"}。所有keys都是可选|
|x|-|-|-|/api/queues/vhost/name/bindings|指定队列的绑定关系列表|
|-|-|x|-|/api/queues/vhost/name/contents|删除指定队列的所有消息，注意您不可以使用GET方式|
|-|-|-|x|/api/queues/vhost/name/actions|对应队列的操作，POST消息如下:{"action":"sync"}目前支持的操作有sync和cancel_sync|
|-|-|-|x|/api/queues/vhost/name/get|获取队列的消息。(这不同于HTTP GET因为会改变队列的状态)有可以POST消息如下:{"count":5,"requeue":true,"encoding":"auto","truncate":50000}count 获取队列消息的最大数量，若队列无法立即提供他们，则您将获取比期望少的消息requeue 指定是否将消息移除队列，如果requeue是true,则消息将被重新分配，但是这些消息的redeliverd标志将被设置encoding 必须是"auto"(payload若可以utf-8编码则已string返回，否则已base64编码)或者"base64"(payload始终以base64编码)如果truncate传入，则消息大小大于给出数值时，消息将被截断truncate是可选，其他都是必填.请注意，HTTP API中的发布/获取路径用于注入测试消息、诊断信息等——它们没有实现可靠的传递，因此应该将其视为系统管理员的工具，而不是用于消息传递的通用API。 |
|x|-|-|-|/api/bindings|所有的绑定关系列表|
|x|-|-|-|/api/bindings/vhost|指定虚拟主机的绑定关系列表|
|x|-|-|x|/api/bindings/vhost/e/exchange/q/queue|exchange和queue之间的绑定关系，记住，一个exchange和一个queue可以绑定多次。为创建新的绑定关系，POST这个URI，您需要传入以下body:{"routing_key":"my_routing_key","arguments":[]}所有keys都是可选的，返回的header会包含Location告诉您新绑定的URI|
|x|-|x|-|/api/bindings/vhost/e/exchange/q/queue/props|exchange和queue之间某个指定的绑定属性。URIs里的props部分是由routing key和参数hash值组成的绑定名称|
|x|-|-|x|/api/bindings/vhost/e/source/e/destination|两个exchange之间的绑定关系，类似于上述exchange和queue的绑定关系列表|
|x|-|x|-|/api/bindings/vhost/e/source/e/destination/props|两个exchange之间某个指定的绑定属性，类似于上述exchange和queue的绑定关系列表|
|x|-|-|-|/api/vhosts|所有的虚拟主机列表|
|x|x|x|-|/api/vhosts/name|某个指定的虚拟主机。因为一个虚拟主机只能有一个名字，所以使用PUT方式新增时不需要传入body. 为打开/关闭tracing，传入以下参数:{"tracing":true}|
|x|-|-|-|/api/vhosts/name/permissions|给出虚拟主机的权限|
|x|-|-|-|/api/users|所有的角色列表|
|x|x|x|-|/api/users/name|查询某个特定的用户，为新增用户，使用PUT时需要传入以下参数:{"password":"secret","tags":"administrator"} 或者 {"password_hash":"2lmoth8l4H0DViLaK9Fxi6l9ds8=", "tags":"administrator"}tags字段必填，password或者password_hash其一必传。设置password_hash为""会使得此用户登陆无需输入密码。tags是以逗号分割的用户标签。目前可识别的是tags有administrator,monitoring和management |
|x|-|-|-|/api/users/user/permissions|此用户的所有权限列表|
|x|-|-|-|/api/whoami|当前认证用户的所有信息|
|x|-|-|-|/api/permissions/vhost/user|指定用户在虚拟主机的权限。使用PUT新增权限，您需要传入以下参数:{"configure":".","write":".","read":".*"}所有参数都是必填|
|x|-|-|-|/api/parameters|所有参数列表|
|x|-|-|-|/api/parameters/component|某组件的参数列表|
|x|-|-|-|/api/parameters/component/vhost|指定虚拟主机组件的参数列表|
|x|x|x|-|/api/parameters/component/vhost/name|指定参数。为新增参数，使用PUT时需要传入以下参数：{"vhost": "/","component":"federation","name":"local_username","value":"guest"} |
|x|-|-|-|/api/policies|所有policie列表|
|x|-|-|-|/api/policies/vhost|指定虚拟主机的policie列表|
|x|x|x|-|/api/policies/vhost/name|指定的policie名信息，为新增policie，使用PUT时需要传入以下参数:{"pattern":"^amq.", "definition": {"federation-upstream-set":"all"}, "priority":0, "apply-to": "all"}pattern 和 definition 必填, priority 和 apply-to 可选.|
|x|-|-|-|/api/aliveness-test/vhost|申请一个测试队列，然后发布和消费消息。用于监控工具。如果一切正常工作，将会返回200状态码和对应body:{"status":"ok"},注意:测试队列将不会被删除(以防止在重复执行此操作时出现队列丢失)。|
