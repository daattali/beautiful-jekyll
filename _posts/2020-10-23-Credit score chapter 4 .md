---
layout: post
title: Explain the Scorecard Model
subtitle: Credit Scorecard chapter 4
tags: [Credit Scorecard]
---


## 1 Tại sao phải diễn giải mô hình Machine learning ?


Lê Ngọc Khả Nhi - một data scientist mà tôi ngưỡng mộ đã từng nói : 

"Một mô hình chính xác dĩ nhiên là tốt, nhưng chưa đủ. Độ chính xác của mô hình là tiêu chí được nhắm tới bởi hầu hết data scientist, tuy nhiên, tính chính xác không đồng nghĩa với tính hiệu quả. "

Thật vậy trong quá trình đưa mô hình Scorecard vào với vận hành tại CS&A, tự bản thấy được còn có rất nhiều vấn đề cần được giải quyết ! 


Cho đến thời điểm hiện tại, mô hình Machine learning đang được áp dụng để xây dựng Scorecard đã và đang cho những dự đoán rất chính xác về kết quả thu hồi nợ. Tuy nhiên khi đưa vào vận hành thì không ít người bắt đầu hoài nghi về kết quả dự đoán của mô hình, bao gồm những người vận hành có nhiều kinh nghiệm và một số chuyên viên phân tích thiếu kỹ năng. 

Họ bắt đầu đặt ra các câu hỏi hoài nghi : 

1. Tại sao một số trường hợp có thanh toán vào tháng trước nhưng vẫn được phân loại xấu (bin 8,9,10) ?
2. Tại sao một số trường hợp mọi yếu tố đều giống nhau nhưng chỉ vì có số POS thấp hơn mà hợp đồng bị phân loại kém hẳn ?

Thời gian gần đây đã bắt đầu có những ý kiến hoài nghi, thậm chí cảnh báo về phong trào sử dụng Big data và Machine learning vào quá trình thu nợ. Một trong những luận điểm mà các bên phản đối đưa ra, đó là hầu hết những mô hình có nội dung không thể giải thích được. Khi họ không thể hiểu được cơ chế đằng sau kết quả, họ không thể tin cậy vào bản thân kết qủa đó, trong khi kết quả dự báo đôi khi ảnh hưởng rất nghiêm trọng đến kết quả thu nợ : thí dụ dự báo case xấu sẽ khiến nhân viên có tâm lý muốn bỏ !

Và cũng có vẻ bất công khi chúng ta đặt Target cao hơn cho 1 nhân viên nào đó vì một mô hình Machine learning đã dự báo rằng với danh mục của bạn thì phải đạt được con số như vậy. Nó cũng giống như một bệnh nhân đi khám và được bác sĩ giải thích như sau : "Bà có 99.5% nguy cơ bi ung thư, vì một mô hình Neural network đã quyết định như vậy". 


## 2 Giải thích mô hình không đơn giản


<img src="(https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_0.png" width="200" text-align="center"/>

Trong Machine learning, có một lời nguyền tai ác, đó là : "Tính tường minh của mô hình tỉ lệ nghịch với tính chính xác", mô hình càng chính xác thì càng bí hiểm. Sự phức tạp đến từ bản chất của algorithm, số lượng input features hoặc cả 2. Thời đại Big Data và IOT đã cưỡng ép chúng ta phải lựa chọn những algorithm phức tạp nhất, vì những mô hình tuyến tính không có cách nào xử lý được lượng data lớn cỡ đó.

Trong sơ đồ trên, những mô hình chính xác nhất lại chính là những mô hình bí hiểm nhất, bao gồm: Random Forest, GBM, Deep neural network, SVM… Chúng trở thành những hộp đen, hay mô hình "Bất khả Tri".

Thật không may, các mô hình chính để xây dụng cho Scorecard lại là Random Forest và Deep learning, việc giải thích chúng đã khó lại càng khó. 

