---
title: JAVA中对try,catch,finally的理解
date: 2018-07-20 12:49:30
tags: ['try','catch','finally','异常']
categories: 
 - 开发语言
 - Java
---

当程序不想给上层抛出异常，或者说想捕获异常时，通常我们会使用到try， catch ， finally。 但是这其中是有一些地方不是特别明白，特记录于此。



# try未发生异常时执行顺序

## 第1个情况：finally中无return

```java
public class TryTest {

    public static void main(String[] args) {
        String result = testFunc();
        System.out.println(result);
    }

    private static String testFunc() {
        try {
            System.out.println("try executing");
            int result = 1 / 1;
            return "try end";
        } catch (Exception e) {
            System.out.println("catch executing");
            return "catch end";
        } finally {
            System.out.println("finally executing");
        }
    }
}
```

打印结果
>try executing
finally executing
try end


## 第2个情况：finally中有return

```java
public class TryTest {

    public static void main(String[] args) {

        String result = testFunc();
        System.out.println(result);
    }

    private static String testFunc() {
        try {
            System.out.println("try executing");
            int result = 1 / 1;
            return "try end";
        } catch (Exception e) {
            System.out.println("catch executing");
            return "catch end";
        } finally {
            System.out.println("finally executing");
            return "finally end";
        }
    }
}
```

打印结果
>try executing
finally executing
finally end

所以总结上述两个情况：

1. 当try无异常时，先执行try不经过catch然后再执行finally
2. 若finally有return，则执行finally的return，程序结束 - **(不推荐finally中使用return)**
3. 若finally无return，则执行try中的return，程序结束。

# try中发生异常时执行顺序

```java
public class TryTest {

    public static void main(String[] args) {
        String result = testFunc();
        System.out.println(result);
    }
    private static String testFunc() {
        try {
            System.out.println("try executing");
            int result = 1 / 0;
            return "try end";
        } catch (Exception e) {
            System.out.println("catch executing");
            return "catch end";
        } finally {
            System.out.println("finally executing");
        }
    }
}
```

打印结果
>try executing
catch executing
finally executing
catch end

总结：

1. 先执行try，若有异常则进入catch，catch return前会先执行finally
2. 若finally有return， 执行finally的return，程序结束 - **程序未贴出，参考try那一节**
3. 若finally无return，执行catch中的return，程序结束

# 三者的关系

1. 编写顺序必定是try -> catch... -> finally 
2. 三者允许无catch或者无finally
3. catch允许有多个
4. 若catch分支未捕捉到实际抛出的异常，则往上层抛出
5. 若存在finally语句分支，则finally必定会被执行
