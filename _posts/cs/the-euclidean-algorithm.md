---
title: 【算法】欧几里得算法（辗转相除法）简易证明
date: 2020-07-17 22:32:00
tags: ['算法','欧几里得']
mathjax: true
categories: 
 - 计算机基础
 - 算法
---

## 题目来源
近来看到书籍《算法图解》里面的一个例子：
>假设你是农场主，有一块土地，你要将这块地均匀地分为方块，且分出来的分块要尽可能的大。
![例子](https://i.loli.net/2020/09/25/KDathTjqQ4Jw8IA.png)


书中并未给出的解答过程就是用的欧几里得算法，具体证明过程无，我自己画了个图方便理解。

![图示](https://i.loli.net/2020/09/25/g6lL4W3IwTR9tiD.png)

步骤：

 1. 从这块地`1680x640`中划出两个`640x640`的方块，剩下的土地使用`同样的计算方法`:**适用于剩余小块地的最大方块，也是适用于整块地的最大方块**
 2. 从剩余的（1680-2*640=400）`640x400`的方块中，划出一块`400x400`
 3. 从剩余的（640-400=240）`400x240`的方块中，划出一块`240x240`
 4. 从剩余的（400-240=160）`240x160`的方块中，划出一块`160x160`
 5. 从剩余的（240-160=80）`160x80`的方块中，划出一块`80x80`，剩余同样是`80x80`（划出那块的n倍，此处n=1），结束

问题在哪里呢? 问题就出在：适用于剩余小块地的最大方块，也是适用于整块地的最大方块 ！！？？

## 证明过程

上面的整个计算过程实际上也是计算A,B两个数值的最大公约数（Greatest Common Divisor：记作符号`gcd`）的过程， 理解了这句话才好进行后面的推断过程。

### 示例

$$gcd(1680, 640) = gcd(640, 400) = gcd(400, 240) \\ = gcd(240, 160) = gcd(160, 80) = gcd(80, 0) = 80;$$

假设：
$$
A = P \ast B+Q; \text{(P,Q为正整数)}
$$
现在我们需要证明为何 ：

$$
gcd(A, B) = gcd(B, A-B)=gcd(B, A-nB) = gcd(Q,B);\\ \text{(n为使得nB≤A的任意正整数)}
$$

### 理解算法

证明`gcd(A,0)=A`, `gcd(0,B)=B`
- 因为A×1=A； 能整除A的最大约数是A：A÷A=1
- 因为对于任意整数C，都有C×0=0；可以得出0也可以整除A：0÷A=0
- 所以A和0的最大公约数就是A

证明B同理；

假设`A-B=C`; 现在证明gcd(A,B)也可以整除C：
>因为：gcd(A,B)是A，B的最大公约数
所以：
1.必定存在一个数整数X，使得X×gcd(A,B)=A
2.必定存在一个数整数Y，使得Y×gcd(A,B)=B

根据A-B=C；于是有
$$
X \ast gcd(A,B) - Y \ast gcd(A,B) = C;
$$
也即
$$
(X-Y) \ast gcd(A,B) = C;
$$

于是：`gcd(A,B)也可以整除C`

根据`A-B=C`；现在证明gcd(B,C)也可以整除A：

>因为：gcd(B,C)是B，C的最大公约数
所以：
1.必定存在一个数整数S，使得S×gcd(B,C)=B
2.必定存在一个数整数T，使得T×gcd(B,C)=C

根据A-B=C；于是有 A=B+C
$$
S \ast gcd(B,C) + T \ast gcd(B,C)= A
$$
也即
$$
(S+T) \ast gcd(B,C)= A
$$

于是：`gcd(B,C)也可以整除A`

根据目前已经证明的：

 - `gcd(A,B)也可以整除C` - 命名为`已证01`
 - `gcd(B,C)也可以整除A` - 命名为`已证02`

**重点：**
因为gcd(A,B)可以整除B（根据定义）和C（根据`已证01`），则gcd(A,B)是B和C的`公约数`，gcd(B,C)也可以整除B和C，并且gcd(B,C)是B和C的`最大公约数`，那么可以得出：
>gcd(B,C)一定是大于或者等于gcd(A,B) - 命名为`已证03` 。

因为gcd(B,C)可以整除A（根据`已证02`）和B（根据定义），则gcd(B,C)是A和B的`公约数`，gcd(A,B)也可以整除A和B，并且gcd(A,B)是A和B的`最大公约数`，那么可以得出：
>gcd(A,B)一定是大于或者等于gcd(B,C) - 命名为`已证04`；

在根据`已证03`和`已证04`（如果a≥b并且b≥a，那么a=b）：
$$
gcd(A,B) = gcd(B,C) =gcd(B,A-B) =gcd(A-B,B) ;
$$
再根据上面得出的结论`gcd(A,B) = gcd(A-B,B)` 可以得出：
$$
gcd(A,B) = gcd(A-B,B)  = gcd(A-B -B,B) =   gcd(A-2B,B)  = ... =gcd(A-nB,B),(nB≤A);
$$

因为之前的假设：
$$
A = P \ast B+Q;
$$
这里我们令`n = P`
$$
gcd(A, B) = gcd(P \ast B+Q, B) = gcd(P \ast B+Q - nB, B) = gcd(Q , B) = gcd(B , Q) ;
$$
得证!

### 参考
[The Euclidean Algorithm](https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/the-euclidean-algorithm)