---
layout: post
title: Fake and Real News Detector
subtitle:  Classification and Sentiment Analysis of Fake and Real News
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [Sentiment Analysis,Tokenization, Text Analysis,xgboost,Plotly express]
---

### Introduction

Fake news include false news stories,disinformation and misinformation with the intent of misleading people. The proliferation of fake news in recent years poses great danger to the safety and security of many people around the world. Some people have acted on fake news to commit certain crimes which are unpardonable. The growth of the internet and social media around the world has helped to explode  the consumption of fake news and conspiracy theories around the world. Determining if a piece of news item is fake or real is not so obvious these days especially when the perpetrators create websites with similar names like well-known authentic  news outlets. In this post we will try to do in-depth exploratory analysis and comparison of real and fake new. We will look at negativity, positivity and neutrality in sentiments expressed in both fake and real news. We would end by demonstrating how we can predict whether a news item is fake or real with a classification model.

The dataset for this analysis is located on kaggle. Find the link [here](https://www.kaggle.com/clmentbisaillon/fake-and-real-news-dataset).


```python
#!pip install gensim # Gensim is an open-source library for unsupervised topic modeling and natural language processing
```


```python
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import os
import nltk
nltk.download('punkt')
nltk.download('stopwords')
nltk.download('wordnet')
from  nltk.stem import SnowballStemmer
from nltk.stem import WordNetLemmatizer
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from wordcloud import WordCloud, STOPWORDS
import re
from nltk.corpus import stopwords
import seaborn as sns 
import gensim
from gensim.utils import simple_preprocess
from gensim.parsing.preprocessing import STOPWORDS
import matplotlib.pyplot as plt
import plotly
import seaborn as sns
from plotly import graph_objs as go
import plotly.express as px
import plotly.figure_factory as ff
from collections import Counter
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_auc_score
from sklearn.metrics import confusion_matrix
from tqdm import tqdm
import itertools
import collections
from xgboost import XGBClassifier
import xgboost as xgb
%matplotlib inline
%autosave 5
```

    [nltk_data] Downloading package punkt to /root/nltk_data...
    [nltk_data]   Package punkt is already up-to-date!
    [nltk_data] Downloading package stopwords to /root/nltk_data...
    [nltk_data]   Package stopwords is already up-to-date!
    [nltk_data] Downloading package wordnet to /root/nltk_data...
    [nltk_data]   Package wordnet is already up-to-date!
    



    Autosaving every 5 seconds
    


```python
import warnings
warnings.filterwarnings("ignore")
from tqdm.notebook import tqdm
tqdm.pandas(desc="Completed") # add progressbar to pandas, use progress_apply instead apply
import plotly.figure_factory as ff
import plotly.graph_objects as go
import plotly.express as px
from ipywidgets import interact #interactive plots
from IPython.display import clear_output
```


```python
from google.colab import drive
drive.mount('/content/drive')
```

    Drive already mounted at /content/drive; to attempt to forcibly remount, call drive.mount("/content/drive", force_remount=True).
    



```python
!unzip /content/drive/MyDrive/Data/Fake_True_News.zip
True_data = pd.read_csv('True.csv')
True_data['label']= 1
Fake_data = pd.read_csv('Fake.csv')
Fake_data['label']=0
True_data.head()
```

    Archive:  /content/drive/MyDrive/Data/Fake_True_News.zip
    replace Fake.csv? [y]es, [n]o, [A]ll, [N]one, [r]ename: yes
      inflating: Fake.csv                
    replace True.csv? [y]es, [n]o, [A]ll, [N]one, [r]ename: yes
      inflating: True.csv                
    




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
      <th>title</th>
      <th>text</th>
      <th>subject</th>
      <th>date</th>
      <th>label</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>As U.S. budget fight looms, Republicans flip t...</td>
      <td>WASHINGTON (Reuters) - The head of a conservat...</td>
      <td>politicsNews</td>
      <td>December 31, 2017</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>U.S. military to accept transgender recruits o...</td>
      <td>WASHINGTON (Reuters) - Transgender people will...</td>
      <td>politicsNews</td>
      <td>December 29, 2017</td>
      <td>1</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Senior U.S. Republican senator: 'Let Mr. Muell...</td>
      <td>WASHINGTON (Reuters) - The special counsel inv...</td>
      <td>politicsNews</td>
      <td>December 31, 2017</td>
      <td>1</td>
    </tr>
    <tr>
      <th>3</th>
      <td>FBI Russia probe helped by Australian diplomat...</td>
      <td>WASHINGTON (Reuters) - Trump campaign adviser ...</td>
      <td>politicsNews</td>
      <td>December 30, 2017</td>
      <td>1</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Trump wants Postal Service to charge 'much mor...</td>
      <td>SEATTLE/WASHINGTON (Reuters) - President Donal...</td>
      <td>politicsNews</td>
      <td>December 29, 2017</td>
      <td>1</td>
    </tr>
  </tbody>
</table>
</div>




```python
df = pd.concat([True_data,Fake_data],axis=0)
print(df.shape)
print(type(df.label))
df.info()
```

    (44898, 5)
    <class 'pandas.core.series.Series'>
    <class 'pandas.core.frame.DataFrame'>
    Int64Index: 44898 entries, 0 to 23480
    Data columns (total 5 columns):
     #   Column   Non-Null Count  Dtype 
    ---  ------   --------------  ----- 
     0   title    44898 non-null  object
     1   text     44898 non-null  object
     2   subject  44898 non-null  object
     3   date     44898 non-null  object
     4   label    44898 non-null  int64 
    dtypes: int64(1), object(4)
    memory usage: 2.1+ MB
    


```python
#df= df.sample(frac=0.1)
df.shape
```




    (44898, 5)




```python
# Create and register a new `tqdm` instance with `pandas`
# (can use tqdm_gui, optional kwargs, etc.)
tqdm.pandas()
#df["title"] = df["title"].progress_apply(preprocess)
#df["text"] = df["text"].progress_apply(preprocess)
```


```python
from sklearn.utils import shuffle
df = shuffle(df)
df.head()
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
      <th>title</th>
      <th>text</th>
      <th>subject</th>
      <th>date</th>
      <th>label</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>13936</th>
      <td>FORMER MEXICAN PREZ Sends “Middle Finger” To T...</td>
      <td>Wow these sound exactly like the type of peopl...</td>
      <td>politics</td>
      <td>May 10, 2016</td>
      <td>0</td>
    </tr>
    <tr>
      <th>10132</th>
      <td>OOPS! NY GOV CUOMO Announces Statues of Confed...</td>
      <td>Really Andrew? Does all of New York really sta...</td>
      <td>politics</td>
      <td>Aug 17, 2017</td>
      <td>0</td>
    </tr>
    <tr>
      <th>7518</th>
      <td>Janet Reno, first U.S. woman attorney general,...</td>
      <td>(Reuters) - Blunt-spoken Janet Reno, who serve...</td>
      <td>politicsNews</td>
      <td>November 7, 2016</td>
      <td>1</td>
    </tr>
    <tr>
      <th>17792</th>
      <td>Murdered North Korean Kim Jong Nam had $100,00...</td>
      <td>KUALA LUMPUR (Reuters) - The half-brother of N...</td>
      <td>worldnews</td>
      <td>October 11, 2017</td>
      <td>1</td>
    </tr>
    <tr>
      <th>22509</th>
      <td>PROPAGANDA: Star Trek Beyond – Social Justice ...</td>
      <td>Jay Dyer 21st Century WireThe last Star Trek r...</td>
      <td>US_News</td>
      <td>August 2, 2016</td>
      <td>0</td>
    </tr>
  </tbody>
</table>
</div>



The gensim.utils.simple_process utility can be used to accomplish some of the basic common text preprocessing and cleaning  such as tokenization and removing stop words.


```python
stop_words = stopwords.words('english')
stop_words.extend(['said','say','from', 'subject', 're', 'edu', 'use'])
lemmatizer = WordNetLemmatizer() 
stemmer = SnowballStemmer("english")


def preprocess(text):
    result = []
    for token in gensim.utils.simple_preprocess(text):
        if token not in gensim.parsing.preprocessing.STOPWORDS and len(token) > 2 and token not in stop_words:
           #token = [stemmer.stem(token)  for token in text.split() ]
           result.append(lemmatizer.lemmatize(token))
    return result
```


```python
#@title Default title text
df["title"] = df["title"].apply(preprocess)
df["text"] = df["text"].apply(preprocess)
```

Combine title and text columns, this will later be used to demonstrate if classification performance improves  with this combination over using either title or text column alone to predict whether the news is Fake or Real.


```python
df["title_text"] = df["text"]+df["title"]
```


```python
df.subject.value_counts()
```




    politicsNews       11272
    worldnews          10145
    News                9050
    politics            6841
    left-news           4459
    Government News     1570
    US_News              783
    Middle-east          778
    Name: subject, dtype: int64



Looking at the subjects we can combine related subjects such  politicsNews and politics to politicsNews.


```python
df.subject.replace({'politics':'politicsNews'},inplace=True)
```


```python
#df['label'] = df['label'].astype(str)
df["label"].replace({0:"Fake",  1:"Real"},inplace=True)
df["label"].value_counts()
```




    Fake    23481
    Real    21417
    Name: label, dtype: int64



#### What is the distribution of Subjects between the True and Fake News?


```python
temp=df.groupby('label').apply(lambda x:x['title'].count()).reset_index(name='Counts')
#temp.label.replace({0:'False',1:'True'},inplace=True)
temp.style.background_gradient(cmap='Purples')
```




<style  type="text/css" >
#T_ff093a42_5f74_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #3f007d;
            color:  #f1f1f1;
        }#T_ff093a42_5f74_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #fcfbfd;
            color:  #000000;
        }</style><table id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >label</th>        <th class="col_heading level0 col1" >Counts</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >Fake</td>
                        <td id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >23481</td>
            </tr>
            <tr>
                        <th id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >Real</td>
                        <td id="T_ff093a42_5f74_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >21417</td>
            </tr>
    </tbody></table>




```python
#Let's draw a Funnel-Chart for better visualization
fig = go.Figure(go.Funnelarea(
    text =temp.label,
    values = temp.Counts,
    title = {"position": "top center", "text": "Funnel-Chart of News Distribution"}
    ))
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)

fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file1.html")
```


<iframe src="/img/FakeNewsDetector/file1.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




```python
temp=df.groupby('label').apply(lambda x:x['title'].count()).reset_index(name='Counts')
#sub_tf_df.label.replace({0:'False',1:'True'},inplace=True)
fig = px.bar(temp, x="label", y="Counts",
             color='Counts', barmode='group',
             title =  "Frequency of Real and Fake News Distribution",
             height=400)

fig.update_layout(
    font_family="Courier New",
    font_color="white",
    title_font_family="Times New Roman",
    title_font_color="white"
   # legend_title_font_color="green"
)
fig.update_xaxes(title_font_family="Arial")
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="plotly_dark")
#fig =px.scatter(x=range(10), y=range(10))
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file2.html")
fig.show()
```


<iframe src="/img/FakeNewsDetector/file2.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>


#### Common Words in News  Fake News Title


```python
top = Counter([item for sublist in df[df.label == "Fake"]["title"] for item in sublist])
temp = pd.DataFrame(top.most_common(20))
temp.columns = ['Common_words','count']
temp.style.background_gradient(cmap='Greens')
```




<style  type="text/css" >
#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #00441b;
            color:  #f1f1f1;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #006227;
            color:  #f1f1f1;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #cfecc9;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #d7efd1;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #e1f3dc;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row5_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #f0f9ec;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #f2faf0;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #f4fbf1;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row9_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row10_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row11_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row12_col1{
            background-color:  #f4fbf2;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row13_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row15_col1{
            background-color:  #f5fbf2;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row16_col1{
            background-color:  #f5fbf3;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row17_col1,#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row18_col1{
            background-color:  #f6fcf4;
            color:  #000000;
        }#T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #f7fcf5;
            color:  #000000;
        }</style><table id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >Common_words</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >trump</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >9350</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >video</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >8558</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >obama</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >2582</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >hillary</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >2322</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >watch</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >1941</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >clinton</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >1175</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >president</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >1165</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >black</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >975</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >tweet</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >936</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >white</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >905</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >new</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >905</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >breaking</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >896</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >news</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >883</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >republican</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >867</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >donald</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >848</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >muslim</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >842</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >gop</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >807</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >american</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >772</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >democrat</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >772</td>
            </tr>
            <tr>
                        <th id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >america</td>
                        <td id="T_0fab6bae_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >703</td>
            </tr>
    </tbody></table>




```python
fig = px.bar(temp, x="count", y="Common_words", title='Commmon Words in Fake News Titles', orientation='h', 
             width=700, height=700,color='Common_words')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="plotly_white")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file3.html")
```

<iframe src="/img/FakeNewsDetector/file3.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>



#### Common Words in News Real News Title


```python
top = Counter([item for sublist in df[df.label == "Real"]["title"] for item in sublist])
temp = pd.DataFrame(top.most_common(20))
temp.columns = ['Common_words','count']
temp.style.background_gradient(cmap='Purples')

```




<style  type="text/css" >
#T_1a299132_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #3f007d;
            color:  #f1f1f1;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #a3a0cb;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #e7e6f1;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row3_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #f4f3f8;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #f5f4f9;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #f6f4f9;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #f6f5f9;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row8_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #f8f6fa;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #f8f7fb;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row11_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row12_col1{
            background-color:  #f9f7fb;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row13_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row15_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row16_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row17_col1{
            background-color:  #fbfafc;
            color:  #000000;
        }#T_1a299132_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_1a299132_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #fcfbfd;
            color:  #000000;
        }</style><table id="T_1a299132_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >Common_words</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >trump</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >5567</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >say</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >2981</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >house</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >1452</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >russia</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >977</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >republican</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >976</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >north</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >926</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >korea</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >898</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >new</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >875</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >state</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >825</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >white</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >818</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >china</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >782</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >senate</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >759</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >court</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >753</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >tax</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >666</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >obama</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >665</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >clinton</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >659</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >election</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >656</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >vote</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >640</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >talk</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >597</td>
            </tr>
            <tr>
                        <th id="T_1a299132_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >leader</td>
                        <td id="T_1a299132_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >597</td>
            </tr>
    </tbody></table>




```python
fig = px.bar(temp, x="count", y="Common_words", title='Commmon Words in Real news Titles', orientation='h', 
             width=700, height=700,color='Common_words')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="plotly_dark")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file4.html")
```


<iframe src="/img/FakeNewsDetector/file4.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>





#### Which Subjects have received the most News Coverage?


```python
temp=df.groupby('subject').apply(lambda x:x['title'].count()).reset_index(name='Counts')
fig=px.bar(temp,x='subject',y='Counts',color='Counts',title='Count of News Articles by Subject')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file2.html")
fig.update_layout( template="plotly_dark")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file5.html")
```

<iframe src="/img/FakeNewsDetector/file5.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




#### Exploring Co-occurring Words (Bigrams)
Let's now explore certain words which occuur together in the tweets. Such words are called bigrams.A bigram or digram is a sequence of two adjacent elements from a string of tokens, which are typically letters, syllables, or words



```python
from nltk import bigrams,trigrams,ngrams
# Create list of lists containing bigrams in tweets
terms_bigram = [list(bigrams(text)) for text in df[df.label == "Real"]["text"]]

# Flatten list of bigrams in clean tweets
bigrams_all = list(itertools.chain(*terms_bigram))

# Create counter of words in clean bigrams
bigram_counts = collections.Counter(bigrams_all)

bigram_df = pd.DataFrame(bigram_counts.most_common(20),
                             columns=['bigram', 'count'])
