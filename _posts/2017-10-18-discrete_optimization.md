---
layout: post
title: Algorithms and discrete optimization
---

Over the years I've struggled with the disconnect between "algorithms" — as a student might see
in a standard algorithms and data structures class — and optimization. Several of the algorithms taught in such courses
are in fact instances of (discrete) optimization: for example, dynamic programming (DP), or Dijkstra's algorithm for finding the shortest path in a graph (related to DP), or greedy algorithms for solving the traveling salesman problem. I like the example of dynamic programming in particular because it can often form a conceptual island in students' minds, without apparent connection to any of their other knowledge (for example, in the famous [CLRS algorithms book](https://en.wikipedia.org/wiki/Introduction_to_Algorithms), DP is listed under the miscellaneous heading "Advanced Design and Analysis Techniques").
In this post I'll do a deep dive into one of our MDS assignments (or "labs" as we call them — but they're really assignments) that attempts to connect these concepts using a single application.
The lab is [available here](https://github.com/UBC-MDS/public/blob/master/courses/512_alg-data-struct/labs/lab4/lab4.ipynb), as part of our [publicly available teaching materials](https://github.com/UBC-MDS/public).

In the lab,
the students apply several approaches to [seam carving](https://en.wikipedia.org/wiki/Seam_carving), which is a clever way of resizing images. Seam carving works by assigning an energy value to each pixel (based on, say, changes in brightness) and then iteratively removing the seam (a connected path across the image) that includes the least total energy. The problem of selecting the best seam is often used as an example application for DP.

The lab is structured around four successively faster approaches to tackling the problem:

1. a brute force approach that recursively tries all possibilities.
2. treating the problem as an integer linear programming (ILP) problem and solving it with [PuLP](https://pythonhosted.org/PuLP/).
3. DP.
4. improving the DP implementation to use code vectorization.

I had two main goals for this lab. First, I wanted students to see that ILP and DP are connected despite them typically showing up in different courses; in fact, they can be used to solve the same problem. Second, I wanted students to see that there are often many ways of tackling the same problem,
and that using the right approach can have huge implications on runtime.

A theme of the lab is that, in order to choose the right algorithm, one has to consider the (admittedly ill-defined) _structure_ of the optimization problem. For example, the problem can be written as minimizing a linear objective with linear constraints, so one can use ILP.
But, looking at the problem another way, choosing pixels in the seam represents just the sort of sequential decision-making that makes a problem amenable to dynamic programming: namely, the recursive solution repeatedly solves the same sub-problem redundantly. Recognizing this more specialized structure allows us to use a more specialized algorithm, thus improving performance. I hope that, after the lab, students view DP as just another tool in their discrete optimization toolbox.

With respect to runtime, one satisfying aspect of this lab is that each approach is _significantly_ faster than the previous: often one or more orders of magnitude faster on our sample problems. These speedups really highlight the benefits of using an appropriate algorithm. (And the differences are large enough that I don't have to worry about the unusual characteristics of one student's laptop messing up the punch line!) When shifting from approach (3) to (4) it's also interesting to see how a different implementation of the same algorithm can be hugely faster in many programming languages; the algorithm is completely unchanged but just rewritten to play nice with Python/Numpy, and results in a big speedup.

For the remainder of the MDS program, continuous optimization plays a much more prominent role than discrete optimization (i.e., in the machine learning and regression courses). But, hopefully this lab
equips MDS students with a bigger picture view of optimization and its applications to data science.
For example, I hope that when encountering decision trees in their first machine learning course, students will
think about the decision tree training process as a discrete optimization problem that is solved approximately.

Finally, for your enjoyment, here's an image that has been (overzealously) resized with seam carving. Needless to say,
the resized image was not generated using the brute force implementation, which would take unimaginably long!

Original image:

![](/img/blog/jack-o-lantern-400x600.jpg)

Resized to 50%:

![](/img/blog/jack-o-lantern-200x300.jpg)

The resized image somehow looks much scarier. Happy Halloween!

---------

[Mike Gelbart](http://www.cs.ubc.ca/~mgelbart/) is a Teaching Fellow in the MDS program and a Lecturer in the Department of Computer Science at UBC.
