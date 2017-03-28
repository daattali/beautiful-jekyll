---
layout: post
title: Multiclass Classification
date: 2017-03-28 16:47:14 +0530
categories: machine learning
tags: [machine_learning]
bigimg: 
  - /img/multiclass-5.png
---

According to Wikipedia:
> In machine learning, **multiclass** or **multinomial classification** is the problem of classifying instances into one of the more than two classes (classifying instances into one of the two classes is called binary classification).

For instance, you are given an Apple product and you are told to classify it into one of the following:

1. Apple Watch
2. Apple TV
3. iMac
4. iPad
5. iPhone
6. iPod
7. MacBook

So, this is a type of multiclass classification problem. 

In this post, let's learn how to approach a multiclass classification problem. We will be using a dataset that has 5 categories to which we should classify the given data. 

TL;DR
Check out the [code](https://github.com/maheshkkumar/multiclass-classification) for this problem.

Let's import all the necessary libraries. 


```python
# imports

# numpy, lambda, matplotlib
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
%matplotlib inline

# scikit-learn
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
from sklearn.cross_validation import ShuffleSplit
from sklearn.learning_curve import learning_curve

# I will be explaining the purpose of each library as we approach the problem.
```

Let's read the input data

```python
# train and test data
# here we will be using pandas library to read the input data in the form of CSV

train = pd.read_csv('train.csv')
test = pd.read_csv('test.csv')
```

```python
# let's see what's inside the training data
# pandas is a good library to play with data, also you can clean the data.

train.head(3)
```
<div>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>id</th>
      <th>feature0</th>
      <th>feature1</th>
      <th>...</th>
      <th>feature247</th>
      <th>feature248</th>
      <th>feature249</th>
      <th>label</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0</td>
      <td>25.208249</td>
      <td>-16.745748</td>
      <td>...</td>
      <td>-4.938090</td>
      <td>130.068955</td>
      <td>-8.231081</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1</td>
      <td>-86.931450</td>
      <td>0.428227</td>
      <td>...</td>
      <td>-6.389429</td>
      <td>-26.164277</td>
      <td>-4.909740</td>
      <td>2</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2</td>
      <td>42.160934</td>
      <td>7.857013</td>
      <td>...</td>
      <td>8.034066</td>
      <td>120.510705</td>
      <td>7.754377</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
<p>3 rows × 252 columns</p>
</div>

```python
# let's check the shape of the dataset

train.shape
```
    (7200, 252)

Looks like the training dataset contains 7200 rows and 252 columns.

Also, there are 250 _features_, an _id_ column and a _label_ column.


```python
# let's check the information about the training and test dataset

train.info()
print("-")*40
test.info()
```
    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 7200 entries, 0 to 7199
    Columns: 252 entries, id to label
    dtypes: float64(250), int64(2)
    memory usage: 13.8 MB
    ----------------------------------------
    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 4800 entries, 0 to 4799
    Columns: 251 entries, id to feature249
    dtypes: float64(250), int64(1)
    memory usage: 9.2 MB
    
Now, let's clean the training dataset for any null values

```python
# checking for null values

train.isnull().sum().sum()
```
    0L

Looks like there are no null values in the dataset

Now, let's do feature selection, where we use the features which we think are important for classification later on on new data.


```python
# feature selection

# seperate labels from training set
labels = train['label']

# drop or remove id and label columns from training set
train.drop(['id', 'label'], axis=1, inplace=True)
```

Let's see how the training set looks after some trimming.


```python
# training set after removing id and label column

train.head(3)
```

<div>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>feature0</th>
      <th>feature1</th>
      <th>feature2</th>
      <th>...</th>
      <th>feature246</th>
      <th>feature247</th>
      <th>feature248</th>
      <th>feature249</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>25.208249</td>
      <td>-16.745748</td>
      <td>50.869944</td>
      <td>...</td>
      <td>3.682115</td>
      <td>-4.938090</td>
      <td>130.068955</td>
      <td>-8.231081</td>
    </tr>
    <tr>
      <th>1</th>
      <td>-86.931450</td>
      <td>0.428227</td>
      <td>2.874836</td>
      <td>...</td>
      <td>6.484784</td>
      <td>-6.389429</td>
      <td>-26.164277</td>
      <td>-4.909740</td>
    </tr>
    <tr>
      <th>2</th>
      <td>42.160934</td>
      <td>7.857013</td>
      <td>151.612757</td>
      <td>...</td>
      <td>-1.971843</td>
      <td>8.034066</td>
      <td>120.510705</td>
      <td>7.754377</td>
    </tr>
  </tbody>
</table>
<p>3 rows × 250 columns</p>
</div>



Let's do the same for test data, remove id column


```python
# what test dataset looks like

test.head(3)
```




<div>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>id</th>
      <th>feature0</th>
      <th>feature1</th>
      <th>feature2</th>
      <th>...</th>
      <th>feature247</th>
      <th>feature248</th>
      <th>feature249</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>7200</td>
      <td>-76.795547</td>
      <td>-12.319618</td>
      <td>-109.961631</td>
      <td>...</td>
      <td>2.619267</td>
      <td>-14.869630</td>
      <td>-4.718944</td>
    </tr>
    <tr>
      <th>1</th>
      <td>7201</td>
      <td>15.860563</td>
      <td>-5.344301</td>
      <td>74.481876</td>
      <td>...</td>
      <td>-16.322332</td>
      <td>-54.813692</td>
      <td>14.470087</td>
    </tr>
    <tr>
      <th>2</th>
      <td>7202</td>
      <td>21.243900</td>
      <td>-7.539082</td>
      <td>-13.128054</td>
      <td>...</td>
      <td>-3.615364</td>
      <td>160.603909</td>
      <td>-11.330304</td>
    </tr>
  </tbody>
</table>
<p>3 rows × 251 columns</p>
</div>




```python
# dropping id column and storing it for later use

test_ids = test['id']
test.drop(['id'], axis=1, inplace=True)
```

Now, we have segregated the data according to our need.

Let's do some visualizations on the labels.


```python
# count of values under each category

label_count = labels.value_counts().sort_index(ascending=True)
print label_count
```

    0    1419
    1    1426
    2    1485
    3    1410
    4    1460
    Name: label, dtype: int64
    


```python
# visualizing the training labels

label_count.plot(kind='bar', color='skyblue')
plt.xlabel("categories")
plt.ylabel("Count of data")
plt.title("Count of data in each category")
plt.grid()
```


![Count in each category](/img/multiclass-1.png)



From the visualization, it's clear that data is spread evenly across all the 5 categories.

Next, let's split the training set into training set and validation set.

For splitting the dataset, we will be making use of train_test_split from sklearn.

Training Set = 80%
Validation Set = 20%

The reason we use **random_state** is that the splitting of the data must not be random, as it might ruin the consistency.


```python
# splitting of the dataset

X_train, X_test, y_train, y_test = train_test_split(train, labels, test_size=0.2, random_state=21)
```


```python
# check out the shape of each of the above train and test datasets
print("Shape of X_train: {}".format(X_train.shape))
print("Shape of y_train: {}".format(y_train.shape))
print("-"*50)
print("Shape of X_test: {}".format(X_test.shape))
print("Shape of y_test: {}".format(y_test.shape))
```

    Shape of X_train: (5760, 250)
    Shape of y_train: (5760L,)
    --------------------------------------------------
    Shape of X_test: (1440, 250)
    Shape of y_test: (1440L,)
    

Looks like we have got 80% and 20% split

Next, let's visualize the range of values in training set


```python
# visualizing the range of values in training set

for i in range(X_train.shape[1]):
    X_train["feature{}".format(i)].hist(alpha=0.3)
plt.xlabel("Range of datapoints")
plt.title("Feature0 to Feature249")
plt.show()
```


![Range of training data without standardization](/img/multiclass-2.png)


Looks like the datapoints range from **-300** to **300**. We shall bring this range to a single digit.

In-order to standardize the data, let's use the StandardScaler from sklearn.

StandardScaler brings down the range of values a single digit, where the new values are **0**. 
StandardScaler applies a normal distribution, with **mean = 0** and **standard deviation = 1**.


```python
# standardize the data
std_scaler = StandardScaler().fit(X_train)

# transform train and test set using standardization
X_train_std = std_scaler.transform(X_train)
X_test_std = std_scaler.transform(X_test)
```

Let's visualize the range of datapoints in training set


```python
# range of values in training dataset after standardization

plt.hist(X_train_std, 50, alpha=0.75)
plt.xlabel('Range of the data points')
plt.grid(True)
plt.show()
```


![Range of data after standardization](/img/multiclass-3.png)


Standardization worked!

The datapoints are now distributed between **-4** and **4**. 

Next, let's convert the **y_train** and **y_test** pandas series to numpy arrays.


```python
# converting from pandas series to numpy array

y_train = np.asarray(y_train, dtype='float64')
y_test = np.asarray(y_test, dtype='float64')
```

So, all the major cleaning process is done, next we need to choose a classification algorithm to train it. 

But, before that we need to know what are the appropriate hyper paramters that our learning algorithm **KNeighborsClassifier** works efficiently.

In-order to choose the appropriate hyperparameters, let's using **GridSearchCV** from **model_selection**.


```python
# an instane of KNNeighborsClassifier
estimator = KNeighborsClassifier()

# cross-validation using ShuffleSplit
# we do this so the GridSearchCV will train and test the dataset to find the appropriate hyperparameters
cv = ShuffleSplit(int(len(X_train_std)), n_iter=10, random_state=0, test_size=0.2)

# instance of GridSearchCV
classifier = GridSearchCV(estimator=estimator, cv=cv, param_grid=dict(n_neighbors=[5,6,7,8,9,10,11,12,13,14,15]))

# let's fit the classifier with the training set
classifier.fit(X_train_std, y_train)
```




    GridSearchCV(cv=ShuffleSplit(5760, n_iter=10, test_size=0.2, random_state=0),
           error_score='raise',
           estimator=KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
               metric_params=None, n_jobs=1, n_neighbors=5, p=2,
               weights='uniform'),
           fit_params={}, iid=True, n_jobs=1,
           param_grid={'n_neighbors': [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]},
           pre_dispatch='2*n_jobs', refit=True, return_train_score=True,
           scoring=None, verbose=0)



