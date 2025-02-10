---
layout: post
title: Hyperparameter Tuning  The Alternating Least-Squares Algorithm for A Recommender System. 
subtitle: Personalized Recommendation with Matrix Factorization 
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [spark,pyspark,matrix factorization, Alternating Least Squares]
---




### Colaborative Filtering :  Hyperparameter Tuning Alternating Least Squares Algorithm



Collaborative filtering is commonly used for recommender systems.
This can be formulated as a learning problem in which we are given the ratings
that users have given certain items and are tasked with predicting their ratings for the rest of the items. A user-item matrix can be constructed as follows:
Given n users and m items,  an n . m matrix A  in which the
(u; i)th entry is r_ui { the rating for item i by user u}. The matrix A has many unobserved ratings which is represented as missing ratings.

The following packages are required  for analysis in this post.They are loaded below.


```python
%matplotlib inline
import pandas as pd
import gzip
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
import multiprocessing
from pyspark.sql.types import IntegerType, FloatType, LongType, DateType, ArrayType
from pyspark.sql.window import Window
from pyspark.sql.types import *
import datetime
import pyarrow as pa
from pyspark import SparkConf, Row
from pyspark.sql.functions import desc
from pyspark.sql.functions import col
from pyspark.sql.functions import *
import glob
from pyspark.ml.recommendation import ALS
from pyspark.ml.evaluation import RegressionEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder, TrainValidationSplit
from pyspark.mllib.recommendation import ALS, MatrixFactorizationModel, Rating
from pyspark.context import SparkContext
from pyspark.serializers import MarshalSerializer
pd.set_option('display.max_rows',500)
pd.set_option('display.max_columns',500)
pd.set_option('display.width',1000)
pd.set_option('display.max_columns',500)
```


```python
path='/PythonRecommenderSystem'


# Check current working directory.
retval = os.getcwd()
print ("Current working directory %s" % retval)

# Now change the directory
os.chdir( path )

# Check current working directory.
retval = os.getcwd()

print("Directory changed successfully %s" % retval)

multiprocessing.cpu_count()
pool = multiprocessing.Pool(processes=multiprocessing.cpu_count()-1)

import multiprocessing as mp

# Step 1: Init multiprocessing.Pool()
pool = mp.Pool(mp.cpu_count())
```

    Current working directory /SparkPython2
    Directory changed successfully /PythonRecommenderSystem


