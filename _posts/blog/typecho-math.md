---
title: Typecho支持数学公式
date: 2020-09-25 13:38:00
tags: ['typecho','mathjax','数学公式']
categories: 
 - 博客
 - Typecho
---

## 支持mathjax

在当前选中的主题，修改header.php，在header标签里面添加：

```php
<!-- 这里是数学公式的支持 -->
  <script type="text/x-mathjax-config">
        MathJax.Hub.Config({
    extensions: ["tex2jax.js"],
    jax: ["input/TeX", "output/HTML-CSS"],
    tex2jax: {
      inlineMath: [ ['$','$'], ["\\(","\\)"] ],
      displayMath: [ ['$$','$$'], ["\\[","\\]"] ],
      processEscapes: true
    },
    "HTML-CSS": { availableFonts: ["TeX"] }
  });
</script>
<script type="text/javascript" 
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/latest.js?config=TeX-AMS-MML_HTMLorMML">
  </script>
```

### src可选

1. https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML
2. https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/latest.js?config=TeX-AMS-MML_HTMLorMML

第二个就是自动帮你使用最新的js代码，官方给的说法是：

>每当MathJax更新且版本更改时，都需要更改URL（否则，您将保持链接中的版本）。 还可以让MathJax为您选择其最新版本。

## 使用后的样式

可以通过查看笔者这篇文章《[欧几里得算法（辗转相除法）简易证明](https://www.nothinghere.cn/cs/the-euclidean-algorithm/)》

## 参考

[mathjax官方文档](http://docs.mathjax.org/en/v2.7-latest/start.html#using-a-content-delivery-network-cdn)
[mathjax语法~中文](https://www.szdev.com/blog/Hexo/mathjax-config-and-tutorial/)