Sơ đồ sau đây tóm tắt quy trình Suy diễn / Diễn dịch dựa vào mô hình:


<img src="(https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_1.png" width="200" text-align="center"/>

Để có thể thực hiện các ý tưởng kể trên chúng ta cần đặt ra các câu hỏi: 
  1. Mô hình này chính xác đến đâu ? Có đáng tin cậy hay không ? 

  2. Mô hình hoạt động như thế nào ? Nó đã học được gì từ dữ liệu ? Đây là câu hỏi rất quan trọng làm nền tảng cho việc diễn giải nội dung/cơ chế của mô hình. Giải đáp được câu hỏi này cho phép rút ra hàng loạt thông tin, suy diễn quan trọng, hữu ích bao gồm: Vai trò của mỗi biến ? Mối liên hệ bộ phận giữa mỗi biến và kết quả là gì ? Kết quả của việc giải thích cơ chế này còn có thể được sử dụng để quay ngược lại cải thiện mô hình bằng cách bỏ bớt những biến không quan trọng, tinh chỉnh tham số của algorithm, thêm dữ liệu mới

  3. Giải thích được cơ chế của mô hình ở cấp độ cá thể: Mô hình hoạt động có chính xác không cho trường hợp này ? Tại sao kết quả lại như vậy ? Biến nào có vai trò/ ảnh hưởng quan trọng nhất ở cá thể này ?

## 3 Giải thích black-box model

### 3.1 Local Interpretable Model-agnostic Explanations
Như đã nói ở trên các mô hình chúng ta đang sử dụng là Random Forest và Deep learning, do đó chúng ta không thể các phương pháp tính điểm cho từng giá trị như Logistic hay Cây quyết định như Decision tree, ... 

Phương pháp đầu tiên được áp dụng là LIME (Local Interpretable Model-agnostic Explanations), dựa trên giả định là bất kể mô hình phức tạp đến đâu, thì tại một miền cục bộ trong không gian dữ liệu, mô hình có thể được ước lượng xấp xỉ bằng quy luật tuyến tính. 

1. Đầu tiên, LIME sẽ lấy thông tin về đặc tính phân phối của feature dựa vào training dataset và nội dung trong model. Thông tin này được lưu trữ trong một object gọi là explainer. 
2. Việc diễn giải sẽ được áp dụng cho 1 trường hợp, cá thể mới. LIME sẽ mô phỏng một lượng lớn các trường hợp giả định (một đám mây nhiễu của features) nằm kề cận chung quanh trường hợp đang được xét, dựa vào quy luật phân phối của features mà nó đã ghi nhận từ trước.
3. LIME áp dụng mô hình cho toàn bộ những điểm trong không gian nhiễu này, đồng thời tính khoảng cách giữa các điểm mô phỏng đến điểm trung tâm là trường hợp được xét. Khoảng cách này sẽ được chuyển thành thang điểm
4. LIME chọn một số lượng M features tiêu biểu nhất cho phép mô tả tốt nhất khoảng cách nói trên.
5. LIME dựng một mô hình rất đơn giản cho các điểm mô phỏng, sử dụng M features được chọn làm predictor, để giải nghĩa cho outcome của model. Mô hình này có dạng Tuyến tính, hoặc mô hình Decision tree. Tham số hồi quy cho mỗi Features được điều chỉnh bằng một trong số (Weight) tỉ lệ với khoảng cách sai biệt với giá trị feature có thực của cá thể.
6. Việc diễn giải tính hợp lý của kết quả được thực hiện dựa vào Weight coefficient và danh sách M features được chọn. Nếu Weight coefficient > 0, thì giá trị quan sát của feature Mi đang ủng hộ cho kết quả tiên lượng (outcome) P, ngược lại, Weight Coefficient <0 thì giá trị feature Mi chống lại kết quả P.


Dưới đây là 1 ví dụ về Lime Cho B2:

<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>var</th>
      <th>value</th>
      <th>rule</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>DAY_FROM_LAST_PAID</td>
      <td>4.0</td>
      <td>DAY_FROM_LAST_PAID &lt;= 13.00</td>
    </tr>
    <tr>
      <th>1</th>
      <td>PAID_LAST_MONTH</td>
      <td>1.0</td>
      <td>PAID_LAST_MONTH &lt;= 1.00</td>
    </tr>
    <tr>
      <th>2</th>
      <td>LAST_RECEIPT_AMT</td>
      <td>85410.0</td>
      <td>LAST_RECEIPT_AMT &lt;= 1000000.00</td>
    </tr>
    <tr>
      <th>3</th>
      <td>PAID_COUNT_6M</td>
      <td>1.0</td>
      <td>PAID_COUNT_6M &lt;= 4.00</td>
    </tr>
    <tr>
      <th>4</th>
      <td>DPD</td>
      <td>44.0</td>
      <td>DPD &lt;= 44.00</td>
    </tr>
    <tr>
      <th>5</th>
      <td>DPD_1M</td>
      <td>44.0</td>
      <td>43.00 &lt; DPD_1M &lt;= 53.00</td>
    </tr>
    <tr>
      <th>6</th>
      <td>DPD_2M</td>
      <td>14.0</td>
      <td>DPD_2M &lt;= 17.00</td>
    </tr>
    <tr>
      <th>7</th>
      <td>POS_BOM</td>
      <td>4222496.0</td>
      <td>POS_BOM &lt;= 9471104.50</td>
    </tr>
    <tr>
      <th>8</th>
      <td>INSTALLMENT</td>
      <td>704000.0</td>
      <td>INSTALLMENT &lt;= 1403000.00</td>
    </tr>
    <tr>
      <th>9</th>
      <td>ACTIVE_NUM</td>
      <td>2.0</td>
      <td>1.00 &lt; ACTIVE_NUM &lt;= 2.00</td>
    </tr>
    <tr>
      <th>10</th>
      <td>DEFER_FLAG</td>
      <td>0.0</td>
      <td>DEFER_FLAG &lt;= 0.00</td>
    </tr>
  </tbody>
</table>

<img src="(https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_2.png" width="200" text-align="center"/>

<img src="(https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_3.png" width="200" text-align="center"/>

Trong 11 features có ảnh hưởng tới kết quả tiên lượng: 8 trong số đó phản đối cho kết quả "Paid"


Các yếu tố ủng hộ: 
- PAID_LAST_MONTH  = 1 : có Paid vào tháng trước 
- DPD = 44 <= 44 
- INSTALLMENT	 = 703665  : INSTALLMENT vừa phải

Nhìn vào các yếu tố phải đối thì có thể rút ra 1 số điều sau: 
Tuy có PAID_LAST_MONTH nhưng ngày thanh toán chỉ cách ngày 1 có 4 ngày, LAST_RECEIPT_AMT rất nhỏ chỉ có 85,410 => rất nghi ngờ đây là trường hợp đập tiền !

**Mô hình đã tiên lượng trường hợp này vào bin 9, và đúng như dự báo, trường hợp này không có thanh toán trong tháng.**



### 3.2 Descriptive Machine Learning EXplanations

Descriptive Machine Learning EXplanations là phương pháp được Przemyslaw Biecek công bố trên CRAN vào giữa tháng 6 năm 2018. Tác giả Biecek đã đi xa hơn bất cứ người nào khác trong việc diễn giải nội dung mô hình, với 3 ý tưởng độc đáo:

1. Đưa ra một quy trình giải nghĩa phổ quát cho mọi mô hình, bất kể bản chất của algorithm và mục tiêu nghiên cứu (hồi quy/tiên lượng, phân loại hay suy diễn)

2. Cho phép trình bày trực quan kết quả diễn giải của hàng loạt mô hình.

