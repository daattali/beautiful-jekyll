---
title: BigDecimal转int数据四舍五入
date: 2018-07-27 11:18:02
updated: 2018-07-27 11:18:02
tags: ['Bigdecimal','int']
categories: 
 - 开发语言
 - Java
---


```java
new BigDecimal("6749.13")
            .multiply(new BigDecimal("1.5"))
            .intValue();
```

解析：`6749.13 * 1.5 = 10123.695`，实际结果=10123，可见intValue是截取小数的。故在将BigDecimal转int时需要先将小数位设置为0，且设置四舍五入。

```java
new BigDecimal("6749.13")
        .multiply(new BigDecimal("1.5"))
        .setScale(0, BigDecimal.ROUND_HALF_UP)
        .intValue();
```

最后结果 = 10124，结果正确。

小问题，搞了半天，证明自己对一些方法理解得不够透彻。
