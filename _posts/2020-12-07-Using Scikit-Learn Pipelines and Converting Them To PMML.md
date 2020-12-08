---
layout: post
title: Using Scikit-Learn Pipelines and Converting Them To PMML
subtitle:  
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [pipelines, PMML, Automation,xgboost]
---


### Using Scikit-Learn Pipelines and Converting Them To PMML


#### Introduction


Pipelining in machine learning involves chaining all the steps involved in training a model together. The pipeline allows to assemble several steps that can be cross-validated together while setting different parameter values. It is a step closer to automating the all the steps such as preprocessing, missing value imputation etc together. The pipeline steps used in getting the model ready for the training can also be applied to test data in a single step to make it ready for prediction. A Pipeline Sequentially applies  a list of transforms and a final estimator to a dataset. The  Intermediate steps of the  implement fit and transform methods whiles the final estimator implements a  fit. The transformers in the pipeline can be cached using memory argument.




```python

#!pip install category-encoders
#!pip install scipy
#!pip install --upgrade pip --user
#!pip install scipy==1.2 --upgrade --user
#!pip install sklearn2pmml
#!pip install numpy
#!pip install sklearn
#!pip install pandas
```


```bash
%%bash

pip install sklearn2pmml
pip install -q git+https://github.com/gmihaila/ml_things.git
!pip install --upgrade scikit-learn
```

    Requirement already satisfied: sklearn2pmml in /usr/local/lib/python3.6/dist-packages (0.61.0)
    Requirement already satisfied: sklearn-pandas>=0.0.10 in /usr/local/lib/python3.6/dist-packages (from sklearn2pmml) (1.8.0)
    Requirement already satisfied: scikit-learn>=0.18.0 in /usr/local/lib/python3.6/dist-packages (from sklearn2pmml) (0.23.2)
    Requirement already satisfied: joblib>=0.13.0 in /usr/local/lib/python3.6/dist-packages (from sklearn2pmml) (0.16.0)
    Requirement already satisfied: pandas>=0.11.0 in /usr/local/lib/python3.6/dist-packages (from sklearn-pandas>=0.0.10->sklearn2pmml) (1.1.2)
    Requirement already satisfied: numpy>=1.6.1 in /usr/local/lib/python3.6/dist-packages (from sklearn-pandas>=0.0.10->sklearn2pmml) (1.18.5)
    Requirement already satisfied: scipy>=0.14 in /usr/local/lib/python3.6/dist-packages (from sklearn-pandas>=0.0.10->sklearn2pmml) (1.4.1)
    Requirement already satisfied: threadpoolctl>=2.0.0 in /usr/local/lib/python3.6/dist-packages (from scikit-learn>=0.18.0->sklearn2pmml) (2.1.0)
    Requirement already satisfied: pytz>=2017.2 in /usr/local/lib/python3.6/dist-packages (from pandas>=0.11.0->sklearn-pandas>=0.0.10->sklearn2pmml) (2018.9)
    Requirement already satisfied: python-dateutil>=2.7.3 in /usr/local/lib/python3.6/dist-packages (from pandas>=0.11.0->sklearn-pandas>=0.0.10->sklearn2pmml) (2.8.1)
    Requirement already satisfied: six>=1.5 in /usr/local/lib/python3.6/dist-packages (from python-dateutil>=2.7.3->pandas>=0.11.0->sklearn-pandas>=0.0.10->sklearn2pmml) (1.15.0)
    

    bash: line 4: !pip: command not found
    


```python
from pandas_profiling import ProfileReport
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.model_selection import GridSearchCV, RandomizedSearchCV
from sklearn.model_selection import StratifiedKFold
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.compose import ColumnTransformer
from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, precision_score, classification_report, recall_score
import pandas_profiling
from sklearn.impute import SimpleImputer
Imputer = SimpleImputer(fill_value=-9999999, strategy='constant')
```


```python
import pandas as pd
from sklearn2pmml.decoration import ContinuousDomain
from sklearn2pmml.pipeline import PMMLPipeline
from sklearn2pmml import make_pmml_pipeline, sklearn2pmml
import xgboost as xgb
from joblib import dump, load
from sklearn.metrics import classification_report, f1_score, accuracy_score, precision_score, confusion_matrix
from sklearn.metrics import roc_auc_score
from sklearn.metrics import auc
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import plot_confusion_matrix
import numpy as np
from sklearn.metrics import classification_report, accuracy_score
from ml_things import plot_dict, plot_confusion_matrix, fix_text
import seaborn as sns; sns.set()
import matplotlib.pyplot as plt
%matplotlib inline
pd.set_option('display.max_columns', None)  # or 1000
pd.set_option('display.max_rows', None)  # or 1000
pd.set_option('display.max_colwidth', None)  # or 19

% %autosave 5
```



    Autosaving every 5 seconds
    


```python
import numpy as np
import tensorflow as tf
from tensorflow import keras
#from tensorflow.keras.preprocessing.image import image_dataset_from_directory
from keras import  layers
import matplotlib.pyplot as plt
import matplotlib as mpl
import os
mpl.rcParams['figure.figsize'] = (12, 10)
colors = plt.rcParams['axes.prop_cycle'].by_key()['color']
%autosave 5
print(tf.__version__)
```



    Autosaving every 5 seconds
    2.3.0
    


```python
from google.colab import drive
import glob
drive.mount('/content/drive', force_remount=True)
```

    Mounted at /content/drive
    

