---
layout: post
title: Credit scorecard chapter 1
subtitle: Logistic regression model
tags: [credit scorecard]
---


# Logistic regression với WOE

**Credit Scorecard** với mục tiêu là chấm điểm và phân loại khách hàng, cho phép đưa ra quyết định về chính sách can thiệp nhằm tối ưu hóa hiệu quả kinh doanh.

Thí dụ minh họa là một dữ liệu về thông tin cơ bản cũng như lịch sử hành vi của khách hàng thuộc nhóm trễ hạn nợ 2 tháng (B2_BOM).

Bài toán được giải quyết dựa trên dữ liệu của 10000 khách hàng, bao gồm nhiều thông tin, các thông tin đã được biến đổi cũng như thay đổi tên trường để đảm bảo lý do bảo mật.

Biến output : **label**
- label = 1: khách hàng mục tiêu
- label = 0: khách hàng bình thường


Mục tiêu bài viết : 
1. Trực quan hóa dữ liệu với seaborn
2. Giới thiệu thuật toán Logistic regression với WOE


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



## Biểu đồ trực quan hóa dữ liệu 

Cách để chúng ta hiểu dữ liệu nhanh nhất đó chính là qua hình ảnh 

Dưới đây mình chủ yếu sử dụng thư viện **seaborn** vì nó khá thuận tiện mà lại rất đẹp nữa

Biểu đồ histogram để thấy được tần suất của dữ liệu:


```python
sns.set_palette("pastel")
sns.set_style('ticks')

df.hist(figsize=(15,12), bins=20, grid=False, ylabelsize= 7, xlabelsize=7)
plt.show()
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_0.png)



Biến phân loại:


```python
sns.countplot(data = df, x = 'label', palette= 'hls' )
plt.show()
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_1.png)


Biểu đồ pairplot để thấy được mối quan hệ của dữ liệu:


```python
plot_cols = ["field0", "field1", "field27", "field15"]
sns.pairplot(df[plot_cols+['label']],
             vars = plot_cols,
             hue='label', diag_kind="kde",
             height=2.5);
```



![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_2.png)



Quan sát thêm sự mối quan hệ giữa các biến với sns.jointplot:


```python
sns.jointplot("field0", "field1", data=df, kind='hex')
```






![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_3.png)



factor "field35" theo "field14" và "label":


```python
sns.factorplot("field35", "field14", "label", data=df, kind="violin")
```








![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_4.png)



## Giới thiệu :


Sau khi nhìn qua dữ liệu chắc chúng ta ai cũng muốn hiểu sâu hơn về dữ liệu cũng như khai thác tri thức từ chúng. Một phương pháp thống kê phổ biến dễ hiểu và cũng rất hiệu quả cho các bài toán phân lớp nhị phân thường được nhắc tới đó chính là Logistic regression. 

Mô hình hồi quy logistic là một trong những kỹ thuật thống kê được sử dụng phổ biến nhất để giải quyết vấn đề phân loại nhị phân. Nó được chấp nhận trong hầu hết các lĩnh vực. Hai khái niệm này - Weight of Evidence (WOE) và Information Value (IV) phát triển từ cùng một kỹ thuật hồi quy logistic. Hai thuật ngữ này đã tồn tại trong thế giới chấm điểm tín dụng trong hơn 4-5 thập kỷ. Chúng đã được sử dụng làm chuẩn để sàng lọc các biến trong các dự án mô hình rủi ro tín dụng như xác suất vỡ nợ. Chúng giúp khám phá dữ liệu và các biến. Nó cũng được sử dụng trong dự án phân tích tiếp thị như mô hình phân khúc khách hàng, v.v.


## mô hình Logistic regression :

Với cơ chế phân lớp đễ hiểu và các hàm kích hoạt cơ bản (activation) như sigmoid thì chúng ta có thể khai thác được rất nhiều từ dữ liệu

