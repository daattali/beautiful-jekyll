---
layout: post
title: Explain the Scorecard Model
subtitle: Credit Scorecard chapter 4
tags: [Credit Scorecard]
---


# 1 Tại sao phải diễn giải mô hình Machine learning ?


Lê Ngọc Khả Nhi - một data scientist mà tôi ngưỡng mộ đã từng nói : 

"Một mô hình chính xác dĩ nhiên là tốt, nhưng chưa đủ. Độ chính xác của mô hình là tiêu chí được nhắm tới bởi hầu hết data scientist, tuy nhiên, tính chính xác không đồng nghĩa với tính hiệu quả. "

Thật vậy trong quá trình đưa mô hình Scorecard vào với vận hành tại CS&A, tự bản thấy được còn có rất nhiều vấn đề cần được giải quyết ! 


Cho đến thời điểm hiện tại, mô hình Machine learning đang được áp dụng để xây dựng Scorecard đã và đang cho những dự đoán rất chính xác về kết quả thu hồi nợ. Tuy nhiên khi đưa vào vận hành thì không ít người bắt đầu hoài nghi về kết quả dự đoán của mô hình, bao gồm những người vận hành có nhiều kinh nghiệm và một số chuyên viên phân tích thiếu kỹ năng. 

Họ bắt đầu đặt ra các câu hỏi hoài nghi : 

1. Tại sao một số trường hợp có thanh toán vào tháng trước nhưng vẫn được phân loại xấu (bin 8,9,10) ?
2. Tại sao một số trường hợp mọi yếu tố đều giống nhau nhưng chỉ vì có số POS thấp hơn mà hợp đồng bị phân loại kém hẳn ?

Thời gian gần đây đã bắt đầu có những ý kiến hoài nghi, thậm chí cảnh báo về phong trào sử dụng Big data và Machine learning vào quá trình thu nợ. Một trong những luận điểm mà các bên phản đối đưa ra, đó là hầu hết những mô hình có nội dung không thể giải thích được. Khi họ không thể hiểu được cơ chế đằng sau kết quả, họ không thể tin cậy vào bản thân kết qủa đó. Kết quả dự báo đôi khi ảnh hưởng rất nghiêm trọng đến kết quả thu nợ : thí dụ dự báo case xấu thì lựa chọn follow hay bỏ ?

Và cũng có vẻ bất công khi chúng ta đặt Target cao hơn cho 1 nhân viên nào đó vì một mô hình Machine learning đã dự báo rằng với danh mục của bạn thì phải đạt được con số như vậy. Nó cũng giống như một bệnh nhân đi khám và được bác sĩ giải thích như sau : "Bà có 99.5% nguy cơ bi ung thư, vì một mô hình Neural network đã quyết định như vậy". 


# 2 Giải thích mô hình không đơn giản.

![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_0.png)

Trong Machine learning, có một lời nguyền tai ác, đó là : "Tính tường minh của mô hình tỉ lệ nghịch với tính chính xác", mô hình càng chính xác thì càng bí hiểm. Sự phức tạp đến từ bản chất của algorithm, số lượng input features hoặc cả 2. Thời đại Big Data và IOT đã cưỡng ép chúng ta phải lựa chọn những algorithm phức tạp nhất, vì những mô hình tuyến tính không có cách nào xử lý được lượng data lớn cỡ đó.

Trong sơ đồ trên, những mô hình chính xác nhất lại chính là những mô hình bí hiểm nhất, bao gồm: Random Forest, GBM, Deep neural network, SVM… Chúng trở thành những hộp đen, hay mô hình "Bất khả Tri".

Thật không may, các mô hình chính để xây dụng cho Scorecard lại là Random Forest và Deep learning, việc giải thích chúng đã khó lại càng khó. 

Sơ đồ sau đây tóm tắt quy trình Suy diễn / Diễn dịch dựa vào mô hình:

![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_1.png)

Để có thể thực hiện các ý tưởng kể trên chúng ta cần đặt ra các câu hỏi: 
  1. Mô hình này chính xác đến đâu ? Có đáng tin cậy hay không ? 

  2. Mô hình hoạt động như thế nào ? Nó đã học được gì từ dữ liệu ? Đây là câu hỏi rất quan trọng làm nền tảng cho việc diễn giải nội dung/cơ chế của mô hình. Giải đáp được câu hỏi này cho phép rút ra hàng loạt thông tin, suy diễn quan trọng, hữu ích bao gồm: Vai trò của mỗi biến ? Mối liên hệ bộ phận giữa mỗi biến và kết quả là gì ? Kết quả của việc giải thích cơ chế này còn có thể được sử dụng để quay ngược lại cải thiện mô hình bằng cách bỏ bớt những biến không quan trọng, tinh chỉnh tham số của algorithm, thêm dữ liệu mới

  3. Giải thích được cơ chế của mô hình ở cấp độ cá thể: Mô hình hoạt động có chính xác không cho trường hợp này ? Tại sao kết quả lại như vậy ? Biến nào có vai trò/ ảnh hưởng quan trọng nhất ở cá thể này ?

# 3 Giải thích black-box model

Như đã nói ở trên các mô hình chúng ta đang sử dụng là Random Forest và Deep learning, do đó chúng ta không thể các phương pháp tính điểm cho từng giá trị như Logistic hay Cây quyết định như Decision tree, ... 

Phương pháp đầu tiên được áp dụng là LIME (Local Interpretable Model-agnostic Explanations), dựa trên giả định là bất kể mô hình phức tạp đến đâu, thì tại một miền cục bộ trong không gian dữ liệu, mô hình có thể được ước lượng xấp xỉ bằng quy luật tuyến tính. 

1. Đầu tiên, LIME sẽ lấy thông tin về đặc tính phân phối của feature dựa vào training dataset và nội dung trong model. Thông tin này được lưu trữ trong một object gọi là explainer. 
2. Việc diễn giải sẽ được áp dụng cho 1 trường hợp, cá thể mới. LIME sẽ mô phỏng một lượng lớn các trường hợp giả định (một đám mây nhiễu của features) nằm kề cận chung quanh trường hợp đang được xét, dựa vào quy luật phân phối của features mà nó đã ghi nhận từ trước.
3. LIME áp dụng mô hình cho toàn bộ những điểm trong không gian nhiễu này, đồng thời tính khoảng cách giữa các điểm mô phỏng đến điểm trung tâm là trường hợp được xét. Khoảng cách này sẽ được chuyển thành thang điểm
4. LIME chọn một số lượng M features tiêu biểu nhất cho phép mô tả tốt nhất khoảng cách nói trên.
5. LIME dựng một mô hình rất đơn giản cho các điểm mô phỏng, sử dụng M features được chọn làm predictor, để giải nghĩa cho outcome của model. Mô hình này có dạng Tuyến tính, hoặc mô hình Decision tree. Tham số hồi quy cho mỗi Features được điều chỉnh bằng một trong số (Weight) tỉ lệ với khoảng cách sai biệt với giá trị feature có thực của cá thể.
6. Việc diễn giải tính hợp lý của kết quả được thực hiện dựa vào Weight coefficient và danh sách M features được chọn. Nếu Weight coefficient > 0, thì giá trị quan sát của feature Mi đang ủng hộ cho kết quả tiên lượng (outcome) P, ngược lại, Weight Coefficient <0 thì giá trị feature Mi chống lại kết quả P.


Dưới đây là 1 ví dụ về Lime :

![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/scorecard_chapter4_2.png)