The dataset is hosted on UCI machine learning dataset repository and can be downloaded from this link [data](https://archive.ics.uci.edu/ml/datasets/Adult). The task is to Predict whether income exceeds $50K/yr based on census data. Decription of the dataset is below. It consist of 14 features both numeric and categorical variables.

- Income : >50K, <=50K. Target variable for income below or equal to $50000 and above $50000. 

- age: continuous.
- workclass: Private, Self-emp-not-inc, Self-emp-inc, Federal-gov, Local-gov, State-gov, Without-pay, Never-worked.
- fnlwgt: continuous.
- education: Bachelors, Some-college, 11th, HS-grad, Prof-school, Assoc-acdm, Assoc-voc, 9th, 7th-8th, 12th, Masters, 1st-4th, 10th, Doctorate, 5th-6th, Preschool.
- education-num: continuous.
- marital-status: Married-civ-spouse, Divorced, Never-married, Separated, Widowed, Married-spouse-absent, Married-AF-spouse.
-- occupation: Tech-support, Craft-repair, Other-service, Sales, Exec-managerial, Prof-specialty, Handlers-cleaners, Machine-op-inspct, Adm-clerical, Farming-fishing, Transport-moving, Priv-house-serv, Protective-serv, Armed-Forces.
- relationship: Wife, Own-child, Husband, Not-in-family, Other-relative, Unmarried.
- race: White, Asian-Pac-Islander, Amer-Indian-Eskimo, Other, Black.
- sex: Female, Male.
- capital-gain: continuous.
- capital-loss: continuous.
- hours-per-week: continuous.
- native-country: United-States, Cambodia, England, Puerto-Rico, Canada, Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China, Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico, Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti, Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia, El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands.






```python
header=['age',
        'workclas',
        'fnlwgt',
        'education',
        'education-num',
        'marital-status',
        'occupation',
        'relationship',
        'race',
        'sex',
        'capital-gain',
        'capital-loss',
        'hours-per-week',
        'native-country',
        'Income']
```


```python
len(header)
```




    15




```python
data= pd.read_csv('/content/drive/My Drive/Data/adult.data',header=0,names=header)

```


```python
data.shape
```




    (32560, 15)




```python
data.head()
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
      <th>age</th>
      <th>workclas</th>
      <th>fnlwgt</th>
      <th>education</th>
      <th>education-num</th>
      <th>marital-status</th>
      <th>occupation</th>
      <th>relationship</th>
      <th>race</th>
      <th>sex</th>
      <th>capital-gain</th>
      <th>capital-loss</th>
      <th>hours-per-week</th>
      <th>native-country</th>
      <th>Income</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>50</td>
      <td>Self-emp-not-inc</td>
      <td>83311</td>
      <td>Bachelors</td>
      <td>13</td>
      <td>Married-civ-spouse</td>
      <td>Exec-managerial</td>
      <td>Husband</td>
      <td>White</td>
      <td>Male</td>
      <td>0</td>
      <td>0</td>
      <td>13</td>
      <td>United-States</td>
      <td>&lt;=50K</td>
    </tr>
    <tr>
      <th>1</th>
      <td>38</td>
      <td>Private</td>
      <td>215646</td>
      <td>HS-grad</td>
      <td>9</td>
      <td>Divorced</td>
      <td>Handlers-cleaners</td>
      <td>Not-in-family</td>
      <td>White</td>
      <td>Male</td>
      <td>0</td>
      <td>0</td>
      <td>40</td>
      <td>United-States</td>
      <td>&lt;=50K</td>
    </tr>
    <tr>
      <th>2</th>
      <td>53</td>
      <td>Private</td>
      <td>234721</td>
      <td>11th</td>
      <td>7</td>
      <td>Married-civ-spouse</td>
      <td>Handlers-cleaners</td>
      <td>Husband</td>
      <td>Black</td>
      <td>Male</td>
      <td>0</td>
      <td>0</td>
      <td>40</td>
      <td>United-States</td>
      <td>&lt;=50K</td>
    </tr>
    <tr>
      <th>3</th>
      <td>28</td>
      <td>Private</td>
      <td>338409</td>
      <td>Bachelors</td>
      <td>13</td>
      <td>Married-civ-spouse</td>
      <td>Prof-specialty</td>
      <td>Wife</td>
      <td>Black</td>
      <td>Female</td>
      <td>0</td>
      <td>0</td>
      <td>40</td>
      <td>Cuba</td>
      <td>&lt;=50K</td>
    </tr>
    <tr>
      <th>4</th>
      <td>37</td>
      <td>Private</td>
      <td>284582</td>
      <td>Masters</td>
      <td>14</td>
      <td>Married-civ-spouse</td>
      <td>Exec-managerial</td>
      <td>Wife</td>
      <td>White</td>
      <td>Female</td>
      <td>0</td>
      <td>0</td>
      <td>40</td>
      <td>United-States</td>
      <td>&lt;=50K</td>
    </tr>
  </tbody>
</table>
</div>




```python
#data['income']  = [1 if  i ==' >50K' else 0  for i in data.Income]

#from sklearn.preprocessing import LabelEncoder 
#labelencoder= LabelEncoder() #initializing an object of class LabelEncoder
#data['Income'] = labelencoder.fit_transform(data['Income']) #fitting and transforming the desired categorical column.
```


```python
print(data.Income.value_counts())
print(data.Income.value_counts(normalize=True)
)
```

     <=50K    24719
     >50K      7841
    Name: Income, dtype: int64
     <=50K    0.759183
     >50K     0.240817
    Name: Income, dtype: float64
    


```python
#def do_the_job(x):
#    ref=[]
#    if (x ==' <=50K'):
#       ret = 0
#    elif (x == ' >50K'):
#       ret =1

#    return ret

#data['income'] = data['Income'].apply(do_the_job)
#data['native-country'].value_counts()
#data[data[data['native-country']==' Holand-Netherlands']['native-country']=='Germany']
#data[data['native-country']==' Holand-Netherlands']['native-country']
#data[data['native-country']==' Germany']['native-country'].tolist()
#data['native-country'] = data['native-country'].str.replace(' Holand-Netherlands' ,' Germany')
```


```python
data.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 32560 entries, 0 to 32559
    Data columns (total 15 columns):
     #   Column          Non-Null Count  Dtype 
    ---  ------          --------------  ----- 
     0   age             32560 non-null  int64 
     1   workclas        32560 non-null  object
     2   fnlwgt          32560 non-null  int64 
     3   education       32560 non-null  object
     4   education-num   32560 non-null  int64 
     5   marital-status  32560 non-null  object
     6   occupation      32560 non-null  object
     7   relationship    32560 non-null  object
     8   race            32560 non-null  object
     9   sex             32560 non-null  object
     10  capital-gain    32560 non-null  int64 
     11  capital-loss    32560 non-null  int64 
     12  hours-per-week  32560 non-null  int64 
     13  native-country  32560 non-null  object
     14  Income          32560 non-null  object
    dtypes: int64(6), object(9)
    memory usage: 3.7+ MB
    


```python
data.describe()
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
      <th>age</th>
      <th>fnlwgt</th>
      <th>education-num</th>
      <th>capital-gain</th>
      <th>capital-loss</th>
      <th>hours-per-week</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>32560.000000</td>
      <td>3.256000e+04</td>
      <td>32560.000000</td>
      <td>32560.000000</td>
      <td>32560.000000</td>
      <td>32560.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>38.581634</td>
      <td>1.897818e+05</td>
      <td>10.080590</td>
      <td>1077.615172</td>
      <td>87.306511</td>
      <td>40.437469</td>
    </tr>
    <tr>
      <th>std</th>
      <td>13.640642</td>
      <td>1.055498e+05</td>
      <td>2.572709</td>
      <td>7385.402999</td>
      <td>402.966116</td>
      <td>12.347618</td>
    </tr>
    <tr>
      <th>min</th>
      <td>17.000000</td>
      <td>1.228500e+04</td>
      <td>1.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>28.000000</td>
      <td>1.178315e+05</td>
      <td>9.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>40.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>37.000000</td>
      <td>1.783630e+05</td>
      <td>10.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>40.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>48.000000</td>
      <td>2.370545e+05</td>
      <td>12.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>45.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>90.000000</td>
      <td>1.484705e+06</td>
      <td>16.000000</td>
      <td>99999.000000</td>
      <td>4356.000000</td>
      <td>99.000000</td>
    </tr>
  </tbody>
</table>
</div>




```python
neg, pos = data.Income.value_counts()
total = neg + pos
print('Examples:\n    Total: {}\n    >50K: {} ({:.2f}% of total)\n  '.format(
    total, pos, 100 * pos / total,100 * neg / total))

print('Total: {}\n    <=50K: {} ({:.2f}% of total)\n  '.format(
    total, neg, 100 * neg / total))
```

    Examples:
        Total: 32560
        >50K: 7841 (24.08% of total)
      
    Total: 32560
        <=50K: 24719 (75.92% of total)
      
    

Check for missing values in the dataframe.


```python
data.isnull().sum(axis=0)
# let df be your dataframe and x be the value you want to fill it with
#heartdata.fillna(-9999.01)
```




    age               0
    workclas          0
    fnlwgt            0
    education         0
    education-num     0
    marital-status    0
    occupation        0
    relationship      0
    race              0
    sex               0
    capital-gain      0
    capital-loss      0
    hours-per-week    0
    native-country    0
    Income            0
    dtype: int64



Remove duplicated columns  if any.


```python
data = data.loc[:,~data.columns.duplicated()]
```

drop all duplicate rows if any


```python
data.drop_duplicates(keep=False, inplace=True)
```

Remove Correlated Features


```python
from tqdm import tqdm
from scipy import stats
from scipy.stats import chi2_contingency
import sys #threshold=0.95
#threshold=0.95



def Remove_correlation(data, threshold):
    ''' 
    Find correlation among columns of a dataframe
    return names of columns removed  
    return  reduced dataframe with correlated columns removed
    '''
# Create correlation matrix
    corr_matrix = data.corr().abs()

# Select upper triangle of correlation matrix
    upper = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(np.bool))

