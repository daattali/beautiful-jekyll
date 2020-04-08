Ở bài trước chúng ta đã có thể xây dựng được mô hình scorecard rồi. Nhưng như vậy là chưa đủ, chúng ta cần trình bày, diễn giải nó một cách khoa học, và dễ hiểu để thuyết phục công ty đưa mô hình vào vận hành.

Do vậy bài này mình sẽ nói về 1 số cách để diễn giải và trình mô hình cho sát với vận hành, với một số đầu mối trong bài các bạn hoàn toàn có thể tự build cho mình các report thật pro. 

Bài này kiến thức thì không có gì cao siêu nhưng hầu hết là do mình tự nghiền ngẫm và học hỏi. Do vậy rất mong nó có ích cho cách bạn dù ít hay nhiều.

Mục tiêu gồm :

    1. Giới thiệu các tiêu chuẩn đánh giá mô hình
    2. Các cách triển khai mô hình 


![Crepe](intro.png)




```python
import numpy as np
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt
%matplotlib inline

import warnings
warnings.filterwarnings('ignore')
```

## Đầu tiên build lại mô hình giống kỳ trước


```python
from sklearn.preprocessing import OneHotEncoder
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
```


```python
df = pd.read_csv('credit_data.csv')
object_cols = list(df.dtypes[df.dtypes == 'object'].index)

# OneHot
onehot = OneHotEncoder(handle_unknown='ignore')
onehot_data = pd.DataFrame(onehot.fit_transform(df[object_cols]).toarray(),
                           columns=onehot.get_feature_names(object_cols)) # đặt columns names

# scale and transform data 
scaler = MinMaxScaler(feature_range=(-1,1))
df_num = df.drop(['label'], axis=1)._get_numeric_data()
scale_data = scaler.fit_transform(df_num )
scale_data = pd.DataFrame(scale_data, columns=df_num.columns)

# tổng hợp dữ liệu đã được onehot 
data = pd.concat([onehot_data, df.drop(object_cols,axis=1)],axis=1)

# tổng hợp dữ liệu đã được scale 
for col in scale_data.columns:
    data[col] = scale_data[col]
    
# TRAINING MODEL
X = data.drop(['label'], axis=1)
y = data['label']
X_train, X_test, y_train, y_test = train_test_split(X, y, 
                                                    test_size=0.3,
                                                    random_state = 15, 
                                                    stratify = y)
clf = LogisticRegression()
clf.fit(X_train, y_train)
```




    LogisticRegression(C=1.0, class_weight=None, dual=False, fit_intercept=True,
                       intercept_scaling=1, l1_ratio=None, max_iter=100,
                       multi_class='auto', n_jobs=None, penalty='l2',
                       random_state=None, solver='lbfgs', tol=0.0001, verbose=0,
                       warm_start=False)



Trong bài này sẽ đề cập đến cách diễn giải và trình bày là chính, do vậy ta sẽ dùng mô hình LogisticRegression để làm ví dụ cho đơn giản


```python
pred = clf.predict(X_test)
pred 
```




    array([0., 0., 0., ..., 0., 0., 0.])



## Dự báo với mô hình


**Dự đoán với phương thức predict():**

phương thức predict cho ta kết quả đầu ra với nhãn cụ thể :

Một cách dễ hiểu nếu kết quả là :
 - 0 tương ứng với khách hàng bình thường
 - 1 tương ứng với khách hàng mục tiêu

Phân bổ của các lớp thực tế:


```python
sns.set_palette("Set3")
fig, axs = plt.subplots(ncols=2,figsize=(12,4))
sns.countplot(y_test, ax=axs[0])
for x, y in enumerate(pd.value_counts(y_test)):
    axs[0].text(x, y, str(y), fontsize=12)      
pd.value_counts(y_test).plot.pie(autopct='%1.2f%%', ax=axs[1])  
plt.title('Các class trong tệp thực tế')
plt.show()
```


![png](output_10_0.png)


Phân bổ của các lớp theo dự báo:


