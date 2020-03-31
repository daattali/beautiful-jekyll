Bài viết thứ 2 nằm trong series về **Credit Scorecard** trong các tổ chức tín dụng. Trong bài này chúng ta cùng tìm hiểu cách ứng dụng các mô hình Machine trong chấm điểm tín dụng cũng như tìm ra mô hình tối ưu nhất. 

**Credit Scorecard** với mục tiêu là chấm điểm và phân loại khách hàng, cho phép đưa ra quyết định về chính sách can thiệp nhằm tối ưu hóa hiệu quả kinh doanh.

Thí dụ minh họa là một dữ liệu về thông tin cơ bản cũng như lịch sử hành vi của khách hàng thuộc nhóm trễ hạn nợ 2 tháng (B2_BOM).

Bài toán được giải quyết dựa trên dữ liệu của 10000 khách hàng, bao gồm nhiều thông tin, các thông tin đã được biến đổi cũng như thay đổi tên trường để đảm bảo lý do bảo mật.

Biến output : **label**
- label = 1: khách hàng không thanh toán 
- label = 0: khách hàng thanh toán


Mục tiêu gồm : 
1. Các phương pháp chuyển dạng, chuẩn hóa dữ liệu
2. Giới thiệu các thuật toán machine learning cơ bản 
3. Turning model sử dụng GridSearchCV và tìm ra mô hình tối ưu

_______________________________

Các thư viện cần dùng:


```python
import numpy as np
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt
%matplotlib inline

import warnings
warnings.filterwarnings('ignore')
```


```python
df = pd.read_csv('credit_data.csv')
df.columns
```




    Index(['field0', 'field1', 'field2', 'field3', 'field4', 'field5', 'field6',
           'field7', 'field8', 'field9', 'field10', 'field11', 'field12',
           'field13', 'field14', 'field15', 'field16', 'field17', 'field18',
           'field19', 'field20', 'field21', 'field22', 'field23', 'field24',
           'field25', 'field26', 'field27', 'field28', 'field29', 'field30',
           'field31', 'field32', 'field33', 'field34', 'field35', 'field36',
           'field37', 'field38', 'field39', 'field40', 'label'],
          dtype='object')



## Bước 1: TRANFORM DATA

Do dữ liệu đã được clean nên chúng ta đến thẳng bước tranform data để chuẩn bị training model machine learning

### OneHotEncoder

Kỹ thuật onehot (hay dummy) là kỹ thuật chuyển dạng dữ liệu từ dạng **chuỗi** sang dạng bool mà vẫn giữ nguyên được giá trị thông tin của dữ liệu. Với phương thức là với mỗi giá trị trong trường dữ liệu cũ ta tạo một trường dữ liệu mới thể hiện rằng dữ liệu tại đó có bằng giá trị đó không. 

Chúng ta sẽ thấy rõ nó hoạt động thế nào sau bước dưới đây:


```python
# chọn các trường dữ liệu chuỗi 
object_cols = list(df.dtypes[df.dtypes == 'object'].index)
df[object_cols].head(3)
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
      <th>field2</th>
      <th>field3</th>
      <th>field9</th>
      <th>field10</th>
      <th>field13</th>
      <th>field35</th>
      <th>field38</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>field2_v0</td>
      <td>field3_v0</td>
      <td>field9_v0</td>
      <td>field10_v0</td>
      <td>field13_v0</td>
      <td>field35_v0</td>
      <td>field38_v0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>field2_v1</td>
      <td>field3_v0</td>
      <td>field9_v0</td>
      <td>field10_v1</td>
      <td>field13_v1</td>
      <td>field35_v0</td>
      <td>field38_v1</td>
    </tr>
    <tr>
      <th>2</th>
      <td>field2_v2</td>
      <td>field3_v1</td>
      <td>field9_v0</td>
      <td>field10_v2</td>
      <td>field13_v2</td>
      <td>field35_v0</td>
      <td>field38_v2</td>
    </tr>
  </tbody>
</table>
</div>




```python
from sklearn.preprocessing import OneHotEncoder

onehot = OneHotEncoder(handle_unknown='ignore')
onehot_data = pd.DataFrame(onehot.fit_transform(df[object_cols]).toarray(),
                           columns=onehot.get_feature_names(object_cols)) # đặt columns names

