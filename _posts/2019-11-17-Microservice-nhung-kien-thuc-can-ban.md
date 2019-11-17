---
layout: post
title: Microservice - những kiến thức căn bản
author: [tunghust]
categories: [technology]
tags: [microservice]
comments: true
---

# Microservice - những kiến thức căn bản
Author: [@tunghust](https://github.com/tunghust)



Chắc hẳn ai cũng đã từng nghe về `Microservice`, kiến trúc `Microservice`. Tuy nghiên bản chất của nó là gì? Tại sao nó lại được nhắc nhiều đến như thế? Bài viết này sẽ cho bàn 1 cái nhìn tổng quát về nó. Cách ứng dụng và triển khai trong dự án thực tế  

## Mục lục
1. `Microservice` là gì?
1. Ưu nhược điểm của `Microservice` là gì?
1. Hành trang để triển khai 1 hệ thống `Microservice`?
1. Triển khai thử 1 hệ thống `Microservice`

## Microservice là gì?

Từ những năm 2016, `Microservice` rất được chú ý và đưa vào sử dụng bởi các công ty to như Amazon, Netflix, Canon hay Cookpad bởi ưu điểm dễ nâng cấp, dễ scale của nó.
Kéo theo đó là cách dịch vụ liên quan đến `cloud`, `IT infrastructure` cũng phát triển chóng mặt.  
Với chỉ 1 vài cú click chuột là bạn đã xây dựng được một hệ thống `infrastructure`, thêm một vài cú click chuột nữa là bạn có thể xây dựng được một ứng dụng chạy trên nền tảng `infrastructure` vừa tạo ra.

Bởi các thế mạnh và linh hoạt của `Microservice` nên hiện nay rất nhiều công ty đang suy nghĩ để đưa nó vào hệ thống của công ty.  
Tuy nhiên, dịch vụ nào, kiến trúc nào cũng có điểm mạnh và điểm yếu của nó, nên việc xem xét và đánh giá có phù hợp với hệ thống hiện tại của công ty không trước khi áp dụng cũng cần được phân tích kĩ càng. Nếu không sẽ chỉ là một mớ bỏng bong mà thôi.

**Vậy, Microservice là gì?**


`Microservice` là một ứng dụng phần mềm chạy độc lập thực hiện 1 chức năng nhất định trong hệ thống. 

![Ví dụ](https://7z2aaa.bn.files.1drv.com/y4mgYaLzN4q45cwMS45mkmzVpoBiX59LyQm6Bua1pEcj8JG2S6Yg4aMS3suBaZeTOwzjeM4uJsPt10Qlo_3vn9i-Pl5pRitWJs71pHGH9qYY4pmKrI29wpoPe7SCcZ7dLFTNy_LuS9i3AxGqro8PHMVMAKZ6mViYBYeWSBxR3Ahv_O_wvZr12cYI_bxV-HT5l0FjgtXsk4C39XxMCrbw1VoOA?width=433&height=370&cropmode=none "Ví dụ")  
*Hình 1: Ví dụ về `Microservice`*

Như bạn thấy trong hình ở ví dụ EC bên trên, có 3 dịch vụ độc lập riêng biệt nhau `Đặt hàng(注文)`, `Thanh toán(決済)`, `Gửi email(メール)` thao tác với 3 DB cũng độc lập nhau\*. Giữa Web App (Client) và Service giao tiếp với nhau bằng `Rest API`, các `API` cũng thể giao tiếp với nhau thông qua `API` hoặc `gRPC`.

\**Tùy vào từng bài toán khác nhau ta sẽ thiết kế DB chung hay riêng biệt nhau*

Chẳng hạn với ví dụ bên trên, khi ta muốn triển khai thêm một hình thức thanh toán mới (`LINE Pay` hay `PayPay`), thì đơn thuần chỉ cần phát triển thêm mỗi chức năng thanh toán mới đó mà ko ảnh hưởng đến các service hiện tại.

**Vậy cấu trúc Wep app truyền thống Monolithic và Microservice khác nhau như thế nào?**

![So sánh cấu trúc web app truyền thống và `Microservice`](https://vmnyxq.bn.files.1drv.com/y4mjqmOtk0L6vmUze75EWVaChNx5pGimms787qLthLhbqDd_BMeMD5jwh1tRhsFGEhG0auTsL69VoJvJ59jXoAakj1XRtz5Fqx1JJJ-JBMkW7z1NDwBRA-YMtycyiYy3tO1xNRDXMfrNrzvNoUbufmHfT3JS_6C6MCE53sXaEEpnnSYNtuS_InNWqzytNv3BVCpr3s6gu3pMUkQzriARxXa0g?width=750&height=390&cropmode=none "So sánh cấu trúc web app truyền thống và `Microservice`")  
*Hình 2: So sánh cấu trúc web app truyền thống và `Microservice`*

Hình trên chắc đã cho bạn cái nhìn khá rõ ràng để so sánh kiến trúc `Monolithic` và `Microservice`.  
Trong khi kiến trúc `Microservice` chia nhỏ từng dịch vụ thành các app riêng biệt thì kiến trúc truyền thống lại gom tất cả thành cục để quản lí & phát triển.  

Bạn đang cân nhắc triển khai `Microservice` vào hệ thống công ty hiện tại trong khi kiến trúc `Monolithic` vẫn đang chạy tốt? Vậy lí do gì để bạn có thể quyết tâm đề bạt công ty nên chuyển sang `Microservice`? Hãy cùng chỉ ra các điểm mạnh & điểm yếu trong phần tiếp theo.

## Ưu nhược điểm của Microservice là gì?

Trước khi đi vào ưu nhược điểm thì chúng ta nên nhìn nhận lại, vậy kiến trúc `Monolithic` đang gặp phải các vấn đề gì?  

- Khi quy mô ứng dụng còn nhỏ thì gần như không vấn đề gì
- Khi ứng dụng phình to ra, thì chỉ cần sửa 1 phần nhỏ cũng ảnh hưởng toàn bộ hệ thống
    - Chính là nguyên nhân phát sinh `bugs`  
    - Chính là nguyên nhân phát sinh dừng dịch vụ cung cấp tạm thời, ảnh hướng khách hàng
- Chi phí bảo trì nâng cấp tốn kém
- Đòi hỏi `server specification` cao để gồng gánh

**Microservice - đơn giản hóa sự phức tạp**

Như đã nói ở trên, ứng dụng được chia thành các chức năng, mỗi chứng năng sẽ được chia thành 1 hoặc nhiều `Microservice`. Dẫn tới khi thực hiện thêm, sửa hoặc loại bỏ một chức năng nào nó thì gần như chỉ `Microservice` đó bị ảnh hưởng, chi phí phát triển thấp. Ngoài ra nếu dùng các dịch vụ trong bộ tools `DevOps` của `AWS` cung cấp, thì dịch vụ của bạn sẽ không phải dừng tạm thời 1s nào để chuyển mình sang một `version` đã được `updated`.

Do các `Microservice` giao tiếp với nhau thông qua `API` hoặc `gRPC` hay các giao thức tương tự, nên việc các `Microservice` dùng chung ngôn ngữ lập trình, chung hệ quản trị CSDL,... là không cần thiết. Thích gì chọn lấy, phù hợp là được. Thậm chí chọn theo `trend` cũng không thành vấn đề.

Có ưu điểm ắt phải có nhược điểm, để cho dễ nhìn thì ưu nhược điểm sẽ được tổng hợp dưới đây:

- Ưu điểm  
    - Do chia nhỏ thành các `service` nên dễ quản lí, bảo trì, vận hành & nâng cấp lên các công nghệ `trend` mới
    - Giảm thiểu thiệt hại tối đa  
         Mỗi `Microservice` là một vùng đất riêng, nên thiệt hại dịch vụ chỉ xảy ra ở `Microservice` đó
    - Dễ `scale`  
         `Microservice` nào đang được dùng nhiều, tải cao thì chỉ cần `scale` chính `Microservice` đó, nếu cần thì chỉ cần `modify` `source code` của `Microservice` đó là được.
    - Tốc độ `deploy & release`
    - Giảm độ trễ vượt bậc do dùng `API` so với cấu trúc `Monolithic`
- Nhược điểm
    - Khó khăn trong khâu quản lí `transaction data`  
         So với cấu trúc `Monolithic` chỉ có 1 DB thì chuyện quản lí `transaction data` sẽ đơn giản hóa hơn nhiều, trong khi thông thường thì mỗi `Microservice` dùng 1 DB riêng. Do đó để đảm bảo tính nhất quán của data trong kiến trúc `Microservice` thì bước thiết kế cần được chú trọng, kết quả data lấy được hay được `insert` vào DB cần được `verify` kĩ càng.
    - Gánh nặng vận hành tăng lên  
         Trạng thái vận hành của từng `Microservice` cần được theo dõi, cần phải cài đặt các `rule` để theo dõi `traffic` kéo theo `cost` vận hành tăng lên 1 phần nào đó.
    - Khó khăn trong khâu thiết kế & thực thi với độ chính xách cao  
         Để có 1 kiến trúc `Microservice` ổn định cần phải có bước thiết kế với độ chính xác cao. Chưa kể có nhiều `Microservice` cùng thao các vào 1 DB hoặc nhiều DB cùng lúc dễ dẫn tới bất đồng bộ dữ liệu, sinh ra các lỗi nghiêm trọng. Để giải quyết được điều này phụ thuộc nhiều vào trình độ của các Kĩ sư thiết kế & phát triển.
    - Khó khăn trong khâu phân tích lỗi  
         Do nhiều `Microservice` đang chạy, nên việc phân tích để phát hiện lỗi đang xảy ra ở `Microservice` nào đòi hỏi kinh nghiệp và kĩ năng phân tích của kĩ sư.
    - Thay đổi kĩ sư phụ trách hệ `Microservice` dễ phát sinh ra chi phí để học các kĩ thuật ngôn ngữ đang được sử dụng ở `Microservice` đó.

**Tóm lại**  
Việc quyết định chuyển hệ thống theo kiến trúc `Monolithic` hiện tại sang `Microservice` cần được bàn bạc và lên kế hoạch chi tiết.
Song, với các ưu điểm vượt trội của `Microservice` thì việc áp dụng vào một hệ thống mới sắp được triển khai là hoàn toàn nên làm.

**Vậy cần chuẩn bị gì để triển khai một hệ thống Microservice?**  
Hãy cùng theo dõi phần tiếp theo để tìm câu trả lời


## Hành trang để triển khai 1 hệ thống Microservice
Đang cập nhật...


