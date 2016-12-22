---
layout: post
title: Principal Component Analysis
date:   2016-12-22 16:47:14 +0530
categories: machine_learning
tags: [machine_learning]
bigimg: /img/pca.png
---
## Principal Component Analysis

This article is divided into two sections, the first section deals with the pictorial explanation of Principal Component Analysis (PCA) and the second section deals with mathematical explanation of PCA.  


### Pictorial Representation

#### 1. **What is Principal Component Analysis?**  

The simplest answer would be that it is an analysis of finding the principal components in the given data set.  
 
It is often useful to measure the data in terms of it’s principal components instead of the normal 2 dimensional plane of x-y axis. The principal components are the underlying structure in the data. They represent the directions in which the data has maximum variance and also the directions in which the data is most spread out.  

Let’s consider the the diagram show below to understand the above statements.  

![Data Set](/img/pc1.png)  

Imagine that the green circles are the data points of a data set. In order to find the direction of maximum variance, fit a straight line in the data set where the data is most spread out. A vertical line with the data points projected on to it will look like the diagram show below.

![Data Set](/img/pc2.png)  

It looks like the line doesn’t show the direction of maximum variance in the data set. It is probably not the principal component.  

A better fit would be a horizontal line and the data points projection is show in the diagram below.

![Data Set](/img/pc3.png)  

Oh yeah, this looks much better and the data is way more spread out on this line, it has maximum variance and with more analysis we can conclude that there cannot be any other line that has maximum variance. Thus, we can say that the horizontal line is the principal component for the above data set.  

#### 2. **Eigenvectors and Eigenvalues**  

In any data set, we can deconstruct the data into eigenvectors and eigenvalues. Eigenvectors and values exist in pairs. Every eigenvector has a corresponding eigenvalue.
 
When we consider the example that we previously used, **eigenvector was the direction of the line (vertical or horizontal) drawn to find the maximum variance**. An eigenvalue is just a number, it tells us how much variance exists in the data in a particular direction and in the previous example an **eigenvalue was a number that tells us how the data set is spread out on the line which is an eigenvector**. 

Therefore, an eigenvector with the highest eigenvalue is the **Principal Component**.

It turns out that there were not many eigenvectors or eigenvalues in the previous example. For a fact the number of eigenvectors and eigenvalues that exist equals the number of dimensions of a data set.

Say you are measuring the age and attendance of each student in a classroom. So, the two variables are age and attendance of students. Therefore the data set is 2 dimensional and it has 2 eigenvectors and eigenvalues.

If you were to measure the age, attendance and percentage of each student in a classroom, this leads to a 3 dimensional data set given the 3 variables. Therefore it will have 3 eigenvectors and eigenvalues.

This might sound confusing and might be complicated, let’s make it clear using some diagrams.

![Data Set](/img/pc4.png)

At the moment the data set which is depicted in oval shape on the x-y axis, where x could be the age and y could be the attendance. These are the 2 dimensions that are currently used to measure the data set.

As already discussed there is a principal component or a line that will split the data set for maximum variance as show below.

![Data Set](/img/pc5.png)

From the above diagram, we get one eigenvector and the second eigenvector will be **perpendicular or orthogonal** to the first one. The reason the two eigenvectors are orthogonal to each other is because the eigenvectors should be able to span the whole x-y area.

![Data Set](/img/pc6.png)

The eigenvectors have given us a much more useful axis to frame the data set. We can now re-produce the above data set with the new dimensions.

![Data Set](/img/pc7.png)

Just to make it clear, we didn’t mess with the data set, we just changed the view of angle of the data set with the new x’-y’ axis. These axes are much more intuitive to the shape of the data set. These directions give the most variation and provide us with more information. In case, there was no variation in the data set, then everything would be equal to 1 and it would have been such a boring statistic and the eigenvalue would be zero.


### Mathematical Representation


In this section, let’s consider the mathematics point of view to understand the PCA and learn some basic statistics along the way to achieve our goal of figuring out PCA.


#### 1. **Mean**

Mean is the average value of the entire data. Let’s consider a group of students, in order to find the mean of their age, we will add up the age of every student and divide the sum by the total number of students.

![Mean](/img/mean.PNG)

#### 2. **Variance**

It is the measure of the spread of the date in the data set using the mean. When we consider the group of students example, variance is the sum of the squared difference between the age of each student and the mean age value, then the sum is divided by the number of students.

![Variance](/img/variance.PNG)

