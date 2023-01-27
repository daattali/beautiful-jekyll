---
title: Python leetcode记录(1) -Two Sum
date: 2017-08-23 18:43:36
tags: ['python','leetcode','编码练习','算法练习','python学习']
categories: 
 - 开发语言
 - Python
---

leetcode官网: [传送门](https://leetcode.com/)

# 题目 Two Sum

    Given an array of integers, return indices of the two numbers such that they add up to a specific target.
    You may assume that each input would have exactly one solution, and you may not use the same element twice.

    Example:
    Given nums = [2, 7, 11, 15], target = 9,

    Because nums[0] + nums[1] = 2 + 7 = 9,
    return [0, 1].



我的答案: 基于python

```python
class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        # 这里是我的答案
        for i in range(len(nums)):

            x = target - nums[i]
            nums.remove(nums[i])
            if x in nums:

                return [i, i+nums.index(x)+1]
```

略坑，上面的答案是错的。进行改进，但是感觉还是太复杂了一些。

```python
import copy
class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        n = copy.deepcopy(nums)
        for i in range(len(nums)):

            x = target - n[i]
            nums.remove(n[i])
            if x in nums:

                return [i, i+nums.index(x)+1]

```

8月24号9:12再次改进，不使用deepcopy

```python
class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
	    for i in range(len(nums)):
	
	        x = target - nums[0]
	        nums.remove(nums[0])
	        if x in nums:
	            return [i, i + nums.index(x) + 1]
```

解题思路: 已知列表[1,3,5,7]和目标6，遍历列表的元素，先取第一个元素，6-1=5，判断5是否在列表中，如果在列表中，则返回第一个元素的位置和5的位置，如果不在列表中，把此元素从列表中移除，继续循环，直到返回为止。**谨记题目说有且只有一个解决方案。**