![image.png](https://miro.medium.com/max/1280/0*gKOV65tvGfY8SMem.png)

**Hàm sigmoid:**

\sigma(x) = \frac{1}{1+e^{-x}}


Về chi tiết cụ thể về cơ chế hoạt động của Logistic regression và hàm activation sigmoid thì mời các bạn các bạn đón đọc trang web rất uy tín dưới đây



<a href="https://machinelearningcoban.com/2017/01/27/logisticregression/">machinelearningcoban.com</a>

## Weight of Evidence(WOE)


**WOE = In(% of non-events / % of events)**

WOE : Trọng số cho biết sức mạnh dự đoán của một biến độc lập liên quan đến biến phụ thuộc. Giúp chuyển đổi một biến độc lập liên tục thành một tập hợp các nhóm hoặc bin dựa trên sự giống nhau của phân phối biến phụ thuộc.


## Information Value(IV):

**IV = ∑ (% of non-events - % of events) * WOE**


IV là một trong những kỹ thuật hữu ích nhất để chọn các biến quan trọng trong mô hình dự đoán. Nó giúp xếp hạng các biến trên cơ sở tầm quan trọng của chúng.

Các bạn có thể tham khảo thêm về WOE và IV qua các bài viết dưới đây 

<a href="https://medium.com/@sundarstyles89/weight-of-evidence-and-information-value-using-python-6f05072e83eb">medium.com</a>
<a href="https://www.kaggle.com/pavansanagapati/weight-of-evidence-woe-information-value-iv">kaggle.com</a>

-----------------------------

## Code nào :

Lý thuyết vậy là nhiều rồi, chắc đọc cũng chán ngấy cả người. Vậy chúng ta cùng thực hành chút cho nóng người nào. 

Về phương pháp biến đổi WOE thì có rất nhiều, mình cũng tự custom module để tính woe để theo ý mình nhưng cũng cần kết hợp với các thư viện có sẵn để đạt kết quả tốt nhât:

Thư viện **scorecardpy** được chuyển đổi từ thư viện scorecard từ R qua python rất tiện lợi cho chúng ta


```python
import scorecardpy as sc
from sklearn.linear_model import LogisticRegression
```





```python
df.isna().sum()
dt_s = df.drop(['field35','field38'], axis=1).copy()


y_label = 'label'
#dt_s  = dt_s[list(clf_info['VAR_NAME'])+ [y_label]]


# breaking dt into train and test
train, test = sc.split_df(dt_s, y_label ,seed=1).values()

# woe binning ------
bins = sc.woebin(dt_s, y=y_label)
#---------------
# sc.woebin_plot(bins)
# converting train and test into woe values
train_woe = sc.woebin_ply(train, bins)  
test_woe = sc.woebin_ply(test, bins)

y_train = train_woe.loc[:,y_label]
X_train = train_woe.loc[:,train_woe.columns != y_label]
y_test = test_woe.loc[:,y_label]
X_test = test_woe.loc[:,train_woe.columns != y_label]

# ===================================================
# --- logistic regression ------
# ===================================================
lr = LogisticRegression(n_jobs=-1)

lr.fit(X_train, y_train)
# score ------

card = sc.scorecard(bins, lr, X_train.columns,points0=150,pdo=-120)
# credit score
train_score = sc.scorecard_ply(train, card, print_step=0)
test_score = sc.scorecard_ply(test, card, print_step=0)

```

    [INFO] creating woe binning ...
    [INFO] converting into woe values ...
    [INFO] converting into woe values ...
    


```python
X_train.columns
```




Index(['field16', 'field36', 'field34_woe', 'field31_woe', 'field18_woe',
       'field2_woe', 'field40_woe', 'field30_woe', 'field0_woe', 'field27_woe',
       'field7_woe', 'field17_woe', 'field29_woe', 'field32_woe',
       'field14_woe', 'field13_woe', 'field25_woe', 'field9_woe', 'field8_woe',
       'field5_woe', 'field3_woe', 'field12_woe', 'field39_woe', 'field10_woe',
       'field20_woe', 'field21_woe', 'field22_woe', 'field1_woe',
       'field37_woe', 'field11_woe', 'field15_woe', 'field4_woe',
       'field19_woe', 'field23_woe', 'field24_woe', 'field26_woe',
       'field28_woe', 'field6_woe', 'field33_woe'],
      dtype='object')




```python
# predicted proability
train_pred = lr.predict_proba(X_train)[:,1]
test_pred = lr.predict_proba(X_test)[:,1]

# performance ks & roc ------
train_perf = sc.perf_eva(y_train, train_pred, title = "train")
test_perf = sc.perf_eva(y_test, test_pred, title = "test")

# score ------
card = sc.scorecard(bins, lr, X_train.columns)
# credit score
train_score = sc.scorecard_ply(train, card, print_step=0)
test_score = sc.scorecard_ply(test, card, print_step=0)

# psi
sc.perf_psi(
  score = {'train':train_score, 'test':test_score},
  label = {'train':y_train, 'test':y_test}
)
```



![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_5.png)





![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_6.png)





![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_7.png)






{'psi':   variable      PSI
 0    score  0.00548, 'pic': {'score': <Figure size 432x288 with 2 Axes>}}




```python
IV = {'VAR_NAME':[],'IV':[]}
for col in list(bins.keys()): 
    IV['VAR_NAME'].append(col)
    IV['IV'].append(bins[col]['total_iv'].iloc[0])
IV = pd.DataFrame(IV["IV"], index = IV['VAR_NAME'],columns=["IV"])
IV.sort_values("IV",inplace = True) 
IV = IV[IV.IV >= 0.02]
fig, ax = plt.subplots(figsize = (8,4),dpi = 100 )
IV.plot.barh(ax = ax)
plt.show()
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_8.png)


Vậy là chúng  ta đã đi được khá nhiều kiến thức. 

Ở kỳ sau chúng ta sẽ áp dụng nhiều phương pháp và mô hình machine learning hiện đại vào trong bài toán credit scorecard.
