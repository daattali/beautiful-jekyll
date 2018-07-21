---
layout: post
title: String Python-basic-examples
# subtile: Hãy viết code như một Pythonista
image: /img/2017-06-08-Tips/quicktip.jpg
tags: [Python, Python-basic, Python-trick]
categories: [Python-basic]
date: 2018-07-20
# 2018-07-14-PE025-1000-digit-Fibonacci-number.md
---
Một số ví dụ khá hay về String trong Python mà ít ngôn ngữ lập trình khác có được.


## String-Python

Trong các ngôn ngữ lập trình thì phần xử lý chuỗi (string) là khá quan trọng. Phần lớn các thao tác xử lý bằng ngôn ngữ lập trình là  xử lý chuỗi. 

### Format string

Ví dụ có 2 trường dữ liệu sau: 

```Python
name = "Vinh.nguyenquang"
job = "Developer"
city = "Hanoi"
```

Để thu được một chuỗi dữ liệu name-job-city thì cách cơ bản nhất:

```Python
title = name + "-" + job + "-" + city

print(title)
```

>Vinh.nguyenquang-Developer

Python3 cung cấp function format của chuỗi để thực hiện tạo thành các chuỗi mới.

Dưới đây là một số ví dụ về function format:

```Python
title= "{}-{}-{}".format(name, job, city)

title = "{0}-{1}-{2}".format(name, job, city)

title= "{name}-{job}-{city}".format(name=name, job=job, city=city)


```

Theo Python docs thì công thức của format string:

>string = template.format(*args, **kwargs)

```Python
args = [name, job, city]
title = "{0}-{1}-{2}".format(*args)

title = "{}-{}-{}".format(*args)

```


```Pythonn
kwargs = {
    "name": name,
    "job": job, 
    "city": city}

title= "{name}-{job}-{city}".format(**kwargs)

```

Một cách tổng hợp hơn, chúng ta có thể thực hiện format dữ liệu như sau:

```Python
args = ['32', 'Python', 'Oracle']

kwargs = {
    "name": name,
    "job": job, 
    "city": city}

title= "{name}-{}-{job}-{city}-main skill: {}-{}".format(*args, **kwargs)


```

Kết quả của công thức format này:

>'Vinh.nguyenquang-32-Developer-Hanoi-main skill: Python-Oracle'

### Join iterator data to string

Trong string Python cung cấp một function khá thú vị mà ít ngôn ngữ lập trình nào có.


Chúng ta có một list (hoặc một set), chúng ta muốn nối tất cả các phần tử của chúng lại và cách nhau bởi một ký tự nào đó.

Ví dụ:

```
work_days = ["Mon", "Tue", "Wed", "Thu", "Fri"]
avaiable_days = "-".join(work_days) 
```

Kết quả thu được

>Mon-Tue-Wed-Thu-Fri


```
args = ('Vinh', 'Developer', 'Hanoi', '32', 'Python', 'Oracle')
title = "-".join(args)

```

>Vinh-Developer-Hanoi-32-Python-Oracle

