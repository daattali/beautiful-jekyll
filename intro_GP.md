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
GPs can also be considered as a generative model, however, one if its advantages is that their predictive distribution has a close form, meaning sampling techniques are not required. 
As it was mentioned above, a GP is the collection of random variables ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x}_i)) that follow a joint distribution. 
The joint Gaussian distribution between ![formula](https://render.githubusercontent.com/render/math?math=\cal{D}), ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}), and ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x_*})) is of the form,

![Figure](assets/img/intro_gp/Equations/GP_Eq_Dist.png)


where ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{K}) is the covariance matrix of the training data *X*, ![formula](https://render.githubusercontent.com/render/math?math=K_*) is the covariance matrix between *X* and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}), and ![formula](https://render.githubusercontent.com/render/math?math=K_{**}) is the covariance with respect to itself. 


The probability distribution over ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x_*})) can be inferred by computing the conditional distribution given the training data, ![formula](https://render.githubusercontent.com/render/math?math=p(f_* | \mathbf{x_*},\cal{D})). 
Conditioning on the training data is the same as selecting the distribution of functions that agree with observed data points ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}).
The mean and covariance matrix of the conditional distribution are,

![Figure](assets/img/intro_gp/Equations/GP_mu_cov.png)

 where ![formula](https://render.githubusercontent.com/render/math?math=\sigma_*) is the predicted variance for ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x}_*). The mean of the conditional distribution can be rewritten as,

![Figure](assets/img/intro_gp/Equations/GP_mu.png)

where ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{d} = K(\mathbf{x}_*,X)^\top K(X,X)^{-1}) and  ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{\alpha} = K(X,X)^{-1}\mathbf{y}). 
The mean of the conditional distribution is a linear combination of the training data, ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}), or a linear combination of the kernel function between the training points and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}). Function ![formula](https://render.githubusercontent.com/render/math?math=d(\cdot,\cdot)) can be understood as a *distance* function.
It is important to state that the accuracy of the prediction with GPs directly depends on the size of the training data *N* and the kernel function ![formula](https://render.githubusercontent.com/render/math?math=k(\cdot,\cdot)). In the following sections, we illustrate the impact that different kernels on GPs' prediction. 

In the GPs' framework, the predicted variance or standard deviation of ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}) represents the uncertainty of the model. 
The uncertainty can be used to sample different regions of the function space to search the location of the minimum or maximum of a particular function.
This is the idea behind a class of ML algorithms known as Bayesian optimiation.

An example of GP regression for,
![Figure](assets/img/intro_gp/Equations/f_x.png).
We use the *exponential squared* kernel  and 7 training points.
In the following section, we describe the most common procedure to train GPs.
![Figure](assets/img/intro_gp/GP_mu.png)


# Training GPs
The goal of any supervised learning algorithm is to infer a function ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)), as accurately as possible, given some example data.
In order to quantify the accuracy of a model we define a *loss* function, ![formula](https://render.githubusercontent.com/render/math?math={\cal L}), for example, the difference between the prediction ![formula](https://render.githubusercontent.com/render/math?math=y_i) and the real value ![formula](https://render.githubusercontent.com/render/math?math=\hat{y_i}) (training points) such as  ![formula](https://render.githubusercontent.com/render/math?math={\cal L} \approx \sum_i^N (y_i - \hat{y}_i)^2) or ![formula](https://render.githubusercontent.com/render/math?math={\cal L} \approx \sum_i^N |y_i - \hat{y}_i|).
The parameters of the model ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{w}) and ![formula](https://render.githubusercontent.com/render/math?math={\cal L}) are interconnected. 
To illustrate this idea let us assume that ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)) is a simple linear regression model, ![formula](https://render.githubusercontent.com/render/math?math=f(\cdot)=a %2B bx). The loss function for such model is, 

![Figure](assets/img/intro_gp/Equations/L2_LR.png)

From the previous equation, we can observe that the value of ![formula](https://render.githubusercontent.com/render/math?math=
{\cal L}) depends on *a* and *b*. 
It can be argued that when ![formula](https://render.githubusercontent.com/render/math?math=
{\cal L}) is large ![formula](https://render.githubusercontent.com/render/math?math=
f(\mathbf{x_i})) not equal to![formula](https://render.githubusercontent.com/render/math?math= \hat{y_i}). On the other hand when ![formula](https://render.githubusercontent.com/render/math?math=
f(\mathbf{x_i}) \approx \hat{y_i}) the value of ![formula](https://render.githubusercontent.com/render/math?math=
{\cal L}) will tend to zero.
Using a loss function to tune the parameters of ![formula](https://render.githubusercontent.com/render/math?math=
f(\cdot)) is known as the *training* stage in ML. 
It must be mentioned that replicating the training data could also mean that  the model ''memorize'' the training data. 
This common problem in ML is known as *overfitting*. 

GPs models can also be trained using a loss function. GP models are non- parametric models, therefore, the dimensionality of the loss function depends on the number of the parameters of the kernel function. Using a loss function to determine the optimal value for the kernel parameters for non-parametric models is computationally expensive and is prone to overfitting. However, it is possible to train GP methods without a loss function. The most common way to train GPs is by finding the kernel parameters (**θ**) that maximize the **marginal likelihood function**,

![Figure](assets/img/intro_gp/Equations/argmax_likelihood.png)

where ![Figure](assets/img/intro_gp/Equations/likelihood.png) is the marginal likelihood for a given model or kernel function Mi. Finding the value of **θ** where ![Figure](assets/img/intro_gp/Equations/likelihood.png) is maximized is known as type II maximum likelihood (ML-II). The marginal likelihood or evidence is defined as,

![Figure](assets/img/intro_gp/Equations/marginal_LLH.png)

In the case of GPs, the marginal likelihood has a closed form. Finding the kernel parameters that maximize the marginal likelihood can be done by maximizing the logarithm of the marginal likelihood w.r.t to **θ**,

![Figure](assets/img/intro_gp/Equations/GP_MLLH.png)

where the first term is known as the data-fit term, the second term reflects the complexity of the model ![Figure](assets/img/intro_gp/Equations/model.png), and the third term is a constant that depends on the number of training points, *N*. The value of ![Figure](assets/img/intro_gp/Equations/log_MLL.png) mainly depends on the data-fit and complexity terms. For instance, for a **θ** that memorizes the training data the value of log|K| is large, while 
![Figure](assets/img/intro_gp/Equations/GP_MLLH_part2.png) will be small. The tradeoff between the data-fit and the complexity term is key for the optimal value of the kernel parameters.


Standard gradient-based optimization algorithm is the most common method to find the optimal value of the kernel parameters. The logarithm of the marginal
likelihood has an analytic form, therefore, it is possible to compute the change of ![Figure](assets/img/intro_gp/Equations/log_MLL.png) as a function of the kernel parameters, ![Figure](assets/img/intro_gp/Equations/grad_log_MLLH.png) . For most cases, the function ![Figure](assets/img/intro_gp/Equations/log_MLL.png) is not a convex function; thus there is a possi- bility that the optimization algorithm gets trapped in one of the local maxima. For GP regression, the value of **θ** does depend on the training data y, and having different training data sets could lead to different values for the kernel parameters.


# Kernel Functions

In the previous sections, we explained how a GP model is trained and also how it can make predictions. We also assumed that GPs need a kernel function in order to construct the covariance matrices ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{K}) and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{K}_{*}). In this section, we introduce various kernels that are used for training GPs and illustrate how prediction with GPs can drastically change depending on which kernel is used. As mentioned previously, the kernel function should describe the similarity between two points. In kernel regression, two points that are similar, under some metric, should have a similar output value ![formula](https://render.githubusercontent.com/render/math?math=y_{i}), predicted by ![formula](https://render.githubusercontent.com/render/math?math=\mu(\mathbf{x}_{i})).

The kernel function  ![formula](https://render.githubusercontent.com/render/math?math=k(\cdot,\cdot)) must be a positive definite function; this restriction comes from the requirement to invert the covariance matrix during training and prediction. The covariance matrix must be a symmetric matrix which forces the kernel function to be symmetric too,  ![formula](https://render.githubusercontent.com/render/math?math=k(\mathbf{x},\mathbf{x}') = k(\mathbf{x}',\mathbf{x})). The Cholesky factorization is the most common algorithm to invert matrices with ![Figure](assets/img/intro_gp/Equations/O_N3.png) complexity where *N* is the number of training points.

All of the kernels that are used in this thesis are *stationary* kernels except for the linear kernel. Any stationary kernel can be rewritten in terms of the **Mahalanobis** distance,

![Figure](assets/img/intro_gp/Equations/Mahalanobis_distance.png)

The Mahalanobis distance reduces to the square of the Euclidian distance when all ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i} = 1).  
Furthermore, when all ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i}) have the same value, the kernel function is an **isotropic kernel**. In the following sections, we list some of the most common kernels that are used in GP models.