That took a while to figure out the appropriate **n_neighbors** value 

Let's check the value of **n_neighbors**


```python
print classifier.best_params_
```

    {'n_neighbors': 15}
    

Looks like assigning **n_neighbors** to **15** is a good choice.

Let's train the KNeighborsClassifier with the best params value


```python
# instance of KNeighborsClassifier

estimator = KNeighborsClassifier(n_neighbors=15)
```


```python
# fit the training data

estimator.fit(X_train_std, y_train)
```




    KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
               metric_params=None, n_jobs=1, n_neighbors=15, p=2,
               weights='uniform')




```python
# testing on validation set

y_pred = estimator.predict(X_test_std)
```

Now, let's print **accuracy_score**, **confusion_matrix** and **classification_report** from **sklearn.metrics**


```python
# printing out some metrics

print("Accuracy: {}".format(accuracy_score(y_test, y_pred)))
print("-"*50)
print("Confusion Matrix: \n{}".format(confusion_matrix(y_test, y_pred)))
print("-"*50)
print("Classification Report: \n{}".format(classification_report(y_test, y_pred)))
```

    Accuracy: 0.970833333333
    --------------------------------------------------
    Confusion Matrix: 
    [[274   2   0   1   0]
     [  2 250   3   1   3]
     [  1   3 280   3   0]
     [  4   6   3 294   3]
     [  3   3   1   0 300]]
    --------------------------------------------------
    Classification Report: 
                 precision    recall  f1-score   support
    
            0.0       0.96      0.99      0.98       277
            1.0       0.95      0.97      0.96       259
            2.0       0.98      0.98      0.98       287
            3.0       0.98      0.95      0.97       310
            4.0       0.98      0.98      0.98       307
    
    avg / total       0.97      0.97      0.97      1440
    
    

