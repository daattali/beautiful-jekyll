---
layout: post
title:  "Recursion, Big O, and the Fibonnaci Sequence"
subtitle: Introduction to recursion
categories: jekyll update
---
 

Problems requiring recursive solutions are rather common in the world of programming. 
As such, it is worthwhile to become acquainted with the concept during one's coding journey.
First, what exactly is recursion? Recursion is a **"divide-and-conquer"** 
approach to problem solving where we:

 1. **Divide** the problem into subproblems that are smaller instances of the same problem.

 2. **Conquer** the subproblems by solving them recursively. If a subproblem is of a trivial size,
 then we have reached a **base case** and can solve said subproblem directly.

 3. **Combine** the solutions to the subproblems to get a solution to the initial problem.

_(adapted from "Introduction to Algorithms," Cormen et. al, 2009)_


A common problem given to students to introduce them to recursive problem solving is finding the
nth number in the Fibonnaci Sequence. Let's walk through the problem and become better acquainted
with recursion.

## Fibonnaci Sequence ##

The Fibonnaci Sequence is defined as follows for f(n), where i indicates the ith number in the sequence:

   >	    i = 0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10 ......        n

 >	 f(n) = 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 ...... f(n-1) + f(n-2) 	
					

As we can see, the above definition of the fibonacci function lends itself to recursion because each 
instance of the problem f(n) can be broken down into two other components that are the same problem, f(n-1) + f(n-2).

Our base case will be the beginning two positions in the sequence, i = 0 and 1 where it is trivial that f(0) = 0
and f(1) = 1.

So, let's go ahead and type up a quick recursive function in Ruby that will solve for the nth Fibonnaci number. 
Programming languages often allow recursion in functions by allowing functions to call themselves within their own
code. 

{% highlight ruby %}
  def fib(n)
    #Le Base Case n == 0 or 1
    return n if n <= 1

    #Le break into subproblems
    (fib(n-1) + fib(n-2)) 
  end
{% endhighlight %}


Note that you can also solve this iteratively, shown below. This will be a quicker
solution in terms of run time, but it is not recursive. 

{% highlight ruby %}
  def fib_iterative(n)
    arr = [0,1]
    i = 2
    while i <= n do
      arr << arr[i-1] + arr[i-2]
      i += 1
    end
    arr[n]
  end  
{% endhighlight %}

Our recursive sequences of calls can be represented as a tree. For example,
consider that we want to find the 4th fibonacci number. As we can see from
the tree below, the function will recursively call on itself with smaller sub problems of fib(n-1) and fib(n-2) until we reach the base cases of n = 1 or 0.
At that point, we propogate the results back up the chain of calls and combine
them to receive our answer.


                       f(4)  = 3                                   
                    /       \                          
                   /         \                       
                f(3)=2  +   f(2) = 1                
               / \            /    \               
              /   \          /      \              
          f(2)=1 + f(1)=1  f(1)=1 + f(0)=0            
          / \                                 
         /   \                                
    f(1)=1 + f(0)=0                              
                                              

You may have noticed that the above function call sequence seems rather long. As 
our value, n, increases, our recursive tree will branch out and increase in depth.
This leads us to our discussion of **Big O Notation**.

## Big O Notation ##

**Big O** notation is used to describe the worst-case performance of an algorithm's 
run-time by giving an upper bound for the growth of its running time as input size tends to infinity. It can also be used to describe space used by an algorithm.