# Find features with correlation greater than 0.95
    drop_columns = [column for column in upper.columns if any(upper[column] > threshold)]

# Drop features 
    red_data=data.drop(drop_columns, axis=1)
    return  drop_columns, red_data
```


```python
print('Features Removed : {}'.format(Remove_correlation(data, threshold=0.95)[0]))
data = Remove_correlation(data, threshold=0.95)[1]
print('shape of dataframe {}'.format(data.shape))
```

    Features Removed : []
    shape of dataframe (32560, 15)
    

No correlated features exist in the dataset.

check the distribution of the target variable.


```python
import seaborn as sns
sns.set_theme(style="darkgrid")
#titanic = sns.load_dataset("titanic")
ax = sns.countplot(x="Income", data=data,palette="Set3")
plt.xlabel('Income')
plt.ylabel('Frequency')
plt.title('frequency of Income  ')
plt.show()
```


    

![png](/img/pipelines/output_30_0.png)    



```python
# get the target, separate target and time from predictors
y = data.Income             
X= data.drop(['Income'], axis=1, inplace=False)
#X= heartdata.drop(['DEATH_EVENT', 'time'], axis=1, inplace=True)
X.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 32560 entries, 0 to 32559
    Data columns (total 14 columns):
     #   Column          Non-Null Count  Dtype 
    ---  ------          --------------  ----- 
     0   age             32560 non-null  int64 
     1   workclas        32560 non-null  object
     2   fnlwgt          32560 non-null  int64 
     3   education       32560 non-null  object
     4   education-num   32560 non-null  int64 
     5   marital-status  32560 non-null  object
     6   occupation      32560 non-null  object
     7   relationship    32560 non-null  object
     8   race            32560 non-null  object
     9   sex             32560 non-null  object
     10  capital-gain    32560 non-null  int64 
     11  capital-loss    32560 non-null  int64 
     12  hours-per-week  32560 non-null  int64 
     13  native-country  32560 non-null  object
    dtypes: int64(6), object(8)
    memory usage: 3.5+ MB
    


```python

# Break off validation set from training data
X_train, X_valid, y_train, y_valid = train_test_split(X, y, train_size=0.75, test_size=0.25,random_state=0)
# Display results
print ("Shapes:")
print ("X: {}".format(X.shape))
print ("y: {}".format(y.shape))
print()
print ("X_train: {}".format(X_train.shape))
print ("X_valid: {}".format(X_valid.shape))
print ("y_train: {}".format(y_train.shape))
print ("y_valid: {}\n".format(y_valid.shape))
```

    Shapes:
    X: (32560, 14)
    y: (32560,)
    
    X_train: (24420, 14)
    X_valid: (8140, 14)
    y_train: (24420,)
    y_valid: (8140,)
    
    

Select the numeric and categorical features. The categorical feature processing would include one-hot encoding


```python
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer, make_column_transformer

##
#numerical_features=heartdata.select_dtypes(exclude=['object','category']).drop('DEATH_EVENT',axis=1).columns.tolist()
# Select numeric columns
numeric_features = [col for col in X_train.columns if X_train[col].dtype in ['int64', 'float64']]
numeric_features
```




    ['age',
     'fnlwgt',
     'education-num',
     'capital-gain',
     'capital-loss',
     'hours-per-week']




```python
categorical_features=X.select_dtypes(include=['object','category']).columns.tolist()
categorical_features
```




    ['workclas',
     'education',
     'marital-status',
     'occupation',
     'relationship',
     'race',
     'sex',
     'native-country']




```python
#R_test = pd.read_csv('C:\\Users\\admin1\\Desktop\\WORK\\R_test_M_LIN.csv',delimiter="\t")
#R_train = pd.read_csv('C:\\Users\\admin1\\Desktop\\WORK\\R_train_M_LIN.csv',delimiter="\t")        
```

impute categorical features by filing with a constant


```python
categorical_transformer = Pipeline(steps=[
    #('encoding',LabelEncoder()),
    ('onehot', OneHotEncoder(handle_unknown='ignore')),
    #('encoding',MyLabelEncoder()),
    #('encoding',MultiColumnLabelEncoder())
    ('imputer', SimpleImputer(fill_value= -9999.01, strategy='constant'))
    #('encoding',OrdinalEncoder(categories='auto')),
   # 
])
```

missing value imputation by flling with a number


```python

numeric_transformer = Pipeline(steps=[
    ('imputer', SimpleImputer(fill_value=-9999999, strategy='constant')),
    ('scaler', StandardScaler()) 
    ])
```


```python
xgb_classifier = xgb.XGBClassifier(
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
```


