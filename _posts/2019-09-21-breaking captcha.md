

## Giới thiệu
Dây là dự án thứ 2 của mình tại công ty, dự án này phục vụ quá trình thu thập dữ liệu, check thông tin các khách hàng trong diện khả nghi.  Do lượng thông tin khách hàng cần check khá lớn nên việc thực hiện công việc này một các tự động sẽ mang lại rất nhiều lợi ích tiết kiệm thời gian và nguồn lực , tăng hiệu quả hoạt động.
Tuy nhiên việc thực hiện tự động gặp phải khó khăn đó là việc check thông tin chỉ được hoàn tất sau khi nhập vào captcha có dạng như sau: 


![Crepe](https://raw.githubusercontent.com/minmax49/minmax49.github.io/master/img/captcha0.png)


## Giải pháp

Việc tự động lấy dữ liệu có thể dễ dàng thực hiện với thư viện selenium của Python, khó khăn duy nhất cần phải giải quyết là phá được captcha.
Với sử lý hình ảnh thì deep learning là sự lựa chọn tốt nhất rồi , open-cv cũng không thể bỏ qua được. Đối với bài toán không quá phức tạp như phá captcha, thì sử dụng các thuật toán phức tạp như yolo, ssd, mask_RCNN trở nên khá cồng kềnh.  Cộng với điều kiện máy công ty không có gpu nên khi triển khai, tốc độ thực thi không đạt như mong muốn. Do vậy hướng đi sử dụng pretrain model đã bị gạt bỏ sau một ngày thử nghiệm. 
Trở lại với open-cv và phân tích các đặc trưng của captcha, ta nhận thấy mỗi captcha có 5 ký tự và chỉ có 3 màu là xanh dương, vàng, đen. Do vậy có thể tách captcha theo 3 màu và cố gắp chia captcha thành 5 phần độc lập bao gồm 5 ký tự, với mỗi phần đó có thể tạo mô hình CNN để dự báo ký tự. 
Việc lọc màu cũng là 1 cách rất tốt để lấy mẫu. Ta chỉ cần chọn các ký tự có màu độc lập là có sẵn 1 bộ mẫu ký tự đơn, sau đó gán nhãn. Tiếp tục thực hiện train model CNN và lấy mẫu thêm theo cách trên mô hình rất nhanh sẽ được củng cố độ chính xác. 

Sau đây là một số kết quả dự báo từ mô hình (hình đã qua open-cv nên màu hơi khác, mình lười chỉnh lại): 
