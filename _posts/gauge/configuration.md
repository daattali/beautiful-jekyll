---
title: Gauge中文文档(6)—配置
date: 2017-09-25 09:28:57
tags: ["gauge", "自动化测试"]
categories:
  - 软件测试
  - 测试工具
  - gauge
---

你可以通过使用`gauge.properties`和`default.properties`文件中的键值对来根据需要配置`Gauge`。

- `gauge.properties` 文件中的全局键值对允许你在所有`Gauge`项目中配置`Gauge`。例如，你可以通过更改 `plugin_connection_timeout` 的值来更改 Gauge 连接到插件时 Gauge 的超时值。此值适用于所有`Gauge`项目。
- `default.properties` 文件中的本地键值对允许你为该文件对应的 Gauge 项目配置 Gauge。例如，每次 Gauge 使用 `overwrite_reports` 键运行 spec 时，你可以创建单独的 Gauge 报告，或创建一个带时间戳的新目录（覆盖以前的报告）。

## 全局配置

`gauge.properties`文件位于：

- macOS/Linux：~/.gauge/config
- Windows：%APPDATA%\Gauge\config

```conf
# 当gauge或者gauge插件更新时发送通知
check_updates = true

# gauge插件库下载地址
gauge_repository_url = https://downloads.getgauge.io/plugin

# gauge模版库下载地址
gauge_templates_url = https://downloads.getgauge.io/templates

# 连接到language runner的超时时间，时间单位：毫秒
runner_connection_timeout = 30000

# 连接到除了language runner之外的插件的超时时间，时间单位：毫秒
plugin_connection_timeout = 10000

# 在发送kill消息后插件停止的超时时间，时间单位：毫秒
plugin_kill_timeout = 10000

# 设置从language runner请求超时，单位毫秒
# 如果项目太大，gauge可能会在runner返回响应消息之前超时。这个值应当设置合理。
runner_request_timeout = 10000
```

可以手动修改该文件中的键值对，或者通过命令`gauge config`来更改键值对：

> $ gauge config [flags] [args]

例如：不允许有版本更新时发送更新通知：

> $ gauge config check_updates false

## 本地配置

某些键值对可以在项目根目录的 `env/default/default.properties` 里面配置， 这些属性覆盖默认属性且只在当前项目中生效。

```conf
# gauge报告目录路径，可以是对于项目的相对路径或者绝对路径
gauge_reports_dir = reports

# 设置为false则报告在每次执行后不会被覆盖
# 设置为true则每次执行会生成一个新的带时间戳的目录
overwrite_reports = true

# 设置为flase则报告中的失败不会截屏
screenshot_on_failure = false

# gauge日志目录路径，可以是对于项目的相对路径或者绝对路径
logs_directory = GaugeLogs

# 是否允许通过多线程的方式启动并行执行spec
enable_multithreading = false

# 指定gauge spec文件的路径
# 可以通过逗号 <,> 分隔多个spec文件或者spec目录
gauge_specs_dir = specs

# csv文件内数据的分隔符号，默认: `,`
csv_delimiter = ,

# 允许一个步骤被写成多行
allow_multiline_step = false
```

## 语言插件配置

`language.properties`是一个`.properties`文件，`language`对应创建项目时使用的开发语言。可以修改这些文件的配置，用作运行 spec 时的环境变量。

该文件位于项目根目录：`env/default/`之下，不同语言之间的配置各异。

{% tabs language %}

<!-- tab <code>Java</code> -->

```conf
# 配置JDK_HOME
gauge_java_home = PATH_TO_JAVA_HOME

# 修改该值以覆盖Gauge项目构建路径
# IDEA和Eclipse的out目录通常是自动检测的
gauge_custom_build_path = PATH_TO_CUSTOM_BUILDPATH

# 指定额外的依赖库
# 可以指定多个，以逗号,隔开
# 默认配置是项目根目录的libs子目录
gauge_additional_libs = libs/*, PATH_TO_NEW_LIBRARY

# 设置JVM运行参数
# 多个参数可以通过逗号,隔开，比如 Xmx1024m, Xms128m
gauge_jvm_args = <JVM_ARGS>

# 指定被编译的java文件目录
# 多个目录以逗号,隔开
gauge_custom_compile_dir =

# 指定内存内对象清除级别
# 默认是<scenario>场景级别，可以设置为<suite> 全局级别, <spec>spec文件级别或者 scenario
gauge_clear_state_level = scenario
```

