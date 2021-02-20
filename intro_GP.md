---
layout: page
title : Gaussian Processes
subtitle: Introduction to Gaussian Processes
---

In the field of machine learning, the branch of supervised learning is focuse on the regression task, ![formula](https://render.githubusercontent.com/render/math?math=f:{\cal R}^{D} \to {\cal R}). 


Machine learning (ML) field is divided into three major areas; supervised, unsupervised, and reinforcement learning (MurphyMLbook,BishopMLbook,RLbook). 
Each of these three fields studies a particular task. In the case of supervised learning, the goal is to find the numerical mapping between an input ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_i}) and an output ![formula](https://render.githubusercontent.com/render/math?math=y_i). The numerical mapping can be viewed as, ![formula](https://render.githubusercontent.com/render/math?math=y_i = f(\mathbf{x_i})). When the output value ![formula](https://render.githubusercontent.com/render/math?math=y_i) is discrete, the problem is known as *classification*. On the other hand, when  ![formula](https://render.githubusercontent.com/render/math?math=y_i) is continuous is known as *interpolation*. This chapter describes one of the most common supervised learning algorithms Guassian process (GP) regression (GPbook). 

# Introduction
As in any other supervised learning algorithm, the goal of GP regression is to infer an unknown function ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) by observing some input, ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{X}), and output data, ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}). 
We denote ![formula](https://render.githubusercontent.com/render/math?math=\cal{D}) as the training dataset that contains both ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{X}) and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}).
 One of the few differences between GP regression and other supervised learning algorithms, like neural networks (NNs), is that GP infer a *distribution over functions* given the training data ![formula](https://render.githubusercontent.com/render/math?math=p(f| \mathbf{X},\mathbf{y})). 
 
GPs are a probabilistic method and assume that each training point is a random variable and they have a joint probability distribution ![formula](https://render.githubusercontent.com/render/math?math=p(f(\mathbf{x}_1), \cdots, f(\mathbf{x}_N))). 
As its name suggests, GP assume that the joint distribution is Gaussian and has a mean ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{\mu}(\mathbf{x})) and covariance ![formula](https://render.githubusercontent.com/render/math?math=K(\mathbf{x},\mathbf{x'})). 
The matrix elements of the covariance are defined as ![formula](https://render.githubusercontent.com/render/math?math=K_{ij} = k(\mathbf{x}_i,\mathbf{x}_j)) where ![formula](https://render.githubusercontent.com/render/math?math=k(\cdot,\cdot)) is a positive defined kernel function. The kernel function plays a key role as it describes the *similarity* relation between two points.
A GP is denoted as,  ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x}) \sim GP \left ( \mu(\mathbf{x}), K(\mathbf{x},\mathbf{x'}) \right)).

In the following sections, we describe the training and prediction of GP regression.


# Prediction with Gaussian Processes
GPs can be considered as a generative model, however, in the framework of GPs the predictive distribution has a close form meaning sampling techniques are not required. 
As it was mentioned above, a \ac{GP} is the collection of random variables $f(\mathbf{x}_i)$ that follow a joint distribution. 
The joint Gaussian distribution between $\cal{D}$, $\mathbf{x_*}$, and $f(\mathbf{x_*})$ is of the form,
![formula](https://render.githubusercontent.com/render/math?math=\begin{pmatrix} f(X)\\f(\mathbf{x_*}) \end{pmatrix} \sim \cal{N} \begin{pmatrix} \begin{pmatrix}\mathbf{\mu}\\  \mathbf{\mu_*}\end{pmatrix}&, \begin{pmatrix}K & K_*\\  K_*^\top & K_{**}\end{pmatrix} \end{pmatrix})