# data sau khi OneHotEncoder
onehot_data.loc[:2,['field2_field2_v0','field2_field2_v1', 'field2_field2_v2']]
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
      <th>field2_field2_v0</th>
      <th>field2_field2_v1</th>
      <th>field2_field2_v2</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0.0</td>
      <td>1.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>1.0</td>
    </tr>
  </tbody>
</table>
</div>




```python
# tổng hợp dữ liệu đã được onehot 
data = pd.concat([onehot_data, df.drop(object_cols,axis=1)],axis=1)
```

### MinMaxScaler

Là kỹ thuật chuẩn hóa dữ liệu phổ biến cho các dữ liệu **Nunberic**. Với cơ chế là đưa dữ liệu về 1 thang đo mới 
vd: *MinMaxScaler(feature_range=(-1,1))*
   - -1 : giá trị nhỏ nhất 
   -   1 : giá trị lớn nhất 

**Tại sao chuẩn hóa dữ liệu lại cẩn thiết ?** 

Vì khi tính toán với nhiều trường dữ liệu khác nhau thì sẽ có các phép toán kiểu như : **age** + **loan** 
Giả sử khách hàng 45 tuổi và vay 50 triệu thì việc lấy số 45 tuổi + 50 triệu có sự bất đồng lớn về thang đo tính toán

Do vậy ta cần đưa **age** và **loan** về cùng thang đo (-1,1) để đạt được hiệu quả cao khi traing model

*Tuy dữ liệu đã được chuẩn hóa nhưng ta vẫn thực hiện lại bước này để demo*


```python
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler(feature_range=(-1,1))

# chọn các trường dữ liệu Nunberic trừ 'label'
df_num = df.drop(['label'], axis=1)._get_numeric_data()

# scale and transform data 
scale_data = scaler.fit_transform(df_num )
scale_data = pd.DataFrame(scale_data, columns=df_num.columns)

# tổng hợp dữ liệu đã được scale 
for col in scale_data.columns:
    data[col] = scale_data[col]
```

## Bước 2 : TRAINING MODEL

Sau khi dữ liệu đã sạch sẽ thơm tho thì chún ta có thể đem đi xào nấu thỏa thích với đủ thể loại thuật toán machine learning

Việc đầu tiên chúng ta cần làm là chia tệp dữ liệu thành các bộ traing_set và test_set:


```python
from sklearn.model_selection import train_test_split

X = data.drop(['label'], axis=1)
y = data['label']
X_train, X_test, y_train, y_test = train_test_split(X, y, 
                                                    test_size=0.3,
                                                    random_state = 15, 
                                                    stratify = y)

```

## Define models and gridsearchs

*Chỉ có 1 cách để biết được mô hình nào là tốt nhất là thử nghiệm thật nhiều loại mô hình.*

Nhưng lại có một vấn để như sau: 

Giả sử ta muốn tìm mô hình tốt hơn giữ mô hình Logistic và mô hình KNN, vậy đầu tiên ta phải tìm được mô hình Logistic tốt nhất và mô hình KNN tốt nhất, sau đó mới so sánh chúng với nhau để tìm ra cái tốt hơn trong những cái tốt.

Nghe hơi rối não nhưng ở đây chúng ta sẽ đề cạp đến 2 khái niệm để giải thích vấn đề này: 

**Parameter** vs **Hyper Parameter**:

- **Parameter** : Tham số trong các phương trình tối ưu của thuật toán , 
        vd: khi chúng ta xét hàm tuyến tính: f(x) = a*x + b thì a và b chính là các Parameter 
        
        => chúng ta cần tìm các parameter để mô hình fit với tập dữ liệu
- **Hyper Parameter**: Siêu tham số trong các mô hình machine learning
        vd: khi chúng ta định nghĩa mô hình RandomForestClassifier(max_features='sqrt', criterion='gini')
        Thì max_features và criterion là các hyper parameter của mô hình là các rule, thuật toán cụ thể mô hình sẽ sử dụng
        
        => chúng ta cần tìm các hyper parameter để tìm ra bộ setup tốt nhất cho mô hình machine learning
         GridSearchCV tìm kiếm hyper parameter tối ưu qua bộ param_grid truyền vào bằng cách chạy từng trường hợp của bộ 
         param và lựa chọn params cho score tốt nhất
         


