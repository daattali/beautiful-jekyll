---
title: 【lombok】@Getter/@Setter再也不用编写getFoo()/setFoo()
date: 2019-01-19 16:25:39
updated: 2019-01-19 16:25:39
tags: ['lombok','getter', 'setter']
categories: 
 - 开发语言
 - Java
 - lombok
---


## 概述

{% note info %}
使用`@Getter`和/或`@Setter`注解任何字段（类属性），让lombok自动生成默认的get方法 / set方法。
{% endnote %}

## Getter

默认的getter返回该字段本身（被`@Getter`标注的字段），如果字段名为`foo`，则自动生成的方法名为`getFoo()`（如果字段的类型为`boolean`，则方法名为`isFoo()`）

## Setter

默认的setter返回为void，如果字段名为`foo`，则自动生成的方法名为`setFoo()`。生成的setter方法有1个入参与该字段类型一致，且将字段设置为此值。

## 访问级别

除非你明确指定生成的方法访问级别，否则生成的`getter / setter`方法默认是`public`。如后面的代码示例所示，合法访问级别为 ` PUBLIC ` ， ` PROTECTED ` ， ` PACKAGE ` 和 ` PRIVATE ` 。

示例中：设置name的set方法的访问级别`protected`，age的get/set方法默认为`public`

{% tabs field %}
<!-- tab 源码 -->
```java
package com.amos.lombok;

import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

public class GetterSetterExample {

    @Getter
    @Setter
    private int age;
    @Setter(AccessLevel.PROTECTED)
    private String name;

    @Override public String toString() {
        return String.format("%s (age: %d)", name, age);
    }
}
```
<!-- endtab  -->

<!-- tab 编译后 -->
```java
package com.amos.lombok;

public class GetterSetterExample {
    private int age;
    private String name;

    public GetterSetterExample() {
    }

    public String toString() {
        return String.format("%s (age: %d)", this.name, this.age);
    }

    public int getAge() {
        return this.age;
    }

    public void setAge(final int age) {
        this.age = age;
    }

    protected void setName(final String name) {
        this.name = name;
    }
}
```
<!-- endtab  -->
{% endtabs %}

## 类级别

你还可以在类上放置`@Getter`和/或`@Setter`注解。在这种情况下，就等同于在该类所有的非静态字段上添加了`@Getter`和/或`@Setter`注解。

你可以在某字段上使用特殊的`AccessLevel.NONE`访问级别，手动禁用该字段的getter / setter生成。使你可以覆盖类上`@Getter`，`@Setter`或`@Data` 注解的行为。

示例中：在age上禁止生成set方法，在name禁止生成get方法

{% tabs class %}
<!-- tab 源码 -->
```java
package com.amos.lombok;

@Setter
@Getter
public class GetterSetterExample {

    @Setter(AccessLevel.NONE)
    private Integer age;

    @Getter(AccessLevel.NONE)
    private String name;
}
```
<!-- endtab -->
<!-- tab 编译后 -->
```java
package com.amos.lombok;

public class GetterSetterExample {
    private Integer age;
    private String name;

    public GetterSetterExample() {
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAge() {
        return this.age;
    }
}
```
<!-- endtab -->
{% endtabs %}

## 生成的方法/字段加注解

要在生成的方法上添加另外的注解（一个或者多个），可以使用`onMethod = @__({@AnnotationsHere, @AnnotationsHereSecond })`; 要将注解（一个或者多个）放在生成的setter方法的唯一形参上，可以使用`onParam = @ __({@AnnotationsHere, @AnnotationsHereSecond})`。但要小心！这是一个实验性功能。

示例中：我们为set方法的入参做非空检查，并且在set方法添加`@Deprecated`注解。

{% tabs annotation %}
<!-- tab 源码 -->
```java
package com.amos.lombok;
public class GetterSetterExample {

    @Getter
    @Setter(onParam = @__({@NonNull}), onMethod = @__({@Deprecated}))
    private Integer age;

    private String name;
}
```
<!-- endtab -->
<!-- tab 编译后 -->
```java
package com.amos.lombok;

public class GetterSetterExample {
    private Integer age;
    private String name;

    public GetterSetterExample() {
    }

    public Integer getAge() {
        return this.age;
    }

    /** @deprecated */
    @Deprecated
    public void setAge(@NonNull Integer age) {
        if (age == null) {
            throw new NullPointerException("age is marked non-null but is null");
        } else {
            this.age = age;
        }
    }
}
```
<!-- endtab -->
{% endtabs %}

## javadoc

lombok v1.12.0中的新功能: 现在将字段上的javadoc复制到生成的getter和setter。通常所有注释文本都被复制，@return被移动到getter方法上，而@param行被移动到setter方法。移动的意思是指：从字段的javadoc中删除，也会为每个getter/setter定义唯一的文本。因此你可以创建名为GETTER和/或SETTER的“section”，section是javadoc中包含2个或更多短划线的行，然后是文本’GETTER’或’SETTER’，后跟2个或更多破折号，行上没有其他内容。如果使用sections，则不再执行@return和@param剥离该section（将@return或@param行移动到该节中）。

{% note info %}
time: 2020-10-01 18:37
不好意思，这个功能目前还尚未搞明白，等彻底搞清楚再来更新。
{% endnote %}
