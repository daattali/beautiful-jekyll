---
title: Gauge中文文档(1)—概述
date: 2017-08-28 17:02:03
updated: 2017-08-28 17:02:03
tags: ["gauge", "自动化测试工具"]
categories:
  - 软件测试
  - 测试工具
  - gauge
description: Gauge是用于编写和运行验收测试的免费开源框架
copyright: true
---

---

英文原文地址: [点击这里](https://docs.getgauge.io/)  
翻译:amoschen  
时间:2017/08/28  
翻译基于原文 0.9.1 版本，有任何异议以及错误请指正。

---

Gauge 是用于编写和运行验收测试的免费开源框架。 Gauge 使其独特的一些关键功能包括：

- 基于 Markdown 的简单，灵活和丰富的语法
- 为编写测试代码提供一致的跨平台/语言支持
- 带有插件支持的模块化架构
- 可通过插件扩展和破解
- 支持数据驱动的执行和外部数据源
- 帮助您创建可维护的测试套件
- 对 VS Code 的集成支持

## Specification

译者注：`Specification`如果实在要翻译这个词，可以翻译成`说明书`，因为 Gauge 最美好的愿景是：面向开发/测试/产品人员。

`Gauge` Specification 是通过 markdown 语法编写，比如：

```md
# 浏览网页

## 查找好吃的地方

- 打开 google 主页地址
```

在上述 markdown 文件中：

- `# 浏览网页` 作为 Specification 文件的标题
- `## 查找好吃的地方` 作为一个`scenario`(场景)
- `* 打开google主页地址` 则作为一个步骤

## Implementation 实现

可以通过对应的开发语言来实现对应的步骤：

```go
step("打开google主页地址", () => {
  goto("google.com")
});
```

`gauge runner` 执行器读取并运行 Specification 中每个场景的步骤及其实现，并生成通过或失败场景的报告。

```txt
# Search the Internet
## Look for something  ✔

Successfully generated html-report to => reports/html-report/index.html
Specifications:       1 executed      1 passed        0 failed        0 skipped
Scenarios:    1 executed      1 passed        0 failed        0 skipped
```

## 重复使用的步骤

`Gauge`可帮助您专注于测试应用程序的流程。通过使步骤尽可能可重复使用来实现此目的。使用 Gauge，您无需使用编程语言来构建自定义框架。

比如，可以通过在步骤里使用引号，传递参数给底层语言实现方法。

```md
# 浏览网页

## 查找好吃的地方

- 打开 google 主页地址
- 搜索 "美食店"
```

实现步骤可以这么写：

```go
step("搜索 <query>", (query) => {
  write(query);
  press("Enter");
});
```

然后，您可以在具有不同参数的场景内或场景间重复使用此步骤。

```md
# 浏览网页

## 查找好吃的地方

- 打开 google 主页地址
- 搜索 "美食店"

## 查找好玩的地方

- 打开 google 主页地址
- 搜索 "休闲玩乐"
```

又或者可以将你的多个步骤组合成`concept`，放置在`.cpt`文件中:

```md
## 查找 <query>

- 打开 google 主页地址
- 搜索 <query>
```

然后，其他步骤便可以使用刚才定义好的`concept`:

```md
# 浏览网页

## 查找好吃的地方

- 查找 "美食店"

## 查找好玩的地方

- 查找 "休闲玩乐"
```

## 数据驱动

`Gauge`还支持使用 Markdown 表以及外部 csv 文件的数据驱动测试

```md
# 浏览网页

| query    |
| -------- |
| 美食店   |
| 休闲玩乐 |
| 电影院   |

## 查找好吃的地方

- 查找 <query>
```

该场景会将表中的所有参数带入步骤中，逐行执行。

在上面的示例中，我们重构了`specification`，使其简洁，灵活，而无需更改实现。
