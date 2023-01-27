---
title: 【lombok】@Cleanup - 自动资源管理，安全的调用close方法
date: 2019-01-18 18:07:46
updated: 2019-01-18 18:07:46
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---


# @Cleanup用法

当在处理 ` 文件对象 ` ，或者 ` 数据库资源 ` 时，我们总是会忘记close，可能引发内存溢出。如果手动去调用close方法，代码又会非常长，现在有了@Cleanup , 我们不再需要担心这些问题。

您可以使用@Cleanup确保在代码执行路径退出当前作用域之前自动清除给定资源。您可以通过使用@Cleanup注释来注释任何局部变量声明来执行此操作，如下所示：  
```java
@Cleanup InputStream in = new FileInputStream（"some_file"）;  
```


因此，在您所在范围的末尾，调用`in.close()`。 保证通过try / finally构造运行此调用。 请看下面的示例，看看它是如何工作的。

如果要清理的对象类型没有close（）方法，而是其他一些无参数方法，则可以指定此方法的名称，如下所示：  

```java
@Cleanup（"dispose"）org.eclipse.swt.widgets.CoolBar bar = new CoolBar（parent，0）;  
```

默认情况下，清除方法假定为close（）。 不能通过@Cleanup调用带有1个或多个参数的清理方法。

为了方便理解，我们假设该 ` 内存资源 ` 是 ` 一扇门 ` 。初始化的时候，这扇门默认是打开的，等于说允许你在房间里做一些事情（看书，打游戏，睡觉） - 方法调用。将内存资源回收当作把门关掉，也就是不再允许你再做上述动作。

看代码！非常简单易懂！！

```java
package com.amos.lombok;

import lombok.Cleanup;

public class Door {

    /**
    * 门是否打开
    * true : 打开
    * false : 关闭
    */
    private boolean openStatus;

    public Door(boolean openStatus) {
        this.openStatus = openStatus;
    }

    public Door() {
        this.openStatus = true;
        System.out.println("初始化时，门的状态默认是-打开 ");
    }

    public void function() {
        System.out.println("调用该对象的某一个或者多个方法ing");
    }

    public void close() {
        System.out.println("关门之前，门的状态是-" + (this.openStatus ? "打开" : "关闭"));
        this.openStatus = false;
        System.out.println("关门之前，门的状态是-关闭");
    }

    public static void main(String[] args) {
        @Cleanup Door door = new Door();
        door.function();
    }
}
```

执行main方式，打印数据如下：

> 初始化时，门的状态默认是-打开  
> 调用该对象的某一个或者多个方法ing  
> 关门之前，门的状态是-打开  
> 关门之前，门的状态是-关闭

可以看出，当在新建的door对象上加上@Cleanup注解后，它会在我们调用完function方法后，自动的帮我们调用close方法。 `希望你自己去试试看，看虽然能看懂，但是手动写一下加深印象 `

编译完后，改main方法生成的class文件如下:

```java 
    
public static void main(String[] args) {
    Door door = new Door();

    try {
        door.function();
    } finally {
        if (Collections.singletonList(door).get(0) != null) {
            door.close();
        }
    }
}
```