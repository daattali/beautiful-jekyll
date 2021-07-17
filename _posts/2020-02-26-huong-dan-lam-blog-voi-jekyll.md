---
layout: post
title: Jekyll Blog
subtitle: Hướng dẫn làm blog với Jekyll
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [books, blog]
---

Lời nói đầu:
Mình đã có 1 thời gian tìm hiểu về nhiều CMS khác nhau, Blogger, WordPress…

WordPress là một CMS khá nổi tiếng, được nhiều người trên thế giới sử dụng, tuỳ biến, chức năng rất đa dạng. Nói chung chung đơn giản thiếu chức năng gì thì cứ tìm plugin cài vào là xong.


 
Nhưng dù vậy, với những người chỉ muốn tạo 1 trang blog nho nhỏ, xinh xinh, và quan trọng là nhanh, thì Jekyll là 1 sự lựa chọn hợp lý. Hơn nữa không phải cài bất kỳ plugin nào như WordPress.

Và hôm nay, mình sẽ nói về Jekyll và cách tạo 1 trang web tĩnh bằng Jekyll 1 cách chi tiết, dễ hiểu nhất. Hãy cùng xem nào.

I. Chuẩn bị.
Tài khoản Github.
Bắt buộc phải tạo 1 tài khoản Github vì chúng ta sẽ lưu Blog của chúng ta lên đấy mà hehe.

Một chút kiên nhẫn
Bản thân mình mới đầu tập dùng Jekyll thì có hơi khó khăn, sau này quen thì cảm thấy nhanh hơn WordPress nhiều hehe.

II. Xây dựng.
Bước 1: Tìm 1 theme Jekyll phù hợp
Một blog hay cũng phải đi kèm với Theme đẹp, bắt mắt đúng không ? Mình lại thích phong cách simple and clean nên có đưa ra 1 vài theme khuyên các bạn nên dùng.

Hyde
Poole
Kiko
Nếu các bạn muốn nhiều lựa chọn hơn thì có thể ghé thăm https://jekyll-themes.com/free/ để chọn nhiều giao diện hơn, tất nhiên có cả giao diện trả phí lẫn giao diện miễn phí.

Ở đây mình sử dụng giao diện Kiko-now, cũng tiện đưa vào bài viết làm ví dụ luôn.

Bước 2: Xiên (Fork) theme về Github của bạn
Đầu tiên, hãy đăng nhập vào tài khoản Github của bạn.
Ở đây mình sẽ chọn theme Kiko, hãy truy cập vào trang mã nguồn của theme: https://github.com/aweekj/kiko-now
Cách Tạo 1 Blog Nhỏ Với Jekyll
Click vào nút Xiên (Fork) để tạo 1 bản sao ở Github của mình.
Sau khi đã Fork về, hãy vào phần Settings để đổi tên repository thành dạng <user>.github.io , trong đó <user> là tên đăng nhập Github của bạn. Sau đó click vào Rename là xong.
Cách Tạo 1 Blog Nhỏ Với Jekyll
ở đây mình sẽ đổi “kiko-now” thành “jh1nxd.github.io”, vì user của mình là jh1nxd.
Tiếp tục các bạn sửa file _config.yml
_config.yml
Các bạn lần lượt sửa baseurl, name , description , avatar theo ý muốn của bạn.

Ở phần baseurl, repository của bạn đặt tên như thế nào thì phải để giống như thế ở phần baseurl


 
Ví dụ: repository của bạn có tên là caodem thì mình để giá trị ở phần baseurl là /caodem và khi đó địa chỉ blog của bạn để truy cập sẽ có dạng: <username>.github.io/caodem

Cách Tạo 1 Blog Nhỏ Với Jekyll
Còn repository của bạn đã đặt tên là <username>.github.io thì ở phần baseurl để trống. khi đó địa chỉ truy cập blog là <username>.github.io.

Khi chỉnh sửa xong thì bạn nhớ Commit changes để lưu lại thay đổi. Sau đó các bạn vào <username>.github.io để xem trang blog của bạn đã lên sóng hay chưa.

>>Xem demo

Bước 3: Đăng bài viết lên blog của bạn.
Sửa file trực tiếp ngay trên Github khá bất tiện, ở đây mình khuyên các bạn nên sử dụng Prose.

Định dạng 1 bài đăng trên Jekyll là Markdown, HTML, các mã Liquid templating, có vài điều lưu ý sau:

Bài đăng sẽ nằm ở trông thư mục _posts. Các bạn nên xoá hết bài đăng cũ ở trong thư mục và bắt đầu viết bài mới.
Format bài đăng sẽ theo kiểu YYYY-MM-DD-tiêu đề bài viết.md, các bạn lúc viết bài thì nên sử dụng bảng mã Markdown Cheatsheet.
Ở mỗi bài viết sẽ phải có phần khai báo quan trọng gọi là Front Matter, là 1 khối chứa các thông tin, giá trị quan trọng, được viết giữa 2 dòng chứa 3 dấu gạch nối.
Ví dụ:
---
layout: post
title: Cách Tạo 1 Blog Nhỏ Với Jekyll
description: cách tạo 1 trang web tĩnh bằng Jekyll 1 cách chi tiết, dễ hiểu nhất.
tags: Caodem, Jekyll
permalink: /cach-tao-1-blog-nho-voi-jekyll/
---
III.Lời kết
Jekyll là 1 trình tạo trang “tĩnh”, có tốc độ load trang rất nhanh và bảo mật. Những bài viết được lưu dưới dạng Markdown (.md) nên rất dễ đọc, thân thiện với người dùng.Một ưu điểm nữa là web tĩnh sẽ cho phép website của bạn miễn nhiễm với các mã độc, sự tấn công của hacker chúng ta thường thấy trên các như WordPress. Hơn nữa mã nguồn được lưu ở phía Github nên sẽ tuyệt đối miễn phí 100%. Cái này là điểm mình thích nhất.

Các bạn có thể tuỳ biến nhiều hơn nữa trên Jekyll, nhưng đôi khi mã nguồn này còn có một số hạn chế nhất định. Vì là trang tĩnh, nên không thể thực thi yêu cầu bên phía máy chủ.

Một số link về Jekyll khá hữu ích:

https://jekyllrb.com/docs/
https://blog.webjeda.com/
Nếu bạn có thắc mắc, vấn đề gì thì hãy để lại bình luận ở phía dưới, chia sẻ bài viết nếu bạn thấy hay. Thanks for reading.