bigram_df.style.background_gradient(cmap='Purples')
```




<style  type="text/css" >
#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #3f007d;
            color:  #f1f1f1;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #62429c;
            color:  #f1f1f1;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #827fbb;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #adabd2;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #bebfdd;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #c5c6e1;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #dbdbec;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #e4e3f0;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row8_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #f0eef5;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #f1f0f6;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #f3f1f7;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row12_col1{
            background-color:  #f5f4f9;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row13_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row15_col1{
            background-color:  #faf9fc;
            color:  #000000;
        }#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row16_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row17_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #fcfbfd;
            color:  #000000;
        }</style><table id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >bigram</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >('united', 'state')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >12215</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >('donald', 'trump')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >10169</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >('white', 'house')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >8419</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >('washington', 'reuters')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >6674</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >('president', 'donald')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >5930</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >('north', 'korea')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >5659</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >('new', 'york')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >4740</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >('prime', 'minister')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >4206</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >('told', 'reuters')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >3496</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >('islamic', 'state')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >3477</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >('barack', 'obama')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >3344</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >('told', 'reporter')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >3189</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >('president', 'barack')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >2960</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >('hillary', 'clinton')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >2499</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >('supreme', 'court')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >2481</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >('trump', 'administration')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >2477</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >('reuters', 'president')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >2394</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >('year', 'old')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >2334</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >('united', 'nation')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >2322</td>
            </tr>
            <tr>
                        <th id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >('secretary', 'state')</td>
                        <td id="T_37bfc54a_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >2317</td>
            </tr>
    </tbody></table>




```python
#df = title_per.to_frame().round(1)
fig.update_layout(
    title_text="High Frequency Bigrams  in Real News",
    # Add annotations in the center of the donut pies.
    annotations=[dict(text='High Frequency ', x=0.5, y=0.5, font_size=14, showarrow=False)])
fig = px.pie(bigram_df, values=bigram_df['count'].values, names= bigram_df.bigram, color_discrete_sequence=px.colors.sequential.YlGnBu,
             title='High Frquency Bigrams for Real News')
fig.update_traces(textposition='inside', textinfo='percent')
fig.update_layout(
   # autosize=False,
    width=800,
    height=800,
   
)
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file6.html")
```


<iframe src="/img/FakeNewsDetector/file6.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="800"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>





#### Bigrams  of Fake News Headlines


```python
# Create list of lists containing bigrams in tweets
terms_bigram = [list(bigrams(text)) for text in df[df.label == "Fake"]["text"]]

# Flatten list of bigrams in clean tweets
bigrams_all = list(itertools.chain(*terms_bigram))

# Create counter of words in clean bigrams
bigram_counts = collections.Counter(bigrams_all)

bigram_df = pd.DataFrame(bigram_counts.most_common(20),
                             columns=['bigram', 'count'])
bigram_df.style.background_gradient(cmap='Purples')
```




<style  type="text/css" >
#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #3f007d;
            color:  #f1f1f1;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #aeadd3;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #bbbbdb;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #c4c5e0;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #c6c7e1;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #c8c8e2;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #cdcde4;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #e6e5f1;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row8_col1,#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #eae8f2;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #eae9f3;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #f0eef5;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row12_col1{
            background-color:  #f2f0f7;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row13_col1{
            background-color:  #f8f7fa;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row14_col1{
            background-color:  #faf9fc;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row15_col1,#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row16_col1{
            background-color:  #fbfafc;
            color:  #000000;
        }#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row17_col1,#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #fcfbfd;
            color:  #000000;
        }</style><table id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >bigram</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >('donald', 'trump')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >16402</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >('featured', 'image')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >8069</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >('hillary', 'clinton')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >7312</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >('white', 'house')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >6749</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >('united', 'state')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >6674</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >('twitter', 'com')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >6567</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >('pic', 'twitter')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >6232</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >('new', 'york')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >4361</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >('president', 'obama')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >4104</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >('president', 'trump')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >4065</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >('getty', 'image')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >4029</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >('fox', 'news')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >3524</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >('year', 'old')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >3248</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >('barack', 'obama')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >2352</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >('trump', 'supporter')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >2086</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >('century', 'wire')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >1930</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >('trump', 'campaign')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >1903</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >('supreme', 'court')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >1827</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >('fake', 'news')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >1818</td>
            </tr>
            <tr>
                        <th id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >('secretary', 'state')</td>
                        <td id="T_6da0e1da_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >1764</td>
            </tr>
    </tbody></table>




```python
colors = ['mediumturquoise','gold' ]
colors1 = ['#F4D03F','#82E0AA', "#F1948A",]


# Use `hole` to create a donut-like pie chart
fig = go.Figure(data=[go.Pie(labels= bigram_df.bigram, values=bigram_df['count'], hole=.4)])

fig.update_traces(hoverinfo='label+value', textinfo='percent', textfont_size=15,
                  marker=dict(colors=px.colors.sequential.YlGnBu, line=dict(color='#000000', width=1)))

fig.update_layout(
   # autosize=False,
    width=800,
    height=800,
   
)
fig.update_layout(
    title_text="High Frequency Bigrams in Fake News ",
    # Add annotations in the center of the donut pies.
    annotations=[dict(text=' ', x=0.5, y=0.5, font_size=14, showarrow=False)])
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file7.html")
```



<iframe src="/img/FakeNewsDetector/file7.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="800"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>









#### Trigrams of Fake News



```python
#list(ngrams(df.text.values[0],n=4))
# Create list of lists containing bigrams in tweets
#trigram = [list(bigrams(tweet)) for tweet in df[df.label == "Fake"]["text"]]
trigram = [list(ngrams(text,n=3)) for text in df[df.label == "Fake"]["text"]]

# Flatten list of bigrams in clean tweets
trigram_all = list(itertools.chain(*trigram))

# Create counter of words in clean bigrams
trigram_counts = collections.Counter(trigram_all)
trigram_df = pd.DataFrame(trigram_counts.most_common(20),
                             columns=['trigram', 'count'])
trigram_df.style.background_gradient(cmap='Blues')
```




<style  type="text/css" >
#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #08306b;
            color:  #f1f1f1;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #cee0f2;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #d2e3f3;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #dbe9f6;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #e4eff9;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #e5eff9;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #e7f1fa;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #e8f1fa;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #eaf2fb;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row9_col1,#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #eff6fc;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #f1f7fd;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row12_col1{
            background-color:  #f2f8fd;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row13_col1{
            background-color:  #f4f9fe;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row15_col1,#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row16_col1{
            background-color:  #f5f9fe;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row17_col1{
            background-color:  #f6faff;
            color:  #000000;
        }#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #f7fbff;
            color:  #000000;
        }</style><table id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >trigram</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >('pic', 'twitter', 'com')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >6185</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >('donald', 'trump', 'realdonaldtrump')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >1692</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >('new', 'york', 'time')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >1581</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >('black', 'life', 'matter')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >1319</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >('president', 'donald', 'trump')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >1049</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >('president', 'united', 'state')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >1015</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >('president', 'barack', 'obama')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >953</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >('news', 'century', 'wire')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >939</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >('featured', 'image', 'video')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >887</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >('century', 'wire', 'say')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >733</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >('video', 'screen', 'capture')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >731</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >('image', 'video', 'screen')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >697</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >('new', 'york', 'city')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >651</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >('featured', 'image', 'screenshot')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >607</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >('www', 'youtube', 'com')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >577</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >('youtube', 'com', 'watch')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >575</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >('http', 'www', 'youtube')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >571</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >('image', 'screen', 'capture')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >529</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >('director', 'james', 'comey')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >518</td>
            </tr>
            <tr>
                        <th id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >('fbi', 'director', 'james')</td>
                        <td id="T_981ec0ee_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >500</td>
            </tr>
    </tbody></table>




```python
#fig = px.bar(trigram_df, x="count", y="trigram", title='Trigrams in Fake News', orientation='h', 
#             width=700, height=700)
#fig.show()
# plot
sns.set_style('ticks')
fig, ax = plt.subplots()
# the size of A4 paper
fig.set_size_inches(10, 7)
ax = sns.barplot(x="count", y="trigram", data=trigram_df,
                 palette="Blues_d")
plt.title('Trigrams of Fake News')
plt.show()
```


    
![png](/img/FakeNewsDetector/output_38_0.png)
    


#### Trigrams of Real News


```python
trigram = [list(ngrams(text,n=3)) for text in df[df.label == "Real"]["text"]]

# Flatten list of bigrams in clean tweets
trigram_all = list(itertools.chain(*trigram))

# Create counter of words in clean bigrams
trigram_counts = collections.Counter(trigram_all)
trigram_df = pd.DataFrame(trigram_counts.most_common(20),
                             columns=['trigram', 'count'])
