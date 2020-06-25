---
title: KMeans Clustering: How it Works, What it Does
subtitle: How KMeans clustering works code-wise and otherwise.
---

## What is KMeans Clustering?

KMeans Clustering is a clustering algorithm, which is to say it takes points of data, and tries to discern groups, or clusters, of those points which fit inside areas of equal size. The reason a clustering algorithm like KMeans would be used in the case of, say, analyzing data, is when graphs such as bar graphs or frequency graphs aren't showing the whole picture. In cases where KMeans might be useful, it may seem at first glance that there are no correlations between two variables when in actuality, there __is__ a pattern, just not a linear one.

### An Example:

Lets say you're given these two graphs:
|  X  |  Y  |
| --- | --- |
| ![X value graph](https://i.imgur.com/3I5bBqi.png) | ![Y value graph](https://i.imgur.com/z6gb7ux.png) |

At first glance, it's not that clear what the data is saying. There's two distinct groups in both the X and Y values; for the X values it almost seems like there's three.

A starter solution would be to plot the points as a scatter plot:
![Scatter Plot](https://i.imgur.com/zmNwC3S.png)

Now the data is a bit more visible, and it's obvious that there are two distinct groups, but we can use a clustering algorithm like KMeans to see what it comes up with for each number of clusters. For the sake of our data, lets say that the answer lies somewhere between 1 and 7, and see what results KMeans gives us for each number of clusters:

![KMeans Cluster Animation](https://raw.githubusercontent.com/Lilchoto3/lilchoto3.github.io/master/img/clusters.gif)

It looks like KMeans starts making stuff up around five clusters, when it splits the left group of the top right cluster in two, and then starts splitting up the bottom left cluster, so it looks like we can definitively say that there are four distinct groups of points.
