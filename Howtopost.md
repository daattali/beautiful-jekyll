# Cách tạo bài viết trên trang web

Tất cả các bài viết trên trang web sử dụng Markdown để format. Nếu bạn chưa biết dùng, tham khảo [Markdown.md](Markdown.md)

Có 2 cách để tạo 1 bài viết mới:

1. Sử dụng Bot do anh Tùng viết
2. Tự viết theo chuẩn và upload lên đúng chỗ

Dùng cách nào thì bước cuối cùng vẫn cần người khác review. Nếu bạn muốn review hoặc được yêu cầu review, tham khảo phần cuối của tài liệu này để biết cách làm.

### 1. Sử dụng Bot

Để thuận tiện cho người không chuyên về tech, anh Tùng đã chuẩn bị 1 cách để ai cũng có thể dễ dàng đăng bài lên web:

1. Đăng nhập Google Drive
2. Truy cập [Spreadsheet quản lý nội dung web](https://docs.google.com/spreadsheets/d/1_klF1Tj8HH3pd1A87oK7fNGGX9MfbrJ6KJY_9Z8rkgI/edit)
3. Chuyển sang sheet `Tin tức` hoặc `Bài viết` tùy nội dung muốn đăng
4. Điền thông tin vào các cột tương ứng
    - Cột A (Date): Đảm bảo date theo đúng format `yyyy/mm/dd`
    - Cột B (Title): Tiêu đề bài viết. KHÔNG sử dụng Markdown.
    - Cột C (Content): Nội dung bài viết sử dụng Markdown.
    - Cột D (Source): Tên nguồn tin. KHÔNG sử dụng Markdown
    - Cột E (SourceLink): URL dẫn đến tin gốc
5. Kiểm tra kỹ xem có typo hay format sai hay không
6. Click nút `Request Update` ở ô F1
7. Báo cho 1 team member khác review


### 2. Tự viết, tự upload (Advanced)

Với người đã quen thì làm cách này sẽ nhanh hơn 1 chút và có thể preview trên máy trước khi nhờ review.

1. Chuẩn bị môi trường preview trên máy local. Hướng dẫn xem ở [đây](https://help.github.com/en/github/working-with-github-pages/testing-your-github-pages-site-locally-with-jekyll)
2. Tạo 1 branch mới từ `master`:
```
$ git checkout master
$ git pull
$ git checkout -b post/new-post-yyyymmdd
```
3. Tạo 1 file mới trong thư mục `_posts/`.
    - Đảm bảo tên file theo đúng format `yyyy-mm-dd-title.md` (thay `title` bằng nội dung bất kỳ, hạn chế dùng tiếng Việt có dấu)
4. Trong file mới tạo, thêm nội dung sau vào đầu file:
```
---
layout: post
title: Tiêu đề bài viết
category: news hoặc thematic
---
```
    - Chú ý `category`: dùng `news` nếu muốn đăng trong mục Tin tức, `thematic` nếu muốn đăng trong mục Bài viết
5. Viết nội dung và format bằng Markdown
    - Chú ý phải có link ghi rõ nguồn bài tin ở dưới cùng nếu là tin sưu tầm
6. Save file, truy cập địa chỉ `127.0.0.1:4000`, tìm và review kết quả
7. Commit và push
```
$ git add _posts/new-post-yyyymmdd
$ git commit -m "Add new post yyyymmdd"
$ git push -u origin post/new-post-yyyymmdd
```
8. Truy cập [GitHub repository](https://github.com/thongtincovid19/thongtincovid19.github.io)
9. Tạo 1 Pull Request. Hướng dẫn xem ở [đây](https://help.github.com/en/desktop/contributing-to-projects/creating-an-issue-or-pull-request#creating-a-new-pull-request)
    - Chú ý chọn branch đích là repo của team (`thongtincovid19`), không phải repo gốc (`BeautifulJekyll`)
10. Báo cho 1 team member khác review

### 3. Nếu bạn là reviewer

1. Truy cập Pull Request muốn review
2. Chuyển sang tab `Files Changed`
3. Review nội dung thay đổi
    - Nếu có môi trường preview trên máy local, hãy checkout branch tương ứng về và preview trước.
    - Chú ý phía trên bên phải có 1 nút `Review changes` màu xanh. Bạn có thể thực hiện bước 4-5 ở đây.
4. Nếu có vấn đề: comment, Request Changes và báo lại cho tác giả
5. Nếu thấy ổn: Approve
6. Chuyển về tab `Conversation`, kéo xuống dưới và click Merge
7. Đợi 30s - 1p và check lại kết quả trên trang web chính thức.