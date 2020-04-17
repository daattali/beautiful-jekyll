# Hướng dẫn sử dụng Markdown

Markdown là 1 dạng syntax dùng để format văn bản. Nhờ ưu thế cách viết đơn giản,
không yêu cầu tool chuyên dụng nên Markdown rất được ưa chuộng khi viết văn bản/message đơn giản.

File Markdown có đuôi là `.md`.

Trong project này bạn có thể sử dụng Markdown để:

1. Tạo bài viết (post)
2. Viết các tài liệu nội bộ như tài liệu này
3. Format nội dung trên [Trello](https://trello.com/b/ZLdoryby/dashboard)

---

## 1 số syntax thường dùng trong Markdown

- Heading: `#[space][heading text]`
    - VD: `# Hướng dẫn sử dụng Markdown` => (xem trên đầu trang)
    - Dấu '#' phải đứng đầu dòng
    - 1 dấu '#' tương ứng với Heading 1 trong Google Docs hoặc MS Docs (to tướng). 2 dấu '##' là Heading 2 ... đến Heading 6
- Xuống dòng: Xuống dòng 2 lần hoặc thêm 2 dấu cách vào cuối dòng
- In đậm:  `**[text]**` hoặc `__[text]__`
    - VD: `**stars**, __underscores__` => **stars**, __underscores__
    - Có thể dùng ở bất cứ đâu, không nhất thiết là đầu dòng
    - Chú ý trước và sau text không được có khoảng trống
- In nghiêng: `*[text]*` hoặc `_[text]_`
    - VD: `*stars*, _underscores_` => *stars*, _underscores_
    - Có thể dùng ở bất cứ đâu, không nhất thiết là đầu dòng
    - Chú ý trước và sau text không được có khoảng trống
- Bullet list: `-[space][text]` hoặc `*[space][text]`
    - VD: `* Bullet list`
    - Nếu muốn thêm 1 layer con thì lùi đầu dòng của layer con
- Numbered list: `[number][dot][space][text]`
    - VD: `1. Point 1`
    - Nếu muốn thêm 1 layer con thì lùi đầu dòng của layer con
    - Có thể dùng kết hợp với Bullet list
- Link: `['['][Displayed text][']']['('][URL][')]`
    - VD: `[Báo Nikkei](https://www.nikkei.com/)` => [Báo Nikkei](https://www.nikkei.com/)
    - Chú ý giữa ngoặc vuông và ngoặc tròn không được có khoảng trống
- Ảnh: `['!']['['][Alt text][']']['('][URL][')']`
	- VD: `![see me](https://(shortened)/256px-Facebook_icon.svg.png)` => ![see me](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Facebook_icon.svg/256px-Facebook_icon.svg.png)
    
Còn nhiều syntax khác, có thể tham khảo tại [đây](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) hoặc [đây](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf).

---

## Convert Google Docs thành Markdown

Nếu bạn không quen sử dụng Markdown thì project có chuẩn bị 1 cách để bạn có thể edit nội dung trên Google Docs rồi sinh ra Markdown tương ứng:

1. Login vào Google Drive với account `thongtincovid19jp@gmail.com`
2. Mở file [Doc2Markdown](https://docs.google.com/document/d/14faU-SCcowvbGhuNyluvc1B6zx42fQoq4Y7LPJp-FGU/edit)
3. Xóa toàn bộ nội dung của file
4. Soạn thảo văn bản bạn muốn và chỉnh sửa format bằng Google Docs như bình thường. Chú ý không thay đổi tên file.
5. Sau khi xong, chọn `Custom Scripts > Convert to Markdown` từ thanh Menu
6. Check mail `thongtincovid19jp@gmail.com` sẽ có 1 email tiêu đề `[MARKDOWN_MAKER] Doc2Markdown` với 2 file đính kèm.
7. Click vào file `Docs2Markdown.md`, nội dung file sẽ hiển thị trong browser.
8. Copy&paste vào chỗ bạn muốn.

Script được viết bởi [Renato Magini](https://github.com/mangini/gdocs2md?fbclid=IwAR1Te3wGR-doE1Fc8I0w3ilGEWEhkQbTFxV6YHEhu_zmaefOXsIx9GGd4Dc), cựu nhân viên Google.
Chỉnh sửa bởi Nghĩa.