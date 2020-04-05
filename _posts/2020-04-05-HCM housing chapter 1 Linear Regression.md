Bài này mình sẽ nói thêm 1 chút về cách xử lý dữ liệu cũng như xây dựng mô hình dự đoán giá nhà cơ bản và rất đơn giản.

Ứng dụng:
    - Sử dụng mô hình để thẩm định một sảm phẩm BDS mới, sản phẩm đang có giá cao hay thấp so với thị trường. 
    Mô hình có tính tham khảo cao với cả nhà đầu tư cá nhân và các tổ chức. 

Let' go

## Load data:


```python
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns
import warnings
import matplotlib as mpl
warnings.filterwarnings("ignore", category=FutureWarning)


mpl.rc('axes', labelsize=8)
mpl.rc('xtick', labelsize=8)
mpl.rc('ytick', labelsize=8)
%matplotlib inline
```


```python
df = pd.read_csv('data/ban-nha-rieng-tp-hcm.csv', 
                 encoding='utf-16')
print(df.shape)
```

    (17737, 24)


## Bước 1 : Clean data

**Phần này xử lý dữ liệu giống trong kỳ trước:**

Chúng ta đã là được các việc sau:
    - bỏ 1 số trường không dùng
    - đổi tên trường
    - tách giá trị số từ chuỗi


```python
# bỏ 1 số trường không dùng
df.drop(['Loại tin rao', 'uptime', 'email', 'Mã tin đăng',
         'long', 'lat','Loại hình tin đăng', 'Ngày đăng', 'Ngày hết hạn',
         'title','url','Địa chỉ','Hướng nhà','Hướng ban công'],
         axis=1, inplace=True)

# đổi tên trường
df.rename(columns = {
                     'Số tầng': 'floors',
                     'Số phòng ngủ': 'bedrooms',
                     'Số toilet': 'toilets',
                     'Mặt tiền': 'facade',
                     'Đường vào': 'road_wide',
                     'Nội thất': 'furniture',
                     }, 
          inplace=True)

# tách giá trị số từ chuỗi
df['price_unit'] = [p.split(' ')[1] for p in df['price']]
df['price'] = [p.split(' ')[0] for p in df['price']]
df['area_unit'] = [p.split(' ')[1] for p in df['area']]
df['area'] = [p.split(' ')[0] for p in df['area']]

df = df[(df['price_unit'] == 'tỷ') & (df['area_unit'] == 'm²')]
df['price'] = df['price'].astype(float)
df['area'] = df['area'].astype(float)

#df['p_m2'] = df['price']*1000/df['area']

converts = ['floors','bedrooms', 'facade', 'road_wide']
def find_number(s):
    if s != 'none':
        return float(s[: s.find('(')].replace(',','.'))
    else:
        return np.nan
    
for col in converts:
    df[col].fillna('none', inplace=True)
    df[col] = [find_number(s) for s in df[col]]
    
df = df[(df['area'] < 200) & (df['price'] < 50)]

df = df[(df['facade'] < 50) & (df['toilets'] < 10) &  (df['road_wide'] < 50)]

df.reset_index(inplace=True, drop=True)
df.drop(['price_unit','area_unit'],
         axis=1, inplace=True)

df = df[~df['district'].isin(['Hóc Môn','Bình Chánh','Cần Giờ', 'Củ Chi'])]

```


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
      <th>floors</th>
      <th>district</th>
      <th>street</th>
      <th>price</th>
      <th>area</th>
      <th>facade</th>
      <th>road_wide</th>
      <th>bedrooms</th>
      <th>toilets</th>
      <th>furniture</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>3.50</td>
      <td>75.0</td>
      <td>4.0</td>
      <td>6.5</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>Full nội thất cơ bản</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>Không.</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>Cơ bản.</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.20</td>
      <td>35.0</td>
      <td>5.0</td>
      <td>4.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>4.45</td>
      <td>140.0</td>
      <td>5.0</td>
      <td>4.0</td>
      <td>9.0</td>
      <td>4.0</td>
      <td>NaN</td>
    </tr>
  </tbody>
</table>
</div>



### Xử lý thêm trường furniture

Nhưng vẫn còn 1 trường là 'furniture' chúng ta chưa xử lý, theo ý kiến cá nhân thì giá BDS cũng sẽ được tác động từ nội thất khá nhiều nên là chúng ta vẫn nên xử lý biến này !


