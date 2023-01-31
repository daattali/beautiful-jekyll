---
layout: post
title: Benchmarking Dynamic Programming with Python
date: '2022-01-09T21:55:00.056+01:00'
author: Morten
tags:
- Programming
- Optimisation
- Python
- source code
- algorithm
- Jupiter Notebook
modified_time: '2022-01-09T22:17:23.608+01:00'
thumbnail: /assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png
blogger_id: tag:blogger.com,1999:blog-6967032375013519080.post-242457983478061363
blogger_orig_url: https://m635j520.blogspot.com/2022/01/benchmarking-dynamic-programming-with.html
cover-img: https://live.staticflickr.com/5121/5378706956_9fa07f7e2b_z.jpg
thumbnail-img: https://live.staticflickr.com/5121/5378706956_9fa07f7e2b_z.jpg
share-img: https://live.staticflickr.com/5121/5378706956_9fa07f7e2b_z.jpg
---

In this post I'll explore and benchmark some simple dynamic programming concepts in Python.

The example I'll use is a classic recursive implementation of the [fibonacci series](https://en.wikipedia.org/wiki/Fibonacci_number). (And for simplicity I'll skip the first element in the series (fib(0)=0).)

[![_DSC7544.jpg](https://live.staticflickr.com/5121/5378706956_9fa07f7e2b_z.jpg)](https://www.flickr.com/photos/mortenjohs/5378706956/ "_DSC7544.jpg")

## Naive approach

This implementation:

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png)

...works well (enough) for small numbers:

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.47.55.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.47.55.png)

but becomes impossibly slow quickly...

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.48.35.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.48.35.png)

...since it has a time complexity of O(2n). (So our seemingly harmless fib(42) would result in more than 4 trillion calls to fib... (Or about 4 times the number of bacteria on the human body... Or 2 times the number of galaxies in the observable universe... Or more than the estimated population of fish in the ocean... Etc.))

## Enter dynamic programming

Since the result of these recursive calls to fib are all deterministic, we can cache the results instead of recalculating them.

### @functools.cache

First a test by simply leveraging the cache in the library [functools](https://docs.python.org/3/library/functools.html)...

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.38.40.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.38.40.png)

This speeds, as expected, the runtime up significantly...

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B21.23.56.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B21.23.56.png)

...by a factor of about a million in the case of this 43rd fibonacci number.  

(Of course we can't run timeit in loops, as the first run would generate the cache for successive runs...)

### Hand made

Then we can to compare this to the classic, hand made, way to implement memoization in dynamic programming, like so:

[](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)

This _should_ give more or less the same results as above. And it does. 

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.55.37.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B10.55.37.png)

Interestingly, it actually systematically outperforms the functools@cache _slightly_ on my M1 air.

On my intel desktop I get similar difference in results results:

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.21.25.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.21.25.png)

[![](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.22.10.png)](/assets/img/posts/benchmarking-dynamic-programming/Screenshot%2B2022-01-09%2Bat%2B11.22.10.png)

Conclusion
----------

Leveraging **@functools.cache** is a great way to implement dynamic programming memoization in Python with little code overhead (but you still _might_ be able to tailor make a faster solution).