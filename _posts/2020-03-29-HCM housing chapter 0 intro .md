---
layout: post
title: HCM housing chapter 0
subtitle: Intro
tags: [HCM housing]
---


Bất động sản là một lĩnh vực mình rất hứng thú, đặc biệt mấy năm gần đây tình hình bất động sản có sự tăng trưởng cực lớn, thị trường đã bùng nổ vào năm 2019, sang năm 2020 thì đã có sự chững lại cùng với đại dịch Covid 19.

Thị trường biến động là thế nhưng chỉ ngồi nghe thì có lẽ chúng ta sẽ không bao giờ hiểu được chuyện gì đang diễn ra ngoài thị trường kia, bản thân tôi thì cũng không đủ tiền để trực tiếp tham gia thị trường vào lúc này, và sẽ thật đáng tiếc nếu bỏ qua gia đoạn đầy thách thức và cơ hội này. 

Nhưng vẫn còn hy vọng, data về các tin đăng rao bán bất động sản thì tràn ngập trên mạng, và may thay tôi cũng có chút kỹ năng để thu thập và xử lý chúng. Vì đó series **HCM housing** ra đời nhằm thỏa mãn niềm đam mê của bản thân và tìm ra các cơ hội đầu tư và cũng là một case study để thấy được data science có tính ứng dụng mạnh thế nào.



```python
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns
%matplotlib inline

import matplotlib as mpl
mpl.rc('axes', labelsize=8)
mpl.rc('xtick', labelsize=8)
mpl.rc('ytick', labelsize=8)
```


```python
df = pd.read_csv('data/housing29_03_20.csv', 
                 encoding='utf-16', 
                 converters={'Ngày đăng': pd.to_datetime, 
                            'Ngày hết hạn': pd.to_datetime},
                )
print(df.shape)

```

    (14390, 24)


## Bước 1 : Clearn data 1 chút

- Đầu tiên bỏ cột không dùng tới lúc này đi cho gọn ( lúc này chưa dùng thôi nhé)


```python
df.drop(['Loại tin rao','uptime','email','Mã tin đăng',
         'title','url','Địa chỉ','Hướng nhà','Hướng ban công'],
         axis=1, inplace=True)         
```

Đổi tên cột nghe cho tây tây (và dễ gọi)


```python
df.rename(columns = {'Loại hình tin đăng':'type',
                     'Ngày đăng': 'up_time', 
                     'Ngày hết hạn': 'end_time',
                     'Số tầng': 'floors',
                     'Số phòng ngủ': 'bedrooms',
                     'Số toilet': 'toilets',
                     'Mặt tiền': 'facade',
                     'Đường vào': 'road_wide',
                     'Nội thất': 'furniture',
                     }, 
          inplace=True)
          
```