```python
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.neural_network import MLPClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier
from scipy import stats

from sklearn.metrics import accuracy_score
from sklearn.metrics import recall_score
from sklearn.metrics import precision_score
from sklearn.metrics import f1_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import roc_curve
from sklearn.metrics import roc_auc_score
import scikitplot as skplt
```


```python
classifiers = [
    [GridSearchCV(estimator=KNeighborsClassifier(n_jobs=-1), param_grid={
        'n_neighbors': [5, 7, 9, 11, 15, 20]
    }, scoring='roc_auc',cv=3, n_jobs=-1), "KNN"],
    [GridSearchCV(estimator=SVC(), param_grid={
        'kernel': ['linear', 'rbf'],
        'C': [0.001, 0.01, 0.1],
        'gamma': [0.001, 0.01, 0.1,]
    }, scoring='roc_auc', cv=3, n_jobs=-1), "SVM"],
    [GridSearchCV(estimator=RandomForestClassifier(n_jobs=-1), param_grid={
        'n_estimators': [200, 500],
        'max_features': ['sqrt', 'log2'],
        'max_depth': [ 7, 8, 12],
        'criterion': ['gini', 'entropy']
    }, scoring='roc_auc', cv=3, n_jobs=-1), "RF"],
    [GridSearchCV(estimator=MLPClassifier(), param_grid={
        'solver': ['lbfgs'],
        'max_iter': [ 1500,2000],
        'alpha': 10.0 ** -np.arange(1, 3),
        'hidden_layer_sizes': np.arange(15, 20),
    }, scoring='roc_auc', cv=3, n_jobs=-1), "MLP"],
    [GridSearchCV(estimator=AdaBoostClassifier(base_estimator=DecisionTreeClassifier()), param_grid={
        'n_estimators': (5, 10),
        'base_estimator__max_depth': (5, 8, 12),
        'algorithm': ('SAMME', 'SAMME.R')
    }, scoring='roc_auc', cv=3, n_jobs=-1), "Ada"]
]
```

**Thực hiện GridSearchCV cho từng thuật toán và so sánh kết quả theo AUC**


```python
results = []
for clf in classifiers:
    clf[0].fit(X_train, y_train)
    results.append((clf[1], clf[0].best_score_, clf[0].best_params_))
results = pd.DataFrame(results, columns=['classifier', 'auc', 'best_params']) 
results
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
      <th>classifier</th>
      <th>auc</th>
      <th>best_params</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>KNN</td>
      <td>0.697754</td>
      <td>{'n_neighbors': 20}</td>
    </tr>
    <tr>
      <th>1</th>
      <td>SVM</td>
      <td>0.744170</td>
      <td>{'C': 0.1, 'gamma': 0.01, 'kernel': 'rbf'}</td>
    </tr>
    <tr>
      <th>2</th>
      <td>RF</td>
      <td>0.773504</td>
      <td>{'criterion': 'entropy', 'max_depth': 12, 'max...</td>
    </tr>
    <tr>
      <th>3</th>
      <td>MLP</td>
      <td>0.653790</td>
      <td>{'alpha': 0.01, 'hidden_layer_sizes': 17, 'max...</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Ada</td>
      <td>0.724699</td>
      <td>{'algorithm': 'SAMME', 'base_estimator__max_de...</td>
    </tr>
  </tbody>
</table>
</div>




```python
sns.set_palette("pastel")
sns.set_style('ticks')
_, ax = plt.subplots(figsize = (7,4))
sns.barplot(x='classifier', y='auc', data=results, ax=ax)
for i, auc in enumerate(results['auc']):
    ax.text(i-0.2, auc, str(round(auc,2)))
ax.set_title('AUC of classifiers')
plt.show()
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/credit_scorecard_01.png)


**Model RF: RandomForestClassifier() cho kết quả AUC cao nhất : 0.77**

do vậy ta dùng bộ best params của mô hình của RF để train mô hình dự báo chính của chúng ta.


```python
results[results['classifier']=='RF']['best_params'].iloc[0]
```




    {'criterion': 'entropy',
     'max_depth': 12,
     'max_features': 'log2',
     'n_estimators': 200}




