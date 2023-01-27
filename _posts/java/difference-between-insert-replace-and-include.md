---
title: thymeleaf - th:insert和th:replace(和th:include)的区别
date: 2018-09-30 18:07:27
tags: ['thymeleaf','insert','replace']
categories: 
 - 开发语言
 - Java
 - thymeleaf
---

# 区别

## 代码示例

```html
<footer th:fragment="copy">
  &copy; 2011 The Good Thymes Virtual Grocery
</footer>
```

使用thymeleaf语法

```html
<body>
  ...
  <div th:insert="footer :: copy"></div>
  <div th:replace="footer :: copy"></div>
  <div th:include="footer :: copy"></div>
</body>
```

渲染之后的结果是

```html
<body>
  ...
  <div>
    <footer>
      &copy; 2011 The Good Thymes Virtual Grocery
    </footer>
  </div>
  <footer>
    &copy; 2011 The Good Thymes Virtual Grocery
  </footer>
  <div>
    &copy; 2011 The Good Thymes Virtual Grocery
  </div>
  
</body>
```

## 结论

- th:insert 如同插入的字面意思，将指定的代码片段插入主标签内
- th:replace 如同替换的字面意思，将主标签替换为指定的代码片段
- th:include (3.0版本后已不推荐使用) 类似于th:insert, 不同的是在插入的时候不带代码片段的标签，只插入代码

## 参考

[template-layout](https://www.thymeleaf.org/doc/tutorials/3.0/usingthymeleaf.html#template-layout)