```python
df.head(1).T
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
      <th>0</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>Loại tin rao</th>
      <td>Bán nhà riêng</td>
    </tr>
    <tr>
      <th>Địa chỉ</th>
      <td>Đường 13, Thủ Đức, Hồ Chí Minh</td>
    </tr>
    <tr>
      <th>Hướng nhà</th>
      <td>Đông-Bắc</td>
    </tr>
    <tr>
      <th>Số tầng</th>
      <td>1(tầng)</td>
    </tr>
    <tr>
      <th>email</th>
      <td>lehoakhanhhoa87@gmail.com</td>
    </tr>
    <tr>
      <th>title</th>
      <td>Bán nhà đường 13, Linh Xuân, Nhà 1 trệt 1 lửng...</td>
    </tr>
    <tr>
      <th>Mã tin đăng</th>
      <td>24908353</td>
    </tr>
    <tr>
      <th>Loại hình tin đăng</th>
      <td>Tin thường</td>
    </tr>
    <tr>
      <th>Ngày đăng</th>
      <td>2020-03-25 00:00:00</td>
    </tr>
    <tr>
      <th>Ngày hết hạn</th>
      <td>2020-01-04 00:00:00</td>
    </tr>
    <tr>
      <th>long</th>
      <td>106.756</td>
    </tr>
    <tr>
      <th>lat</th>
      <td>10.8533</td>
    </tr>
    <tr>
      <th>district</th>
      <td>Thủ Đức</td>
    </tr>
    <tr>
      <th>street</th>
      <td>Linh Xuân</td>
    </tr>
    <tr>
      <th>price</th>
      <td>2.75 tỷ</td>
    </tr>
    <tr>
      <th>area</th>
      <td>81 m²</td>
    </tr>
    <tr>
      <th>uptime</th>
      <td>25/03/2020</td>
    </tr>
    <tr>
      <th>url</th>
      <td>/ban-nha-rieng-duong-13-phuong-linh-xuan/13-1-...</td>
    </tr>
    <tr>
      <th>Mặt tiền</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Đường vào</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Số phòng ngủ</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Số toilet</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Nội thất</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Hướng ban công</th>
      <td>NaN</td>
    </tr>
  </tbody>
</table>
</div>


Xem thông tin Non-Null và kiểu dữ liệu:

```python
df.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 14390 entries, 0 to 14389
    Data columns (total 15 columns):
     #   Column     Non-Null Count  Dtype         
    ---  ------     --------------  -----         
     0   floors     9656 non-null   object        
     1   type       14390 non-null  object        
     2   up_time    14390 non-null  datetime64[ns]
     3   end_time   14390 non-null  datetime64[ns]
     4   long       14388 non-null  float64       
     5   lat        14388 non-null  float64       
     6   district   14390 non-null  object        
     7   street     14390 non-null  object        
     8   price      14390 non-null  object        
     9   area       14390 non-null  object        
     10  facade     6603 non-null   object        
     11  road_wide  7809 non-null   object        
     12  bedrooms   8261 non-null   object        
     13  toilets    6993 non-null   float64       
     14  furniture  2593 non-null   object        
    dtypes: datetime64[ns](2), float64(3), object(10)
    memory usage: 1.6+ MB

Đổi tên giá trị biến trong trường 'type':

```python
df['type'] = df['type'].map({'Tin thường': 'nomal',
                             'Tin Vip 3': 'v3',
                             'Tin Vip 2': 'v2',
                             'Tin Vip 1': 'v1',
                             'Tin Vip đặc biệt': 'vs'})
                             
```

- Tách giá price, area từ chuỗi:


```python
df['price_unit'] = [p.split(' ')[1] for p in df['price']]
df['price'] = [p.split(' ')[0] for p in df['price']]
df['area_unit'] = [p.split(' ')[1] for p in df['area']]
df['area'] = [p.split(' ')[0] for p in df['area']]
print(df['price_unit'].value_counts(), end='\n\n')
print(df['area_unit'].value_counts())

#np.unique(df['price_unit'], return_counts=True)

```

    tỷ          13522
    thuận         545
    triệu         255
    triệu/m²       68
    Name: price_unit, dtype: int64
    
    m²     14042
    xác      348
    Name: area_unit, dtype: int64


Chỉ lấy các record có 'price_unit là' 'tỷ' và 'area_unit' là 'm²'

```python
df = df[(df['price_unit'] == 'tỷ') & (df['area_unit'] == 'm²')]

```

Chuyển dữ liệu 'price' và 'area' mới xử lý về kiểu float để tính toán:

```python
df['price'] = df['price'].astype(float)
df['area'] = df['area'].astype(float)
df.describe()

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
      <th>long</th>
      <th>lat</th>
      <th>price</th>
      <th>area</th>
      <th>toilets</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>13223.000000</td>
      <td>13223.000000</td>
      <td>13225.000000</td>
      <td>13225.000000</td>
      <td>6370.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>106.671245</td>
      <td>10.811026</td>
      <td>10.253711</td>
      <td>88.636981</td>
      <td>3.586185</td>
    </tr>
    <tr>
      <th>std</th>
      <td>0.059644</td>
      <td>0.348298</td>
      <td>177.415904</td>
      <td>187.661826</td>
      <td>2.892462</td>
    </tr>
    <tr>
      <th>min</th>
      <td>105.852447</td>
      <td>10.387579</td>
      <td>1.000000</td>
      <td>8.000000</td>
      <td>1.000000</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>106.639569</td>
      <td>10.768930</td>
      <td>3.550000</td>
      <td>48.000000</td>
      <td>2.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>106.671258</td>
      <td>10.797014</td>
      <td>5.700000</td>
      <td>64.000000</td>
      <td>3.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>106.700338</td>
      <td>10.832499</td>
      <td>9.000000</td>
      <td>90.000000</td>
      <td>4.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>106.954798</td>
      <td>21.028949</td>
      <td>19800.000000</td>
      <td>12600.000000</td>
      <td>70.000000</td>
    </tr>
  </tbody>
</table>
</div>




```python
df['p_m2'] = df['price']/df['area']

```



- Tách giá trị số từ chuỗi các trường 'floors','bedrooms', 'facade', 'road_wide'


```python
converts = ['floors','bedrooms', 'facade', 'road_wide']
df[converts].head(3)

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
      <th>bedrooms</th>
      <th>facade</th>
      <th>road_wide</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1(tầng)</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>1</th>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2(tầng)</td>
      <td>3(phòng)</td>
      <td>4(m)</td>
      <td>6,50(m)</td>
    </tr>
  </tbody>
</table>
</div>




```python
df[converts].info()

```

    <class 'pandas.core.frame.DataFrame'>
    Int64Index: 13225 entries, 0 to 14389
    Data columns (total 4 columns):
     #   Column     Non-Null Count  Dtype 
    ---  ------     --------------  ----- 
     0   floors     8951 non-null   object
     1   bedrooms   7558 non-null   object
     2   facade     6118 non-null   object
     3   road_wide  7153 non-null   object
    dtypes: object(4)
    memory usage: 516.6+ KB

Nhận thấy giá trị số sẽ bao gồm các phần tử bắt đầu cho đến ký tự '(' trong chuỗi nên ta viết hàm xử lý như dưới:

```python
def find_number(s):
    if s != 'none':
        return float(s[: s.find('(')].replace(',','.'))
    else:
        return np.nan
    
for col in converts:
    df[col].fillna('none', inplace=True)
    df[col] = [find_number(s) for s in df[col]]
```


```python
df.head(1).T
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
      <th>0</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>Loại tin rao</th>
      <td>Bán nhà riêng</td>
    </tr>
    <tr>
      <th>Địa chỉ</th>
      <td>Đường 13, Thủ Đức, Hồ Chí Minh</td>
    </tr>
    <tr>
      <th>Hướng nhà</th>
      <td>Đông-Bắc</td>
    </tr>
    <tr>
      <th>Số tầng</th>
      <td>1(tầng)</td>
    </tr>
    <tr>
      <th>email</th>
      <td>lehoakhanhhoa87@gmail.com</td>
    </tr>
    <tr>
      <th>title</th>
      <td>Bán nhà đường 13, Linh Xuân, Nhà 1 trệt 1 lửng...</td>
    </tr>
    <tr>
      <th>Mã tin đăng</th>
      <td>24908353</td>
    </tr>
    <tr>
      <th>Loại hình tin đăng</th>
      <td>Tin thường</td>
    </tr>
    <tr>
      <th>Ngày đăng</th>
      <td>2020-03-25 00:00:00</td>
    </tr>
    <tr>
      <th>Ngày hết hạn</th>
      <td>2020-01-04 00:00:00</td>
    </tr>
    <tr>
      <th>long</th>
      <td>106.756</td>
    </tr>
    <tr>
      <th>lat</th>
      <td>10.8533</td>
    </tr>
    <tr>
      <th>district</th>
      <td>Thủ Đức</td>
    </tr>
    <tr>
      <th>street</th>
      <td>Linh Xuân</td>
    </tr>
    <tr>
      <th>price</th>
      <td>2.75 tỷ</td>
    </tr>
    <tr>
      <th>area</th>
      <td>81 m²</td>
    </tr>
    <tr>
      <th>uptime</th>
      <td>25/03/2020</td>
    </tr>
    <tr>
      <th>url</th>
      <td>/ban-nha-rieng-duong-13-phuong-linh-xuan/13-1-...</td>
    </tr>
    <tr>
      <th>Mặt tiền</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Đường vào</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Số phòng ngủ</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Số toilet</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Nội thất</th>
      <td>NaN</td>
    </tr>
    <tr>
      <th>Hướng ban công</th>
      <td>NaN</td>
    </tr>
  </tbody>
</table>
</div>



## Bước 2 : Biểu diễn dữ liệu
- Dữ liệu khá đa dạng nhưng mình chỉ quan tâm tới các diện tích < 200m2 và giá tiền < 100 tỷ:


```python
df = df[(df['area'] < 200) & (df['price'] < 100)]