<!-- endtab -->
<!-- tab <code>JS</code> -->

```conf
# Gauge执行spec超时时间，覆盖默认配置
test_timeout = 10000

# 是否支持浏览器调试
DEBUG = false

# 步骤对应代码实现的目录，相对于项目根目录而言，以逗号,隔开
STEP_IMPL_DIR = tests
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```conf
# 步骤对应代码实现的目录，相对于项目根目录而言，以逗号,隔开
STEP_IMPL_DIR = tests
```

<!-- endtab -->
<!-- tab <code>C#</code> -->

```conf
# 步骤对应代码实现的目录，相对于项目根目录而言，以逗号,隔开
STEP_IMPL_DIR = tests
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

Ruby 语言没有其他特定的配置信息。

<!-- endtab -->

{% endtabs %}

## HTTP 代理

Gauge 连接互联网来下载插件，模版等等。如果你想使用代理，你需要配置代理设置使得 `gauge` 通过代理服务器连接互联网。（译者注：这并非 Gauge 的配置，而是修改或者添加当前用户的环境变量）

### 无认证

如果不需要认证，将环境变量 `HTTP_PROXY` 设置为代理服务器 URL。

`Linux` 或者 `MacOS`：

> $ export HTTP_PROXY = http://server-ip:port

`Windows`：

> $ set HTTP_PROXY = http://server-ip:port

### 有认证

如果需要认证，将环境变量 `HTTP_PROXY` 设置为代理服务器 URL 以及认证信息。

Linux`或者`MacOS`：

> $ export HTTP_PROXY = http://username:password@server-ip:port

`Windows`：

> $ set HTTP_PROXY = http://username:password@server-ip:port

## 构建工具配置

### Maven

使用 gauge-maven-plugin 在你的 gauge java 项目执行 specs，并使用 maven 管理依赖项。

#### 从 archetype 创建新项目

> $ mvn archetype:generate -DgroupId={projectGroupId} \\
> -DartifactId={projectArtifactId} \\
> -DarchetypeArtifactId=gauge-archetype-java \\
> -DarchetypeGroupId=com.thoughtworks.gauge.maven

基于你的项目来设置{projectGroupId} 和 {projectArtifactId} 。查看 [maven 文档](https://maven.apache.org/pom.html#Maven_Coordinates)
以理解 groupId 和 artifactId 在 maven 项目中的意义。

#### 在 IDE 创建 gauge maven 项目

在项目中生成的 **pom.xml** 将具有 **gauge-java** 依赖关系和在测试阶段定义的执行目标 **gauge:execute** 。

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
<modelVersion>4.0.0</modelVersion>

<groupId>com.foo</groupId>
<artifactId>my-gauge-tests</artifactId>
<version>1.0-SNAPSHOT</version>

<dependencies>
    <dependency>
        <groupId>com.thoughtworks.gauge</groupId>
        <artifactId>gauge-java</artifactId>
        <version>0.2.2</version>
        <scope>test</scope>
    </dependency>
</dependencies>

<build>
    <testSourceDirectory>${project.basedir}/src/test/java</testSourceDirectory>
    <plugins>
        <plugin>
            <groupId>com.thoughtworks.gauge.maven</groupId>
            <artifactId>gauge-maven-plugin</artifactId>
            <version>1.4.0</version>
            <executions>
                <execution>
                    <phase>test</phase>
                    <configuration>
                        <specsDir>specs</specsDir>
                    </configuration>
                    <goals>
                        <goal>execute</goal>
                    </goals>
                </execution>
            </executions>
        </plugin>
    </plugins>
</build>
</project>
```

#### 使用 maven 执行 specs

如果在 test 阶段（参考上述 xml 文件）执行目标已添加，然后运行 maven 。maven 的`test`阶段将也在项目中执行 gauge specs。

> $ mvn test

- 仅执行 specs 目录

> $ mvn gauge:execute -DspecsDir=specs

- 运行对应 pom.xml 中指定配置文件的 gauge specs

> $ mvn gauge:execute -P \<profile-name>

- 并行执行 specs

> $ mvn gauge:execute -DspecsDir=specs -DinParallel=true

- 通过 tags 执行 specs

