---
title: 【轮盘赌算法】Java给定List，元素越大取到的概率越大(越小)
date: 2018-12-24 10:08:07
tags: ['轮盘赌','集合取值','值越大概率大']
categories: 
 - 开发语言
 - Java
---

# 背景

数据库里面存储姓氏表，但是姓氏有权重，也就是说权重越大，被取到的概率越高。我是通过JAVA实现的，未通过SQL来实现（有点复杂）。


## 参考

参考此处 [mr_orange_klj的博客](https://blog.csdn.net/mr_orange_klj/article/details/78063563)，已经在他的实现上做了改进。

# 具体实现

```java
package com.amos.learn.algol;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * 轮盘赌算法
 *
 * @author amos
 */
public class Roulette {

    /**
     * @param list 将原list转化为各自的概率list
     * @param pow  [pow >= 1]  列表中的数越大取到的概率越大，反之概率越小
     */
    private List<Double> listRate(List<Double> list, int pow) {

        // 保留小数点位数
        int digit = 4;
        // 计算整个list中进行次方计算后的总和
        double sum = 0;

        List<Double> rateList = new LinkedList<>();
        for (Double i :
                list) {
            sum += Math.pow(i, pow);
        }
        // 计算各自的概率
        BigDecimal rateSum = BigDecimal.ZERO;
        for (int i = 0; i < list.size(); i++) {

            BigDecimal powResult = new BigDecimal(Math.pow(list.get(i), pow))
                .setScale(digit, RoundingMode.HALF_UP);

            BigDecimal value;
            // 最后一个元素的概率可能会有一定的误差
            // 用 1 - 之前的概率和来消除误差
            if (i == list.size() - 1) {
                value = BigDecimal.ONE.subtract(rateSum)
                    .setScale(digit, RoundingMode.HALF_UP);
            }
            else {
                value = powResult.divide(new BigDecimal(sum)
                    .setScale(digit, RoundingMode.HALF_UP), RoundingMode.HALF_UP);
            }
            rateSum = rateSum.add(value);
            rateList.add(value.doubleValue());
        }
        return rateList;

    }

    /**
     * @param p 权重数组
     * @return 被选中的数值
     */
    private int roulette(List<Double> p) {

        double ran = Math.random();
        double pointer = 0;
        for (int i = 0; i < p.size(); i++) {
            pointer += p.get(i);
            if (ran <= pointer) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
	
		int pow = -1;
        Roulette roulette = new Roulette();
        List<Double> list = new LinkedList<>();
        list.add(1d);
        list.add(2d);
        list.add(3d);
        list.add(4d);
        List<Double> rateList = roulette.listRate(list, pow);
        System.out.println(rateList);
        //  保留当前元素出现次数的map
        Map<Double, Integer> map = new LinkedHashMap<>(12);
        // 初始化map
        for (Double d :
                list) {
            map.put(d, 0);
        }
        for (int i = 0; i < 1000000; i++) {
            // rou点得到的当前list的位置
            int indicator = roulette.roulette(rateList);
            // 将map里面的数值 + 1
            map.put(list.get(indicator), map.get(list.get(indicator)) + 1);
        }
        System.out.println(map);
    }
}
```

## pow = -1

结果
>[0.48, 0.24, 0.16, 0.12]
{1.0=479598, 2.0=240974, 3.0=159972, 4.0=119456}

## pow = 2

结果
>[0.0333, 0.1333, 0.3, 0.5334]
{1.0=32932, 2.0=133382, 3.0=299979, 4.0=533707}

从上面的结果可以看出，随机取到的次数和概率是非常接近的。
