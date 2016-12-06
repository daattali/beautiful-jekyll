---
layout: post
title: "Text classification on Amazon Reviews"
share_img: https://github.com/fderyckel/fderyckel.github.io/blob/master/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-22-1.png
tags: [caret, RTextTools, text_mining, SVM]
---
-   [Introduction of text analysis with R.](#introduction-of-text-analysis-with-r.)
-   [First method using the `tm` and `caret` package](#first-method-using-the-tm-and-caret-package)
    -   [Simple example](#simple-example)
        -   [Text pre-processing](#text-pre-processing)
        -   [Create the model and use it for prediction](#create-the-model-and-use-it-for-prediction)
    -   [Second example on Amazon Reviews](#second-example-on-amazon-reviews)
        -   [Pre-processing](#pre-processing)
        -   [Conclusion](#conclusion)
-   [Second method with RTextTools. Let's start easy with some simple text](#second-method-with-rtexttools.-lets-start-easy-with-some-simple-text)
    -   [First example with easy data](#first-example-with-easy-data)
        -   [Text pre-processing](#text-pre-processing-1)
        -   [Creating and testing the model](#creating-and-testing-the-model)
    -   [Second example with Amazon reviews and "SVM" method](#second-example-with-amazon-reviews-and-svm-method)
    -   [Second example with Amazon reviews and "Maximum Enthropy method"](#second-example-with-amazon-reviews-and-maximum-enthropy-method)
        -   [Conclusion](#conclusion-1)
-   [Where to go from here](#where-to-go-from-here)
-   [Resources used](#resources-used)

This document has been inspired by the Coursera course on [Machine Learning Foundations: A Case Study Approach](https://www.coursera.org/learn/ml-foundations/) given by Carlos Guestrin and by Emily Fox from Washington University. This course is part of the [Machine Learning Specialization](https://www.coursera.org/specializations/machine-learning)

The task was to apply classfification on an Amazon review dataset. Given a review, we create a model that will decide if the review is *positive* (associated with a rating of 4 or 5) or *negative* (associate with a rating of 1 or 2). This is a supervised learning task as the grading associated with the reviews is used as the response variable.

The course use Python and the GraphLab Create framework around it. Although it is exciting to learn Python, I'm a bit less thrilled to have to learn it from a a framework which license will expire in a year. That said the framework seems very powerful and quite easy to use (a lot of the default parameters seem to work very nicely out of the box.)

So I was thinking to try a similar approach with R. I have to say I did struggle a bit to find appropriate packages and ways to use to them. So this is a very basic attempt to replicate a supervised linear classification on text.

Introduction of text analysis with R.
=====================================

One have quite a few choice when doing text analytics in R. The `tm` package is probably one of the most well known.
I also came accross 3 others: `RTextTools`, `quantedea` and `tidytext`.

`RTextTools` is using a variety of existing R packages, it is designed as a one-stop-shop for conducting supervised learning with textual data. Overall, RTextTools offers a comprehensive approach to text classification, by interfacing with existing text pre-processing routines and machine learning algorithms and by providing new analytics functions.

We have not yet managed to try with the other 2 packages.

First method using the `tm` and `caret` package
===============================================

This is the very simple and basic method to show how we can apply classification as supervised learning on texts.

Simple example
--------------

Let's first create a character vector with 3 elements.

``` r
exa1 <- c('Cats like to chase mice.', 'Dogs bite people.', 'Dogs like to run after cats.')
str(exa1)
```

    ##  chr [1:3] "Cats like to chase mice." "Dogs bite people." ...

``` r
class(exa1)
```

    ## [1] "character"

Most algorithms applyied on text tend to use a matrix with each of the terms used in a corpus (the series of documents) and their frequency. This is called a 'Document Term Matrix' aka DTM.
It is fairly straight forward to create such a DTM with the `tm` package.

### Text pre-processing

``` r
library(tm)
library(dplyr)
library(tibble)

# Create a corpus from our character vector
corpus <- Corpus(VectorSource(exa1))

# Create the document term matrix
tdm <- DocumentTermMatrix(corpus, list(removePunctuation = TRUE, 
                                       removeNumbers = TRUE))

train_set <- as.matrix(tdm)

# add the classifier column and make it a data frame
train_set <- cbind(train_set, c(0,1,0))
colnames(train_set)[ncol(train_set)] <- "y"
train_set <- as.data.frame(train_set)
train_set$y <- as.factor(train_set$y)

# let's have a glimpse at our training set  
glimpse(train_set)
```

    ## Observations: 3
    ## Variables: 10
    ## $ after  <dbl> 0, 0, 1
    ## $ bite   <dbl> 0, 1, 0
    ## $ cats   <dbl> 1, 0, 1
    ## $ chase  <dbl> 1, 0, 0
    ## $ dogs   <dbl> 0, 1, 1
    ## $ like   <dbl> 1, 0, 1
    ## $ mice   <dbl> 1, 0, 0
    ## $ people <dbl> 0, 1, 0
    ## $ run    <dbl> 0, 0, 1
    ## $ y      <fctr> 0, 1, 0

Each observation represent one document (in our case one element of our original character vector). Each variable represent a word used in the corpus. The *0* and *1* are their frequency.

### Create the model and use it for prediction

Now that we have a training set, we can create a model based on our training set. We do this by using the `caret` package and the `bayesglm` method.

``` r
library(caret)
exa1_model <- train(y ~., data = train_set, method = 'svmLinear3')
```

Let's check the accuracy of our model on our training set.

``` r
# Check accuracy on training.
predict(exa1_model, newdata = train_set)
```

    ## [1] 0 1 0
    ## Levels: 0 1

Let's try our model on new data.

``` r
# Test data.
data2 <- c('Bats eat bugs.')
corpus <- Corpus(VectorSource(data2))
tdm <- DocumentTermMatrix(corpus, control = list(dictionary = Terms(tdm)))
test <- as.matrix(tdm)

# Check accuracy on test.
predict(exa1_model, newdata = test)
```

    ## [1] 0
    ## Levels: 0 1

Second example on Amazon Reviews
--------------------------------

Let's see if we can use this technique with our some of our Amazon Reviews. We have saved the review on this file in [Google Drive](https://drive.google.com/file/d/0ByHtvgo2NGDMN0txU2p5QTR3VEk/view?usp=sharing)

### Pre-processing

We first load these reviews

``` r
product_review <- readr::read_csv("toyamazonPhilips.csv")

#Let's have a quick look at the reviews
head(product_review, 4)
```

    ## # A tibble: 4 × 5
    ##                               name
    ##                              <chr>
    ## 1 Philips Avent 3 Pack 9oz Bottles
    ## 2 Philips Avent 3 Pack 9oz Bottles
    ## 3 Philips Avent 3 Pack 9oz Bottles
    ## 4 Philips Avent 3 Pack 9oz Bottles
    ## # ... with 4 more variables: review <chr>, rating <int>, count <int>,
    ## #   standev <dbl>

``` r
#Let's see the table of ratings.  
table(product_review$rating)
```

    ## 
    ##  1  2  3  4  5 
    ## 45 33 17 30 66

``` r
# We'll put a 1 for great reviews (4 or 5) or a 0 for bad reviews (1 or 2)
# We remove all the reviews that have a rating of 3
library(dplyr)
product_review <- product_review %>% filter(rating != 3) %>% 
                    mutate(rating_new = if_else(rating >= 4, 1, 0))
product_review_training <-  product_review[1:150, ]
```

Now we create our corpus, then tokenize, then make it back to a data frame.

``` r
library(tm)
corpus_toy <- Corpus(VectorSource(product_review_training$review))
tdm_toy <- DocumentTermMatrix(corpus_toy, list(removePunctuation = TRUE, 
                                               removeNumbers = TRUE))

training_set_toy <- as.matrix(tdm_toy)

training_set_toy <- cbind(training_set_toy, product_review_training$rating_new)

colnames(training_set_toy)[ncol(training_set_toy)] <- "y"

training_set_toy <- as.data.frame(training_set_toy)
training_set_toy$y <- as.factor(training_set_toy$y)
```

Now that we have our data frame ready, let's create our model.

``` r
library(caret)
review_toy_model <- train(y ~., data = training_set_toy, method = 'svmLinear3')
```

Now we try our model on new review data

``` r
test_review_data <- product_review[151:191, ]

test_corpus <- Corpus(VectorSource(test_review_data$review))
test_tdm <- DocumentTermMatrix(test_corpus, control=list(dictionary = Terms(tdm_toy)))
test_tdm <- as.matrix(test_tdm)

#Build the prediction  
model_toy_result <- predict(review_toy_model, newdata = test_tdm)

check_accuracy <- as.data.frame(cbind(prediction = model_toy_result, rating = test_review_data$rating_new))

check_accuracy <- check_accuracy %>% mutate(prediction = as.integer(prediction) - 1)

check_accuracy$accuracy <- if_else(check_accuracy$prediction == check_accuracy$rating, 1, 0)
round(prop.table(table(check_accuracy$accuracy)), 3)
```

    ## 
    ##     0     1 
    ## 0.208 0.792

### Conclusion

This method is really dependend on the method we use in the `train` function.
After a bit of reading on text classification such as these reviews, we noticed that often the **SVM** method was quite efficient for this type of task.
We also use the `bayesglm` method but computer stalled everytime on the same train set due to lack of computation power. I'm sure we could try other method and parameters to try to get better results.

Second method with RTextTools. Let's start easy with some simple text
=====================================================================

First example with easy data
----------------------------

### Text pre-processing

``` r
library(tibble)
library(tidyr)
pos_tweets =  rbind(
  c('I love this car', 'positive'),
  c('This view is amazing', 'positive'),
  c('I feel great this morning', 'positive'),
  c('I am so excited about the concert', 'positive'),
  c('He is my best friend', 'positive')
)

neg_tweets = rbind(
  c('I do not like this car', 'negative'),
  c('This view is horrible', 'negative'),
  c('I feel tired this morning', 'negative'),
  c('I am not looking forward to the concert', 'negative'),
  c('He is my enemy', 'negative')
)

test_tweets = rbind(
  c('feel happy this morning', 'positive'),
  c('larry friend', 'positive'),
  c('not like that man', 'negative'),
  c('house not great', 'negative'),
  c('your song annoying', 'negative')
)

tweets = rbind(pos_tweets, neg_tweets, test_tweets)
```

We have just created 4 matrices.

``` r
class(tweets)
```

    ## [1] "matrix"

In text processing, one of the first thing to do usually is to create the DTM (document term matrix).

``` r
library(RTextTools)
tweets_matrix = create_matrix(tweets[,1], language = 'English', 
                              removeStopwords = FALSE, 
                              removeNumbers = TRUE, 
                              stemWords = FALSE)
```

Now `tweets_matrix` is a dtm.

``` r
tweets_matrix
```

    ## <<DocumentTermMatrix (documents: 15, terms: 29)>>
    ## Non-/sparse entries: 49/386
    ## Sparsity           : 89%
    ## Maximal term length: 8
    ## Weighting          : term frequency (tf)

`RTextTools` requires to first build a container.

``` r
#Here we also specify the training set and the testing set
container = create_container(tweets_matrix, as.numeric(as.factor(tweets[,2])), 
                             trainSize = 1:10, testSize = 11:15, 
                             virgin = FALSE)
```

### Creating and testing the model

We now create our model.

``` r
tweet_model <- train_model(container, algorithm = "SVM")
```

We test our model.

``` r
tweet_model_result <- classify_model(container, tweet_model)
table(as.numeric(as.factor(tweets[11:15, 2])), tweet_model_result[,"SVM_LABEL"])
```

    ##    
    ##     1 2
    ##   1 1 2
    ##   2 2 0

``` r
analytics = create_analytics(container, tweet_model_result)
summary(analytics)
```

    ## ENSEMBLE SUMMARY
    ## 
    ##        n-ENSEMBLE COVERAGE n-ENSEMBLE RECALL
    ## n >= 1                   1               0.2
    ## 
    ## 
    ## ALGORITHM PERFORMANCE
    ## 
    ## SVM_PRECISION    SVM_RECALL    SVM_FSCORE 
    ##         0.165         0.165         0.165

Second example with Amazon reviews and "SVM" method
---------------------------------------------------

Let's now try this method with our Amazon Reviews. We can use the same dataframe that we used in our previous method.
Like before we "DocumentTermMatrix", we create a matrix of terms

``` r
product_review_matrix <- create_matrix(product_review[,2], language = "English", 
                                       removeNumbers = TRUE, 
                                       removePunctuation = TRUE, 
                                       removeStopwords = FALSE, stemWords = FALSE)

product_review_container <- create_container(product_review_matrix,
                                             product_review$rating_new, 
                                             trainSize = 1:150, testSize = 151:174, 
                                             virgin = FALSE)

product_review_model <- train_model(product_review_container, algorithm = "SVM", kernel="radial")

product_review_model_result <- classify_model(product_review_container, product_review_model)
x <- as.data.frame(cbind(product_review$rating_new[151:174], product_review_model_result$SVM_LABEL))
colnames(x) <- c("actual_ratings", "predicted_ratings")
x <- x %>% mutate(predicted_ratings = predicted_ratings - 1)
round(prop.table(table(x$actual_ratings == x$predicted_ratings)), 3)
```

    ## 
    ## FALSE  TRUE 
    ##  0.25  0.75

Second example with Amazon reviews and "Maximum Enthropy method"
----------------------------------------------------------------

Let's now try this method with our Amazon Reviews. We can use the same dataframe that we used in our previous method.
Like before we "DocumentTermMatrix", we create a matrix of terms

``` r
product_review_matrix <- create_matrix(product_review[,2], language = "English", 
                                       removeNumbers = TRUE, 
                                       removePunctuation = TRUE, 
                                       removeStopwords = FALSE, stemWords = FALSE)

product_review_container <- create_container(product_review_matrix,
                                             product_review$rating_new, 
                                             trainSize = 1:150, testSize = 151:174, 
                                             virgin = FALSE)

product_review_model <- train_model(product_review_container, algorithm = "MAXENT")

product_review_model_result <- classify_model(product_review_container, product_review_model)
x <- as.data.frame(cbind(product_review$rating_new[151:174], product_review_model_result$MAXENTROPY_LABEL))
colnames(x) <- c("actual_ratings", "predicted_ratings")
x <- x %>% mutate(predicted_ratings = predicted_ratings - 1)
round(prop.table(table(x$actual_ratings == x$predicted_ratings)), 3)
```

    ## 
    ## FALSE  TRUE 
    ##  0.25  0.75

### Conclusion

This is model gives the same result (which was expected as we used the same method, although `caret` use the `LiblineaR` package and `RTextTools` use the `e1071` package) on the same testing set. That said I would tend to prefer the RTextTools way of classifying as it seems slightly cleaner and use less computing time when it is time to train the model.

Where to go from here
=====================

There is more work to do in finding other relevant algorithms, understanding their parameters and doing more work on model evaluation.

Resources used
==============

For the [intro](http://datascienceplus.com/sentiment-analysis-with-machine-learning-in-r/)

To check the [method](http://topepo.github.io/caret/train-models-by-tag.html#support-vector-machines) on the caret package.

Introductory article of the [RTextTools](https://journal.r-project.org/archive/2013-1/collingwood-jurka-boydstun-etal.pdf) package by its author.

Another article on using the `method = "svm"` with the [RTextTool](http://www.svm-tutorial.com/2014/11/svm-classify-text-r/) package.

A resource on [sentiment analysis](https://www.codementor.io/python/tutorial/data-science-python-r-sentiment-classification-machine-learning) with R and Python