All the above scores are fine, let's have a look at the learning curve.


```python
def leaning_curve_plot(estimator, X, y, cv):
    plt.figure()
    plt.title("Learning Curve")
    plt.xlabel("Traning Example")
    plt.ylabel("Score")
    plt.grid()
    
    # compute mean and standard deviation
    train_sizes, train_scores, test_scores = learning_curve( estimator, X, y, cv=cv, n_jobs=-1, train_sizes=np.linspace(.1, 1.0, 5))
    train_scores_mean = np.mean(train_scores, axis=1)
    train_scores_std = np.std(train_scores, axis=1)
    test_scores_mean = np.mean(test_scores, axis=1)
    test_scores_std = np.std(test_scores, axis=1)

    # fill_between 
    plt.fill_between(train_sizes, train_scores_mean - train_scores_std, train_scores_mean + train_scores_std, alpha=0.1, color='r')
    plt.fill_between(train_sizes, test_scores_mean - test_scores_std, test_scores_mean + test_scores_std, alpha=0.1, color='g')
    
    # plotting 
    plt.plot(train_sizes, train_scores_mean, 'o-', color='r', label="Trainig score")
    plt.plot(train_sizes, test_scores_mean, 'o-', color='g', label="Cross Validation score")

    plt.legend(loc="best")
    
    return plt
```