```python
print('values :', len(df['furniture'].unique()), end='\n\n')
print(df[['furniture']].info(), end='\n')
print(df['furniture'].value_counts().head())
```

    values : 833
    
    <class 'pandas.core.frame.DataFrame'>
    Int64Index: 4600 entries, 0 to 4901
    Data columns (total 1 columns):
     #   Column     Non-Null Count  Dtype 
    ---  ------     --------------  ----- 
     0   furniture  1693 non-null   object
    dtypes: object(1)
    memory usage: 71.9+ KB
    None
    Cao cấp              56
    Cao cấp.             55
    Đầy đủ.              53
    Nội thất cao cấp.    48
    Đầy đủ               47
    Name: furniture, dtype: int64


Tuy nhiên có một vấn đề là dữ liệu kiểu nhập tự do nên khá khó phân tích, có đến 1283 giá trị nhập khác nhau trên 2723 giá trị không null

Nhận thấy rằng đa số các nhà có nột thất thì họ mới ghi vào phần 'furniture', do vậy chúng ta có thể tạo 1 trường dữ liệu để thể hiện là nhà có nột thất hay không.

Một cách tốt hơn nữa là chúng ta sẽ phân tích cấu trúc chuỗi và phân loại nội thất theo:

    - cao cấp
    - cơ bản
    - không
Cách này thì mình nghĩ sẽ giữ được nhiều thông tin hơn nên các bạn có cơ hội thì làm thử nhé, mình làm cơ bản cho nhanh đã


```python
df['furniture'].fillna(0, inplace=True)
df.loc[df['furniture'] != 0, 'furniture'] = 1
df['furniture'] = df['furniture'].astype(int)
```


```python
df['furniture'].head()
```




    0    1
    1    1
    2    1
    3    0
    4    0
    Name: furniture, dtype: int64



### Xử lý missing values


```python
missing = pd.concat(
    [df.isna().sum()*100/len(df), df.isna().sum()], 
    axis=1
)
missing.columns = ['%null', '#null']
missing = missing[missing['#null'] >0].sort_values('#null')
print( 'Missing values: ')
print(missing)
```

    Missing values: 
                 %null  #null
    bedrooms  0.478261     22
    floors    3.086957    142


Với các dữ liệu missing values thì chúng ta có khá nhiều cách xử lý. Nhưng quan trọng nhất vẫn là ta hiểu được tại sao dữ liệu đó lại missing. Trong trường hợp của chúng ta thì dữ liệu missing do yếu tố chủ quan của người đăng tin, quên nhập, không nhập dữ liệu vào.

Với dữ liệu numeric có một số cách để xử lý dữ liệu missing như thay bằng 1 giá trị số cụ thể như 0, -99, cũng có thể thay bằng giá trị mode, median , mean của trường dữ liệu, hoặc tạo 1 mô hình để dự đoán chính giá trị missing đó.

Vậy chúng ta hãy cùng thử nghiệm 1 số phương pháp trên để tìm ra phương án tốt nhất.

Bộ dữ liệu thay thế giá trị missing = 0:


```python
df0 = df.fillna(0)
df0.head(3)
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
      <th>floors</th>
      <th>district</th>
      <th>street</th>
      <th>price</th>
      <th>area</th>
      <th>facade</th>
      <th>road_wide</th>
      <th>bedrooms</th>
      <th>toilets</th>
      <th>furniture</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>3.50</td>
      <td>75.0</td>
      <td>4.0</td>
      <td>6.5</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
  </tbody>
</table>
</div>



Bộ dữ liệu thay thế giá trị missing = median:


```python
for col in missing.index:
    df[col].fillna(df[col].median(), inplace=True)
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
      <th>floors</th>
      <th>district</th>
      <th>street</th>
      <th>price</th>
      <th>area</th>
      <th>facade</th>
      <th>road_wide</th>
      <th>bedrooms</th>
      <th>toilets</th>
      <th>furniture</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>3.50</td>
      <td>75.0</td>
      <td>4.0</td>
      <td>6.5</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2.0</td>
      <td>Thủ Đức</td>
      <td>Linh Xuân</td>
      <td>1.87</td>
      <td>40.0</td>
      <td>4.0</td>
      <td>3.0</td>
      <td>2.0</td>
      <td>2.0</td>
      <td>1</td>
    </tr>
  </tbody>