![runtime-graph](https://ka-perseus-images.s3.amazonaws.com/501211c02f4c6765f60f23842450e1151cfd9c89.png){:class="img-responsive"}

**Some Examples:**
 - O(1): An algorithm that always executes in the same time no matter the size of the input.

 {% highlight ruby %}
    def return_first(arr)
      arr[0]
    end
{% endhighlight %}

- O(N): An algorithm whose performance grows linearly in proportion to 
the size of the input.

 {% highlight ruby %}
    def add_one_to_each(arr)
      arr.map{|x| x + 1}
    end
{% endhighlight %}

- O(N^2): An algorithm whose performance grows proportional to the square of the size of the input. Happens with nested iterations. Deeper nesting results in O(N^k)
complexity, where k is the depth of nesting.

- O(2^n): An algorithm's performance time will double for each increase to the input size.

So, just how fast is our recursive approach to the Fibonnaci problem? Let's take a look at a general case recursion tree for the problem.

                          f(n)                     -  Branching factor of 2               
                         /    \                    |     -> doubles each level
                        /      \                   |  Maximum depth of n levels  
                     f(n-1)    f(n-2)              |     -2 branches
                    / \          / \               |
                   /   \        /   \              |    
               f(n-2)  f(n-3) f(n-3) f(n-4)        |    - 4 branches
               / \        /\    / \    /  \        |
              /   \      /  \              \       |    
         f(n-3)f(n-4) f(n-4) f(n-5)  .... f(n-6)   |    - 8 branches 
                                                   - 

 - Since we are going from n down to the base cases, decreasing n by 1 each level, in the worst case we will have n levels to this tree
 - When we get down to the bottom of the tree, and we have n levels, and the number of branches doubles each time, we will 
   in the worst case have 2^n leaf nodes. Each leaf node will be evaluated in constant time.
 - Thus we can say our function runs in O(2^n) time roughly from the leaf nodes. Adding all the leaf nodes together would look like: 2^n + 2^n-1 +2^n-2 +... 2^0. Since 2^n 
   contains our largest exponent,  it will define the bound of the function as input size approaches infinity. 


**More on Runtime**
Let's take a closer look at the runtime of the fibonnaci ruby function again, this time getting to it in a different way.

{% highlight ruby %}
  def fib(n)
    #Comparison is O(1)
    return n if n <= 1

    #Le break into subproblems
    (fib(n-1) + fib(n-2))
    #O(1)   O(1)   O(1)
    # Substraction is O(1), addition is O(1),
    # we want to find out what the O is of fib ()   
  end
{% endhighlight %}


From the above, we can try to calculate the time of running fib on n as follows:

T(n) = T(n-1) + T(n-2) + 4, where T(0) = T(1) = 1

**Lower Bound:**

T(n-1) ⪆ T(n-2)

=> T(n) ≈ 2T(n-2) + c, c=4, k = 1 **<-- Lower bound, since T(n-1) is a bit bigger than T(n-2), the expression we substitute for**

T(n-2) = T(n-3) + T(n-4) + c, T(n-3) ⪆ T(n-4)

=> T(n) = 2{2T(n-4) + c} + c, k = 2

=> T(n) ≈ 4T(n-4) + 3c, k =2

=> T(n) ≈ 8T(n-6) + 7c, k =3

...
=> T(n) ≈ 2^kT(n-2k) + (2^k-1)c

T(0) = T(n-2k) => k = n/2

=> T(n) ≈ 2^(n/2)T(0) + (2^(n/2)-1)c

=> T(n) ≈ (1+c)\*2^(n/2) - c

Thus, on the lower bound, we have T(n) is proportional to 2^(n/2)


**Upper Bound:**

T(n-2)  ⪅ T(n-1)

=> T(n) ≈ 2T(n-1) + c, c=4, k = 1 **<-- Upper bound, since T(n-2) is a bit smaller than T(n-1), the expression we substitute for**

T(n-1) = T(n-2) + T(n-3) + c, T(n-3) ⪅  T(n-2)

=> T(n) = 4T(n-2) +3c

=> T(n) ≈ 8T(n-3) + 7c, k =3

...

=> T(n) ≈ 2^kT(n-k) + (2^k-1)c

T(0) = T(n-k) => k = n

=> T(n) ≈ 2^nT(0) + (2^n-1)c

=> T(n) ≈ (1+c)\*2^n - c

Thus, on the upper bound, we have T(n) is proportional to 2^n. We can say that fib(n) is O(2^n)!
 

Now that we have a Big O estimate, how can we improve our runtime? Well, if we look at the above recursion tree, we can see that we solve for the same problems multiple times when we try to find fib(n)! For instance, above we can see that fib(n-4) is repeated multiple times on the way down to the base case. If we could somehow avoid this repeated work, we would only have to solve each fib(n-k) expression once down to the base cases.To resolve this redundancy, we can use
**dynamic programming**, which we will talk about in a later blog post.

