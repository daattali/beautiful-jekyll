
# Cách preview trang web trước khi đăng bài chính thức

Trước khi post bài hay thay đổi 1 chức năng trên web, mình (Nghĩa) khuyến khích mọi người preview trước xem khi lên môi trường thực tế trông sẽ thế nào.  
Dưới đây là hướng dẫn cụ thể cách dựng môi trường web trên máy tính và hướng dẫn preview 1 pull request trên máy.

## Cài đặt môi trường (30p):

_Đối tượng: người không có background về kỹ thuật, máy tính chưa từng cài môi trường lập trình Ruby. Nếu bạn có background kỹ thuật, hãy tự search Google "GitHub Pages local build"._

1. Nếu bạn dùng Windows: download [Git for Windows]([https://gitforwindows.org/](https://gitforwindows.org/)) và cài đặt (chỉ cần Next đến hết).
- Để chạy chương trình mới cài, bạn vào Start Menu và tìm "Git Bash". ![Find Git](/img/find_git.png)
- Từ dưới đây sẽ gọi Git Bash là "terminal" để đồng nhất với Mac/Linux.

2. Cài đặt Ruby (bỏ qua nếu trên máy bạn đã có sẵn Ruby):
- Windows: Download và cài đặt [Ruby Installer](https://github.com/oneclick/rubyinstaller2/releases/download/RubyInstaller-2.6.6-1/rubyinstaller-devkit-2.6.6-1-x64.exe).
- Mac/Linux: Dùng [RVM](http://rvm.io/)

3. Cài đặt Bundle:
- Gõ lệnh sau vào terminal: `$ gem install bundler`
  - Chú ý không gõ dấu `$`.
  - Ở dưới nhìn thấy cú pháp tương tự bạn tự hiểu là phải gõ vào terminal. 
4. Lấy code từ GitHub về máy:
```
$ cd ~/Desktop
$ git config --global user.name "your name"
$ git config --global user.email "your.email"
$ git clone https://github.com/thongtincovid19/thongtincovid19.github.io.git
```
Thư mục `thongtincovid19.github.io` sẽ được tạo ở Desktop, chứa toàn bộ các file của dự án.

5. Cài đặt Jekyll
- Mac/Linux: mở file `Gemfile` trong thư mục dự án, tìm dòng `gem 'tzinfo-data', platforms: [:mingw, :mswin, :x64_mingw]` (dòng 2 từ dưới lên) và thêm dấu `#` đằng trước.
- `$ gem install tzinfo-data`
- `$ bundle install`

6. Bật trang web trên máy cá nhân
- `$ bundle exec jekyll serve`
- Không tắt terminal, truy cập vào trang web http://127.0.0.1:4000/

Từ sau bước 6, nếu terminal vẫn chạy thì bất kỳ thay đổi gì bạn thực hiện trên các file trong thư mục dự án sẽ được phản ánh ngay lập tức lên trang web trên máy bạn. Trang web chính thức sẽ không bị ảnh hưởng.

Để dừng chạy web trên máy, bạn quay lại terminal và nhấn `Ctrl+C`.

Từ lần chạy web thứ 2 trở đi, chỉ cần chạy lại bước 6 là được.

## Preview 1 pull request

Pull Request đơn giản là 1 thay đổi mà bạn hay 1 người khác đã thực hiện và muốn đưa lên trang web chính thức. Sau khi cài đặt và chạy website trên máy, để preview (xem trước) chỉ cần làm như sau:

1. Đảm bảo là terminal đang chạy trong thư mục dự án
```
$ cd ~/Desktop/thongtincovid19.github.io
```
2. Lấy code của Pull Request
```
$ git checkout pull-request-branch
```
Thay `pull-request-branch` bằng thông tin lấy từ pull request: ![branch name](/img/branch_name.png)

3. Truy cập vào trang web http://127.0.0.1:4000/ để xem thay đổi
- Có 1 số Pull Request cần phải chạy lại cả `$ bundle exec jekyll serve` thì mới thấy được thay đổi.

## Đưa thay đổi của bạn lên web chính thức

Nếu bạn đã làm 1 chức năng mới hoặc bài post mới, đã preview ưng ý trên máy cá nhân, bạn có thể sử dụng terminal để "commit" chức năng/post mới lên GitHub để người khác review và đưa lên web chính thức. Xem chi tiết bên [Howtopost.md](Howtopost.md)