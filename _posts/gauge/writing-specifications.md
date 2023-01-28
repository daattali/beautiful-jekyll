---
title: Gauge中文文档(3)—编写Specifications
date: 2017-08-30 18:00:20
updated: 2017-08-30 18:00:20
tags: ["gauge", "自动化测试工具"]
categories:
  - 软件测试
  - 测试工具
  - gauge
---

## Specifications（spec）

spec 是业务层测试用例，描述了被测应用程序的特定特征。Gauge spec 支持`.spec` 和`.md` 文件格式。以类似于 markdown 的语法编写。

- 每一个 spec 文件包含一个或者多个 `scenario（场景）`
- 每一个 spec 可以使用 `tags` 来打标签

### Specs 文件夹

在 Guage 项目被创建和初始化之后，会在项目根目录下自动新增一个名为`specs`的文件夹，以及包含名为`example.spec`的文件。这个样例文件帮助你理解怎么来编写`spec`。

{: .box-info}

`specs`目录的路径和名字可以通过修改项目中`default.properties`文件的键值对来修改。



### 示例

```md
# Search Specification

The admin user must be able to search for available products on the search page.
Tags: search, admin

- User must be logged in as "admin"
- Open the product search page

## Successful search

Tags: successful
For an existing product name, the search result will contain the product name.

- Search for product "Die Hard"
- "Die Hard11 should show up in the search results

## Unsuccessful search

On an unknown product name search the search results will be empty

- Search for product "unknown"
- The search results will be empty
```

## Specifications 的组成

一个 spec 文件由不同的部分组成，一些是可选一些事必需的。组成部分如下：

- spec 标题
- scenario 场景
- step 步骤
- parameters 参数
- tags 标签
- comments 注释

### Spec 标题

Spec 文件必须以 spec 标题开始，且一个 spec 文件只能包含一个 spec 标题。它是以`<H1>`的 markdown 语法编写，可以使用以下两种形式：

> Spec Heading
> \=\=\=\=\=\=\=\=\=\=\=\=\=\=\=

或者

> \# Spec Heading

- 每个 spec 必须包含一个或者多个 Scenarios；
- 每个 spec 可以使用 Tags 标记。

### Scenarios（场景）

每个场景代表特定 spec 中的单个工作流程。Spec 必须包含至少一个 scenario。  
一个场景在场景的标题或者场景名后开始，场景标题以`<H2>`的 markdown 语法编写，可以使用以下两种形式:

> Scenario heading  
> \-\-\-\-\-\-\-\-\-\-\-

或者

> \#\# Scenario heading

- 一个场景包含一个或者更多步骤在 scenario 名的下面
- 可以使用标签来标记场景

#### 场景示例

```md
# Configuration

The admin user should be able to switch permissions for other user.

## Admin Login

- User must login as "admin"
- Navigate to the configuration page
- Change permissions for user "john" to "admin"
- User "john" should have admin permissions
```

#### 表格驱动场景

Gauge 1.0.3 新增一个实验性功能在场景级别提供表格驱动。这样会在执行该场景时遍历表格中的每一行数据。通过修改`/env/default/default.properties`文件里面的`allow_scenario_datatable=true`来开启该功能。

```md
# Search specification

## Vowel counts in multiple word

| Word   | Vowel Count |
| ------ | ----------- |
| Gauge  | 3           |
| Mingle | 2           |
| Snap   | 1           |
| GoCD   | 1           |
| Rhythm | 0           |

This is the second scenario in this specification

Here's a step that takes a table

- The word <Word> has <Vowel Count> vowels.
```

因为这是实验性功能，所以目前在一些情况下不会生效：

- IDE 插件不支持
- CSV 文件不可以作为场景的表格数据
- 报告插件不兼容该功能

### Steps（步骤）

步骤是使用 `Markdown` 无序列表语法编写的 spec 文件中的可执行组件。在 spec 中，步骤既可以存在于场景中，也可以存在于场景之外。当在场景之外使用步骤时，它们可以是以下类型:

- context 步骤（上下文步骤）
- tear down 步骤（收尾步骤）

