---
layout: post
title: How To Use Numerical Data with ConvNets
subtitle: Guide on How to Use Additional Numeric Data with Images for Training a Convolutional Neural Network
gh-repo: ghosh-r/ghosh-r.github.io
gh-badge: [star, follow]
tags: [deep-learning, neural-networks, computer-vision, nn-architectures, cnn]
comments: true
cover-img: /assets/img/2020-12-16-numerical-data-additional-input-1-0.jpg
---

#### Introduction

This problem appeared to me as a question in a Kaggle Community forum. Someone wants to use location data along with pictures of houses to predict house price. This is my take on how to do that, and additional thoughts.

#### Dealing with the Images

I am assuming that you are trying to predict the prices of the houses where the pictures of the houses are among the inputs.

This can be accomplished by putting the prices as targets \\(y\\). And then have the NN predict the price for previously unseen house pictures as \\(\hat{y}\\).

How I would approach this problem-

* Form a dataset that has the prices as labels \\(y\\) and the images as inputs.
* Split the dataset in train-valid-test splits (remember to shuffle it)
* Create and train the NN to output a single number \\(\hat{y}\\) which will be the price (remember that the output layer has to have a single output node that outputs a raw number, preferably a float, to predict the price).

Up to this point, it is quite a simple problem. Note that I am not taking into account the location information at all. So this model will be unusable in the real world. A mansion in rural Texas will definitely cost a lot less than a 2 bedroom house in counties near San Fransisco. You get the idea. So, we will have to take the location into account. Even after that, it will not be very useful, either. Will come to that later.

#### Using the Location Information

It was very simple till now. This is the part where it becomes tricky. How to integrate the additional location information into the input of the NN? There are two approaches to this.

##### Adding an Additional Layer

The images will come in three-layer RGB format, the trick is to add an additional fourth layer that contains the location information.

This is essentially what you do-
![](/assets/img/2020-12-16-numerical-data-additional-input-1.png)
[Embedding the location information into an additional layer | Source: Author]

* Pro: The whole ConvNet gets to see the location data and learns well.
* Con: ConvNets are not good at dealing with such information, so this approach might not be very effective.

##### Concatenating Informations after Feature Extraction by ConvNets, and before the FC Layers

In architectures like ResNet50, there are several fully connected (FC) layers trailing the convolutional layers. The goal is to put tabular data into those FC layers and let those last FC layers learn from the location information.

The architecture will look similar to this-
![](/assets/img/2020-12-16-numerical-data-additional-input-2.png)
[ Concatenating Informations after Feature Extraction by ConvNets, and before the FC Layers | Source: [Comparison of Deep Learning Approaches for Multi-Label Chest X-Ray Classification](https://www.nature.com/articles/s41598-019-42294-8)]

* Pro: Inputting numerical data directly to the FC layers which are comparatively much better than ConvNets in dealing with raw numbers.
* Con: The ConvNet is not being utilized in this approach. (Maybe even mess with the extracted features, I am not sure.)

See more on comparisons of these two approaches [in Data Science Stack Exchange](https://datascience.stackexchange.com/questions/68450/how-can-you-include-information-not-present-in-an-image-for-neural-networks).

#### Concluding Thoughts

Even after this, the model will have none to severely limited capabilities in the real world. Because all pictures of houses will not be captured by professionals, and pictures of houses taken from different angles will be perceived very differently by the ConvNet. Additionally, a very large dataset will have to be present for any possible real-world application.

*[[Original comment on Kaggle](https://www.kaggle.com/discussion/203341#1115340)]*
