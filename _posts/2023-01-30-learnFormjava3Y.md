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


[articals](https://github.com/ZhongFuCheng3y/athena)

[words](https://github.com/wurara/wurara.github.io/tree/master/assets/words)

[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2023-01-30-learnFormjava3Y.md)
