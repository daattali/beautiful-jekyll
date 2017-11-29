---
layout: post
title: Sửa lỗi không hiển thị được unicode trên cmd của Window
image: img/2017-06-08-Tips/quicktip.jpg
tags: [Python, lap-trinh, program-language, Python-tips]
categories: [Dev-Python]
date: 2017-06-08
---

Bạn sử dụng ubuntu để code Python, bạn được hỗ trợ tối đa về các vấn đề liên quan đến mã hóa. Còn khi bạn dùng trên window thì sao ? Một số thứu sẽ không như mong muốn.

Với Ubuntu khi thực hiện lệnh trên terminal

```
Print("Xin chào, tôi đang code python...")
```

Kết quả sẽ hiển thị


> Xin chào, tôi đang code python...


Nhưng nếu bạn dùng hệ điều Window, các bạn sẽ nhận được kết quả:


>UnicodeEncodeError: 'charmap' codec can't encode character '\u1ea3' in position 2: character maps to <undefined>


Không sao, mọi thứ đều có thể giải quyết được:


**For Python 2 try:**
```
print unicode(string, 'unicode-escape')
```

**For Python 3 try:**
```
import os 
string = "002 Xin chào, tôi đang code python..." 
os.system('echo ' + string)
```

**Best solution:** try to install win-unicode-console: 

```
pip install win-unicode-console 
```

Sau khi cài xong, nhớ print thử một dòng xem kết quả hiển thị tiếng Việt trên cmd thế nào nhé :) 
