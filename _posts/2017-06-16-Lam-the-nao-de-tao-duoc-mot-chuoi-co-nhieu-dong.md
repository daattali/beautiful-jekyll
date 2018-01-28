---
layout: post
title: Làm thế nào để tạo được một chuỗi có nhiều dòng ?
subtile: Way to create a long multi-line string
image: /img/2017-12-01-Tips/quicktip.jpg
tags: [Python, lap-trinh, programming-language, Python-tips]
categories: [Dev-Python]
date: 2017-06-16
---

Học đến phần string (chuỗi) trong python, gặp phải một vấn đề...làm thế nào để khai báo được 1 chuỗi gồm nhiều dòng trên python ? 

Ví dụ: Có chuỗi như sau

```
Nói một lời thôi, người ơi 
Người có nghe không 
Nói một lời thôi, người ơi 
Người có nghe không 
Người ơi người nói đi 
Em đừng như thế 
```

Cách stupid nhất mà tôi có thể nghĩ ra:

```Python
LYRICS = "Nói một lời thôi, người ơi\n" \
         + "Người có nghe không\n" \
         + "Nói một lời thôi, người ơi\n" \
         + "Người có nghe không\n" \
         + "Người ơi người nói đi\n" \
         + "Em đừng như thế"
```

Sau một hồi chỉnh chỉnh, sửa sửa, split à ơi các kiểu, cuối cùng đã ra kết quả:

```Python
LYRICS = ("Nói một lời thôi, người ơi\n"
          "Người có nghe không\n"
          "Nói một lời thôi, người ơi\n"
          "Người có nghe không\n"
          "Người ơi người nói đi\n"
          "Em đừng như thế")
```

