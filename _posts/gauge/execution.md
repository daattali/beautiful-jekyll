---
title: Gauge中文文档(4)—执行Specifications
date: 2017-09-06 19:25:58
updated: 2017-09-06 19:25:58
tags: ["gauge", "自动化测试"]
categories:
  - 软件测试
  - 测试工具
  - gauge
---

本章节会提供如下信息：如何执行 Gauge Spec 文件；使用`gauge run`命令执行 spec 时使用的多个参数；详细的报告；数据驱动执行；spec 并行执行；如何重新运行失败和不稳定的测试；运行 spec 时发生的错误以及故障排除信息。

有关 spec 的更多信息，请参阅[编写 Specifications 章节](https://www.nothinghere.cn/gauge/writing-specifications/)。

## 执行 Spec

可以通过执行 `gauge run` 命令来执行 Gauge spec 文件。当该命令被执行时，`Gauge` 会扫描当前项目的根目录以及其子目录，并选择有效的 spec 文件。


你必须已经创建了对应的 specs 目录，或者在默认配置文件内设置了对应的 spec 执行路径。


在项目根目录下，使用如下命令执行 Gauge spec:

> $ gague run [args] [flags]

- args: spec 文件存放目录，spec 文件路径，或（和）场景路径
- flags: 可选项，比如 `--tags`，`-e`，`-f` 等等

注意：spec 也可以通过 IDE 执行，比如 VScode 或者 IDEA 等等

## 通过 gauge run 传递多个参数

在执行`gauge run`命令时，可以通过选择对应的 spec 目录，spec 文件，场景级别，或者三者之间的组合来传递适当的参数。这些参数之间需要通过空格进行分隔。

这些参数可以是下列中其一：

- 包含 spec 文件的目录或者子目录
- spec 文件的路径或者场景路径
- 以上参数的组合

## 使用目录作为执行 spec 参数

Gauge 可以从单个目录、子目录或多个目录中运行。你可以使用 `gauge run` 命令指定目录或子目录的路径。

项目根目录下的目录：

> $ gauge run specs  
> $ gauge run test_specs

项目根目录下的子目录：

> $ gauge run \<path_dir>
> $ gauge run specs/sub1_specs specs/sub2_specs

多个目录或者子目录组合：

> $ gauge run \<dir1> \<path_dir2> \<path_dir3>
> $ gauge run specs test_specs

## 使用文件作为执行 spec 参数

通过使用`gauge run`命令提供这些 spec 的确切位置，你可以选择并仅运行某些 spec。

运行单个文件：

> $ gauge run \<path_to_spec>
> $ gauge run specs/example.spec

运行多个文件：

> $ gauge run \<path_to_spec1> \<path_to_spec2> \<path_to_spec3>
> $ gauge run specs/example.spec specs/sub1_specs/sub1_example.spec

## 使用场景路径作为执行 spec 参数

你可以选择仅运行 spec 的某个（多个）场景。`gauge run`命令的参数可以是特定场景或场景列表以及该场景范围内的行号。可以使用场景跨越的任何行号。

单个场景：

> $ gauge run \<specification_path>:\<scenario_line_number>

多个场景：

> $ gauge run \<specification_path>:\<scenario_line_number> \<specification_path>:\<scenario_line_number>...

假设在项目根目录，specs 文件夹内包含 spec1.spec 文件（注意：为方便查看行号是另外加的，一般 IDE 才上会显示）：

```md
1 # Configuration
2
3 ## Admin Login
4 _ User must login as "admin"
5 _ Navigate to the configuration page
6
7 ## User Login
8 _ User must login as "user1"
9 _ Navigation to configuration page is restricted.
```

为执行第二个场景：`User Login`，使用如下命令：

> $ gauge run specs/spec1.spec:7

第 7 行指示将要执行的第二个场景，因为场景范围从第 7 行到第 9 行，你可以使用 7~9 之间的任意数字。

除了上述 `spec1.spec` 文件之外，如果在 specs 目录里还有另外一个 `test1.spec` 文件：

```md
1 # Search specification
2
3 ## Successful search
4 _ Log in as "admin"
5 _ Open the product search page
6 _ Search for product "Cup Cakes"
7 _ "Cup Cakes" should show up in the search results
```

为同时执行上面两个文件内的`Admin Login`场景和`Successful search`场景：

> gauge run specs/spec1.spec:3 specs/test1.spec:4

注意：test1.spec 也可以位于非 specs 目录。

## 使用标签筛选 spec 和场景

你可以将`--tags`标志与`gauge run`命令一起使用，以过滤 spec 和场景。前提是：你必须在 spec 或者场景内有添加 `Tags`。

> $ gauge run --tags tag1,tag2 spec

或者

> $ gauge run --tags "tag1, tag2" specs

这仅执行标记有 `tag1` 和 `tag2` 的场景和 spec。

```md
# Search Specification

The admin user must be able to search for available
products on the search page.

Tags: search, admin

- User must be logged in as "admin"
- Open the product search page

## Successful search

Tags: successful

For an existing product name, the search result will
contain the product name.

- Search for product "Cup Cakes"
- "Cup Cakes" should show up in the search results

## Unsuccessful search

On an unknown product name search, the search results
will be empty

- Search for product "unknown"
- The search results will be empty
```

在上述 spec 中，如果想要同时标记有`search`和`admin`的所有场景被执行，使用下列命令：

> $ gauge run --tags "search & admin" SPEC_FILE_NAME

如果想要标记有`search` 或者 `admin`的场景被执行，使用下列命令：

> $ gauge run --tags "search" SPEC_FILE_NAME
> $ gauge run --tags "admin" SPEC_FILE_NAME

## Tags 表达式

标签可以与表达式一起使用。这可以帮助你有效地搜索和过滤 spec 和场景。下表列出了在选择 spec 和场景时的标签和表达式及其相应的操作。


命令行内使用`非 - !` 符号时，必须在`!`带上转义符`\`


| Tags                   | 选择的 spec/场景                        |
| ---------------------- | --------------------------------------- |
| !TagA                  | 不包含标签 TagA                         |
| TagA & TagB            | 同时包含 TagA 和 TagB.                  |
| TagA & !TagB           | 有标签 TagA 但没有标签 TagB.            |
| TagA \| TagB           | 有标签 TagA 或 TagB.                    |
| (TagA & TagB) \| TagC  | 有标签 TagC 或者同时包含 TagA 和 TagB   |
| !(TagA & TagB) \| TagC | 有标签 TagC 或者不同时包含 TagA 和 TagB |
| (TagA \| TagB) & TagC  | 包含 [TagA 和 TagC] 或者 [TagB 和 TagC] |

## 详细的报告

默认情况下，Gauge 会生成报告，这些报告在执行时显示 spec 是通过还是失败。为了简化调试，还可以为每个步骤生成报告，以显示步骤是否已成功执行。可以使用 `--verbose` 标志生成此类报告。这些报告在控制台上生成。

> $ gauge run --verbose specs

## 数据驱动执行

在步骤开始之前，在 spec 开始时以 Markdown 表格格式定义了数据表。数据表应具有标题行和一个或多个数据行。该表中的标题名称可以在尖括号`<>`中的步骤中使用，以引用数据表中的特定列作为参数。
运行 spec 时，将对表的每个数据行执行每种场景。表参数以 Multi-Markdown 表格式编写。

### 示例

```md
# Table driven execution

| id  | name      |
| --- | --------- |
| 1   | vishnu    |
| 2   | prateek   |
| 3   | navaneeth |

## Scenario

- Say "hello" to <name>

## Second Scenario

- Say "namaste" to <name>
```

在上面的示例，步骤使用数据表格中的 `name` 列作为动态参数。

`Scenario` 和 `Second Scenario` 都会首先执行第一行数据 `1,vishnu`，然后连续地执行表格中第二和第三行的值。

### 选中数据表格行

默认情况下，spec 中的场景会针对所有数据表格行运行。可以使用标志 `--table-rows` 针对选定的数据表行运行，并指定应执行场景的行号。如果有多个行号，则应以逗号分隔。注意：只有单个 spec 文件才可以使用`--table-rows`标志

> $ gauge run --table-rows "1" specs/hello.spec
> $ gauge run --table-rows "1,4,7" specs/hello.spec

针对哪些场景运行，也可以指定表格行范围。 例如：

> $ gauge run --table-rows "1-3" specs/hello.spec

这将针对表格行 1，2，3 执行场景。

### CSV 文件作为表格参数

spec 的数据表也可以从外部 CSV 文件传递。假设现在`users.csv`文件包含如下数据信息：

```csv
id,name
1,Alice
2,Bob
3,Eve
```

在 spec 中，步骤使用`name`列数据如下：

```md
# Table driven execution

table: /the/path/to/users.csv

## Scenario

- Say "hello" to <name>

## Second Scenario

- Say "namaste" to <name>
```

## 并行执行

可以并行执行 spec 以更快的运行测试并分发负载。这可以通过命令完成：

> $ gauge run --parallel specs

或者

> $ gauge run -p specs

这样会根据机器的 CPU 核数量创建多个执行流，并在执行者之间分配负载。并行执行流数量可以通过 `-n` 标志指定。例如：

> $ gauge run --parallel -n=4 specs

这会创建四个并行执行流。


执行流数量的指定应该是由机器的可用 CPU 核数量决定，超过此数量可能会导致不良结果。要进行优化，请尝试使用线程执行来完成并行执行。


### 使用线程并行执行

在并行执行中，每个执行流会启动一个新的工作进程。这可以通过使用`多线程`取代`进程`来进行优化。这只会有一个工作进程且启动多个线程。为使用它，通过设置 `enable_multithreading` 环境变量为 `true`。这个属性也可以添加到默认/自定义环境的配置文件中。

> enable_multithreading = true

必要条件：

- 线程安全的测试代码
- 语言执行插件应该支持多线程


目前，这个功能只有 Java 语言支持。


### 使用 `--strategy` 执行测试

该功能允许在`执行期间`动态分配 spec 给工作流，而不是在执行开始时分配。这使得 Gauge 可以优化你的系统或执行环境的资源。这是非常有用的，因为某些 spec 可能需要比其他 spec 花费更多的时间，这可能是由于 spec 中场景的数量或被测功能的性质所致。以下命令将在指定数量的流中分配测试：

#### lazy

> $ gauge run -n=4 --strategy="lazy" specs

或者

> $ gauge run -n=4 specs

假设你有 100 个测试用例，你选择运行四个工作流或四个核心；在执行期间，lazy 分配将动态地将下一个 spec 分配给已完成先前执行的工作流并正在等待其他工作的流。

#### eager

lazy 分配测试是默认的行为。根据需求，另一种叫做 `eager` 的策略也是有用的。在这种情况下，100 个测试用例在执行之前被平均分配。

> $ gauge run -n=4 --strategy="eager" specs


lazy 策略只有在你未使用 `-g` 标志时生效。这是因为分组依赖于开始执行之前`测试spec`的分配。结合 lazy 策略使用它将不会对你的测试套件执行产生影响。简单理解：`-g`使用时，lazy 策略失效。


## 执行一组 Spec

spec 可以分成组，并且 `--group` 或者 `-g` 标志提供执行特定组的功能。spec 按照字母顺序排序，然后分成组，不管命令执行多少次都保证每个组都有相同的 spec 集合。可以通过下面的命令完成：

> $ gauge run -n=\<number_of_groups> -g=\<group_number> specs

- -n：分组的数量
- -g：分组号

> $ gauge run -n=4 -g=2 specs

这会将 specs 目录内的 spec 文件根据字母的顺序分为 4 组，然后指定执行第 2 组。不论命令执行了多少次，Gauge 仍会以相同顺序执行同一组 spec。

## 重新执行失败用例

Gauge 提供仅重新执行上次执行过程中失败场景的功能。失败场景运行可以通过使用 gauge 标签 `--failed` 。假如你运行 `gauge run specs` 后 3 个场景失败了，你通过下面的命令，可以仅仅重新执行失败场景而不是执行所有的场景。

> $ gauge run --failed

这个命令甚至会设置在你上次运行中提供的标志，比如，你已经执行了下列命令：

> $ gauge run --env="chrome" --verbose specs

并且三个场景在这次运行过程中失败了， `gauge run --failed` 命令设置 `--env` 和 `--verbose` 标志为对应的值然后仅仅执行失败的三个场景。这个情况下 `gauge run --failed` 相当于命令:

> $ gauge run --env="chrome" --verbose specs \<path_to_failed_scenarios>

### 使用`--max-retries-count`重新执行失败场景

使用`--max-retries-count`指定失败重试次数

> $ gauge run --max-retries-count=number_of_retries

### 使用`--retry-only`重新执行失败场景

你可以使用`--retry-only`标志过滤失败时必须重新运行特定次数的场景。该标志的值是用于关联场景的标签。

> $ gauge run --max-retries-count=number_of_retries --retry-only "\<tag_name>"

`tag_name` 可以是标签表达式。假如没有指定标签，那么所有失败的场景都将重试`number_of_retries`次。

## 执行中发生的错误

### 解析错误

当spec或者concept文件不符合对应语法时会抛出。

比如： <code>[ParseError] hello_world.spec : line no: 25, Dynamic parameter \<product> could not be resolved</code>

解析错误分类如下：

|解析错误|执行过程的行为|
|--|--|
|Concept标题内未定义步骤|停止|
|Concept内循环引用|停止|
|Concept标题包含未动态参数|停止|
|Concept没有包含步骤|停止|
|发现重复的Concept定义|停止|
|场景标题在concept文件内不被允许|停止|
|表格内的数据不属于任何步骤|忽略表格，继续执行|
|表格头部栏包含重复列|spec标记为FAIL，继续执行其他步骤|
|tear down至少应包含3个下划线|spec标记为FAIL，继续执行其他步骤|
|场景标题为空字符|spec标记为FAIL，继续执行其他步骤|
|表格头部栏为空|spec标记为FAIL，继续执行其他步骤|
|同一个文件内有多个一级标题（spec标题）|spec标记为FAIL，继续执行其他步骤|
|场景应该定义在spec标题之后|spec标记为FAIL，继续执行其他步骤|
|无法从文件中解析出表格数据|spec标记为FAIL，继续执行其他步骤|
|spec没有任何元素|spec标记为FAIL，继续执行其他步骤|
|spec没有标题|spec标记为FAIL，继续执行其他步骤|
|spec标题为空|spec标记为FAIL，继续执行其他步骤|
|动态参数不能被解析|spec标记为FAIL，继续执行其他步骤|
|步骤为空|spec标记为FAIL，继续执行其他步骤|
|同个spec有重复的场景定义|spec标记为FAIL，继续执行其他步骤|

### 验证错误

在下列情况发生错误时，Gauge会跳过执行场景

1. 步骤未有对应代码实现
2. 重复的步骤实现：项目中spec文件下的某一个步骤对应多处代码实现
