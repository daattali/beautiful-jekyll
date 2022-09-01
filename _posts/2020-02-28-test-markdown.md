---
layout: post
title: 示例博客文章
subtitle: 每个帖子还有一个副标题
# gh-repo: daattali/beautiful-jekyll
gh-badge: [star, fork, follow]
tags: [test]
comments: true
---

这是一篇演示文章，向您展示如何使用markdown撰写博客文章。我强烈建议您花5分钟学习如何用markdown书写 - 它将教您如何将常规文本转换为粗体/斜体/标题/表格/等。

**这是一些粗体文本**

## 这是一个次要标题

这是一个无用的表：

| 数字 | 下一个数字 | 上一个数字 |
| :------ |:--- | :--- |
| 5 | 6 | 4 |
| 10 | 11 | 9 |
| 7 | 8 | 6 |
| 2 | 3 | 1 |


美味的薄饼怎么样？

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg)

它也可以居中！

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg){: .mx-auto.d-block :}

下面是一个代码块：
~~~
var foo = function(x) {
  return(x + 5);
}
foo(3)
~~~

下面是具有语法突出显示的相同代码：

```javascript
var foo = function(x) {
  return(x + 5);
}
foo(3)
```

这里又是相同的代码，但带有行号：

{% highlight javascript linenos %}
var foo = function(x) {
  return(x + 5);
}
foo(3)
{% endhighlight %}

## 盒子
您可以添加通知，警告和错误框，如下所示：

### 通知

{: .box-note}
**注意：** 这是一个通知框。

### 警告

{: .box-warning}
**警告:**  这是一个警告框。

### 错误

{: .box-error}
**错误:**  这是一个错误框。