```python
sns.set_palette("Set2")
fig, axs = plt.subplots(ncols=2,figsize=(12,4))
sns.countplot(pred, ax=axs[0])
for x, y in enumerate(pd.value_counts(pred)):
    axs[0].text(x, y, str(y), fontsize=12)      
pd.value_counts(pred).plot.pie(autopct='%1.2f%%', ax=axs[1])  
plt.title('Các class theo dự báo')
plt.show()
```


![png](output_12_0.png)


Nhìn vào pie chart ta thấy được tỷ lệ giữa 2 class 0, 1 trong kết quả dự báo của tệp test có sự khác biệt so với thực tế. 

Có vẻ như mô hình dự báo chưa chính xác. Nhưng làm sao để biết được mô hinh chúng ta có hiệu quả và hiệu quả đến bao nhiêu. Chúng ta có thể đánh giá mô hình theo một số phương pháp dưới đây


# Các phương pháp đánh giá mô hình:


Trong các bài toán phân lớp nhị phân (chỉ có 2 lớp) có một lớp quan trọng hơn và cần dự báo chính xác thì lớp quan trọng hơn sẽ được gán nhãn là 1  **Positive**, biến còn lại là 0: **Negative**



Chúng ta cần làm quen với các khái niệm :

- **TP** - True Positive: Số lượng dự đoán là 1 và thực tế là 1 
- **FP** - False Positive: Số lượng dự đoán là 1 và thực tế là 1 
- **TN** - True Negative: Số lượng dự đoán là 0 và thực tế là 0 
- **FN** - False Negative: Số lượng dự đoán là 0 và thực tế là 1 


- **FPR** - False Positive Rate: Tỷ lệ dự báo sai biến Positive
- **FNR** - False Negative Rate: Tỷ lệ bỏ sót biến Positive

confusion_matrix: thể hiện có bao nhiêu dữ liệu được dự đoán vào class nào và class thực sự của chúng.



![Crepe](confusion2.png)


**Accuracy:** = TP+TN / TP+TN+FP+FN  (Tỷ lệ dự đoán đúng )

**Recall:** = TP / TP+FN  (Tỉ lệ Dự đoán true positive trong số những điểm thực sự là positive (TP + FN).)

**Precision:** = TP / TP+FP  (Tỷ lệ số điểm true positive trong số những điểm được phân loại là positive (TP + FP))



#### confusion_matrix:


```python
cr = pd.crosstab( y_test, pred, rownames=['Actual'], colnames=['Predicted'])
sns.heatmap(cr, fmt='', annot=True, cmap="YlGnBu")
plt.show()
```


![png](output_16_0.png)


#### Các chỉ số:


```python
from sklearn.metrics import accuracy_score
from sklearn.metrics import recall_score
from sklearn.metrics import precision_score
```


```python
y_pred = clf.predict(X_test)
acc = accuracy_score(y_test, y_pred)
recall = recall_score(y_test, y_pred )
precision = precision_score(y_test, y_pred )
score_metrix = pd.DataFrame([('accuracy', acc), ('recall', recall), 
                             ('precision', precision)],
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
      <th>recall</th>
      <th>precision</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>score</th>
      <td>0.812</td>
      <td>0.265501</td>
      <td>0.620818</td>
    </tr>
  </tbody>
</table>
</div>



Quay lại một chút về vấn đề dự đoán với phương thức predict() để hiểu hơn tại sao mô hình lại có thể dự báo nhãn cho tệp test. 



```python
fig, axs = plt.subplots(ncols=2, figsize=(12,4))
x = np.linspace(-10, 10, 100) 
z = 1/(1 + np.exp(-x)) 
for i, c in enumerate([0.5, 0.2]) :
    y1, y2, y3 = 1 + 0*x, c + 0*x, 0*x
    axs[i].plot(x, z, linewidth=4, color = 'k') 
    axs[i].axhline(c, color='k', linestyle='dashed')
    axs[i].fill_between(x, y2, y1, color='red', alpha='0.1')
    axs[i].fill_between(x, y3, y2, color='green', alpha='0.1')
    axs[i].text(-10, c+ 0.02, f'threshold : {c}')
    axs[i].text(3, c/2, '0 - Negative', fontsize=12, weight='bold')
    axs[i].text(3, 0.7, '1 - Positive', fontsize=12, weight='bold')
    axs[i].set_xlabel("x") 
    axs[i].set_ylabel("Y")
    axs[i].set_title(f"Phân lớp với threshold : {c}")
