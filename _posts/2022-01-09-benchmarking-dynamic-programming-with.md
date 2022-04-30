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
thumbnail: https://lh3.googleusercontent.com/-Pb8CSa_-_BA/YdtMvXGnW_I/AAAAAAADz0g/7Tj6i6ttq3Ar6ya17yqMQ4FPim5rlQY4wCNcBGAsYHQ/s72-w640-c-h70/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png
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

[![](https://lh3.googleusercontent.com/-Pb8CSa_-_BA/YdtMvXGnW_I/AAAAAAADz0g/7Tj6i6ttq3Ar6ya17yqMQ4FPim5rlQY4wCNcBGAsYHQ/w640-h70/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png)](https://lh3.googleusercontent.com/-Pb8CSa_-_BA/YdtMvXGnW_I/AAAAAAADz0g/7Tj6i6ttq3Ar6ya17yqMQ4FPim5rlQY4wCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.46.38.png)

...works well (enough) for small numbers:

[![](https://lh3.googleusercontent.com/-M9iwzZWQI88/YdtM1PSVfKI/AAAAAAADz0k/IRAoAqoN66koCsIUq8SvJ0puKOztQ_cOQCNcBGAsYHQ/w640-h48/Screenshot%2B2022-01-09%2Bat%2B10.47.55.png)](https://lh3.googleusercontent.com/-M9iwzZWQI88/YdtM1PSVfKI/AAAAAAADz0k/IRAoAqoN66koCsIUq8SvJ0puKOztQ_cOQCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.47.55.png)

but becomes impossibly slow quickly...

[![](https://lh3.googleusercontent.com/-mdeHWjxl-kw/YdtM8q7EBvI/AAAAAAADz0o/Af7JhdkJv2orT44sjM-YWQuzeT-OODOfQCNcBGAsYHQ/w640-h52/Screenshot%2B2022-01-09%2Bat%2B10.48.35.png)](https://lh3.googleusercontent.com/-mdeHWjxl-kw/YdtM8q7EBvI/AAAAAAADz0o/Af7JhdkJv2orT44sjM-YWQuzeT-OODOfQCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.48.35.png)

...since it has a time complexity of O(2n). (So our seemingly harmless fib(42) would result in more than 4 trillion calls to fib... (Or about 4 times the number of bacteria on the human body... Or 2 times the number of galaxies in the observable universe... Or more than the estimated population of fish in the ocean... Etc.))

## Enter dynamic programming

Since the result of these recursive calls to fib are all deterministic, we can cache the results instead of recalculating them.

### @functools.cache

First a test by simply leveraging the cache in the library [functools](https://docs.python.org/3/library/functools.html)...

[![](https://lh3.googleusercontent.com/-4hlYrIxPUL8/YdtNMXbwOkI/AAAAAAADz04/7SeWFWcKGxMpBSanTpsElGKp8X5O2T2mACNcBGAsYHQ/w640-h106/Screenshot%2B2022-01-09%2Bat%2B11.38.40.png)](https://lh3.googleusercontent.com/-4hlYrIxPUL8/YdtNMXbwOkI/AAAAAAADz04/7SeWFWcKGxMpBSanTpsElGKp8X5O2T2mACNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B11.38.40.png)

This speeds, as expected, the runtime up significantly...

[![](https://lh3.googleusercontent.com/-EZYD6B95m3I/YdtNZZoQXCI/AAAAAAADz08/tdIjJUErBfA6taD13pQHoRULj3uz4DPLACNcBGAsYHQ/w640-h50/Screenshot%2B2022-01-09%2Bat%2B21.23.56.png)](https://lh3.googleusercontent.com/-EZYD6B95m3I/YdtNZZoQXCI/AAAAAAADz08/tdIjJUErBfA6taD13pQHoRULj3uz4DPLACNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B21.23.56.png)

...by a factor of about a million in the case of this 43rd fibonacci number.  

(Of course we can't run timeit in loops, as the first run would generate the cache for successive runs...)

### Hand made

Then we can to compare this to the classic, hand made, way to implement memoization in dynamic programming, like so:

[](https://lh3.googleusercontent.com/-TXJUHmmcjlM/YdtNiWzMtJI/AAAAAAADz1E/tOWj-svimA0Bytf7jGaeUAxL5UuEPuMeQCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)[![](https://lh3.googleusercontent.com/-TXJUHmmcjlM/YdtNiWzMtJI/AAAAAAADz1E/tOWj-svimA0Bytf7jGaeUAxL5UuEPuMeQCNcBGAsYHQ/w640-h102/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)](https://lh3.googleusercontent.com/-TXJUHmmcjlM/YdtNiWzMtJI/AAAAAAADz1E/tOWj-svimA0Bytf7jGaeUAxL5UuEPuMeQCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.54.27.png)

This _should_ give more or less the same results as above. And it does. 

[![](https://lh3.googleusercontent.com/-yaq2tS4jPsQ/YdtNu0fhEzI/AAAAAAADz1M/WITs0wr1xC8oP-cCa_vfKKWCJ6XPuF61ACNcBGAsYHQ/w640-h50/Screenshot%2B2022-01-09%2Bat%2B10.55.37.png)](https://lh3.googleusercontent.com/-yaq2tS4jPsQ/YdtNu0fhEzI/AAAAAAADz1M/WITs0wr1xC8oP-cCa_vfKKWCJ6XPuF61ACNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B10.55.37.png)

Interestingly, it actually systematically outperforms the functools@cache _slightly_ on my M1 air.

On my intel desktop I get similar difference in results results:

[![](https://lh3.googleusercontent.com/-1uqfk_-BQxk/YdtN8xH_YLI/AAAAAAADz1U/-yqbls4450kRK6iNXF9PqDELLKuVok3qwCNcBGAsYHQ/w640-h50/Screenshot%2B2022-01-09%2Bat%2B11.21.25.png)](https://lh3.googleusercontent.com/-1uqfk_-BQxk/YdtN8xH_YLI/AAAAAAADz1U/-yqbls4450kRK6iNXF9PqDELLKuVok3qwCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B11.21.25.png)

[![](https://lh3.googleusercontent.com/-oCnUDGvYjtk/YdtN_kaAvjI/AAAAAAADz1c/aba-uFO9jEg2i0XfG6UoAaewFGWIsS0WwCNcBGAsYHQ/w640-h52/Screenshot%2B2022-01-09%2Bat%2B11.22.10.png)](https://lh3.googleusercontent.com/-oCnUDGvYjtk/YdtN_kaAvjI/AAAAAAADz1c/aba-uFO9jEg2i0XfG6UoAaewFGWIsS0WwCNcBGAsYHQ/Screenshot%2B2022-01-09%2Bat%2B11.22.10.png)

Conclusion
----------

Leveraging **@functools.cache** is a great way to implement dynamic programming memoization in Python with little code overhead (but you still _might_ be able to tailor make a faster solution).