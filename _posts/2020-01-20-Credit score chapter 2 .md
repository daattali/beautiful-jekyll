---
layout: post
title: Scorecard with Machine learning 
subtitle: Credit Scorecard chapter 2
tags: [Credit Scorecard]
thumbnail-img: /assets/img/credit_scorecard_01.png
---

Bài viết thứ 2 nằm trong series về **Credit Scorecard** trong các tổ chức tín dụng. Trong bài này chúng ta cùng tìm hiểu cách ứng dụng các mô hình Machine trong chấm điểm tín dụng cũng như tìm ra mô hình tối ưu nhất. 

**Credit Scorecard** với mục tiêu là chấm điểm và phân loại khách hàng, cho phép đưa ra quyết định về chính sách can thiệp nhằm tối ưu hóa hiệu quả kinh doanh.

Thí dụ minh họa là một dữ liệu về thông tin cơ bản cũng như lịch sử hành vi của khách hàng thuộc nhóm trễ hạn nợ 2 tháng (B2_BOM).

Bài toán được giải quyết dựa trên dữ liệu của 10000 khách hàng, bao gồm nhiều thông tin, các thông tin đã được biến đổi cũng như thay đổi tên trường để đảm bảo lý do bảo mật.

Biến output : **label**
- label = 1: khách hàng mục tiêu
- label = 0: khách hàng bình thường


Mục tiêu gồm : 
1. Các phương pháp chuyển dạng, chuẩn hóa dữ liệu
2. Giới thiệu các thuật toán machine learning cơ bản 
3. Turning model sử dụng GridSearchCV và tìm ra mô hình tối ưu

_______________________________



## Bước 1: Data preprocessing

Do dữ liệu đã được clean nên chúng ta đến thẳng bước tranform data để chuẩn bị training model machine learning

### OneHotEncoder

Kỹ thuật onehot (hay dummy) là kỹ thuật chuyển dạng dữ liệu từ dạng **chuỗi** sang dạng bool mà vẫn giữ nguyên được giá trị thông tin của dữ liệu. Với phương thức là với mỗi giá trị trong trường dữ liệu cũ ta tạo một trường dữ liệu mới thể hiện rằng dữ liệu tại đó có bằng giá trị đó không. 

Chúng ta sẽ thấy rõ nó hoạt động thế nào sau bước dưới đây:

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





data sau khi OneHotEncoder:





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





### MinMaxScaler

Là kỹ thuật chuẩn hóa dữ liệu phổ biến cho các dữ liệu **Numeric**. Với cơ chế là đưa dữ liệu về 1 thang đo mới 
vd: *MinMaxScaler(feature_range=(-1,1))*
   - -1 : giá trị nhỏ nhất 
   -   1 : giá trị lớn nhất 

**Tại sao chuẩn hóa dữ liệu lại cẩn thiết ?** 

Vì khi tính toán với nhiều trường dữ liệu khác nhau thì sẽ có các phép toán kiểu như : **age** + **loan** 
Giả sử khách hàng 45 tuổi và vay 50 triệu thì việc lấy số 45 tuổi + 50 triệu có sự bất đồng lớn về thang đo tính toán

Do vậy ta cần đưa **age** và **loan** về cùng thang đo (-1,1) để đạt được hiệu quả cao khi traing model



## Bước 2 : MODEL

Sau khi dữ liệu đã sạch sẽ thơm tho thì chún ta có thể đem đi xào nấu thỏa thích với đủ thể loại thuật toán machine learning

Việc đầu tiên chúng ta cần làm là chia tệp dữ liệu thành các bộ traing_set và test_set:



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
         

**Thực hiện GridSearchCV cho từng thuật toán và so sánh kết quả theo AUC**


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

<img src="/assets/img/credit_scorecard_01.png" />

**Model RF: RandomForestClassifier() cho kết quả AUC cao nhất : 0.77**

do vậy ta dùng bộ best params của mô hình của RF để train mô hình dự báo chính của chúng ta.


    RandomForestClassifier(bootstrap=True, class_weight=None, criterion='entropy',
                           max_depth=12, max_features='log2', max_leaf_nodes=None,
                           min_impurity_decrease=0.0, min_impurity_split=None,
                           min_samples_leaf=1, min_samples_split=2,
                           min_weight_fraction_leaf=0.0, n_estimators=200,
                           n_jobs=None, oob_score=False, random_state=None,
                           verbose=0, warm_start=False)


**Thêm các metrix để đánh giá mô hình:**

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

<img src="/assets/img/credit_scorecard_02.png" />

**Với mô hình RandomForestClassifier, chúng ta có thể lấy được độ quan trọng của từng biến tới mô hình:**

<img src="/assets/img/credit_scorecard_03.png" />

Vậy là tới đây chúng ta đã biết cách để tìm ra mô hình machine learning tối ưu để giải quyết vấn đề của mình, bài cũng khá dài nên chapter này sẽ tạm dừng tại đây.

Kỳ tới chúng ta sẽ đi sâu hơn vào các ứng dụng của machine learning cũng như cách khai thác chúng !