trigram_df.style.background_gradient(cmap='Blues')
```




<style  type="text/css" >
#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #08306b;
            color:  #f1f1f1;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #7db8da;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #d1e2f3;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #d3e3f3;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row4_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #ecf4fb;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #edf4fc;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row7_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #eef5fc;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row9_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #f2f8fd;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #f4f9fe;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row12_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row13_col1{
            background-color:  #f5f9fe;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row15_col1{
            background-color:  #f5fafe;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row16_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row17_col1{
            background-color:  #f6faff;
            color:  #000000;
        }#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_b852c82e_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #f7fbff;
            color:  #000000;
        }</style><table id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >trigram</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >('president', 'donald', 'trump')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >5869</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >('president', 'barack', 'obama')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >2960</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >('reuters', 'president', 'donald')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >1562</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >('washington', 'reuters', 'president')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >1533</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >('new', 'york', 'reuters')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >845</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >('elect', 'donald', 'trump')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >834</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >('president', 'elect', 'donald')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >832</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >('respond', 'request', 'comment')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >806</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >('president', 'vladimir', 'putin')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >791</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >('state', 'rex', 'tillerson')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >673</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >('secretary', 'state', 'rex')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >672</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >('national', 'security', 'adviser')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >639</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >('russian', 'president', 'vladimir')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >613</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >('speaker', 'paul', 'ryan')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >608</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >('washington', 'reuters', 'republican')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >603</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >('prime', 'minister', 'theresa')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >584</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >('chancellor', 'angela', 'merkel')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >570</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >('leader', 'mitch', 'mcconnell')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >568</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >('democratic', 'president', 'barack')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >550</td>
            </tr>
            <tr>
                        <th id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >('republican', 'presidential', 'candidate')</td>
                        <td id="T_b852c82e_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >541</td>
            </tr>
    </tbody></table>




```python
sns.set_style('ticks')
fig, ax = plt.subplots()
# the size of A4 paper
fig.set_size_inches(10, 7)
ax = sns.barplot(x="count", y="trigram", data=trigram_df,
                 palette="Blues_d")
plt.title('Trigrams of Real News')
plt.show()
```


    
![png](/img/FakeNewsDetector/output_41_0.png)
   






#### Word Cloud using the Real News


```python
top = Counter([item for sublist in df[df.label == "Real"]["text"] for item in sublist])
temp = pd.DataFrame(top.most_common(20))
temp.columns = ['Common_words','count']
temp.style.background_gradient(cmap='Blues')
```




<style  type="text/css" >
#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #08306b;
            color:  #f1f1f1;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #4695c8;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #8dc1dd;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #91c3de;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #bdd7ec;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #bfd8ed;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #cde0f1;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #dae8f6;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #dbe9f6;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #e1edf8;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #e2edf8;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #e3eef8;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row12_col1,#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row13_col1{
            background-color:  #e5eff9;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row15_col1{
            background-color:  #e7f1fa;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row16_col1{
            background-color:  #edf4fc;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row17_col1,#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row18_col1{
            background-color:  #f5fafe;
            color:  #000000;
        }#T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #f7fbff;
            color:  #000000;
        }</style><table id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >Common_words</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >trump</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >54734</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >state</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >37678</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >reuters</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >28976</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >president</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >28728</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >republican</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >23007</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >year</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >22622</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >government</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >19992</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >house</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >17030</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >new</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >16917</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >united</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >15590</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >people</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >15356</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >party</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >15294</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >election</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >14759</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >official</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >14620</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >told</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >14245</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >country</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >14161</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >washington</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >12988</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >campaign</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >11155</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >group</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >11129</td>
            </tr>
            <tr>
                        <th id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >week</td>
                        <td id="T_c1e909a2_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >10658</td>
            </tr>
    </tbody></table>




```python
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from sklearn.model_selection import train_test_split # function for splitting data to train and test sets

import nltk
from nltk.corpus import stopwords
from nltk.classify import SklearnClassifier

from wordcloud import WordCloud,STOPWORDS
import matplotlib.pyplot as plt
%matplotlib inline


from subprocess import check_output
from os import path
from wordcloud import WordCloud

#d = path.dirname("/Users/nanaakwasiabayieboateng/PythonNLTK")




# Read the whole text.
#text = str(train['text'])

#stopwords = set(STOPWORDS)
#stopwords.add("Chrysler")

color = ['black','white'];

#background_color="white", max_words=2000, mask=text,
#               stopwords=stopwords, contour_width=3, contour_color='steelblue'
    
fig, (ax1, ax2,) = plt.subplots(1, 2, figsize=[26, 10])
sns.set_color_codes("pastel")   


wordcloud = WordCloud(max_words = 2000,  
                       width=1000,
                       height=800,
                       colormap='viridis',
                      max_font_size=80, min_font_size=2,  # Font size range
                      background_color=color[1],
                    margin=0,
                     
               stopwords = stop_words).generate("".join(str(df[df.label == "Real"].text.values)))
ax1.imshow(wordcloud, interpolation = 'bilinear')

sns.color_palette("viridis", as_cmap=True)
ax2= sns.barplot(y="Common_words", x="count", data=temp,
            label="Total",palette="viridis")
ax2.set_ylabel('')  
ax2.set_title('Word related to Positive News');
#ax1.imshow(wordcloud)
ax1.axis('off')
ax1.set_title('High Frequency Words');

```


    
![png](/img/FakeNewsDetector/output_44_0.png)


    


#### Word Cloud using the Real  News

#### Lets Look at the Count of Words Distribution in the Title


```python
top = Counter([item for sublist in df[df.label == "Fake"]["text"] for item in sublist])
temp = pd.DataFrame(top.most_common(20))
temp.columns = ['Common_words','count']
temp.style.background_gradient(cmap='Greens')
```




<style  type="text/css" >
#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #00441b;
            color:  #f1f1f1;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #c9eac2;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #cfecc9;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #daf0d4;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #e6f5e1;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row5_col1,#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row6_col1{
            background-color:  #e8f6e3;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #e8f6e4;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #e9f7e5;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #eaf7e6;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row10_col1{
            background-color:  #ebf7e7;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #edf8e9;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row12_col1,#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row13_col1{
            background-color:  #f1faee;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row14_col1,#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row15_col1{
            background-color:  #f2faef;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row16_col1{
            background-color:  #f2faf0;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row17_col1{
            background-color:  #f4fbf1;
            color:  #000000;
        }#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row18_col1,#T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row19_col1{
            background-color:  #f7fcf5;
            color:  #000000;
        }</style><table id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >Common_words</th>        <th class="col_heading level0 col1" >count</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >trump</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >80049</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >president</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >28406</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >people</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >26678</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >state</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >23663</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >clinton</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >19866</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >time</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >19199</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >year</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >19074</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >obama</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >18838</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >like</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >18667</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >american</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >18106</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >donald</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >17780</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >republican</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >16756</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row12" class="row_heading level0 row12" >12</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row12_col0" class="data row12 col0" >right</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row12_col1" class="data row12 col1" >14857</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row13" class="row_heading level0 row13" >13</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row13_col0" class="data row13 col0" >news</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row13_col1" class="data row13 col1" >14679</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row14" class="row_heading level0 row14" >14</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row14_col0" class="data row14 col0" >new</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row14_col1" class="data row14 col1" >14416</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row15" class="row_heading level0 row15" >15</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row15_col0" class="data row15 col0" >image</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row15_col1" class="data row15 col1" >14312</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row16" class="row_heading level0 row16" >16</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row16_col0" class="data row16 col0" >hillary</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row16_col1" class="data row16 col1" >14192</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row17" class="row_heading level0 row17" >17</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row17_col0" class="data row17 col0" >white</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row17_col1" class="data row17 col1" >13573</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row18" class="row_heading level0 row18" >18</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row18_col0" class="data row18 col0" >know</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row18_col1" class="data row18 col1" >12062</td>
            </tr>
            <tr>
                        <th id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002level0_row19" class="row_heading level0 row19" >19</th>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row19_col0" class="data row19 col0" >medium</td>
                        <td id="T_f0bd63e0_5f75_11eb_a08c_0242ac1c0002row19_col1" class="data row19 col1" >11847</td>
            </tr>
    </tbody></table>




```python
fig, (ax1, ax2,) = plt.subplots(1, 2, figsize=[26, 10])
sns.set_color_codes("pastel")   
color = ['black','white'];

wordcloud = WordCloud(max_words = 2000,  
                       width=1000,
                       height=800,
                       colormap='viridis',
                      max_font_size=80, min_font_size=2,  # Font size range
                      background_color=color[1],
                    margin=0,
                     
               stopwords = stop_words).generate("".join(str(df[df.label == "Fake"].text.values)))