</table>
</div>




```python
df = df[df['district'] == 'Thủ Đức']
df.drop(['district', 'street'], axis=1, inplace=True)
```

##  Bước 2 : Visualization


Xem phân phối của các biến:


```python
from scipy.stats import norm

cols, rows = 2,4
fig, axs = plt.subplots(nrows=rows, ncols=cols, figsize=(12,15))
fig.subplots_adjust(wspace=0.15, hspace=0.25)
cols = np.array(df.columns).reshape(rows, cols)
for r in range(len(axs)):
    for c in range(len(axs[r])):
        sns.distplot(df[cols[r,c]],
                    fit=norm,
                    ax = axs[r,c])
        (mu, sigma) = norm.fit(df[cols[r,c]])
        axs[r,c].legend(['Normal dist. ($\mu=$ {:.2f} and $\sigma=$ {:.2f} )'.format(mu, sigma)],loc='best')

```


![png](output_24_0.png)


**correlation matrix** cho ta thấy sự tương quan giữa các biến, 

- giá trị cao (max = 1) cho sự đồng biến 
- giá trị thấp (min =-1) cho nghịch biến 
- và bàng quang khi = 0.



```python
#correlation matrix
corrmat = df.corr()
f, ax = plt.subplots(figsize=(10, 8))  
sns.heatmap(corrmat, vmax=.8, annot=True);
```


![png](output_26_0.png)



```python
top_features = np.array(corrmat.index[abs(corrmat["price"])>0.5])
top_features
```




    array(['price', 'area', 'road_wide', 'bedrooms', 'toilets'], dtype=object)



Top các thuộc tính có tương quan cao với biến price:


```python
top_features = list(corrmat.index[abs(corrmat["price"])>0.5])
f, ax = plt.subplots(figsize=(5, 4))  
sns.heatmap(df[top_features].corr(), vmax=.8, annot=True)
top_features.remove('price')
```


![png](output_29_0.png)



```python
cols, rows = 2,2
fig, axs = plt.subplots(nrows=rows, ncols=cols, figsize=(12,8))
labels = np.array(top_features).reshape(rows, cols)
for r in range(len(axs)):
    for c in range(len(axs[r])):
        sns.regplot(x=labels[r,c], 
                y='price',
                data=df,
                lowess=True,
                marker=".",
                scatter_kws={'alpha':0.3, 'color':'grey'},
                ax=axs[r,c])
```


![png](output_30_0.png)



```python
from sklearn.model_selection import train_test_split

X = df.drop(['price'], axis=1)
y = df['price']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=15)
```

### Hồi quy tuyến tính với phương pháp OLS


```python
import statsmodels.api as sm      
X_train1 = sm.add_constant(X_train)
lm = sm.OLS(y_train, X_train1).fit()
print(lm.summary())
```

                                OLS Regression Results                            
    ==============================================================================
    Dep. Variable:                  price   R-squared:                       0.565
    Model:                            OLS   Adj. R-squared:                  0.558
    Method:                 Least Squares   F-statistic:                     88.16
    Date:                Sun, 05 Apr 2020   Prob (F-statistic):           7.54e-82
    Time:                        15:49:23   Log-Likelihood:                -795.61
    No. Observations:                 484   AIC:                             1607.
    Df Residuals:                     476   BIC:                             1641.
    Df Model:                           7                                         
    Covariance Type:            nonrobust                                         
    ==============================================================================
                     coef    std err          t      P>|t|      [0.025      0.975]
    ------------------------------------------------------------------------------
    const         -0.9891      0.338     -2.924      0.004      -1.654      -0.324
    floors         0.3321      0.095      3.501      0.001       0.146       0.518
    area           0.0257      0.002     10.916      0.000       0.021       0.030
    facade         0.1948      0.052      3.777      0.000       0.093       0.296
    road_wide      0.1615      0.022      7.280      0.000       0.118       0.205
    bedrooms      -0.0531      0.088     -0.607      0.544      -0.225       0.119
    toilets        0.4166      0.077      5.427      0.000       0.266       0.567
    furniture      0.1319      0.120      1.098      0.273      -0.104       0.368
    ==============================================================================
    Omnibus:                       10.497   Durbin-Watson:                   2.166
    Prob(Omnibus):                  0.005   Jarque-Bera (JB):               18.606
    Skew:                           0.022   Prob(JB):                     9.11e-05
    Kurtosis:                       3.960   Cond. No.                         458.
    ==============================================================================
    
    Warnings:
    [1] Standard Errors assume that the covariance matrix of the errors is correctly specified.



