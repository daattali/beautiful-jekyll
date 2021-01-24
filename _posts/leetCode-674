leetCode 每日一题 674
给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。

连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。

示例 1：

输入：nums = [1,3,5,4,7]
输出：3
解释：最长连续递增序列是 [1,3,5], 长度为3。
尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。 
示例 2：

输入：nums = [2,2,2,2,2]
输出：1
解释：最长连续递增序列是 [2], 长度为1。
 

提示：

0 <= nums.length <= 104
-109 <= nums[i] <= 109
## 题解

### 一维DP，保存前一位的最大连续数组
'''python3
class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        if not nums: return 0
        dp = [1 for x in nums]
        for i in range(1,len(nums)):
            if nums[i] > nums[i-1]: dp[i] = dp[i-1]+1
            else: dp[i] = 1
        return max(dp)
'''

### 不需要保存所有的状态值，可以仅保存最新的1个状态
"""python3
class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        if not nums: return 0
        res,temp = 1,1
        for i in range(1,len(nums)):
            if nums[i-1] < nums[i]: temp += 1
            else:res,temp = max(res,temp),1
        return max(res,temp)
"""
