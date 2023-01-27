---
title: Java链式编程 - 以Beetl模版渲染为例
date: 2018-04-24 22:49:00
updated: 2018-04-24 22:49:00
tags: ['java','链式编程','beetl','模版渲染']
categories: 
 - 开发语言
 - Java
---

# 背景
目前工作需要对已有的文件进行参数渲染，以供其他方法调用。打个比方，我现在有一段报文如下：

```json
{
  "a":"a",
  "b":"hello kitty",
  "c":"c",
  "d":"d",
  "e":"hello world"
}
```
那我需要修改某个或者某些字段的数值，如何做呢 ？ 那就轮到模版渲染引擎Beetl出场，然后我们会以链式编程的方式来实现。
# 链式编程
## 创建模版
将上面的报文已文件形式报文，放置到resource目录下，命名为example.json。项目结构如图

![项目结构](https://i.loli.net/2020/09/25/9UJZA23pCIzxgMq.png)

修改文件内容如下

```json
{
  "a":"${a}",
  "b":"hello kitty",
  "c":"${c}",
  "d":"${c}",
  "e":"hello world"
}
```
## 渲染模版
我们的目的是渲染模版，在这里我采用的是java的链式编程方式来实现。要达到这个目的，也就是说通过"实例名.方法名"这样的方式，必须使得实例方法返回的都是它本身。

```java
import org.beetl.core.Configuration;
import org.beetl.core.GroupTemplate;
import org.beetl.core.Template;
import org.beetl.core.resource.ClasspathResourceLoader;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * @author Amos
 */
public class BeetlUtil{

    private Template tmp;
	
	// 对象初始化
    private BeetlUtil(String fileName) {
        ClasspathResourceLoader resourceLoader = new ClasspathResourceLoader("json");
        Configuration cfg = null;
        try {
            cfg = Configuration.defaultConfiguration();
        } catch (IOException e) {
            e.printStackTrace();
        }
        GroupTemplate gt = new GroupTemplate(resourceLoader, cfg);
        this.tmp = gt.getTemplate(fileName);
    }

	
	// 通过传入map来渲染模版
	// map的key作为模版的变量
	// map的value作为传入的数值
    public BeetlUtil bind(Map map) {
        this.tmp.binding(map);
        return this;
    }
    
    // 单个参数渲染
	// key作为模版的变量
	// value作为传入的数值 
    public BeetlUtil bind(String key, Object obj) {
        tmp.binding(key, obj);
        return this;
    }
    
	// 将模版转为String
    public String asString() {
        return tmp.render();
    }


    public static void main(String[] args) {

        Map<String, String> map = new HashMap<String, String>(16){
            {
                put("c","hello c");
                put("d","hello d");
            }
        };
        // 1. 初始化
        // 2. 通过map传参
        // 3. 通过key/value传参
        // 4. 将模版文件转为String
        // 这里便是采用链式调用的方式
        String str = new BeetlUtil("example.json")
                .bind(map)
                .bind("a","hello a")
                .asString();
        System.out.println(str);
    }
}
```

打印结果

```json
{
  "a":"hello a",
  "b":"hello kitty",
  "c":"hello c",
  "d":"hello d",
  "e":"hello world"
}
```