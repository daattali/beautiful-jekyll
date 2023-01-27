---
title: 【算法】从多个部门选择不在同个部门的人员
date: 2020-11-13 12:32:00
tags: ['算法','面试题']
mathjax: true
categories: 
 - 计算机基础
 - 算法
---


# 题目

来源：同事面试之前需要做一份笔试题，这是笔试题里面的其中一道题。


市场部门委托进行分组方案数量计算的程序开发，需求如下：某网格下按照区域分为四个大组，每个大组内销售经理人数分别为a,b,c,d人，需要从中选出2人，且2人不能再同一个大组中。程序需要输入四个组人数的情况下，输出全部选取方式的数量。

输入：第一行输入四个整数a b c d

输出：可选方案的总数量

输入样例：1, 2, 1, 0 ; 输出样例： 5



## 简单解法

此方法需要对概率计算的理解比较通透，我们把四个组，两两分组成一对：

[a,b],[a,c],[a,d] | [b,c],[b,d] | [c,d]

因为需要每一个组中人员不可以重复选，也就是说：该组几个人，就有几种可能，于是乎：

    sum = a*b + a*c + a*d + b*c + b*d + c*d

## 递归

定义一个方法，该方法的输入为一个int数组{a,b,c,d}，以及需要从数组中选中人员数目。比如我们需要计算4个组中，2个人员个数：

func({a,b,c,d}, 2), 方法的返回为，当前数组中，选择对应人数的方案个数。

4选2 拆分 = （第一位选0） 1 \* 剩余3选2 + （第一位选1 ） a \* 剩余3选1

    func({a,b,c,d}, 2) = 1 * func({b,c,d}, 2) + a * func({b,c,d}, 1);

3选1， 3选2，同理拆分， 直到数组只剩下最后一个元素：

func({d}, 0) = 1
func({d}, 1) = d
func({d}, >1) = 0

完整的代码片段：

```java
/**
 * @param nums 数组 比如  {1, 2, 1, 0}
 * @param count 需要选择的人员数
 */
public static int calculate(int[] nums, int count) {
    // 数组长度
    int length = nums.length;
    // 当前数组的第一个元素 方便后面的计算
    int first = nums[0];
    // 数组中最后一个元素的情况
    if (length == 1) {
        if (count == 0) {
            return 1;
        } else if (count == 1) {
            return first;
        } else {
            return 0;
        }
    }
    int[] newNums = new int[length-1];
    for (int i = 0; i < length-1; i++) {
        newNums[i] = nums[i + 1];
    }
    // 若当前位置选0 去掉该位之后可选方案
    int calZero = calculate(newNums, count);
    // 若当前位置选1 去掉该位之后可选方案
    int calOne = calculate(newNums, count - 1) * first;
    return calOne + calZero;
}
```