ax1.imshow(wordcloud, interpolation = 'bilinear')

sns.color_palette("viridis", as_cmap=True)
ax2= sns.barplot(y="Common_words", x="count", data=temp,
            label="Total",palette="viridis")
ax2.set_ylabel('')  
ax2.set_title('Word related to Positive News');
#ax1.imshow(wordcloud)
ax1.axis('off')
ax1.set_title('High Frequency Words');

```


    
![png](/img/FakeNewsDetector/output_48_0.png)
    

 Donald Trunmp dominates the news whether fake or real.

#### Analysis Over Time


```python
import datetime
from IPython.display import display, HTML

df["date"] = pd.to_datetime(df["date"], errors='coerce')

df['year'] = df['date'].dt.year
df['month'] = df['date'].dt.month
df['day'] = df['date'].dt.day
h= df.head(2)

# render dataframe as html
html = h.to_html(render_links=True, index=False).replace('<th>','<th style = "background-color: #48c980">')
# write html to file 
text_file = open("/content/drive/MyDrive/Colab Notebooks/NLP/h.html", "w") 
text_file.write(html) 
text_file.close() 
HTML('h.html')


```

<iframe src="/img/FakeNewsDetector/h.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="800"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>






```python
import seaborn as sns
temp=df.groupby('year').apply(lambda x:x['text'].count()).reset_index(name='Counts')
temp.style.set_properties(**{'background-color': 'pink',
                            'color': 'black',
                            'border-color': 'white'})

temp.style.background_gradient(cmap='Greens')
```




<style  type="text/css" >
#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row0_col0,#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #f7fcf5;
            color:  #000000;
        }#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #e9f7e5;
            color:  #000000;
        }#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row1_col0{
            background-color:  #aedea7;
            color:  #000000;
        }#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #3fa85b;
            color:  #000000;
        }#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row2_col0{
            background-color:  #37a055;
            color:  #000000;
        }#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row2_col1,#T_8326f91c_5f76_11eb_a08c_0242ac1c0002row3_col0{
            background-color:  #00441b;
            color:  #f1f1f1;
        }</style><table id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >year</th>        <th class="col_heading level0 col1" >Counts</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >2015.000000</td>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >2479</td>
            </tr>
            <tr>
                        <th id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >2016.000000</td>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >16470</td>
            </tr>
            <tr>
                        <th id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >2017.000000</td>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >25904</td>
            </tr>
            <tr>
                        <th id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >2018.000000</td>
                        <td id="T_8326f91c_5f76_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >35</td>
            </tr>
    </tbody></table>




```python
temp=df.groupby('year').apply(lambda x:x['text'].count()).reset_index(name='Counts')
#temp['year'] = temp['year'].astype(str)

fig = px.bar(temp, x="year", y="Counts",color="Counts",text='Counts')
#fig = px.histogram(temp, x="year", y="Counts")
fig.update_layout(
    title=" Frequency of Words Used In News per  Year",
    xaxis_title="Year",
    yaxis_title="Frequency",
    #legend_title="",
    font=dict(
        family="Courier New, monospace",
        size=18,
        color="RebeccaPurple"
    )
)
#Forcing an axis to be categorical
fig.update_xaxes(type='category')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="plotly_white")
#fig.update_yaxes(title='')
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file8.html")
```




<iframe src="/img/FakeNewsDetector/file8.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




```python
temp=df.groupby('month').apply(lambda x:x['text'].count()).reset_index(name='Counts')
temp.style.clear()
cm = sns.light_palette("green", as_cmap=True)
temp.style.background_gradient(cmap=cm)

```




<style  type="text/css" >
#T_adae2822_5f76_11eb_a08c_0242ac1c0002row0_col0,#T_adae2822_5f76_11eb_a08c_0242ac1c0002row6_col1,#T_adae2822_5f76_11eb_a08c_0242ac1c0002row7_col1{
            background-color:  #ebf3eb;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row0_col1{
            background-color:  #d3e7d3;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row1_col0,#T_adae2822_5f76_11eb_a08c_0242ac1c0002row4_col1{
            background-color:  #d5e9d5;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row1_col1{
            background-color:  #e0eedf;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row2_col0{
            background-color:  #c0dec0;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row2_col1{
            background-color:  #bfdebf;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row3_col0{
            background-color:  #abd4ab;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row3_col1{
            background-color:  #d9ead9;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row4_col0{
            background-color:  #95c995;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row5_col0{
            background-color:  #80bf80;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row5_col1{
            background-color:  #e5f0e5;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row6_col0{
            background-color:  #6bb46b;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row7_col0{
            background-color:  #56aa56;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row8_col0{
            background-color:  #3f9f3f;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row8_col1{
            background-color:  #1d8e1d;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row9_col0{
            background-color:  #2a952a;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row9_col1{
            background-color:  #058205;
            color:  #f1f1f1;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row10_col0{
            background-color:  #158a15;
            color:  #000000;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row10_col1,#T_adae2822_5f76_11eb_a08c_0242ac1c0002row11_col0{
            background-color:  #008000;
            color:  #f1f1f1;
        }#T_adae2822_5f76_11eb_a08c_0242ac1c0002row11_col1{
            background-color:  #50a750;
            color:  #000000;
        }</style><table id="T_adae2822_5f76_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >month</th>        <th class="col_heading level0 col1" >Counts</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >1.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >3106</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >2.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >2957</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >3.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >3336</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >4.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >3034</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >5.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >3076</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >6.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >2896</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >7.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >2829</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >8.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >2829</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >9.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >5199</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >10.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >5476</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >11.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >5536</td>
            </tr>
            <tr>
                        <th id="T_adae2822_5f76_11eb_a08c_0242ac1c0002level0_row11" class="row_heading level0 row11" >11</th>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row11_col0" class="data row11 col0" >12.000000</td>
                        <td id="T_adae2822_5f76_11eb_a08c_0242ac1c0002row11_col1" class="data row11 col1" >4614</td>
            </tr>
    </tbody></table>




```python
temp=df.groupby('month').apply(lambda x:x['text'].count()).reset_index(name='Counts')

temp.style.background_gradient(cmap=cm)
#fig = px.scatter(temp, x="day", y="Counts",mode='lines+markers')
fig = go.Figure()
#fig.add_trace(go.bar(x=temp.day, y=temp.Counts ))
#fig = px.line(temp, x="day", y="Counts")
fig = px.bar(temp, x="month", y="Counts",color="Counts")
fig.update_layout(
    title=" Frequency of Words Used In News per Month of the Year",
    xaxis_title="Month",
    yaxis_title="Frequency",
    #legend_title="",
    font=dict(
        family="Courier New, monospace",
        size=18,
        color="white"
    )
)

fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="plotly_dark")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file9.html")
```

<iframe src="/img/FakeNewsDetector/file9.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




```python
temp=df.groupby('day').apply(lambda x:x['text'].count()).reset_index(name='Counts')

#fig = px.scatter(temp, x="day", y="Counts",mode='lines+markers')
fig = go.Figure()
fig.add_trace(go.Scatter(x=temp.day, y=temp.Counts,
                         marker=dict(
        color=np.random.randn(temp.shape[0]),
        colorscale='Viridis',
        line_width=1
    ),
                    mode='lines+markers'))
#fig = px.line(temp, x="day", y="Counts")

fig.update_layout(
    title=" Frequency of Words Used In News per Day of the Month",
    xaxis_title="Month",
    yaxis_title="Frequency",
    #legend_title="",
    font=dict(
        family="Courier New, monospace",
        size=18,
        color="RebeccaPurple"
    )
)