The Digital Music review dataset from the Amazon product dataset used in this work can be found [here](http://jmcauley.ucsd.edu/data/amazon/links.html)
.This dataset contains didgital music reviews and metadata from Amazon, including 142.8 million reviews spanning May 1996 - July 2014.
This dataset includes reviews (ratings, text, helpfulness votes), product metadata (descriptions, category information, price, brand, and image features), and links (also viewed/also bought graphs).The discription of the dataset is as follows:

* reviewerID - ID of the reviewer, e.g. A2SUAM1J3GNN3B 
* asin - ID of the product, e.g. 0000013714
* reviewerName - name of the reviewer
* helpful - helpfulness rating of the review, e.g. 2/3
* reviewText - text of the review
* overall - rating of the product
* summary - summary of the review
* unixReviewTime - time of the review (unix time)
* reviewTime - time of the review (raw)

Import the data downloaded from the amazon site as below.


```python
import json

Digital_Music = []
for line in open('reviews_Digital_Music.json', 'r'):
    Digital_Music.append(json.loads(line))
```


```python
df=pd.DataFrame(Digital_Music)
#we will randomly sample about 20% of our available data to 
#reduce the computational time and cost
df=df.sample(frac=0.2, replace=False, random_state=1)
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
      <th>82875</th>
      <td>B00000581T</td>
      <td>[2, 5]</td>
      <td>5.0</td>
      <td>This album is outstanding, from beginning to e...</td>
      <td>11 11, 2000</td>
      <td>ASSY7Q8GQCQC4</td>
      <td>HM</td>
      <td>Outstanding</td>
      <td>973900800</td>
    </tr>
    <tr>
      <th>612792</th>
      <td>B005X5LADS</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>I heard a selection from this cd on Pandora an...</td>
      <td>08 22, 2013</td>
      <td>A33URADTU6RTSY</td>
      <td>J. Malone</td>
      <td>Truly relaxing music --</td>
      <td>1377129600</td>
    </tr>
    <tr>
      <th>573729</th>
      <td>B004UP3T2C</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>All time hit! Takes you right back to a summer...</td>
      <td>11 10, 2012</td>
      <td>A1SNCP893TLCWT</td>
      <td>GhostDust1863</td>
      <td>great song</td>
      <td>1352505600</td>
    </tr>
  </tbody>
</table>
</div>



check the class of each column variable


```python
df.info()
```

    <class 'pandas.core.frame.DataFrame'>
    Int64Index: 167201 entries, 82875 to 522564
    Data columns (total 9 columns):
    asin              167201 non-null object
    helpful           167201 non-null object
    overall           167201 non-null float64
    reviewText        167201 non-null object
    reviewTime        167201 non-null object
    reviewerID        167201 non-null object
    reviewerName      166737 non-null object
    summary           167201 non-null object
    unixReviewTime    167201 non-null int64
    dtypes: float64(1), int64(1), object(7)
    memory usage: 12.8+ MB


Convert the aisin column from string to numeric.


```python
#df["asin"] = df["asin"].convert_objects(convert_numeric=True)
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
      <th>overall</th>
      <th>unixReviewTime</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>167201.000000</td>
      <td>1.672010e+05</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>4.539823</td>
      <td>1.296173e+09</td>
    </tr>
    <tr>
      <th>std</th>
      <td>0.960933</td>
      <td>1.266856e+08</td>
    </tr>
    <tr>
      <th>min</th>
      <td>1.000000</td>
      <td>8.931168e+08</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>4.000000</td>
      <td>1.245197e+09</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>5.000000</td>
      <td>1.358294e+09</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>5.000000</td>
      <td>1.381104e+09</td>
    </tr>
    <tr>
      <th>max</th>
      <td>5.000000</td>
      <td>1.406074e+09</td>
    </tr>
  </tbody>
</table>
</div>




```python
df.shape
```




    (167201, 9)



The columns which are to build the reccomender system are  the reviewer/user ID, the ID of the product aisin and the item rating (overall). We can rename some of the columns to a lot recognizable and select the columns which are needed to build our reccomender system.


```python
df.isnull().sum()
```




    asin                0
    helpful             0
    overall             0
    reviewText          0
    reviewTime          0
    reviewerID          0
    reviewerName      464
    summary             0
    unixReviewTime      0
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
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>82875</th>
      <td>B00000581T</td>
      <td>[2, 5]</td>
      <td>5.0</td>
      <td>This album is outstanding, from beginning to e...</td>
      <td>11 11, 2000</td>
      <td>ASSY7Q8GQCQC4</td>
      <td>HM</td>
      <td>Outstanding</td>
      <td>973900800</td>
    </tr>
    <tr>
      <th>612792</th>
      <td>B005X5LADS</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>I heard a selection from this cd on Pandora an...</td>
      <td>08 22, 2013</td>
      <td>A33URADTU6RTSY</td>
      <td>J. Malone</td>
      <td>Truly relaxing music --</td>
      <td>1377129600</td>
    </tr>
    <tr>
      <th>573729</th>
      <td>B004UP3T2C</td>
      <td>[0, 0]</td>
      <td>5.0</td>
      <td>All time hit! Takes you right back to a summer...</td>
      <td>11 10, 2012</td>
      <td>A1SNCP893TLCWT</td>
      <td>GhostDust1863</td>
      <td>great song</td>
      <td>1352505600</td>
    </tr>
  </tbody>
</table>
</div>



These three columns are what is of interest in our collaborative filtering task.


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
      <th>82875</th>
      <td>ASSY7Q8GQCQC4</td>
      <td>B00000581T</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>612792</th>
      <td>A33URADTU6RTSY</td>
      <td>B005X5LADS</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>573729</th>
      <td>A1SNCP893TLCWT</td>
      <td>B004UP3T2C</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>470228</th>
      <td>A2WL6QTD4CZWD2</td>
      <td>B002P9WOMQ</td>
      <td>5.0</td>
    </tr>
    <tr>
      <th>261494</th>
      <td>A11J6JC55R633N</td>
      <td>B000TEEA1M</td>
      <td>5.0</td>
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

    +--------------+----------+------+
    |        UserID|    ItemID|rating|
    +--------------+----------+------+
    | ASSY7Q8GQCQC4|B00000581T|   5.0|
    |A33URADTU6RTSY|B005X5LADS|   5.0|
    |A1SNCP893TLCWT|B004UP3T2C|   5.0|
    |A2WL6QTD4CZWD2|B002P9WOMQ|   5.0|
    +--------------+----------+------+
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
      <td>167201</td>
      <td>167201</td>
      <td>167201</td>
    </tr>
    <tr>
      <th>1</th>
      <td>mean</td>
      <td>None</td>
      <td>5.963927389565217E9</td>
      <td>4.539823326415512</td>
    </tr>
    <tr>
      <th>2</th>
      <td>stddev</td>
      <td>None</td>
      <td>9.090571950387818E8</td>
      <td>0.9609327057388072</td>
    </tr>
    <tr>
      <th>3</th>
      <td>min</td>
      <td>A00167062N853P9T0TEJ5</td>
      <td>5555991584</td>
      <td>1.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>max</td>
      <td>AZZZF6NKJ4QYV</td>
      <td>B00LWJDZHI</td>
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
     |-- ItemID: string (nullable = true)
     |-- rating: double (nullable = true)
    



```python
DF.select('UserID').distinct().show(5)
```

    +--------------+
    |        UserID|
    +--------------+
    |A3A7F8AQMAVFGN|
    |A1Z6W412RO5156|
    |A14B6M7JU3JSMZ|
    |A2Z9L0JK0XRS61|
    |A33RII6U1H9EV9|
    +--------------+
    only showing top 5 rows
    



```python
from pyspark.sql.functions import countDistinct, avg, stddev

DF.select(countDistinct('UserID')).show()
```

    +----------------------+
    |count(DISTINCT UserID)|
    +----------------------+
    |                130379|
    +----------------------+
    


**Convert string type columns to numeric**

The ML library accepts only numeric input


```python
#DF=DF.withColumn("itemId", DF["ItemID"].cast("int"))
```


```python
#DF=DF.withColumn("userId", DF["userId"].cast("int"))
```


```python
DF.printSchema()
```

    root
     |-- UserID: string (nullable = true)
     |-- ItemID: string (nullable = true)
     |-- rating: double (nullable = true)
    


**convert categorical data to numerical data in Pyspark**

Since the pyspark ML accepts only numeric input, we shall convert the UserID from string type to numeric. Each UserID will be converted to a unique numeric ID number.The Stringindexer function in Spark ML can be used for this converting many columns from string to numeric at the same time.


```python
from pyspark.sql.functions import *
from pyspark.ml import Pipeline
from pyspark.ml.feature import StringIndexer
#indexer = StringIndexer(inputCol="UserID", outputCol="moduserID")
#DFF = indexer.fit(DF).transform(DF)
```


```python

indexers = [StringIndexer(inputCol=column, outputCol=column+"_index").fit(DF) for column in list(set(DF.columns)-set(['rating']))]


pipeline = Pipeline(stages=indexers)
DFF = pipeline.fit(DF).transform(DF)

DFF.show(5)
```

    +--------------+----------+------+------------+------------+
    |        UserID|    ItemID|rating|UserID_index|ItemID_index|
    +--------------+----------+------+------------+------------+
    | ASSY7Q8GQCQC4|B00000581T|   5.0|     45352.0|      8956.0|
    |A33URADTU6RTSY|B005X5LADS|   5.0|    107082.0|      6347.0|
    |A1SNCP893TLCWT|B004UP3T2C|   5.0|    127045.0|      5391.0|
    |A2WL6QTD4CZWD2|B002P9WOMQ|   5.0|     87818.0|     31360.0|
    |A11J6JC55R633N|B000TEEA1M|   5.0|     35016.0|     60263.0|
    +--------------+----------+------+------------+------------+
    only showing top 5 rows
    



```python
#DFF=DFF.withColumn("moduserID", DFF["moduserID"].cast("int"))
#DFF=DFF.withColumn("itemId", DFF["itemId"].cast("int"))
```


```python
DFF.printSchema()
```

    root
     |-- UserID: string (nullable = true)
     |-- ItemID: string (nullable = true)
     |-- rating: double (nullable = true)
     |-- UserID_index: double (nullable = false)
     |-- ItemID_index: double (nullable = false)
    


Select the three columns for our analysis and rename the columns with farmiliar column names


```python
#DFF = DFF.drop('UserID')
#DFF= DFF.select(['moduserID', 'itemId', 'rating'])
DFF = DFF.select(col("UserID_index").alias("userId"),col("ItemID_index").alias("itemId"),col("rating"))
```

**Training the Model and Making Predictions**

To train the model and make predictions, we need a training and an evaluation set. Here the training set is 80% of randomly selected samples and the rest are for evaluation.

Note that because the split is random and there is no random state parameter as in Scikit-Learn these results will not be exactly reproducible.


```python
DFF.show(3)
```

    +--------+------+------+
    |  userId|itemId|rating|
    +--------+------+------+
    | 45352.0|8956.0|   5.0|
    |107082.0|6347.0|   5.0|
    |127045.0|5391.0|   5.0|
    +--------+------+------+
    only showing top 3 rows
    


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




    DataFrame[userId: double, itemId: double, rating: double]




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
      <td>167201</td>
      <td>167201</td>
      <td>167201</td>
    </tr>
    <tr>
      <th>1</th>
      <td>mean</td>
      <td>51996.47661198198</td>
      <td>21262.852022416133</td>
      <td>4.539823326415512</td>
    </tr>
    <tr>
      <th>2</th>
      <td>stddev</td>
      <td>41561.27675663137</td>
      <td>24994.03017898536</td>
      <td>0.9609327057388072</td>
    </tr>
    <tr>
      <th>3</th>
      <td>min</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>max</td>
      <td>130378.0</td>
      <td>81077.0</td>
      <td>5.0</td>
    </tr>
  </tbody>
</table>
</div>



The following line creates the alternating least squares model. Then the model is fitted with the training data and predictions are made on the test set. The alternating least squares is similar to regular least squares. Inalternating least squares, the objective function is minimized by holding other varaibles constant except one at each time. By holding all other variables constant except one, the minimization reduces to something similar to least squares.

#### Hyperparameter Tuning

The following parameters in the ALS are to be tuned. The paper Large- Scale Parallel  Colaborative Filtering for the Netflix Price is available on this link [here](https://github.com/tolleiv/thesis/blob/master/Research/Papers/__Zhou08%20-%20Large-scale%20Parallel%20Collaborative%20Filtering%20for%20the%20Netflix%20Prize.pdf). For a detailed explanation of the model, reading through the paper would be appropriate.

**numBlocks** is the number of blocks the users and items will be partitioned into in order to parallelize computation (defaults to 10).

**rank** is the number of latent factors in the model (defaults to 10).

**maxIter** is the maximum number of iterations to run (defaults to 10).

**regParam** specifies the regularization parameter in ALS (defaults to 1.0).

**implicitPrefs** specifies whether to use the explicit feedback ALS variant or one adapted for implicit feedback data (defaults to false which means using explicit feedback).

**alpha** is a parameter applicable to the implicit feedback variant of ALS that governs the baseline confidence in preference observations (defaults to 1.0).


#### Explicit vs. implicit feedback

The standard approach to matrix factorization based collaborative filtering treats the entries in the user-item matrix as explicit preferences given by the user to the item, for example, users giving ratings to a product. Explicit preferencces are always not available.Inplicit preferences which can be inferred from numbers representing the strength in observations of user actions can be used instead.Example of inplicit feedback/preferences include views, clicks, purchases, likes, shares etc.


#### Scaling of the regularization parameter
The regularization   parameter regParam is scaled in solving each least squares problem by the number of ratings the user generated in updating user factors, or the number of ratings the product received in updating product factors. This makes regParam less dependent on the scale of the dataset, allowing the best parameter learned from a sampled subset to be applied to the full dataset and expect similar performance.

#### Cold-start strategy
The cold-start problem arises in colaborative filtering prediction when we encouter users/items  with no prior  rating history in our training set. The default behavior of the spark ALS model is to assign NaN values as predictions in such situation.Spark allows users to set the coldStartStrategy parameter to "drop" in order to drop any rows in the DataFrame of predictions that contain NaN values. The evaluation metric will then be computed over the non-NaN data and will be valid.

#### Two standardizing Approaches

We demonstrate two standardization approaches, the min-max and normalization. The normalization approach is what we apply on the target variable ratings.


```python
mean_rating, sttdev_rating = DFF.select(mean("rating"), stddev("rating")).first()

max_rating,min_rating = DFF.select(max("rating"), min("rating")).first()


DFF=DFF.withColumn("rating_Normalized", (col("rating") - mean_rating) / sttdev_rating)

DFF=DFF.withColumn("rating_minmax", (col("rating") - min_rating) /(max_rating-min_rating))



DFF.show(5)
```

    +--------+-------+------+------------------+-------------+
    |  userId| itemId|rating| rating_Normalized|rating_minmax|
    +--------+-------+------+------------------+-------------+
    | 45352.0| 8956.0|   5.0|0.4788854316605702|          1.0|
    |107082.0| 6347.0|   5.0|0.4788854316605702|          1.0|
    |127045.0| 5391.0|   5.0|0.4788854316605702|          1.0|
    | 87818.0|31360.0|   5.0|0.4788854316605702|          1.0|
    | 35016.0|60263.0|   5.0|0.4788854316605702|          1.0|
    +--------+-------+------+------------------+-------------+
    only showing top 5 rows
    



```python
DFF.select(max("rating")).first()[0]
```




    5.0




```python
train, test = DFF.randomSplit([0.8, 0.2], seed=12345)

ALSExplicit = ALS( implicitPrefs=False, userCol="userId", itemCol="itemId", ratingCol="rating_minmax",
          coldStartStrategy="drop")

defaultModel = ALSExplicit.fit(train)

```


```python

# A CrossValidator requires an Estimator, a set of Estimator ParamMaps, and an Evaluator.
# We use a ParamGridBuilder to construct a grid of parameters to search over.
# With 2 values for rank and 2 values for regParam, 2 values for maxIter,2 values for alpha
# this grid will have 2 x 2 x 2 x 2 = 16 parameter settings for CrossValidator to choose from.

paramMapExplicit = ParamGridBuilder() \
                    .addGrid(ALSExplicit.rank, [ 8, 12]) \
                    .addGrid(ALSExplicit.maxIter, [5,10]) \
                    .addGrid(ALSExplicit.regParam, [0.01,0.001]) \
                    .addGrid(ALSExplicit.alpha, [2.0,3.0]) \
                    .build()

evaluatorR = RegressionEvaluator(metricName="rmse", labelCol="rating_minmax")


# Run cross-validation, and choose the best set of parameters.
CVALSExplicit = CrossValidator(estimator=ALSExplicit,
                            estimatorParamMaps=paramMapExplicit,
                            evaluator=evaluatorR,
                           numFolds=5)


CVModelEXplicit = CVALSExplicit.fit(train)
```


```python
# Make predictions on test documents. cvModel uses the best model found (cvModelInplicit).
predsExplicit = CVModelEXplicit.bestModel.transform(test)


predictions=predsExplicit.withColumn("predictnew", ((max_rating-min_rating)*col("prediction") + min_rating) )


predictions =predictions.select([c for c in predictions.columns if c not in {'rating_Normalized','rating_minmax','prediction'}])

predictions.show(5)
```

    +------+------+------+-------------------+
    |userId|itemId|rating|         predictnew|
    +------+------+------+-------------------+
    |1562.0| 148.0|   4.0| 1.3738184571266174|
    | 357.0| 148.0|   5.0| 1.4132280349731445|
    |5678.0| 463.0|   4.0| 1.5864256620407104|
    |2144.0| 463.0|   4.0| 1.6909311413764954|
    |3369.0| 471.0|   5.0| 2.3148409128189087|
    +------+------+------+-------------------+
    only showing top 5 rows
    


We convert back normalized predictions back to its original  interval between 1 and 5. The standardization to mean of 0  and standard deviation of 1 narrows the prediction prediction interval and thereby improves the quality of the predictions from the model.


```python
# Evaluate the model by computing the RMSE on the test data

evaluator = RegressionEvaluator(metricName="rmse", labelCol="rating",
                                predictionCol="predictnew")
rmse = evaluator.evaluate(predictions)

print("Root-mean-square error is {}".format(rmse))
```

    Root-mean-square error is 3.7312300283404176



```python
# Generate top 10 digital music recommendations for each user
userRecs = CVModelEXplicit.bestModel.recommendForAllUsers(10)
# Generate top 10 user recommendations for each digital music
DigitalMusicRecs = CVModelEXplicit.bestModel.recommendForAllItems(10)

userRecs.show(10)
```

    +------+--------------------+
    |userId|     recommendations|
    +------+--------------------+
    |   148|[[2788, 1.3300879...|
    |   463|[[1289, 1.3111275...|
    |   471|[[3575, 1.153979]...|
    |   496|[[2079, 1.925576]...|
    |   833|[[1572, 1.4387902...|
    |  1088|[[1457, 1.3470203...|
    |  1238|[[3472, 1.164058]...|
    |  1342|[[1422, 1.4752936...|
    |  1580|[[3077, 1.4021921...|
    |  1591|[[1001, 1.54133],...|
    +------+--------------------+
    only showing top 10 rows
    


#### Single Prediction
A prediction for a single userId and itemId can be generated as follows:


```python
d = {'userId': [0], 'itemId': [2875]}
df = pd.DataFrame(data=d)
df2=spark.createDataFrame(df)

single_pred=CVModelEXplicit.bestModel.transform(df2)

single_pred.withColumn("prediction", (sttdev_rating*col("prediction") + mean_rating) ).show()


```

    +------+------+-----------------+
    |userId|itemId|       prediction|
    +------+------+-----------------+
    |     0|  2875|4.540941984998424|
    +------+------+-----------------+
    


#### Save Models


```python
#save to folder models which is created in the writing process
#folder models must not already be present
path="/PythonRecommenderSystem/models"


model = CVModelEXplicit
model.write().overwrite().save(path)


#load the model 

sameModel = CVModelEXplicit.load(path)
sameModel
```




    CrossValidatorModel_0ed894fbc20d




```python
#stop the spark cluster here
pool.close()
spark.stop()
```