> $ mvn gauge:execute -DspecsDir=specs -Dtags="!in-progress"

- 指定执行环境

> $ mvn gauge:execute -DspecsDir=specs -Denv="dev"

#### maven 其他属性

可以额外设置以下插件属性：

| 属性       | 用法               | 描述                                          |
| ---------- | ------------------ | --------------------------------------------- |
| specsDir   | -DspecsDir=specs   | gauge specs 目录路径，用来执行 specs          |
| tags       | -Dtags=tag1 & tag2 | 通过 tag 表达式来筛选 specs                   |
| inParallel | -DinParallel=true  | 并行执行 specs                                |
| nodes      | -Dnodes=3          | 同 `parallel` 一同使用，设置并行执行流数量    |
| env        | -Denv=qa           | gauge 执行环境                                |
| dir        | -Ddir=.            | 设置 gauge 工作目录，默认是 project.base.dir. |
| flags      | -Dflags="–verbose" | 添加额外的 gauge 标志来执行                   |

可以查看 gauge 帮助文档，列出所有可用于 **-Dflags** 选项的 flags。

### Gradle

使用 gauge-gradle-plugin 来执行你 gauge java 项目中的 specs，并通过 gradle 管理依赖项。

#### 项目中使用插件

添加插件 **gauge**， 并添加 classpath 至你的 **build.gradle**配置中 ，下列是一个 gradle 文件示例：

```conf
apply plugin: 'java'
apply plugin: 'gauge'
apply plugin: 'application'

group = "my-gauge-tests"
version = "1.0.0"

description = "My Gauge Tests"

buildscript {
    repositories {
        mavenCentral()
    }
    dependencies {
        classpath 'com.thoughtworks.gauge.gradle:gauge-gradle-plugin:+'
    }
}

repositories {
    mavenCentral()
}

dependencies {
}

// configure gauge task here (optional)
gauge {
    specsDir = 'specs'
    inParallel = true
    nodes = 2
    env = 'dev'
    tags = 'tag1'
    additionalFlags = '--verbose'
}
```