```python

preprocessor = ColumnTransformer(
    transformers=[
        ('num', numeric_transformer, numeric_features),
        ('cat', categorical_transformer, categorical_features)])

# Append classifier to preprocessing pipeline.

pipeline_f = Pipeline(steps=[('preprocessor', preprocessor),
                      #('dropfeature',UniqueDropper()),
                      #('anova', SelectPercentile(chi2)),
                      # ('feature_selection', SelectFromModel(LinearSVC(penalty="l1"))),
                      ('classifier', xgb_classifier)])


xgb_model = pipeline_f.fit(X_train,  y_train)

print("model score: %.3f" % pipeline_f.score(X_valid, y_valid))

```

    model score: 0.868
    


```python
# Get predictions
preds = pipeline_f.predict(X_valid)

# Evaluate the model
score = accuracy_score(y_valid,preds)

# Display the result
print("Accuracy Score: {}".format(score))


pred_prob = pipeline_f.predict_proba(X_valid)
print(pred_prob)
```

    Accuracy Score: 0.8681818181818182
    [[0.7959137  0.20408632]
     [0.9082163  0.09178371]
     [0.9838083  0.01619174]
     ...
     [0.90567094 0.09432907]
     [0.9148087  0.08519129]
     [0.9606085  0.0393915 ]]
    


```python
#pipe.predict(X_valid)
#y_valid
y_val  = [1 if  i ==' >50K' else 0  for i in y_valid]
y_pred  = [1 if  i ==' >50K' else 0  for i in preds]
```


```python
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
from sklearn.metrics import precision_recall_fscore_support
from numpy import trapz
from scipy.integrate import simps
from sklearn.metrics import f1_score

def Evaluate(y_val, y_pred):
      ''' A function that calculates the confusion matrix, accuracy, precision, recall, and f1_score.
        Accuracy, precision, recall, and f1_score.'''
      CM = confusion_matrix(y_val, y_pred)
      TN = CM[0][0]
      FN = CM[1][0]
      TP = CM[1][1]
      FP = CM[0][1]
      print(' (True Negatives): {}'.format(TN))
      print(' (False Negatives):  {}'.format(FN))
      print(' (True Positives): {}'.format(TP))
      print(' (False Positives):{}'.format(FP))
      print('Total Number from positive class  from Confusion Matrix : ', np.sum(CM[1]))
      auc = roc_auc_score(y_val, y_pred)
      prec=precision_score(y_val, y_pred)   
      rec=recall_score(y_val, y_pred)
     # calculate F1 score
      f1 = f1_score(y_val, y_pred)
      print('auc :{}'.format(auc))
      print('precision :{}'.format(prec))
      print('recall :{}'.format(rec))
      print('f1 :{}'.format(f1))
    # Compute Precision-Recall and plot curve
      precision, recall, thresholds = precision_recall_curve(y_val, y_pred)
    #use the trapezoidal rule to calculate the area under the precion-recall curve
      area =  trapz(recall, precision)
   
    #area =  simps(recall, precision)
      print("Area Under Precision Recall  Curve(AP): %0.4f" % area)  

    
```


```python
Evaluate(y_val, y_pred)
```

     (True Negatives): 5818
     (False Negatives):  698
     (True Positives): 1249
     (False Positives):375
    Total Number from positive class  from Confusion Matrix :  1947
    auc :0.7904737533993637
    precision :0.7690886699507389
    recall :0.6414997431946584
    f1 :0.6995239428731448
    Area Under Precision Recall  Curve(AP): 0.5090
    


```python

# Create the evaluation report.
#evaluation_report = classification_report(y_val, y_pred, labels=['<=50K','>50K'], target_names=['<=50K','>50K'])
evaluation_report = classification_report(y_valid, preds )
# Show the evaluation report.
print(evaluation_report)

```

                  precision    recall  f1-score   support
    
           <=50K       0.89      0.94      0.92      6193
            >50K       0.77      0.64      0.70      1947
    
        accuracy                           0.87      8140
       macro avg       0.83      0.79      0.81      8140
    weighted avg       0.86      0.87      0.86      8140
    
    


```python
from ml_things import plot_dict, plot_confusion_matrix, fix_text

# Plot confusion matrix.
# <=50K    24719
# >50K      7841
# Plot confusion matrix.

plot_confusion_matrix(y_true=y_val, y_pred=y_pred, 
                      classes=['<=50K','>50K'], normalize=False, 
                      magnify=1,
                      );


plot_confusion_matrix(y_true=y_val, y_pred=y_pred, 
                      classes=['<=50K','>50K'], normalize=True, 
                      magnify=1,
                      );
 #y_true=y_val, y_pred=y_pred,                     
```

    Confusion matrix, without normalization
    Normalized confusion matrix
    


    

![png](/img/pipelines/output_48_1.png)
    



    

![png](/img/pipelines/output_61_1.png)
    


The intermediate steps in a Pipeline
can be accessed by  using the "named_steps" attribute:

pipe.named_steps.STEP_NAME.ATTRIBUTE


```python
#xgb_no_weights_pred = xgb_no_weights.predict_proba(test_x)
#xgb_pred = xgb_model.predict_proba(test_set)[:,1]
#joblib.dump(xgb_model, 'C:\\Users\\admin1\\Desktop\\WORK\\xgbmodel.joblib')
#xgb_model =  joblib.load( '/content/drive/My Drive/ImbalancedData/xgb_no_weights.joblib')
#print(pipe.steps[1])
print(pipeline_f.steps[1][1].feature_importances_.shape)
print(pipeline_f.named_steps.classifier)
print(pipeline_f.named_steps.preprocessor)
```

    (108,)
    XGBClassifier(base_score=0.5, booster='gbtree', colsample_bylevel=1,
                  colsample_bynode=1, colsample_bytree=0.8, eta=0.1,
                  eval_metric='auc', gamma=0.05, learning_rate=0.1,
                  max_delta_step=1, max_depth=6, min_child_weight=2, missing=None,
                  n_estimators=100, n_jobs=-1, nthread=-1,
                  objective='binary:logistic', random_state=0, reg_alpha=0,
                  reg_lambda=1, scale_pos_weight=1, seed=None, silent=1,
                  subsample=0.7, tree_method='approx', verbose=1, verbosity=1)
    ColumnTransformer(n_jobs=None, remainder='drop', sparse_threshold=0.3,
                      transformer_weights=None,
                      transformers=[('num',
                                     Pipeline(memory=None,
                                              steps=[('imputer',
                                                      SimpleImputer(add_indicator=False,
                                                                    copy=True,
                                                                    fill_value=-9999999,
                                                                    missing_values=nan,
                                                                    strategy='constant',
                                                                    verbose=0)),
                                                     ('scaler',
                                                      StandardScaler(copy=True,
                                                                     with_mean=True,
                                                                     with_std=True))],
                                              verbose=False),...
                                                      OneHotEncoder(categories='auto',
                                                                    drop=None,
                                                                    dtype=<class 'numpy.float64'>,
                                                                    handle_unknown='ignore',
                                                                    sparse=True)),
                                                     ('imputer',
                                                      SimpleImputer(add_indicator=False,
                                                                    copy=True,
                                                                    fill_value=-9999.01,
                                                                    missing_values=nan,
                                                                    strategy='constant',
                                                                    verbose=0))],
                                              verbose=False),
                                     ['workclas', 'education', 'marital-status',
                                      'occupation', 'relationship', 'race', 'sex',
                                      'native-country'])],
                      verbose=False)
    


