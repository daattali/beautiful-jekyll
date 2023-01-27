---
title: Springboot设置默认访问路径方法
date: 2019-02-20 14:53:52
updated: 2019-02-20 14:53:52
tags: ['Springboot','修改路径指向']
categories: 
 - 开发语言
 - Java
 - Spring
---

# 前言

当使用springboot与其他框架结合编写web前后端时，可能存在这样的需求：我想在访问10.10.10.100时，实际上需要访问10.10.10.100/hello页面。（端口已省略，自行设置）

# 解决
## 方案1 - 实现WebMvcConfigurer接口
搜过很多博客，里面的内容虽然可以用。但是基本上都是基于继承`WebMvcConfigurerAdapter `类实现的，而官方的源码里面已经==不推荐使用==该类了。

下面给出我的解决方案，很简单：

```java
import org.springframework.context.annotation.Configuration;
import org.springframework.core.Ordered;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class DefaultView implements WebMvcConfigurer {

    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/").setViewName("hello");
        registry.setOrder(Ordered.HIGHEST_PRECEDENCE);
    }
}
```
### 补充&注意点
-  setViewName ：将 `/` 指向 `/hello`

这里需要注意，因为我的项目里把url的访问路径后缀".html"全部都去掉了，所以可以这么用。如果你的不是，需要做对应调整。
 
补充我的application.properties文件部分配置：
       
    server.port=80
    spring.thymeleaf.prefix=classpath:/templates/
    spring.thymeleaf.suffix=.html
    spring.mvc.favicon.enabled=true

`@Configuration` 别忘了加，我自己就是忘了加，以为没生效，折腾半天。

## 方案2 - @Controller路由设置

```java
@Controller
public class PageController {

    @GetMapping(value = "/")
    public String defaultPath(Model model) {
        return "hello";
    }
  }
```
properties文件配置同方案1一致
