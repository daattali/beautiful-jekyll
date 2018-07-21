---
layout: post
title: Kiểu dữ liệu Boolean trong  Python
# subtile: Hãy viết code như một Pythonista
image: /img/2017-06-08-Tips/quicktip.jpg
tags: [Python, Python-basic, Python-trick]
categories: [Python-basic]
date: 2018-07-21
# 2018-07-14-PE025-1000-digit-Fibonacci-number.md
---
Một số điều khá thú vị về kiểu dữ liệu Boolean trong Python...


## Conditionals-Python

Điều kiện rẽ nhánh là xương sống của các chương trình phần mềm. Về cơ bản chỉ có 2 giá trị True/False sẽ quyết định khi nào chương trình đi theo hướng nào. 

Trong một số ngôn ngữ lập trình, bắt buộc phải quy chuẩn về True/False trong điều kiện rẽ nhánh, ở Python thì không cần vậy. 

### Phép toán logic:

Trong Python có các phép toán Logic so sánh để sinh ra giá trị Boolean cơ bản như các ngôn ngữ lập trình khác

```Python
value = 13
print(value == 13)
print(value != 13)
print(value > 5)
print(value < 15)
print(value >= 13)
print(value <= 13)
print(12<= value <= 13)
print(12< value < 14)
```


```
>>> value = 13
>>> print(value == 13)
True
>>> print(value != 13)
False
>>> print(value > 5)
True
>>> print(value < 15)
True
>>> print(value >= 13)
True
>>> print(value <= 13)
True
>>> print(12<= value <= 13)
True
>>> print(12< value < 14)
True
```

Ngoài ra Python còn cung cấp các toán tử khác như:
`is`, `is not`


```Python
>>> list_number_1 = [1, 2, 3]
>>> list_number_2 = [1, 2, 3]
>>> list_number_3 = list_number_1
>>> print(list_number_1 is list_number_2)
False
>>> print(list_number_1 is list_number_3)
True
>>> 
>>> print(id(list_number_1))
4326971208
>>> print(id(list_number_2))
4326955912
>>> print(id(list_number_3))
4326971208
>>> 

```

Nhìn vào ví dụ trên, ta thấy về giá trị thì list_number_1, list_number_2, list_number_3 hoàn toàn giống nhau nhưng `id()` thì không. 

Phép toán so sánh `is` được dùng so sánh bởi các giá trị `id()` 

```Python
>>> list_number_3.append(4)
>>> print(list_number_1 is list_number_3)
True
>>> list_number_3
[1, 2, 3, 4]
>>> 
```

==> Hạn chế dùng phép toán so sánh `is` trong Python.

### Dữ liệu Boolean trong Python:

Ngoài True/False thông dụng thì còn có thể sinh ra dữ liệu Boolean bằng các cách:

Dữ liệu collection:

```Python

>>> empty_list = []
>>> bool(empty_list)
False

>>> empty_set = ()
>>> bool(empty_set)
False

>>> empty_dic = {}
>>> bool(empty_dic)
False


>>> data_list = [1]
>>> bool(data_list)
True
>>> data_set = (1)
>>> bool(data_set)
True
>>> data_dict = {1}
>>> bool(data_dict)
True

```

Dữ liệu kiểu number:

```Python
>>> bool(1)
True
>>> bool(-1)
True
>>> bool(0)
False
>>> 

```

Dữ liệu kiểu string:

```Python
>>> bool("day la string")
True
>>> bool("")
False
>>> 

```

Dữ liệu None:
```Python
>>> bool(None)
False

```

Toán tử `not`:
```Python
>>> bool(not True)
False

>>> bool(not False)
True
```

Toán tử `in`:
```Python
>>> numbers = [1, 2, 3, 4]
>>> number = 1
>>> bool(number in numbers)
True
>>> number_2 = 5
>>> bool(number_2 in numbers)
False
>>> bool(number_2 not in numbers)
True

```


### Phép toán so sánh phức hợp
Có một ví dụ về so sánh và rẽ nhánh như sau:

```Python
weather = "Sunny"
if weather == "Rain" or weather == "Snow":
    umbrella = True
else:
    umbrella = False

print("weather: {}-umbrella: {}".format(weather, umbrella))

```

Có thể viết một cách ngắn ngọn hơn:

```Python
weather = "Sunny"
umbrella = weather == "Rain" or weather == "Snow"
print("weather: {}-umbrella: {}".format(weather, umbrella))
```

