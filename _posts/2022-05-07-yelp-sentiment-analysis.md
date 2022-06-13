---

<center> <h2> <span style='color:#DF7F00'> Yelp Sentiment Analysis </span> </h2> </center>

---

In this [Jupyter Notebook](https://jupyter.org/install) do sentiment analysis on restaurant reviews from **Yelp!**.

Natural language processing is the area of study that focus on text and voice recognizion and extracting useful information from sentences.

In this project, we will go through the processing of [restaurant reviews from Yelp!](https://archive-beta.ics.uci.edu/ml/datasets/sentiment+labelled+sentences), converting sentences to numerical variables, removing [stop words](https://en.wikipedia.org/wiki/Stop_word), and selecting the most "important" words using the [TF-IDF](https://en.wikipedia.org/wiki/Tf%E2%80%93idf) method.

For the modeling part, we will see the effect of selection different levels of [n-grams](https://en.wikipedia.org/wiki/N-gram), and test different machine learning models.

The first step is to load the libraries we will use during the webinar.


```python
# Core libraries
import pandas as pd
import numpy as np

# NLP
import nltk.corpus
nltk.download("stopwords")
from nltk.corpus import stopwords

# Visualization
from wordcloud import WordCloud
import matplotlib.pyplot as plt

# Machine Learning
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
```

    [nltk_data] Downloading package stopwords to
    [nltk_data]     /Users/leonardoqueiroz/nltk_data...
    [nltk_data]   Package stopwords is already up-to-date!


Loading the data. It is a `txt` file, not a `csv`, and the columns are separated by a `tab`. We can load it using the `pd.read_csv` and set the separation argument to `"\t"`.


```python
reviews = pd.read_csv("data.csv")
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>995</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>996</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>997</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>998</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>999</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
<p>1000 rows × 2 columns</p>
</div>




```python
reviews.rename(columns = {0 : "Review", 1 : "Sentiment"}, inplace = True)
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>995</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>996</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>997</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>998</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>999</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
<p>1000 rows × 2 columns</p>
</div>



Checking some reviews:


```python
reviews.loc[500, "Review"]
```




    "I also had to taste my Mom's multi-grain pumpkin pancakes with pecan butter and they were amazing, fluffy, and delicious!"



## Initial data analysis

Checking for duplicated rows:


```python
reviews.duplicated().sum()
```




    4



There are duplicated rows. Let's check them:


```python
reviews[reviews.duplicated(keep = False) == True]
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
      <th>Review</th>
      <th>Sentiment</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>334</th>
      <td>I love this place.</td>
      <td>1</td>
    </tr>
    <tr>
      <th>380</th>
      <td>I won't be back.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>383</th>
      <td>The food was terrible.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>505</th>
      <td>I would not recommend this place.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>814</th>
      <td>I love this place.</td>
      <td>1</td>
    </tr>
    <tr>
      <th>816</th>
      <td>The food was terrible.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>843</th>
      <td>I won't be back.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>846</th>
      <td>I would not recommend this place.</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
</div>



Removing duplicates:


```python
reviews.drop_duplicates(inplace = True)
reviews.reset_index(drop = True, inplace = True)
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>991</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>992</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
    </tr>
    <tr>
      <th>993</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>994</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
    </tr>
    <tr>
      <th>995</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
<p>996 rows × 2 columns</p>
</div>



Info of the data:


```python
reviews.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 996 entries, 0 to 995
    Data columns (total 2 columns):
     #   Column     Non-Null Count  Dtype 
    ---  ------     --------------  ----- 
     0   Review     996 non-null    object
     1   Sentiment  996 non-null    int64 
    dtypes: int64(1), object(1)
    memory usage: 15.7+ KB


Counting uniques sentiments:


```python
reviews["Sentiment"].value_counts()
```




    1    499
    0    497
    Name: Sentiment, dtype: int64



This data is well balanced, no need to worry about it!

Checking for missing values:


```python
reviews.isna().sum()
```




    Review       0
    Sentiment    0
    dtype: int64



No missing values.

## Starting NLP

We will go through the following steps:

* Remove punctuations and lower cases
* Remove *stop words*
* Word cloud
* TF-IDF and n-grams

### Remove Punctuations

The first thing we will do is to remove the punctuation from the sentences using the `maketrans` and `translate` string methods, and the method`punctuation` from the *string* library (for more, watch the [learning lab 24](https://www.crewes.org/ResearchLinks/DataScience/summary.php?docid=CDS2022024)).


```python
def remove_punctuation(txt):
    import string
    return txt.translate(str.maketrans("", "", string.punctuation)).lower()
```


```python
reviews["Review_no_Punctuation"] = reviews["Review"].apply(remove_punctuation)
```


```python
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
      <th>Review_no_Punctuation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
      <td>wow loved this place</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
      <td>crust is not good</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
      <td>not tasty and the texture was just nasty</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
      <td>stopped by during the late may bank holiday of...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
      <td>the selection on the menu was great and so wer...</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>991</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
      <td>i think food should have flavor and texture an...</td>
    </tr>
    <tr>
      <th>992</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
      <td>appetite instantly gone</td>
    </tr>
    <tr>
      <th>993</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
      <td>overall i was not impressed and would not go back</td>
    </tr>
    <tr>
      <th>994</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
      <td>the whole experience was underwhelming and i t...</td>
    </tr>
    <tr>
      <th>995</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
      <td>then as if i hadnt wasted enough of my life th...</td>
    </tr>
  </tbody>
</table>
<p>996 rows × 3 columns</p>
</div>




```python
reviews.loc[500, "Review_no_Punctuation"]
```




    'i also had to taste my moms multigrain pumpkin pancakes with pecan butter and they were amazing fluffy and delicious'



Without the punctuation and text in lower case, can we have more duplicated rows?


```python
reviews[["Sentiment", "Review_no_Punctuation"]].duplicated().sum()
```




    1




```python
reviews[reviews[["Sentiment", "Review_no_Punctuation"]].duplicated(keep = False) == True]
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
      <th>Review</th>
      <th>Sentiment</th>
      <th>Review_no_Punctuation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>446</th>
      <td>Will not be back.</td>
      <td>0</td>
      <td>will not be back</td>
    </tr>
    <tr>
      <th>744</th>
      <td>Will not be back!</td>
      <td>0</td>
      <td>will not be back</td>
    </tr>
  </tbody>
</table>
</div>




```python
reviews.drop(744, inplace = True)
reviews.reset_index(inplace = True, drop = True)
```

### Remove Stop Words

Let's use library `nltk` to remove the stop words.


```python
import nltk.corpus
nltk.download("stopwords")
from nltk.corpus import stopwords
```

    [nltk_data] Downloading package stopwords to
    [nltk_data]     /Users/leonardoqueiroz/nltk_data...
    [nltk_data]   Package stopwords is already up-to-date!



```python
stop_words = stopwords.words("english")
print(sorted(stop_words))
```

    ['a', 'about', 'above', 'after', 'again', 'against', 'ain', 'all', 'am', 'an', 'and', 'any', 'are', 'aren', "aren't", 'as', 'at', 'be', 'because', 'been', 'before', 'being', 'below', 'between', 'both', 'but', 'by', 'can', 'couldn', "couldn't", 'd', 'did', 'didn', "didn't", 'do', 'does', 'doesn', "doesn't", 'doing', 'don', "don't", 'down', 'during', 'each', 'few', 'for', 'from', 'further', 'had', 'hadn', "hadn't", 'has', 'hasn', "hasn't", 'have', 'haven', "haven't", 'having', 'he', 'her', 'here', 'hers', 'herself', 'him', 'himself', 'his', 'how', 'i', 'if', 'in', 'into', 'is', 'isn', "isn't", 'it', "it's", 'its', 'itself', 'just', 'll', 'm', 'ma', 'me', 'mightn', "mightn't", 'more', 'most', 'mustn', "mustn't", 'my', 'myself', 'needn', "needn't", 'no', 'nor', 'not', 'now', 'o', 'of', 'off', 'on', 'once', 'only', 'or', 'other', 'our', 'ours', 'ourselves', 'out', 'over', 'own', 're', 's', 'same', 'shan', "shan't", 'she', "she's", 'should', "should've", 'shouldn', "shouldn't", 'so', 'some', 'such', 't', 'than', 'that', "that'll", 'the', 'their', 'theirs', 'them', 'themselves', 'then', 'there', 'these', 'they', 'this', 'those', 'through', 'to', 'too', 'under', 'until', 'up', 've', 'very', 'was', 'wasn', "wasn't", 'we', 'were', 'weren', "weren't", 'what', 'when', 'where', 'which', 'while', 'who', 'whom', 'why', 'will', 'with', 'won', "won't", 'wouldn', "wouldn't", 'y', 'you', "you'd", "you'll", "you're", "you've", 'your', 'yours', 'yourself', 'yourselves']



```python
reviews["Review_Clean"] = reviews["Review_no_Punctuation"].apply(lambda x: ' '.join([word for word in x.split() if word not in (stop_words)]))
```


```python
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
      <th>Review_no_Punctuation</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
      <td>wow loved this place</td>
      <td>wow loved place</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
      <td>crust is not good</td>
      <td>crust good</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
      <td>not tasty and the texture was just nasty</td>
      <td>tasty texture nasty</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
      <td>stopped by during the late may bank holiday of...</td>
      <td>stopped late may bank holiday rick steve recom...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
      <td>the selection on the menu was great and so wer...</td>
      <td>selection menu great prices</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>990</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
      <td>i think food should have flavor and texture an...</td>
      <td>think food flavor texture lacking</td>
    </tr>
    <tr>
      <th>991</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
      <td>appetite instantly gone</td>
      <td>appetite instantly gone</td>
    </tr>
    <tr>
      <th>992</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
      <td>overall i was not impressed and would not go back</td>
      <td>overall impressed would go back</td>
    </tr>
    <tr>
      <th>993</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
      <td>the whole experience was underwhelming and i t...</td>
      <td>whole experience underwhelming think well go n...</td>
    </tr>
    <tr>
      <th>994</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
      <td>then as if i hadnt wasted enough of my life th...</td>
      <td>hadnt wasted enough life poured salt wound dra...</td>
    </tr>
  </tbody>
</table>
<p>995 rows × 4 columns</p>
</div>



We need to be careful when removing stop words, or we can change the meaning of the sentence. Let's remove some elements from the *stop words* list:


```python
not_stop_words = ["not", "no"]
stop_words_new = [x for x in stop_words if x not in not_stop_words]
print(sorted(stop_words_new))
```

    ['a', 'about', 'above', 'after', 'again', 'against', 'ain', 'all', 'am', 'an', 'and', 'any', 'are', 'aren', "aren't", 'as', 'at', 'be', 'because', 'been', 'before', 'being', 'below', 'between', 'both', 'but', 'by', 'can', 'couldn', "couldn't", 'd', 'did', 'didn', "didn't", 'do', 'does', 'doesn', "doesn't", 'doing', 'don', "don't", 'down', 'during', 'each', 'few', 'for', 'from', 'further', 'had', 'hadn', "hadn't", 'has', 'hasn', "hasn't", 'have', 'haven', "haven't", 'having', 'he', 'her', 'here', 'hers', 'herself', 'him', 'himself', 'his', 'how', 'i', 'if', 'in', 'into', 'is', 'isn', "isn't", 'it', "it's", 'its', 'itself', 'just', 'll', 'm', 'ma', 'me', 'mightn', "mightn't", 'more', 'most', 'mustn', "mustn't", 'my', 'myself', 'needn', "needn't", 'nor', 'now', 'o', 'of', 'off', 'on', 'once', 'only', 'or', 'other', 'our', 'ours', 'ourselves', 'out', 'over', 'own', 're', 's', 'same', 'shan', "shan't", 'she', "she's", 'should', "should've", 'shouldn', "shouldn't", 'so', 'some', 'such', 't', 'than', 'that', "that'll", 'the', 'their', 'theirs', 'them', 'themselves', 'then', 'there', 'these', 'they', 'this', 'those', 'through', 'to', 'too', 'under', 'until', 'up', 've', 'very', 'was', 'wasn', "wasn't", 'we', 'were', 'weren', "weren't", 'what', 'when', 'where', 'which', 'while', 'who', 'whom', 'why', 'will', 'with', 'won', "won't", 'wouldn', "wouldn't", 'y', 'you', "you'd", "you'll", "you're", "you've", 'your', 'yours', 'yourself', 'yourselves']



```python
reviews["Review_Clean"] = reviews["Review_no_Punctuation"].apply(lambda x: ' '.join([word for word in x.split() if word not in (stop_words_new)]))
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
      <th>Review_no_Punctuation</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
      <td>wow loved this place</td>
      <td>wow loved place</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
      <td>crust is not good</td>
      <td>crust not good</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
      <td>not tasty and the texture was just nasty</td>
      <td>not tasty texture nasty</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
      <td>stopped by during the late may bank holiday of...</td>
      <td>stopped late may bank holiday rick steve recom...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
      <td>the selection on the menu was great and so wer...</td>
      <td>selection menu great prices</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>990</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
      <td>i think food should have flavor and texture an...</td>
      <td>think food flavor texture lacking</td>
    </tr>
    <tr>
      <th>991</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
      <td>appetite instantly gone</td>
      <td>appetite instantly gone</td>
    </tr>
    <tr>
      <th>992</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
      <td>overall i was not impressed and would not go back</td>
      <td>overall not impressed would not go back</td>
    </tr>
    <tr>
      <th>993</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
      <td>the whole experience was underwhelming and i t...</td>
      <td>whole experience underwhelming think well go n...</td>
    </tr>
    <tr>
      <th>994</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
      <td>then as if i hadnt wasted enough of my life th...</td>
      <td>hadnt wasted enough life poured salt wound dra...</td>
    </tr>
  </tbody>
</table>
<p>995 rows × 4 columns</p>
</div>



Now we can drop some columns:


```python
reviews.drop(["Review_no_Punctuation"], axis = 1, inplace = True)
reviews
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
      <th>Review</th>
      <th>Sentiment</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Wow... Loved this place.</td>
      <td>1</td>
      <td>wow loved place</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Crust is not good.</td>
      <td>0</td>
      <td>crust not good</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Not tasty and the texture was just nasty.</td>
      <td>0</td>
      <td>not tasty texture nasty</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>1</td>
      <td>stopped late may bank holiday rick steve recom...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>The selection on the menu was great and so wer...</td>
      <td>1</td>
      <td>selection menu great prices</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>990</th>
      <td>I think food should have flavor and texture an...</td>
      <td>0</td>
      <td>think food flavor texture lacking</td>
    </tr>
    <tr>
      <th>991</th>
      <td>Appetite instantly gone.</td>
      <td>0</td>
      <td>appetite instantly gone</td>
    </tr>
    <tr>
      <th>992</th>
      <td>Overall I was not impressed and would not go b...</td>
      <td>0</td>
      <td>overall not impressed would not go back</td>
    </tr>
    <tr>
      <th>993</th>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>0</td>
      <td>whole experience underwhelming think well go n...</td>
    </tr>
    <tr>
      <th>994</th>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>0</td>
      <td>hadnt wasted enough life poured salt wound dra...</td>
    </tr>
  </tbody>
</table>
<p>995 rows × 3 columns</p>
</div>




```python
reviews.reset_index(inplace = True, drop = True)
```

## Word Cloud

Let's do the word cloud of the review column.


```python
from wordcloud import WordCloud
import matplotlib.pyplot as plt
```


```python
text = " ".join(txt for txt in reviews.Review_Clean.astype(str))
print(text)
```

    wow loved place crust not good not tasty texture nasty stopped late may bank holiday rick steve recommendation loved selection menu great prices getting angry want damn pho honeslty didnt taste fresh potatoes like rubber could tell made ahead time kept warmer fries great great touch service prompt would not go back cashier no care ever say still ended wayyy overpriced tried cape cod ravoli chickenwith cranberrymmmm disgusted pretty sure human hair shocked no signs indicate cash highly recommended waitress little slow service place not worth time let alone vegas not like burrittos blah food amazing service also cute could care less interior beautiful performed thats rightthe red velvet cakeohhh stuff good never brought salad asked hole wall great mexican street tacos friendly staff took hour get food 4 tables restaurant food luke warm sever running around like totally overwhelmed worst salmon sashimi also combos like burger fries beer 23 decent deal like final blow found place accident could not happier seems like good quick place grab bite familiar pub food favor look elsewhere overall like place lot redeeming quality restaurant inexpensive ample portions good prices poor service waiter made feel like stupid every time came table first visit hiro delight service sucks shrimp tender moist not deal good enough would drag establishment hard judge whether sides good grossed melted styrofoam didnt want eat fear getting sick positive note server attentive provided great service frozen pucks disgust worst people behind register thing like prime rib dessert section bad food damn generic burger good beef cooked right want sandwich go firehouse side greek salad greek dressing tasty pita hummus refreshing ordered duck rare pink tender inside nice char outside came running us realized husband left sunglasses table chow mein good horrible attitudes towards customers talk one customers dont enjoy food portion huge loved itfriendly servers great food wonderful imaginative menu heart attack grill downtown vegas absolutely flatlined excuse restaurant not much seafood like 5 strings pasta bottom salad right amount sauce not power scallop perfectly cooked ripped banana not ripped petrified tasteless least think refill water struggle wave 10 minutes place receives stars appetizers cocktails handmade delicious wed definitely go back glad found place great food service huge portions give military discount always great time dos gringos updatewent back second time still amazing got food apparently never heard salt batter fish chewy great way finish great deal included 5 tastings 2 drinks jeff went beyond expected really really good rice time service meh took 30 min get milkshake nothing chocolate milk guess known place would suck inside excalibur didnt use common sense scallop dish quite appalling value well 2 times bad customer service sweet potato fries good seasoned well today second time ive lunch buffet pretty good much good food vegas feel cheated wasting eating opportunity going rice company coming like experiencing underwhelming relationship parties cant wait person ask break walked place smelled like old grease trap 2 others eating turkey roast beef bland place pan cakes everyone raving taste like sugary disaster tailored palate six year old love pho spring rolls oh yummy try poor batter meat ratio made chicken tenders unsatisfying say food amazing omelets die everything fresh delicious summary largely disappointing dining experience like really sexy party mouth youre outrageously flirting hottest person party never hard rock casino never ever step forward best breakfast buffet say bye bye tip lady well never go back food arrived quickly not good side cafe serves really good food server fantastic found wife loves roasted garlic bone marrow added extra meal another marrow go good thing waiter helpful kept bloddy marys coming best buffet town price cannot beat loved mussels cooked wine reduction duck tender potato dishes delicious one better buffets went tigerlilly fantastic afternoon food delicious bartender attentive personable got great deal ambience wonderful music playing go back next trip sooooo good real sushi lovers lets honest yama not good least 40min passed us ordering food arriving wasnt busy really fantastic thai restaurant definitely worth visit nice spicy tender good prices check pretty gross ive better atmosphere kind hard mess steak although much liked look sound place actual experience bit disappointing dont know place managed served blandest food ever eaten preparing indian cuisine worst service boot least worries service fine waitress friendly guys steaks steak loving son steak best worst places said best steak hes ever eaten thought youd venture away get good sushi place really hit spot night host staff lack better word bitches bland not liking place number reasons dont want waste time bad reviewing ill leave phenomenal food service ambiance wouldnt return definitely worth venturing strip pork belly return next time im vegas place way overpriced mediocre food penne vodka excellent good selection food including massive meatloaf sandwich crispy chicken wrap delish tuna melt tasty burgers management rude delicious nyc bagels good selections cream cheese real lox capers even great subway fact good come every subway not meet expectations seriously solid breakfast one best bars food vegas extremely rude really many restaurants would love dine weekend vegas drink never empty made really great menu suggestions dont waiter wasnt helpful friendly rarely checked us husband ate lunch disappointed food service red curry much bamboo shoots wasnt tasty nice blanket moz top feel like done cover subpar food bathrooms clean place well decorated menu always changing food quality going service extremely slow service little slow considering served 3 people servers food coming slow pace give 2 thumbs watched waiter pay lot attention tables ignore us fiancé came middle day greeted seated right away great restaurant mandalay bay waited forty five minutes vain crostini came salad stale highlights great quality nigiri staff friendly joint always clean different cut piece day still wonderful tender well well flavored ordered voodoo pasta first time id really excellent pasta since going gluten free several years ago place good unfortunately must hit bakery leftover day everything ordered stale came back today since relocated still not impressed seated immediately menu diverse reasonably priced avoid cost restaurant always full never wait delicious place handsdown one best places eat phoenix metro area dont go looking good food ive never treated bad bacon hella salty also ordered spinach avocado salad ingredients sad dressing literally zero taste really vegas fine dining used right menus handed ladies no prices listed waitresses friendly lordy khao soi dish not missed curry lovers everything menu terrific also thrilled made amazing accommodations vegetarian daughter perhaps caught night judging reviews im not inspired go back service leaves lot desired atmosphere modern hip maintaining touch coziness not weekly haunt definitely place come back every literally sat 20 minutes no one asking take order burger absolutely no flavor meat totally bland burger overcooked no charcoal flavor also decided not send back waitress looked like verge heart attack dressed treated rudely probably dirt love place hits spot want something healthy not lacking quantity flavor ordered lemon raspberry ice cocktail also incredible food sucked expected sucked could imagined interesting decor really like crepe station also served hot bread butter home made potato chips bacon bits topvery original good watch preparing delicious food egg rolls fantastic order arrived one gyros missing salad wings ice cream dessert left feeling quite satisfied im not really sure joeys voted best hot dog valley readers phoenix magazine best place go tasty bowl pho live music fridays totally blows ive never insulted felt disrespected friendly staff worth drive heard good things place exceeding every hope could dreamed food great serivce warm beer didnt help great brunch spot service friendly inviting good lunch spot ive lived since 1979 first last time ive stepped foot place worst experience ever must night place sides delish mixed mushrooms yukon gold puree white corn beateous bug never showed would given 4 sure side wall bug climbing kitchen 10 minutes waiting salad realized wasnt coming time soon friend loved salmon tartar wont go back extremely tasty waitress good though soggy not good jamaican mojitos delicious small not worth price food rich order accordingly shower area outside rinse not take full shower unless dont mind nude everyone see service bit lacking lobster bisque bussell sprouts risotto filet needed salt pepperand course none tables hopefully bodes going business someone cook come either cold not enough flavor bad loved bacon wrapped dates unbelievable bargain folks otto always make us feel welcome special mains also uninspired place first pho amazing wonderful experience made place muststop whenever town food isnt bad enough enjoy dealing worlds worstannoying drunk people fun chef ordered double cheeseburger got single patty falling apart picture uploaded yeah still sucks great place couple drinks watch sporting events walls covered tvs possible give zero stars theyd descriptions said yum yum sauce another said eel sauce yet another said spicy mayowell none rolls sauces id say would hardest decision honestly ms dishes taste supposed taste amazing not rolled eyes may stayed not sure go back try everyone attentive providing excellent customer service horrible dont waste time money dish quite flavourful time side restaurant almost empty no excuse wasnt busy either also building freezing cold like reviewer said couldnt pay eat place drinks took close 30 minutes come one point seriously flavorful delights folks much better ayce sushi place went vegas lighting dark enough set mood based subpar service received no effort show gratitude business wont going back owners really great people nothing privileged workingeating greek dressing creamy flavorful overall dont think would take parents place made similar complaints silently felt pizza good peanut sauce tasty 7 table service pretty fast fantastic service well wouldve given godfathers zero stars possible know make tough short flavor hope place sticks around bars vegas not ever recall charged tap water restaurant atmosphere exquisite good service clean inexpensive boot seafood fresh generous portion plus 8 bucks service not par either thus far visited twice food absolutely delicious time good year ago self proclaimed coffee cafe wildly disappointed veggitarian platter world cant go wrong food cant beat stopped place madison ironman friendly kind staff chefs friendly good job ive better not dedicated boba tea spots even jenni pho liked patio service outstanding goat taco didnt skimp meat wow flavor think not mac salad pretty bland not getting went bachi burger friends recommendation not disappointed service stinks waited waited place not quality sushi not quality restaurant would definitely recommend wings well pizza great pizza salads things went wrong burned saganaki waited hour breakfast could done 100 times better home place amazing hate disagree fellow yelpers husband disappointed place waited 2 hours never got either pizzas many around us came later dont know slow staff great food delish incredible beer selection live neighborhood disappointed wont back convenient location didnt know pulled pork could soooo delicious get incredibly fresh fish prepared care go gave 1 star rating please know third time eating bachi burger writing review love fact everything menu worth never dining place food excellent service good good beer drink selection good food selection please stay away shrimp stir fried noodles potato chip order sad could probably count many chips box probably around 12 food really boring good servicecheck greedy corporation never see another dime never ever go back much id like go back cant get passed atrocious service never return summer dine charming outdoor patio delightful not expect good fantastic food ordered toasted english muffin came untoasted food good never going back great food price high quality house made bus boy hand rude point friends basically figured place joke didnt mind making publicly loudly known back good bbq lighter fare reasonable pricing tell public back old ways considering two us left full happy 20 cant go wrong bread made inhouse downside service also fries without doubt worst fries ive ever service exceptional food good reviews couple months later returned amazing meal favorite place town shawarrrrrrma black eyed peas sweet potatoes unreal wont disappointed could serve vinaigrette may make better overall dish still good go far many places ive never seen restaurant serves 1 egg breakfast especially 400 mom got home immediately got sick bites salad servers not pleasant deal dont always honor pizza hut coupons truly unbelievably good glad went back fantastic service pleased atmosphere everything gross love place great service food first bathrooms location dirty seat covers not replenished plain yucky burger got gold standard 17 burger kind disappointed omg food delicioso nothing authentic place spaghetti nothing special whatsoever dishes salmon best great vegetables fresh sauce feels like authentic thai worth driving tucson selection probably worst ive seen vegasthere none pretty good beer selection place like chipotle better classywarm atmosphere fun fresh appetizers succulent steaks baseball steak 5 stars brick oven bread app eaten multiple times time food delicious sat another ten minutes finally gave left terrible everyone treated equally special shouldnt take 30 min pancakes eggs delicious good side staff genuinely pleasant enthusiastic real treat sadly gordon ramseys steak place shall sharply avoid next trip vegas always evening wonderful food delicious best fish ive ever life bathroom next door nice buffet small food offered bland outstanding little restaurant best food ever tasted pretty cool would say definitely turn doubt ill back unless someone else buying server great job handling large rowdy table find wasting food despicable wasnt food wife lobster bisque soup lukewarm would come back sushi craving vegas staff great ambiance great deserves 5 stars left stomach ache felt sick rest day dropped ball dining space tiny elegantly decorated comfortable customize order way youd like usual eggplant green bean stir fry love beans rice mediocre best best tacos town far took back money got outta interesting part town place amazing rude inconsiderate management staff not friendly wait times served horrible no one even says hi first 10 minutes wont back great dinners service outshining definitely recommend halibut food terrible never ever go back told many people happened dont recommend unless car breaks front starving come back every time im vegas place deserves one star 90 food disgrace def coming back bowl next time want healthy authentic ethic food try place continue come ladies night andddd date night highly recommend place anyone area several times past experience always great walked away stuffed happy first vegas buffet experience service excellent prices pretty reasonable considering vegas located inside crystals shopping mall aria summarize food incredible nay transcendant nothing brings joy quite like memory pneumatic condiment dispenser im probably one people ever go ians not like kids pizza always hit lots great side dish options kiddos service perfect family atmosphere nice see cooked perfection service impeccable one simply disappointment overall disappointed quality food bouchon dont accountant know im getting screwed great place eat reminds little mom pop shops san francisco bay area today first taste buldogis gourmet hot dog tell ever thought possible left frustrated ill definitely soon food really good got full petty fast service fantastic total waste time dont know kind best iced tea come hungry leave happy stuffed service give no stars assure wont disappointed take little bad service food sucks gave trying eat crust teeth still sore completely grossed really enjoyed eating first time going think quickly become regular server nice even though looked little overwhelmed needs stayed professional friendly end dinner companions told meeverything fresh nice texture taste ground right next table large smeared beensteppedinandtrackedeverywhere pile green bird poop furthermore cant even find hours operation website weve tried like place 10 times think done mistake no complaints seriously good pizza im expertconnisseur topic waiter jerk strike 2 wants rushed nicest restaurant owners ive ever come across never come loved biscuits service quick friendly ordered appetizer took 40 minutes pizza another 10 minutes absolutley fantastic huge awkward 15lb piece cow 34ths gristle fat definitely come back like steiners dark feels like bar wow spicy delicious youre not familiar check ill take business dinner dollars elsewhere id love go back anyway fs restaurant wonderful breakfastlunch nothing special day week different deal delicious not mention combination pears almonds bacon big winner not back sauce tasteless food delicious spicy enough sure ask spicier prefer way ribeye steak cooked perfectly great mesquite flavor dont think well going back anytime soon food gooodd far sushi connoisseur definitely tell difference good food bad food certainly bad food insulted last 3 times lunch bad chicken wings contained driest chicken meat ever eaten food good enjoyed every mouthful enjoyable relaxed venue couples small family groups etc nargile think great best tater tots southwest loved place definitely not worth 3 paid vanilla ice cream creamy smooth profiterole choux pastry fresh enough im az time new spot manager worst inside really quite nice clean food outstanding prices reasonable dont think ill running back carlys anytime soon food due fact took 20 minutes acknowledged another 35 minutes get foodand kept forgetting things love margaritas first vegas buffet not disappoint good though one note ventilation could use upgrading great pork sandwich dont waste time total letdown would much rather go camelback flower shop cartel coffee third cheese friends burger cold enjoy pizza brunch steaks well trimmed also perfectly cooked group 70 claimed would 40 handled us beautifully loved asked bill leave without eating didnt bring either place jewel las vegas exactly ive hoping find nearly ten years living seafood limited boiled shrimp crab legs crab legs definitely not taste fresh selection food not best delicious absolutely back isnt small family restaurant fine dining establishment toro tartare cavier extraordinary liked thinly sliced wagyu white truffle dont think back long time attached gas station rarely good sign awesome back many times soon menu much good stuff could not decide worse humiliated worker right front mebunch horrible name callings conclusion filling meals daily specials always hit group tragedy struck pancake also really good pretty large first crawfish experience delicious monster chicken fried steak eggs time favorite waitress sweet funny also taste moms multigrain pumpkin pancakes pecan butter amazing fluffy delicious id rather eat airline food seriously cant say enough good things place ambiance incredible waitress manager friendly would not recommend place overall wasnt impressed noca gyro basically lettuce terrible service thoroughly disappointed dont much pasta love homemade hand made pastas thin pizzas give try happy far best cheesecurds ever reasonably priced also everything perfect night food good typical bar food drive get first glance lovely bakery cafe nice ambiance clean friendly staff anyway not think go back point finger item menu order wont disappointed oh thing beauty restaurant havent gone go greasy unhealthy meal first time might last burgers amazing similarly delivery man not say word apology food 45 minutes late way expensive sure order dessert even need pack togo tiramisu cannoli die first time cant wait next bartender also nice everything good tasty place two thumbs upway best place vegas breakfast check sat sun love authentic mexican food want whole bunch interesting yet delicious meats choose need try place terrible management excellent new restaurant experienced frenchman zero stars would give zero stars great steak great sides great wine amazing desserts worst martini ever steak shrimp opinion best entrees gc opportunity today sample amazing pizzas waited thirty minutes seated although 8 vacant tables folks waiting yellowtail carpaccio melt mouth fresh wont try going back even empty no im going eat potato found strangers hair spicy enough perfect actually last night second time dining happy decided go back not even hello right desserts bit strange boyfriend came first time recent trip vegas could not pleased quality food service really recommend place go wrong donut place nice ambiance would recommend saving room guess maybe went night disgraceful however recent experience particular location not good know not like restaurants something avoid establishment think restaurant suffers not trying hard enough tapas dishes delicious heart place salad bland vinegrette baby greens hearts palm two felt disgusting good time believe place great stop huge belly hankering sushi generous portions great taste never go back place never ever recommended place anyone servers went back forth several times not even much helped food delicious hour seriously consider theft eew location needs complete overhaul recently witnessed poor quality management towards guests well waited waited waited also came back check us regularly excellent service server super nice checked us many times pizza tasted old super chewy not good way swung give try deeply disappointed service good company better staff also friendly efficient service im fan quick youre served nice folks boy sucker dry rated look authentic thai food go else steaks 100 recommended pulled car waited another 15 minutes acknowledged great food great service clean friendly setting assure ill back hate things much cheap quality black olives breakfast perpared great beautiful presentation 3 giant slices toast lightly dusted powdered sugar kids play area nasty great place fo take eat waitress friendly happy accomodate veganveggie options omg felt like never eaten thai food dish extremely crumby pretty tasteless pale color instead nice char no flavor croutons also taste homemade extra plus got home see driest damn wings ever itll regular stop trips phoenix really enjoyed crema café expanded even told friends best breakfast not good money miss wish one philadelphia got sitting fairly fast ended waiting 40 minutes place order another 30 minutes food arrived also best cheese crisp town good value great food great service couldnt ask satisfying meal food good awesome wanted leave made drive way north scottsdale not one bit disappointed not eating owners really really need quit soooooo cheap let wrap freaking sandwich two papers not one checked place couple years ago not impressed chicken got definitely reheated ok wedges cold soggy sorry not getting food anytime soon absolute must visit cow tongue cheek tacos amazing friend not like bloody mary despite hard rate businesses actually rare give 1 star really want make experience good one not return chicken pho tasted bland disappointing grilled chicken tender yellow saffron seasoning drive thru means not want wait around half hour food somehow end going make us wait wait pretty awesome place ambience perfect best luck rude noncustomer service focused new management grandmother make roasted chicken better one asked multiple times wine list time ignored went hostess got one staff always super friendly helpful especially cool bring two small boys baby four stars food guy blue shirt great vibe still letting us eat roast beef sandwich tasted really good evening drastically sick highquality chicken chicken caesar salad ordered burger rare came well done promptly greeted seated tried go lunch madhouse proven dead wrong sushi bar not quality great service fast food impeccable waiting hour seated not greatest moods good joint macarons insanely good im not eating waiter attentive friendly informative maybe werent cold would somewhat edible place lot promise fails deliver bad experience mistake food average best great food wont going back anytime soon disappointed ordered 35 big bay plater great place relax awesome burger beer perfect sitdown family meal get together friends not much flavor poorly constructed patio seating comfortable fried rice dry well hands favorite italian restaurant screams legit booksomethats also pretty rare vegas not fun experience atmosphere great lovely duo violinists playing songs requested personally love hummus pita baklava falafels baba ganoush amazing eggplant convenient since staying mgm owners super friendly staff courteous great eclectic selection sweet potato tots good onion rings perfection close staff attentive chef generous time even came around twice take pictures owner used work nobu place really similar half price google mediocre imagine smashburger pop dont go promise wont disappoint sushi lover avoid place means great double cheeseburger awesome service food fantastic neighborhood gem cant wait go back plantains worst ive ever tasted great place highly recommend service slow not attentive gave 5 stars im giving 5 stars staff spends time talking dessert panna cotta amazing good food great atmosphere1 damn good steak total brunch fail prices reasonable flavors spot sauce home made slaw not drenched mayo decor nice piano music soundtrack pleasant steak amazingrge fillet relleno best seafood plate ever good food good service absolutely amazing probably wont back honest definitely back sergeant pepper beef sandwich auju sauce excellent sandwich well hawaiian breeze mango magic pineapple delight smoothies ive tried far theyre good went lunch service slow much say place walked expected amazing quickly disappointed mortified needless say never back anyways food definitely not filling price pay expect chips came dripping grease mostly not edible wasnt really impressed strip steak going since 2007 every meal awesome server nice attentive serving staff cashier friendly even brought food work hospitality industry paradise valley refrained recommending cibo longer atmosphere fun would not recommend others service quick even go orders like like mean really get famous fish chips terrible said mouths bellies still quite pleased not thing 2 thumbs reading please dont go loved grilled pizza reminded legit italian pizza pros large seating area nice bar area great simple drink menu best brick oven pizza homemade dough really nice atmosphere tonight elk filet specialand sucked one bite hooked ordered old classics new dishes going times sorely disappointed everything cute quaint simple honest chicken deliciously seasoned perfect fry outside moist chicken inside food great always compliments chef special thanks dylan recommendation order yummy tummy awesome selection beer great food awesome service one nice thing added gratuity bill since party larger 6 8 didnt expect tip fly apple juice fly han nan chicken also tasty service thought good food barely lukewarm must sitting waiting server bring us ryans bar definitely one edinburgh establishment wont revisiting nicest chinese restaurant ive overall like food service also serve indian naan bread hummus spicy pine nut sauce world probably never coming back wouldnt recommend friends pasta also bad barely touched try airport experience tasty food speedy friendly service love decor chinese calligraphy wall paper never anything complain restaurant clean family restaurant feel way fried im not sure long stood long enough begin feel awkwardly place opened sandwich impressed not good way warm feeling service felt like guest special treat extensive menu provides lots options breakfast always order vegetarian menu dinner wide array options choose watched prices inflate portions get smaller management attitudes grow rapidly wonderful lil tapas ambience made feel warm fuzzy inside got enjoy seafood salad fabulous vinegrette wontons thin not thick chewy almost melt mouth level 5 spicy perfect spice didnt overwhelm soup sat right time server get go fantastic main thing didnt enjoy crowd older crowd around mid 30s im side town definitely spot ill hit wait 30 minutes get drink longer get 2 arepas great place eat jalapeno bacon soooo good service poor thats nice food good service good prices good place not clean food oh stale chicken dishes ok beef like shoe leather service beyond bad im happy tasted like dirt one places phoenix would definately go back block amazing close house lowkey nonfancy affordable prices good food hot sour egg flower soups absolutely 5 stars sashimi poor quality soggy tasteless great time family dinner sunday night food not tasty not say real traditional hunan style bother slow service flair bartenders absolutely amazing frozen margaritas way sugary taste good ordered twice nutshell 1 restaraunt smells like combination dirty fish market sewer girlfriends veal bad unfortunately not good pretty satifying experience join club get awesome offers via email perfect someone likes beer ice cold case even colder bland flavorless good way describing barely tepid meat chains im no fan beat place easily nachos must not coming back dont many words say place everything pretty well staff super nice quick even crazy crowds downtown juries lawyers court staff great atmosphere friendly fast service received pita huge lot meat thumbs food arrives meh paying 785 hot dog fries looks like came kids meal wienerschnitzel not idea good meal classic maine lobster roll fantastic brother law works mall ate day guess sick night good going review place twice hereas tribute place tribute event held last night chips salsa really good salsa fresh place great mediocre food get inside youll impressed place im super pissd service super friendly sad little vegetables overcooked place nice surprise goldencrispy delicious high hopes place since burgers cooked charcoal grill unfortunately taste fell flat way flat could eat bruschetta day devine not single employee came see ok even needed water refill finally served us food lastly mozzarella sticks best thing ordered first time ever came amazing experience still tell people awesome duck server negligent needs made us feel unwelcome would not suggest place service terrible though place overpriced not consistent boba really overpriced packed say desserts yummy seasonal fruit fresh white peach puree kept getting worse worse im officially done place honestly blown definitely would not eat not waste money love put food nice plastic containers opposed cramming little paper takeout boxes crêpe delicate thin moist awful service wont ever go food quality horrible price think place would much rather gone service fair best love sushi found kabuki overpriced overhip underservices favor stay away dish poor service no one table thought food average worth wait best service food ever maria server good friendly made day excellent paid bill not tip felt server terrible job lunch great experience never bland food surprised considering article read focused much spices flavor food way overpriced portions fucking small recently tried caballeros back every week since 40 bucks head really expect better food food came good pace ate twice last visit especially enjoyed salmon salad could not believe dirty oysters place deserves no stars fact im going round 4 stars awesome disbelief dish qualified worst version foods ever tasted bad day not low tolerance rude customer service people job nice polite wash dishes otherwise potatoes great biscuit probably would not go flavorful perfect amount heat price reasonable service great wife hated meal coconut shrimp friends really not enjoy meals either fella got huevos rancheros didnt look appealing went happy hour great list wines may say buffet pricey think get pay place getting quite lot probably wont coming back worst foodservice ive place pretty good nice little vibe restaurant talk great customer service course back hot dishes not hot cold dishes close room tempi watched staff prepare food bare hands no gloveseverything deep fried oil love fries beans always pleasure dealing plethora salads sandwiches everything ive tried gets seal approval place awesome want something light healthy summer sushi strip place go service great even manager came helped table feel dining room college cooking course high class dining service slow best started review two stars im editing give one worst sushi ever eat besides costcos excellent restaurant highlighted great service unique menu beautiful setting boyfriend sat bar completely delightful experience weird vibe owners hardly meat ive better bagels grocery store go place gyros love ownerchef one authentic japanese cool dude burgers arent good pizza used amazing doughy flavorless found six inch long piece wire salsa service terrible food mediocre definately enjoyed ordered albondigas soup warm tasted like tomato soup frozen meatballs three different occasions asked well done medium well three times got bloodiest piece meat plate two bites refused eat anymore service extremely slow 20 minutes wait got table seriously killer hot chai latte no allergy warnings menu waitress absolutely no clue meals not contain peanuts boyfriend tried mediterranean chicken salad fell love rotating beers tap also highlight place pricing bit concern mellow mushroom worst thai ever stay vegas must get breakfast least want first say server great perfect service pizza selections good strawberry tea good highly unprofessional rude loyal patron overall great experience spend money elsewhere regular toasted bread equally satisfying occasional pats butter mmmm buffet bellagio far anticipated drinks weak people order not correct also feel like chips bought not made house disappointing dinner went elsewhere dessert chips sals amazing wont returning new fav vegas buffet spot seriously cannot believe owner many unexperienced employees running around like chickens heads cut sad felt insulted disrespected could talk judge another human like call steakhouse cant properly cook steak dont understand im not impressed concept food thing wasnt crazy guacamole dont like puréed really nothing postinos hope experience better got food poisoning buffet brought fresh batch fries thinking yay something warm no hilarious yummy christmas eve dinner remember biggest fail entire trip us needless say wont going back anytime soon place disgusting every time eat see caring teamwork professional degree ri style calamari joke however much garlic fondue barely edible could barely stomach meal didnt complain business lunch bad lost heart finish also took forever bring us check asked arent ones make scene restaurants dont get itdefinitely lost love one disappointing experience food par dennys say not good want wait mediocre food downright terrible service place waaaaaayyyyyyyyyy rated saying wont going back place fairly clean food simply wasnt worth place lacked style sangria half glass wine full 12 ridiculous dont bother coming meat pretty dry sliced brisket pulled pork building seems pretty neat bathroom pretty trippy wouldnt eat equally awful probably not hurry go back slow seating even reservation not good stretch imagination cashew cream sauce bland vegetables undercooked chipolte ranch dipping sause tasteless seemed thin watered no heat bit sweet not really spicy enough lacked flavor disappointed place horrible way overpriced maybe vegetarian fare ive twice thought average best wasnt busy know tables outside also dirty lot time workers not always friendly helpful menu ambiance not feel like buffet setting douchey indoor garden tea biscuits con spotty service fries not hot neither burger came back cold food came disappointment ensued real disappointment waiter husband said rude not even apologize bad food anything reason eat would fill night binge drinking get carbs stomach insults profound deuchebaggery go outside smoke break serving solidify someone orders two tacos dont think may part customer service ask combo ala cart quite disappointed although blame needs placed door rave reviews couldnt wait eat herewhat disappointment del taco pretty nasty avoided possible not hard make decent hamburger dont like hell no go back weve gotten much better service pizza place next door services received restaurant dont know big deal place wont back yaall immediately said wanted talk manager not want talk guy shots fireball behind bar ambiance isnt much better unfortunately set us disapppointment entrees food wasnt good servers suck wait correction server heimer sucked happened next prettyoff putting bad cause know family owned really wanted like place overpriced getting vomited bathroom mid lunch kept looking time soon become 35 minutes yet still no food places eat no circumstances would ever return tops list started tuna sashimi brownish color obviously wasnt fresh food average sure beat nachos movies would expect little bit coming restaurant ha long bay bit flop problem charge 1199 sandwich no bigger subway sub offers better amount vegetables shrimp unwrapped live 12 mile brushfire literally ice cold lacked flavor seemed undercooked dry really impressive place hasnt closed would avoid place staying mirage refried beans came meal dried crusty food bland spend money time place else lady table next us found live green caterpillar salad presentation food awful cant tell disappointed think food flavor texture lacking appetite instantly gone overall not impressed would not go back whole experience underwhelming think well go ninja sushi next time hadnt wasted enough life poured salt wound drawing time took bring check



```python
wordcloud = WordCloud(background_color = "white", width = 1920, height = 1080).generate(text)

plt.figure(figsize = (10,5))
plt.imshow(wordcloud, interpolation = 'bilinear')
plt.axis("off")
plt.tight_layout(pad = 0)
plt.show()
```


    
![png](/assets/img/posts/yelp-sentiment-analysis/Yelp_Sentiment_Analysis_52_0.png)
    


### TF-IDF with n-grams

For the **TF-IDF**, let's use the *Scikit-Learn* implementation.


```python
from sklearn.feature_extraction.text import TfidfVectorizer
```


```python
vectorizer = TfidfVectorizer(
    lowercase = True, 
    stop_words = stop_words_new, 
    ngram_range = (1, 1), 
    min_df = 0, 
    max_df = 1
)

X = vectorizer.fit_transform(reviews["Review_Clean"])
```


```python
len(vectorizer.get_feature_names_out())
```




    1202



Let's remove words that appear in many documents (common words):


```python
vectorizer = TfidfVectorizer(
    lowercase = True, 
    stop_words = stop_words_new, 
    ngram_range = (1, 2), 
    min_df = 0.006, 
    max_df = 0.2
)

X = vectorizer.fit_transform(reviews["Review_Clean"])
```


```python
len(vectorizer.get_feature_names_out())
```




    212




```python
vectorizer.get_feature_names_out()
```




    array(['absolutely', 'also', 'always', 'amazing', 'ambiance', 'another',
           'area', 'around', 'atmosphere', 'attentive', 'authentic',
           'awesome', 'back', 'bad', 'bar', 'beer', 'best', 'better', 'bit',
           'bland', 'breakfast', 'buffet', 'burger', 'came', 'cant', 'check',
           'chicken', 'chips', 'clean', 'cold', 'come', 'coming', 'cooked',
           'could', 'day', 'deal', 'definitely', 'delicious', 'didnt',
           'dining', 'dinner', 'disappointed', 'dish', 'dishes', 'done',
           'dont', 'eat', 'eating', 'either', 'enjoy', 'enough', 'even',
           'ever', 'every', 'everything', 'excellent', 'experience', 'family',
           'fantastic', 'far', 'feel', 'felt', 'first', 'first time',
           'flavor', 'food', 'food good', 'found', 'fresh', 'friendly',
           'friends', 'fries', 'get', 'getting', 'give', 'go', 'go back',
           'going', 'going back', 'good', 'good food', 'got', 'great',
           'great food', 'great place', 'great service', 'happy', 'hard',
           'horrible', 'hot', 'hour', 'ill', 'im', 'impressed', 'inside',
           'ive', 'know', 'last', 'left', 'like', 'little', 'lot', 'love',
           'loved', 'lunch', 'made', 'make', 'management', 'many', 'meal',
           'meat', 'mediocre', 'menu', 'minutes', 'money', 'much', 'must',
           'never', 'next', 'nice', 'night', 'no', 'not', 'not good',
           'nothing', 'one', 'order', 'ordered', 'overall', 'overpriced',
           'people', 'perfect', 'pho', 'pizza', 'place', 'poor', 'potato',
           'pretty', 'price', 'prices', 'probably', 'quality', 'quite',
           'really', 'really good', 'recommend', 'restaurant', 'right',
           'rude', 'said', 'salad', 'sandwich', 'sauce', 'say', 'see',
           'selection', 'seriously', 'served', 'server', 'service', 'shrimp',
           'side', 'since', 'slow', 'small', 'soon', 'special', 'spicy',
           'spot', 'staff', 'stars', 'steak', 'still', 'super', 'sure',
           'sushi', 'table', 'take', 'taste', 'tasted', 'tasty', 'tell',
           'tender', 'terrible', 'thing', 'think', 'time', 'times', 'took',
           'town', 'tried', 'try', 'twice', 'two', 'us', 'vegas', 'wait',
           'waited', 'waiter', 'waitress', 'want', 'warm', 'wasnt', 'way',
           'well', 'went', 'wonderful', 'wont', 'worst', 'worth', 'would',
           'would not'], dtype=object)




```python
X.toarray()
```




    array([[0.        , 0.        , 0.        , ..., 0.        , 0.        ,
            0.        ],
           [0.        , 0.        , 0.        , ..., 0.        , 0.        ,
            0.        ],
           [0.        , 0.        , 0.        , ..., 0.        , 0.        ,
            0.        ],
           ...,
           [0.        , 0.        , 0.        , ..., 0.        , 0.31035956,
            0.39540897],
           [0.        , 0.        , 0.        , ..., 0.        , 0.        ,
            0.        ],
           [0.        , 0.        , 0.        , ..., 0.        , 0.        ,
            0.        ]])




```python
reviews_tfidf = pd.DataFrame(X.toarray(), columns = vectorizer.get_feature_names_out())
reviews_tfidf["Sentiment"] = reviews["Sentiment"]
reviews_tfidf["Review"] = reviews["Review"]
reviews_tfidf["Review_Clean"] = reviews["Review_Clean"]
reviews_tfidf
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
      <th>absolutely</th>
      <th>also</th>
      <th>always</th>
      <th>amazing</th>
      <th>ambiance</th>
      <th>another</th>
      <th>area</th>
      <th>around</th>
      <th>atmosphere</th>
      <th>attentive</th>
      <th>...</th>
      <th>went</th>
      <th>wonderful</th>
      <th>wont</th>
      <th>worst</th>
      <th>worth</th>
      <th>would</th>
      <th>would not</th>
      <th>Sentiment</th>
      <th>Review</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>1</td>
      <td>Wow... Loved this place.</td>
      <td>wow loved place</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>Crust is not good.</td>
      <td>crust not good</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>Not tasty and the texture was just nasty.</td>
      <td>not tasty texture nasty</td>
    </tr>
    <tr>
      <th>3</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>1</td>
      <td>Stopped by during the late May bank holiday of...</td>
      <td>stopped late may bank holiday rick steve recom...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>1</td>
      <td>The selection on the menu was great and so wer...</td>
      <td>selection menu great prices</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>990</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>I think food should have flavor and texture an...</td>
      <td>think food flavor texture lacking</td>
    </tr>
    <tr>
      <th>991</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>Appetite instantly gone.</td>
      <td>appetite instantly gone</td>
    </tr>
    <tr>
      <th>992</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.31036</td>
      <td>0.395409</td>
      <td>0</td>
      <td>Overall I was not impressed and would not go b...</td>
      <td>overall not impressed would not go back</td>
    </tr>
    <tr>
      <th>993</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>The whole experience was underwhelming, and I ...</td>
      <td>whole experience underwhelming think well go n...</td>
    </tr>
    <tr>
      <th>994</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0</td>
      <td>Then, as if I hadn't wasted enough of my life ...</td>
      <td>hadnt wasted enough life poured salt wound dra...</td>
    </tr>
  </tbody>
</table>
<p>995 rows × 215 columns</p>
</div>




```python
reviews_tfidf.describe().T
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
      <th>count</th>
      <th>mean</th>
      <th>std</th>
      <th>min</th>
      <th>25%</th>
      <th>50%</th>
      <th>75%</th>
      <th>max</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>absolutely</th>
      <td>995.0</td>
      <td>0.004644</td>
      <td>0.053705</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.770192</td>
    </tr>
    <tr>
      <th>also</th>
      <td>995.0</td>
      <td>0.014561</td>
      <td>0.092338</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>always</th>
      <td>995.0</td>
      <td>0.008556</td>
      <td>0.073123</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>amazing</th>
      <td>995.0</td>
      <td>0.015109</td>
      <td>0.104130</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>ambiance</th>
      <td>995.0</td>
      <td>0.004761</td>
      <td>0.058447</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>worst</th>
      <td>995.0</td>
      <td>0.009014</td>
      <td>0.079662</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>worth</th>
      <td>995.0</td>
      <td>0.006267</td>
      <td>0.065320</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>would</th>
      <td>995.0</td>
      <td>0.012516</td>
      <td>0.077454</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.812606</td>
    </tr>
    <tr>
      <th>would not</th>
      <td>995.0</td>
      <td>0.003629</td>
      <td>0.043518</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.596498</td>
    </tr>
    <tr>
      <th>Sentiment</th>
      <td>995.0</td>
      <td>0.501508</td>
      <td>0.500249</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.0</td>
      <td>1.0</td>
      <td>1.000000</td>
    </tr>
  </tbody>
</table>
<p>213 rows × 8 columns</p>
</div>




```python
reviews_tfidf.isna().sum()
```




    absolutely      0
    also            0
    always          0
    amazing         0
    ambiance        0
                   ..
    would           0
    would not       0
    Sentiment       0
    Review          0
    Review_Clean    0
    Length: 215, dtype: int64



## Sentiment Analysis

Let's try the following methods from the `Scikit-Learn` package:

* Logistic Regression
* Random Forest
* Neural Networks


```python
from sklearn.model_selection import train_test_split

train, test = train_test_split(reviews_tfidf, test_size = 0.2, random_state = 1)
```


```python
print(train.shape)
print(test.shape)
print(reviews_tfidf.shape)
```

    (796, 215)
    (199, 215)
    (995, 215)


### Logistic Regression

Train the model:


```python
features = vectorizer.get_feature_names_out()
target = "Sentiment"
```


```python
model_logistic = LogisticRegression(
    solver = "newton-cg",
    max_iter = 100,
    verbose = 2,
    n_jobs = -1,
    random_state = 1
).fit(train[features], train[target])
```

    [Parallel(n_jobs=-1)]: Using backend LokyBackend with 4 concurrent workers.
    [Parallel(n_jobs=-1)]: Done   1 out of   1 | elapsed:    8.6s finished


Predictions:


```python
test["Prediction_Logistic"] = model_logistic.predict(test[features])
```


```python
test[["Sentiment", "Prediction_Logistic", "Review", "Review_Clean"]].sample(20, random_state = 2)
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
      <th>Sentiment</th>
      <th>Prediction_Logistic</th>
      <th>Review</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>945</th>
      <td>0</td>
      <td>0</td>
      <td>It wasn't busy at all and now we know why.</td>
      <td>wasnt busy know</td>
    </tr>
    <tr>
      <th>543</th>
      <td>0</td>
      <td>0</td>
      <td>I won't try going back there even if it's empty.</td>
      <td>wont try going back even empty</td>
    </tr>
    <tr>
      <th>50</th>
      <td>1</td>
      <td>1</td>
      <td>We ordered the duck rare and it was pink and t...</td>
      <td>ordered duck rare pink tender inside nice char...</td>
    </tr>
    <tr>
      <th>962</th>
      <td>0</td>
      <td>0</td>
      <td>Hell no will I go back</td>
      <td>hell no go back</td>
    </tr>
    <tr>
      <th>233</th>
      <td>0</td>
      <td>0</td>
      <td>Ordered a double cheeseburger &amp; got a single p...</td>
      <td>ordered double cheeseburger got single patty f...</td>
    </tr>
    <tr>
      <th>599</th>
      <td>0</td>
      <td>0</td>
      <td>Not good for the money.</td>
      <td>not good money</td>
    </tr>
    <tr>
      <th>874</th>
      <td>0</td>
      <td>1</td>
      <td>Now the burgers aren't as good, the pizza whic...</td>
      <td>burgers arent good pizza used amazing doughy f...</td>
    </tr>
    <tr>
      <th>148</th>
      <td>0</td>
      <td>0</td>
      <td>I give it 2 thumbs down</td>
      <td>give 2 thumbs</td>
    </tr>
    <tr>
      <th>175</th>
      <td>0</td>
      <td>0</td>
      <td>Perhaps I caught them on an off night judging ...</td>
      <td>perhaps caught night judging reviews im not in...</td>
    </tr>
    <tr>
      <th>274</th>
      <td>1</td>
      <td>1</td>
      <td>The chefs were friendly and did a good job.</td>
      <td>chefs friendly good job</td>
    </tr>
    <tr>
      <th>370</th>
      <td>0</td>
      <td>0</td>
      <td>I left with a stomach ache and felt sick the r...</td>
      <td>left stomach ache felt sick rest day</td>
    </tr>
    <tr>
      <th>509</th>
      <td>0</td>
      <td>0</td>
      <td>Thoroughly disappointed!</td>
      <td>thoroughly disappointed</td>
    </tr>
    <tr>
      <th>345</th>
      <td>1</td>
      <td>1</td>
      <td>Pretty good beer selection too.</td>
      <td>pretty good beer selection</td>
    </tr>
    <tr>
      <th>700</th>
      <td>0</td>
      <td>0</td>
      <td>The chips that came out were dripping with gre...</td>
      <td>chips came dripping grease mostly not edible</td>
    </tr>
    <tr>
      <th>581</th>
      <td>0</td>
      <td>1</td>
      <td>Over rated.</td>
      <td>rated</td>
    </tr>
    <tr>
      <th>808</th>
      <td>1</td>
      <td>1</td>
      <td>The first time I ever came here I had an amazi...</td>
      <td>first time ever came amazing experience still ...</td>
    </tr>
    <tr>
      <th>94</th>
      <td>0</td>
      <td>1</td>
      <td>say bye bye to your tip lady!</td>
      <td>say bye bye tip lady</td>
    </tr>
    <tr>
      <th>915</th>
      <td>0</td>
      <td>0</td>
      <td>Needless to say, I won't be going back anytime...</td>
      <td>needless say wont going back anytime soon</td>
    </tr>
    <tr>
      <th>59</th>
      <td>0</td>
      <td>0</td>
      <td>The ripped banana was not only ripped, but pet...</td>
      <td>ripped banana not ripped petrified tasteless</td>
    </tr>
    <tr>
      <th>703</th>
      <td>1</td>
      <td>1</td>
      <td>Our server was very nice and attentive as were...</td>
      <td>server nice attentive serving staff</td>
    </tr>
  </tbody>
</table>
</div>



Metrics:


```python
from sklearn.metrics import accuracy_score, f1_score
```


```python
print("-" * 75)
print("Logistic regression scores:")
print("Accuracy score:", accuracy_score(test[target], test["Prediction_Logistic"]))
print("F1 score:", f1_score(test[target], test["Prediction_Logistic"]))
print("-" * 75)
```

    ---------------------------------------------------------------------------
    Logistic regression scores:
    Accuracy score: 0.7286432160804021
    F1 score: 0.7032967032967034
    ---------------------------------------------------------------------------


### Random Forest


```python
model_rf = RandomForestClassifier(
    n_estimators = 500,
    max_depth = 25,
    random_state = 1
).fit(train[features], train[target])
```


```python
test["Prediction_RF"] = model_rf.predict(test[features])
test[["Sentiment", "Prediction_Logistic", "Prediction_RF", "Review", "Review_Clean"]].sample(20, random_state = 2)
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
      <th>Sentiment</th>
      <th>Prediction_Logistic</th>
      <th>Prediction_RF</th>
      <th>Review</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>945</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>It wasn't busy at all and now we know why.</td>
      <td>wasnt busy know</td>
    </tr>
    <tr>
      <th>543</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>I won't try going back there even if it's empty.</td>
      <td>wont try going back even empty</td>
    </tr>
    <tr>
      <th>50</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>We ordered the duck rare and it was pink and t...</td>
      <td>ordered duck rare pink tender inside nice char...</td>
    </tr>
    <tr>
      <th>962</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Hell no will I go back</td>
      <td>hell no go back</td>
    </tr>
    <tr>
      <th>233</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Ordered a double cheeseburger &amp; got a single p...</td>
      <td>ordered double cheeseburger got single patty f...</td>
    </tr>
    <tr>
      <th>599</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Not good for the money.</td>
      <td>not good money</td>
    </tr>
    <tr>
      <th>874</th>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>Now the burgers aren't as good, the pizza whic...</td>
      <td>burgers arent good pizza used amazing doughy f...</td>
    </tr>
    <tr>
      <th>148</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>I give it 2 thumbs down</td>
      <td>give 2 thumbs</td>
    </tr>
    <tr>
      <th>175</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Perhaps I caught them on an off night judging ...</td>
      <td>perhaps caught night judging reviews im not in...</td>
    </tr>
    <tr>
      <th>274</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>The chefs were friendly and did a good job.</td>
      <td>chefs friendly good job</td>
    </tr>
    <tr>
      <th>370</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>I left with a stomach ache and felt sick the r...</td>
      <td>left stomach ache felt sick rest day</td>
    </tr>
    <tr>
      <th>509</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Thoroughly disappointed!</td>
      <td>thoroughly disappointed</td>
    </tr>
    <tr>
      <th>345</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>Pretty good beer selection too.</td>
      <td>pretty good beer selection</td>
    </tr>
    <tr>
      <th>700</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>The chips that came out were dripping with gre...</td>
      <td>chips came dripping grease mostly not edible</td>
    </tr>
    <tr>
      <th>581</th>
      <td>0</td>
      <td>1</td>
      <td>0</td>
      <td>Over rated.</td>
      <td>rated</td>
    </tr>
    <tr>
      <th>808</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>The first time I ever came here I had an amazi...</td>
      <td>first time ever came amazing experience still ...</td>
    </tr>
    <tr>
      <th>94</th>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>say bye bye to your tip lady!</td>
      <td>say bye bye tip lady</td>
    </tr>
    <tr>
      <th>915</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Needless to say, I won't be going back anytime...</td>
      <td>needless say wont going back anytime soon</td>
    </tr>
    <tr>
      <th>59</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>The ripped banana was not only ripped, but pet...</td>
      <td>ripped banana not ripped petrified tasteless</td>
    </tr>
    <tr>
      <th>703</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>Our server was very nice and attentive as were...</td>
      <td>server nice attentive serving staff</td>
    </tr>
  </tbody>
</table>
</div>




```python
print("-" * 75)
print("Random forest scores:")
print("Accuracy score:", accuracy_score(test[target], test["Prediction_RF"]))
print("F1 score:", f1_score(test[target], test["Prediction_RF"]))
print("-" * 75)
```

    ---------------------------------------------------------------------------
    Random forest scores:
    Accuracy score: 0.7989949748743719
    F1 score: 0.7560975609756098
    ---------------------------------------------------------------------------


### Neural Networks


```python
model_nn = MLPClassifier(
    hidden_layer_sizes = (50, 50, 50),
    solver = "lbfgs",
    max_iter = 1000,
    activation = "relu",
    random_state = 1
).fit(train[features], train[target])
```


```python
test["Prediction_MLP"] = model_nn.predict(test[features])
test[["Sentiment", "Prediction_Logistic", "Prediction_RF", "Prediction_MLP", "Review", "Review_Clean"]].sample(20, random_state = 2)
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
      <th>Sentiment</th>
      <th>Prediction_Logistic</th>
      <th>Prediction_RF</th>
      <th>Prediction_MLP</th>
      <th>Review</th>
      <th>Review_Clean</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>945</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>It wasn't busy at all and now we know why.</td>
      <td>wasnt busy know</td>
    </tr>
    <tr>
      <th>543</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>I won't try going back there even if it's empty.</td>
      <td>wont try going back even empty</td>
    </tr>
    <tr>
      <th>50</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>We ordered the duck rare and it was pink and t...</td>
      <td>ordered duck rare pink tender inside nice char...</td>
    </tr>
    <tr>
      <th>962</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Hell no will I go back</td>
      <td>hell no go back</td>
    </tr>
    <tr>
      <th>233</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Ordered a double cheeseburger &amp; got a single p...</td>
      <td>ordered double cheeseburger got single patty f...</td>
    </tr>
    <tr>
      <th>599</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Not good for the money.</td>
      <td>not good money</td>
    </tr>
    <tr>
      <th>874</th>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>Now the burgers aren't as good, the pizza whic...</td>
      <td>burgers arent good pizza used amazing doughy f...</td>
    </tr>
    <tr>
      <th>148</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>I give it 2 thumbs down</td>
      <td>give 2 thumbs</td>
    </tr>
    <tr>
      <th>175</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Perhaps I caught them on an off night judging ...</td>
      <td>perhaps caught night judging reviews im not in...</td>
    </tr>
    <tr>
      <th>274</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>The chefs were friendly and did a good job.</td>
      <td>chefs friendly good job</td>
    </tr>
    <tr>
      <th>370</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>1</td>
      <td>I left with a stomach ache and felt sick the r...</td>
      <td>left stomach ache felt sick rest day</td>
    </tr>
    <tr>
      <th>509</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Thoroughly disappointed!</td>
      <td>thoroughly disappointed</td>
    </tr>
    <tr>
      <th>345</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>Pretty good beer selection too.</td>
      <td>pretty good beer selection</td>
    </tr>
    <tr>
      <th>700</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>The chips that came out were dripping with gre...</td>
      <td>chips came dripping grease mostly not edible</td>
    </tr>
    <tr>
      <th>581</th>
      <td>0</td>
      <td>1</td>
      <td>0</td>
      <td>0</td>
      <td>Over rated.</td>
      <td>rated</td>
    </tr>
    <tr>
      <th>808</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>The first time I ever came here I had an amazi...</td>
      <td>first time ever came amazing experience still ...</td>
    </tr>
    <tr>
      <th>94</th>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>say bye bye to your tip lady!</td>
      <td>say bye bye tip lady</td>
    </tr>
    <tr>
      <th>915</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>Needless to say, I won't be going back anytime...</td>
      <td>needless say wont going back anytime soon</td>
    </tr>
    <tr>
      <th>59</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>1</td>
      <td>The ripped banana was not only ripped, but pet...</td>
      <td>ripped banana not ripped petrified tasteless</td>
    </tr>
    <tr>
      <th>703</th>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>Our server was very nice and attentive as were...</td>
      <td>server nice attentive serving staff</td>
    </tr>
  </tbody>
</table>
</div>




```python
index = 874
print(test[["Review"]].loc[index].values)
print(test[["Review_Clean"]].loc[index].values)
```

    ["Now the burgers aren't as good, the pizza which used to be amazing is doughy and flavorless."]
    ['burgers arent good pizza used amazing doughy flavorless']



```python
print("-" * 75)
print("Logistic regression scores:")
print("Accuracy score:", accuracy_score(test[target], test["Prediction_Logistic"]))
print("F1 score:", f1_score(test[target], test["Prediction_Logistic"]))
print("-" * 75)
print("Random forest scores:")
print("Accuracy score:", accuracy_score(test[target], test["Prediction_RF"]))
print("F1 score:", f1_score(test[target], test["Prediction_RF"]))
print("-" * 75)
print("Neural Networks scores:")
print("Accuracy score:", accuracy_score(test[target], test["Prediction_MLP"]))
print("F1 score:", f1_score(test[target], test["Prediction_MLP"]))
print("-" * 75)
```

    ---------------------------------------------------------------------------
    Logistic regression scores:
    Accuracy score: 0.7286432160804021
    F1 score: 0.7032967032967034
    ---------------------------------------------------------------------------
    Random forest scores:
    Accuracy score: 0.7989949748743719
    F1 score: 0.7560975609756098
    ---------------------------------------------------------------------------
    Neural Networks scores:
    Accuracy score: 0.7336683417085427
    F1 score: 0.7103825136612022
    ---------------------------------------------------------------------------



```python

```
