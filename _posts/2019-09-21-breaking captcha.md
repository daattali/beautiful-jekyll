---
layout: post
title: Breaking captcha CIC
subtitle: ứng dụng Computer Vision
tag: Computer Vision
thumbnail-img: /assets/img/captcha4.png
share-img: /assets/img/captcha4.png
---



Thời buổi bây giờ các thuật toán deep learning đã rất phát triển, các pre-trained model thì vô số, việc tiếp cận cũng rất dễ dàng. Tự thấy mình cũng chẳng là gì trong thế giới trí tuệ đó, nhưng mình lại rất thích đem các phát kiến machine learning đó vào ứng dụng trong thực tế. Cũng tự nhủ với mình rằng mình không phát minh ra các thuật toán đó nhưng mình sẽ ứng dụng chúng thật tốt để tạo ra thêm nhiều giá trị cho xã hội. Bài này mình sẽ giới thiệu một ứng dụng nho nhỏ của mình về Computer Vision trong việc tự động các công việc nhàm chán tại công ty.

### Giới thiệu  
Đây là dự án thứ 2 của mình tại công ty, dự án này phục vụ quá trình thu thập dữ liệu, check thông tin các khách hàng trong diện khả nghi. Do lượng thông tin khách hàng cần check khá lớn nên việc thực hiện công việc này một cách tự động sẽ mang lại rất nhiều lợi ích tiết kiệm thời gian và nguồn lực, tăng hiệu quả hoạt động.
Tuy nhiên việc thực hiện tự động gặp phải khó khăn đó là việc check thông tin chỉ được hoàn tất sau khi nhập vào captcha có dạng như sau: 

<img src="/assets/img/captcha0.png" width="700" />

<img src="/assets/img/captcha1.png" width="700" />


### Giải pháp

Việc tự động lấy dữ liệu có thể dễ dàng thực hiện với thư viện selenium của Python, khó khăn duy nhất cần phải giải quyết là phá được captcha.
Với xử lý hình ảnh thì deep learning là sự lựa chọn tốt nhất rồi , open-cv cũng không thể bỏ qua được. Đối với bài toán không quá phức tạp như phá captcha, thì sử dụng các thuật toán phức tạp như yolo, ssd, mask_RCNN trở nên khá cồng kềnh.  Cộng với điều kiện máy công ty không có gpu nên khi triển khai, tốc độ thực thi không đạt như mong muốn. Do vậy hướng đi sử dụng pre-trained model đã bị gạt bỏ sau một ngày thử nghiệm. 

Trở lại với open-cv và phân tích các đặc trưng của captcha, ta nhận thấy mỗi captcha có 5 ký tự và chỉ có 3 màu là xanh dương, vàng, đen. Do vậy có thể tách captcha theo 3 màu và cố gắp chia captcha thành 5 phần độc lập bao gồm 5 ký tự, với mỗi phần đó có thể tạo mô hình CNN để dự báo ký tự. 

Việc lọc màu cũng là 1 cách rất tốt để lấy mẫu. Ta chỉ cần chọn các ký tự có màu độc lập là có sẵn 1 bộ mẫu ký tự đơn, sau đó gán nhãn. Tiếp tục thực hiện train model CNN và lấy mẫu thêm theo cách trên mô hình rất nhanh sẽ được củng cố độ chính xác. 

Sau đây là một số kết quả dự báo từ mô hình (hình đã qua open-cv nên màu hơi khác, mình lười chỉnh lại): 

<img src="/assets/img/captcha3.png" width="700" />

<img src="/assets/img/captcha4.png" width="700" />

Và bây giờ thì việc khó khăn nhất là captcha đã được hóa giải, công việc tự động khác thì đã có selenium lo, chúng ta có thể vào lấy thông tin trên CIC dễ như ăn cháo với hiệu suất gấp mấy chục lần con người. 
