---
title: idea jdk已经是1.8，依然出现Diamond types are not supported at this language level
date: 2018-03-27 20:04:00
tags: ['IDEA']
categories: 
 - 开发语言
 - Java
---

下面的方案二选一即可，推荐第二个方案`maven`配置。

## Idea三处修改

- project structure中的project ，SDK选择1.8，Project language level选择8
- project structure中的module，选择Language level为8
- setting中的java compiler


![project.png](https://i.loli.net/2020/09/25/JS2QI7X38Ljqa6K.png)

![module.png](https://i.loli.net/2020/09/25/qdfYTFLxkp7NmE1.png)

![compile.png](https://i.loli.net/2020/09/25/kxIgeaojrFNZflz.png)

 
## maven配置

```xml
<!--控制项目的language level和compile 版本-->
<build>
  <plugins>
    <plugin>
      <groupId>org.apache.maven.plugins</groupId>
      <artifactId>maven-compiler-plugin</artifactId>
      <version>2.3.2</version>
      <configuration>
          <source>1.8</source>
          <target>1.8</target>
      </configuration>
    </plugin>
  </plugins>
</build>
```