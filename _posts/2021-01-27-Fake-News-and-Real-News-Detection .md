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
    
    



