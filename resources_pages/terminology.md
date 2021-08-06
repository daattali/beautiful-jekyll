---
layout: page
title: Data science terminology
---

## About this document
This document is intended to help students navigate the large amount of jargon, terminology, and acronyms encountered in the MDS program and beyond. There is also an accompanying [blog post](https://ubc-mds.github.io/2017-12-14-terminology/). Course numbers of the form DSCI XXX refer to relevant [UBC MDS courses](https://ubc-mds.github.io/descriptions/).

## Stat-ML dictionary

This section covers terms that have different meanings in different contexts, specifically statistics vs. machine learning (ML).

#### `regression`
  * in ML, `regression` refers to predicting continuous outputs given input features, and classification refers to predicting categorical outputs given input features.
  * in statistics, both of the above tasks are referred to as `regression`. See also `supervised learning` below.


#### `bias`
  * even within statistics this word has [a lot of meanings](https://en.wikipedia.org/wiki/Bias_(statistics)). See also [bias of an estimator](https://en.wikipedia.org/wiki/Bias_of_an_estimator).
  * in ML, when we have a trasformation of the form Wx+b (especially in linear models or neural networks) we refer to b as the "bias term" or the elements of b as the biases if b is a vector. For example, see [this Stack Overflow post](http://stackoverflow.com/questions/2480650/role-of-bias-in-neural-networks). In statistics we would call this the "intercept".
  * in both fields, we talk about the bias-variance tradeoff; see below.


#### `parameter` and `parametric`
  * in statistics, `parameter` is used to describe probability distributions, like "the gamma distribution has a shape parameter and a scale parameter". Thus, a `parametric model` is a model using a parametric probability distribution.
  * in ML, `parameter` refers to the components (usually numbers) that are getting learned in a system. A `parametric model` has a fixed number of parameters that is independent of the number of training examples, and typically doesn't require the training examples to be stored in order to make predictions. An example would be linear regression, which involves one parameter per feature plus one more intercept parameter. On the other hand, [k-nearest neighbours](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) (KNN) would be an example of a nonparametric model as we don't "distill" the training data into a fixed set of parameters. Another way to think about this is that, with KNN, the complexity of the model grows with the amount of training data.
  * the differences above can cause confusion. For example, a statistician might say a linear [support vector machine](https://en.wikipedia.org/wiki/Support_vector_machine) (SVM) is not a parametric classifier because it is not based on an underlying probabilistic model. And yet, in ML, a linear SVM is parametric because we're learning one parameter per dimension (in the primal formulation) to represent a linear boundary, and thus the number of parameters is fixed.

#### `early stopping`
  * in ML, this refers to terminating an optimization routine before reaching convergence, which may mitigate overfitting (see [here](https://en.wikipedia.org/wiki/Early_stopping)).
  * in statistics, this sometimes refers to stopping an experiment early, particularly as in early stopping of clinical trials.

#### `hypothesis`
  * in statistics, this word evokes [hypothesis testing](https://en.wikipedia.org/wiki/Statistical_hypothesis_testing).
  * in ML, `hypothesis` is sometimes used to refer to a particular model or decision boundary from the hypothesis space. E.g., we select a linear decision boundary from the hypothesis space of all possible hyperplanes; more complicated models have a larger hypothesis space.

#### `factor`
  * in statistics, `factor` means categorical variable; factorial experiment means trying all possible combinations of two or more factors.
  * spanning both statistics and ML, we have [factor analysis](https://en.wikipedia.org/wiki/Factor_analysis) and [factor graphs](https://en.wikipedia.org/wiki/Factor_graph), which do not use `factor` in the sense described above (or in the same way as each other, even...).
  * (and in math, factor means one of several things being multiplied together.)

#### `kernel`

This is not a Stat vs. ML problem, but more of a Stat/ML vs. CS vs. math problem. For even more definitions, see the [Wikipedia disambiguation page](https://en.wikipedia.org/wiki/Kernel). Overall, this word ranks up there with `bias` as a hopelessly overloaded and confusing word.

  * in statistics and ML, `kernel methods` refer to applications of the kernel trick, which is a computational speedup in cases where only the dot products of features are needed to make predictions. A common use case is kernel SVMs but they can be used in many other places.
  * in density estimation and visualization, `kernel density estimation` involves placing a kernel-shaped "bump" in place of each point. This is related to kernel methods mentioned above, and in particular kernel regression.
  * in computer science, the word `kernel` appears in the field of operating systems. 
  * as data scientists, we also see it in Jupyter notebooks: the "Python kernel", etc. This is probably related to the CS meaning above?
  * in linear algebra, `kernel` is another name for nullspace. 
  
#### `sample`

  * in statistics, it is standard to say "a sample of size N" when referring to data coming from a probability distribution.
  * in machine learning, it is standard to say "N samples" to mean the same thing. E.g., "I will draw N samples from the exponential distribution".

## Common acronyms
 * `FDR`: False Discovery Rate
 * `MC`: Monte Carlo
 * `MCMC`: Markov chain Monte Carlo
 * `OOP`: object-oriented programming
 * `IID`: independent and identically distributed
 * `RV`: random variable
 * `CDF`: cumulative distribution function
 * `ROC`: receiver operating characteristic (curve) -- sort of like precision/recall
 * `MAP`: maximum a posteriori (DSCI 553), not to be confused with `map` of MapReduce (DSCI 513/525).
 * `NLP`: natural language processing
 * `PCA`: principal components analysis
 * `EM` : expectation maximization algorithm

### Acronyms that have more than one meaning
* `S3`: is an OOP paradigm in R (DSCI 524), and a storage service offered by Amazon (DSCI 525)
* `ML`: Maximum Likelihood, Machine Learning
* `CI`: Confidence Interval (DSCI 552), Continuous Integration (DSCI 524)
* `IP`: Internet Protocol (as in IP address, DSCI 525), and Intellectual Property (as in software licenses, DSCI 524)
* `MDS`: Master of Data Science, or Multi-Dimensional Scaling (DSCI 563).
* `PDF`: Probability Density Function, or the file format, Portable Document Format. And at UBC it even has a third meaning: Post-Doctoral Fellow. So, at UBC, a PDF could save a plot of a PDF as a PDF!

## Compare and contrast

#### `underfitting` vs. `overfitting` 
  * `underfitting` refers to a model that is too simple to perform well even on the training data. 
  * `overfitting` refers to a model that is too specific to the particular training set, potentially because the model is too complex. 


#### `bias-variance tradeoff` vs `fundamental tradeoff of ML`
  * The `bias-variance tradeoff` refers to the tradeoff between the bias and the variance of an estimator (see above for more on the term `bias`)
  * The `fundamental tradeoff of ML` refers to the tradeoff between training error and approximation error. 
  * Bias-variance refers to a specific model more in the abstract, whereas training/approximation error refer to a specific model trained on a specific training set.
  * High bias is roughly the same idea as high training error (underfitting). It means that the model assumptions prevent us from achieving low training error.
  * High variance is roughly the same idea as high approximation error (overfitting). It means that model would change significantly if given different training data from the same distribution.


#### `parameter` vs. `hyperparameter`
  * following up on the ML definition of a `parameter` (see above), we also contrast this with a `hyperparameter`, which are high-level decisions that one chooses before training the model. For example, "k" in k-nearest neighbours classification is a hyperparameter. Unlike parameters, hyperparameters are most often chosen by humans (although hyperparameter tuning is becoming automated to some extent as well).

#### `discriminative` vs. `generative`
A [discriminative model](https://en.wikipedia.org/wiki/Discriminative_model) directly models the probability of a given output given the inputs. On the other hand, with a [generative model](https://en.wikipedia.org/wiki/Generative_model) one starts from assumptions about how the data are generated (the "forward model"), and then performs inference about the model given the data (the "backward" step). The term `generative model` itself has some ambiguity: in some contexts it includes the prior distribution (see below) and in other contexts it does not.

#### `Bayesian` vs. `frequentist`
This represents a divide in the field of statistics and is related to, but not the same as, `discriminative` vs. `generative` above.
The [Bayesian approach](https://en.wikipedia.org/wiki/Bayesian_inference) involves generative models and following [Bayes' Theorem](https://en.wikipedia.org/wiki/Bayes%27_theorem). In this paradigm, one uses a generative model and attempts to compute a posterior distribution of the quantities of interest. See DSCI 553. The [frequentist approach](https://en.wikipedia.org/wiki/Frequentist_inference) relates to hypothesis testing and does not involve prior distributions (which is both good and bad!). See DSCI 552.

#### `supervised` vs. `unsupervised` learning
In [supervised learning](https://en.wikipedia.org/wiki/Supervised_learning) you are given a set of input-output pairs and you try to model the relationship between them so that, given a new input, you can predict its output. In [unsupervised learning](https://en.wikipedia.org/wiki/Unsupervised_learning) there are no outputs. Your job is then to find some structure or pattern in the data. Sometimes it's helpful to think of unsupervised learning as supervised learning except that you don't know which features are the inputs and which are the output(s).

See also [pattern recognition](https://en.wikipedia.org/wiki/Pattern_recognition) and [semi-supervised learning](https://en.wikipedia.org/wiki/Semi-supervised_learning).

#### `learning` vs. `inference`
One (probably flawed) definition of `learning` is updating your parameters given your data. The term `inference` is perhaps slightly more specific, as it typically refers to inferring parameters of a model, either Bayesian or frequentist (see above). Here's some [more thoughts on this](https://www.quora.com/What-is-the-difference-between-inference-and-learning).

#### `validation set` vs. `test set`
There doesn't seem to be a super strong concensus on what these terms mean. Most would agree that `training set` is the data set that you train a model / learning algorithm on. A reasonable definition of `validation set` is that it's a subset of your training data that you hold out to "validate" your model, i.e. assess how well it performs on unseen (during training) data. Sometimes `test set` is used as a synonym of `validation set`; or sometimes it's a second validation set that is only used once, after hyperparameter optimization is performed on the validation set; or sometimes it's used to mean the feature values on which we'll have to make predictions "in production", in which case we'll see the input values but never the true output values of the test set.


#### `mean` vs. `expected value`

These are the same thing when referring to a random variable. However, `mean` is sometimes used to refer to the sample mean. Therefore you can have the (sample) mean of the data you collected, but not the expected value. You can also discuss the mean of a bunch of numbers, like the mean (or average) of 1,2,3,4,5; but you wouldn't say the expected value of these numbers.

#### `dimension` vs. `size` vs. `length` (of a vector)

The term `dimension` is unfortunately overloaded when it comes to vectors. From a math standpoint, we're referring to the dimensionality of the space that the vector lives in, which is going to be number of elements in the vector. For example the vector `x = [1,2,3]` is a vector in 3-dimensional space because there are 3 coordinates. So we could say its dimension is 3. However, from a programming point of view, we would call `x` a 1-D array. In contrast, a "2-D array" is a rectangular structure with elements like `x[2,3]`; in other words, what we call a matrix in math. In Python/numpy, the programming dimensionality can be evaluating with `x.ndim`, and the math dimensionality with `x.shape` (or `x.size` or `len(x)`).

The term `length` has its own problems too. In programming, the length of a vector is the number of elements; I also called this the `size` or the math-dimensionality above. However, in math the length may refer to the L2-norm of a vector; that is, the square root of the sum of the squares of its elements, computed using `numpy.linalg.norm(x)`. 

In general, we have to be careful with these terms. If you say "x is 3-dimensional", are you referring to `len(x)` or `x.ndim`?


## Definitions

### Error types
* `Type I error`: false positive, meaning it was actually negative but you said positive
* `Type II error`: false negative, meaning it was actually positive but you said negative
* `sensitivity` aka `recall`: true positive rate. in math: 1 - (# of type II errors)/(# of true positives)
* `specificity`: true negative rate. in math: 1 - (# of type I errors)/(# of true negatives)
* `precision` aka `positive predictive value`: 1 - (# of type I errors)/(# reported positives)

[[relevant image](https://cloud.githubusercontent.com/assets/6865016/16235952/720f2a36-378b-11e6-9355-449be54f0729.png)]

Note: [`power`](https://en.wikipedia.org/wiki/Statistical_power) and `sensitivity` are highly related. But we tend to think of power as a conditional probability (a property of a statistical test) whereas we tend to think of sensitivity/recall as counts (a property of the predictions).

#### `lasso` and `ridge` regression
`Lasso regression` means regression using L1 regularization.

`Ridge regression` means regression using L2 regularization.

#### `shrinkage`
This can be thought of in terms of regularization. As an example, using L2 regularization in regression "shrinks" the coefficients. But it's best not to interpret "shrink" as "make smaller in magnitude". In Bayesian terms, a regularizer is viewed as a prior distribution. You could have a prior that believes the weights are near some non-zero value, and thus the prior "shrinks your beliefs to that value". Thus, `shrinkage` can be thought of as shrinking your uncertainty in the model parameters rather than literally making the weights smaller, although both become true when you are shrinking towards zero (which is almost always the case with regularization).


## Equivalence classes

In each equivalence class below, the terms tend to be used interchangeably (even if this isn't a good idea!).

* regression coefficients = weights = parameters
* residual variance = noise variance
* inputs = predictors = features = explanatory variables = regressors = independent variables = covariates = attributes = exogenous variables
* outputs = outcomes = targets = response variables = dependent variables = endogenous variables. Also called a label if it's categorical.
* Gaussian distribution = Normal distribution = bell curve
* sensitivity = recall (see Error types above)
* training =  learning = fitting (sort of; depending on context)
* ordinary least squares (OLS) = linear least squares = least squares
* softmax classification = softmax regression = multinomial logit regression
* kriging = Gaussian process regression
* Bayesian network = Bayes net = directed graphical model = DAG graphical model
* Markov random field = Markov network = undirected graphical model
* one-hot encoding = one-of-k encoding = dummy variables (sort of)

## Misc
This is not really a terminology issue, but note a connection between `collaborative filtering` in recommender systems (ML) and `data imputation` (statistics). Both are about estimating missing values. But imputation is more of a means to an end whereas in collaborative filtering finding those values is often the end itself.
