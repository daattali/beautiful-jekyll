---
title: kafka-java客户端连接报错解决方案
date: 2019-04-13 15:19:00
updated: 2019-04-13 15:19:00
tags: ['kafka','java客户端']
categories: 
 - 开发语言
 - Java
---


第一次使用kafka，对他还不是很熟悉。然后在使用java发送消息的时候，一直报错，报错信息如下：

	Can't resolve address hostname:9092


## 解决历程

贴代码, 代码取之于kafka官网示例

```java
package com.amos.learn.util;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.junit.Test;

import java.util.Properties;

public class KafkaUtil {

    @Test
    public void sendKafka() {

        Properties props = new Properties();
        props.put("bootstrap.servers", "192.168.102.87:9092");
        props.put("acks", "all");
        props.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        props.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");

        Producer<String, String> producer = new KafkaProducer<>(props);
        for (int i = 0; i < 1; i++) {
            producer.send(new ProducerRecord<>("your_topic", Integer.toString(i), Integer.toString(i)));
        }
        producer.close();
    }

}

```

执行该代码一直报错，也就是发送不成。

解决步骤：

1. 我首先想到了是不是我本地没有访问不到该IP/端口
（`还是太幼稚，根本不应该这么想！` 为什么呢 ？ 结合代码里的kafka配置和报错日志来看，代码里面填写的ip:host，但是呢，报错信息里面却是kafka 服务器的hostname，所以可以断定，客户端代码已经连接到kafka服务器了，要不然它怎么知道`hostname`的呢 ? 当然这是后话了。 ）

打开cmd命令面板，依次输入
>$ ping 192.168.102.87
>$ telnet 192.168.102.87 9092

都可以正常ping通/telnet通

2. 代码有问题? 
可是，我是从官网取的代码！ 暂时排除该可能性

3. maven包有问题 / 有冲突?
可能性不大， 日志也没有包含相应的提示

4. 猜不出答案，google一下

[kafka-api-java-io-ioexception](https://stackoverflow.com/questions/44542328/kafka-api-java-io-ioexception-cant-resolve-address-xxx-x-x-xx9091)

修改本机的hosts文件，我的是windows系统，`C:\Windows\System32\drivers\etc\hosts`，在最末尾添加一行：

>192.168.102.87 your_kafka_hostname

注意：请修改为对应的服务器主机名。

然后再执行代码，发送成功。
