---
title: KMeans Clustering: How it Works, What it Does
subtitle: How KMeans clustering works code-wise and otherwise.
---

## What is KMeans Clustering?

![Example of KMeans](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/KMeans-Gaussian-data.svg/952px-KMeans-Gaussian-data.svg.png)

KMeans Clustering is a clustering algorithm, which is to say it takes points of data, and tries to discern groups, or clusters, of those points based on their distance from k number of centroids. These centroids are originally chosen as random points within the scope of the data, then slowly altered by finding the mean of the nearest points to each centroid. Once the groups of points linked to each centroid stops moving, the model has "converged" meaning that further iteration wouldn't change anything.

### An Example, the UCI Iris dataset:

Lets say you're given these two graphs and told to find how many classes are in the data based on them:
|  Petal Width  |  Petal Length  |
| --- | --- |
| ![X value graph](https://i.imgur.com/hjkztR5.png) | ![Y value graph](https://i.imgur.com/7iu1dmV.png) |

At first glance, it's not that clear what the data is saying. It's obvious that there's two distinct groups in both the width and length values, but one portion seems to be a larger, wider blob that's more spread out. Let's try adding these two dimensions together.

A starter solution would be to plot the points as a scatter plot:
![Scatter Plot](https://i.imgur.com/s9lp9B4.png)

Now the data is a bit more visible, and it's obvious that there are two distinct groups. While we're still not displaying all dimensions of the data (the Iris dataset has four variables to work with), we can still use a clustering algorithm like KMeans to cluster the data using all four dimensions. Also, while it is already known from the data set that there are three classes in the data, lets say for the sake of experimentation that we don't know and want to use KMeans to find out.

![KMeans Cluster Animation](https://raw.githubusercontent.com/Lilchoto3/lilchoto3.github.io/master/img/clusters.gif)

It looks like KMeans starts making stuff up around four clusters, and really starts falling apart at five clusters, when the bottom left group gets shattered into a bunch of colors. It should also be noted that my graphs are not as uniform as the example graph at the top of the page. This is primarily due to the fact that I'm using all four variables of the Iris dataset, but only displaying two; I'm essentially taking a 2D slice of a 4D graph.

## How it works

![Example clustering iteration animation](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ea/K-means_convergence.gif/440px-K-means_convergence.gif)


