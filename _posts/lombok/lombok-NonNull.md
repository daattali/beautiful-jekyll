---
title: 【lombok】@NonNull - 不再担忧NullPointerException
date: 2019-01-18 17:36:47
updated: 2019-01-18 17:36:47
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---


## 概述


说到`NullPointerException`，可能会是所有Java搬砖工的噩梦吧？

现在有了` @NonNull ` , 让我们不再害怕NPE!!!


你可以在方法或构造函数的参数上使用`@NonNull`注解让lombok为你生成`null-check`(空值检查，下同)语句。

如果lombok为你生成整个方法或构造函数（例如在类上使用`@Data`注解），Lombok总是将字段上标注了 ` @NonNull ` 的各种注解视为生成`null-check`的信号。现在，在参数上使用lombok自己的`@lombok.NonNull`会在你的方法或构造函数中只插入null-check语句。

`null-check`看起来像 ` if (param == null) throw new NullPointerException("param is marked @NonNull but is null") ` ; 并将此语句插入到方法的最顶层。对于构造函数，将在任何显式`this()`或`super()`调用之后立即插入非空检查。

如果上层已经存在非空检查，则不会生成额外的非空检查。（这句话研究了半天也没想明白是啥意思，有知道的麻烦告知与我，感激！！）原文 ` If a null-check is already present at the top, no additional null-check will be generated. `

## NonNull示例

```java
package com.amos.lombok;

import lombok.NonNull;

public class NonNullExample {

    private String name;
    // 在构造器上使用@NonNull
    public NonNullExample(@NonNull String name) {
        this.name = name;
    }

    // 在普通方法上使用@NonNull
    public static void example(@NonNull String str) {
        System.out.println(str);
    }

    public static void main(String[] args) {
        // 异常1
        NonNullExample example = new NonNullExample(null);
        // 异常2
        example(null);
    }
}
```

执行main方法后，异常堆栈信息如下:

> Exception in thread “main” java.lang.NullPointerException: name is marked @NonNull but is null

异常2堆栈信息如下:

> Exception in thread “main” java.lang.NullPointerException: str is marked @NonNull but is null

## 编译后的代码

```java
package com.amos.lombok;

import lombok.NonNull;

public class NonNullExample {
    private String name;

    public NonNullExample(@NonNull String name) {
        if (name == null) {
            throw new NullPointerException("name is marked @NonNull but is null");
        } else {
            this.name = name;
        }
    }

    public static void example(@NonNull String str) {
        if (str == null) {
            throw new NullPointerException("str is marked @NonNull but is null");
        } else {
            System.out.println(str);
        }
    }

    public static void main(String[] args) {
        example((String)null);
        new NonNullExample((String)null);
    }
}
```