```python

preprocessor.fit(X_train)
#preprocessor.get_feature_names()
```




<style>div.sk-top-container {color: black;background-color: white;}div.sk-toggleable {background-color: white;}label.sk-toggleable__label {cursor: pointer;display: block;width: 100%;margin-bottom: 0;padding: 0.2em 0.3em;box-sizing: border-box;text-align: center;}div.sk-toggleable__content {max-height: 0;max-width: 0;overflow: hidden;text-align: left;background-color: #f0f8ff;}div.sk-toggleable__content pre {margin: 0.2em;color: black;border-radius: 0.25em;background-color: #f0f8ff;}input.sk-toggleable__control:checked~div.sk-toggleable__content {max-height: 200px;max-width: 100%;overflow: auto;}div.sk-estimator input.sk-toggleable__control:checked~label.sk-toggleable__label {background-color: #d4ebff;}div.sk-label input.sk-toggleable__control:checked~label.sk-toggleable__label {background-color: #d4ebff;}input.sk-hidden--visually {border: 0;clip: rect(1px 1px 1px 1px);clip: rect(1px, 1px, 1px, 1px);height: 1px;margin: -1px;overflow: hidden;padding: 0;position: absolute;width: 1px;}div.sk-estimator {font-family: monospace;background-color: #f0f8ff;margin: 0.25em 0.25em;border: 1px dotted black;border-radius: 0.25em;box-sizing: border-box;}div.sk-estimator:hover {background-color: #d4ebff;}div.sk-parallel-item::after {content: "";width: 100%;border-bottom: 1px solid gray;flex-grow: 1;}div.sk-label:hover label.sk-toggleable__label {background-color: #d4ebff;}div.sk-serial::before {content: "";position: absolute;border-left: 1px solid gray;box-sizing: border-box;top: 2em;bottom: 0;left: 50%;}div.sk-serial {display: flex;flex-direction: column;align-items: center;background-color: white;}div.sk-item {z-index: 1;}div.sk-parallel {display: flex;align-items: stretch;justify-content: center;background-color: white;}div.sk-parallel-item {display: flex;flex-direction: column;position: relative;background-color: white;}div.sk-parallel-item:first-child::after {align-self: flex-end;width: 50%;}div.sk-parallel-item:last-child::after {align-self: flex-start;width: 50%;}div.sk-parallel-item:only-child::after {width: 0;}div.sk-dashed-wrapped {border: 1px dashed gray;margin: 0.2em;box-sizing: border-box;padding-bottom: 0.1em;background-color: white;position: relative;}div.sk-label label {font-family: monospace;font-weight: bold;background-color: white;display: inline-block;line-height: 1.2em;}div.sk-label-container {position: relative;z-index: 2;text-align: center;}div.sk-container {display: inline-block;position: relative;}</style><div class="sk-top-container"><div class="sk-container"><div class="sk-item sk-dashed-wrapped"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="a7b4a31d-074c-4e77-a729-90550c63db05" type="checkbox" ><label class="sk-toggleable__label" for="a7b4a31d-074c-4e77-a729-90550c63db05">ColumnTransformer</label><div class="sk-toggleable__content"><pre>ColumnTransformer(transformers=[('num',
                                 Pipeline(steps=[('imputer',
                                                  SimpleImputer(fill_value=-9999999,
                                                                strategy='constant')),
                                                 ('scaler', StandardScaler())]),
                                 ['age', 'fnlwgt', 'education-num',
                                  'capital-gain', 'capital-loss',
                                  'hours-per-week']),
                                ('cat',
                                 Pipeline(steps=[('onehot',
                                                  OneHotEncoder(handle_unknown='ignore')),
                                                 ('imputer',
                                                  SimpleImputer(fill_value=-9999.01,
                                                                strategy='constant'))]),
                                 ['workclas', 'education', 'marital-status',
                                  'occupation', 'relationship', 'race', 'sex',
                                  'native-country'])])</pre></div></div></div><div class="sk-parallel"><div class="sk-parallel-item"><div class="sk-item"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="110c55a3-6627-4f37-b585-6b9608470f78" type="checkbox" ><label class="sk-toggleable__label" for="110c55a3-6627-4f37-b585-6b9608470f78">num</label><div class="sk-toggleable__content"><pre>['age', 'fnlwgt', 'education-num', 'capital-gain', 'capital-loss', 'hours-per-week']</pre></div></div></div><div class="sk-serial"><div class="sk-item"><div class="sk-serial"><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="a14def71-270c-4e0e-a44d-c0439bbbc70a" type="checkbox" ><label class="sk-toggleable__label" for="a14def71-270c-4e0e-a44d-c0439bbbc70a">SimpleImputer</label><div class="sk-toggleable__content"><pre>SimpleImputer(fill_value=-9999999, strategy='constant')</pre></div></div></div><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="cdb0c481-04e0-4bbc-8ec7-f052501048e2" type="checkbox" ><label class="sk-toggleable__label" for="cdb0c481-04e0-4bbc-8ec7-f052501048e2">StandardScaler</label><div class="sk-toggleable__content"><pre>StandardScaler()</pre></div></div></div></div></div></div></div></div><div class="sk-parallel-item"><div class="sk-item"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="7fb9fed1-a59f-41f9-b072-a8b08734c2f4" type="checkbox" ><label class="sk-toggleable__label" for="7fb9fed1-a59f-41f9-b072-a8b08734c2f4">cat</label><div class="sk-toggleable__content"><pre>['workclas', 'education', 'marital-status', 'occupation', 'relationship', 'race', 'sex', 'native-country']</pre></div></div></div><div class="sk-serial"><div class="sk-item"><div class="sk-serial"><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="9fbb45bc-14bd-4785-b003-a3027d73a5fd" type="checkbox" ><label class="sk-toggleable__label" for="9fbb45bc-14bd-4785-b003-a3027d73a5fd">OneHotEncoder</label><div class="sk-toggleable__content"><pre>OneHotEncoder(handle_unknown='ignore')</pre></div></div></div><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="2c4b99f0-c5da-4dbf-acfb-956935077601" type="checkbox" ><label class="sk-toggleable__label" for="2c4b99f0-c5da-4dbf-acfb-956935077601">SimpleImputer</label><div class="sk-toggleable__content"><pre>SimpleImputer(fill_value=-9999.01, strategy='constant')</pre></div></div></div></div></div></div></div></div></div></div></div></div>




