---
layout: post
title: Implementing a Binary Classifier in Python
date:   2017-01-21 16:47:14 +0530
categories: machine_learning
tags: [machine_learning]
bigimg: /img/neuron_model.jpg
---

## Implementing a Binary Classifier in Python

Machine Learning (ML) is playing a key role in a wide range of critical applications, such as Computer Vision, Data Mining, Natural Language Processing, Speech Recognition and others. ML provides potential solutions in all of the above mentioned domains and more, it's surely going to be the the driving force of our future digital civilization. 

ML can be a bit intimidating for a newcomer. The concept of ML might be quite abstract and the newcomer might be bombarding himself with multiple questions. One big question being, "How does it work?".

In order to explain this, I decided to write a Binary Classifier from scratch. I will not be making use of *Scikit-learn* in this post. The imperative of this post is to understand the core working principle of an ML algorithm.

### What is a Binary Classifier?

Let's consider a scenario where you are told to seperate a basket full of Apples and Oranges into two seperate baskets.

![Apples and Oranges](/img/apples-and-oranges.png) 

**So, what do you do?**  
-   You might look at the color
-   You might look at the shape or the dimensions
-   You might feel the difference in the texture
-   You might feel the difference in the weights  

Afer you find the difference between the two, then you'll seperate them.

Now, let's explain the Binary Classifier from the above scenario.

1. Firstly, you get the data to solve your problem. (Basket full of Apples and Oranges)
2. Secondly, you create a feature set, which uniquely defines each data. (Your assumptions like color, size, weights and etc.)
3. Thirdly, you are able to label or categorize each data. (Apple or Orange)
4. Fourthly, you have learnt to differentiate the data during the entire process. (In future, you'll be able to differentiate between an Apple and a Orange)

A **Classifier** in Machine Learning is an *algorithm*, that will determine the class to which the input data belongs to based on a set of features.

There are three types of problems in Machine Learning:  
1. *Supervised Learning*
2. *Unsupervised Learning*
3. *Reinforcement Learning*

A Binary Classifier is an instance of Supervised Learning. In Supervised Learning we have a set of input data and a set of labels, our task is to map each data with a label. A Binary Classifier classifies elements into two groups, either **Zero** or **One**.

### Machine Learning Model

Machine Learning model comprises of four steps:  
1. *Data Preprocessing*
2. *Learning*
3. *Evaluation*
4. *Prediction*

#### Data Preprocessing

As Machine Learning algorithms learn from the data, we are obliged to feed them the right kind of data. So, the step towards achieving that is via *Data Preprocessing*.

Data Preprocessing is a data mining technique that involves transforming the raw data into an understandable format. Real-world data is often incomplete, noisy, inconsistent or unreliable and above all it might be unstructured.

In simple terms, Data Preprocessing implies grooming the raw data according to your requirement using certain techniques.

Steps involved in Data Preprocessing:  
1. *Data Cleaning* - Fill in the missing values, detect and remove noisy data and outliers.
2. *Data Transformation* - Normalize data to reduce dimensions and noise.
3. *Data Reduction* - Sample data records or attributes for easier data handling.
4. *Data Discretization* - Convert continuous attributes to categorical attributes for ease of use with certain machine learning methods.
5. *Text Cleaning* - Remove embedded characters which may cause data misalignment, for e.g., embedded tabs in a tab-separated data file, embedded new lines which may break records, etc.

#### Learning 

Once you have your dataset after preprocessing, then it's time to select a *learning algorithm* to perform your desired task. In our case it's *Binary Classifier or a Perceptron*. 

Parameters to consider, while choosing a learning algorithm:  
1. *Accuracy*
2. *Training Time*
3. *Linearity*
4. *Number of Parameters*
5. *Number of Features*

#### Evaluation

The metrics that you choose to evaluate the machine learning algorithm are very important. The choice of metrics influences how the performance of machine learning is measured and compared. 

##### Classification Metrics  
1. *Classification Accuracy*
2. *Logarithmic Loss*
3. *Area Under ROC Curve*
4. *Confusion Matrix*
5. *Classification Report*

##### Regression Metrics  
1. *Mean Absolute Error*
2. *Mean Squared Error*
3. *R-Squared*

### Implementing the Perceptron


*A Perceptron is an algorithm for learning a binary classifier: a function that maps it's input *x* to an output value *f(x)* *

### Algorithm 

------- Image --------

Where, 
1. *w* is a vector of real-value weights 
2. *w.x* is a dot product
3. *b* is the bias 

The value of *f(x)* is either **0** or **1**, which is used to classify *x* as either a positive or a negative instance. 


### Implementation

Let's implement the perceptron to predict the outcome of an **OR** gate. 


1. Firstly, let's initialize an array with initial weights equal to **0**. The length of the array is equal to **number of features + 1**. The additional feature is the "threshold". 

    <pre><code>self.weight_matrix = np.zeros(1 + X.shape[1])</code></pre>

2. Secondly, The loop "iterates" multiple times over the training code to optimize the weights to the dataset.

    <pre><code>for _ in range(number_of_iterations):</code></pre>
    
3. We loop over each training data point and it's target. The target is the desired output we want the algorithm to predict. As it's a binary classifier, the targeted ouput is either a **0** or **1**.

    The prediction calculation is a matrix multiplication of the features with the appropirate weights. To this multiplication we add the "threshold" value. 
    
    If the resulting value is above **0**, then the predicted category is <code>1</code>. 
    
    If the resulting value is below **0**, the the predicted category is <code>0</code>.
    
    At each iteration, if the prediction is not accurate, the algorithm will adjust the weights. The adjustment of the weights will be done proportionally to the difference between the target and predicted value. 
    
    The difference is then mulitplied by the **learning rate <code>(rate)</code>**. Higher the value of <code>rate</code>, larger the correction of weights. The algorithm will stop to adjust the weights when the predicted value becomes accurate.
        
    <pre>
        self.weight_matrix = np.zeros(1 + X.shape[1])
        <br>
        # Iterating multiple times to optimize the weights.
        for _ in range(number_of_iterations):
            for xi, target in zip(X, y):
                update = self.rate * (target - self.predict(xi))
                self.weight_matrix[1:] += update * xi
                self.weight_matrix[0] += update
        <br>
        def dot_product(self, X):
            """ Calculate the dot product """
            return np.dot(X, self.weight_matrix[1:]) + self.weight_matrix[0]
        <br>
        def predict(self, X):
            """ Predicting the label for the input data """
            return np.where(dot_product(X) >= 0.0, 1, 0)
    </pre>

You could also try to change the training dataset in order to model an **AND**, **NOR** or **NOT**. Note that it's impossible to to model **XOR** function using a single perceptron like the one we implemented, because the two labels (**0** or **1**) of an **XOR** function are not lineraly seperable. 

In that case you would have to use multiple layers of Perceptrons which is basically a simple **Neural Network**.

### Wrap Up

Here's the entire code:

<script src="https://gist.github.com/maheshkkumar/e8352426a2c803b610283158aedd0b76.js"></script>