```


![png](output_21_0.png)


Giá trị đầu ra của hàm sigmoid luôn nằm trong khoẳng từ 0 đến 1 nếu ta lấy ngưỡng(threshold) là 0.5 và chia dữ liệu làm 2 phần 
phần < 0.5 sẽ được gán nhãn là 0 và ngược lại thì ta sẽ được kết quả như phương thức predict() đã làm.

Phương thức predict_proba() trả về cho ta giá trị xác xuất, phương thức predict() thì lấy ngưỡng mặc định là 0.5 và đưa ra kết quả phân lớp.

Do vậy nếu ta sử dụng phương thức predict_proba() và thay đổi ngưỡng phân lớp thì kết quả phân lớp sẽ khác biệt rất nhiều, confusion_matrix, accuracy, recall, precision cũng sẽ thay đổi theo. 

Vì mục việc tìm ra các khách hàng không thanh toán - label 1 là quan trọng hơn nên chung ta sẽ cố gắng tăng **FPR** để giảm **FNR**, với tôn chỉ là thà giết lầm còn hơn bỏ sót. Bằng cách giảm ngưỡng(threshold) xuống dưới 0.5(vd: 0.2) chúng ta sẽ làm tăng lượng dữ liệu được gán nhãn **Positive** lên và **TP**, **FP** sẽ tăng , **TN**, **FN** sẽ giảm theo - đồng nghĩa với giá trị **FPR** sẽ tăng

Receiver operating characteristic - ROC curve sẽ thể hiện được FPR và TPR thay đổi thế nào qua các threshold thư viện sklearn 
hỗ trợ chúng ta khảo sát và vẽ ROC curve rất tốt.


```python
from sklearn.metrics import roc_curve, auc
extra = [150, 580, 800]
extrax, extray = [], []
prob = clf.predict_proba(X_test)[:, 1:]
fpr, tpr, thresholds = roc_curve(y_test.tolist(), prob, pos_label = None)
for i in extra:
    extrax.append(fpr[i])
    extray.append(tpr[i])
    print(f"threshold: %.2f, FPR: %.2f, TPR: %.2f" %(thresholds[i], fpr[i], tpr[i]))
```

    threshold: 0.45, FPR: 0.06, TPR: 0.31
    threshold: 0.13, FPR: 0.45, TPR: 0.75
    threshold: 0.07, FPR: 0.85, TPR: 0.97


Vẽ ROC curve và thể hiện 3 ví dụ trên biểu đồ:


```python
plt.figure(figsize=(12,7))
plt.plot(fpr, tpr, lw=2, label='ROC curve (area = %0.2f)'%auc(fpr, tpr))
plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver operating characteristic')
plt.legend(loc="lower right")
for i in extra:
    plt.plot(fpr[i],tpr[i],'bo')
    plt.plot((0,fpr[i]),(tpr[i],tpr[i]), color='k', linestyle='dashed', linewidth=1, alpha=0.2)    
    plt.plot((fpr[i],fpr[i]),(0,tpr[i]), color='k', linestyle='dashed', linewidth=1, alpha=0.2)
    plt.text(fpr[i]-0.02 ,tpr[i]+0.02, 'threshold: %.2f'%(thresholds[i]))
