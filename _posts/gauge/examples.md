---
title: Gauge中文文档(7)—Gauge实战 & CI/CD
date: 2017-10-16 09:19:25
tags: ['gauge', '自动化测试']
categories: 
 - 软件测试
 - 测试工具
 - gauge
---

## gauge项目实例

{% tabs language %}
<!-- tab <code>Java</code> -->

下面列出了使用Gauge为Java语言和不同框架设置测试项目的示例。

|框架|描述|链接|
|--|--|--|
|maven+selenium|Gauge和Selenium进行Web自动化测试的示例项目。使用Maven作为构建工具|查看[更多](https://github.com/getgauge-examples/java-maven-selenium)|
|gradle+selenium|Gauge和Selenium进行Web自动化测试的示例项目。使用Gradle作为构建工具|查看[更多](https://github.com/getgauge-examples/java-gradle-selenium)|
|sahi|使用Gauge和Sahi进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/gauge-example-sahi)|
|Selendroid|使用Gauge和Selendroid进行移动APP自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/gauge_selendroid)|
|Guice|使用Gauge和Guice进行Web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/gauge-guice)|
|Spring|使用Gauge和Spring进行Web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/ioc-spring#gauge-with-spring)|

<!-- endtab -->

<!-- tab <code>C#</code> -->
下面列出了使用Gauge为C#语言和不同框架设置测试项目的示例。

|框架|描述|链接|
|--|--|--|
|Selenium|Gauge和Selenium进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/csharp-selenium)|
|带页面对象的Selenium|Gauge和带页面的Selenium进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/gauge-example-csharp)|

<!-- endtab -->

<!-- tab <code>JS</code> -->
下面列出了使用Gauge为JS语言和不同框架设置测试项目的示例。

|框架|描述|链接|
|--|--|--|
|Taiko|Gauge和Taiko进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/js-taiko)|

<!-- endtab -->

<!-- tab <code>Python</code> -->
下面列出了使用Gauge为Python语言和不同框架设置测试项目的示例。

|框架|描述|链接|
|--|--|--|
|Selenium|Gauge和Selenium进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/python-selenium)|

<!-- endtab -->

<!-- tab <code>Ruby</code> -->
下面列出了使用Gauge为Ruby语言和不同框架设置测试项目的示例。

|框架|描述|链接|
|--|--|--|
|Selenium|Gauge和Selenium进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/ruby-selenium)|
|Capybara|Gauge和Capybara进行web自动化测试的示例项目|查看[更多](https://github.com/getgauge-examples/gauge-example-ruby)|

<!-- endtab -->

{% endtabs %}

## CI/CD集成

|CI/CD工具|描述|链接|
|--|--|--|
|GoCD|GoCD与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/gocd.html)|
|TeamCity|TeamCity与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/teamcity.html)|
|Travis-Ci|Travis-Ci与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/travis.html)|
|CircleCI|CircleCI与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/circle.html)|
|Jenkins|Jenkins与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/jenkins.html)|
|Azure|Azure与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/azure.html)|
|Docker|Docker与Gauge集成|查看[更多](https://docs.gauge.org/howto/ci_cd/docker.html)|

## 与jenkins集成

前提：

1. 知晓jenkins的基本操作
2. jenkisn服务器已经安装好 Gauge

### 新建项目

在安装完jenkins之后，是没有构建maven项目的选项的，需要添加`maven`插件。当前演示jenkins版本:`2.269`

需要安装的插件：

- HTML Publisher plugin
- Maven Integration plugin
- Git plugin

![jenkins-gauge-project](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/gauge-examples/jenkins-gauge-project.png)
<center>图：创建jenkins项目</center>

#### 添加Freestyle project

通过`gauge run specs`执行测试项目

1. 进入 `Source Code Management`， 选择Git（需要jenkins安装git插件）
2. 输入测试项目git地址，此处填写测试demo地址：https://github.com/amosnothing/gauge-java-maven.git
3. git密码验证不用管，如果有密码请自行添加
4. 进入 `Build`，添加 Execute shell(linux服务器)/Execute Windows batch command(Windows服务器)
5. 填写 gauge run specs；(更多命令参考其他章节)
6. `Goals and options` 填写 test；(执行mvn test会触发maven gauge插件，然后指定配置在pom.xml文件里面的命令)
7. 添加 `Post-build Actions`，HTML directory to archive 填写：`reports/html-report/` ，其他默认即可

![HTML-Report-setting](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/gauge-examples/HTML-Report-setting.png)
<center>图：HTML-Report-setting</center>

#### 添加maven项目

通过maven下载依赖包，并通过gauge-maven插件执行测试项目

1. 进入 `Source Code Management`， 选择Git（需要jenkins安装git插件）
2. 输入测试项目git地址，此处填写测试demo地址：https://github.com/amosnothing/gauge-java-maven.git
3. git密码验证不用管，如果有密码请自行添加
4. 进入 `Build`
5. `Goals and options` 填写 test；(执行mvn test会激活maven gauge插件，然后触发配置在pom.xml文件里面的命令)
6. 添加 `Post-build Actions`，`HTML directory to archive` 填写：`reports/html-report/` ，其他默认即可

### 查看报告

在项目面板，点击 Build now，在项目构建完之后会生成HTML-report。点击面板的 `HTML Report` 即可查看最后一次的报告。

![html-report-example](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/gauge-examples/html-report-example.png)
<center>图：html-report-example</center>

### 注意事项

1. 以root身份权限安装的gauge插件，在jenkins上构建并不能被识别到。因为jenkins的身份默认是用户：`jenkins`，而你登陆服务器的身份不一定是jenkins，可以尝试以jenkins身份登陆服务器进行安装，或者将root身份安装的gauge插件复制到jenkins目录下，比如：cp /root/.gauge/plugins/json-report/* /var/lib/jenkins/.gauge/plugins/json-report/ -Rf
2. 待添加