## Constant kernel
The constant kernel, arguably the most simple kernel, assumes that the similarity relation between two points is constant,

![Figure](assets/img/intro_gp/Equations/k_constant.png)

The kernel parameter ![formula](https://render.githubusercontent.com/render/math?math=\ell) can be optimized by maximizing the logarithm of the
marginal likelihood. ![formula](https://render.githubusercontent.com/render/math?math=k_{C}(\cdot,\cdot)) is a one-time differentiable function.


## Square exponential kernel
The square exponential (SE) kernel, also known as the radial basis function (**RBF**) kernel, is probably the most used kernel in GP regression. The SE kernel is a stationary kernel since it depends on the difference between two points,

![Figure](assets/img/intro_gp/Equations/k_SE.png)

Each ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i}) defines the characteristic length-scale for each dimension. Depending on the user, the SE kernel can be isotropic, all ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i}) have the same value, or anisotropic, each ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i}) has a different value. As it was mentioned in the previous section, the values of each ![formula](https://render.githubusercontent.com/render/math?math=\ell_{i}) are optimized by maximizing the logarithm of the marginal likelihood. The training of an isotropic SE kernel is faster since the total number of parameters in the kernel is one, while anisotropic SE kernels have *d* parameters, *d* is the dimension of **x**. The SE kernel is infinitely differentiable.

![Figure](assets/img/intro_gp/GP_k_SE.png)


## Matern kernel
The Matern  (MAT) kernels are probably the second most used kernel for GPs,

![Figure](assets/img/intro_gp/Equations/k_Mat_5-2.png)

![Figure](assets/img/intro_gp/GP_k_mat_5-2.png)



