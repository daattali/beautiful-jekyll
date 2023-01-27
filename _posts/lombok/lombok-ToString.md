---
title: 【lombok】@ToString - 让lombok帮你生成toString方法
date: 2019-01-19 22:49:55
updated: 2019-01-19 22:49:55
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---


## 概述

任何类定义都可以加上`@ToString`注解，让lombok生成`toString()`方法的实现。默认情况下，它会按顺序打印你的类名称以及每个字段，并以逗号分隔。

### 包含字段 OR 排除字段

通过将`includeFieldNames`参数设置为true，你可以使得`toString()`方法的输出更加的清晰（但因此输出的字符串也会变得更长）。

默认情况下，`toString()`方法将输出所有<font color="#FF0000">非静态字段</font>。如果要跳过某些字段，可以使用`@ToString.Exclude`注释这些字段。或者，你可以使用`@ToString(onlyExplicitlyIncluded = true)`准确指定要使用的字段，然后使用`@ToString.Include`标记要包含的字段。

### 是否包含父类

通过将`callSuper`设置为true，可以将父类的toString方法添加到该类的toString输出中。请注意，`java.lang.Object`中`toString()`的默认实现几乎没有意义，除非你确实是继承于另一个类（非Object类），否则你可能不需要将其设置为true（直白点理解：如果你实现的类是继承于Object类，则toString的注解根本就无需将`callSuper`设置为true，因为这没有意义）。

### 包含方法

可以在`toString()`中包含方法调用的输出，但是只能包含不带参数的实例（非静态）方法。为此，请使用`@ ToString.Include`标记该方法。

### 修改字段名 OR 打印顺序

可以使用`@ToString.Include(name ="anotherName")`更改用于标识成员的名称，并且可以通过`@ToString.Include(rank = -1)`更改成员的打印顺序。未被标记添加rank标记的成员的rank默认优先级=0，更高优先级的成员将优先被打印，并且相同优先级的成员以它们在源文件中出现的相同顺序被打印。

## @ToString示例

```java
package com.amos;

import lombok.ToString;

@ToString
public class ToStringExample {

    /**
    * 静态field不会被生成到toString方法内
    */
    private static final int STATIC_VAR = 10;
    private String name;
    private Shape shape = new Square(5, 10);
    private String[] tags = new String[]{"1", "2", "3"};
    /**
        * 标记 @ToString.Exclude
        * toString方法不包含此字段
        */
    @ToString.Exclude
    private int id;

    /**
    *  callSuper -> toString方法体内会带上超类的toString方法
    *  includeFieldNames -> 是否包含字段名，false不包含 true包含  默认是true
    */
    @ToString(callSuper = true, includeFieldNames = false)
    public static class Square extends Shape {

        private final int width, height;

        public Square(int width, int height) {
            this.width = width;
            this.height = height;
        }
    }

    public static class Shape {

        @Override
        public String toString() {
            return "Shape[" + this.hashCode() + "]";
        }
    }

    public static void main(String[] args) {
        System.out.println(new Shape());
        System.out.println(new Square(1,2));
        System.out.println(new ToStringExample());

    }
}
```

执行main方法后，打印内容如下:

> Shape[1929600551]  
> ToStringExample.Square(super=Shape[1053782781], 1, 2)  
> ToStringExample(name=null, shape=ToStringExample.Square(super=Shape[1211888640], 5, 10), tags=[1, 2, 3])

## 编译后的代码

通过查看编译后的class文件，加深一下印象，class文件如下所示:

```java
package com.amos;

import java.util.Arrays;

public class ToStringExample {
    private static final int STATIC_VAR = 10;
    private String name;
    private ToStringExample.Shape shape = new ToStringExample.Square(5, 10);
    private String[] tags = new String[]{"1", "2", "3"};
    private int id;

    public ToStringExample() {
    }

    public static void main(String[] args) {
        System.out.println(new ToStringExample.Shape());
        System.out.println(new ToStringExample.Square(1, 2));
        System.out.println(new ToStringExample());
    }

    public String toString() {
        return "ToStringExample(name=" + this.name + ", shape=" + this.shape + ", tags=" + Arrays.deepToString(this.tags) + ")";
    }

    public static class Shape {
        public Shape() {
        }

        public String toString() {
            return "Shape[" + this.hashCode() + "]";
        }
    }

    public static class Square extends ToStringExample.Shape {
        private final int width;
        private final int height;

        public Square(int width, int height) {
            this.width = width;
            this.height = height;
        }

        public String toString() {
            return "ToStringExample.Square(super=" + super.toString() + ", " + this.width + ", " + this.height + ")";
        }
    }
}
```

先看Shape类，调用System.out.printXX方法时，默认会调用该对象的toString方法，所以Shape的toString打印结果比较好理解。

再看Square的toString方法，因为Square类是ToStringExample类的静态内部类，所以在该类名前会有ToStringExample类名标识。因为添加了 ` callSuper = true ` ，所以在toString方法内，会加上超类的toString方法（查看class文件）。再看 ` includeFieldNames = false ` ，toString默认会带上字段名的，标识会false后，不会带字段名 ` width ` 和 ` height ` .

最后看ToStringExample的toString方法，因为`STATIC_VAR`是静态字段，所以不会置于toString方法体内，又因为id被添加上`@ToString.Exclude`注解，所以该字段也不会置于toString方法体内。
