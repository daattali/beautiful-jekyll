---
layout: post
title: Khởi đầu với RESTful-API
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-12-REST/rest-bia.png
tags: [Python, lap-trinh, programming-language, Flask, RESTful-API]
categories: [Dev-Python]
date: 2018-03-11
---

I. Khái niệm về REST - API
**RESTful - API**: RESTful API là một tiêu chuẩn dùng trong việc thết kế các thiết kế API cho các ứng dụng web để quản lý các resource (CRUD).


![/img/2018-03-12-REST/RESTful-API-design.jpg](/img/2018-03-12-REST/RESTful-API-design.jpg)

**Resources:** Tài nguyên riêng của mỗi hệ thống. 

- Với facebook: Users/accounts, posts/notes/images, comments/likes/emotions
- Với Instagram: Photos, comments
- Với CMS/báo online: Bài viết, tranh ảnh, quảng cáo,...
- Với trang thương mại điện tử: Hàng hoá, người dùng, quảng cáo,...


Việc quản lý resourcess bao gồm: 
- Tạo mới một resource (create)
- Lấy thông tin một resource (read)
- Cập nhật một resource (update)
- Xoá một resource (delete)


**Web-API hoặc HTTP API:** Quy chuẩn cho việc hiển thị và trao đổi dữ liệu giữa các hệ thống tài nguyên web. 

 RESTful là một trong các web API được sử dụng phổ biến ngày nay

 **REST và REST(ful)**:

REST: Representational State Transfer

Ứng dụng thiết kế kiểu REST được gọi là RESTful.
(Một kiểu "ghép chữ" giống beauty --> beautiful)

REST là một công nghệ, bất kể ngôn ngữ nào cũng có thể tạo ra cấu trúc API.

Giao tiếp giữa các hệ thống là kiểu dữ liệu JSON, Gzip, ...

**Ví dụ:** API được xây dựng kiểu RESTful (thường được dùng để demo):

https://reqres.in/

(Các ví dụ xem trực tiếp trên website)

II. Kết hợp Python và REST


```python
import requests
```

## Get list of records


```python
# List users
```


```python
url = "https://reqres.in/api/users"
response = requests.get(url)
print(response.status_code)
print(response.text)
```

    200
    {"page":1,"per_page":3,"total":12,"total_pages":4,"data":[{"id":1,"first_name":"George","last_name":"Bluth","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/calebogden/128.jpg"},{"id":2,"first_name":"Janet","last_name":"Weaver","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/josephstein/128.jpg"},{"id":3,"first_name":"Emma","last_name":"Wong","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/olegpogodaev/128.jpg"}]}



```python
# List users by page
url = "https://reqres.in/api/users?page=2"
response = requests.get(url)
print(response.status_code)
print(response.text)
```

    200
    {"page":2,"per_page":3,"total":12,"total_pages":4,"data":[{"id":4,"first_name":"Eve","last_name":"Holt","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/marcoramires/128.jpg"},{"id":5,"first_name":"Charles","last_name":"Morris","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/stephenmoon/128.jpg"},{"id":6,"first_name":"Tracey","last_name":"Ramos","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/bigmancho/128.jpg"}]}



```python
# List users by page
url = "https://reqres.in/api/users?page=5"
response = requests.get(url)
print(response.status_code)
print(response.text)
```

    200
    {"page":5,"per_page":3,"total":12,"total_pages":4,"data":[]}


## Get single record


```python
# Get single user by id

url = "https://reqres.in/api/users/4"
response = requests.get(url)
print(response.status_code)
print(response.text)

```

    200
    {"data":{"id":4,"first_name":"Eve","last_name":"Holt","avatar":"https://s3.amazonaws.com/uifaces/faces/twitter/marcoramires/128.jpg"}}


## PUT (update) single record 


```python
data = {"first_name":"Eve","last_name":"Holts"}
url = "https://reqres.in/api/users/4"

response = requests.put(url, data=data)
print(response.status_code, response.text)

```

    200 {"first_name":"Eve","last_name":"Holts","updatedAt":"2018-03-13T16:06:41.344Z"}





    '{"first_name":"Eve","last_name":"Holts","updatedAt":"2018-03-13T16:06:41.344Z"}'



## POST (create) single record


```python
data = {"first_name": "vinh", "last_name": "nguyen"}
url = "https://reqres.in/api/users"
response = requests.post(url, data=data)
print(response.status_code, response.text)


```

    201 {"first_name":"vinh","last_name":"nguyen","id":"21","createdAt":"2018-03-13T16:14:00.109Z"}


## DELETE single record


```python
url = "https://reqres.in/api/users/4"
response = requests.delete(url)
print(response.status_code, response.text)
```

    204 


### Header 


```python
print(response.headers)
```

    {'Date': 'Tue, 13 Mar 2018 16:16:18 GMT', 'Content-Type': 'application/json; charset=utf-8', 'Transfer-Encoding': 'chunked', 'Connection': 'keep-alive', 'Set-Cookie': '__cfduid=dfd14bd66a7f0a95ae0e31af31d5135101520957778; expires=Wed, 13-Mar-19 16:16:18 GMT; path=/; domain=.reqres.in; HttpOnly', 'X-Powered-By': 'Express', 'Access-Control-Allow-Origin': '*', 'ETag': 'W/"86-9B5QK3TRVrioxat8SkBJMLV3PsU"', 'Expect-CT': 'max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"', 'Server': 'cloudflare', 'CF-RAY': '3fafcde2c892a51e-NRT', 'Content-Encoding': 'gzip'}



```python
header = {"Authorization": "Bearer " + "token"}
data = {"first_name": "vinh", "last_name": "nguyen"}
session = requests.session()
session.headers.update(header)

url = "https://reqres.in/api/users"
response = session.post(url, data="data")
print(response.status_code, response.text)
```

    201 {"id":"665","createdAt":"2018-03-13T16:23:46.218Z"}