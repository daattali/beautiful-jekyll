---
layout: post
title: Tạo một ứng dụng đơn giản bằng Python - Flask
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-16-Flask/flask.png
tags: [Python, lap-trinh, programming-language, Flask, RESTful-API]
categories: [Dev-Python]
date: 2018-03-16
---

# Xây dựng ứng dụng quản lý contact bằng flask

## Về cơ sở dữ liệu

Sử dụng cơ sở dữ liệu SQLite3.

Tạo cơ sở dữ liệu SQLite3 có tên contact.db

Dùng script sau để tạo bảng dữ liệu Contacts

```SQL
CREATE TABLE `Contacts` (
	`ContactId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`Name`	TEXT NOT NULL,
	`Phone`	TEXT,
	`Address`	TEXT
);
```


## Về form mẫu:

Trang home sẽ hiển thị danh sách các contact đang có trên hệ thống/

![home.png](/img/2018-03-16-Flask/home.png)

Trang thêm mới một contact

![Add_phone.png](/img/2018-03-16-Flask/Add_phone.png)


![MODIFIES.png](/img/2018-03-16-Flask/update_phone.png)

![MODIFIES.png](/img/2018-03-16-Flask/delete.png)

![MODIFIES.png](/img/2018-03-16-Flask/404.png)


sample code: [Github-quangvinh86](https://github.com/quangvinh86/flask-contact-management)