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
    
    



