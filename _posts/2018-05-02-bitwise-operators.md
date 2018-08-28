---
layout: post
title:  "Bitwise Operators"
categories: jekyll update
---

I recently ran into a javascript coding problem that lent itself
well to a solution involving bitwise operations, which prompted me
to write a post about the topic. 

In this problem, you are given array of integers. One of these
integers will appear an odd number of times, and you want to 
find said integer. The solution to the problem is given below:

{% highlight javascript %}
	let findOdd = (arr) => arr.reduce((a, b)=> a^b);
	
	let nums = [1,1,2,-2,5,2,4,4,-1,-2,5];
	findOdd(nums);
	// >> -1
{% endhighlight %}

In the above solution, we are making use of the bitwise **XOR** 
operator (^), which performs the logical exclusive or operation on the binary representations of 'a' and 'b'. 

'a' and 'b' start out as the first two numbers in the array. We apply the XOR operator on these two numbers, then use the result as the 'a' term and the next number in the array as the 'b' term until we've gone through the array applying XOR.

In the XOR operation, we take two bit patterns of the same length
and then perform a logical exclusive or operation on each pair of 
corresponding bits. 

This operation returns 1 if only one of the two bits in the pair are 1,
otherwise it returns 0.

	 1 ^ 5 = 0001 // 1
             0101 // 5
        XOR  ____
             0100 // 4


If two numbers are the same and have an XOR applied, they will "cancel
out" of the sequence due to the logic of XOR. So, for our problem, only a 
number that appears an odd number of times will not have been cancelled
out by the last application of XOR.

		[2,3,2].reduce((a,b)=>a^b);
     /****************************************/

        2^3 = 0010 //2
              0011 //3
         XOR  ____
              0001 //1

        1^2 = 0001 //1
              0010 //2
          XOR ____ 
              0011 //3, our answer    

## The Bitwise Operators ##

Bitwise operations are ubiquitous in programming! 

Here are some of the common bitwise operators supported in JavaScript:

**AND (a&b)**:
given two bit sequences, returns 1 where both bits in a pair
are 1, and 0 otherwise.


	3&4 = 0011 //3
          0100 //4
      AND ____ 
          0000 //0


**OR (a|b)**:
given two bit sequences, returns 1 when at least one bit in a pair
is 1, and 0 otherwise.


	3|4 = 0011 //3
          0100 //4
      AND ____ 
          0111 //7


**NOT (~a)**:
Inverts the bit sequence given.


	7  =   0111 
	~7 =   1000 //-8


**Left Shift (a << b)**:
Will shift the binary representation of a b bits to the left.
0 shifts in for the rightmost bits as shifting occurs.
Supports up to 32 bits.

	4 << 3:
	         00000100 //4
             00100000 //32 


 In the future, I hope to add to this blog post with more example
 problems that use bitwise operations, but in the meantime, here is one
 more! You can multiply a number by 7 using the left shift operation
 as follows:

{% highlight javascript %}
	let multSeven = (num) => (num<<3) - num;
	multSeven(7);
	// >> 49
{% endhighlight %}




