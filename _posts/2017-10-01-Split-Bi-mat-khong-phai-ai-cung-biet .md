---
layout: post
title: Split() và Split(" ") khác nhau như thế nào ?
#subtile: Way to create a long multi-line string
image: /img/2017-12-01-Tips/GoodIdea.jpg
tags: [Python, lap-trinh, programming-language, Python-tips]
categories: [Dev-Python]
date: 2017-10-01
---

Muốn chia một chuỗi thành các chuỗi con theo các dấu phân cách khác nhau, ta sẽ dùng hàm split(). Muốn chia chuối thành các chuỗi con với delimiter (dấu phân cách) là khoảng trống, ta sẽ làm như thế nào ?

Ví dụ: Có chuỗi như sau
```Python
new_string = "Toi la toi  dung mong    doi thay   toi lam gi"
```

Yêu cầu: Chia chuỗi thành các chữ khác nhau. Mỗi chữ sẽ cách nhau bởi khoảng trắng.

Thông thường, ta sẽ gặp cách sử dụng như sau: 

```Python
>>> list1 =  my_string.split(' ')
['Toi', 'la', 'toi', '', 'dung', 'mong', '', '', '', 'doi', 'thay', '', '', 'toi', 'lam', 'gi']

```
Oh! Trong list1 có chứa các "chuỗi" con là các chuỗi rỗng. Nguyên nhân do trong my_string có những khoảng có nhiều hơn 1 khoảng trắng. 

Để xử lý các empty string và đếm số từ chẳng hạn, ta sẽ phải thêm một vài dòng code nữa. 
Việc này thật nhàm chán và vô vị. Python cung cấp giải pháp cho chúng ta luôn này.

```Python
>>> list2 = my_string.split()
['Toi', 'la', 'toi', 'dung', 'mong', 'doi', 'thay', 'toi', 'lam', 'gi']
```

Như vậy hàm split() sẽ tự động thực hiện thêm nhiệm vụ loại bỏ các khoảng trắng vô nghĩa về mặt ngữ nghĩa.

Tuy nhiên tùy từng trường hợp mà dev cần phải tỉnh táo và linh động để quyết định sử dụng split(' ') hay split() nhé.

Dưới đây là một ví dụ ... không thể dùng split() được mà bắt buộc phải dùng split(' ').

>Thực hiện viết hoa mỗi chữ cái đầu tiên của mỗi từ trong chuỗi --> Cần trả lại nguyên trạng các vị trí từ trong chuỗi.



**Note:** Có thể bạn đã biết.

Ngoài split() thì Python cũng cung cấp cho người dùng một hàm nữa là splitline() --> thực hiện chia một chuỗi thành nhiều dòng khác nhau. Vậy liệu split("\n") và splitlines() có khác nhau không ? 

_Đừng nghĩ, hãy làm_


```Python
LYRICS = ("Nói một lời thôi, người ơi\n"
          "Người có nghe không\n"
          "Nói một lời thôi, người ơi\n"
          "Người có nghe không\n"
          "Người ơi người nói đi\n"
          "Em đừng như thế")
my_list1 = LYRICS.splitlines()
my_list2 = LYRICS.split("\n")
my_list1 == my_list2
True
```
Kết quả nhận được là True --> hai hàm này chức năng như nhau.

Để xem nếu thêm một blank line thì có ra kết quả khác nhau không nhé.


```Python
LYRICS = ("Nói một lời thôi, người ơi\n"
          "\n"
          "Người có nghe không\n"
          "Nói một lời thôi, người ơi\n"
          "Người có nghe không\n"
          "Người ơi người nói đi\n"
          "Em đừng như thế")
my_list1 = LYRICS.splitlines()
my_list2 = LYRICS.split("\n")
my_list1 == my_list2
True
```

Vẫn True --> có thể dùng splitlines thay vì dùng split("\n").

Bravo Python!