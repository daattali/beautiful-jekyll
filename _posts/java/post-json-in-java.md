---
title: Java简单入门【对比Python】Part2.POST JOSN请求
date: 2018-03-05 00:16:18
updated: 2018-03-05 00:16:18
tags: ['Java入门','JavaPost','JavaJson','JavaPython','Postman']
categories: 
 - 开发语言
 - Java
---

# Post Json例子

这里我们选择postman自带的post地址，您打开postman后点击Collections，里面有很多请求的例子。

- url = https://postman-echo.com/post
- content-type = application/json
- body = {"a":"123","b":"456"}  -> 这里您随便传均可


# Postman请求

具体请查看图片，地址，请求头，请求参数均填写正确。
![这里写图片描述](http://img.blog.csdn.net/20180305000252168?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYW1vc2Nu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

# Python请求

和上一节一样，用的requests库。

```python
# coding:utf-8

import json
import requests

def post_json():
    url = "https://postman-echo.com/post"
    body = {
        "myName": "amos",
        "age": "17"
    }

    response = requests.post(url=url,
                             headers={"content-type": "application/json"},
                             data=json.dumps(body),
                             )
    print(response.content)

if __name__ == "__main__":
    post_json()
```

返回内容如下: (是否和postman一样呢?)
>b'{"args":{},"data":{"myName":"amos","age":"17"},"files":{},"form":{},"headers":{"host":"postman-echo.com","content-length":"31","accept":"*/*","accept-encoding":"gzip, deflate","content-type":"application/json","user-agent":"python-requests/2.18.4","x-forwarded-port":"443","x-forwarded-proto":"https"},"json":{"myName":"amos","age":"17"},"url":"https://postman-echo.com/post"}'

有点不一样，注意到前面的"b"了吗？返回的内容是bytes类型。想要str类型很简单，bytes转str。`print(response.content)` - > 改为 `print(response.content.decode())`即可。

# JAVA请求

先加入maven依赖

```xml
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-core</artifactId>
    <version>2.9.4</version>
</dependency>
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.9.4</version>
</dependency>
<dependency>
    <groupId>org.apache.httpcomponents</groupId>
    <artifactId>fluent-hc</artifactId>
    <version>4.5.4</version>
</dependency>
```

## java代码

```java
import org.apache.http.HttpEntity;
import org.apache.http.client.fluent.Response;
import org.apache.http.client.fluent.Request;
import org.apache.http.entity.StringEntity;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.http.MediaType;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


public class RequestClient {

    private final static String JSON = MediaType.APPLICATION_JSON_UTF8_VALUE;
    
	public String postJson(String url, String body) throws IOException {

        HttpEntity httpEntity = new StringEntity(body);

        Response response = Request.Post(url)
                .addHeader("Content-Type", JSON)
                .body(httpEntity)
                .execute();

        return response.returnContent().asString();

    }
    public static void main(String[] args) throws IOException {
        RequestClient client  = new RequestClient();
        String url = "https://postman-echo.com/post";
        Map<String, String> map = new HashMap<String, String>();
        map.put("myName", "amos");
        map.put("age", "17");
        // 将map转为json
        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(map);

        System.out.println(client.postJson(url, body));
    }
}
```

运行main方法之后打印返回内容如下:

>{"args":{},"data":{"myName":"amos","age":"17"},"files":{},"form":{},"headers":{"host":"postman-echo.com","content-length":"28","accept-encoding":"gzip,deflate","content-type":"application/json;charset=UTF-8","user-agent":"Apache-HttpClient/4.5.4 (Java/9.0.1)","x-forwarded-port":"443","x-forwarded-proto":"https"},"json":{"myName":"amos","age":"17"},"url":"https://postman-echo.com/post"}