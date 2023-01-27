---
title: Python函数式编程简单示例
date: 2017-10-09 16:28:23
tags: ['python','函数式编程','lambda','reduce','map']
categories: 
 - 开发语言
 - Python
---

## 斐波那契数列

思路：1.将相应位置上的数值先求出来，2.利用map计算出数列

```python
def f(n):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		return f(n-2)+f(n-1)
		
if __name__ == "__main__":

	print map(f, range(1,11))
```


打印结果

> [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]

## n！+(n-1)! + ... + 2!+1!

思路：1. 先写出求阶乘的函数，2.再用reduce求和

先写求阶乘的函数：

```python
# coding:utf-8

def factorial(n):

	return reduce(lambda x,y:x*y, range(1,n+1)) # 返回 n*(n-1)*...*2*1
```

再用reduce求和

```python
def fact_sum(n):
	
	# map 将n，n-1，...，2，1的阶乘算出来放在一个列表内
	# reduce 将列表内的所有数进行相加
	return reduce(lambda x,y:x+y, map(factorial, range(1,n+1)))
	
```

将这两个函数合在一起表示：

```python
#求10!+9!+...+2!+1!
print reduce(lambda x,y:x+y, map(lambda n:reduce(lambda x,y:x*y, range(1,n+1)), range(1,10+1)))
```

用到函数式编程，代码量确实精简了许多。很显然，这一行代码的可读性很差，所以一般情况下，函数式编程需要用得教合理为宜。

## 计算（a,b）之间的质数

思路：1.先写出算质数的函数，2.用filter方法将符合的质数筛选出来。

求质数：

```python
def prime(n):

	j = not [n%k for k in range(2,n/2+1) if not n%k]
	# 列表推导，一个数n对2,3,4...n/2-1,n/2求余，若能整除，则列表中必有一个元素0
	# 再将列表用bool表示，能整除时列表为True，不能整除时列表为False，
	# 取反：not [...] 能整除时列表为False非质数，不能整除时列表为True质数
	# 说一下k的范围为什么是(2,n/2+1),k实际取值是 2到n/2. 首先是为了节省计算的时间空间, 
	# n最小能被2整除，所以当k等于n/2时
	# n/2+1,n/2+2,...n-1 后面的可以不用再算了，肯定是除不尽的。大家可以用一个奇数一个偶数来试试
	# 奇数n=15，k取到n/2=7即可，没错吧? 
	# 偶数n=16，k取到n/2=8即可，也没问题。
	return j
```

使用filter将某个区间符合条件的质数筛选出来

```python
def is_prime(a,b):
	filter(prime, range(a,b+1)))
```

一句话表示：

```python
# 求1000-1100之间的质数
print(filter(lambda x:not [x%i for i in range(2,x/2+1) if not x%i], range(1000,1100+1)))
```