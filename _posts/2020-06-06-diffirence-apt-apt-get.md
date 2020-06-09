---
layout: post
title: Tìm hiểu sự khác nhau giữa lệnh apt và apt-get trong ubuntu
subtitle: Each post also has a subtitle
# gh-repo: daattali/beautiful-jekyll
# gh-badge: [star, fork, follow]
# tags: [test]
comments: true
---

Một trong những tính năng mới đáng chú ý của Ubuntu 16.04 là 'giới thiệu' lệnh apt . Thực tế là phiên bản ổn định đầu tiên của apt đã được phát hành vào năm 2014 nhưng mọi người bắt đầu chú ý đến nó vào năm 2016 với việc phát hành Ubuntu 16.04

Nó trở nên phổ biến để xem apt install packagethay vì thông thường apt-get install package. Cuối cùng, nhiều bản phân phối khác theo bước chân của Ubuntu và bắt đầu khuyến khích người dùng sử dụng apt thay vì apt-get.

Bạn có thể tự hỏi sự khác biệt giữa apt-get và apt là gì? Và nếu chúng có cấu trúc lệnh tương tự, thì cần gì cho lệnh apt mới? Bạn cũng có thể nghĩ nếu apt tốt hơn apt-get? Bạn nên sử dụng lệnh apt mới hay gắn bó với các lệnh apt-get cũ tốt ?

Tôi sẽ giải thích tất cả những câu hỏi này trong bài viết này và tôi hy vọng rằng đến cuối bài viết này, bạn sẽ có một bức tranh rõ ràng hơn.

apt vs apt-get

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg){: .center-block :}

Chỉ là một từ nhanh chóng cho người dùng Linux Mint. Vài năm trước, Linux Mint đã triển khai một trình bao bọc python có tên apt thực sự sử dụng apt-get nhưng cung cấp các tùy chọn thân thiện hơn. Cái apt mà chúng ta đang thảo luận ở đây không giống với cái trong Linux Mint.