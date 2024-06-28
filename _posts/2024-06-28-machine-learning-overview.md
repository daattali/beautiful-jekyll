---
layout: post
title: Gearing Up for Machine Learning My Journey to GCP Professional ML Engineer
subtitle: To help reinforce my learning, I’m creating various blog posts on the topics I’m studying in preparation for the exam, and to assist anyone else embarking upon the  Google Cloud ML Engineer certification, or interested in learning more about machine learning topics. This blog post focuses on Machine Learning, how it relates to Artificial Intelligence and the common model types.
#description: ""
#cover-img: /assets/img/path.jpg
#thumbnail-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
#share-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
readtime: true
share-title: "Gearing Up for Machine Learning: My Journey to GCP Professional ML Engineer"
share-description: "To help reinforce my learning, I’m creating various blog posts on the topics I’m studying in preparation for the exam, and to assist anyone else embarking upon the  Google Cloud ML Engineer certification, or interested in learning more about machine learning topics. This blog post focuses on Machine Learning, how it relates to Artificial Intelligence and the common model types."
#share-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
tags: [Google Cloud Professional Machine Learning Engineer, Machine Learning, Supervised, Classification, AI]
---

* toc
{:toc}

# Machine Learning

Machine learning (ML) is a subfield of artificial intelligence that deals with the ability of computers to learn without explicit programming. Imagine a child learning to recognize different animals. Through exposure to pictures and real-life encounters, the child grasps the distinguishing features of each animal. Similarly, machine learning algorithms learn from data to make data-driven predictions or uncover hidden patterns.

Artificial intelligent (AI) is the branch of computer science that focuses on creating intelligent agents (systems) that can reason, learn and act autonomously in a manner similar to humans. Machine learning provides the specific techniques and algorithms that enable this to happen. It's the engine that powers many of the intelligent applications we use today, from facial recognition software to recommendation systems, to self driving cars.

# Supervised vs Unsupervised Learning

There are two main categories of machine learning: supervised and unsupervised.

## Supervised Learning

With supervised learning we provide the algorithm with labelled data, where each data point has a corresponding label or outcome (think “cat” or “dog” for an image dataset). The algorithm then learns the relationship between these features and their labels, using this knowledge to predict labels for new, unseen data.

Some example use cases for supervised learning models include:

- Spam filtering (classifying emails as spam or not-spam).
- Image recognition (identifying objects in an image).
- Stock price prediction (predicting future stock prices based on historical data).

## Unsupervised Learning

With unsupervised learning the algorithm is presented with unlabelled data and must independently discover inherent patterns or structures within it. This can involve grouping similar data points together (clustering) or identifying hidden relationships between features.

Example use cases of unsupervised learning includes:

- Customer segmentation (grouping customers with similar characteristics for targeted marketing).
- Anomaly detection (identifying unusual patterns in data, like fraudulent transactions).
- Recommendation systems (suggesting products to users based on their past purchases).

# Classification vs. Regression Models

Within supervised learning, we have two major model types: classification and regression.

## Classification Models

Classification models are designed to assign data points to particular categories. This can be either binary classification models, where the data is classified as one item or another, or multiclass classification models where the data is classified into three or more potential categories.

The first stage of classification starts with data wrangling. This is the term given for sorting the raw collected data into a useable format by resolving any inconsistencies, managing missing values and transforming the data into the required form for the model. For image classification, this may include tasks like resizing images and encoding into a numerical format for the model. For text classification, this includes methods of encoding text into numerical format with the likes of one hot encoding practices.

After data wrangling comes feature engineering. At this stage, we extract the most relevant features from the data for effective classification. These features then act as fingerprints helping the model to distinguish between the different classification categories.

Classification models are a supervised learning model, and as such depend upon labelled datasets for training. Each datapoint within the data set has a pre-assigned label corresponding to the category it belongs to.

Once we have a labelled dataset, and know what features to use for the model, we then need to decide upon the model’s algorithm. There are many algorithms available for classification machine learning, ranging from logistic regression, clustering to sentinel analysis and neural networks. Selection of the algorithm depends upon the classification task you are performing. 

The model is now ready for training. At this stage the model consumes the labelled training dataset, analysing patterns between features and their connections to the category labels. The model iterates through the dataset dependent upon the hyperparameters specified for the model, calculating the optimal model performance. The dataset is typically split into a training dataset, validation data set and test dataset. It's essential that each dataset is unique, but also representative of the entire dataset. Failure of achieving this may result in the model not appearing to perform as well as it could if the data had been correctly split.

Once the optimal model is determined, it is ready to be consumed and start making predictions against new unseen, unlabelled data by analysing the new data's features and based upon the model's learned patterns, allocates the data point to most likely classification category.

Whilst the model is now happily allocating categories to new data points, it is essential to monitor performance. Metrics including accuracy, precision and recall provide insights into how well the model is performing against new data. If the performance isn’t satisfactory and deviates significantly from the trained model, it may indicate issues like overfitting and require further refinement, either by adjusting hyperparameters accordingly, increasing generalisation or using an alternative algorithm.

## Regression Models

Instead of predicting distinct categories, regression models predict a continuous value based on one or more variables. The regression model focuses on uncovering trends and estimating how one variable affects another. A well documented use case is predicting housing values- whilst a classification model may predict a house as "affordable" vs "not affordable," a regression model would predict the actual value of the property i.e. a continuous value on a number line.

The outcome variable, i.e. what the model is aiming to predict, and the the predictor variables i.e. factors influencing the outcome variable are the two key components in regression models. The model aims to find a mathematical equation to best represent the relationship between the outcome and predictor variables. The equation is often visualised as a line or curve, aiming to minimise the difference between the model's predicted value and the actual value.

The most common type of regression model is a linear regression- this uses a straight line to model the relationship. However many data sets exhibit curvier trends, where linear regression falls shorts. For these scenarios, polynomial regression is often the best fit. There are various other types of model analysis for non linear regression including decision tree regression, random forest regression, support vector regression and lasso regression.

The stages referenced above for classification models also apply to regression models e.g. data wrangling and feature engineering.

Common regression models include:

- Linear Regression: The workhorse for simple relationships between features and a target value.
- Lasso & Ridge Regression: Regularized models to prevent overfitting, especially with many features.
- XGBoost & Random Forest Regression: Ensemble methods for improved accuracy on complex relationships.

Choosing the right model ultimately depends on the problem you're trying to solve!
