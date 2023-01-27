---
title: Python实现简单的API
date: 2017-07-12 17:22:19
updated: 2017-07-12 17:22:19
tags: ['python','api','server','wsgiref','接口']
categories: 
 - 开发语言
 - Python
---

# Get方法

```python
# coding:utf-8

import json
from urlparse import parse_qs
from wsgiref.simple_server import make_server

# 定义函数，参数是函数的两个参数，都是python本身定义的，默认就行了。
def application(environ, start_response):
    # 定义文件请求的类型和当前请求成功的code
    start_response('200 OK', [('Content-Type', 'text/html')])
    # environ是当前请求的所有数据，包括Header和URL，body，这里只涉及到get
    # 获取当前get请求的所有数据，返回是string类型
    params = parse_qs(environ['QUERY_STRING'])
    # 获取get中key为name的值
    name = params.get('name', [''])[0]
    no = params.get('no', [''])[0]
    # 组成一个数组，数组中只有一个字典
    dic = {'name': name, 'no': no}
    return [json.dumps(dic)]

if __name__ == "__main__":
    port = 5088
    httpd = make_server("0.0.0.0", port, application)
    print "serving http on port {0}...".format(str(port))
    httpd.serve_forever()
```

## 请求示例

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcwNzEyMTcxOTIzMzg1?x-oss-process=image/format,png)

# Post方法

```python
# coding:utf-8

import json
from wsgiref.simple_server import make_server

# 定义函数，参数是函数的两个参数，都是python本身定义的，默认就行了。
def application(environ, start_response):
    # 定义文件请求的类型和当前请求成功的code
    start_response('200 OK', [('Content-Type', 'application/json')])
    # environ是当前请求的所有数据，包括Header和URL，body

    request_body = environ["wsgi.input"].read(int(environ.get("CONTENT_LENGTH", 0)))
    request_body = json.loads(request_body)

    name = request_body["name"]
    no = request_body["no"]
    # input your method here
    # for instance:
    # 增删改查
    dic = {'myNameIs': name, 'myNoIs': no}

    return [json.dumps(dic)]


if __name__ == "__main__":
    port = 6088
    httpd = make_server("0.0.0.0", port, application)
    print "serving http on port {0}...".format(str(port))
    httpd.serve_forever()
```

## 请求示例

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcwNzEyMTcyMDA4Mjc4?x-oss-process=image/format,png)

# 疑问

 1. 怎么实现请求的路径限制？
 2. 怎么限制接口调用方的headers？
以上待研究，未完待续。。。