Variance can also be represented as the measure of the deviation from the mean for the points in one dimension.

#### 3. **Covariance**

It is a measure of how much each of the dimensions vary from the mean with respect to each other.

The covariance is measured between 2 dimensions to see if there is relationship between the 2 dimensions, e.g., relationship between the height and weight of students.

The covariance of one dimension is variance.

![covariance](/img/covariance.PNG)

A **positive value** of covariance indicates that both the dimensions are **directly proportional** to each other, where if one dimension increases the other dimension increases accordingly.

A **negative value** of covariance indicates that both the dimensions are **indirectly proportional** to each other, where if one dimension increases then other dimension decreases accordingly.

If in case the **covariance is zero**, then the two dimensions are **independent** of each other.

One of the major purpose of covariance is to find the relationship between dimensions in high dimensional data set, usually dimensions greater than 3, where the visualization is tricky.

We can also represent the dimensions of a higher dimensional data set in terms of **covariance matrix**. Let’s consider the example of a 3 dimensional data set, then the covariance matrix can be represented as follows

![covariance](/img/covariance_matrix.PNG)

#### 4. **Transformation Matrices**

Consider the following 2 dimensional matrix multiplied by a vector.

![Matrix Transformations](/img/matrix_transformations.PNG)

Now, assume we take a multiple of (3,2) vector and multiply it with the 2 dimensional matrix.

![Matrix Transformations](/img/matrix_transformations_2.PNG)
![Matrix Transformations](/img/matrix_transformations_3.PNG)

From the above two operations, what did we understand?

* A vector consists of both length and direction. Scaling a vector by a value only changes it’s length and not it’s direction. This is an important observation in the transformation of matrices leading to form **eigenvectors** and **eigenvalues**.

* Irrespective of how much we scale the vector (3,2) by, the solution under the transformation matrix is always a multiple of 4.

#### 5. **Eigenvalue Problem**  

The eigenvalue problem is any problem of the form:

![Matrix Transformations](/img/eigen_problem_2.PNG)

Any value of lambda for which the above equation has a solution is called the **eigenvalue** for **A** and the vector v which corresponds to this value is called the **eigenvector** of **A**.

Going back to our above example:

![Matrix Transformations](/img/eigen_problem_3.PNG)

#### 6. **Noise**

Noise in any data must be low or — no matter the analysis technique — no information about a system can be extracted.

There exists no absolute scale for the noise but rather it is measured relative to the measurement, e.g. recorded ball positions.

A common measure is the *signal-to-noise ration (SNR)*, or a ration of variances.

![Signal to Noise](/img/signal_to_noise.PNG)

A high *SNR (>>1)* indicates high precision data, while a low *SNR* indicates noise contaminated data.

#### 7. **Covariance Matrix**

Assuming zero mean data (subtracting the mean from each data value), consider the indexed vectors *{x1, x2, …., xm}* which are the rows of an m x n matrix **X**.

Each row corresponds to all measurements of a particular measurement type *(xi)*.

Each column of **X** corresponds to a set of measurements from a particular time instant.

We can now define our covariance matrix **Sx**.

![Matrix Transformations](/img/covariance_matrix_2.PNG)

* **Sx** is a square symmetric m x m matrix.
* The **diagonal terms** of **Sx** are the **variance** of particular measurement types.
* The **off-diagonal** terms of **Sx** are the **covariance** between the measurement types.


#### 8. **Solving PCA: Eigen Vectors of Covariance Matrix**


Let’s derive our first algebraic solution to PCA using linear algebra. This solution is based on the property of eigenvector decomposition.

The goal is summarized as follows:

* Find some orthonormal matrix **P** where **Y = PX** such that **Sy** is diagonalized. The rows of **P** are the *principal components* of **X**.
* We begin by rewriting **Sy** in terms of our variable of choice **P**.

![Matrix Transformations](/img/covariance_matrix_3.PNG)

* A is a symmetric matrix and can also be written as below

![Matrix Transformations](/img/covariance_matrix_4.PNG)

* Now comes the trick. *Let’s select the matrix **P** to be a matrix where each row of **P** is an eigenvector*.

![Matrix Transformations](/img/covariance_matrix_5.PNG)

* So, it is evident that the choice of **P** diagonalizes **Sy**. This was the goal for PCA.

Hope you found this article useful and understood Principal Component Analysis. 

In the next article, let’s take a look at the applications point of view of PCA.

*Thank you for reading. Peace!*