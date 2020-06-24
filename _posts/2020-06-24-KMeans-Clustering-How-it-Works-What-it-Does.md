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