```python
from sklearn.compose import ColumnTransformer
#preprocessor.get_feature_names()
#pipeline_f.get_feature_names()
#pipeline_f["pipeline_f"]["pipeline_f"][-1]
preprocessor.transform(X).toarray()
```




    array([[ 0.83962322, -1.01883977,  1.13061257, ...,  1.        ,
             0.        ,  0.        ],
           [-0.04263147,  0.24414566, -0.41852807, ...,  1.        ,
             0.        ,  0.        ],
           [ 1.06018689,  0.4261946 , -1.19309838, ...,  1.        ,
             0.        ,  0.        ],
           ...,
           [ 1.42779301, -0.36414118, -0.41852807, ...,  1.        ,
             0.        ,  0.        ],
           [-1.21897105,  0.10904291, -0.41852807, ...,  1.        ,
             0.        ,  0.        ],
           [ 0.98666566,  0.93398469, -0.41852807, ...,  1.        ,
             0.        ,  0.        ]])



The pipeline can be exported/saved  to file as follows:


```python
#!pip install scikit-learn==0.23.2
from sklearn.utils import estimator_html_repr

with open('/content/drive/My Drive/Data/pipeline.html','w') as f:
     f.write(estimator_html_repr(pipeline_f))
```

The pipeline can also be plotted as shown below:


```python
#plot pipeline
from sklearn import set_config


set_config(display='diagram')   
# diplays HTML representation in a jupyter context
pipeline_f 
```




<style>div.sk-top-container {color: black;background-color: white;}div.sk-toggleable {background-color: white;}label.sk-toggleable__label {cursor: pointer;display: block;width: 100%;margin-bottom: 0;padding: 0.2em 0.3em;box-sizing: border-box;text-align: center;}div.sk-toggleable__content {max-height: 0;max-width: 0;overflow: hidden;text-align: left;background-color: #f0f8ff;}div.sk-toggleable__content pre {margin: 0.2em;color: black;border-radius: 0.25em;background-color: #f0f8ff;}input.sk-toggleable__control:checked~div.sk-toggleable__content {max-height: 200px;max-width: 100%;overflow: auto;}div.sk-estimator input.sk-toggleable__control:checked~label.sk-toggleable__label {background-color: #d4ebff;}div.sk-label input.sk-toggleable__control:checked~label.sk-toggleable__label {background-color: #d4ebff;}input.sk-hidden--visually {border: 0;clip: rect(1px 1px 1px 1px);clip: rect(1px, 1px, 1px, 1px);height: 1px;margin: -1px;overflow: hidden;padding: 0;position: absolute;width: 1px;}div.sk-estimator {font-family: monospace;background-color: #f0f8ff;margin: 0.25em 0.25em;border: 1px dotted black;border-radius: 0.25em;box-sizing: border-box;}div.sk-estimator:hover {background-color: #d4ebff;}div.sk-parallel-item::after {content: "";width: 100%;border-bottom: 1px solid gray;flex-grow: 1;}div.sk-label:hover label.sk-toggleable__label {background-color: #d4ebff;}div.sk-serial::before {content: "";position: absolute;border-left: 1px solid gray;box-sizing: border-box;top: 2em;bottom: 0;left: 50%;}div.sk-serial {display: flex;flex-direction: column;align-items: center;background-color: white;}div.sk-item {z-index: 1;}div.sk-parallel {display: flex;align-items: stretch;justify-content: center;background-color: white;}div.sk-parallel-item {display: flex;flex-direction: column;position: relative;background-color: white;}div.sk-parallel-item:first-child::after {align-self: flex-end;width: 50%;}div.sk-parallel-item:last-child::after {align-self: flex-start;width: 50%;}div.sk-parallel-item:only-child::after {width: 0;}div.sk-dashed-wrapped {border: 1px dashed gray;margin: 0.2em;box-sizing: border-box;padding-bottom: 0.1em;background-color: white;position: relative;}div.sk-label label {font-family: monospace;font-weight: bold;background-color: white;display: inline-block;line-height: 1.2em;}div.sk-label-container {position: relative;z-index: 2;text-align: center;}div.sk-container {display: inline-block;position: relative;}</style><div class="sk-top-container"><div class="sk-container"><div class="sk-item sk-dashed-wrapped"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="ee34d542-63bb-4366-9a9b-26c1aaf47e64" type="checkbox" ><label class="sk-toggleable__label" for="ee34d542-63bb-4366-9a9b-26c1aaf47e64">Pipeline</label><div class="sk-toggleable__content"><pre>Pipeline(steps=[('preprocessor',
                 ColumnTransformer(transformers=[('num',
                                                  Pipeline(steps=[('imputer',
                                                                   SimpleImputer(fill_value=-9999999,
                                                                                 strategy='constant')),
                                                                  ('scaler',
                                                                   StandardScaler())]),
                                                  ['age', 'fnlwgt',
                                                   'education-num',
                                                   'capital-gain',
                                                   'capital-loss',
                                                   'hours-per-week']),
                                                 ('cat',
                                                  Pipeline(steps=[('onehot',
                                                                   OneHotEncoder(handle_unknown='ignore')),
                                                                  ('imputer',
                                                                   SimpleImputer(fill_value=-9999.01,
                                                                                 strategy='constant'))]),
                                                  ['workclas', 'education',
                                                   'marital-status',
                                                   'occupation', 'relationship',
                                                   'race', 'sex',
                                                   'native-country'])])),
                ('classifier',
                 XGBClassifier(colsample_bytree=0.8, eta=0.1, eval_metric='auc',
                               gamma=0.05, max_delta_step=1, max_depth=6,
                               min_child_weight=2, n_jobs=-1, subsample=0.7,
                               tree_method='approx', verbose=1))])</pre></div></div></div><div class="sk-serial"><div class="sk-item sk-dashed-wrapped"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="1e74eb66-f302-4094-a2a7-37b359aaf36a" type="checkbox" ><label class="sk-toggleable__label" for="1e74eb66-f302-4094-a2a7-37b359aaf36a">preprocessor: ColumnTransformer</label><div class="sk-toggleable__content"><pre>ColumnTransformer(transformers=[('num',
                                 Pipeline(steps=[('imputer',
                                                  SimpleImputer(fill_value=-9999999,
                                                                strategy='constant')),
                                                 ('scaler', StandardScaler())]),
                                 ['age', 'fnlwgt', 'education-num',
                                  'capital-gain', 'capital-loss',
                                  'hours-per-week']),
                                ('cat',
                                 Pipeline(steps=[('onehot',
                                                  OneHotEncoder(handle_unknown='ignore')),
                                                 ('imputer',
                                                  SimpleImputer(fill_value=-9999.01,
                                                                strategy='constant'))]),
                                 ['workclas', 'education', 'marital-status',
                                  'occupation', 'relationship', 'race', 'sex',
                                  'native-country'])])</pre></div></div></div><div class="sk-parallel"><div class="sk-parallel-item"><div class="sk-item"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="85558373-7e6d-4604-b5f7-67e349a4a288" type="checkbox" ><label class="sk-toggleable__label" for="85558373-7e6d-4604-b5f7-67e349a4a288">num</label><div class="sk-toggleable__content"><pre>['age', 'fnlwgt', 'education-num', 'capital-gain', 'capital-loss', 'hours-per-week']</pre></div></div></div><div class="sk-serial"><div class="sk-item"><div class="sk-serial"><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="bde2ac5f-1273-4ba7-8875-c4fa61baf6dc" type="checkbox" ><label class="sk-toggleable__label" for="bde2ac5f-1273-4ba7-8875-c4fa61baf6dc">SimpleImputer</label><div class="sk-toggleable__content"><pre>SimpleImputer(fill_value=-9999999, strategy='constant')</pre></div></div></div><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="b0f56c26-8268-4c58-8949-b4c86b282b62" type="checkbox" ><label class="sk-toggleable__label" for="b0f56c26-8268-4c58-8949-b4c86b282b62">StandardScaler</label><div class="sk-toggleable__content"><pre>StandardScaler()</pre></div></div></div></div></div></div></div></div><div class="sk-parallel-item"><div class="sk-item"><div class="sk-label-container"><div class="sk-label sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="e8f8e285-b044-4f36-998e-f560b5f26cd8" type="checkbox" ><label class="sk-toggleable__label" for="e8f8e285-b044-4f36-998e-f560b5f26cd8">cat</label><div class="sk-toggleable__content"><pre>['workclas', 'education', 'marital-status', 'occupation', 'relationship', 'race', 'sex', 'native-country']</pre></div></div></div><div class="sk-serial"><div class="sk-item"><div class="sk-serial"><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="9d44337e-c6bf-474a-9260-46888800bef0" type="checkbox" ><label class="sk-toggleable__label" for="9d44337e-c6bf-474a-9260-46888800bef0">OneHotEncoder</label><div class="sk-toggleable__content"><pre>OneHotEncoder(handle_unknown='ignore')</pre></div></div></div><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="32f60081-345a-414e-a2c5-9e58fb05488f" type="checkbox" ><label class="sk-toggleable__label" for="32f60081-345a-414e-a2c5-9e58fb05488f">SimpleImputer</label><div class="sk-toggleable__content"><pre>SimpleImputer(fill_value=-9999.01, strategy='constant')</pre></div></div></div></div></div></div></div></div></div></div><div class="sk-item"><div class="sk-estimator sk-toggleable"><input class="sk-toggleable__control sk-hidden--visually" id="40676a00-295a-4941-8365-cc7d6ad3f771" type="checkbox" ><label class="sk-toggleable__label" for="40676a00-295a-4941-8365-cc7d6ad3f771">XGBClassifier</label><div class="sk-toggleable__content"><pre>XGBClassifier(colsample_bytree=0.8, eta=0.1, eval_metric='auc', gamma=0.05,
              max_delta_step=1, max_depth=6, min_child_weight=2, n_jobs=-1,
              subsample=0.7, tree_method='approx', verbose=1)</pre></div></div></div></div></div></div></div>



