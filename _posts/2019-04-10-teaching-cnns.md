---
layout: post
title: Teaching CNNs
subtitle: Unpacking convolutional neural networks
---

When I first learned about convolutional neural networks (CNNs, or convnets), I was shown a picture much like the one below, which is from the [AlexNet paper](https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf):

![](https://cdn-images-1.medium.com/max/1600/1*qyc21qM0oxWEuRaj-XJKcw.png)

From what I have seen, this type of diagram is fairly standard in both CNN papers **and** CNN teaching, even though the audiences are very different in those two situations. In this post, I will describe my approach for teaching CNNs here at UBC. The lecture itself, in which I implemented my approach, can be found [here](https://github.com/UBC-MDS/DSCI_572_sup-learn-2_public/blob/master/lectures/lecture7.ipynb).

I have two main beliefs about teaching CNNs: teaching 1D convnets first, and using a different type of diagram. The post will address each of these notions, followed by some smaller comments.

### Starting with 1D convnets

As far as I can tell, 2D convnets are probably the most popular type. By "2D" I mean that each **feature** is a 2D signal, i.e., an image. Perhaps because of their popularity, 2D convnets are often at the forefront of lessons on CNNs. Indeed, the figure above represents a 2D convnet. However, I find that 1D convnets are much easier to teach and understand, because the convolutional-ness is more clearly isolated and differentiated from the features. Therefore, I start by teaching 1D convnets fully before moving on to the 2D case. The fact that there's is still plenty more to say about the 2D case supports teaching 1D first; they are similar but 2D is sufficiently more confusing that I can spend another 20 min explaining how they differ.

### Circle/arrow diagrams

Main ideas:

- Teach 1D first
- Do not use the old figure type
- Use the circle/arrow figures
- Change multiplication ("0D convolution") to convolution

Smaller ideas:

- Differentiate between ordered and unordered dimensions (could show quiz question?!)
- Set padding so that the size stays the same



--------

[Mike Gelbart](https://www.mikegelbart.com/) is Option Co-Director of the MDS Vancouver program and an Instructor in the UBC Department of Computer Science.
