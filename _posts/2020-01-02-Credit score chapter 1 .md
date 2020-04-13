---
layout: post
title: Scorecard with Logistic regression and WOE-IV
subtitle: Credit Scorecard chapter 1
tags: [Credit Scorecard]
---


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




## Biểu đồ trực quan hóa dữ liệu 

Cách để chúng ta hiểu dữ liệu nhanh nhất đó chính là qua hình ảnh 

Dưới đây mình chủ yếu sử dụng thư viện **seaborn** vì nó khá thuận tiện mà lại rất đẹp nữa

Biểu đồ histogram để thấy được tần suất của dữ liệu:




![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_0.png)



Biến phân loại:



![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_1.png)


Biểu đồ pairplot để thấy được mối quan hệ của dữ liệu:




![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_2.png)



Quan sát thêm sự mối quan hệ giữa các biến với sns.jointplot:






![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_3.png)



factor "field35" theo "field14" và "label":









![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_4.png)



## Giới thiệu :


Sau khi nhìn qua dữ liệu chắc chúng ta ai cũng muốn hiểu sâu hơn về dữ liệu cũng như khai thác tri thức từ chúng. Một phương pháp thống kê phổ biến dễ hiểu và cũng rất hiệu quả cho các bài toán phân lớp nhị phân thường được nhắc tới đó chính là Logistic regression. 

Mô hình hồi quy logistic là một trong những kỹ thuật thống kê được sử dụng phổ biến nhất để giải quyết vấn đề phân loại nhị phân. Nó được chấp nhận trong hầu hết các lĩnh vực. Hai khái niệm này - Weight of Evidence (WOE) và Information Value (IV) phát triển từ cùng một kỹ thuật hồi quy logistic. Hai thuật ngữ này đã tồn tại trong thế giới chấm điểm tín dụng trong hơn 4-5 thập kỷ. Chúng đã được sử dụng làm chuẩn để sàng lọc các biến trong các dự án mô hình rủi ro tín dụng như xác suất vỡ nợ. Chúng giúp khám phá dữ liệu và các biến. Nó cũng được sử dụng trong dự án phân tích tiếp thị như mô hình phân khúc khách hàng, v.v.


## mô hình Logistic regression :

Với cơ chế phân lớp đễ hiểu và các hàm kích hoạt cơ bản (activation) như sigmoid thì chúng ta có thể khai thác được rất nhiều từ dữ liệu

![image.png](https://miro.medium.com/max/1280/0*gKOV65tvGfY8SMem.png)



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

## Thực hành nào :

Lý thuyết vậy là nhiều rồi, chắc đọc cũng chán ngấy cả người. Vậy chúng ta cùng thực hành chút cho nóng người nào. 

Về phương pháp biến đổi WOE thì có rất nhiều, mình cũng tự custom module để tính woe để theo ý mình nhưng cũng cần kết hợp với các thư viện có sẵn để đạt kết quả tốt nhât:

Dưới đây là kết quả chúng chạy mô hình credit scorecard





![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_5.png)





![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_6.png)





![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_7.png)








![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/creadit_scorecard1_8.png)


Vậy là chúng  ta đã đi lướt qua khá nhiều kiến thức. 

Ở kỳ sau chúng ta sẽ áp dụng nhiều phương pháp và mô hình machine learning hiện đại vào trong bài toán credit scorecard.