步骤也可以被包含在 concept 文件之中。每一个步骤都有一个使用编程语言的底层代码实现。当 spec 的步骤执行的同时底层代码被执行。参阅不同语言下的 [步骤实现](https://docs.getgauge.io/language.html#language-steps) 。

#### 步骤示例

在下面的示例中，前面带有破折号`-`的两个句子是在 `Successful search` 场景中列出的无序步骤。

```md
# Search specification

## Successful search

Tags: successful

For an existing product name, the search result will contain the product name

- Search for product "Cup Cakes"
- "Cup Cakes" should show up in the search results
```

以引号表示的值是作为语言特定结构传递到基础步骤实现的参数。**注意**：下面的字符是为参数保留的，它们不可以使用在步骤内。

- "
- <
- \>

### 参数

可以定义步骤以将值作为参数，以便可以使用不同的参数值来重新使用。

在代码里的底层步骤实现里，必须和步骤传递来的参数数量一致。传递给步骤的参数是下列类型：

#### 参数示例

在下面的例子中，"Cup Cakes"(使用双引号包围)作为两个步骤中的参数值

```md
# Search specification

## Successful search

Tags: successful

For an existing product name, the search result will contain the product name

- Search for product "Cup Cakes"
- "Cup Cakes" should show up in the search results
```

在下面的步骤例子中，参数值是"product 1" 和 "product 2"。

```md
- Check "product 1" exists
- Check "product 2" exists
```

一个步骤可以包含以下类型的参数：

- 简单参数
- 动态参数
- 表格参数
- 特殊参数

#### 1.简单参数

它们是以双引号传入到步骤里的值。如下步骤"gauge-java"和"100"便是简单参数

```md
- Create a "gauge-java" project
- Write "100" line specification
```

#### 2.动态参数

`动态参数`用作占位符，而不是实际值。在引用表格数据的表列值时使用这些参数。数据表是在 spec 开始时定义的。动态参数也可用作`concept`中的值。动态参数具有以下语法：\<dynamic_param\>

**表格中使用动态参数的示例**：

在下面的示例中，\<name\>是动态参数。 \<name\>可以使用表中`name`列中的数值，也就是“ Alice”，“ Bob”或“ Eve”。

```md
    |id| name      |
    |--|-----------|
    |1 | Alice     |
    |2 | Bob       |
    |3 | Eve       |

## First scenario

- Say "hello" to <name>.

## Second scenario

- Say "namaste" to <name>.
```

**concept 中使用动态参数的示例**：

example.cpt

```md
# A sample concept that takes a <parameter>

- And used the <parameter> in a step.
```

上述 concept 可以被调用，并且可以在调用时将值传递给参数对应位置的\<parameter\>。（译者注：可以将其理解为一个函数/方法的传参）

```md
- A sample concept that takes a "dummy value"
```

备注：有关如何使用动态参数引用表格单元格值的说明，请参阅本 [示例](https://docs.getgauge.io/longstart.html#example-inline-table) 。

#### 3.表格参数

表格参数可以在以下两种方式使用:

- 当要针对多组数据执行 spec 中的场景或者多个场景时，可以使用数据驱动执行
- 表或者内联表可以作为参数传递给步骤

#### 表格中的值在内联表内

数据表内的动态值也可以参考传递给步骤中的表格参数

```md
# Create projects

| id  | name |
| --- | ---- |
| 1   | john |
| 2   | mike |

## First scenario

- Create the following projects

  | project name | username |
  | ------------ | -------- |
  | gauge java   | <name>   |
  | gauge ruby   | <name>   |
```

在上述的示例，表格参数`<name>`使用数据表格内的动态值`john`/`mike`。(译者注：该`Create the following projects`步骤实际上会执行 4 次：2x2)

#### 特殊参数

特殊参数提供了将更强大更丰富的数据作为参数传递到步骤的能力。

- 它们在步骤中以尖括号 `<>` 输入
- 它们包含两个由冒号分割的部分:\<prefix:value\>

**Prefix** ：定义特殊参数的类型，比如：file 或者 table  
**Value** ：定义特殊参数的值：

- File
- CSV

##### 特殊参数:文件

这是通过读取文件然后将文件内容作为字符串参数传给底层步骤。  
**语法** ： \<file:[value]\> [value]是指文件的路径

{: .box-info}

[value]可以是相对或者绝对路径。相对路径相对于 [GAUGE_PROJECT_ROOT](https://docs.getgauge.io/using.html#gauge-project-root) 来解析。


示例:

```md
- Verify email text is <file:email.txt>
- Check if <file:/work/content.txt> is visible
```

文件的路径可以是相对 Gague 项目路径的相对路径或者文件的绝对路径。

##### 特殊参数:CSV

表格通常用于从外部 csv 文件读取再传递表格值给步骤。步骤中的参数文本包含前缀表和 csv 文件的路径。  
**语法** ： \<table:[value]> [value]是指 csv 文件的路径。

{: .box-info}

[value]可以是相对或者绝对路径。相对路径相对于 [GAUGE_PROJECT_ROOT](https://docs.getgauge.io/using.html#gauge-project-root) 来解析。


示例

```md
- Step that takes a table <table:data.csv>
- Check if the following users exist <table:/Users/john/work/users.csv>
```

csv 文件内容：

> Id,Name  
> 1,The Way to Go On  
> 2,Ivo Jay Balbaert

第一行被视为表头，后面的行视为列的值。

### 标签

`Tags` 用于将标签与 sepc 或者 scenarios 关联。标签用前缀 `Tags`，以及逗号分割值组成：

- Spec 和 scenarios 可以单独标记
- 只能将一组标签添加到单个 spec 或者 scenario 中

它们有助于基于使用标签来过滤 spec 或者场景。当使用的标签数量较多时，可以将标签定义为多行，以增强可读性。

#### 标签示例

在下面的例子里 `Login specification`（spec 级别） 和 `Successful login scenario` （场景级别）都有标签。

```md
# Login specification

Tags: login, admin, user-abc

## Successful login scenario

Tags: login-success, admin
```

应用在 spec 的标签自动应用在场景里。

### Concepts

Concepts 提供将步骤中的重复使用的逻辑组合到一个单元中的能力。它通过组合步骤来提供更高层次的业务抽象。它们在项目中 specs 文件夹的 .cpt 格式文件内被定义。它们也可以保存在 specs 文件夹的子目录内。

- Concepts 在 spec 的使用就象其他步骤一样，将适当的参数传递给它们。
- Concepts 下的所有步骤都按照定义的顺序执行。

**备注** ：一个 .cpt 文件可以包含多个 concept 定义

#### concept 定义

使用 concept 定义在 sepcs 文件夹内创建一个 .cpt 文件。Concept 定义包含两部分：

- Concept 标题：

  - concept 标题定义 concept 的名字和它将使用的参数。它写成 markdown `H1` 格式。
  - 所有的参数被定义在角括号 `<>`
  - 一个 concept 的定义必须包含 concept 标题: \# Concept name with \<param0> and \<param1>

- 步骤：
  - 所有从 concept 标题使用的参数在 `<>` 内
  - 固定的静态参数用 `""` 括起来
  - concept 定义也可以调用其他 concept

```md
# Login as user <username> and create project <project_name>

- Login as user <username> and "password"
- Navigate to project page
- Create a project <project_name>
```

在上面的示例：

- 第一行是 concept 标题
- 下面三行是在 concept 中的步骤

### Contexts 上下文

上下文或者上下文步骤是在任何场景之前被定义在 spec 的步骤。它们允许你指定必须用来执行 spec 步骤的条件集合。上下文步骤可以用来在执行场景前初始化数据。它们也可以完成初始化 (setup) 或者收尾 (tear down) 功能。

- 任何常规步骤可以作为上下文步骤
- 上下文在执行场景前被执行

```md
# Delete project

- Sign up for user "mike"
- Log in as "mike"

## Delete single project

- Delete the "example" project
- Ensure "example" project has been deleted

## Delete multiple projects

- Delete all the projects in the list
- Ensure project list is eapty
```

在上面的示例 spec 中， `User is logged in as Mike` 和 `Navigate to the project page`是上下文步骤，它们在任意场景前被定义。这些步骤在每个场景 `Delete single project` 和 `Delete multiple projects` 执行之前被执行。

Spec 执行过程应该是:

1. 上下文执行：包含步骤 `Sign up for user "mike"` 和步骤 `Log in as "mike"`
2. `Delete single project` 场景执行
3. 上下文执行：包含步骤 `Sign up for user "mike"` 和步骤 `Log in as "mike"`
4. `Delete multiple projects` 场景执行

### Tear Down 步骤

Tear Down 步骤在最后一个场景后被定义在 spec 内的步骤。它们允许你在每个场景执行后指定一系列清理步骤。

- 任何常规的步骤可以作为 tear down 步骤
- tear down 步骤在每个 spec 内的场景执行后被执行

#### Tear Down 语法

`___` :三个或者更多的连续下划线指示 tear down 的开始。编写在 tear down 内（在三个或者更多联系的下划线之后）的步骤将被认为是 tear down 步骤。

```md
---

- tear down step 1
- tear down step 2
- tear down step 3
```

#### Tear Down 示例

```md
# Delete project

- Sign up for user "mike"
- Log in as "mike"

## Delete single project

- Delete the "example" project
- Ensure "example" project has been deleted

## Delete multiple projects

- Delete all the projects in the list
- Ensure project list is eapty

---

These are teardown steps

- Logout user "mike"
- Delete user "mike"
```

在上述示例 spec 中， `Logout user "mike"` 和 `Delete user "mike"` 是 tear down 步骤，它们在三个或者更多连续下划线后被定义。Spec 执行过程应该是:

1. 上下文执行
2. `Delete single project` 场景执行
3. Tear down 步骤执行
4. 上下文执行
5. `Delete multiple projects` 场景执行
6. Tear down 步骤执行

### 步骤实现

每个步骤的实现都对应于安装 Gauge 时所使用的语言插件等效的代码。代码在执行 spec 中的步骤时运行。该代码必须具有与该步骤中提到的相同数量的参数。
可以用不同的方式来实现步骤，例如简单步骤，表格参数步骤，步骤别名以及用作步骤参数的枚举数据类型。

#### 简单步骤

> \* Say “hello” to “gauge”

##### 代码实现

{% tabs langauge %}

<!-- tab <code>C#</code> -->

```C#
// 方法可以写在任意C#文件内，做为项目的一部分
public class StepImplementation {

    [Step("Say <greeting> to <product name>")]
    public void HelloWorld(string greeting, string name) {
        // Step implementation
    }

}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
// 该方法可以在任意java类中编写，只要它在classpath中
public class StepImplementation {

    @Step("Say <greeting> to <product name>")
    public void helloWorld(String greeting, String name) {
        // Step implementation
    }

}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```js
step("Say <greeting> to <name>", function (greeting, name, done) {
  try {
    setTimeout(function () {
      // Code for step
      done();
    }, 1000);
  } catch (e) {
    done(e);
  }
});

// Handling errors in promises with done
step("Say <greeting> to <name>", function (greeting, name, done) {
  // Let promise1 be some promise we need to wait for.
  promise1.then(done).catch(function (e) {
    done(e);
  });
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
@step("Say <greeting> to <product name>")
def hello_world(greeting, name):
  assert False, "Add implementation code"
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
step 'Say <greeting> to <product name>' do |greeting, name|
  # Code for the step
end
```

<!-- endtab -->

{% endtabs %}

#### 步骤别名

当同一步骤功能有多个步骤名称时，步骤别名就是一项功能。步骤实现中的参数必须与所有步骤名称中使用的参数的数量和类型相匹配。当以不同方式表示相同功能时，可以在 spec 中使用步骤别名功能。这增强了 spec 的可读性。
步骤别名功能可帮助你遵循良好的软件工程实践，例如在代码级别遵循 DRY（不要自己重复）原则，同时确保清楚地表达功能。

**示例 1**

在下面的例子中，`Create a user "user 1"` 和 `Create another user "user 2"` 属于步骤别名，因为他们有相同的步骤实现，但是表达却各异。

```md
# User Creation

## Multiple Users

- Create a user "user 1"
- Verify "user 1" has access to dashboard
- Create another user "user 2"
- Verify "user 2" has access to dashboard
```

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
public class Users {

    [Step("Create a user <user_name>", "Create another user <user_name>")]
    public void CreateUser(string user_name) {
        // create user user_name
    }

}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
public class Users {

    @Step({"Create a user <user_name>", "Create another user <user_name>"})
    public void createUser(String user_name) {
        // create user user_name
    }

}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
step(["Create a user <username>", "Create another user <username>"], function (username) {
        // do cool stuff
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
@step(["Create a user <user name>", "Create another user <user name>"])
def create_user(user_name):
  print("create {}.".format(user_name))
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
step 'Create a user <user name>','Create another user <user name>' do |user_name|
    // create user user_name
end
```

<!-- endtab -->

{% endtabs %}

**示例 2**

在下面的例子中，两个场景中发送邮件的功能相同，但表述各异。

```md
## User Creation

- User creates a new account
- A "welcome" email is sent to the user

## Shopping Cart

- User checks out the shopping cart
- Payment is successfully received
- An email confirming the "order" is sent
```

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
public class Users {

    [Step({"A <email_type> email is sent to the user",
    "An email confirming the <email_type> is sent"})]
    public void SendEmail(string email_type) {
        // Send email of email_type
    }
}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
public class Users {

    @Step({"A <email_type> email is sent to the user",
    "An email confirming the <email_type> is sent"})
    public void sendEmail(String email_type) {
        // Send email of email_type
    }
}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
step(["A <email_type> email is sent to the user",
    "An email confirming the <email_type> is sent"],
function (email_type) {
    // do cool stuff
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import step

@step(["A <email_type> email is sent to the user",
    "An email confirming the <email_type> is sent"])
def email(email_type):
  print("create {}.".format(email_type))
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
step 'A <email_type> email is sent to the user',
  'An email confirming the <email_type> is sent' do |email_type|
  email_service.send email_type
end
```

<!-- endtab -->

{% endtabs %}

### 枚举做为参数

{: .box-info}

该功能仅仅支持`Java`


可以将`Enum`数据类型的常量值用作步骤中的参数。但是，参数的类型应与步骤实现代码中的 Enum 名称匹配。

在下面的示例中，参数 SOUTH 为“ Enum”数据类型。在等效代码中，参数\<direction\>与枚举名称`Direction`匹配。

```md
- Navigate towards "SOUTH"
```

实现

```java
public enum Direction { NORTH, SOUTH, EAST, WEST; }

@Step("Navigate towards <direction>")
public void navigate(Direction direction) {
    //  code here
}
```

### 注释

注释无格式，任何普通的文本行都被当作注释。

```md
I’m a comment! 这是一段注释!
```

### 图片

内联图片语法如下所示：

```md
![Alt text](/path/to/img.jpg)
![Alt text](/path/to/img.jpg “Optional title”)
```

图片的路径应该是当前目录的相对路径。

### 链接

```md
This is [an example]([http://getgauge.io](http://getgauge.io) “Title) inline link.
[This link](<[http://github.com/getgauge/gauge](http://github.com/getgauge/gauge)>) has no title attribute.
```

## 执行钩子

在测试套件执行期间，可以使用测试执行钩子作为不同的级别运行任意测试代码。

### 钩子实现

{% tabs language %}

<!-- tab <code>C#</code> -->

默认情况下，Gauge 会在每个场景之后清除状态，以便为下一个场景执行时创建新对象。你可以使用`csharp.properties`文件配置 Gauge 清除内存对象的级别。

有关在`csharp.properties`文件中配置适当的环境变量的更多信息，请参阅[语言插件配置](https://docs.gauge.org/configuration.html#language-config)

```C#
public class ExecutionHooks
{

    [BeforeSuite]
    public void BeforeSuite() {
        // Code for before suite
    }

    [AfterSuite]
    public void AfterSuite() {
        // Code for after suite
    }

    [BeforeSpec]
    public void BeforeSpec() {
        // Code for before spec
    }

    [AfterSpec]
    public void AfterSpec() {
        // Code for after spec
    }

    [BeforeScenario]
    public void BeforeScenario() {
        // Code for before scenario
    }

    [AfterScenario]
    public void AfterScenario() {
        // Code for after scenario
    }

    [BeforeStep]
    public void BeforeStep() {
        // Code for before step
    }

    [AfterStep]
    public void AfterStep() {
        // Code for after step
    }

}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

默认情况下，Gauge 会在每个场景之后清除状态，以便为下一个场景执行时创建新对象。你可以使用`java.properties`文件配置 Gauge 清除内存对象的级别。

有关在`java.properties`文件中配置适当的环境变量的更多信息，请参阅[语言插件配置](https://docs.gauge.org/configuration.html#language-config)

```Java
public class ExecutionHooks {

    @BeforeSuite
    public void BeforeSuite() {
        // Code for before suite
    }

    @AfterSuite
    public void AfterSuite() {
        // Code for after suite
    }

    @BeforeSpec
    public void BeforeSpec() {
        // Code for before spec
    }

    @AfterSpec
    public void AfterSpec() {
        // Code for after spec
    }

    @BeforeScenario
    public void BeforeScenario() {
        // Code for before scenario
    }

    @AfterScenario
    public void AfterScenario() {
        // Code for after scenario
    }

    @BeforeStep
    public void BeforeStep() {
        // Code for before step
    }

    @AfterStep
    public void AfterStep() {
        // Code for after step
    }

}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
beforeSuite(fn, [opts]) {
    // Code for before suite
}

beforeSpec(fn, [opts]) {
    // Code for before spec
}

beforeScenario(fn, [opts]) {
    // Code for before scenario
}

beforeStep(fn, [opts]) {
    // Code for before step
}

afterSuite(fn, [opts]) {
    // Code for after suite
}

afterSpec(fn, [opts]) {
    // Code for after spec
}

afterScenario(fn, [opts]) {
    // Code for after scenario
}

afterStep(fn, [opts]) {
    // Code for after step
}
```

在钩子中处理异步代码

```Javascript
// using done
beforeStep(function (context, done) {
    setTimeout(function() {
        done();
    }, 1000);
});

// using async functions
beforeStep(async function () {
    // async code for before step
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import before_step, after_step, before_scenario, after_scenario, before_spec, after_spec, before_suite, after_suite

@before_step
def before_step_hook():
    print("before step hook")

@after_step
def after_step_hook():
    print("after step hook")

@before_scenario
def before_scenario_hook():
    print("before scenario hook")

@after_scenario
def after_scenario_hook():
    print("after scenario hook")

@before_spec
def before_spec_hook():
    print("before spec hook")

@after_spec
def after_spec_hook():
    print("after spec hook")

@before_suite
def before_suite_hook():
    print("before suite hook")

@after_suite
def after_suite_hook():
    print("after suite hook")
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
before_suite do
    # Code for before suite
end

after_suite do
    # Code for after suite
end

before_spec do
    # Code for before spec
end

after_spec do
    # Code for after spec
end

before_scenario do
    # Code for before scenario
end

after_scenario do
    # Code for after scenario
end

before_step do
    # Code for before step
end

after_step do
    # Code for after step
end
```

<!-- endtab -->

{% endtabs %}

### 钩子中的当前执行上下文

为了获得有关当前 spec，场景和步骤执行的其他信息，可以将一个名为`ExecutionContext`的附加参数添加到钩子方法中。

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
using Gauge.CSharp.Lib;
using static Gauge.CSharp.Lib.ExecutionContext;

[BeforeScenario]
public void BeforeScenario(ExecutionContext context)
{
    String scenarioName = context.CurrentScenario.Name;
    //Code for before scenario
}

[AfterSpec]
public void AfterSpec(ExecutionContext context)
{
    Specification specification = context.CurrentSpecification;
    //Code for after spec
}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
@BeforeScenario
public void loginUser(ExecutionContext context) {
    String scenarioName = context.getCurrentScenario().getName();
    // Code for before scenario
}

@AfterSpec
public void performAfterSpec(ExecutionContext context) {
Specification currentSpecification = context.getCurrentSpecification();
    //Code for after spec
}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
beforeScenario(function (context) {
    var scenario = context.currentScenario
    // Code for before scenario
});

afterSpec(function (context) {
    var specification = context.currentSpec
    //Code for after spec
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import before_step, after_scenario

@before_step
def before_step_hook(context):
    print(context)

@after_spec
def after_spec_hook(context):
    print(context)
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
before_spec do |execution_info|
    puts execution_info.inspect
end

after_spec do |execution_info|
    puts execution_info.inspect
end
```

<!-- endtab -->

{% endtabs %}

### 基于标签筛选钩子执行

你可以指定执行钩子可以运行的标签。这样可以确保钩子仅在具有指定标签的场景和 spec 上运行。

{: .box-info}

Tags 不可以通过 `@BeforeSuite` 和 `@AfterSuite`钩子来指定


{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
// 在当前spec和场景中，运行在tag1和tag2标签之前的before spec钩子
[BeforeSpec("tag1, tag2")]
public void LoginUser() {
    // Code for before scenario
}

// 在当前spec和场景中，运行在tag1 或者 tag2标签的步骤之后的钩子
// 默认的tag表达式为 Operator.AND 即：tag1 & tag2
// 当前tag表达式已经被修改
[AfterStep("tag1", "tag2")]
[TagAggregationBehaviour(TagAggregation.Or)]
public void PerformAfterStep() {
    // Code for after step
}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
// 在当前spec和场景中，运行在tag1和tag2标签之前的before spec钩子
@BeforeSpec(tags = {"tag1, tag2"})
public void loginUser() {
    // Code forbefore scenario
}

// 在当前spec和场景中，运行在tag1 或者 tag2标签的步骤之后的钩子
// 默认的tag表达式为 Operator.AND 即：tag1 & tag2
// 当前tag表达式已经被修改
@AfterStep(tags = {"tag1", "tag2"}, tagAggregation = Operator.OR)
public void performAfterStep() {
    // Code for after step
}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
// A before spec hook that runs when tag1 and tag2
// is present in the current scenario and spec.
beforeSpec(function () {
    //implementation
}, { tags: [ "tag1", "tag2" ]});

// A after step hook runs when tag1 or tag2
// is present in the currentscenario and spec.
// Default tagAggregation value is Operator.AND.
afterStep(function () {
    //implementation
}, { tags: [ "tag1", "tag2" ]});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
# 在当前spec和场景中，运行在tag1和tag2标签之前的before spec钩子
@before_spec("<tag1> and <tag2>")
def before_spec_hook():
    print("before spec hook with tag")

# 在当前spec和场景中，运行在tag1 或者 tag2标签的步骤之后的钩子
# 默认的tag表达式为 Operator.AND 即：tag1 & tag2
# 当前tag表达式已经被修改
@after_step("<tag1> and <tag2>")
def after_step_hook():
    print("after step hook with tag")
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
# 在当前spec和场景中，运行在tag1和tag2标签之前的before spec钩子
before_spec({tags: ['tag2', 'tag1']}) do
    # Code for before scenario
end

# 在当前spec和场景中，运行在tag1 或者 tag2标签的步骤之后的钩子
# 默认的tag表达式为 Operator.AND 即：tag1 & tag2
# 当前tag表达式已经被修改
after_step({tags: ['tag2', 'tag1'], operator: 'OR'}) do
    # Code for after step
```

<!-- endtab -->

{% endtabs %}

## 数据存储

使用 Gauge 公开的 DataStore，可以在运行时在不同类中定义的步骤中共享数据（对象）。

根据清除内存中对象的生命周期，有三种不同类型的数据存储。

### ScenarioStore 场景级别

在场景执行的生命周期内，此 DataStore 会将值添加到内存中。执行每个场景后，将会清除该值。

### SpecStore spec 级别

在 spec 执行的生命周期内，此 DataStore 会将值添加到内存中。执行每个 spec 后，将会清除该值。

### SuiteStore 测试套件级别

在整个测试套件执行的生命周期内，此 DataStore 会将值添加到内存中。在整个测试套件执行完后将会清除该值。

### 不同级别使用示例

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
using Gauge.CSharp.Lib;

// 场景级别
// 存储数值
var scenarioStore = DataStoreFactory.ScenarioDataStore;
scenarioStore.Add("element-id", "455678");

// 获取数值
var elementId = (string) scenarioStore.Get("element-id");

// avoid type cast by using generic Get
var anotherElementId = scenarioStore.Get("element-id");

// spec级别
// 存储数值
var specStore = DataStoreFactory.SpecDataStore;
specStore.Add("element-id", "455678");

// 获取数值
var elementId = (string) specStore.Get("element-id");

// avoid type cast by using generic Get
var anotherElementId = specStore.Get("element-id");


// 测试套件级别
// 存储数值
var suiteStore = DataStoreFactory.SuiteDataStore;
suiteStore.Add("element-id", "455678");

// 获取数值
var suiteStore = DataStoreFactory.SuiteDataStore;
var elementId = (string) suiteStore.Get("element-id");

// Avoid type cast by using generic Get
var anotherElementId = suiteStore.Get("element-id");
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
// 场景级别
import com.thoughtworks.gauge.datastore.ScenarioDataStore;

// 存储数值
ScenarioDataStore.put("element-id", "455678");

// 获取数值
String elementId = (String) ScenarioDataStore.get("element-id");

// spec级别
import com.thoughtworks.gauge.datastore.SpecDataStore;

// 存储数值
SpecDataStore.put("key", "455678");

// 获取数值
String elementId = (String) SpecDataStore.get("key");

// 测试套件级别
import com.thoughtworks.gauge.datastore.SuiteDataStore;

// 存储数值
SuiteDataStore.put("element-id", "455678");

// 获取数值
String elementId = (String) SuiteDataStore.get("element-id");
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
// 场景级别
// 存储数值
gauge.dataStore.scenarioStore.put(key, value);

// 获取数值
gauge.dataStore.scenarioStore.get(key);

// spec级别
// 存储数值
DataStore specStore = gauge.dataStore.specStore.put(key, value);

// 获取数值
DataStore specStore = gauge.dataStore.specStore.get(key);

// 测试套件级别
// 存储数值
DataStore suiteStore = gauge.dataStore.suiteStore.put(key, value);

// 获取数值
DataStore specStore = gauge.dataStore.suiteStore.get(key);
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import data_store

# 场景级别
# 存储数值
data_store.scenario["key"] = value
# OR
data_store.scenario.key = value

# 获取数值
data_store.scenario["key"]
# OR
data_store.scenario.key

# spec级别
# 存储数值
data_store.spec["key"] = value
# OR
data_store.spec.key = value

# 获取数值
data_store.spec["key"]
# OR
data_store.spec.key

# 测试套件级别
 # 存储数值
data_store.suite["key"] = value
# OR
data_store.suite.key = value

# 获取数值
data_store.suite["key"]
# OR
data_store.suite.key
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
# 场景级别
# 存储数值
scenario_store = DataStoreFactory.scenario_datastore;
scenario_store.put("element-id", "455678");

# 获取数值
element_id = scenario_store.get("element-id");

# spec级别
# 存储数值
spec_store = DataStoreFactory.spec_datastore;
spec_store.put("element-id", "455678");

# 获取数值
element_id = spec_store.get("element-id");

# 测试套件级别
# 存储数值
suite_store = DataStoreFactory.suite_datastore;
suite_store.put("element-id", "455678");

# 获取数值
suite_store = DataStoreFactory.suite_datastore;
element_id = suite_store.get("element-id");
```

<!-- endtab -->

{% endtabs %}

## 采用自定义截屏

当 Gauge 截屏时，默认会捕捉屏幕上显示的任何内容。如果你想定制此行为并使 Gauge 能够截取你选择的屏幕快照(例如，你可能想要只截取浏览器页面的屏幕快照)，那么你可以在创建 Gauge 项目时使用，在对应语言的步骤实现中使用适当的驱动程序 api。

{: .box-info}

如果在类路径中发现多个自定义截取屏幕实现，那么 gauge 将`随机`选择一个来截屏。这是因为 gauge 选择它找到的第一个截屏代码实现，而这又取决于库的扫描顺序。


{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
//Using Webdriver public
class CustomScreenGrabber : ICustomScreenshotGrabber {

    // Return a screenshot byte array
    public byte[] TakeScreenshot() {
        var driver = DriverFactory.getDriver();
        return ((ITakesScreenshot) driver).GetScreenshot().AsByteArray;
    }
}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
public class CustomScreenshotGrabber implements CustomScreenshotWriter {

    // Return a screenshot file name
    @Override
    public String takeScreenshot() {
        TakesScreenshot driver = (TakesScreenshot) DriverFactory.getDriver();
        String screenshotFileName = String.format("screenshot-%s.png", UUID.randomUUID().toString());
        File screenshotFile = new File(Paths.get(System.getenv("gauge_screenshots_dir"), screenshotFileName).toString());
        File tmpFile = driver.getScreenshotAs(OutputType.FILE);
        try {
            FileUtils.copyFile(tmpFile, screenshotFile);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return screenshotFileName;
    }

}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
// Using Taiko
// Return a screenshot file name
gauge.customScreenshotWriter = async function () {
    const screenshotFilePath = path.join(process.env['gauge_screenshots_dir'], `screenshot-${process.hrtime.bigint()}.png`);
    await screenshot({ path: screenshotFilePath });
    return path.basename(screenshotFilePath);
};
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
# Using Webdriver
from uuid import uuid1
from getgauge.python import custom_screenshot_writer

# Return a screenshot file name
@custom_screenshot_writer
def take_screenshot():
    # Use appropriate webdriver instance
    image = driver.get_screenshot_as_png()
    file_name = os.path.join(os.getenv("gauge_screenshots_dir"), "screenshot-{0}.png".format(uuid1().int))
    file = open(file_name, "wb")
    file.write(image)
    return os.path.basename(file_name)
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
# Using Webdriver
Gauge.configure do |config|
    config.custom_screenshot_writer = -> {
        screenshot_data = driver.screenshot_as(:png)
        file = File.join(config.screenshot_dir, "screenshot-#{(Time.now.to_f*10000).to_i}.png")
        File.write(file, screenshot_data)
        File.basename(file)
    }
end
```

<!-- endtab -->

{% endtabs %}

## 报告中添加截屏

如果在运行 spec 时出现任何故障，默认会捕捉到此类故障的截图。如果你想让 spec 在任何时间点捕获截屏，当 spec 运行时，调用对应的 API:

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
GaugeScreenshots.Capture();
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
Gauge.captureScreenshot();
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
gauge.screenshot();
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import Screenshots

Screenshots.capture_screenshot()
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
Gauge.capture
```

<!-- endtab -->

{% endtabs %}

该 API 可以在步骤实现或者钩子中使用，在执行报告中，这些截屏会显示在步骤之后。

## 报告中添加自定义消息

自定义消息或自定义数据，可以通过调用步骤实现或者钩子中的 API 来添加到执行报告里。这些消息将会展示在步骤之后。

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
GaugeMessages.WriteMessage("Custom message for report");
var id = "4567";
GaugeMessages.WriteMessage("User id is {0}", id);
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
Gauge.writeMessage("Custom message for report");
String id = "4567";
Gauge.writeMessage("User id is %s", id);
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
gauge.message("Custom message for report");
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
from getgauge.python import Messages
Messages.write_message("Custom message for report")
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
Gauge.write_message("Custom message for report")
id = "4567"
Gauge.write_message("User id is" + id)
```

<!-- endtab -->

{% endtabs %}

## 失败继续执行

Gauge 默认在第一个失败步骤时中断执行。所以如果场景中的第一个步骤失败了，随后的所有步骤都将跳过执行。虽然这适用于大多数用例，但是有时你需要执行场景中的所有步骤，而不管前面的步骤成功与否。

为了解决这个要求，Gauge 为对应语言执行器提供了一种方法，可以将步骤标记为可恢复，具体取决于步骤实现是否有明确要求。每个语言执行器使用不同的语法，具体取决于语言习语，允许标记步骤实现为失败继续执行。

{% tabs language %}

<!-- tab <code>C#</code> -->

```C#
// The ``[ContinueOnFailure]`` attribute tells Gauge to continue executing others
// steps even if the current step fails.

public class StepImplementation {
    [ContinueOnFailure]
    [Step("Say <greeting> to <product name>")]
    public void HelloWorld(string greeting, string name) {
        // If there is an error here, Gauge will still execute next steps
    }

}
```

<!-- endtab -->
<!-- tab <code>Java</code> -->

```Java
// The ``@ContinueOnFailure`` annotation tells Gauge to continue executing other
// steps even if the current step fails.

public class StepImplementation {
    @ContinueOnFailure
    @Step("Say <greeting> to <product name>")
    public void helloWorld(String greeting, String name) {
        // If there is an error here, Gauge will still execute next steps
    }

}

// 指定错误类列表
@ContinueOnFailure({AssertionError.class, CustomError.class})
@Step("hello")
public void sayHello() {
  // code here
}

@ContinueOnFailure(AssertionError.class)
@Step("hello")
public void sayHello() {
  // code here
}

@ContinueOnFailure
@Step("hello")
public void sayHello() {
  // code here
}
```

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```Javascript
// The ``@ContinueOnFailure`` annotation tells Gauge to continue executing other
// steps even if the current step fails.

gauge.step("Say <greeting> to <product>.", { continueOnFailure: true}, function (greeting,product) {
});
```

<!-- endtab -->
<!-- tab <code>Python</code> -->

```Python
 # The ``@ContinueOnFailure`` annotation tells Gauge to continue executing other
# steps even if the current step fails.

@continue_on_failure([RuntimeError])
@step("Say <greeting> to <product>")
def step2(greeting,product):
    pass
```

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```Ruby
# The ``:continue_on_failure => true`` keyword argument
# tells Gauge to continue executing other steps even
# if the current step fails.

step 'Say <greeting> to <name>', :continue_on_failure => true do |greeting, name|
    # If there is an error here, Gauge will still execute next steps
end
```

<!-- endtab -->

{% endtabs %}

`ContinueOnFailure`可以采用一个可选参数来指定异常类列表，在发生异常时，将在这些异常类上继续执行下一步的步骤。该可选的参数可以用来控制什么类型的异常`Gauge`必须继续执行，而不是继续执行每一个异常。

例如，当 `RuntimeException` 异常发生时，理想情况下不希望继续进一步执行。但是，如果是断言错误，则继续执行测试可能没有问题。目前只支持`Java`和`Python`。

如果 ContinueOnFailure 没有参数，那么无论发生哪种类型的异常，步骤执行都会默认继续。

## Gauge 项目结构

当为特定语言插件初始化一个 Gauge 项目时，在\<project_root\>处创建一个项目结构。这个项目的结构由：特定于语言的文件（取决于所使用的语言插件）以及所有语言插件共有文件和目录组成。

\<project_root\> -Gauge 项目创建的位置。

### 通用 Gauge 项目结构

共有项目文件包含以下：

- env 目录
- logs 目录
- specs 目录
- manifest.json 文件

```tree
├── env
│  └── default
│     └── default.properties
├── logs
├── manifest.json
├── specs
   └── example.spec
```

#### env 目录

env 文件夹包含多个特定于环境的目录。每一个目录都有`.property`文件，定义了在 spec 执行期间为特定环境设置的环境变量。

初始化 Gauge 项目时，将创建一个 `env/default` 目录。默认目录具有 `default.properties` 文件，该文件包含在 spec 执行期间设置的默认环境变量。此目录还具有特定于语言的`.property` 文件，其中包含特定于语言的环境变量。

#### specs 目录

specs 目录包含该项目的所有 spec 文件。在此目录中创建了一个名为 example.spec 的 spec 样本文件，以了解 spec 文件的格式。

spec 是用 Markdown 编写的业务测试用例，描述了需要测试的应用程序的特定功能。

#### manifest.json 文件

该文件包含了项目所需的插件以及语言信息。在 Gauge 项目初始化之后，该文件具有如下信息：

```json
{
  "Language": "<language>",
  "Plugins": ["html-report"]
}
```

- Language： 指示测试代码所使用的语言，Gauge 通过对应的语言执行器来运行对应的 spec
- Plugins： 指示项目所使用的插件列表。有些插件在每个项目中是默认使用的，也可以通过安装所需的插件，将其添加到项目中使用

例如：你想要添加`xml-report`插件到该文件中，那么你必须先安装该插件，在插件安装完成之后，文件显示如下：

```json
{
  "Language": "<language>",
  "Plugins": ["html-report", "xml-report"]
}
```

### 不同语言项目结构

{% tabs language %}

<!-- tab <code>C#</code> -->

```text
├── foo.csproj
├── foo.sln
├── manifest.json
├── packages.config
├── StepImplementation.cs
│
├── env
│   └───default
│           csharp.properties
│
├───packages
    └───<Nuget Package Binaries>
├───Properties
│       AssemblyInfo.cs
│
└───specs
        example.spec
```

**packages.config**
Nuget 包二进制文件包含 Gauge 的 Nuget 依赖项。

**StepImplementation.cs**
该文件包含定义在 `example.spec` 中的简单步骤实现

<!-- endtab -->
<!-- tab <code>Java</code> -->

```text
├── manifest.json
├── libs
└── src
    └── test
        └── java
            └── StepImplementation.java
├── env
    └── default
        └── java.properties
└───specs
    example.spec
```

**libs**
该目录包含项目所需的 Java 依赖

**src**
该目录包含步骤实现对应的 Java 类

<!-- endtab -->
<!-- tab <code>Javascript</code> -->

```text
├── manifest.json
└── tests
        └── step_implementation.js
├── env
    └── default
        └── js.properties
└───specs
        example.spec
```

**tests**
该目录包含步骤实现对应的测试代码

<!-- endtab -->
<!-- tab <code>Python</code> -->

```text
├── manifest.json
└── step_impl
        └── step_impl.py
├── env
    └── default
        └── python.properties
└───specs
    example.spec
```

**step_impl**
该目录包含步骤实现对应的测试代码

<!-- endtab -->
<!-- tab <code>Ruby</code> -->

```text
├── manifest.json
├── env
│   └── default
│       └── ruby.properties
└── step_implementations
    └── step_implementation.rb
└───specs
        example.spec
```

**step_implementations**
该目录包含步骤实现对应的测试代码

<!-- endtab -->

{% endtabs %}