Generate pmml from the pipeline using the sklearn2pmml. The  make_pmml_pipeline function  translates a regular Scikit-Learn estimator or pipeline to a PMML pipeline.


```python
from sklearn2pmml import make_pmml_pipeline, sklearn2pmml

pipeline = make_pmml_pipeline(
pipeline_f
#active_fields = ["x1", "x2", ...], optional Feature name
#target_fields = ["y"]  optional target name
)
sklearn2pmml(pipeline, "/content/drive/My Drive/Data/xgbmodel.pmml")
```

    /usr/local/lib/python3.6/dist-packages/sklearn/base.py:213: FutureWarning: From version 0.24, get_params will raise an AttributeError if a parameter cannot be retrieved as an instance attribute. Previously it would return None.
      FutureWarning)
    

Equivalently the pmml could be generated by using the PMMLPipeline  function from the sklearn2pmml in the pipeline steps.


```python
from sklearn2pmml import PMMLPipeline
from sklearn2pmml.decoration import CategoricalDomain, ContinuousDomain
from sklearn_pandas import DataFrameMapper


# it takes a list of tuples as parameter
pipeline = PMMLPipeline(
    [('preprocessor', preprocessor),
                      #('dropfeature',UniqueDropper()),
                      #('anova', SelectPercentile(chi2))
                     # ("feat_sel", SelectKBest(10)),

                      ('classifier', xgb_classifier)]
)

#  the pipeline object is  used similar to how a regular classifier is used in
#scikit-learn.
pipeline.fit(X=X_train,  y=y_train)

from sklearn2pmml import sklearn2pmml

#pipeline = sklearn2pmml.make_pmml_pipeline(pipeline)

sklearn2pmml(pipeline, "/content/drive/My Drive/Data/xgbmodel.pmml", with_repr = True)

```

    /usr/local/lib/python3.6/dist-packages/sklearn/base.py:197: FutureWarning: From version 0.24, get_params will raise an AttributeError if a parameter cannot be retrieved as an instance attribute. Previously it would return None.
      FutureWarning)
    

### Adding Hyperparameter Tuning to Pipeline

The steps in creating a pmml file from pipeline steps above does not include hyperparameter tuning. In the steps below we show how to include hyperparameter tuning in the pipeline steps.


```python
#help(make_pmml_pipeline)
#help(sklearn2pmml)

from sklearn.model_selection import GridSearchCV
from sklearn2pmml import PMMLPipeline
from sklearn2pmml import sklearn2pmml




#pipeline = PMMLPipeline([...])


#tuner = RandomizedSearchCV(pipeline, param_grid = {...})
#tuner.fit(X_train,  y_train)
# GridSearchCV.best_estimator_ is of type PMMLPipeline
#sklearn2pmml(tuner.best_estimator_, "/content/drive/My Drive/Data/xgbmodel.pmml")
```

Equivalently using the  make_pmml_pipeline function is shown below


