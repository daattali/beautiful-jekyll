---
title: 通过Jmeter调用上传文件接口
date: 2020-01-17 08:22:46
tags: ['Java', 'Jmeter', '上传文件']
categories: 
 - 软件测试
 - 测试工具
---


## 背景

昨日与同事讨论问题过程中，他提到通过Jmeter无法上传文件，需要自己写Java代码。然后我回复了他，Jmeter是可以做到上传文件的。

下面我们自己动手写一个上传文件的接口，并通过Jmeter调用达到上传文件，并保存在本地。

## 编写上传文件接口

1. 通过IDEA新建项目
2. 选择`Spring Initializr`
3. 添加依赖如下

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.2.2.RELEASE</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>com.example</groupId>
    <artifactId>demo</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>demo</name>
    <description>Demo project for Spring Boot</description>

    <properties>
        <java.version>1.8</java.version>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>

</project>
```

4. 新建Java类

```java
package com.example.demo.controller;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.util.Objects;
import java.util.UUID;

@RestController
public class FileController {

    @PostMapping("/upload")
    @ResponseBody
    public String upload(@RequestParam("file") MultipartFile file, @RequestParam("name") String name) {
        String filename = "";
        try {
            //上传目录地址 自定义
            String uploadDir = "d:/file_spring/" + name + "/";

            //如果目录不存在，自动创建文件夹
            File dir = new File(uploadDir);
            if (!dir.exists()) {
                dir.mkdir();
            }
            //调用上传方法
            filename = executeUpload(uploadDir, file);
        } catch (Exception e) {
            //打印错误堆栈信息
            e.printStackTrace();
        }
        return filename;
    }

    private String executeUpload(String uploadDir, MultipartFile file) throws Exception {
        //文件后缀名
        int index = Objects.requireNonNull(file.getOriginalFilename()).lastIndexOf(".");
        String suffix = file.getOriginalFilename().substring(index);
        //上传文件名
        String filename = UUID.randomUUID() + suffix;
        //服务器端保存的文件对象
        File serverFile = new File(uploadDir + filename);

        if (!serverFile.exists()) {
            //先得到文件的上级目录，并创建上级目录，在创建文件
            serverFile.getParentFile().mkdir();
            try {
                //创建文件
                serverFile.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        //将上传的文件写入到服务器端文件内
        file.transferTo(serverFile);
        return filename;
    }
}
```

## 通过Jmeter调用

1.添加线程组

2.添加HTTP请求 

设置http
![image1](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/upload-file-via-jmeter/https-setting.png)

设置文件路径
![image2](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/upload-file-via-jmeter/file-path-setting.png)

3. 查看结果
文件最终成功上传到本地
![image3](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/upload-file-via-jmeter/after-request.png)
