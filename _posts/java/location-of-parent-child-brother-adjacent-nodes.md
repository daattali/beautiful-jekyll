---
title: Java selenium - 父子、兄弟、相邻节点定位方式详解
date: 2018-03-18 22:43:00
tags: ['java','元素定位','xpath','动态定位','selenium']
categories: 
 - 软件测试
 - 测试工具
 - Selenium
---


所有的细节全部已经验证通过，`Python`可参考此篇文章《[Python selenium —— 父子、兄弟、相邻节点定位方式详解](http://blog.csdn.net/huilan_same/article/details/52541680)》

另外，贴出来的代码全部取至于[PPmoney官网](https://www.ppmoney.com/)。^_^ 小小滴广告一波啦。



## 由弟弟节点定位哥哥节点

### id动态

咱们先看一下html代码
1. 咱们需要定位在button x
2. button x节点下的 系统提示节点的id属性属于动态属性 id是变化的
3. 若当前页面还有其他以id="title:xxx" 作为属性的div节点，另说。。

如何做 ?

```html
<td i="header" class="ui-dialog-header">
    <button i="close" class="ui-dialog-close" title="取消">×</button>
    <div i="title" class="ui-dialog-title" id="title:1521380976967">系统提示</div>
</td>
```

先定位到id, 因为是动态的所以咱们需要用到contains
下面的代码是指div节点id元素包含"title:"字符串

```Java
By by = By.xpath("//div[contains(@id,'title:')]");
```
再定位到系统提示的父节点
> /..   表示父节点

```Java
By by = By.xpath("//div[contains(@id,'title:')]/..");
```
最后定位到我们期望的x元素

**方法1：**
 [ ]中括号1表示同级第一个以button为tag的节点，依次类推
```Java
By by = By.xpath("//div[contains(@id,'title:')]/../button[1]");
```
**方法2：**
preceding-sibling - 上一个同级节点 
```Java
By by = By.xpath("//div[contains(@id,'title:')]/preceding-sibling::button[1]");
```

### id已知

> 先讲难的，再讲简单的，神经病啊！！？？ 其实差别不大。

若是id已知，咱们把刚才的html稍微改一下

```html
<td i="header" class="ui-dialog-header">
    <button i="close" class="ui-dialog-close" title="取消">×</button>
    <div i="title" class="ui-dialog-title" id="title">系统提示</div>
</td>
```
定位方法：二选一

```Java
By by = By.xpath("//div[@id='title')]/../button[1]");
```

```Java
By by = By.xpath("//div[@id='title')]/preceding-sibling::button[1]");
```

## 由哥哥节点定位弟弟节点

哥哥定位弟弟 同 弟弟定位哥哥比较相近，咱们把 弟弟定位哥哥 小节的代码稍微改一下， **希望大家可以举一反三，多思考多动手。**

```html
<td i="header" class="ui-dialog-header">
	<div i="title" class="ui-dialog-title" id="title">系统提示</div>
	<button i="close" class="ui-dialog-close" title="取消">×</button>
</td>
```
**方法1：**
细心的同学可能会发现，其实这里的定位方法与 <弟弟定位哥哥> 完全一样。
```Java
By by = By.xpath("//div[@id='title')]/../button[1]");
```

**方法2：**
和<弟弟定位哥哥> 稍微有点差别
**following-sibling - 下一个同级节点**

```Java
By by = By.xpath("//div[@id='title')]/following-sibling::button[1]");
```

## 由子节点定位父节点

贴一下html代码 -> test.html

```html
<div class="btn-recharge-c cf">充值父节点
    <input class="pp-btn pp-btn-lg btn-recharge" id="btnRecharge" type="button" value="充值">
</div>
```
已知充值子节点的id=btnRecharge，咱们需要定位父节点

```Java
driver = DriverFactory.getDriver();
driver.get("E:\\test.html");
// 注意 /.. 表示父节点
String text_0 = driver.findElement(By.xpath("//input[@id='btnRecharge']/..")).getText();
// parent:: 表示父节点 ， div - 表示tag必须是div
String text_1 = driver.findElement(By.xpath("//input[@id='btnRecharge']/parent::div")).getText();
// * 通配符 父节点任意tag均可
String text_2 = driver.findElement(By.xpath("//input[@id='btnRecharge']/parent::*")).getText();

System.out.println(text_0);
System.out.println(text_1);
System.out.println(text_2);
```
结果都是
> 充值父节点

## 由父节点定位子节点

咱们先看代码，test.html

```html
<div class="btn-recharge-c cf" id="father">充值父节点
    <input class="pp-btn pp-btn-lg btn-recharge" type="button" value="充值">
    <input class="pp-btn pp-btn-lg btn-recharge" type="button" value="充值的弟弟">
</div>
```
想获取到<充值>节点（或者<充值的弟弟>节点）可以有以下方法:
方法1：
```Java
// 先通过id找到父节点,再找到子节点(默认查找最近的一个),再获取属性值value
String text_0 = driver.findElement(By.id("father"))
    .findElement(By.tagName("input"))
    .getAttribute("value");
System.out.println(text_0);
```
方法2：

```Java
// 先通过id找到父节点,再找到所有的子节点，取第一个,再获取属性值value
String text_1 = driver.findElement(By.id("father"))
    .findElements(By.tagName("input")).get(0)
    .getAttribute("value");
System.out.println(text_1);
```
方法3：

```Java
// xpath轴 child 子节点
// 如果不用[] 默认取第一个子节点
// 如果用[]   则使用//div[@id='father']/child::input[1]
String text_2 = driver.findElement(By.xpath("//div[@id='father']/child::input"))
    .getAttribute("value");
System.out.println(text_2);
```

方法4：

```Java
// xpath轴 child 子节点 * 通配符
// 如果不用[] 默认取第一个子节点
// 如果用[]   则使用//div[@id='father']/child::*[1]
String text_3 = driver.findElement(By.xpath("//div[@id='father']/child::*"))
    .getAttribute("value");
System.out.println(text_3);
```

方法5：

```Java
// css 父子关系查找
String text_4 = driver.findElement(By.cssSelector("div#father>input"))
    .getAttribute("value");
System.out.println(text_4);
```

方法6：

```Java
// css nth-child (1)子节点-充值 (2)子节点-充值的弟弟
String text_5 = driver.findElement(By.cssSelector("div#father>input:nth-child(1)"))
    .getAttribute("value");
System.out.println(text_5);
```

方法7：

```Java
// css nth-of-type (1)子节点-充值 (2)子节点-充值的弟弟
String text_6 = driver.findElement(By.cssSelector("div#father>input:nth-of-type(1)"))
    .getAttribute("value");
System.out.println(text_6);
```

## 节点跳跃定位

> 也不知道这个定位叫法对不对， 哈哈 ，暂且这么叫吧 ~

先看代码，有些不重要的部分已经省略。

```html
<div class="ct-mod-recharge-bd" id="rechargeForm">
    <!--充值金额-->
    <div class="rec-field cf">
        ...
    </div>
    <!--充值方式-->
    <div class="rec-field cf">
        <div class="rec-field-l">
            <label for="">支付方式</label>
        </div>
        <div class="rec-field-r">
            <ul class="choice-type cf">
                <li class="selected" data-recargeway="SWIFT"><u class="u-Lianlianpay"></u></li>
                <li data-recargeway="WEB"><u class="u-bank"></u></li>
            </ul>
        </div>
    </div>
    <!--快捷支付选择银行-->
    <div data-accountbank="" class="rec-field cf">
       ...
    </div>
    <!--选择银行-->
</div>
```

看一下页面样式， 我们的目的是 <快捷支付><网银支付>这两个元素

![支付方式](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/location-of-parent-child-brother-adjacent-nodes/pay.png)

我们需要定位到支付方式处，这里没有任何id，name什么的。但是看到最外层div是有一个id的，咱们就用他。

```Java
driver.findElement(By.id("rechargeForm"))
    .findElements(By.tagName("li")).get(1).click();
```

咱们先取到id = rechargeForm的div层，然后再在取到的这层div内查找以li为标签的元素。
因为以li为tag的元素有两个，看情况是取第一个还是第二个。可以看出来，我们并不是以父子定位或者兄弟定位的方式，而是跳跃了几个层级的方式来定位的，代码简化了不少。
