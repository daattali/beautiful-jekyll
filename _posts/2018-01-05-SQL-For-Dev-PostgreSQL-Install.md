---
layout: post
title: SQL cơ bản cho lập trình viên - Cài đặt PostgreSQL
image: /img/2018-01-05-TSQL/t-sql-mini-logo.jpg
tags: [lap-trinh, programming-language, T-SQL, PostgreSQL]
categories: [Dev-Database]
date:   2018-01-05

---
**SQL (Structured Query Language)**  hay ngôn ngữ truy vấn mang tính cấu trúc, là một loại ngôn ngữ máy tính phổ biến để tạo, sửa, và lấy dữ liệu từ một hệ quản trị cơ sở dữ liệu quan hệ (DBMS - Database Management System).

# SQL & DBMS
Các hệ quản trị cơ sở dữ liệu quan hệ thường gặp: 
- Microsoft SQL Server
- Oracle database
- MySQL
- SQLite
- PostgreSQL
- DB2, Lotus,...

T-SQL viết tắt của Transaction - SQL là một kiểu ngôn ngữ lập trình database hướng thủ tục được xây dựng bởi Microsoft và ban đầu là dành riêng cho MS SQL Server.

Sau này T-SQL được mở rộng và trở thành một loại ngôn ngữ dùng chung cho hầu hết các DBMS. Tất nhiên là mỗi DBMS sẽ có một số lệnh khác do cấu trúc DBMS.

# PostgreSQL

**PostgreSQL**: là một DBMS được xây dựng bởi một nhóm có tên *The PostgreSQL Global Development Group* có bản có phí và miễn phí. Hai phiên bản khác nhau về support từ nhà cung cấp. Bản miễn phí không được support từ nhà cung cấp và bị giới hạn về các công cụ đi kèm.

PostgreSQL cung cấp đầy đủ các tính năng của một DBMS lớn như cung cấp từng space, khả năng backup - recover, backlog,...

**Download:**

<https://www.postgresql.org/download/>

Nên sử dụng bản 10.

Với windows:

<https://www.enterprisedb.com/downloads/postgres-postgresql-downloads#windows>


![01_Download_Postgres.png](/img/2018-01-05-TSQL/01_Download_Postgres.png)

**Install:**

Việc cài đặt trên windows khá dễ dàng với các thao tác next, next


![_Postgres.png](/img/2018-01-05-TSQL/02_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/03_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/04_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/05_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/06_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/07_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/08_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/09_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/10_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/11_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/12_Postgres.png)


Download bổ sung các extension (có thể bỏ qua)


**Phương thức hoạt động**

PostgreSQL Hoạt động theo mô hình client/server
- Server process: quản lý database files, nhận kết nối từ clients, thực hiện các hoạt động trong database -> các process có tên postgres
- Các ứng dụng client: kết nối đến server qua giao tiếp TCP/IP

Khi có 1 connection mới, 1 process được tạo ra để phục vụ cho connection đó, để không phụ thuộc vào master server process

Các tool quản trị PostgreSQL:

– psql: chương trình quản trị bằng dòng lệnh

– pgAdmin: chương trình quản trị dùng giao diện đồ họa

– 3rd party tools


**Giới thiệu các pgAdmin**

![_Postgres.png](/img/2018-01-05-TSQL/15_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/16_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/17_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/18_Postgres.png)


Tạo mới một database:
![_Postgres.png](/img/2018-01-05-TSQL/19_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/20_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/21_Postgres.png)

![_Postgres.png](/img/2018-01-05-TSQL/22_Postgres.png)


Tạo mới một table:

![_Postgres.png](/img/2018-01-05-TSQL/23_Postgres.png)
![_Postgres.png](/img/2018-01-05-TSQL/24_Postgres.png)





