---
layout: post
title: Linear Search
permalink: /linear_search/
---

# What is Linear Search?
It is the most simplest searching algorithm. The strategy is to simply compare the target element (i.e. the element is to search) with each and every element of the array or list. In simple words, this strategy is what a layman could think!

# Concept of Linear Search
Consider a sorted array `a[]` of n elements, and an element x is to be searched whether it is present in the array or not. 
Following rules are repeatedly followed:
 * Compare the target element `x` with each element of the array
 * Return the index i of the element if `x = a[i]`
This concept will be better understood by going through the following illustration. 
# Illustration of Linear Search
Consider the following array. Here element to search is `x = 4` and it matches at `index 3`
 https://user-images.githubusercontent.com/35966401/48720491-0034de80-ec4a-11e8-8ed2-87ee327ff550.png
<p align="center">
   <img src="https://user-images.githubusercontent.com/35966401/48720491-0034de80-ec4a-11e8-8ed2-87ee327ff550.png" alt="" />
  
</p>

                                                                                       
### Pseudo Code of Linear Search
```py
## PSEUDO CODE
 LinearSearch(L,key):  
  for i in range(len(L)):
    if L[i] == key:
      return i
  retrun -1 it is returned only when element is not found
```

# Code of Linear Search
```py
## Define a function 

def LinearSearch(L,key):  
  for i in range(len(L)):
    if L[i] == key:
      return i
  return -1

if __name__ == "__main__":  ##
  list1 = [0,2,1,4,5]
  k = 5
  print('Found in index',LinearSearch(list,k)) 
```
### Output :
```py 
Found in index 4 
```
