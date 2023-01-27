---
title: Java数组与List相互转换以及注意事项
date: 2019-05-31 08:13:34
updated: 2019-05-31 08:13:34
tags: ['Java','数组','List']
categories: 
 - 开发语言
 - Java
---

# Ⅰ. List转数组

以实际使用的代码举例，我用到`apache`的`httpcomponents`包（发送HTTP请求）. 传参请求的body是Map，header是Map，构造请求client。该过程会使用到`List转数组`。


```java
public static String postForm(String url, Map<String, String> body, Map<String, String> headers) 
    throws IOException {

    Objects.requireNonNull(url, "url");
    Objects.requireNonNull(body, "body");
    // 头
    List<BasicHeader> headerList = new ArrayList<>();
    headers.forEach((k, v) -> headerList.add(new BasicHeader(k, v)));
    BasicHeader[] basicHeaders = headerList.toArray(new BasicHeader[0]);
    // body
    List<NameValuePair> bodyForm = new ArrayList<>();
    body.forEach((k, v) -> bodyForm.add(new BasicNameValuePair(k, v)));

    Response response = Request.Post(url)
        // 设置头, 需要将List转为数组
        .setHeaders(basicHeaders)
        .bodyForm(bodyForm)
        .execute();
    return response.returnContent().asString();
}
```

## 具体使用

```java
# 这里JavaBean根据你的实际情况做调整
List<JavaBean> list= new ArrayList<>();
# do something , initialize this list...

JavaBean[] basicHeaders = list.toArray(new JavaBean[0]);
```

## 注意事项

使用上述方式做转换的时候，`new JavaBean[0]` 我并没有传入0，而是初始化了数组的大小，传入的是该List的长度，即是`new JavaBean[list.size()]`, 但是IDEA给了提示，说该写法不友好。具体提示如下：
>Inspection info: There are two styles to convert a collection to an array: either using a pre-sized array (like c.toArray(new String[c.size()])) or using an empty array (like c.toArray(new String[0]).
In older Java versions using pre-sized array was recommended, as the reflection call which is necessary to create an array of proper size was quite slow. However since late updates of OpenJDK 6 this call was intrinsified, making the performance of the empty array version the same and sometimes even better, compared to the pre-sized version. Also passing pre-sized array is dangerous for a concurrent or synchronized collection as a data race is possible between the size and toArray call which may result in extra nulls at the end of the array, if the collection was concurrently shrunk during the operation.
This inspection allows to follow the uniform style: either using an empty array (which is recommended in modern Java) or using a pre-sized array (which might be faster in older Java versions or non-HotSpot based JVMs).

{% note info %}
检查信息：有两种样式可以将集合转换为数组：使用预先调整大小的数组（如c.toArray（new string[c.size()]）或使用空数组（如c.toArray(new string[0])。
在使用更大尺寸的数组的Java版本中，建议创建一个适当大小的数组所需的反射调用是相当慢的。然而，由于OpenJDK6的更新较晚，这一调用被内部化，使得空数组版本的性能与预调整大小的版本相同，有时甚至更好。另外，传递预先确定大小的数组对于并发或同步的集合也很危险，因为在大小和ToArray调用之间可能会发生数据争用，如果在操作期间集合同时收缩，则可能会导致数组末尾出现额外的空值。
这种检查允许遵循统一的风格：要么使用空数组（在现代Java中推荐），要么使用预先大小的数组（在旧的Java版本或基于非`HotSpot JVM`中可能更快）。
{% endnote %}

重点关注最后一句的总结：<font color=red>要么使用空数组（在现代Java中推荐），要么使用预先大小的数组（在旧的Java版本或基于非HotSpot JVM中可能更快）</font>

# Ⅱ. 数组转List

数组转List在 `java.util.Arrays`类内有方法可以直接使用

```java
public static void main(String[] args) {

    Obj a = new Obj();
    a.setName("a");
    Obj b = new Obj();
    b.setName("b");
    Obj[] objArray = new Obj[]{
            a, b
    };
    List<Obj> list = Arrays.asList(objArray);
}
```