```python
pipeline.fit(X=X_train,  y=y_train)
```




    PMMLPipeline(steps=[('preprocessor', ColumnTransformer(n_jobs=None, remainder='drop', sparse_threshold=0.3,
                      transformer_weights=None,
                      transformers=[('num',
                                     Pipeline(memory=None,
                                              steps=[('imputer',
                                                      SimpleImputer(add_indicator=False,
                                                                    copy=True,
                                                                    fill_value=-9999999,
                                                                    missing_values=nan,
                                                                    strategy='constant',
                                                                    verbose=0)),
                                                     ('scaler',
                                                      StandardScaler(copy=True,
                                                                     with_mean=True,
                                                                     with_std=True))],
                                              verbose=False),...
                                                      OneHotEncoder(categories='auto',
                                                                    drop=None,
                                                                    dtype=<class 'numpy.float64'>,
                                                                    handle_unknown='error',
                                                                    sparse=True)),
                                                     ('imputer',
                                                      SimpleImputer(add_indicator=False,
                                                                    copy=True,
                                                                    fill_value=-9999.01,
                                                                    missing_values=nan,
                                                                    strategy='constant',
                                                                    verbose=0))],
                                              verbose=False),
                                     ['workclas', 'education', 'marital-status',
                                      'occupation', 'relationship', 'race', 'sex',
                                      'native-country'])],
                      verbose=False)),
           ('classifier', XGBClassifier(base_score=0.5, booster='gbtree', colsample_bylevel=1,
                  colsample_bynode=1, colsample_bytree=0.8, eta=0.1,
                  eval_metric='auc', gamma=0.05, learning_rate=0.1,
                  max_delta_step=1, max_depth=6, min_child_weight=2, missing=None,
                  n_estimators=100, n_jobs=-1, nthread=-1,
                  objective='binary:logistic', random_state=0, reg_alpha=0,
                  reg_lambda=1, scale_pos_weight=1, seed=None, silent=1,
                  subsample=0.7, tree_method='approx', verbose=1, verbosity=1))])




```python
# Define model parameters for grid search
search_spaces = {'classifier__learning_rate': [0.1],
              'classifier__n_estimators': [100],
              'classifier__max_depth': [ 5, 6],
              'classifier__min_child_weight': [1, 2],
              'classifier__gamma': [0.05],
              'classifier__subsample': [ 0.70, 0.80],
              'classifier__colsample_bytree': [ 0.70, 0.80, 0.90],
              'classifier__random_state' : [10]}
```


```python
#RandomizedSearchCV.best_estimator_ is of type PMMLPipeline
tuner  = RandomizedSearchCV(pipeline_f, search_spaces, cv=5, n_jobs=-1,scoring='roc_auc')
tuner.fit(X=X_train,  y=y_train)
sklearn2pmml(make_pmml_pipeline(tuner.best_estimator_),
 "/content/drive/My Drive/Data/xgbmodel.pmml")
```

    /usr/local/lib/python3.6/dist-packages/sklearn/base.py:197: FutureWarning: From version 0.24, get_params will raise an AttributeError if a parameter cannot be retrieved as an instance attribute. Previously it would return None.
      FutureWarning)
    

We can look at the best parameter values from the hyperparameter search.


```python

tuner.best_estimator_.get_params
```




    <bound method Pipeline.get_params of Pipeline(memory=None,
             steps=[('preprocessor',
                     ColumnTransformer(n_jobs=None, remainder='drop',
                                       sparse_threshold=0.3,
                                       transformer_weights=None,
                                       transformers=[('num',
                                                      Pipeline(memory=None,
                                                               steps=[('imputer',
                                                                       SimpleImputer(add_indicator=False,
                                                                                     copy=True,
                                                                                     fill_value=-9999999,
                                                                                     missing_values=nan,
                                                                                     strategy='constant',
                                                                                     verbose=0)),
                                                                      ('scaler',
                                                                       StandardScaler(copy=True,
                                                                                      wit...
                                   colsample_bytree=0.8, eta=0.1, eval_metric='auc',
                                   gamma=0.05, learning_rate=0.1, max_delta_step=1,
                                   max_depth=6, min_child_weight=2, missing=None,
                                   n_estimators=100, n_jobs=-1, nthread=-1,
                                   objective='binary:logistic', random_state=10,
                                   reg_alpha=0, reg_lambda=1, scale_pos_weight=1,
                                   seed=None, silent=1, subsample=0.7,
                                   tree_method='approx', verbose=1, verbosity=1))],
             verbose=False)>



Using the second pipeline with RandomizedSearchCV to  generate pmml is shown below


```python
#import matplotlib.pyplot as plt
#from sklearn2pmml import make_pmml_pipeline, sklearn2pmml


#tuner = RandomizedSearchCV(pipeline, search_spaces)
#tuner.fit(X=X_train,  y=y_train)
# GridSearchCV.best_estimator_ is of type Pipeline
#sklearn2pmml(make_pmml_pipeline(tuner.best_estimator_),
                  #active_fields =
#[...], target_fields = [...]),
# "/content/drive/My Drive/Data/xgbmodel.pmml"
#)
print("Best parameter (CV score=%0.3f):" % tuner.best_score_)
print('Best Hyperparameter values :{}'.format(tuner.best_params_))
```

    Best parameter (CV score=0.925):
    Best Hyperparameter values :{'classifier__subsample': 0.8, 'classifier__random_state': 10, 'classifier__n_estimators': 100, 'classifier__min_child_weight': 1, 'classifier__max_depth': 6, 'classifier__learning_rate': 0.1, 'classifier__gamma': 0.05, 'classifier__colsample_bytree': 0.7}
    


```python

#fig, ax = plt.subplots(figsize=(12,18))
#xgb.plot_importance(xgb_model, max_num_features=50, height=0.8, ax=ax)
#plt.show()
```


```python
sklearn2pmml(pmml_pipeline, "C:/Users/admin1/Desktop/WORK/xgboost.pmml")
```

After the pmml is created, the acccuracy of predictions from the pmml fie can be compared with that from the scikit-learn by using the pypmml library. The library allows you to read a pmml file and make predictions on test data.


```python
#!pip install pypmml
!ls '/content/drive/My Drive/Data/xgbmodel.pmml'
```

    '/content/drive/My Drive/Data/xgbmodel.pmml'
    


```python

"""
import pmml file into python
"""

from pypmml import Model
import pandas as pd



model = Model.fromFile("/content/drive/My Drive/Data/xgbmodel.pmml") 
```

Use the preprocessor from the pipeline to prepare the test data for prediction


```python
#
test_data = preprocessor.transform(X_valid).toarray()
#Prediction
new_pred = model.predict(test_data)

```
