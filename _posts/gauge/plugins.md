---
title: Gauge中文文档(5)—插件的使用
date: 2017-09-14 09:08:50
tags: ["gauge", "自动化测试工具"]
categories:
  - 软件测试
  - 测试工具
  - gauge
---

本章节提供 Gauge 支持的多类型插件，以及插件安装和卸载相关信息。插件为 Gauge 提供额外的功能。

## 安装插件

插件使用子命令 `install` 安装， `gauge install <plugin_name>` 命令会检索插件库（译者注：通过`gauge config --list`显示对应地址）并下载安装它们。

### 指定插件版本

通过添加`--version`标志来指定插件版本号：

> $ gauge install java --version <plugin_version>

### 离线安装

插件可以使用 `--file` 或者 `--f` 标志从 `zip` 文件安装，取代从插件库下载安装（译者注：由于大陆童鞋的网络连接到 github 非常慢，推荐使用离线安装的方式，先下载到本地再安装）。

> $ gauge install html-report –file ZIP_FILE_PATH

从相应存储库的版本部分下载最新版本的插件，请参阅 [插件列表](https://getgauge.io/plugins.html) 查找插件库。

## 更新插件

使用 `update` 子命令升级插件到最新版本。 `gauge update <plugin_name>` 这将从我们的插件库下载最新的插件。

> $ gauge update java

或者可通过使用标志 `--version` 升级该插件到特定的版本：

> $ gauge update java –version 0.3.2

也可以通过执行下面的命令升级所有的插件:

> $ gauge update –all

## 卸载插件

卸载某个插件：

> $ gauge uninstall java

下载某个特定版本的插件：

> $ gauge uninstall java --version <plugin_version>

## 插件安装故障处理

通过情况下，在线安装插件会出现各种网络异常情况。所以可以通过手动下载ZIP文件，然后离线安装的方式。点击[此处](https://gauge.org/plugins/)查看各个插件的下载地址。

## 插件目录

插件安装的默认路径对于不同的操作系统而言各异：

- Windows：`%APPDATA%\.gauge\plugins`
- macOS X：`~/.gauge/plugins`
- Linux：`~/.gauge/plugins`

或者可以通过修改环境变量`GAUGE_HOME`来修改 gauge 插件安装目录。

## 插件类型

### 语言插件

语言插件，也称为语言执行器，允许用户使用他们选择的语言编写 spec。允许你使用下列语言编写你的测试：

- Java
- C#
- Ruby
- JS
- Python

> $ gauge install java
> $ gauge install js
> $ gauge install python
> $ gauge install ruby
> $ gauge install csharp

### 报告插件

报告插件生成各种格式的执行报告。

- XML 报告
- HTML 报告
- Flash 报告

> $ gauge install html-report
> $ gauge install xml-report
> $ gauge install flash

### IDE 插件

Gauge 为流行的 IDE 提供了插件，可以改善编写测试 spec 的体验。我们建议你使用 VSCode 插件。然而 Gauge 可以在你选择的任何编辑器上不使用插件。

- 与 Intellij 集成
- 与 Visual Studio Code 集成

通过使用 VSCode 的 Gauge 扩展，可以在 VSCode 中创建和运行 Gauge 项目。这个插件目前支持 Gauge 与 Java, JavaScript, Ruby, Python, c#(.Net Core)和 TypeScript。

### 其他插件

文档插件根据 spec 生成易于浏览的 HTML 格式文档

- [spectacle](https://github.com/getgauge/spectacle)

## 构建工具

- [Maven](https://github.com/getgauge/gauge-maven-plugin)
- [Gradle](https://github.com/manupsunny/gauge-gradle-plugin)
