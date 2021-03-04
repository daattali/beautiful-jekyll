---
layout: page
title : Bayesian Optimization
subtitle: Introduction to Bayesian Optimization
---


The optimization of machine learning algorithms is one of the most important research. 
Here we present a breif introduction of **Bayesian Optimization** (BO), a novel search algorithm that can minimize black-box functions.

# Introduction
The goal of an *optimization problem* is to find the best solution among all potential solutions. 
In the field of ML, the optimization problem is associated with the search for the values of the parameters of a model that better described the problem, e.g. minimizing a loss function. 
Synthetic chemistry also has optimization problems, for example varying the reaction conditions to increase percent yield.

The optimization of a function is also a supervised learning problem, but instead of finding the best global representation of function ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)), the goal is to find the ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x})  where ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) is minimum,

![Figure](assets/img/intro_bo/Equations/arg_min.png)

The most common optimization algorithm for continuous functions is *gradient descent* (GD). GD algorithm is designed to minimize a function iteratively by displacing the current point in the direction of the negative gradient of the function,

![Figure](assets/img/intro_bo/Equations/gradient_descent.png)

where the parameter ![formula](https://render.githubusercontent.com/render/math?math=\eta) is known as the *learning rate*.
![formula](https://render.githubusercontent.com/render/math?math=\eta) is also related in the trade-off between exploitation and exploration and plays a key role in the convergence of the algorithm.   
For example, when ![formula](https://render.githubusercontent.com/render/math?math=\eta) is small GD is exploiting ![Figure](assets/img/intro_bo/Equations/x_n+1_x_n.png); where as  ![Figure](assets/img/intro_bo/Equations/eta_gg_0.png)  is related to exploration. 
GD is one of the first optimization algorithms used to train NNs, backpropagation algorithm. 

GD has been a widely successful optimization algorithm.
However, not every function can be optimized using GD.
For example, there is no analytic function that describes the relation between the percent yield given some experimental conditions for a chemical reaction, therefore one can not use GD to increase the percent yield.
There are many other problems that are described by non-analytic functions or *black-box* functions, where evaluations are point-wise.
BO is designed to tackle the optimization of black-box functions where gradients are not available.  
For obvious reasons, trying to find the minimum of ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) by randomly sampling is not the smartest strategy, since it may take a large number of evaluations from ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) before finding the minimum.
BO tries to infer the location of the minimum of a black-box function by proposing a smarter iterative sampling scheme. 
In the case of GD we assume that the gradient gives us the information of where to sample the next point in order to get closer to the minimum. 
Considering that black-box functions do not have a gradient, it is necessary to propose a metric that quantifies the informational gain as a function of the space.

The core of BO relays in two components,
1. ![formula](https://render.githubusercontent.com/render/math?math={\cal F}(\cdot)) --> **model** that mimics the black-box function.
2. ![formula](https://render.githubusercontent.com/render/math?math=\alpha(\cdot))  --> **acquisition function** that quantifies the information gain for a given
point.


In a previous post we introduced [Gaussian Processes](intro_GP.md), a probabilist regression model capable of learning complex functions. 
