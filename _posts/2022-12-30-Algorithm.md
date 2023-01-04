---
layout: post
title: 算法笔记
subtitle: https://github.com/trekhleb/javascript-algorithms/blob/master/README.zh-CN.md
gh-repo: wurara/wurara.github.io
gh-badge: [star, fork, follow]
tags: [Algorithm]
comments: true
---

### 贪心算法  
  每个子问题取最优解，问题就是最优解。
  - [最简理解背包算法](https://github.com/trekhleb/javascript-algorithms/tree/master/src/algorithms/sets/knapsack-problem)
  
### 动态规划  
  每个子问题结果存缓存，下次碰到这个子问题就从缓存中获得结果。 
  
  例如：1+1+1+1+1+1=6 ==》 (1+1+1+1+1+1)+1=7  
  第一次计算结果为6，后续计算不需要从头遍历求每一次加法的解，只需要将缓存的6取出再次+1即可求解。
  
  - [好文章CSDN](https://blog.csdn.net/u013309870/article/details/75193592)
    - 自顶向下：在求算过程中缓存子问题结果（合并的子问题结果如1+1+1=3的结果）并缓存
    - 自底向上：在求算前算出每个子问题的结果并缓存
 
{: .box-note} 
动态规划是优化的分治法，将子问题的结果缓存，不需要再求已经求过的问题的解。
{: .box-note} 
 
### 分治法  
  如果在求次方的过程中将每个小的次方缓存，则这个算法演变成动态规划。  
  [最简理解求次方](https://github.com/trekhleb/javascript-algorithms/tree/master/src/algorithms/math/fast-powering)
### 回溯法  
类似于 BF 算法 试图产生所有可能的解决方案，但每次生成解决方案测试如果它满足所有条件，那么只有继续生成后续解决方案。否则回溯并继续寻找不同路径的解决方案。(差不多穷举了)  
[最简理解回溯法](https://github.com/trekhleb/javascript-algorithms/tree/master/src/algorithms/sets/combination-sum)  






  [edit](https://github.com/wurara/wurara.github.io/edit/master/_posts/2022-12-30-Algorithm.md)
