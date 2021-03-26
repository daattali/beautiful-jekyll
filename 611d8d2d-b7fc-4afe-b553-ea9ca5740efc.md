 I saw this list on reddit awhile ago. I think it solidly encapsulates the core types of problem you will see in the wild:

[https://www.teamblind.com/post/New-Year-Gift---Curated-List-of-Top-100-LeetCode-Questions-to-Save-Your-Time-OaM1orEU](https://www.teamblind.com/post/New-Year-Gift---Curated-List-of-Top-100-LeetCode-Questions-to-Save-Your-Time-OaM1orEU)

From those I think the top three that pops up in technical/phone screens are graph/tree traversal, strings and arrays.  Still it's 76 problems, assuming you would want 30 minutes on average per problem and probably want to do each 3 times (not in a single session, spread out minimum by a week) then you're looking at 114 hours. I believe everyone can spare at least 5 hours each week with enough discipline (that means sacrificing socializing a little bit and maybe waking up a little early on weekends), with that assumption most people can cover it solidly within 6 months. This is a high, conservative estimate. In most cases people can cover it probably under 2\~3 months.

If you're absolutely strapped for time then here are imo the most important problems

* Array - I think you should cover this one in it's entirety (at least look at the solutions), but here are what I think are the three most important.
   * Two Sum - covers hashing, and good warm up on arrays
   * Best Time to Buy and Sell Stock - helps you get into analyzing subproblems, important for later building intuition for dynamic programming.
   * Container With Most Water - this problem reminds you that you're not limited to one pointer and/or one direction you can traverse arrays
* Binary - I kinda wanna say this one is safe to skip, but probably go over at least one. This type of problem doesn't seem to pop up too often.
   * Sum of Two Integers - light practice on using bitwise operators
* Dynamic Programming - So far I have only ran into this type problem once, and it was one of the 'easier' variant where it was backtracking with memoization. Practice due to the sheer difficulty in building intuition compared to other types of problems.
   * Coin Change - Gets you in the habit on looking at sub problems
   * Longest Increasing Subsequence - both top-down and bottom-up approaches can be applied
   * Word Break - Kinda similar general strategy to Longest Increasing Subsequence, but there seem to be a disproportionate amount of problems dealing with substrings so this might be just good overall practice.
   * Longest Common Subsequence - This sub type of problem occurs often where you need to consider allocating 2d array or thinking of a solution in '2-dimensions'  (if that makes sense).
* Graph - I think this, strings and trees are probably the most important to understand. Consider covering entirety of this section.
   * Course Schedule - gets you to consider cycles
   * Number of Islands - dfs/bfs practice
   * Alien Dictionary - this one was stupidly hard first time through, but still good practice of both building a graph (adjacency map, matrix...or really anything you prefer) and then traversing it. Something this hard will probably never pop up, but good practice.
* Interval - I can't really say how important these problems are, but the first three should be good on covering the general ideas behind this.
* Linked List - These problems are usually really easy, but always be weary what variables are actually referencing. Usually if you can't think of the clever solution you can toss into a hash map (usually)
   * Detect Cycle in a Linked List - covers slow/fast pointers, or a case where you can use a hash set
   * Merge Two Sorted Lists - practice in keeping track of pointers
   * Merge K Sorted Lists - I think this is closer to understanding sorting then pure linked list problem, but still I guess good practice
* Matrix - I don't think this is too important, it's just weird in-place matrix manipulations. The only good problem I would say is Word Search, but even that one is closer to graph traversal.
* String - Important. I will probably would want to cover this in its entirety.
   * Longest Substring Without Repeating Characters - sliding window with hashing
   * Longest Palindromic Substring - substrings pops up a lot, so good practice.  also a good general practice of 'expanding from center' for palindromes.
   * Encode and Decode Strings - good practice on string parsing
* Tree - I think this can really be grouped together with graph traversal, but there is a good probability of running into a binary tree problem. I would probably consider this one as important too and you may want to cover it's entirety.
   * Binary Tree Level Order Traversal - bfs with a small twist
   * Serialize and Deserialize Binary Tree - practice on tree traversal and I solve this problem thinking of binary tree in array form so good practice on traversing a tree when it's in array form
   * Word Search II - this one is a little weird, you need to construct your own tree (a trie to be specific) and have to traverse the graph and tree simultaneously. If you can solve this then I would think you have tree/graph traversal type problems down cold.
* Heap - Probably just go over Find Median from Data Stream and in general just get comfortable all varieties of sorting algorithms (primarily heap sort, merge sort, and quick sort).

I apologize for giant wall of text, but hopefully above will help someone. So above is around \~25 problems and estimating conservatively you should be able to cover in \~5 weeks.  


**Edit -** Also, whichever language you use get really comfortable in knowing and memorizing syntax for built-in string methods, built-in methods for maps/sets, sorting methods, and in general any useful built-in data structures. 