plt.yticks(list(plt.xticks()[0]) + extray)
plt.xticks(list(plt.xticks()[0]) + extrax)
plt.show()
```


![png](output_25_0.png)


**AUC** - Area Under the Curve là diện tích nằm dưới ROC curve cũng là một tiêu chuẩn đánh giá mô hình, giá trị này càng cao thì mô hình càng tốt. 

Nếu thuộc lĩnh vực tài chính thì các bạn sẽ không lạ gì với chỉ số **GINI** - tiêu chuẩn để đo độ chính xác của mô hình credit scorecard.

Và chúng ta có thể tính GINI theo công thức đơn giản dưới đây:

**GINI = AUC * 2 - 1**


# Các phương pháp triển khai mô hình:

Sau khi chúng ta xây dựng được mô hình thì vấn đề triển khai thế nào cho dễ dàng hỗ trợ cho vận hành tốt nhất cũng là vấn đề quan trọng


### Bước 1:  Chuyển dải xác xuất về score:

Đầu tiên khi Chúng ta dùng phương thức predict_proba() để chấm điểm thì kết quả trả về sẽ là một dải xác xuất, ta hoàn toàn có thể dùng dải xác xuất này là điểm số để đánh giá chất lượng của từng trường hợp. 

Tuy nhiên con số xác xuất thì sẽ không được mỹ quan và thân thiện với các bộ phận vận hành vì vậy chúng ta có thể chuển dải xác xuất về dải điểm từ 0 đến 1000

Dữ liệu thường có phân phối lệch trái do số giá trị có class 0 chiếm áp đảo, cho nên điều quan trọng hơn hết là khi ta chuyển dải xác xuất sang dải score ta có thể tổ chức lại phân phối của dải điểm để gần với phân phối chuẩn.


```python
def prob2score(p=0.5 ,foo=4.0, bar=0.0115):
    p = min(probs[np.where(probs>0)])*1 if p<= 0 else p
    score  = (np.log(1/p  - 1 ) -foo)/-bar
    score = 0 if score <0 else score
    return int(score)
score = [prob2score(p, 10, 0.0165) for p in prob]
```


```python
from scipy.stats import norm

fig, axs = plt.subplots(ncols=2, figsize=(12,4))
for ax, y, title in zip(axs,[prob,score],['dải xác xuất','dải score']):
    sns.distplot(y,
                 fit=norm,
                 hist_kws={"alpha":0.2},
                 norm_hist=True,
                 bins = 40,
                 ax = ax)
    (mu, sigma) = norm.fit(y)
    ax.set_title('Phân phối '+title)
    ax.legend(['Normal dist. ($\mu=$ {:.2f} and $\sigma=$ {:.2f} )'.format(mu,sigma)])
```


![png](output_30_0.png)


**Phân phối của dải score cân xứng hơn hẳn, sẽ phù hợp cho ứng dụng, hỗ trợ vận hành hơn dải xác xuất.**


```python
def score_PN_rate(iter_n = 20):
    df_temp = pd.DataFrame({'score':score, 'y':y_test})
    for i in range(0, max(df_temp['score']), iter_n):
        df_temp.loc[df_temp.score.isin(range(i,i+iter_n)), 'score_r'] = i
    x1 = df_temp[df_temp.y==1].groupby(['score_r']).agg(len)[['y']]
    x0 = df_temp[df_temp.y==0].groupby(['score_r']).agg(len)[['y']]
    x = df_temp.groupby(['score_r']).agg(len)[['y']]
    x = x.merge(x1,how='left', on='score_r').merge(x0,how='left', on='score_r')
    x.columns = ['count', 'P','N']
    x['P'] = x['P']/x['count'] * 100
    x['N'] = x['N']/x['count'] * 100
    fig, ax = plt.subplots(figsize=(8,6))
    x[['P','N']].plot.bar(ax = ax)
    ax.set_ylabel('%')
    ax.set_title('Score Positive and Negative rate')
score_PN_rate()
```


![png](output_32_0.png)


### Bước 2: Chuyển dải score về các bin:

Tuy dải score đã đẹp rồi, nhưng ta vẫn cần khái quát chúng hơn nữa để có thể dễ dàng theo dõi performance dễ dàng hơn. 

Trường hợp dưới đây mình gon dải score vào 5 bin sao cho số lượng phần tử mỗi bin xấp xỉ nhau, từ đó ta có thể đễ dàng phân tích theo nhiều chiều hơn.


```python
nbin = 5
df_probs = pd.DataFrame({'score':score, 'y':y_test})
cuts = pd.qcut(score, nbin, precision=5).unique()
for i,cut in enumerate(cuts.categories):
    df_probs.loc[(df_probs.score > cut.left) &(df_probs.score <= cut.right),'bin'] = i+1
    df_probs.loc[(df_probs.score > cut.left) &(df_probs.score <= cut.right),'bin_value'] = cut
