---
layout: post
title: Scorecard Model Explain
subtitle: Credit Scorecard chapter 4
tags: [Credit Scorecard]
---


# 1 Tại sao phải diễn giải mô hình Machine learning ?


Lê Ngọc Khả Nhi - một data scientist mà tôi ngưỡng mộ đã từng nói : 

"Một mô hình chính xác dĩ nhiên là tốt, nhưng chưa đủ. Độ chính xác của mô hình là tiêu chí được nhắm tới bởi hầu hết data scientist, tuy nhiên, tính chính xác không đồng nghĩa với tính hiệu quả. "

Thật vậy trong quá trình đưa mô hình Scorecard vào với vận hành tại CS&A, tự bản thấy được còn có rất nhiều vấn đề cần được giải quyết ! 


Cho đến thời điểm hiện tại, mô hình Machine learning đang được áp dụng để xây dựng Scorecard đã và đang cho những dự đoán rất chính xác về kết quả thu hồi nợ. Tuy nhiên khi đưa vào vận hành thì không ít người bắt đầu hoài nghi về kết quả dự đoán của mô hình, bao gồm những người vận hành có nhiều kinh nghiệm và một số chuyên viên phân tích thiếu kỹ năng. 

Họ bắt đầu đặt ra các câu hỏi hoài nghi : 

1. Tại sao một số trường hợp có thanh toán vào tháng trước nhưng vẫn được phân loại xấu (bin 8,9,10) 
2. Tại sao một số trường hợp mọi yếu tố đều giống nhau nhưng chỉ vì có số POS thấp hơn mà hợp đồng bị phân loại kém hẳn


Thời gian gần đây đã bắt đầu có những ý kiến hoài nghi, thậm chí cảnh báo về phong trào sử dụng Big data và Machine learning vào quá trình thu nợ. Một trong những luận điểm mà các bên phản đối đưa ra, đó là hầu hết những mô hình có nội dung không thể giải thích được. Khi họ không thể hiểu được cơ chế đằng sau kết quả, họ không thể tin cậy vào bản thân kết qủa đó. Kết quả dự báo đôi khi ảnh hưởng rất nghiêm trọng đến kết quả thu nợ : thí dụ dự báo case xấu thì lựa chọn follow hay bỏ ?

Và cũng có vẻ bất công khi chúng ta set Target cao hơn cho 1 nhân viên nào đó vì một mô hình Machine learning đã dự báo rằng với danh mục của bạn thì phải đạt được con số như vậy. Nó cũng giống như một bệnh nhân đi khám và nhận được bác sĩ giải thích như sau : "Bà có 99.5% nguy cơ bi ung thư, vì một mô hình Neural network đã quyết định như vậy". 


# 2 Giải thích mô hình không đơn giản chút nào