fig.update_xaxes(tickvals=temp.day,tickangle=45)
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout( template="seaborn")
#fig.update_xaxes(showticklabels=False)
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file10.html")
```


<iframe src="/img/FakeNewsDetector/file10.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>





#### Distribution of Token Lengths


```python
df["token_length"]  = df["text"].apply(lambda x : len(x))
df.head()
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
      <th>title</th>
      <th>text</th>
      <th>subject</th>
      <th>date</th>
      <th>label</th>
      <th>title_text</th>
      <th>year</th>
      <th>month</th>
      <th>day</th>
      <th>token_length</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>3056</th>
      <td>[chicago, cub, snub, trump, visit, white, hous...</td>
      <td>[unprecedented, clear, aimed, donald, trump, n...</td>
      <td>News</td>
      <td>2017-01-11</td>
      <td>Fake</td>
      <td>[unprecedented, clear, aimed, donald, trump, n...</td>
      <td>2017.0</td>
      <td>1.0</td>
      <td>11.0</td>
      <td>152</td>
    </tr>
    <tr>
      <th>21285</th>
      <td>[outrageous, example, radical, allowed, colleg...</td>
      <td>[war, expect, child, fight, war, leftist, acad...</td>
      <td>left-news</td>
      <td>2015-11-28</td>
      <td>Fake</td>
      <td>[war, expect, child, fight, war, leftist, acad...</td>
      <td>2015.0</td>
      <td>11.0</td>
      <td>28.0</td>
      <td>570</td>
    </tr>
    <tr>
      <th>11575</th>
      <td>[wow, barbara, bush, keynote, speaker, baby, k...</td>
      <td>[father, staunch, supporter, life, mother, voc...</td>
      <td>politicsNews</td>
      <td>2017-02-25</td>
      <td>Fake</td>
      <td>[father, staunch, supporter, life, mother, voc...</td>
      <td>2017.0</td>
      <td>2.0</td>
      <td>25.0</td>
      <td>149</td>
    </tr>
    <tr>
      <th>267</th>
      <td>[trump, puerto, rico, disgustingly, tell, puer...</td>
      <td>[thought, possibly, worse, donald, trump, lowe...</td>
      <td>News</td>
      <td>2017-10-03</td>
      <td>Fake</td>
      <td>[thought, possibly, worse, donald, trump, lowe...</td>
      <td>2017.0</td>
      <td>10.0</td>
      <td>3.0</td>
      <td>115</td>
    </tr>
    <tr>
      <th>18532</th>
      <td>[islamic, state, torch, oil, well, northern, i...</td>
      <td>[baghdad, reuters, islamic, state, militant, s...</td>
      <td>worldnews</td>
      <td>2017-10-02</td>
      <td>Real</td>
      <td>[baghdad, reuters, islamic, state, militant, s...</td>
      <td>2017.0</td>
      <td>10.0</td>
      <td>2.0</td>
      <td>120</td>
    </tr>
  </tbody>
</table>
</div>




```python
import plotly.figure_factory as ff
import numpy as np


# Group data together
hist_data = [df[df.label=="Fake"]["token_length"], df[df.label=="Real"]["token_length"]]

group_labels = ['Fake', 'Real']
colors = ['slategray', 'magenta']
                         
# Create distplot with custom bin_size
fig = ff.create_distplot(hist_data, group_labels, bin_size=.2,
                          curve_type='normal', # override default 'kde'
                         colors=colors)
#fig = ff.create_distplot(hist_data, group_labels, show_hist=False, colors=colors)
# Add title
#fig.update_layout(title_text='Distribution of Text Token Counts')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout(xaxis_range=[0,1500])
fig.update_layout( template="plotly")
fig.update_layout(
    autosize=False,
    width=1000,
    height=600,)
fig.update_layout(
    title=" Distribution of Text Token Counts",
    xaxis_title="Token Length",
    yaxis_title="Frequency")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file11.html")
```




<iframe src="/img/FakeNewsDetector/file11.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>





Most token lengths for the news items is between 0 to 500 words.


```python
from matplotlib import pyplot as plt
import seaborn as sns

from matplotlib import rcParams

# figure size in inches
#rcParams['figure.figsize'] = 11.7,8.27
#plt.figure(figsize=(12,10))
#multiple="stack",, kind="kde", fill=True
sns.set_theme();
sns.set(rc={'figure.figsize':(13,10)})
#fig, ax = plt.subplots()
#sns.set_size_inches(11.7, 8.27)
sns.displot(df, x="token_length",hue="label")
plt.xlim([0, 2500]);
plt.xlabel('Token Length');
plt.ylabel('Frequency');
plt.show()
```


    
![png](/img/FakeNewsDetector/output_61_0.png)
    









#### Visualizing Networks of Co-occurring Word
The  bigrams can be  visualized looking at  the top occurring bigrams as networks using the Python package NetworkX.


```python
import networkx as nx

# Create dictionary of bigrams and their counts
d = bigram_df.set_index('bigram').T.to_dict('records')

# Create network plot 
G = nx.Graph()

# Create connections between nodes
for k, v in d[0].items():
    G.add_edge(k[0], k[1], weight=(v * 5))


fig, ax = plt.subplots(figsize=(18, 10))

pos = nx.spring_layout(G, k=2)

# Plot networks
nx.draw_networkx(G, pos,
                 font_size=16,
                 width=3,
                 edge_color='grey',
                 node_color='green',
                 with_labels = False,
                 ax=ax)


# Create offset labels
for key, value in pos.items():
    x, y = value[0]+.135, value[1]+.045
    ax.text(x, y,
            s=key,
            bbox=dict(facecolor='yellow', alpha=0.25),
            horizontalalignment='center', fontsize=13)
    
plt.show()
```


    
![png](/img/FakeNewsDetector/output_63_0.png)
    


#### Sentiment Analysis with Vader
- For top 2000 highest frequency words in Fake/Real determine polarity of each with vader from Textblob package. The polarity  will then be used to classify news as either negative,positive or neutral. 


```python
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from nltk.sentiment.util import *
from textblob import TextBlob
from nltk import tokenize

#df.info()
df.drop_duplicates(subset = "text", keep = "first", inplace = True)


def get_polarity(text):
    return TextBlob(text).sentiment.polarity

df['Polarity'] = df['text'].progress_apply(get_polarity)
```


    HBox(children=(FloatProgress(value=0.0, max=38646.0), HTML(value='')))


    
    


```python
df['sentiment_vader']=''
df.loc[df.Polarity>0,'sentiment_vader']='POSITIVE'
df.loc[df.Polarity==0,'sentiment_vader']='NEUTRAL'
df.loc[df.Polarity<0,'sentiment_vader']='NEGATIVE'
#df.head()
```


```python
df["label"].replace({0:"Fake",  1:"Real"},inplace=True)
temp=df.groupby(['label','sentiment_vader']).apply(lambda x:x['sentiment_vader'].count()).reset_index(name='Counts')
temp.style.background_gradient(cmap='Greens')
```




<style  type="text/css" >
#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row0_col2{
            background-color:  #c8e9c1;
            color:  #000000;
        }#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row1_col2{
            background-color:  #f7fcf5;
            color:  #000000;
        }#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row2_col2{
            background-color:  #137d39;
            color:  #f1f1f1;
        }#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row3_col2{
            background-color:  #c0e6b9;
            color:  #000000;
        }#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row4_col2{
            background-color:  #f5fbf3;
            color:  #000000;
        }#T_6de1090a_5f79_11eb_a08c_0242ac1c0002row5_col2{
            background-color:  #00441b;
            color:  #f1f1f1;
        }</style><table id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >label</th>        <th class="col_heading level0 col1" >sentiment_vader</th>        <th class="col_heading level0 col2" >Counts</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >Fake</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >NEGATIVE</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row0_col2" class="data row0 col2" >4185</td>
            </tr>
            <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >Fake</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >NEUTRAL</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row1_col2" class="data row1 col2" >322</td>
            </tr>
            <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >Fake</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >POSITIVE</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row2_col2" class="data row2 col2" >12947</td>
            </tr>
            <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >Real</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >NEGATIVE</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row3_col2" class="data row3 col2" >4654</td>
            </tr>
            <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >Real</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >NEUTRAL</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row4_col2" class="data row4 col2" >551</td>
            </tr>
            <tr>
                        <th id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >Real</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >POSITIVE</td>
                        <td id="T_6de1090a_5f79_11eb_a08c_0242ac1c0002row5_col2" class="data row5 col2" >15987</td>
            </tr>
    </tbody></table>




```python
#temp=df.groupby(['label','sentiment_vader']).agg(['count']).reset_index()[['label','sentiment_vader','title']]
#temp.rename(columns={'title': 'Counts'}, inplace=True)
#temp
#
```


```python
fig = px.bar(temp, x="label", y="Counts", facet_col="sentiment_vader",
             color=["crimson","crimson","crimson","green","green","green"],text='Counts')
#Forcing an axis to be categorical
fig.update_xaxes(type='category')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout(showlegend=False)
fig.update_layout( template="plotly_white")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file12.html")
```


<iframe src="/img/FakeNewsDetector/file12.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>






```python
fig = px.bar(temp, x="label", y="Counts",color="sentiment_vader", barmode="group",text='Counts')
#Forcing an axis to be categorical
fig.update_xaxes(type='category')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout(title_text='Sentiment Distribution over Real and Fake News')
fig.update_traces(texttemplate='%{text:.2s}', textposition='outside')
fig.update_layout(barmode='group', xaxis_tickangle=0)
fig.update_layout(barmode='group', xaxis={'categoryorder':'category ascending'})
fig.update_layout(
    legend=dict(
        x=1,
        y=1,
        traceorder="reversed",
        #title_font_family="Times New Roman",
        font=dict(
            family="Courier",
            size=12,
            color="black"
        ),
        bgcolor="LightSteelBlue",
        bordercolor="Black",
        borderwidth=2
    )
)

fig.update_layout( template="simple_white")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file13.html")
```



<iframe src="/img/FakeNewsDetector/file13.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>



#### Has the News Grown More Negative Between 2015 to 2018?

Yes. The proportion of negative sentiments in the news has increased  between 2015 to 2017.



```python
df.head()
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
      <th>title</th>
      <th>text</th>
      <th>subject</th>
      <th>date</th>
      <th>label</th>
      <th>Polarity</th>
      <th>sentiment_vader</th>
      <th>year</th>
      <th>month</th>
      <th>day</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>As U.S. budget fight looms, Republicans flip t...</td>
      <td>WASHINGTON (Reuters) - The head of a conservat...</td>
      <td>politicsNews</td>
      <td>2017-12-31</td>
      <td>Real</td>
      <td>0.037083</td>
      <td>POSITIVE</td>
      <td>2017.0</td>
      <td>12.0</td>
      <td>31.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>U.S. military to accept transgender recruits o...</td>
      <td>WASHINGTON (Reuters) - Transgender people will...</td>
      <td>politicsNews</td>
      <td>2017-12-29</td>
      <td>Real</td>
      <td>0.055880</td>
      <td>POSITIVE</td>
      <td>2017.0</td>
      <td>12.0</td>
      <td>29.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Senior U.S. Republican senator: 'Let Mr. Muell...</td>
      <td>WASHINGTON (Reuters) - The special counsel inv...</td>
      <td>politicsNews</td>
      <td>2017-12-31</td>
      <td>Real</td>
      <td>0.115930</td>
      <td>POSITIVE</td>
      <td>2017.0</td>
      <td>12.0</td>
      <td>31.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>FBI Russia probe helped by Australian diplomat...</td>
      <td>WASHINGTON (Reuters) - Trump campaign adviser ...</td>
      <td>politicsNews</td>
      <td>2017-12-30</td>
      <td>Real</td>
      <td>0.035968</td>
      <td>POSITIVE</td>
      <td>2017.0</td>
      <td>12.0</td>
      <td>30.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Trump wants Postal Service to charge 'much mor...</td>
      <td>SEATTLE/WASHINGTON (Reuters) - President Donal...</td>
      <td>politicsNews</td>
      <td>2017-12-29</td>
      <td>Real</td>
      <td>0.030093</td>
      <td>POSITIVE</td>
      <td>2017.0</td>
      <td>12.0</td>
      <td>29.0</td>
    </tr>
  </tbody>
</table>
</div>




```python

df["date"] = pd.to_datetime(df["date"], errors='coerce')

df['year'] = df['date'].dt.year
df['month'] = df['date'].dt.month
df['day'] = df['date'].dt.day
df['year'] = df['year'].fillna(0)
df['year'] = df['year'].astype(int)
temp=df.groupby(['year','sentiment_vader']).agg({'title':'count'}).query('year>0')
temp = temp.groupby(level=0).apply(lambda x:1 * x / float(x.sum())).reset_index()
temp.rename(columns={'title': 'Ratio'}, inplace=True)
temp.style.background_gradient(cmap='Blues')
```




<style  type="text/css" >
#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row0_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row1_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row2_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row4_col2,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row7_col2{
            background-color:  #f7fbff;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row0_col2{
            background-color:  #b5d4e9;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row1_col2{
            background-color:  #f5fafe;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row2_col2{
            background-color:  #084488;
            color:  #f1f1f1;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row3_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row4_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row5_col0{
            background-color:  #abd0e6;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row3_col2{
            background-color:  #c9ddf0;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row5_col2,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row9_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row10_col0{
            background-color:  #08306b;
            color:  #f1f1f1;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row6_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row7_col0,#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row8_col0{
            background-color:  #3787c0;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row6_col2{
            background-color:  #b8d5ea;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row8_col2{
            background-color:  #084082;
            color:  #f1f1f1;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row9_col2{
            background-color:  #99c7e0;
            color:  #000000;
        }#T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row10_col2{
            background-color:  #08509b;
            color:  #f1f1f1;
        }</style><table id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002" ><thead>    <tr>        <th class="blank level0" ></th>        <th class="col_heading level0 col0" >year</th>        <th class="col_heading level0 col1" >sentiment_vader</th>        <th class="col_heading level0 col2" >Ratio</th>    </tr></thead><tbody>
                <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row0" class="row_heading level0 row0" >0</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row0_col0" class="data row0 col0" >2015</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row0_col1" class="data row0 col1" >NEGATIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row0_col2" class="data row0 col2" >0.250470</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row1" class="row_heading level0 row1" >1</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row1_col0" class="data row1 col0" >2015</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row1_col1" class="data row1 col1" >NEUTRAL</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row1_col2" class="data row1 col2" >0.028804</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row2" class="row_heading level0 row2" >2</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row2_col0" class="data row2 col0" >2015</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row2_col1" class="data row2 col1" >POSITIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row2_col2" class="data row2 col2" >0.720726</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row3" class="row_heading level0 row3" >3</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row3_col0" class="data row3 col0" >2016</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row3_col1" class="data row3 col1" >NEGATIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row3_col2" class="data row3 col2" >0.199669</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row4" class="row_heading level0 row4" >4</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row4_col0" class="data row4 col0" >2016</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row4_col1" class="data row4 col1" >NEUTRAL</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row4_col2" class="data row4 col2" >0.021059</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row5" class="row_heading level0 row5" >5</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row5_col0" class="data row5 col0" >2016</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row5_col1" class="data row5 col1" >POSITIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row5_col2" class="data row5 col2" >0.779271</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row6" class="row_heading level0 row6" >6</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row6_col0" class="data row6 col0" >2017</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row6_col1" class="data row6 col1" >NEGATIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row6_col2" class="data row6 col2" >0.244642</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row7" class="row_heading level0 row7" >7</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row7_col0" class="data row7 col0" >2017</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row7_col1" class="data row7 col1" >NEUTRAL</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row7_col2" class="data row7 col2" >0.022905</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row8" class="row_heading level0 row8" >8</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row8_col0" class="data row8 col0" >2017</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row8_col1" class="data row8 col1" >POSITIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row8_col2" class="data row8 col2" >0.732453</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row9" class="row_heading level0 row9" >9</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row9_col0" class="data row9 col0" >2018</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row9_col1" class="data row9 col1" >NEGATIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row9_col2" class="data row9 col2" >0.314286</td>
            </tr>
            <tr>
                        <th id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002level0_row10" class="row_heading level0 row10" >10</th>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row10_col0" class="data row10 col0" >2018</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row10_col1" class="data row10 col1" >POSITIVE</td>
                        <td id="T_4688ee5c_5f7b_11eb_a08c_0242ac1c0002row10_col2" class="data row10 col2" >0.685714</td>
            </tr>
    </tbody></table>




```python
fig = px.bar(temp, x="year", y="Ratio",color="sentiment_vader", barmode="group")
#Forcing an axis to be categorical
fig.update_xaxes(type='category')
#fig.update_traces(texttemplate='%{text:.2s}', textposition='outside')
fig.update_xaxes(type='category')
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout(title_text='Sentiment Distribution over Real and Fake News')
#fig.update_traces( texttemplate='{}',textposition='outside')
fig.update_layout(barmode='group', xaxis_tickangle=-45)
fig.update_layout(barmode='group', xaxis={'categoryorder':'category ascending'})
fig.update_layout(yaxis=dict(tickformat=".0%"))
fig.update_yaxes(title="Percent",title_font_family="Arial")
fig.update_layout( template="ggplot2")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file14.html")
```


<iframe src="/img/FakeNewsDetector/file14.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>



```python
temp=df.groupby(['day','sentiment_vader']).agg({'title':'count'})
temp = temp.groupby(level=0).apply(lambda x:1 * x / float(x.sum())).reset_index()
temp.rename(columns={'title': 'Ratio'}, inplace=True)
#fig = px.line(temp, x="day", y="Ratio",color="sentiment_vader",line_group="sentiment_vader")
fig = go.Figure()
fig.add_trace(go.Scatter(x=temp[temp.sentiment_vader=="POSITIVE"]["day"], 
                         y=temp[temp.sentiment_vader=="POSITIVE"]["Ratio"],
                    mode='lines+markers',
                    name='POSITIVE'))
fig.add_trace(go.Scatter(x=temp[temp.sentiment_vader=="NEGATIVE"]["day"], 
                         y=temp[temp.sentiment_vader=="NEGATIVE"]["Ratio"],
                    mode='lines+markers',
                    name='NEGATIVE'))
fig.add_trace(go.Scatter(x=temp[temp.sentiment_vader=="NEUTRAL"]["day"], 
                         y=temp[temp.sentiment_vader=="NEUTRAL"]["Ratio"],
                    mode='lines+markers', name='NEUTRAL'))
fig.update_xaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_yaxes(showline=True, linewidth=2, linecolor='black', mirror=True)
fig.update_layout(title_text='Sentiment Distribution over Real and Fake News Every Day of The Month')
fig.update_layout( template="plotly_dark")
fig.update_layout(xaxis_tickangle=-45)
#["plotly", "plotly_white", "plotly_dark", "ggplot2", "seaborn", "simple_white", "none"]
fig.update_layout(yaxis=dict(tickformat=".0%"))
fig.update_yaxes(title="Percent",title_font_family="Arial")
fig.show()
fig.write_html("/content/drive/MyDrive/Colab Notebooks/NLP/htmlfies/file15.html")
```





<iframe src="/img/FakeNewsDetector/file15.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>



#### Classification of News as Real or Fake using Titles as Features


```python
%%time
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn import preprocessing
le = preprocessing.LabelEncoder()

y=  le.fit_transform(df.label)

X_train, X_test, y_train, y_test = train_test_split(df.title, y, test_size = 0.2,random_state=2)

#vectorizer = CountVectorizer().fit(X_train)
vectorizer = TfidfVectorizer(use_idf=True).fit(X_train)
train_x = vectorizer.transform(X_train)
test_x = vectorizer.transform(X_test)


model = LogisticRegression(C=2.5)
model.fit(train_x, y_train)
y_pred = model.predict(test_x)
accuracy_value = roc_auc_score(y_test, y_pred)
print("accuracy score {}".format(accuracy_value))
```

    accuracy score 0.9568209165268219
    CPU times: user 1.77 s, sys: 1.14 s, total: 2.91 s
    Wall time: 2.31 s
    

The title alone can predict fake or reals by nearly 96% accuracy.

#### Classification of News as Real or Fake with Text as Features


```python
%%time

X_train, X_test, y_train, y_test = train_test_split(df.text, y, test_size = 0.2,random_state=2)

vectorizer = CountVectorizer().fit(X_train)
#vectorizer = TfidfVectorizer(use_idf=True).fit(X_train)
train_x = vectorizer.transform(X_train)
test_x = vectorizer.transform(X_test)
model = xgb.XGBClassifier(
              n_jobs = -1,
              max_depth = 6,
              #learning_rate=  0.1,
              min_child_weight= 2, 
              #min_samples_split= 0.9,
              n_estimators= 100,
              eta = 0.1, 
              verbose = 1, 
              gamma=0.05,
              #nrounds = 100
              objective = "binary:logistic", 
              eval_metric = "auc",       #"aucpr",    # "aucpr",  #aucpr, auc
              subsample = 0.7,
              colsample_bytree =0.8,
              max_delta_step=1,
              verbosity=1,
              tree_method='approx')

model.fit(train_x, y_train)
y_pred = model.predict(test_x)
accuracy_value = roc_auc_score(y_test, y_pred)
print("accuracy score {}".format(accuracy_value))
```

    accuracy score 0.9970340274765952
    CPU times: user 3min 45s, sys: 359 ms, total: 3min 45s
    Wall time: 2min 8s
    

#### Classification of News as Real or Fake with Title and Text Combined as Features


```python
%%time
X_train, X_test, y_train, y_test = train_test_split(df.title_text, y, test_size = 0.2,random_state=2)

vectorizer = CountVectorizer().fit(X_train)
#vectorizer = TfidfVectorizer(use_idf=True).fit(X_train)
train_x = vectorizer.transform(X_train)
test_x = vectorizer.transform(X_test)

model = xgb.XGBClassifier(
              n_jobs = -1,
              max_depth = 6,
              #learning_rate=  0.1,
              min_child_weight= 2, 
              #min_samples_split= 0.9,
              n_estimators= 100,
              eta = 0.1, 
              verbose = 1, 
              gamma=0.05,
              #nrounds = 100
              objective = "binary:logistic", 
              eval_metric = "auc",       #"aucpr",    # "aucpr",  #aucpr, auc
              subsample = 0.7,
              colsample_bytree =0.8,
              max_delta_step=1,
              verbosity=1,

              tree_method='approx')
#model = LogisticRegression(C=2.5)
model.fit(train_x, y_train)
y_pred = model.predict(test_x)
accuracy_value = roc_auc_score(y_test, y_pred)
print("accuracy score {}".format(accuracy_value))
```

    accuracy score 0.9975657161197259
    CPU times: user 3min 51s, sys: 693 ms, total: 3min 52s
    Wall time: 2min 12s
    


```python
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
import seaborn as sns
p=0.5

def PlotConfusionMatrix(y_test,pred,y_test_normal,y_test_pneumonia,label):

    cfn_matrix = confusion_matrix(y_test,pred)
    cfn_norm_matrix = np.array([[1.0 / y_test_normal,1.0/y_test_normal],[1.0/y_test_pneumonia,1.0/y_test_pneumonia]])
    norm_cfn_matrix = cfn_matrix * cfn_norm_matrix

    #colsum=cfn_matrix.sum(axis=0)
    #norm_cfn_matrix = cfn_matrix / np.vstack((colsum, colsum)).T

    fig = plt.figure(figsize=(15,5))
    ax = fig.add_subplot(1,2,1)
    #sns.heatmap(cfn_matrix,cmap='magma',linewidths=0.5,annot=True,ax=ax,annot=True)
    sns.heatmap(cfn_matrix, annot = True,fmt='g',cmap='rocket')
    #tick_marks = np.arange(len(y_test))
    #plt.xticks(tick_marks, np.unique(y_test), rotation=45)
    plt.title('Confusion Matrix',color='b')
    plt.ylabel('Real Classes')
    plt.xlabel('Predicted Classes')
    plt.savefig('/content/drive/My Drive/Colab Notebooks/NLP/cm_' +label +  '.png')
        
    ax = fig.add_subplot(1,2,2)
    sns.heatmap(norm_cfn_matrix,cmap=plt.cm.Blues,linewidths=0.5,ax=ax,annot=True)

    plt.title('Normalized Confusion Matrix',color='b')
    plt.ylabel('Real Classes')
    plt.xlabel('Predicted Classes')
    plt.savefig('/content/drive/My Drive/Colab Notebooks/NLP/cm_norm' +label +  '.png')
    plt.show()
    
    print('---Classification Report---')
    print(classification_report(y_test,pred))
    

y_test_real,y_test_fake = np.bincount(y_test)
y_pred= np.where(y_pred<p,0,1 )


PlotConfusionMatrix(y_test,y_pred,y_test_real,y_test_fake,label= 'classification Report')
```


    
![png](/img/FakeNewsDetector/output_83_0.png)
    



    ---Classification Report---
                  precision    recall  f1-score   support
    
               0       1.00      1.00      1.00      4702
               1       1.00      1.00      1.00      4278
    
        accuracy                           1.00      8980
       macro avg       1.00      1.00      1.00      8980
    weighted avg       1.00      1.00      1.00      8980
    
    



