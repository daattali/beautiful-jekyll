---
title: Gauge中文文档(2)—开始
date: 2017-08-30 11:47:25
updated: 2017-08-30 11:47:25
tags: ["gauge", "自动化测试工具"]
categories:
  - 软件测试
  - 测试工具
  - gauge
---


本章节带领你快速预览`Gauge`的核心功能。在阅读完本章后，你便可知晓如何安装 `Gauge`，以及学会创建你的第一个测试自动化项目。

## 安装 Gauge

; 不同的操作系统
{% tabs os %}

<!-- tab <code>Linux</code> -->

### Linux 安装 Gauge

可以使用 Shell 脚本将`Gauge`安装在任何版本的 Linux 上。以下步骤将指导您在 Linux 机器上快速安装:

- APT_GET

  $ sudo apt-key adv --keyserver hkp://pool.sks-keyservers.net --recv-keys 023EDB0B
  $ echo deb https://dl.bintray.com/gauge/gauge-deb stable main | sudo tee -a /etc/apt/sources.list
  $ sudo apt-get update && sudo apt-get install gauge

- DNF
  $ sudo dnf install gauge

- ZIP

  1. 下载[ZIP 文件](https://github.com/getgauge/gauge/releases/download/v1.1.5/gauge-1.1.5-linux.x86_64.zip)
  2. 执行命令： $ unzip -o gauge-1.1.5-linux.x86_64.zip -d /usr/local/bin

- NPM
  系统要求： Node.js >= 10.16.3 (LTS) & NPM >= (6.9.0)
  $ npm install -g @getgauge/cli

- CURL

  - 安装到 `/usr/local/bin` : curl -SsL https://downloads.gauge.org/stable | sh
  - 安装到你指定的位置： curl -SsL https://downloads.gauge.org/stable | sh -s -- --location-[custom path]

<!-- endtab -->
<!-- tab <code>macOS</code> -->

### macOS 安装 Gauge

本节提供有关在 macOS 环境中设置`Gauge`的特定说明。

- HomeBrew
  $ brew install gauge
- CURL
  - 安装到 `/usr/local/bin` : curl -SsL https://downloads.gauge.org/stable | sh
  - 安装到你指定的位置： curl -SsL https://downloads.gauge.org/stable | sh -s -- --location-[custom path]
- ZIP
  1. 下载[ZIP 文件](https://github.com/getgauge/gauge/releases/download/v1.1.5/gauge-1.1.5-darwin.x86_64.zip)
  2. 执行：$ unzip -o gauge-GAUGE_LATEST_VERSION_PLACEHOLDER-darwin.x86_64.zip -d /usr/local/bin
- NPM
  系统要求： Node.js >= 10.16.3 (LTS) & NPM >= (6.9.0)
  $ npm install -g @getgauge/cli

<!-- endtab -->
<!-- tab <code>Windows</code> -->

### Windows 安装 Gauge

- Windows EXE

  1. 下载[exe 文件](https://github.com/getgauge/gauge/releases/download/v1.1.5/gauge-1.1.5-windows.x86_64.exe)
  2. 运行 exe 文件然后按顺序点击按钮，中途可以勾选你需要的`开发语言`

- Chocolate

  1. 打开 cmd 或者 power shell
  2. 运行: $ choco install gauge

- ZIP

  1. 下载[ZIP 文件](https://github.com/getgauge/gauge/releases/download/v1.1.5/gauge-1.1.5-windows.x86_64.zip)
  2. PowerShell 运行： $ Expand-Archive -Path gauge-1.1.5-windows.x86_64.zip -DestinationPath custom_path

- NPM
  系统要求： Node.js >= 10.16.3 (LTS) & NPM >= (6.9.0)
  $ npm install -g @getgauge/cli

<!-- endtab -->

{% endtabs %}

### 安装 VS Code 的 Gauge 插件

1. 打开最新版本的 `vscode`
2. 进入扩展商店
3. 搜索 `Gauge`
4. 点击安装

![pic](https://docs.gauge.org/_images/VSCode_Gauge_install_plugin.png)

## 创建测试项目

不同开发语言下，运行测试项目所需要求：

- Java: JDK >= 11
- C#: .net Sdk >= 2.0
- JS: Nodejs >= 10.16.3 (LTS)
- Python： Python >= 2.7 & Pip
- Ruby: Ruby >= 2.3.0 & Bundler

### 在 VSCode 创建测试项目

VSCode 内的 Gauge 插件可以帮助你快速创建 Gauge 项目，以及执行 Gauge 测试代码。

#### 创建项目

一旦安装好 VSCode 的 Gauge 插件，你便可以通过快捷指令：ctrl + shift + p 唤起 VSCode 的命令面板，输入：`Gauge: Create new Gauge Project` 来创建新的 Gauge 测试项目。

![VSCode_create_gauge_project](https://docs.gauge.org/_images/VSCode_create_gauge_project.png)

#### 选择模板

选择对应开发语言的模板：

![VSCode_select_project_tempate](https://docs.gauge.org/_images/VSCode_select_project_tempate.png)

#### 选择项目存放位置

选择新 Gauge 项目的存放地址：

![VSCode_create_project_select_folder1](https://docs.gauge.org/_images/VSCode_create_project_select_folder1.png)

#### 命名你的项目

给你的项目命名：

![VSCode_enter_project_name](https://docs.gauge.org/_images/VSCode_enter_project_name.png)

在你创建完你的项目之后，你可在文件预览窗口看到一些模板文件(根据你选择的开发语言而决定文件格式和文件结构的不同)：

![Java_folder_structure2](https://docs.gauge.org/_images/Java_folder_structure2.png)

![VSCode_Java_project_file_structure](https://docs.gauge.org/_images/VSCode_Java_project_file_structure.png)

## 执行 Spec

现在你已经成功的初始化了一个 `Gauge` 测试项目，我们接着往后看，如何执行测试项目中的 spec 模板文件。

一个 spec 文件详细申明了一些你想要测试的内容。在 Gauge 中，这些都被放置在`.spec`文件中。

### 打开 Spec 文件

打开 spec 文件模板，该文件放置于项目的`specs/example.spec`处

![VSCode_open_example](https://docs.gauge.org/_images/VSCode_open_example.spec.png)

### 运行 spec 文件

在 VSCode 中，点击选项：`Run Spec`

![run_spec](https://docs.gauge.org/_images/VSCode_run_code_lens.png)

然后你可以在 VSCode 的`Output`处，看到本次测试运行的输出：

![VSCode_execution_console](https://docs.gauge.org/_images/VSCode_execution_console.png)

## 查看报告

即可以通过 VSCode 运行面板查看结果

![VSCode_report_link](https://docs.gauge.org/_images/VSCode_report_link.png)

---

Specifications: (w) executed (x) passed (y) failed (z) skipped  
Scenarios: (a) executed (b) passed (c) failed (d) skipped

---

Scenarios 统计表示

| 值  | 描述                 |
| --- | -------------------- |
| (a) | scenarios 执行总数   |
| (b) | scenarios 执行通过数 |
| (c) | scenarios 执行失败数 |
| (d) | scenarios 执行跳过数 |

Specifications 统计表示

| 值  | 描述                      |
| --- | ------------------------- |
| (w) | Specifications 执行总数   |
| (x) | Specifications 执行通过数 |
| (y) | Specifications 执行失败数 |
| (z) | Specifications 执行跳过数 |

也可以通过在命令面板执行：`Gauge: Show Last Run Report` 来通过浏览器打开测试报告

![VSCode_show_last_run_report](https://docs.gauge.org/_images/VSCode_show_last_run_report.png)

测试报告在浏览器中打开的样式：

![HTML_report](https://docs.gauge.org/_images/HTML_report.png)

到此我们结束了 Gauge 的入门旅程。希望这可以帮助您安装和设置第一个 Gauge 项目。Gauge 具有强大的语言和工具支持以及通用的报告功能。
