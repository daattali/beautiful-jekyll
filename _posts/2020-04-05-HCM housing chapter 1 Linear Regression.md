---
layout: post
title: House price prediction
subtitle: HCM housing chapter 1 
tags: [HCM-housing]
thumbnail-img: /assets/img/chapter_1_house_prices_predict_4.png
---

Bài này mình sẽ nói thêm 1 chút về cách xử lý dữ liệu cũng như xây dựng mô hình dự đoán giá nhà cơ bản và rất đơn giản.

Ứng dụng:
    - Sử dụng mô hình để thẩm định một sảm phẩm BDS mới, sản phẩm đang có giá cao hay thấp so với thị trường. 
    Mô hình có tính tham khảo cao với cả nhà đầu tư cá nhân và các tổ chức. 

Let' go



## Bước 1 : Clean data

**Phần này xử lý dữ liệu khá giống trong kỳ trước:**

Chúng ta đã làm được các việc sau:

- bỏ 1 số trường không dùng
- đổi tên trường
- tách giá trị số từ chuỗi



<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }
    table {
      font-size: 12px;
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


Tuy nhiên có một vấn đề là dữ liệu kiểu nhập tự do nên khá khó phân tích, có đến 833 giá trị nhập khác nhau trên 1693 giá trị không null

Nhận thấy rằng đa số các nhà có nột thất thì họ mới ghi vào phần 'furniture', do vậy chúng ta có thể tạo 1 trường dữ liệu để thể hiện là nhà có nột thất hay không.

Một cách tốt hơn nữa là chúng ta sẽ phân tích cấu trúc chuỗi và phân loại nội thất theo:

- cao cấp
- cơ bản
- không

Cách này thì mình nghĩ sẽ giữ được nhiều thông tin hơn nên các bạn có cơ hội thì làm thử nhé, mình làm cơ bản cho nhanh đã


    0    1
    1    1
    2    1
    3    0
    4    0
    Name: furniture, dtype: int64



### Xử lý missing values



    Missing values: 
                 %null  #null
    bedrooms  0.478261     22
    floors    3.086957    142


Với các dữ liệu missing values thì chúng ta có khá nhiều cách xử lý. Nhưng quan trọng nhất vẫn là ta hiểu được tại sao dữ liệu đó lại missing. Trong trường hợp của chúng ta thì dữ liệu missing do yếu tố chủ quan của người đăng tin, quên nhập, không nhập dữ liệu vào.

Với dữ liệu numeric có một số cách để xử lý dữ liệu missing như thay bằng 1 giá trị số cụ thể như 0, -99, cũng có thể thay bằng giá trị mode, median , mean của trường dữ liệu, hoặc tạo 1 mô hình để dự đoán chính giá trị missing đó.

Vậy chúng ta hãy cùng thử nghiệm 1 số phương pháp trên để tìm ra phương án tốt nhất.

Bộ dữ liệu thay thế giá trị missing = 0:



<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }
    table {
      font-size: 12px;
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

<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }
    table {
      font-size: 12px;
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





##  Bước 2 : Visualization


Xem phân phối của các biến:

<img src="/assets/img/chapter_1_house_prices_predict_1.png" />


**correlation matrix** cho ta thấy sự tương quan giữa các biến, 

- giá trị cao (max = 1) cho sự đồng biến 
- giá trị thấp (min =-1) cho nghịch biến 
- và bàng quan khi = 0.

<img src="/assets/img/chapter_1_house_prices_predict_2.png" />

    array(['price', 'area', 'road_wide', 'bedrooms', 'toilets'], dtype=object)

Top các thuộc tính có tương quan cao với biến price:

<img src="/assets/img/chapter_1_house_prices_predict_3.png" />

Xem qua quan hệ tuyến tính giữa các biến độc lập và biến phụ thuộc:

<img src="/assets/img/chapter_1_house_prices_predict_4.png" />

### Hồi quy tuyến tính với phương pháp OLS

<table class="simpletable">
<caption>OLS Regression Results</caption>
<tr>
  <th>Dep. Variable:</th>          <td>price</td>      <th>  R-squared:         </th> <td>   0.565</td>
</tr>
<tr>
  <th>Model:</th>                   <td>OLS</td>       <th>  Adj. R-squared:    </th> <td>   0.558</td>
</tr>
<tr>
  <th>Method:</th>             <td>Least Squares</td>  <th>  F-statistic:       </th> <td>   88.16</td>
</tr>
<tr>
  <th>Date:</th>             <td>Sun, 05 Apr 2020</td> <th>  Prob (F-statistic):</th> <td>7.54e-82</td>
</tr>
<tr>
  <th>Time:</th>                 <td>16:03:41</td>     <th>  Log-Likelihood:    </th> <td> -795.61</td>
</tr>
<tr>
  <th>No. Observations:</th>      <td>   484</td>      <th>  AIC:               </th> <td>   1607.</td>
</tr>
<tr>
  <th>Df Residuals:</th>          <td>   476</td>      <th>  BIC:               </th> <td>   1641.</td>
</tr>
<tr>
  <th>Df Model:</th>              <td>     7</td>      <th>                     </th>     <td> </td>   
</tr>
<tr>
  <th>Covariance Type:</th>      <td>nonrobust</td>    <th>                     </th>     <td> </td>   
</tr>
</table>

<table class="simpletable">
<tr>
      <td></td>         <th>coef</th>     <th>std err</th>      <th>t</th>      <th>P>|t|</th>  <th>[0.025</th>    <th>0.975]</th>  
</tr>
<tr>
  <th>const</th>     <td>   -0.9891</td> <td>    0.338</td> <td>   -2.924</td> <td> 0.004</td> <td>   -1.654</td> <td>   -0.324</td>
</tr>
<tr>
  <th>floors</th>    <td>    0.3321</td> <td>    0.095</td> <td>    3.501</td> <td> 0.001</td> <td>    0.146</td> <td>    0.518</td>
</tr>
<tr>
  <th>area</th>      <td>    0.0257</td> <td>    0.002</td> <td>   10.916</td> <td> 0.000</td> <td>    0.021</td> <td>    0.030</td>
</tr>
<tr>
  <th>facade</th>    <td>    0.1948</td> <td>    0.052</td> <td>    3.777</td> <td> 0.000</td> <td>    0.093</td> <td>    0.296</td>
</tr>
<tr>
  <th>road_wide</th> <td>    0.1615</td> <td>    0.022</td> <td>    7.280</td> <td> 0.000</td> <td>    0.118</td> <td>    0.205</td>
</tr>
<tr>
  <th>bedrooms</th>  <td>   -0.0531</td> <td>    0.088</td> <td>   -0.607</td> <td> 0.544</td> <td>   -0.225</td> <td>    0.119</td>
</tr>
<tr>
  <th>toilets</th>   <td>    0.4166</td> <td>    0.077</td> <td>    5.427</td> <td> 0.000</td> <td>    0.266</td> <td>    0.567</td>
</tr>
<tr>
  <th>furniture</th> <td>    0.1319</td> <td>    0.120</td> <td>    1.098</td> <td> 0.273</td> <td>   -0.104</td> <td>    0.368</td>
</tr>
</table>

<table class="simpletable">
<tr>
  <th>Omnibus:</th>       <td>10.497</td> <th>  Durbin-Watson:     </th> <td>   2.166</td>
</tr>
<tr>
  <th>Prob(Omnibus):</th> <td> 0.005</td> <th>  Jarque-Bera (JB):  </th> <td>  18.606</td>
</tr>
<tr>
  <th>Skew:</th>          <td> 0.022</td> <th>  Prob(JB):          </th> <td>9.11e-05</td>
</tr>
<tr>
  <th>Kurtosis:</th>      <td> 3.960</td> <th>  Cond. No.          </th> <td>    458.</td>
</tr>
</table>

<img src="/assets/img/chapter_1_house_prices_predict_5.png" />

### Giải thích 1 số thuật ngữ thống kê:

1. **R-squared**: Độ giải thích biến phụ thuộc bởi các biến độc lâp

   R-squared = 0.565, 56.5% biến thiên của biến phụ thuộc(price) được giải thích bởi các biến độc lập, 43.5% còn lại nằm ngoài mô hình.


2. **Đa cộng tuyến**:  Xảy ra khi các biến độc lập có mối quan hệ tuyến tính cao (hệ số tương quan gần tới 1), biến không ảnh hưởng tới biến phụ thuộc.

    Có thể dùng P_value để tìm các biến bị đa cộng tuyến nếu P_value lớn hơn mức ý nghĩa thì biến đa cộng tuyến.
    Ở trường hợp của chúng ta biến bedrooms có P_value = 0.544, rất cao và có hiện tượng đa cộng tuyến


3. **Tự tương quan**: Quan điểm thống kê cổ điển giả định rằng quan hệ tương quan giữa các thành viên của chuỗi của các quan sát được sắp xếp theo thời gian hoặc không gian trong ngữ cảnh hồi qui không tồn tại trong các nhiễu ui.
    
    Kiểm định Durbin-Watson = 2.166 cho kết quả nằm trong khoảng (1,3) nhiễu sẽ không có sự tự tương quan.
    
    Nghe có vẻ hơi rắc rối nhưng hãy quan sát đồ thị dưới đây để thấy rõ vấn đề:
    



<img src="/assets/img/chapter_1_house_prices_predict_6.png" />

  4. **RMSE**:  Root Mean Square Error
  
  Là chênh lệch giữa giá trị thực và giá trị dự báo nhằm đánh giá chất lượng hay sự phù hợp của mô hình dự báo.


    rmse on test: 1.2007801545340961
    rmse on train: 1.2521709451245022


Kỳ này chúng ta đã nói về cách xây dựng mô hình hồi quy tuyến tính để dự báo giá nhà. Tuy mô hình còn khá đơn giản và chúng ta cần phải tinh chỉnh rất nhiều thứ để có một mô hình tốt hơn, điều đó cần thời gian và sự nghiên cứu nghiêm túc. 

Theo mình data science là môn khoa học thực nghiệm, do vậy chúng ta phải kiên trì để giống như Edison - tìm ra chiếc bóng đèn của mình.

Mời các bạn đón đọc kỳ sau, chúng ta sẽ nói về timeseries, một chủ đề khá thú vị đó !