```

Có 24 quận nên chia làm 4 dòng 6 cột vẽ cho đẹp

set : cols, rows = 4, 6


```python
cols, rows = 6,4

fig, axs = plt.subplots(nrows=rows, ncols=cols, figsize=(18,10))
fig.subplots_adjust(wspace=0.25, hspace=0.5)
label = df['district'].unique().reshape(rows, cols)

for r in range(len(axs)):
    for c in range(len(axs[r])):
        sns.regplot(x='area', 
                    y='price',
                    data=df[df['district']==label[r,c]],
                    lowess = True,
                    marker = ".",
                    scatter_kws={'alpha':0.3, 'color':'grey'},
                    ax = axs[r,c])
        axs[r,c].set_title(label[r,c])

```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/output_22_0.png)



```python
df = df[df['lat']<20]
```

Biểu đồ quan hệ giữa area và price theo từng quận :

```python
cols, rows = 6,4

fig, axs = plt.subplots(nrows=rows, ncols=cols, figsize=(18,10))
fig.subplots_adjust(wspace=0.25, hspace=0.5)
label = df['district'].unique().reshape(rows, cols)

cmap = sns.cubehelix_palette(dark=.1, light=.8, as_cmap=True)
for r in range(len(axs)):
    for c in range(len(axs[r])):
        sns.scatterplot(x='long', 
                        y='lat',
                        size="p_m2",
                        data=df[df['district']==label[r,c]],
                        hue="p_m2",
                        palette=cmap,
                        #marker = ".",
                        #scatter_kws={'alpha':0.3, 'color':'grey'},
                        ax = axs[r,c])
        axs[r,c].set_title(label[r,c])
        axs[r,c].get_legend().remove()
        
```


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/output_24_0.png)




Biểu đồ phân bổ price theo từng quận :

```python
df_choise =  df[~df['district'].isin(['Hóc Môn', 'Nhà Bè',
                                     'Bình Chánh','Cần Giờ', 
                                     'Củ Chi'])]
fig, ax = plt.subplots( figsize=(10,10))
sns.scatterplot(x='long', 
                y='lat',
                size="p_m2",
                hue ='p_m2',
                hue_order='district',
                #hue_norm='p_m2',
                sizes=(10, 100),
                palette=cmap,
                data=df_choise,
                )
for d in df_choise['district'].unique():
    ax.text(df[df['district'] == d]['long'].mean(), df[df['district'] == d]['lat'].mean(), d)
    
ax.get_legend().remove()
ax.set_title('Các quận nội thành')


```




    Text(0.5, 1.0, 'Các quận nội thành')




![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/output_25_1.png)



Tới đây thì dữ liệu cũng tàm tạm để xây dựng các mô hình dự đoán giá nhà rồi, và đó cũng sẽ là chủ để trong kỳ tới. 

Mời các bạn đón đọc !

