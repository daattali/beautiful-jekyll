---
layout: post
title: BigQuery ML Customer Churn Model for Subscriptions
image: /img/hello_world.jpeg
---



Building a BigQuery Machine Learning model that can predict which of your prospects will convert into customers or which customers will churn is a very valuable insight to any company. You can use this as a tool to better allocate sales resources, forecast your revenue or to prevent your customers from churning before they do. The reason for me writing this post is because there is a lack of documentation (or some are just outright wrong and when I reach out the authors, it seems like they don’t know what they are doing) on the internet for predicting customer churn in a subscription based model (specifically a fixed 12 or 24 subscription model). 

In this post, I will talk about the customer churn model for a 12 month subscription model, but you can apply this method to any business model or if you are trying to predict prospect conversion.

## Step 1: Gather information and variables
In order to be able to build a customer churn prediction model, we need to understand what are the leading indicators for a customer to churn after their subscription and what are the most important factors for identifying a healthy user. Some might be so obvious and the best way to discover these variables is by doing some information gathering with the sales team or anyone who works closely with customers. They have the best insight on what variables would be good to test.

Once you have your list of variables, it is time to get your data together. The creation of the dataset is a very important step because it will save you a lot of headaches down the road. Make sure it is flexible to adding or manipulating variables. You will need to remove any columns with missing data or you can use imputation methods to fill in missing data.

## Step 2: Test variables for significance and high collinearity
Begin testing which variables are significant enough to be included in your model. You can easily do this by plotting the confidence interval of each variable for both classes (churned or renewed). 

After testing which variables are significantly different between the classes, you will have to test for multicollinearity. You can do this by measuring the Variance Inflation Factor (VIF) for each variable. Any VIF over 5 usually means the variable is highly collinear with other variables. For example, sessions and time spent on the application can be highly collinear with each other and it might make more sense to only pick sessions or time spent on the application (depending on what you are trying to measure). 


## Step 3: Create Logistic Regression model in BigQuery
### Create Model:

```
CREATE MODEL `bqml_tutorial.example`
OPTIONS
  (model_type='logistic_reg',
    input_label_cols=['churn']) AS
SELECT
  age,
  sessions,
  Month of subscription,
  Days since last active
FROM
  Data_table
```

### Evaluation Model:

```
SELECT
  *
FROM
  ML.EVALUATE(MODEL `bqml_tutorial.example`,
    (
    SELECT
  age,
  sessions,
  Month of subscription,
  Days since last active
FROM
  Data_table))
```

### Apply prediction model:

```
SELECT
  *
FROM
  ML.PREDICT(MODEL `bqml_tutorial.example`,
    (
     SELECT
username,
  age,
  sessions,
  Month of subscription,
  Days since last active
FROM
  test_data_table))
```
### Confusion Matrix:
Checking the confusion matrix is really useful to see how many correct deals you predicted in each class (Won and Lost).

```
SELECT
  *
FROM
  ML.CONFUSION_MATRIX(MODEL `bqml_tutorial.example`,
    (
     SELECT
username,
  age,
  sessions,
  Month of subscription,
  Days since last active
FROM
  test_data_table))
```

## Step 4: Model Tuning

If you have imbalance classes, then use the auto_class = True. You can put this option in the Create Model code. 

If you don’t have a lot of data and you don’t mind a long query, then you can turn off the auto learn rate. 

You can engineer your own features such as concatenating the time and user engagement variables or various flags.

## Step 5: Implementation
You can implement this model into Salesforce or into Looker. I can write about this in another article.