```python
plt = leaning_curve_plot(estimator, X_train_std, y_train, cv)
plt.show()
```


![Learning Curve](/img/multiclass-4.png)


Looks like the estimator's score goes high when the dataset size increases.


```python
# Time to classify the test set
X_test = std_scaler.transform(test)
```


```python
y_pred = estimator.predict(X_test)
```


```python
# saving the output to a csv
output = pd.DataFrame({'id': test_ids, 'label': y_pred})
```


```python
# printing output
output.head(4)
```




<div>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>id</th>
      <th>label</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>7200</td>
      <td>4.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>7201</td>
      <td>2.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>7202</td>
      <td>2.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>7203</td>
      <td>4.0</td>
    </tr>
  </tbody>
</table>
</div>

Now, let's look at the decision boundary for the given dataset


```python
# reducing the dimensionality from 15 to 2
X_train_embedded = TSNE(n_components=2).fit_transform(X_train_std)
print X_train_embedded.shape
model = KNeighborsClassifier(n_neighbors=15).fit(X_train_std, y_train)
y_predicted = model.predict(X_train_std)

# creating meshgrid
resolution = 150 # 150x150 background pixels
X2d_xmin, X2d_xmax = np.min(X_train_embedded[:,0]), np.max(X_train_embedded[:,0])
X2d_ymin, X2d_ymax = np.min(X_train_embedded[:,1]), np.max(X_train_embedded[:,1])
xx, yy = np.meshgrid(np.linspace(X2d_xmin, X2d_xmax, resolution), np.linspace(X2d_ymin, X2d_ymax, resolution))

# approximate Voronoi tesselation on resolution x resolution grid using 1-NN
background_model = KNeighborsClassifier(n_neighbors=15).fit(X_train_embedded, y_predicted) 
voronoiBackground = background_model.predict(np.c_[xx.ravel(), yy.ravel()])
voronoiBackground = voronoiBackground.reshape((resolution, resolution))

#plot
plt.contourf(xx, yy, voronoiBackground)
plt.scatter(X_train_embedded[:,0], X_train_embedded[:,1], c=y_train)
plt.show()
```
    (5760L, 2L)
    
![Decision Boundary](/img/multiclass-5.png)


Here, we see a clear classification of the datapoints into one of the five categories. 

Hope you have understood the process of solving a multiclass classification problem. 