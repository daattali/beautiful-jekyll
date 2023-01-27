---
title: idea使用maven自动生成mybatis代码
date: 2018-02-05 21:41:00
tags: ['mybatis','IDEA','maven']
categories: 
 - 开发语言
 - Java
---

# 项目目录

![项目目录.png](https://i.loli.net/2020/09/25/vsbI61iXOgBJwHo.png)

- dao 存放mapper.java文件
- models 存放生成的数据库表model
- resources目录下的mapperXML存放生成的.xml文件



# 配置详情
## maven配置
properties标签内添加对应版本

```xml
<mybatis.version>3.3.0</mybatis.version>
<mybatis-spring.version>1.2.0</mybatis-spring.version>
<!--分页用 -->
<mybatis_pagehelper_version>4.1.6</mybatis_pagehelper_version>
```

dependencies标签内添加

```xml
<dependency>
    <groupId>org.mybatis</groupId>
    <artifactId>mybatis</artifactId>
    <version>${mybatis.version}</version>
</dependency>
<dependency>
    <groupId>org.mybatis</groupId>
    <artifactId>mybatis-spring</artifactId>
    <version>${mybatis-spring.version}</version>
</dependency>
<dependency>
    <groupId>com.github.pagehelper</groupId>
    <artifactId>pagehelper</artifactId>
    <version>${mybatis_pagehelper_version}</version>
</dependency>
```

build标签的子标签plugins内添加

```xml
<plugin>
<groupId>org.mybatis.generator</groupId>
<artifactId>mybatis-generator-maven-plugin</artifactId>
<version>1.3.2</version>
<configuration>
        <verbose>true</verbose>
        <overwrite>true</overwrite>
        <!-- 这里是 generatorConfig.xml文件的路径 请看第一张图-->
        <configurationFile>./src/main/resources/generatorConfig.xml
        </configurationFile>
    </configuration>
    <dependencies>
        <!-- 数据库驱动 我这里是postgre，其他的数据库记得改-->
        <dependency>
            <groupId>org.postgresql</groupId>
            <artifactId>postgresql</artifactId>
            <version>9.4.1208</version>
        </dependency>
    </dependencies>
</plugin>
```

## generatorConfig.xml配置

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE generatorConfiguration PUBLIC "-//mybatis.org//DTD MyBatis Generator Configuration 1.0//EN"
        "http://mybatis.org/dtd/mybatis-generator-config_1_0.dtd" >
<generatorConfiguration>
	<!-- application.properties 用来配置数据库连接，与此文件在同目录 -->
    <properties resource="application.properties"/>
    <context id="context1" targetRuntime="MyBatis3">
        <!-- 抑制警告 -->
        <property name="suppressTypeWarnings" value="true"/>

        <!-- generate entity时，生成hashcode和equals方法 -->
        <!-- <plugin type="org.mybatis.generator.plugins.EqualsHashCodePlugin" /> -->
        <!-- generate entity时，生成serialVersionUID -->
        <plugin type="org.mybatis.generator.plugins.SerializablePlugin"/>
        <!-- 这个插件只会增加字符串字段映射到一个JDBC字符的方法 -->
        <plugin type="org.mybatis.generator.plugins.CaseInsensitiveLikePlugin"/>
        <!-- genenat entity时,生成toString -->
        <plugin type="org.mybatis.generator.plugins.ToStringPlugin"/>

        <!-- 是否去除自动生成的注释 true：是 ： false:否 -->
        <commentGenerator>
            <property name="suppressAllComments" value="true"/>
            <property name="suppressDate" value="true"/>
        </commentGenerator>

        <!-- 数据库配置全部用application.properties文件内配置 -->
        <jdbcConnection driverClass="${datasource.driverClass}"
                        connectionURL="${datasource.url}"
                        userId="${datasource.username}" 
                        password="${datasource.password}">
        </jdbcConnection>

        <javaTypeResolver>
            <property name="forceBigDecimals" value="false"/>
        </javaTypeResolver>

        <!-- generate Model -->
        <javaModelGenerator targetPackage="com.ppmon.qa.models"
                            targetProject="${project}">
            <property name="enableSubPackages" value="false"/>
            <property name="trimStrings" value="true"/>
            <property name="isMergeable" value="false"/>
        </javaModelGenerator>

        <!-- generate xml -->
        <sqlMapGenerator targetPackage="mapperXML"
                         targetProject="${project_sources}">
            <property name="enableSubPackages" value="false"/>
        </sqlMapGenerator>

        <!-- generate Mapper -->
        <javaClientGenerator type="XMLMAPPER" targetPackage="com.ppmon.qa.dao"
                             targetProject="${project}">
            <property name="enableSubPackages" value="false"/>
        </javaClientGenerator>
        <table schema="" tableName="user_info" domainObjectName="UserInfo" modelType="flat"
               enableCountByExample="false" enableUpdateByExample="false"
               enableDeleteByExample="false" enableSelectByExample="false"
               selectByExampleQueryId="false">
        </table>
    </context>
</generatorConfiguration>
```

## application.properties配置

这里面的配置变量会在generatorConfig.xml中使用到

```conf
datasource.url=jdbc:postgresql://1xx.xx.xx.xx:5432/database_name?characterEncoding#UTF-8
datasource.username=username
datasource.password=password
datasource.driverClass=org.postgresql.Driver

project=./src/main/java
project_sources=./src/main/resources
```

# 生成代码文件和xml文件

选择idea右侧的maven，点击刷新，再找到mybatis-generator双击mybatis-generator:generate

![maven插件](https://i.loli.net/2020/09/25/BCrfPW89LIk2zoa.png)

**生成后的样子**

![生成后的代码](https://i.loli.net/2020/09/25/yRWZNdGaFtp3U1M.png)


# 遇到的问题

1. 点击生成后，一直提示找不到路径E:\gauge_java\silvergrd\silvergrd-gauge\src\main\resources，处理方法：src子目录下名字本是test,改为main即可。 但是为什么要去寻找main目录，尚未找到答案。
2. 提示找不到generatorConfig.xml文件，处理方法：在maven的pom文件内，指定正确的generatorConfig.xml路径。请看maven配置的configurationFile一行。
3. 生成的XML文件与我期望的不匹配，处理方法：generatorConfig.xml文件内配置的targetProject不对

如下:

```xml
<sqlMapGenerator targetPackage="mapperXML" targetProject="${project_sources}">
   <property name="enableSubPackages" value="false"/>
</sqlMapGenerator>
```

# 参考出处

[mybatis官网](http://www.mybatis.org/generator/configreference/xmlconfig.html)
[csdn文章1-作者:兮风](http://blog.csdn.net/pk490525/article/details/16819307)
[csdn文章2-作者:橙子wj](http://blog.csdn.net/antony9118/article/details/54314653)
[cnblog文章-作者:梦见舟](https://www.cnblogs.com/mengjianzhou/p/7918590.html)