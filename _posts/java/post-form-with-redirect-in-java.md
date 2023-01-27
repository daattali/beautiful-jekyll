---
title: Java简单入门 - Part3.POST Form重定向处理(httpcomponents:fluent-hc)
date: 2019-02-20 11:15:08
tags: ['java','http重定向','fluent-hc']
categories: 
 - 开发语言
 - Java
---

# 背景

## 遇到问题

通过fluent-hc编写了一个HttpUtil类，该类包含post form, post json, get 等等方法。此时我需要用该util类来发送请求并保存返回对象body。可是，向某个url 发送post form后，总是会引发httpResponseException, 进入源码查看原因getStatusCode>= 300 。

## 猜测

1. 服务器端拒绝当前请求
2. 服务器端无响应
3. 其他原因


# 解决问题

## 替换client调试

更换另外一个httpclient类再发起请求，可以正常返回，说明传参是没有问题的。然后打印返回的statusCode发现“code = 302”，原来是因为有重定向的原因。向某个URL post一段报文后，在该服务器接收到报文信息后，会重定向另外一个URL，我们需要通过httpClient来处理该重定向url。

>重定向(Redirect)就是通过各种方法将各种网络请求重新定个方向转到其它位置（如：网页重定向、域名的重定向、路由选择的变化也是对数据报文经由路径的一种重定向）。

## 引入maven包

    <dependency>
        <groupId>org.apache.httpcomponents</groupId>
        <artifactId>fluent-hc</artifactId>
        <version>4.5.6</version>
    </dependency>

## 其他版本信息

OS   : windows 7 
IDEA : 2018.3.3
JAVA : 8
maven : 3.3.9
    
若需要引入其他maven包，请尽可能使用最新版本.

## 修改util代码

（只包含了post form部分，其他代码与标题无关已省略）

细节请参看代码内注释部分，有不明白的地方可以留言或者看源码。

```java
package com.amos.hc;

import com.alibaba.fastjson.JSONObject;
import org.apache.http.HttpEntity;
import org.apache.http.NameValuePair;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.client.LaxRedirectStrategy;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.util.*;

public class HttpUtil {

    private final static String APPLICATION_FORM_URLENCODED_VALUE = "application/x-www-form-urlencoded";

    public static String postForm(String url, Map<String, String> body) throws IOException {

        return postForm(url, body, false);
    }

    public static String postForm(String url, String body) throws IOException {
        Objects.requireNonNull(url, "url");
        Objects.requireNonNull(body, "body");

        Map<String, Object> param = JSONObject.parseObject(body);

        // LinkedHashMap 有序map
        Map<String, String> param1 = new LinkedHashMap<>(16);
        param.forEach((k, v) -> param1.put(k, String.valueOf(v)));

        return postForm(url, param1);
    }

    public static String postForm(String url, Map<String, String> body, Boolean enableRedirect) throws IOException {
        Objects.requireNonNull(url, "url");
        Objects.requireNonNull(body, "body");

        // http客户端构造器
        HttpClientBuilder builder = HttpClientBuilder.create();

        // 根据传入的布尔值 确定是否开启重定向
        if (enableRedirect) {
            LaxRedirectStrategy redirectStrategy = new LaxRedirectStrategy();
            builder.setRedirectStrategy(redirectStrategy);
        }
        // 键值对 保存入参
        List<NameValuePair> formBody = new ArrayList<>();
        CloseableHttpClient httpClient = builder.build();

        body.forEach((k, v) -> formBody.add(new BasicNameValuePair(k, v)));
        UrlEncodedFormEntity entity = new UrlEncodedFormEntity(formBody, "utf-8");
        // 构造post请求
        HttpPost httpPost = new HttpPost(url);
        // 设置请求实体
        httpPost.setEntity(entity);

        CloseableHttpResponse response = httpClient.execute(httpPost);
        HttpEntity httpEntity = response.getEntity();
        String responseContent =  EntityUtils.toString(httpEntity);
        // 关闭client
        httpClient.close();
        // 关闭返回对象
        response.close();
        return responseContent;
    }
```

# 资料参考

1. [java重定向与转发区别](https://www.cnblogs.com/yinyl/p/8116490.html)
2. [HttpComponents 重定向问题分析和解决](https://xuzonghua-itianyi-com.iteye.com/blog/1908580)
3. 百度百科 - [重定向](https://baike.baidu.com/item/%E9%87%8D%E5%AE%9A%E5%90%91/9064196?fr=aladdin)
