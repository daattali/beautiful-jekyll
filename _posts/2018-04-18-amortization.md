---
layout: post
title:  "Amortized Runtime"
categories: jekyll update
---


**Amortized runtime analysis** is a runtime analysis where we average the runtime of performing a sequence of data structure operations over all operations performed in order to arrive at a guaranteed average performance for each operation in the worst case. 

This is a relevant analysis when the cost of an operation will vary in the sequence (i.e. it is expensive at some points and not at others).

## Application ##
As an example, consider a dynamically resized array where capacity 
grows as elements are inserted. Such a data structure will be implemented
using a static array where elements are inserted into the static array
until capacity is reached, each insertion taking O(1) time. Once capacity
is reached, however, then we will need to create a new array that is 
twice the size of the previous array and copy all n elements over, 
giving us an insertion time of O(n) for this nth operation in the sequence.


	[1] => [1, _]        # add(1): Insert 1 into array of size 1.
                         #         Array is full, so copy over everything 
                         #         into array size 2. O(n)

	[1,2] => [1,2,_,_]   #add(2): Insert 2 into array size 2. 
                         #        Array is full, so copy over everything
                         #        into new array of size 4. O(n)

	[1,2,3,_]            #add(3): Insert 3 into array size 4.
                         #        O(1) 

	[1,2,3,4]=>          #add(4): Insert 4 into array of size 4. 
	[1,2,3,4,_,_,_,_]    #        Array is full, so copy over everything
	                     #        into array of size 8. O(n)

	[1,2,3,4,5,_,_,_]    #add(5): Insert 5 into array of size 8.
	                     #        O(1))

	[1,2,3,4,5,6,_,_]    #add(6): Insert 6 into array of size 8. O(1)

	[1,2,3,4,5,6,7,_]    #add(7): Insert 7 into array of size 8. O(1)  

	[1,2,3,4,5,6,7,8]=>  #add(8): Insert 8 into array of size 8. 
	[1,2,3,4,5,6,7,8,    #        Array is full, so copy over 
	 _,_,_,_,_,_,_,_]    #        everything into array of size 16. O(n)

Notice that we double the size of the array as we hit an nth insertion that is a power of 2. 
In other words, the nth insertion where n is a power of 2 is O(n). All other
insertions will take O(1) time.


When describing the runtime of insertion into a dynamic array, saying
it is O(n) time would not reflect that not all insertions
will take that time. Instead, we would want an average cost for insertion.

After X elements, we double capacity for array sizes $$1, 2, 4, 8, 16...X$$. 
This will respectively take $$1, 2, 4, 8, 16...X$$ copies into the new arrays.
The runtime can be thought of in terms of the series
$$1 + 2 + 4 + 8 + 16 +...+X$$, where X is the number of elements inserted. X will
be a power of 2 to refelct worst case scenario for last insertion.

The above series can be expressed as $$X + X/2 + X/4 + X/8 + ... 1$$, as it 
begins at 1 and doubles each time to reach X.

Using the formula for a geomtric series below, we find that the series
is roughly equal to 2X-1.

$$2^k+\frac{2^k}{2}+\frac{2^k}{4}+⋯+1 =$$

$$2^k+2^{k−1}+2^{k−2}+⋯+1=$$

$$2^{k+1}−1 =$$

$$2n−1$$

For example, 
$$x = 2^4 = 16,  k = 4$$   

$$16+8+4+2+1 = $$

$$16 + \frac{16}{2} + \frac{16}{4} + \frac{16}{8} + 1 = $$

$$2^4 + 2^3 + 2^2 + 2^1 + 1 = $$

$$2^5 - 1 = $$

$$31 $$ 

Since X insertions takes O(2X) time, the ammortized time for each insertion is O(1).

The method we just used above to determine the amortized runtime is 
referred to as **aggreggate analysis**, in which we determine an
upper bound T(n) on the total cost of a sequence of n operations and
average the cost as T(n)/n.

There are two more powerful techniques in ammortized analysis called
the **accounting method** and the **potential method**, which we may
discuss at a later time.


