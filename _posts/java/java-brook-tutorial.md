---
title: Java通用数据生成工具类brook使用文档
date: 2020-11-11 11:11:11
tags: ["工具类", "brook"]
sticky: 1
categories:
  - 开发语言
  - Java
---

# brook 文档

项目github仓库：[brook](https://github.com/amosnothing/brook)，欢迎`star`或提交`pull`。

## 背景

日常工作中，经常需要一些用户信息的测试数据，比如`身份证`，`手机号码`，`银行卡`，`姓名`（这四类信息称为四要素）等等。一般情况下比较便捷的做法：

- Java：定义一个类里面放一些常用的身份证前缀，银行卡 bin 等，然后通过随机生成
- Python： 定义多个字典，字典也是放一些常用的数据，也通过组合或者随机生成
- 其他: 跟上述原理差得不多

但是存在会存在一些`问题`：

- 重复造轮子：小张的项目自己写了一套 utils 类，小红的项目里面又另外写了一套 utils 类
- 功能单一： 造的轮子相对简单，只能生成一些相对固定的数据

如果将这些大家用得特别多的数据，通过一个统一的工具类来生成，会不会给大家带来`便利`呢？答案是肯定的：

- 用法简单：一个链式调用即可生成想要的数据
- 功能多样：根据不同的条件生成不同的测试数据，满足不同的业务需求
- 减少造轮子成本
- 数据`严谨`： 生成的身份证完全遵循【六位数字地址码，八位数字出生日期码，三位数字顺序码和一位数字校验码】；银行卡 bin 完全可以通过阿里的[银行卡校验接口](https://ccdcapi.alipay.com/validateAndCacheCardInfo.json?_input_charset=utf-8&cardNo=6230530030008566609&cardBinCheck=true)；姓名由姓氏和名字组合，姓氏来自 wiki 百科人数总数前 400 的姓，名字来自某数据库内 120 万条去重去掉不优雅的数据; 等等

## 使用方法

pom 中加入依赖:

```xml
<dependency>
  <groupId>cn.nothinghere</groupId>
  <artifactId>brook</artifactId>
  <version>${lastVersion}</version>
</dependency>
```

最新版本：注意版本号前面无需加`v`，比如`0.0.1`即可：

![v](https://img.shields.io/maven-central/v/cn.nothinghere/brook)

## 身份证

```java
String idCard = DataFactory.idCardBuilder()
            .withProvince(Province.HEBEI)
            .withCity(City.TANGSHAN)
            .withDistrict("古冶区")
            .withAge(18, 31)
            .withGender(Gender.FEMALE)
            .build();
```

入参全部非必填

| 方法           | 入参     | 说明                                         |
| -------------- | -------- | -------------------------------------------- |
| withProvince() | Province | 建议`省`采用枚举类的方式                       |
| withProvince() | String   | 不建议手动传入某个省的字符串类型             |
| withCity()     | City     | 建议`市`采用枚举类的方式                      |
| withCity()     | String   | 不建议手动传入某个市的字符串类型             |
| withDistrict() | String   | 因为`区`的数据太多，没有单独定义成枚举类       |
| withAge()      | int      | 指定固定的年龄                               |
| withAge()      | int, int | 指定年龄区间，后一个年龄不包含               |
| withGender()   | Gender   | 男性：Gender.MALE；女性：Gender.FEMALE        |
| withBirthday() | String   | 指定生日，格式为：yyyyMMdd，不要和年龄一起用 |

## 银行卡

```java
String bankCardNo = DataFactory.bankCardBuilder()
                .withBank(StateBank.ABC)
                .withType(BankCardType.DC)
                .withLength(16)
                .build();
```

入参全部非必填

| 方法         | 入参         | 说明                                                                    |
| ------------ | ------------ | ----------------------------------------------------------------------- |
| withBank()   | Bank         | StateBank:大型银行 OR 股份制银行；CityBank:城市商业银行，小银行用得不多 |
| withType()   | BankCardType | DC: "储蓄卡", CC: "信用卡", SCC: "准贷记卡", PC: "预付费卡"             |
| withLength() | int          | 银行卡号长度，一般是 16~19                                              |

## 手机号码

```java
String phone = DataFactory.phoneBuilder()
        .withOperator(Operator.CMCC)
        .build();
```

入参非必填

| 方法           | 入参     | 说明                            |
| -------------- | -------- | ------------------------------- |
| withOperator() | Operator | 移动:CMCC, 联通:CUCC, 电信:CTCC |

## 姓名

```java
String name = DataFactory.nameBuilder()
                    .withGender(Gender.MALE)
                    .withLength(3)
                    .build();
```

生成数据样例：
>张玉虎
>黄昌明

入参全部非必填

| 方法         | 入参   | 说明                                  |
| ------------ | ------ | ------------------------------------- |
| withGender() | Gender | 男性：Gender.MALE；女性：Gender.FEMALE |
| withLength() | int    | 2 字，3 字，4 字                      |

## 邮箱

```java
String email = DataFactory.emailBuilder()
            .withName("王思聪")
            .build();
```

生成数据样例：
>wangsicong@outlook.com

入参全部非必填

| 方法       | 入参   | 说明                                         |
| ---------- | ------ | -------------------------------------------- |
| withName() | String | 中文 OR 英文，中文会自动转为拼音，英文无变化 |

## 地址

注意这里后面还会做修改，因为实际上地址不可能只有省+市+区，等有空闲时间会逐渐细分到 xx 镇 xx 村等等；

```java
String address = DataFactory.addressBuilder()
                    .withProvince(Province.HEBEI)
                    .withCity(City.TANGSHAN)
                    .withDistrict("古冶区")
                    .build();
```

生成数据样例：
>河北省唐山市古冶区

入参全部非必填：

| 方法           | 入参     | 说明                                   |
| -------------- | -------- | -------------------------------------- |
| withProvince() | Province | 建议`省`采用枚举类的方式                       |
| withProvince() | String   | 不建议手动传入某个省的字符串类型             |
| withCity()     | City     | 建议`市`采用枚举类的方式                      |
| withCity()     | String   | 不建议手动传入某个市的字符串类型             |
| withDistrict() | String   | 因为`区`的数据太多，没有单独定义成枚举类       |

## 职业

```java
String occupation = DataFactory.occupationBuilder()
                        .withType(MajorType.PROFESSION)
                        .build();
```

生成数据样例：
>电气工程技术人员

入参全部非必填

| 方法       | 入参     | 说明                                                              |
| ---------- | -------- | ----------------------------------------------------------------- |
| withType() | 职业类型 | 8 大类，具体可见`cn.nothinghere.brook.value.occupation.MajorType` |

## 车牌号

```java
String licensePlate = DataFactory.licensePlateBuilder()
                .withProvince(Province.HEBEI)
                .withCity(City.TANGSHAN)
                .withDistrict("古冶区")
                .withType(PlateType.COMMON)
                .build();
```

入参全部非必填：

| 方法           | 入参      | 说明                                                                                                    |
| -------------- | --------- | ------------------------------------------------------------------------------------------------------- |
| withProvince() | Province | 建议`省`采用枚举类的方式                       |
| withProvince() | String   | 不建议手动传入某个省的字符串类型             |
| withCity()     | City     | 建议`市`采用枚举类的方式                      |
| withCity()     | String   | 不建议手动传入某个市的字符串类型             |
| withDistrict() | String   | 因为`区`的数据太多，没有单独定义成枚举类       |
| withType()     | PlateType | 车牌类型：COMMON-常用/普通车牌；MOTOR-摩托车；BUS-公交大巴；TAXI-出租车；FOREIGNER-外籍；TEMPORARY-临时 |

## 其他

待添加...