count_g = df_probs.groupby('bin').count()['y']
total = df_probs.groupby('bin').sum()['y']
df_range = pd.concat([count_g,total], axis = 1)
df_range.columns = ['total', 'positive']
df_range['%positive'] = df_range.positive *100/ df_range.total
df_range['interval'] = cuts.categories
```


```python
df_range
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
      <th>total</th>
      <th>positive</th>
      <th>%positive</th>
      <th>interval</th>
    </tr>
    <tr>
      <th>bin</th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>1.0</th>
      <td>619</td>
      <td>47.0</td>
      <td>7.592892</td>
      <td>(366.99999, 458.0]</td>
    </tr>
    <tr>
      <th>2.0</th>
      <td>595</td>
      <td>72.0</td>
      <td>12.100840</td>
      <td>(458.0, 484.0]</td>
    </tr>
    <tr>
      <th>3.0</th>
      <td>587</td>
      <td>86.0</td>
      <td>14.650767</td>
      <td>(484.0, 507.0]</td>
    </tr>
    <tr>
      <th>4.0</th>
      <td>602</td>
      <td>136.0</td>
      <td>22.591362</td>
      <td>(507.0, 553.0]</td>
    </tr>
    <tr>
      <th>5.0</th>
      <td>597</td>
      <td>288.0</td>
      <td>48.241206</td>
      <td>(553.0, 747.0]</td>
    </tr>
  </tbody>
</table>
</div>




```python
df_probs.head()
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
      <th>score</th>
      <th>y</th>
      <th>bin</th>
      <th>bin_value</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>2935</th>
      <td>470</td>
      <td>0.0</td>
      <td>2.0</td>
      <td>(458.0, 484.0]</td>
    </tr>
    <tr>
      <th>3182</th>
      <td>459</td>
      <td>0.0</td>
      <td>2.0</td>
      <td>(458.0, 484.0]</td>
    </tr>
    <tr>
      <th>2238</th>
      <td>466</td>
      <td>0.0</td>
      <td>2.0</td>
      <td>(458.0, 484.0]</td>
    </tr>
    <tr>
      <th>4786</th>
      <td>511</td>
      <td>0.0</td>
      <td>4.0</td>
      <td>(507.0, 553.0]</td>
    </tr>
    <tr>
      <th>8048</th>
      <td>490</td>
      <td>1.0</td>
      <td>3.0</td>
      <td>(484.0, 507.0]</td>
    </tr>
  </tbody>
</table>
</div>




```python
fig, axs = plt.subplots(ncols=2, figsize=(12,5))
sns.barplot(x=df_range.index, y="%positive", data=df_range,
            palette="Blues", hue="%positive", dodge=False, ax=axs[0])
axs[0].grid(which='major', axis = 'y', linestyle='--')
axs[0].set_xlabel('Bin')
axs[0].set_title("positive rate")
for i, v in zip(df_range.index, df_range['%positive']):
    axs[0].text(i-1.2, v,str(round(v,1))+ '%', fontweight='bold',fontsize = 8)
axs[0].get_legend().remove()
sns.boxplot(x="bin", y="score",linewidth=0.5,
            data=df_probs, ax=axs[1], palette= "Blues") 
axs[1].set_title('Boxplot Score by Bin')
axs[1].set_ylabel('Score')
axs[1].set_xlabel('Bin')
axs[1].grid(which='major', axis = 'y', linestyle='--',color = '#bebebe')
```


![png](output_37_0.png)


Với cách thức trên thì việc đưa mô hình vào vận hành là rất thuận tiện rồi. Bài kỳ này xin kết thúc tại đây. 

Kỳ sau mình sẽ nói về cách đánh giá lại hiệu quả ứng dụng mô hình và tối ưu vận hành qua mô hình nhân quả.

Mong các bạn đón xem.