3. Giải đáp hầu hết câu hỏi quan trọng để "hiểu" mô hình, bao gồm: Nội dung và cơ chế hoạt động : Tầm quan trọng của các biến, Quan hệ riêng phần của từng biến đối với kết quả (đặc biệt hữu ích cho bài toán hồi quy), độ chính xác của mô hình và diễn giải cho từng cá thể (theo phương pháp breakdown).

Dưới đây là 1 ví dụ khác Cho B2:

 <table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>variable</th>
      <th>cumulative</th>
      <th>contribution</th>
      <th>sign</th>
      <th>position</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>intercept</td>
      <td>0.254452</td>
      <td>0.254452</td>
      <td>1.0</td>
      <td>15</td>
    </tr>
    <tr>
      <th>1</th>
      <td>PAID_LAST_MONTH = 1.0</td>
      <td>0.490566</td>
      <td>0.236114</td>
      <td>1.0</td>
      <td>14</td>
    </tr>
    <tr>
      <th>2</th>
      <td>POS_BOM = 40310000.0</td>
      <td>0.640417</td>
      <td>0.149850</td>
      <td>1.0</td>
      <td>13</td>
    </tr>
    <tr>
      <th>3</th>
      <td>LAST_RECEIPT_AMT = 3263000.0</td>
      <td>0.610289</td>
      <td>-0.030127</td>
      <td>-1.0</td>
      <td>12</td>
    </tr>
    <tr>
      <th>4</th>
      <td>ACTIVE_NUM = 1.0</td>
      <td>0.615844</td>
      <td>0.005555</td>
      <td>1.0</td>
      <td>11</td>
    </tr>
    <tr>
      <th>5</th>
      <td>TENOR = 18.0</td>
      <td>0.615844</td>
      <td>0.000000</td>
      <td>0.0</td>
      <td>10</td>
    </tr>
    <tr>
      <th>6</th>
      <td>EFF_RATE = 45.0</td>
      <td>0.615844</td>
      <td>0.000000</td>
      <td>0.0</td>
      <td>9</td>
    </tr>
    <tr>
      <th>7</th>
      <td>PTP = 0.0</td>
      <td>0.615844</td>
      <td>0.000000</td>
      <td>0.0</td>
      <td>8</td>
    </tr>
    <tr>
      <th>8</th>
      <td>DAY_FROM_LAST_PAID = 1.0</td>
      <td>0.523748</td>
      <td>-0.092096</td>
      <td>-1.0</td>
      <td>7</td>
    </tr>
    <tr>
      <th>9</th>
      <td>DEFER_FLAG = 0.0</td>
      <td>0.520220</td>
      <td>-0.003528</td>
      <td>-1.0</td>
      <td>6</td>
    </tr>
    <tr>
      <th>10</th>
      <td>DPD_2M = 14.0</td>
      <td>0.518671</td>
      <td>-0.001549</td>
      <td>-1.0</td>
      <td>5</td>
    </tr>
    <tr>
      <th>11</th>
      <td>INSTALLMENT = 3251000.0</td>
      <td>0.467187</td>
      <td>-0.051485</td>
      <td>-1.0</td>
      <td>4</td>
    </tr>
    <tr>
      <th>12</th>
      <td>DPD = 44.0</td>
      <td>0.408504</td>
      <td>-0.058682</td>
      <td>-1.0</td>
      <td>3</td>
    </tr>
    <tr>
      <th>13</th>
      <td>PAID_COUNT_6M = 1.0</td>
      <td>0.452468</td>
      <td>0.043964</td>
      <td>1.0</td>
      <td>2</td>
    </tr>
    <tr>
      <th>14</th>
      <td>DPD_1M = 44.0</td>
      <td>0.273401</td>
      <td>-0.179067</td>
      <td>-1.0</td>
      <td>1</td>
    </tr>
    <tr>
      <th>15</th>
      <td>prediction</td>
      <td>0.273401</td>
      <td>0.273401</td>
      <td>1.0</td>
      <td>0</td>
    </tr>
  </tbody>
</table>


<img src="(https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_4.png" width="200" text-align="center"/>


