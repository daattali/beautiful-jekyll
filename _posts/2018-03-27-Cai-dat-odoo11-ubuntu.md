---
layout: post
title: Cài đặt Odoo11
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-27-odoo/biaOdoo.png
tags: [Python, lap-trinh, programming-language, Odoo-11]
categories: [Dev-Odoo]
date: 2018-03-27
---

# Hướng dẫn cài đặt Odoo11 trên Ubuntu 16.4

**Bước 1:** Cập nhật apt source lists

```bash
sudo apt-get update
sudo apt-get upgrade
```

apt (Advance package tool) một dự án lớn chứa các gói phần mềm dành cho Debian và Ubuntu.

apt-get giao diện command-line của dự án (khác với giao diện GUI)

apt-get gồm có các lệnh sau: 

```
vinhnq@VINHNQ:~$ apt-get 
autoclean        check            dselect-upgrade  source
autoremove       clean            install          update
build-dep        dist-upgrade     purge            upgrade
changelog        download         remove        
```


**Bước 2:** Cài đặt các gói liên quan của Odoo trong ubuntu (Odoo Web Dependencies):
```
sudo apt-get install -y npm
sudo ln -s /usr/bin/nodejs /usr/bin/node
sudo npm install -g less less-plugin-clean-css
sudo apt-get install -y node-less
```

Các gói Odoo Web Dependencies dùng để hiển thị giao diện web của Odoo tốt hơn.

**Bước 3:** Cài đặt PostgreSQL và tạo user odoo để thực hiện quản trị cơ sở dữ liệu Odoo.

Cài đặt PostgreSQL: Search google

Tạo user Odoo trong postgresql

```
sudo service postgresql start

sudo su - postgres

createuser --createdb --username postgres --no-createrole --no-superuser --pwprompt odoo

```
```
Enter password for new role: *****
Enter it again:*****

exit
```

--> Nhớ password để  sau còn dùng.


**Bước 4:** Update một số lỗi "ngớ ngẩn" của hệ điều hành và postgre


**Bước 5:** Cài đặt pip3 cho Ubuntu

```
sudo apt-get install -y python3-pip

```

**Bước 6:** Cài đặt các package của Python:

```
pip3 install Babel decorator docutils ebaysdk feedparser gevent greenlet
pip3 install html2text Jinja2 lxml Mako MarkupSafe mock num2words ofxparse
pip3 install passlib Pillow psutil psycogreen psycopg2 pydot pyparsing PyPDF2
pip3 install pyserial python-dateutil python-openid pytz pyusb PyYAML qrcode
pip3 install reportlab requests six suds-jurko vatnumber vobject Werkzeug
pip3 install XlsxWriter xlwt xlrd 
```

**Bước 7:** Cài đặt git nếu chưa có

```
sudo apt-get install -y git

```


Đi đến vị trí đặt project. Thực hiện clone project về:
```
git clone https://www.github.com/odoo/odoo --depth 1 --branch 11.0 --single-branch
```

--> nhớ vị trí đặt project để sau còn cho vào file config.

**Bước 8:** Tạo thư mục log cho ứng dụng
```
sudo mkdir /var/log/odoo
```
--> nhớ vị trí đặt log để sau còn cho vào file config.

**Bước 9:** Tạo file config: 
Từ vị trí đặt project đi đến đường dẫn:  /odoo/debian

Sử dụng trình editor bất kỳ bằng quyền root để mở file
```
sudo nano odoo.conf
```

Điền nội dung như bên dưới: 

```
[options]
; This is the password that allows database operations:
; admin_passwd = admin
db_host = 127.0.0.1 
db_port = 4532 
db_user = odoo
db_password = 12345678
logfile = /var/log/odoo/odoo-server.log
addons_path = /home/vinhnq/Projects/Odoo/Odoo11/odoo/addons
```

Đóng file lại.

**Bước 10:**
Copy file config vừa xong, để  vào vị trí
/etc/odoo.conf


**Bước 11:**
Khởi tạo môi trường test Odoo:

Đứng từ thư mục chứa Odoo code đã download về từ bước trước(thư mục chứa odoo-bin)

```
./odoo-bin
```

```
vinhnq@VINHNQ:~/Projects/Odoo/Odoo11/odoo$ ./odoo-bin
[]
2018-03-27 17:09:54,846 13368 INFO ? odoo: Odoo version 11.0
2018-03-27 17:09:54,846 13368 INFO ? odoo: addons paths: ['/home/vinhnq/.local/share/Odoo/addons/11.0', '/home/vinhnq/Projects/Odoo/Odoo11/odoo/odoo/addons', '/home/vinhnq/Projects/Odoo/Odoo11/odoo/addons']
2018-03-27 17:09:54,846 13368 INFO ? odoo: database: default@default:default
2018-03-27 17:09:54,879 13368 INFO ? odoo.service.server: HTTP service (werkzeug) running on 0.0.0.0:8069
2018-03-27 17:09:55,384 13368 INFO ? odoo.addons.base.ir.ir_actions_report: Will use the Wkhtmltopdf binary at /usr/local/bin/wkhtmltopdf
````

**HTTP service (werkzeug) running on 0.0.0.0:8069**

Mở đường dẫn tại: 127.0.0.1:8069


---------------
Nếu có lỗi =)) 
Thực hiện các bước dưới đây:


**Bước x+1 :**  tạo user odoo - gắn vào group odoo

```
sudo adduser --system --home=/opt/odoo --group odoo
```

Chuyển sang sử dụng user của user mới tạo:

```
sudo su - odoo -s /bin/bash
```

Thực hiện install các package Python cho user mới tạo:

```
pip3 install Babel decorator docutils ebaysdk feedparser gevent greenlet
pip3 install html2text Jinja2 lxml Mako MarkupSafe mock num2words ofxparse
pip3 install passlib Pillow psutil psycogreen psycopg2 pydot pyparsing PyPDF2
pip3 install pyserial python-dateutil python-openid pytz pyusb PyYAML qrcode
pip3 install reportlab requests six suds-jurko vatnumber vobject Werkzeug
pip3 install XlsxWriter xlwt xlrd 
```

copy đường dẫn của odoo từ chỗ download git về thư mục gốc của user odoo.
```
sudo cp -r Odoo11/odoo/ /opt/odoo/
```

Mở file config /opt/odoo/odoo/debian/odoo.conf

```
[options]
; This is the password that allows database operations:
db_host = localhost
db_port = 5432 
db_user = odoo
db_password = 12345678
logfile = /var/log/odoo/odoo-server.log
addons_path = /opt/odoo/odoo/addons
```

Save as file này vào thư mục etc
```
sudo chown odoo: /etc/odoo-server.conf
sudo chmod 640 /etc/odoo-server.conf
```

Thực hiện chuyển vào user odoo
```
sudo su - odoo -s /bin/bash
ls
cd odoo
ls
./odoo-bin

```

Lúc này...sẽ mở được link với đường dẫn: 
http://127.0.0.1:6089

và ra giao diện như sau:

![20.png](/img/2018-03-27-odoo/Selection_020.png)

Sau khi nhập dữ liệu và làm như các bước trên, nhấn vào "Create database"

![21.png](/img/2018-03-27-odoo/Selection_021.png)

