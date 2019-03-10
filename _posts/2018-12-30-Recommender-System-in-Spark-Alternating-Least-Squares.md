---
layout: post
title: Building Recommender System in Spark Using Alternating Least Squares Algorithm 
subtitle: Personalized Recommendation with Matrix Factorization 
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [spark,pyspark,matrix factorization, Alternating Least Squares]
---



#### Building Recommender System in Spark : Alternating Least Squares Algorithm



A common challenge  for online companies such as in  retail marketing is that of recommending new products to users in personalized settings (e.g. Amazon's product recommender system, and ebay recom-mendations). Often not only is interest in recommending new products but also recommending products that have been purchased in the past by the shopper and adding a targeted discount coupon with the goal of  increasing sales. A common approach to solving this problem is through matrix factorization, where given the ratings
that users have given certain items and are tasked with predicting their ratings for the rest of the items. 

This can be formulated as a learning problem in which we are given the ratings
that users have given certain items and are tasked with predicting their ratings for the rest of the items. A user-item matrix can be constructed as follows:
Given n users and m items,  an n . m matrix A  in which the
(u; i)th entry is rui { the rating for item i by user u. The matrix A has many unobserved ratings which is represented as missing ratings.


We load the required packages below.


```python
%matplotlib inline
import pandas as pd
import gzip
import os 
import matplotlib.pyplot as plt
import os, random, time, shutil, requests
import numpy as np
# Hide warnings if there are any
import warnings
warnings.filterwarnings('ignore')
import seaborn as sns; sns.set() 
from datetime import datetime, timedelta
from dateutil.parser import parse
from scipy import stats
from ast import literal_eval
import warnings; warnings.simplefilter('ignore')
from sklearn.model_selection import train_test_split
from numpy import linalg as LA
import multiprocessing
```


```python
from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('recommender').getOrCreate()
from pyspark.ml.recommendation import ALS
from pyspark.ml.evaluation import RegressionEvaluator
```


```python
path='/Users/nanaakwasiabayieboateng/PythonRecommenderSystem'


# Check current working directory.
retval = os.getcwd()
print ("Current working directory %s" % retval)

# Now change the directory
os.chdir( path )

# Check current working directory.
retval = os.getcwd()

print("Directory changed successfully %s" % retval)

# list files in current directory
#files = os.listdir(path)
#print(files)
```

    Current working directory /Users/nanaakwasiabayieboateng/SparkPython2
    Directory changed successfully /Users/nanaakwasiabayieboateng/PythonRecommenderSystem


The Musical Instruments reviews dataset from the Amazon product dataset used in this work can be found [here](http://jmcauley.ucsd.edu/data/amazon/links.html)
.This dataset contains product reviews and metadata from Amazon, including 142.8 million reviews spanning May 1996 - July 2014.
This dataset includes reviews (ratings, text, helpfulness votes), product metadata (descriptions, category information, price, brand, and image features), and links (also viewed/also bought graphs).The discription of the dataset is as follows:
reviewerID - ID of the reviewer, e.g. A2SUAM1J3GNN3B
asin - ID of the product, e.g. 0000013714
reviewerName - name of the reviewer
helpful - helpfulness rating of the review, e.g. 2/3
reviewText - text of the review
overall - rating of the product
summary - summary of the review
unixReviewTime - time of the review (unix time)
reviewTime - time of the review (raw)

Import the data downloaded from the amazon site as below.


```python
import json

Musical_Instruments = []
for line in open('reviews_Musical_Instruments.json', 'r'):
    Musical_Instruments.append(json.loads(line))
```


```python
df=pd.DataFrame(Musical_Instruments)
df.head(3)
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>asin</th>
      <th>helpful</th>
      <th>overall</th>
      <th>reviewText</th>
      <th>reviewTime</th>
      <th>reviewerID</th>
      <th>reviewerName</th>
      <th>summary</th>
      <th>unixReviewTime</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0006428320</td>
      <td>[0, 0]</td>
      <td>3.0</td>
      <td>The portfolio is fine except for the fact that...</td>
      <td>03 11, 2014</td>
      <td>A1YS9MDZP93857</td>
      <td>John Taylor</td>
      <td>Parts missing</td>
      <td>1394496000</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0014072149</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>If you are a serious violin student on a budge...</td>
      <td>06 6, 2013</td>
      <td>A3TS466QBAWB9D</td>
      <td>Silver Pencil</td>
      <td>Perform it with a friend, today!</td>
      <td>1370476800</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0041291905</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>This is and excellent edition and perfectly tr...</td>
      <td>10 14, 2013</td>
      <td>A3BUDYITWUSIS7</td>
      <td>joyce gabriel cornett</td>
      <td>Vivalldi's Four Seasons</td>
      <td>1381708800</td>
    </tr>
  </tbody>
</table>
</div>



check the class of each column variable


```python
df.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 500176 entries, 0 to 500175
    Data columns (total 9 columns):
    asin              500176 non-null object
    helpful           500176 non-null object
    overall           500176 non-null float64
    reviewText        500176 non-null object
    reviewTime        500176 non-null object
    reviewerID        500176 non-null object
    reviewerName      497590 non-null object
    summary           500176 non-null object
    unixReviewTime    500176 non-null int64
    dtypes: float64(1), int64(1), object(7)
    memory usage: 34.3+ MB



```python
df.dtypes
```




    asin               object
    helpful            object
    overall           float64
    reviewText         object
    reviewTime         object
    reviewerID         object
    reviewerName       object
    summary            object
    unixReviewTime      int64
    dtype: object



Alternative if we convert the variable unixReviewTime which is in unix time format,thus the number of seconds since January 01 1970 (UTC) into a standard date format, we can easily use pandas to extract the day, month and year from the date.


```python

#convert unix time in seconds to date-time
df["Date_Time"] = pd.to_datetime(df["unixReviewTime"], unit='s')
df['year'] = df['Date_Time'].dt.year
df['month'] = df['Date_Time'].dt.month
df['day'] = df['Date_Time'].dt.day
df.head(3)
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>asin</th>
      <th>helpful</th>
      <th>overall</th>
      <th>reviewText</th>
      <th>reviewTime</th>
      <th>reviewerID</th>
      <th>reviewerName</th>
      <th>summary</th>
      <th>unixReviewTime</th>
      <th>Date_Time</th>
      <th>year</th>
      <th>month</th>
      <th>day</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0006428320</td>
      <td>[0, 0]</td>
      <td>3.0</td>
      <td>The portfolio is fine except for the fact that...</td>
      <td>03 11, 2014</td>
      <td>A1YS9MDZP93857</td>
      <td>John Taylor</td>
      <td>Parts missing</td>
      <td>1394496000</td>
      <td>2014-03-11</td>
      <td>2014</td>
      <td>3</td>
      <td>11</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0014072149</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>If you are a serious violin student on a budge...</td>
      <td>06 6, 2013</td>
      <td>A3TS466QBAWB9D</td>
      <td>Silver Pencil</td>
      <td>Perform it with a friend, today!</td>
      <td>1370476800</td>
      <td>2013-06-06</td>
      <td>2013</td>
      <td>6</td>
      <td>6</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0041291905</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>This is and excellent edition and perfectly tr...</td>
      <td>10 14, 2013</td>
      <td>A3BUDYITWUSIS7</td>
      <td>joyce gabriel cornett</td>
      <td>Vivalldi's Four Seasons</td>
      <td>1381708800</td>
      <td>2013-10-14</td>
      <td>2013</td>
      <td>10</td>
      <td>14</td>
    </tr>
  </tbody>
</table>
</div>



Convert the aisin column from string to numeric.


```python
df["asin"] = df["asin"].convert_objects(convert_numeric=True)
#df['asin']=  df["asin"].astype(str).astype(float)
```

The summary statistics  for the numeric columns from the dataset is shown below: 


```python
df.describe()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>asin</th>
      <th>overall</th>
      <th>unixReviewTime</th>
      <th>year</th>
      <th>month</th>
      <th>day</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>2.114000e+03</td>
      <td>500176.000000</td>
      <td>5.001760e+05</td>
      <td>500176.000000</td>
      <td>500176.000000</td>
      <td>500176.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>1.472931e+09</td>
      <td>4.244350</td>
      <td>1.344561e+09</td>
      <td>2012.151987</td>
      <td>6.001763</td>
      <td>15.543731</td>
    </tr>
    <tr>
      <th>std</th>
      <td>1.336889e+09</td>
      <td>1.203374</td>
      <td>6.487853e+07</td>
      <td>2.095034</td>
      <td>3.623264</td>
      <td>8.794805</td>
    </tr>
    <tr>
      <th>min</th>
      <td>6.428320e+06</td>
      <td>1.000000</td>
      <td>8.934624e+08</td>
      <td>1998.000000</td>
      <td>1.000000</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>7.678510e+08</td>
      <td>4.000000</td>
      <td>1.325030e+09</td>
      <td>2011.000000</td>
      <td>3.000000</td>
      <td>8.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>1.417030e+09</td>
      <td>5.000000</td>
      <td>1.364342e+09</td>
      <td>2013.000000</td>
      <td>6.000000</td>
      <td>15.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>1.417030e+09</td>
      <td>5.000000</td>
      <td>1.388189e+09</td>
      <td>2013.000000</td>
      <td>9.000000</td>
      <td>23.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>9.868239e+09</td>
      <td>5.000000</td>
      <td>1.406074e+09</td>
      <td>2014.000000</td>
      <td>12.000000</td>
      <td>31.000000</td>
    </tr>
  </tbody>
</table>
</div>




```python
df.shape
```




    (500176, 13)



The columns which are to build the reccomender system are  the reviewer/user ID, the ID of the product aisin and the item rating (overall). We can rename some of the columns to a lot recognizable and select the columns which are needed to build our reccomender system.


```python
df.isnull().sum()
```




    asin              498062
    helpful                0
    overall                0
    reviewText             0
    reviewTime             0
    reviewerID             0
    reviewerName        2586
    summary                0
    unixReviewTime         0
    Date_Time              0
    year                   0
    month                  0
    day                    0
    dtype: int64




```python
df.rename(columns={'reviewerID': 'UserID', 'overall': 'rating','asin':'ItemID'}, inplace=True)
df.head(3)
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>ItemID</th>
      <th>helpful</th>
      <th>rating</th>
      <th>reviewText</th>
      <th>reviewTime</th>
      <th>UserID</th>
      <th>reviewerName</th>
      <th>summary</th>
      <th>unixReviewTime</th>
      <th>Date_Time</th>
      <th>year</th>
      <th>month</th>
      <th>day</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>6428320.0</td>
      <td>[0, 0]</td>
      <td>3.0</td>
      <td>The portfolio is fine except for the fact that...</td>
      <td>03 11, 2014</td>
      <td>A1YS9MDZP93857</td>
      <td>John Taylor</td>
      <td>Parts missing</td>
      <td>1394496000</td>
      <td>2014-03-11</td>
      <td>2014</td>
      <td>3</td>
      <td>11</td>
    </tr>
    <tr>
      <th>1</th>
      <td>14072149.0</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>If you are a serious violin student on a budge...</td>
      <td>06 6, 2013</td>
      <td>A3TS466QBAWB9D</td>
      <td>Silver Pencil</td>
      <td>Perform it with a friend, today!</td>
      <td>1370476800</td>
      <td>2013-06-06</td>
      <td>2013</td>
      <td>6</td>
      <td>6</td>
    </tr>
    <tr>
      <th>2</th>
      <td>41291905.0</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>This is and excellent edition and perfectly tr...</td>
      <td>10 14, 2013</td>
      <td>A3BUDYITWUSIS7</td>
      <td>joyce gabriel cornett</td>
      <td>Vivalldi's Four Seasons</td>
      <td>1381708800</td>
      <td>2013-10-14</td>
      <td>2013</td>
      <td>10</td>
      <td>14</td>
    </tr>
  </tbody>
</table>
</div>




```python
dff=df[['UserID', 'ItemID', 'rating']]
dff.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>UserID</th>
      <th>ItemID</th>
      <th>rating</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>A1YS9MDZP93857</td>
      <td>6428320.0</td>
      <td>3.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>A3TS466QBAWB9D</td>
      <td>14072149.0</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>A3BUDYITWUSIS7</td>
      <td>41291905.0</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>A19K10Z0D2NTZK</td>
      <td>41913574.0</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>A14X336IB4JD89</td>
      <td>201891859.0</td>
      <td>1.0</td>
    </tr>
  </tbody>
</table>
</div>



We create a SparkSession then import the recommendation system and evaluation algorithms. SparkSessions were introduced in Spark 2.0.The SparkContext is no longer needed to start a session since the sparkSession creates a SparkContext,SpankConf and SparkContext.



```python
from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('ALSRecommenderSystem').getOrCreate()
from pyspark.ml.recommendation import ALS
from pyspark.ml.evaluation import RegressionEvaluator
```

We can create a Spark DataFrame below by converting the pandas dataframe to spark dataframe, alternative we could have imported the data straight as a Spark DataFrame with spark.read.csv('/file path', inferSchema=True, header=True)


```python
DF=spark.createDataFrame(dff)
```


```python
DF.show(4)
```

    +--------------+-----------+------+
    |        UserID|     ItemID|rating|
    +--------------+-----------+------+
    |A1YS9MDZP93857|  6428320.0|   3.0|
    |A3TS466QBAWB9D|1.4072149E7|   5.0|
    |A3BUDYITWUSIS7|4.1291905E7|   5.0|
    |A19K10Z0D2NTZK|4.1913574E7|   5.0|
    +--------------+-----------+------+
    only showing top 4 rows
    


DF.describe() function produces the summary statistics from the data. There are about 157836 observations. The mean rating is about 4.3. The rating ranges from 1 to 5. The toPandas() function converts the summary statistic output into a pandas dataframe which is pretty.



```python
DF.describe().toPandas()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>summary</th>
      <th>UserID</th>
      <th>ItemID</th>
      <th>rating</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>count</td>
      <td>500176</td>
      <td>500176</td>
      <td>500176</td>
    </tr>
    <tr>
      <th>1</th>
      <td>mean</td>
      <td>None</td>
      <td>NaN</td>
      <td>4.244349988803941</td>
    </tr>
    <tr>
      <th>2</th>
      <td>stddev</td>
      <td>None</td>
      <td>NaN</td>
      <td>1.2033741013944728</td>
    </tr>
    <tr>
      <th>3</th>
      <td>min</td>
      <td>A0002382258OFJJ2UYNTR</td>
      <td>6428320.0</td>
      <td>1.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>max</td>
      <td>AZZZTAPYKI9RD</td>
      <td>NaN</td>
      <td>5.0</td>
    </tr>
  </tbody>
</table>
</div>




```python
DF.printSchema()
```

    root
     |-- UserID: string (nullable = true)
     |-- ItemID: double (nullable = true)
     |-- rating: double (nullable = true)
    



```python
DF.select('UserID').distinct().show(5)
```

    +--------------+
    |        UserID|
    +--------------+
    | A1KP0BRI68RCN|
    |A3W0PTHD219LXE|
    |A165QTRGCJVCZZ|
    |A140XH16IKR4B0|
    | AT9557I2MAJKU|
    +--------------+
    only showing top 5 rows
    



```python
from pyspark.sql.functions import countDistinct, avg, stddev

DF.select(countDistinct('UserID')).show()
```

    +----------------------+
    |count(DISTINCT UserID)|
    +----------------------+
    |                339231|
    +----------------------+
    


**Convert string type columns to numeric**

The ML library accepts only numeric input


```python
DF=DF.withColumn("itemId", DF["ItemID"].cast("int"))
```


```python
#DF=DF.withColumn("userId", DF["userId"].cast("int"))
```


```python
DF.printSchema()
```

    root
     |-- UserID: string (nullable = true)
     |-- itemId: integer (nullable = true)
     |-- rating: double (nullable = true)
    


**convert categorical data to numerical data in Pyspark**

Since the pyspark ML accepts only numeric input, we shall convert the UserID from string type to numeric. Each UserID will be converted to a unique numeric ID number.


```python
from pyspark.sql.functions import *
from pyspark.ml import Pipeline
from pyspark.ml.feature import StringIndexer
indexer = StringIndexer(inputCol="UserID", outputCol="moduserID")
DFF = indexer.fit(DF).transform(DF)
```


```python
DFF=DFF.withColumn("moduserID", DFF["moduserID"].cast("int"))
DFF=DFF.withColumn("itemId", DFF["itemId"].cast("int"))
```


```python
DFF.printSchema()
```

    root
     |-- UserID: string (nullable = true)
     |-- itemId: integer (nullable = true)
     |-- rating: double (nullable = true)
     |-- moduserID: integer (nullable = true)
    



```python
DFF.show(4)
```

    +--------------+--------+------+---------+
    |        UserID|  itemId|rating|moduserID|
    +--------------+--------+------+---------+
    |A1YS9MDZP93857| 6428320|   3.0|     5092|
    |A3TS466QBAWB9D|14072149|   5.0|    15198|
    |A3BUDYITWUSIS7|41291905|   5.0|    50865|
    |A19K10Z0D2NTZK|41913574|   5.0|   309908|
    +--------------+--------+------+---------+
    only showing top 4 rows
    


rename the columns with farmiliar column names


```python
#DFF = DFF.drop('UserID')
DFF= DFF.select(['moduserID', 'itemId', 'rating'])
DFF = DFF.select(col("moduserID").alias("userId"),col("itemId").alias("itemId"),col("rating").alias("rating"))
```

**Training the Model and Making Predictions**

To train the model and make predictions, we need a training and an evaluation set. Here the training set is 80% of randomly selected samples and the rest are for evaluation.

Note that because the split is random and there is no random state parameter as in Scikit-Learn these results will not be exactly reproducible.


```python
DFF.show(3)
```

    +------+--------+------+
    |userId|  itemId|rating|
    +------+--------+------+
    |  5092| 6428320|   3.0|
    | 15198|14072149|   5.0|
    | 50865|41291905|   5.0|
    +------+--------+------+
    only showing top 3 rows
    



```python
DFF.printSchema()
```

    root
     |-- userId: integer (nullable = true)
     |-- itemId: integer (nullable = true)
     |-- rating: double (nullable = true)
    


#### Check for missing values

We can check for which columns have missing values in the spark dataframe as shown below. Handling missing data in machine learning is an important subject. The basic approach include deleting ,mean and median imputation for continuous and categorical variables respectively.


```python
from pyspark.sql.functions import col,sum
DFF.select(*(sum(col(c).isNull().cast("int")).alias(c) for c in DFF.columns)).show()
```

    +------+------+------+
    |userId|itemId|rating|
    +------+------+------+
    |     0|     0|     0|
    +------+------+------+
    


Equivalently,


```python
from pyspark.sql.functions import lit

rows = DFF.count()
summary = DFF.describe().filter(col("summary") == "count")
summary.select(*((lit(rows)-col(c)).alias(c) for c in DFF.columns)).show()
```

    +------+------+------+
    |userId|itemId|rating|
    +------+------+------+
    |   0.0|   0.0|   0.0|
    +------+------+------+
    


Suppose the column itemId contained missing observations and we wanted to delete the
rows with NA values based on this column, we would as follows :


```python
DFF.na.drop(subset=["itemId"])
```




    DataFrame[userId: int, itemId: int, rating: double]




```python
DFF.describe().toPandas()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>summary</th>
      <th>userId</th>
      <th>itemId</th>
      <th>rating</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>count</td>
      <td>500176</td>
      <td>500176</td>
      <td>500176</td>
    </tr>
    <tr>
      <th>1</th>
      <td>mean</td>
      <td>121011.79597581651</td>
      <td>5211427.368528278</td>
      <td>4.244349988803941</td>
    </tr>
    <tr>
      <th>2</th>
      <td>stddev</td>
      <td>107725.35618017272</td>
      <td>8.37320292264631E7</td>
      <td>1.2033741013944728</td>
    </tr>
    <tr>
      <th>3</th>
      <td>min</td>
      <td>0</td>
      <td>0</td>
      <td>1.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>max</td>
      <td>339230</td>
      <td>2147483647</td>
      <td>5.0</td>
    </tr>
  </tbody>
</table>
</div>



Split the dataframe into 75% for training and 25% as the test set.


```python
training, test = DFF.randomSplit([0.75,0.25])
```

The following line creates the alternating least squares model. Then the model is fitted with the training data and predictions are made on the test set. The alternating least squares is similar to regular least squares. Inalternating least squares, the objective function is minimized by holding other varaibles constant except one at each time. By holding all other variables constant except one, the minimization reduces to something similar to least squares.


```python
als = ALS(maxIter=5, regParam=0.01, userCol='userId', itemCol='itemId', ratingCol='rating')

model = als.fit(training)

predictions = model.transform(test)
```


To prevent the mean squared error producing NaN we drop any NaN which may be present in 
the predictions .


```python
predictions.describe().toPandas()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>summary</th>
      <th>userId</th>
      <th>itemId</th>
      <th>rating</th>
      <th>rating_scaled</th>
      <th>prediction</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>count</td>
      <td>51493</td>
      <td>51493</td>
      <td>51493</td>
      <td>51493</td>
      <td>51493</td>
    </tr>
    <tr>
      <th>1</th>
      <td>mean</td>
      <td>20876.33086050531</td>
      <td>1690542.568349096</td>
      <td>4.351873070126037</td>
      <td>0.08935133405110446</td>
      <td>0.08461853259996296</td>
    </tr>
    <tr>
      <th>2</th>
      <td>stddev</td>
      <td>20011.651527771326</td>
      <td>4.695574783695837E7</td>
      <td>1.0662019165643304</td>
      <td>0.8860103564874956</td>
      <td>0.7040405588438029</td>
    </tr>
    <tr>
      <th>3</th>
      <td>min</td>
      <td>0</td>
      <td>0</td>
      <td>1.0</td>
      <td>-2.696044384738196</td>
      <td>-2.6432934</td>
    </tr>
    <tr>
      <th>4</th>
      <td>max</td>
      <td>68314</td>
      <td>2147483647</td>
      <td>5.0</td>
      <td>0.6279427239795259</td>
      <td>0.62812227</td>
    </tr>
  </tbody>
</table>
</div>




```python
predictions = predictions.na.drop()
```

Evaluation
Add the mean subracted earlier during standardizing and add multiply
the variance dividing to scale.


```python

evaluator = RegressionEvaluator(metricName='rmse', labelCol='rating')
rmse = evaluator.evaluate(predictions)
rmse
```




    1.436062196037978


