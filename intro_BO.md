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

The optimization of a function is also a supervised learning problem, but instead of finding the best global representation of function $f(\cdot)$, the goal is to find the ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x})  where ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) is minimum,

![Figure](assets/img/intro_bo/Equations/arg_min.png)


In a previous post we introduced [Gaussian Processes](intro_GP.md), a probabilist regression model capable of learning complex functions. 
