---
title: Java简单入门【对比Python】Part1.POST表单请求
date: 2018-01-20 02:12:27
tags: ['Java','JavaPost','Java表单','Python表单','Fluent Post']
categories: 
 - 开发语言
 - Java
---

# 啰嗦一下

之所以现在学习编程越来越容易，因为咱们都是踩在巨人的肩膀上。所以咱们在学习的过程中**慢慢**成长为巨人，也有必要让其他人**快速**成长起来。

# Post表单例子

咱们拿百度获取access token的例子，详情见这里[百度文档](http://ai.baidu.com/docs#/Auth/top%E3%80%82)



**请求URL数据格式**

向授权服务地址`https://aip.baidubce.com/oauth/2.0/token`发送请求（推荐使用POST），并在URL中带上以下参数：

- grant_type： 必须参数，固定为client_credentials；
- client_id： 必须参数，应用的API Key；
- client_secret： 必须参数，应用的Secret Key；

OK，咱们就使用POST方式来获取token，let's go！！！

# Postman请求

这些参数是私人的，所以打码了，希望理解。
![postman请求表单实例](http://img.blog.csdn.net/20180120021448413?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYW1vc2Nu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

# Python请求

咱们使用py超好用的模块requests，详细内容大家可以自行谷歌一下，蛮强大的，个人极力推荐。

```python
# coding:utf-8

import requests

def bd_token():
    url = 'https://aip.baidubce.com/oauth/2.0/token'
    # 这些字段的值我已经改了，复制这段代码请求不会正常返回
    body = {'client_id': 'dGL7SgioYB4LsZnG9EnsCxxx',
            'client_secret': 'BtZOxfurI47joml87nc1KMyB1hEmexxx',
            'grant_type':'client_credentials'}

    response = requests.post(url=url,
                             headers={"content-type": "application/x-www-form-urlencoded; charset=utf-8"},
                             data=body).content
    return response

if __name__ == "__main__":
    print(bytes.decode(bd_token()))
```

# Java请求

咱们使用Java的Fluent API来完成Java的Post表单请求，公司推荐的，个人还在学习当中。

首先需要先引入maven包，pom.xml添加以下依赖：

```xml
<!-- https://mvnrepository.com/artifact/org.apache.httpcomponents/httpclient -->
<dependency>
    <groupId>org.apache.httpcomponents</groupId>
    <artifactId>fluent-hc</artifactId>
    <version>4.5.4</version>
</dependency>
```

```java
import org.apache.http.HttpEntity;
import org.apache.http.client.fluent.Form;
import org.apache.http.client.fluent.Response;
import org.apache.http.client.fluent.Request;
import org.apache.http.util.EntityUtils;
import java.io.IOException;


public class BaiduToken{

    public static void main(String[] args) throws IOException {
		// 将表单数据组装成Form格式
        Form form = Form.form().add("client_id", "dGL7SgioYB4LsZnG9EnsCkrP")
                .add("client_secret", "BtZOxfurI47joml87nc1KMyB1hEmeOBE")
                .add("grant_type","client_credentials");
        String url = "https://aip.baidubce.com/oauth/2.0/token";
        Response response = Request.Post(url)
                .addHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8")
                .bodyForm(form.build())
                .execute();
        // 获得返回结果方法1
        HttpEntity entity;
        entity = response.returnResponse().getEntity();
        System.out.println(EntityUtils.toString(entity));
        // 获得返回结果方法2
        System.out.println(response.returnContent().asString());
    }
}
```
