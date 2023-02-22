---
layout: post
title: learnFormjava3Y
subtitle: 雪豹-大型猫科食肉动物，属于世界级濒危物种
thumbnail-img: /assets/img/xuebao.png
share-img: /assets/img/path.jpg
tags: [java , ]
---

## java 基础
### 泛型  

- 泛型方法  

```
public <T> void show(T t) {
    System.out.println(t);

}
```  
- 泛型类  

```
/*
2:类型变量定义在类上,方法中也可以使用
*/
public class ObjectTool<T> {
    private T obj;

    public T getObj() {
        return obj;
    }

    public void setObj(T obj) {
        this.obj = obj;
    }
}
```
- 泛型接口  

```
/*
    把泛型定义在接口上
 */
public interface Inter<T> {
    public abstract void show(T t);

}

---
实现泛型接口的类
/**
 * 子类明确泛型类的类型参数变量:
 */

public class InterImpl implements Inter<String> {
    @Override
    public void show(String s) {
        System.out.println(s);

    }
}

---
/**
 * 子类不明确泛型类的类型参数变量:
 *      实现类也要定义出<T>类型的
 *
 */
public class InterImpl<T> implements Inter<T> {

    @Override
    public void show(T t) {
        System.out.println(t);

    }
}
```


### 注解
#### 基础注解
- 重写注解：@Override
- 过时注解：@Deprecated 
- 抑制编译器警告注解：@SuppressWarnings
- “堆污染”警告：@SafeVarargs
- 函数式接口：@FunctionalInterface  


{: .box-note} 
函数式接口是一个接口只有一个方法  
{: .box-note} 

### NIO

- buffer
    1. 数据操作
        - allocate：创建缓冲区
        - put：写入数据
        - get：获取数据
    2. 核心变量
        - Capacity：最大容量
        - Limit：有数据的位置上限
        - Position：位置
        - Mark：标识
    3. 缓冲区操作
        - flip：重置读取位置上限和位置，即更新Limit和Position
        - clear：清空缓冲区（实际是重置核心变量，数据未处理）
- channel
    1. FileChannel
        - open：打开一个channel
        - read：从channel中读取一个缓冲块
        - map：将缓冲区映射到buffer中
        - write：讲缓冲块写入channel中
        - transfer：直接发送到另一个channel  
        - register：将通道注册到selector中
        - configureBlocking：是否阻塞（配置selector必须是false）  

{: .box-note} 
一般是操作直接缓冲区，操作系统和用户程序直接操作一个文件映像。直接操作速度快，但是创建慢。
{: .box-note} 
    
- selector
    - selectedKeys().iterator()：获得selector的key集合
    - SelectionKey
        - isAcceptable：接受事件就绪
        - isReadable：读取事件就绪
        - channel：获取监听的channel
        - remove：删除监听的通道

### 反射  

想要使用反射，我先要得到class文件对象，其实也就是得到Class类的对象

1. 获取class文件对象的方式：
    1. Object类的getClass()方法
    2. 数据类型的静态属性class
    3. Class类中的静态方法：public static Class ForName(String className)

2. 获取成员变量并使用
    1. 获取Class对象
    2. 通过Class对象获取Constructor对象
    3. Object obj = Constructor.newInstance()创建对象
    4. Field field = Class.getField("指定变量名")获取单个成员变量对象
    5. field.set(obj,"") 为obj对象的field字段赋值  

3. 通过反射调用成员方法
    1. 获取Class对象
    2. 通过Class对象获取Constructor对象
    3. Constructor.newInstance()创建对象
    4. 通过Class对象获取Method对象, getMethod("方法名");
    5. Method对象调用invoke方法实现功能    

{: .box-note}  
如果需要访问私有或者默认修饰的成员变量  
setAccessible() 暴力访问  
{: .box-note}  

### COW机制

cow-copy on write：当有数据写入时才复制一份，用于节约内存空间，加快访问速度。  
原理：在子进程读取数据时使用指针指向父进程数据，当任何一方写入时才真正复制一份数据做写入操作（如redis是fork出一个子进程来拷贝数据到磁盘，linux的文件系统在修改时会先拷贝一份出来，写完后再覆盖原文件）。

### Thread

#### 实现方法
1. 创建一个类，继承Thread，重写run方法
2. 实现Runnable接口，重写run方法
3. 实现callable接口，重写call方法，有方法返回值

### 线程状态
- NEW
- RUNNABLE
- BLOCKED
- WAITING
- TIMED_WAITING
- TERMINATED

待续：https://blog.csdn.net/panweiwei1994/article/details/78483167
{: .box-note}  
strat启动线程，run只是方法调用。
{: .box-note}  


[articals](https://github.com/ZhongFuCheng3y/athena)

[words](https://github.com/wurara/wurara.github.io/tree/master/assets/words)

[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2023-01-30-learnFormjava3Y.md)
