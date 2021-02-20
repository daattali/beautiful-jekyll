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
As it was mentioned above, a GP is the collection of random variables ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x}_i)) that follow a joint distribution. 
The joint Gaussian distribution between ![formula](https://render.githubusercontent.com/render/math?math=\cal{D}), ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}), and ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x_*})) is of the form,

<img src="http://www.sciweavers.org/tex2img.php?eq=%5Cbegin%7Bpmatrix%7D%20f%28X%29%5C%5Cf%28%5Cmathbf%7Bx_%2A%7D%29%20%5Cend%7Bpmatrix%7D%20%5Csim%20%5Ccal%7BN%7D%20%5Cbegin%7Bpmatrix%7D%20%5Cbegin%7Bpmatrix%7D%5Cmathbf%7B%5Cmu%7D%5C%5C%20%20%5Cmathbf%7B%5Cmu_%2A%7D%5Cend%7Bpmatrix%7D%26%2C%20%5Cbegin%7Bpmatrix%7DK%20%26%20K_%2A%5C%5C%20%20K_%2A%5E%5Ctop%20%26%20K_%7B%2A%2A%7D%5Cend%7Bpmatrix%7D%20%5Cend%7Bpmatrix%7D%0A&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\begin{pmatrix} f(X)\\f(\mathbf{x_*}) \end{pmatrix} \sim \cal{N} \begin{pmatrix} \begin{pmatrix}\mathbf{\mu}\\  \mathbf{\mu_*}\end{pmatrix}&, \begin{pmatrix}K & K_*\\  K_*^\top & K_{**}\end{pmatrix} \end{pmatrix}" width="285" height="46" />

where ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{K}) is the covariance matrix of the training data *X*, ![formula](https://render.githubusercontent.com/render/math?math=K_*) is the covariance matrix between *X* and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}), and ![formula](https://render.githubusercontent.com/render/math?math=K_{**}) is the covariance with respect to itself. 


The probability distribution over ![formula](https://render.githubusercontent.com/render/math?math=f(\mathbf{x_*})) can be inferred by computing the conditional distribution given the training data, ![formula](https://render.githubusercontent.com/render/math?math=p(f_* | \mathbf{x_*},\cal{D})). 
Conditioning on the training data is the same as selecting the distribution of functions that agree with observed data points ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}).
The mean and covariance matrix of the conditional distribution are,

<img src="http://www.sciweavers.org/tex2img.php?eq=%0A%5Cmathbf%7B%5Cmu%7D%28%5Cmathbf%7Bx%7D_%2A%29%20%26%3D%26%20K%28%5Cmathbf%7Bx%7D_%2A%2CX%29%5E%5Ctop%20K%28X%2CX%29%5E%7B-1%7D%5Cmathbf%7By%7D%20%5C%5C%0A%5Csigma_%2A%20%26%3D%26%20K%28%5Cmathbf%7Bx%7D_%2A%2C%5Cmathbf%7Bx%7D_%2A%29-%20K%28%5Cmathbf%7Bx%7D_%2A%2CX%29%5E%5Ctop%20K%28X%2CX%29%5E%7B-1%7DK%28X%2C%5Cmathbf%7Bx%7D_%2A%29%20%0A&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\mathbf{\mu}(\mathbf{x}_*) &=& K(\mathbf{x}_*,X)^\top K(X,X)^{-1}\mathbf{y} \\\sigma_* &=& K(\mathbf{x}_*,\mathbf{x}_*)- K(\mathbf{x}_*,X)^\top K(X,X)^{-1}K(X,\mathbf{x}_*) " width="375" height="44" />

 where ![formula](https://render.githubusercontent.com/render/math?math=\sigma_*) is the predicted variance for ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x}_*). The mean of the conditional distribution can be rewritten as,

<img src="http://www.sciweavers.org/tex2img.php?eq=%5Cmathbf%7B%5Cmu%7D%28%5Cmathbf%7Bx%7D%2A%29%20%20%26%3D%26%20%5Csum_i%20d%28%5Cmathbf%7Bx%7D_%2A%2C%20%5Cmathbf%7Bx%7D_i%29y_i%20%20%3D%20%5Csum_i%20%5Calpha_i%20k%28%5Cmathbf%7Bx%7D_%2A%2C%5Cmathbf%7Bx%7D_i%29%0A&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\mathbf{\mu}(\mathbf{x}*)  &=& \sum_i d(\mathbf{x}_*, \mathbf{x}_i)y_i  = \sum_i \alpha_i k(\mathbf{x}_*,\mathbf{x}_i)" width="340" height="42" />

where ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{d} = K(\mathbf{x}_*,X)^\top K(X,X)^{-1}) and  ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{\alpha} = K(X,X)^{-1}\mathbf{y}). 
The mean of the conditional distribution is a linear combination of the training data, ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{y}), or a linear combination of the kernel function between the training points and ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}). Function ![formula](https://render.githubusercontent.com/render/math?math=d(\cdot,\cdot)) can be understood as a *distance* function.
It is important to state that the accuracy of the prediction with GPs directly depends on the size of the training data *N* and the kernel function ![formula](https://render.githubusercontent.com/render/math?math=k(\cdot,\cdot)). In the following sections, we illustrate the impact that different kernels on GPs' prediction. 

In the GPs' framework, the predicted variance or standard deviation of ![formula](https://render.githubusercontent.com/render/math?math=\mathbf{x_*}) represents the uncertainty of the model. 
The uncertainty can be used to sample different regions of the function space to search the location of the minimum or maximum of a particular function.
This is the idea behind a class of ML algorithms known as Bayesian optimiation.

An example of GP regression for ![formula](https://render.githubusercontent.com/render/math?math=f(x) = \frac{x}{10} + x^2 + 10\sin(\frac{3}{2}x)). We use the *exponential squared* kernel  and 7 training points.
In the following section, we describe the most common procedure to train GPs.

<object data="assets/img/GP_mu.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="assets/img/GP_mu.pdf">
        <p>This browser does not support PDFs. Please download the PDF to view it: <a href="http://yoursite.com/the.pdf">Download PDF</a>.</p>
    </embed>
</object>



