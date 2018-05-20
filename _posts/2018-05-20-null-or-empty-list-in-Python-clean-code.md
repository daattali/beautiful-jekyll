---
layout: post
title: Trả về 'none' hay 'empty' list trong Python
# subtile: Hãy viết code như một Pythonista
image: /img/2018-05-20-clean-code/cleancode.jpg
tags: [Python, lap-trinh, programming-language, Pythonista, Clean-Code]
categories: [Dev-Python]
date: 2018-05-20
---


**Return ???**: Khi viết một function, một lập trình viên luôn phải nghĩ nên trả về cái gì là hợp lý.
Nhân dịp đọc lại cuốn clean-code lần thứ N, đọc đến đoạn NullPointerException trong Java, chợt nghĩ ra với Python thì thế nào. 

Câu chuyện như này:
- A gọi B 
- B truy suất vào DB lấy ra list các bản ghi trong DB.


```Python

db = EmployeesDB()
employees = db.get_employees()
for employee in employees:
    # do something

```

- Nếu không có bản ghi nào trong DB, db.get_employees() nên trả về cái gì ? None hay []
Thường các lập trình viên sẽ trả lời: "kiểm tra None ở `employees`, cần gì quan tâm đến việc nó trả về cái gì. Vì python thì `None` hay `[]` đều là `False`"


```Python

db = EmployeesDB()
employees = db.get_employees()
if employees:
    for employee in employees:
        # do something

```

Cũng không tệ nếu như bạn là người code `db.get_employees()` và sau này chỉ có bạn dùng đến nó.
Nếu làm theo nhóm và có ai đó sẽ dùng đến code của bạn và họ không biết phải đặt đoạn `if not employees:` trong code. Thật tệ khi chạy chương trình sẽ trả về: 
```
'Nonetype' object is not iterable
```

Vậy hãy viết code `db.get_employees()` trả về [] khi không lấy được dữ liệu từ DB nhé.

```Python
# EmployeesDB class

def get_employees():
    # do something and return list of record
    # if nothing to return, return empty list
    return []

```


Tương tự như vậy với dictionary, hãy trả về với một dict rỗng chứ đừng trả về None