```python
rf = RandomForestClassifier(criterion='entropy',
                            max_depth=12,
                            max_features='log2',
                            n_estimators=200)
rf.fit(X_train, y_train)
```




    RandomForestClassifier(bootstrap=True, class_weight=None, criterion='entropy',
                           max_depth=12, max_features='log2', max_leaf_nodes=None,
                           min_impurity_decrease=0.0, min_impurity_split=None,
                           min_samples_leaf=1, min_samples_split=2,
                           min_weight_fraction_leaf=0.0, n_estimators=200,
                           n_jobs=None, oob_score=False, random_state=None,
                           verbose=0, warm_start=False)



**Thêm các metrix để đánh giá mô hình:**


```python
y_pred = rf.predict(X_test)
acc = accuracy_score(y_test, y_pred)
recall = recall_score(y_test, y_pred )
precision = precision_score(y_test, y_pred )
f1 = f1_score(y_test, y_pred)
probs = rf.predict_proba(X_test)[:, 1]
auc = roc_auc_score(y_test,probs)
gini = 2*auc - 1
df_ks = pd.DataFrame({'y':y_test,'y_pred': probs})
ks = stats.ks_2samp(df_ks[df_ks['y'] == 0]['y_pred'], 
                    df_ks[df_ks['y'] == 1]['y_pred']).statistic

score_metrix = pd.DataFrame([('accuracy', acc), ('f1', f1), ('recall', recall), 
                             ('precision', precision), ('auc', auc), 
                             ('gini', gini), ('ks', ks)],
                            columns = ['metrix', 'score'])
score_metrix.set_index(['metrix'], drop=True, inplace=True)
score_metrix.T
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
      <th>metrix</th>
      <th>accuracy</th>
      <th>f1</th>
      <th>recall</th>
      <th>precision</th>
      <th>auc</th>
      <th>gini</th>
      <th>ks</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>score</th>
      <td>0.821667</td>
      <td>0.387171</td>
      <td>0.26868</td>
      <td>0.692623</td>
      <td>0.769251</td>
      <td>0.538503</td>
      <td>0.417165</td>
    </tr>
  </tbody>
</table>
</div>



Do chúng ta đang cố gắp phân loại khách hàng vào 2 nhóm, do vậy chỉ số **AUC** và **KS** sẽ được ưu tiên dùng trong việc đánh giá mô hình


```python
fpr, tpr, thresholds = roc_curve(y_test, probs)
fig, (ax,ax2) = plt.subplots(1,2,figsize = (10,4))
ax.plot([0, 1], [0, 1],  linestyle='--', color = 'black')
ax.plot(fpr, tpr,linewidth= 3)
ax.set_xlabel('False Positive Rate',fontsize=8)
ax.set_ylabel('True Positive Rate',fontsize=8)
ax.set_title('ROC Curve',fontsize=12)
ax.text(0.45,0.3,'GINI : '+str(round(gini*100,2))+' %',fontsize = 10)
ax.text(0.45,0.2,'ROC Curve : '+str(round( auc *100,2))+' %',fontsize = 10)
skplt.metrics.plot_ks_statistic(y_test, rf.predict_proba(X_test), 
                                ax= ax2, title_fontsize=12, text_fontsize=10)
plt.legend(fontsize=8) 
plt.show()
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/credit_scorecard_02.png.png)

**Với mô hình RandomForestClassifier, chúng ta có thể lấy được độ quan trọng của từng biến tới mô hình:**


```python
plt.figure()
ims = pd.DataFrame({'x':X_train.columns, 'y':rf.feature_importances_})
ims.set_index('x', drop = True, inplace = True)
ims.sort_values('y', inplace = True, ascending=False)
ims = ims[:20]
fig, ax = plt.subplots(figsize = (12,8))
im.plot.barh(ax=ax)
ax.tick_params(axis='both', which='major', labelsize=10)
plt.title('Feature Importances')
plt.xlabel('Relative Importance')
plt.ylabel('fields')
plt.show()
```


    <Figure size 432x288 with 0 Axes>



![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/credit_scorecard_03.png)



Vậy là tới đây chúng ta đã biết cách để tìm ra mô hình machine learning tối ưu để giải quyết vấn đề của mình, bài cũng khá dài nên chapter này sẽ tạm dừng tại đây.

Kỳ tới chúng ta sẽ đi sâu hơn vào các ứng dụng của machine learning cũng như cách khai thác chúng !
