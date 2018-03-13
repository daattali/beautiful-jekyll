---
layout: post
title: Tạo nhanh một restful-api-bằng flask framework-P1
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-12-REST/rest-bia.png
tags: [Python, lap-trinh, programming-language, Flask, RESTful-API]
categories: [Dev-Python]
date: 2018-03-12
---

Tạo một ứng dụng RESTful-API nhỏ bằng Flask để demo kiến trúc logic RESTful

**Bước 1**: Tạo virtual environment, cài vào các thư viện sau:
```
pip install flask
pip install flask-sqlachemy
pip install flask_restful
pip install flask_cors
```

**Bước 2**: Tạo cấu trúc website:
HR application
```
    app.py
    settings.py
    config.ini
    dbconnect package
        __init__.py
    database folder
    users package
        users_model
        users_controller
        users_api
        users_view

    departments package
    ....
```

**Bước 3: ** Xây dựng cơ chế đọc/ghi database local (sqlite3)
Đọc đường dẫn đến database HR_sqlite3.db trong settings.py

>dbconnect/___ init __.py
```Python
from flask_sqlalchemy import SQLAlchemy

database = SQLAlchemy()

```

>app.py
```Python
import settings
from dbconnect import database


app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + settings.DB_PATH
database.init_app(app)

```

**Bước 4:** Xây dựng prototype cho end-point: users_api
End-point được design dưới dạng:

/hr-api/users/<user_id>

/hr-api/users/

Bao gồm các function:

get_user

get_users

put_user

post_user

delete_user

Sử dụng Blueprint, Resouce của flask-restful để đăng ký và sử dụng API

>users/users_endpoint.py

```Python
from flask import Blueprint, json, jsonify, request
from flask_restful import Resource, Api, reqparse

bp_users = Blueprint('users', __name__)
api_users = Api(bp_users)

class Users(Resource):
    def get(self, username):
        return jsonify({
            "status_code": 200,
            "text": username
        })

    def put(self, user_name):
        pass


    def delete(self, user_name):
        pass

class UsersList(Resource):
    def post(self):
        pass
    
    def get(self, user_name):
       pass


api_users.add_resource(Users, '/users/<username>')
api_users.add_resource(UsersList, '/users/')
```

>app.py

```Python
from flask import Flask
from flask_restful import Api
# from flask_sqlalchemy import SQLAlchemy
from flask_cors import CORS
import settings
from dbconnect import database
from users.users_endpoint import bp_users

app = Flask(__name__)
api = Api(app)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///" + settings.DB_PATH
database.init_app(app)

cors = CORS(app, resources={r"/hr-api/*": {"origins": "*"}})

app.register_blueprint(bp_users, url_prefix="/hr-api")

@app.route("/")
def hello():
    return "Hello World!"

if __name__ == "__main__":
    app.run(debug=True, port=5008)


```

**Thử nghiệm: **
Từ hr-even, thực hiện bật webiste:
```
python app.py
```

Thực hiện get dữ liệu: 
>http://127.0.0.1:5008/hr-api/users/username

Kết quả trả về:

```
{
  "status_code": 200, 
  "text": "username"
}
```
