---
layout: page
title: Nginx - Gunicorn
subtitle: Tips for deploying Python applications with Nginx using Gunicorn
tag: [other, linux, devops]
---


Code chán rồi thì ta qua làm Devops luôn nhé. Bài này sẽ nói về sau khi ta code Django, Flask chán chê rồi thì làm sao đưa nó lên production.

Nói chung cái flow sẽ như thế này, tài liệu nhiều lắm ở đây chúng ta sẽ không lam man mà tập trung vào 1 số vấn dề quan trọng trong quá trình setup: 

<img src="https://miro.medium.com/max/3068/1*pNTf9tIEwnU72_dda7-ajg.jpeg"/>

# Gunicorn

# step 1 : setup gunicorn.service

### chạy thử  gunicorn

*flask*
```cmd
gunicorn --bind 0.0.0.0:8001 wsgi
```
*django*
```cmd
gunicorn --bind 0.0.0.0:8001 Wl_app_01.wsgi
```

### gunicorn.service:

*nếu là dự án django thì phải collectstatic*
*trong setting.py :*
```python 
STATIC_ROOT = os.path.join(PROJECT_ROOT, 'staticfiles')
```
chạy lệnh để collectstatic qua /staticfiles/: 
```python 
python manage.py collectstatic
```


```bash 
cd /etc/systemd/system
touch wl-app.service
``` 
**Content:**
```bash
[Unit]
Description=Gunicorn instance to serve wl-app
After=network.target

[Service]
User=apache
Group=apache
WorkingDirectory=/opt/wl-app-01
Environment="PATH=/opt/wl-app-01/venv/bin"
ExecStart=/opt/wl-app-01/venv/bin/gunicorn --workers 3 --bind 127.0.0.1:5003 -m 007 Wl_app_01.wsgi:application

[Install]
WantedBy=multi-user.target
```

**start service:**

```bash
systemctl enable wl-app # set enable, service sẽ tự khởi động cùng hệ thống (mất điện, sập server)
systemctl start wl-app
systemctl status wl-app

``` 

# step 2 : config nginx

```bash 
cd /etc/nginx/conf.d/
touch wl-app.conf
``` 

**Content:**
```bash
server {
    listen 80;
    server_name _; # server_name = _ sẽ chạy trên 0.0.0.0 , còn đúng ra sẽ bỏ domain vào vd: jav.vn.com;

    access_log  /var/log/nginx/wl-app-access.log;
    error_log  /var/log/nginx/wl-app-error.log;

    location / {
       proxy_send_timeout          600;
                proxy_read_timeout          600;
                send_timeout                600;
                proxy_set_header        Host            $host;
                proxy_set_header        X-Real-IP       $remote_addr;
                proxy_set_header        X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header        X-Forwarded-Port $server_port;
                proxy_set_header        X-Forwarded-Host $host;
       proxy_pass http://127.0.0.1:5003;   #port mở bằng service gunicorn
    }

     location /static/{
           alias /opt/wl-app-01/Wl_app_01/staticfiles/; #nhớ set dir vừa collectstatic
     }

}
``` 

```bash
sudo systemctl enable nginx.service
sudo systemctl start nginx.service
sudo systemctl status nginx.service
```

# Lỗi bất cập
## lỗi page admin: không đăng nhập được user admin khi sử dụng MongoDb backend:

Vẫn tạo superuser "root" như bình thường nhưng vẫn lỗi có thể là do

*trong collection auth_user thiếu trường id, cần thêm vào ở dạng NumberInt* 
query thử collection db.auth_user, xem có trường 'id' chưa, nếu chưa có thì thêm vào:

```bash
db.auth_user.updateOne({"username" : "root"}, {$set:{'id': NumberInt(1)}})
```