```python
ypred = lm.predict(sm.add_constant(X_test))
ytrain = lm.predict(sm.add_constant(X_train))
_, ax = plt.subplots(figsize=(12,6))
df_pred = pd.DataFrame({'y_pred':ypred, 'y_true': y_test})
df_pred.sort_values('y_true', inplace=True)
df_pred.reset_index(drop=True, inplace=True)
df_pred.plot(ax=ax)
plt.title('Kết quả dự đoán giá nhà theo mô hình hồi quy tuyến tính')
plt.show()
```


![png](output_34_0.png)


### Giải thích 1 số thuật ngữ thống kê:

1. **R-squared**: Độ giải thích biến phụ thuộc bởi các biến độc lâp

   R-squared = 0.565, 56.5% biến thiên của biến phụ thuộc(price) được giải thích bởi các biến độc lập, 43.5% còn lại nằm ngoài mô hình.


2. **Đa cộng tuyến**:  Xảy ra khi các biến độc lập có mối quan hệ tuyến tính cao (hệ số tương quan gần tới 1), biến không ảnh hưởng tới biến phụ thuộc.

    Có thể dùng P_value để tìm các biến bị đa cộng tuyến nếu P_value lớn hơn mức ý nghĩa thì biến đa cộng tuyến.
    Ở trường hợp của chúng ta biến bedrooms có P_value = 0.544, rất cao và có hiện tượng đa cộng tuyến


3. **Tự tương quan**: Quan điểm thống kê cổ điển giả định rằng quan hệ tương quan giữa các thành viên của chuỗi của các quan sát được sắp xếp theo thời gian hoặc không gian trong ngữ cảnh hồi qui không tồn tại trong các nhiễu ui.
    
    Kiểm định Durbin-Watson = 2.166 cho kết quả nằm trong khoảng (1,3) nhiễu sẽ không có sự tự tương quan.
    
    Nghe có vẻ hơi rắc rối nhưng hãy quan sát đồ thị dưới đây để thấy rõ vấn đề:
    


```python
time = np.arange(0, 15, 0.1)
values1 = np.sin(time)
values2 = np.random.uniform(-0.2, 0.2, len(time))
values3 = np.sort(values2)
fig, axs = plt.subplots(nrows=1,ncols=3, figsize=(12,3))
for ax, value in zip(axs,[values1,values3,values2]):
    ax.set_ylim(-1,1)
    ax.axhline(y=0, color='k')
    ax.set_xlabel('time')
    ax.scatter(time, value)
axs[0].set_title('Có tương quan giữa các nhiễu')                 
axs[1].set_title('Có tương quan giữa các nhiễu')
axs[2].set_title('Không có tương quan giữa các nhiễu')
plt.show()
```


![png](output_36_0.png)


  4. **RMSE**:  Root Mean Square Error
  
  Là chênh lệch giữa giá trị thực và giá trị dự báo nhằm đánh giá chất lượng hay sự phù hợp của mô hình dự báo.


```python
print('rmse on test:', rmse(y_test.values, ypred.values))
print('rmse on train:', rmse(y_train.values, ytrain.values))
```

    rmse on test: 1.2007801545340961
    rmse on train: 1.2521709451245022


Kỳ này chúng ta đã nói về cách xây dựng mô hình hồi quy tuyến tính để dự báo giá nhà. Tuy mô hình còn khá đơn giản và chúng ta cần phải tinh chỉnh rất nhiều thứ để có một mô hình tốt hơn, điều đó cần thời gian và sự nghiên cứu nghiêm túc. 

Theo mình data science là môn khoa học thực nghiệm, do vậy chúng ta phải kiên trì để giống như Edison - tìm ra chiếc bóng đèn của mình.

Mời các bạn đón đọc kỳ sau, chúng ta sẽ nói về timeseries, một chủ đề khá thú vị đó !
