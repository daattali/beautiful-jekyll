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






[articals](https://github.com/ZhongFuCheng3y/athena)

[words](https://github.com/wurara/wurara.github.io/tree/master/assets/words)

[edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2023-01-30-learnFormjava3Y.md)