此插件亦在 [Gradle Plugin Portal](https://plugins.gradle.org/) 可用，更多细节参考 [这里](https://plugins.gradle.org/plugin/com.thoughtworks.gauge) 。

#### 执行 specs

- 执行 gauge specs

> $ gradle specs

- 并行执行 specs

> $ gradle gauge -PinParallel=true -PspecsDir=specs

- 通过 tags 执行 specs

> $ gradle gauge -Ptags="!in-progress" -PspecsDir=specs

- 指定执行环境

> $ gradle gauge -Penv="dev" -PspecsDir=specs

备注：将 specsDir 作为最后一个参数传递。

#### gradle 其他属性

可以额外设置以下插件属性：

| 属性       | 用法               | 描述                                          |
| ---------- | ------------------ | --------------------------------------------- |
| specsDir   | -PspecsDir=specs   | gauge specs 目录路径，用来执行 specs          |
| tags       | -Ptags=tag1 & tag2 | 通过 tag 表达式来筛选 specs                   |
| inParallel | -PinParallel=true  | 并行执行 specs                                |
| nodes      | -Pnodes=3          | 同 `parallel` 一同使用，设置并行执行流数量    |
| env        | -Penv=qa           | gauge 执行环境                                |
| dir        | -Pdir=.            | 设置 gauge 工作目录，默认是 project.base.dir. |
| flags      | -Pflags="–verbose" | 添加额外的 gauge 标志来执行                   |

查看 gauge 帮助文档，列出所有可用于 **-PadditionalFlags** 选项的 flags。

## 项目中使用不同环境

特定于环境的变量可以通过使用`.properties`文件来管理。一个项目可以有多个环境，并且在执行 spec 的时候通过参数 `-env` 指定运行时加载的环境。 `default` 是默认环境，它在没有指定`-env`时被加载。

`Java` 项目环境目录结构：

```text
├── env
      └── default
         ├── default.properties
         └── java.properties
```

自定义的属性键值对，既可以添加到已有`.properties`文件，也可以添加到新创建的`.properties`文件。

### 创建新的环境

创建名为 `ci` 的环境：

1. 在 `env` 目录创建 `ci` 目录
2. 添加属性文件，比如： `user.properties`

```text
  ├── env
    ├── ci
        |── user.properties
    |── default
        ├── default.properties
        └── java.properties
```

### 执行指定环境

通过使用 `env` 标志来指定对应的环境。在运行时，在`.properties`文件中使用的键值对将被设置为环境变量。例如执行时使用 `ci` 环境：

> $ gauge run –env ci specs

### 多环境同时执行

通过使用`env`标志来指定多个环境，这可以简化测试工作。

> $ gauge run --env "\<name_of_env_1>, \<name_of_env_2>, default" specs

或者不指定`defalut`环境，但是在执行过程中，gauge 会自动将 defalut 添加到 --env 列表的末尾。也就是说下面两个命令是等效的：

> $ gauge run --env "\<name_of_env_1>, \<name_of_env_2>, default" specs
> $ gauge run --env "\<name_of_env_1>, \<name_of_env_2>" specs

### 环境优先级

环境变量值的优先级顺序如下：

1. 用户级别环境变量或者系统级别环境变量值；
2. 通过 `--env` 标志传递的项目环境变量值；
3. `gauge.properties` gauge 全局键值对配置；
4. `env/default` 目录（如果存在）内项目环境变量值；
5. Gauge 默认环境变量值，如下：

表格 6-1：

| 属性                  | 值      |
| --------------------- | ------- |
| gauge_reports_dir     | reports |
| overwrite_reports     | true    |
| screenshot_on_failure | true    |
| logs_directory        | logs    |

Gauge 加载环境变量如下：

- 项目运行后，用户传递的 `--env` 标志内的环境会被加载。如果用户没有传递此标志，则会加载 `default` 环境。
- 然后加载 `default` 环境，只有还未设置的值会被加载。这一步不会覆盖第一步里设置的变量。
- 最后 Gauge 将加载还未设置的环境变量，如表格 6-1。
- 可以通过明确设置相应的系统环境变量来覆盖这些值。
- 如果在 `--env` 标志提到的环境在项目中未被找到，则 gauge 会以非 0 退出代码结束。
- gauge 项目不需要有 `default` 环境，因为 gauge 会使用上述变量的默认值。用户仍可以设置 `default` 环境为覆盖或者添加新的环境变量，但是不用通过 `--env` 标志。

## 多环境下的工作流程

\<project_root>：项目根目录

### 未指定环境参数

> $ `gauge run specs`

- 如果 `<project_root>/env/default` 不存在，Gauge 将设置默认环境变量为表格 6-1 提到的值。
- 如果 `<project_root>/env/default` 存在，Gauge 将设置环境变量为 `default` 环境提到的值。然后设置任意变量（仍未设置的变量）如表格 6-1。

### 指定环境参数

> $ `gauge run --env==java_ci specs`

- 如果 `<project_root>/env/java_ci` 不存在，Gauge 将以非 0 退出代码结束。
- 如果 `<project_root>/env/java_ci` 存在，Gauge 将设置环境变量为 `java_ci` 环境内提到的值。然后从 `default` 环境加载还未被设置的变量。最后，设置环境变量（如果还未设置）为表格 6-1 提到的值。

### 指定某（多）个环境变量

> $ `gauge_reports_dir=newReportsDir gauge run specs`

或者用户明确地在 shell 里设置 `gauge_reports_dir=newReportsDir` 然后执行 `gauge run specs`

除了变量 `gauge_reports_dir` ，Gauge 将先从 `env/default` 目录加载，再根据表格 6-1 设置所有的默认环境变量。

### 指定环境参数+指定某（多）个环境变量

> $ `gauge_reports_dir=newReportsDir gauge run --env=java_ci specs`

或者用户明确地在 shell 里设置 `gauge_reports_dir=newReportsDir` 然后执行 `gauge run --env=java_ci specs`

Gauge 将设置环境变量为 `java_ci` 环境提到的值。然后从 `default` 环境加载还未被设置的其他变量。最后， 设置环境变量(如果还未设置)为表格 6-1 提到的值。因为变量 `gauge_reports_dir` 已经明确地在 shell 设置，其将不会被覆盖，依然是 `newReportsDir` 。


译者注：这一段，可以不用死记硬背，根据最近原则即可。

命令行指定键值对，则一定是根据指定的键值属性来运行；指定环境，根据环境内的配置文件来，其他未被配置的 key 取默认配置；什么都没有指定，全部根据默认配置来。

