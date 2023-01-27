---
title: 为什么Java Calendar类的月份与实际月份少1？
date: 2019-01-24 11:30:34
tags: ['Calendar','月份']
categories: 
 - 开发语言
 - Java
---


这个答案搜了很多，好像也没有一个明确的回答
> 最初猜想:
>`Calendar`类当初设计时的一个bug，由于已经使用开来，没法贸然的修改

## 查源码找答案

下面是Calendar类中属性`MONTH`的注释以及定义：
```java
 /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * month. This is a calendar-specific value. The first month of
     * the year in the Gregorian and Julian calendars is
     * <code>JANUARY</code> which is 0; the last depends on the number
     * of months in a year.
     *
     * @see #JANUARY
     * @see #FEBRUARY
     * @see #MARCH
     * @see #APRIL
     * @see #MAY
     * @see #JUNE
     * @see #JULY
     * @see #AUGUST
     * @see #SEPTEMBER
     * @see #OCTOBER
     * @see #NOVEMBER
     * @see #DECEMBER
     * @see #UNDECIMBER
     */
    public final static int MONTH = 2;
```

注释大致的意思是：
>字段编号指示`月份`以用于get/set方法，这是特定于日历的值。 格列高利历(Gregorian) /朱利安历(Julian)的一年中的第一个月是`JANUARY`，即`0`;  最后一个月份取决于一年中的月数。

最后一句话是什么意思呢? 下面再说。 我们一起看一下上述`13`个月份的定义，请注意，不是12个月，而是13个月。

```java
    /**
     * Value of the {@link #MONTH} field indicating the
     * first month of the year in the Gregorian and Julian calendars.
     */
    public final static int JANUARY = 0;

    /**
     * Value of the {@link #MONTH} field indicating the
     * second month of the year in the Gregorian and Julian calendars.
     */
    public final static int FEBRUARY = 1;

    /**
     * Value of the {@link #MONTH} field indicating the
     * third month of the year in the Gregorian and Julian calendars.
     */
    public final static int MARCH = 2;

    /**
     * Value of the {@link #MONTH} field indicating the
     * fourth month of the year in the Gregorian and Julian calendars.
     */
    public final static int APRIL = 3;

    /**
     * Value of the {@link #MONTH} field indicating the
     * fifth month of the year in the Gregorian and Julian calendars.
     */
    public final static int MAY = 4;

    /**
     * Value of the {@link #MONTH} field indicating the
     * sixth month of the year in the Gregorian and Julian calendars.
     */
    public final static int JUNE = 5;

    /**
     * Value of the {@link #MONTH} field indicating the
     * seventh month of the year in the Gregorian and Julian calendars.
     */
    public final static int JULY = 6;

    /**
     * Value of the {@link #MONTH} field indicating the
     * eighth month of the year in the Gregorian and Julian calendars.
     */
    public final static int AUGUST = 7;

    /**
     * Value of the {@link #MONTH} field indicating the
     * ninth month of the year in the Gregorian and Julian calendars.
     */
    public final static int SEPTEMBER = 8;

    /**
     * Value of the {@link #MONTH} field indicating the
     * tenth month of the year in the Gregorian and Julian calendars.
     */
    public final static int OCTOBER = 9;

    /**
     * Value of the {@link #MONTH} field indicating the
     * eleventh month of the year in the Gregorian and Julian calendars.
     */
    public final static int NOVEMBER = 10;

    /**
     * Value of the {@link #MONTH} field indicating the
     * twelfth month of the year in the Gregorian and Julian calendars.
     */
    public final static int DECEMBER = 11;

    /**
     * Value of the {@link #MONTH} field indicating the
     * thirteenth month of the year. Although <code>GregorianCalendar</code>
     * does not use this value, lunar calendars do.
     */
    public final static int UNDECIMBER = 12;
```

把重点放在第一个月以及最后一个月的注释上面：

JANUARY初始化int数值 = `0`， 指示在格列高利历(Gregorian) /朱利安历(Julian)中的第一个月份
> JANUARY = 0  -  indicating the first month of the year in the Gregorian and Julian calendars. 

> 格里高利历（Gregorian Calendar）
>格里高利历，是国际通用的历法，即公历。到今天，格里高利历已被世界广泛采用，成为国际通用历法。

### 中国采用格里高利历
>中国使用格里高利历是在公元1912年1月1日，中华民国成立之时。但由于历史原因，依旧使用中华民国记年。类似的情况如日本至今还保持着天皇年号纪年，比如平成某某年。公元1949年10月1日，中华人民共和国成立，正式采用公元纪年法。

因为中国人民在日常人活中的月份都是从`1`开始计算的，而`Calendar`类从`0`开始算，于是乎便解释了为何`取出的月份比实际少1`。

##  为何要将JANUARY定义为0
目前确实也没有一个准确的答案，但还是可以挑选出一些大家认为合理的：

 1. 数组以0作为索引开始，月份也借鉴此做法；
 2. 年份月份日期唯独只有月份有自己的名字，什么意思呢? 一月 = January，二月=February... 于是将其从0开始标注索引
 3. Java是基于C语言的，而C语言的'time.h'里面的月份`tm_mon `也是从0~11
 4. SUN公司开发人员的懒惰

## 【重要】使用Calendar关于月份的建议

>set 月份时 一律  - 1
>get 月份时 一律 + 1

```java
@Test
public void testCalendar() {
    Calendar cal = Calendar.getInstance();
    // 当前月份是 1月
    // 若不对月份做处理 则打印结果为 0
    System.out.println(cal.get(Calendar.MONTH));
    // 期望打印当前实际月份 则+1 打印 = 1
    System.out.println(cal.get(Calendar.MONTH) + 1);
    
    //  期望设置日历的月份 = 8月  -> 将set与get独立
    cal.set(Calendar.MONTH, 8 - 1);
    //  打印设置是否有效    -> 将set与get独立 
    System.out.println(cal.get(Calendar.MONTH) + 1);
}
```
当然在同时存在`get()`和`set()`月份方法的时候，你不额外加`+1`和`-1`，数据是没有问题的。但：如果两个方法调用相隔很远，又或者只有其中一个方法呢 ?

若是某个客户端使用了错误生成日历的方法，找到问题的根源会比较麻烦。尽可能的按照上述要求来做，这样在日历的月份上出错的可能性大大降低。

执行结果:
>0
1
8

## 【推荐】日历替代方案

[joda-time](https://www.joda.org/joda-time/)
