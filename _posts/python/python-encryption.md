---
title: Python2/Python3数据加密
date: 2017-07-07 12:10:39
tags: ['python加密','py2加密','py3加密','数据加密','接口加密']
categories: 
 - 开发语言
 - Python
---



# python2
先说py2，因为个人习惯，一直都是用的py2。引入的模块是m2crypto，怎么引入我也写一下，当时因为这个问题，挣扎了许久！！

## 搜索M2Crypto
https://pypi.python.org/pypi/M2CryptoWin64/

## 下载安装

>$ pip install --egg M2CryptoWin64

```python
# coding:utf-8

from M2Crypto import RSA, BIO, EVP

def sign_sha1(data):
    # 下面的这三行 我也不是很懂 待研究
    m = EVP.MessageDigest("sha1")  # 先计算散列值
    m.update(data)
    digest = m.final()

    mb = None
    begin = '-----BEGIN PRIVATE KEY-----\n'
    end = '\n-----END PRIVATE KEY-----'

    #  ++++++++++++++ 取常量 +++++++++++++++++++++
    pri_key = "put your private_key here!!"
    # 私钥数据是一行，因为对格式有要求，将它分解为多行，每64个字符一行
    pri_key = [pri_key[i:i + 64] for i in range(0, len(pri_key), 64)]
    # 以BIO的方式读入内存，如果以直接读取文件 或者 读字符串的方式 会有其他错误，暂时以此方法避免
    mb = BIO.MemoryBuffer(begin + "\n".join(pri_key) + end)
    if mb:
        key = RSA.load_key_bio(mb)
        result = key.sign(digest, 'sha1')
        # 将加密的密文从base64解为str类型
        return result.encode('base64')
    else:
        raise 'error'
```

# python3

再说一下py3的背景：个人用py2同django做的页面提供给组员造数据用，然后另外一个同事将我的这个功能添加到另外一个数据平台内。问题是他的py是3版本。我的是用2写的，但是我引入的模块是m2crypto，这个模块在3是不支持的，需要用其他模块代替。

下面是他改写后的代码：

```python
from OpenSSL.crypto import load_privatekey, sign, FILETYPE_PEM
import base64

def sign_sha1(data):
    begin = '-----BEGIN RSA PRIVATE KEY-----\n'
    end = '\n-----END RSA PRIVATE KEY-----'
    pri_key = "put your private_key here!!"
    pri_key = [pri_key[i:i + 64] for i in range(0, len(pri_key), 64)]
    s = begin + "\n".join(pri_key) + end
    private_key = load_privatekey(FILETYPE_PEM, s)
    r = sign(private_key, data, "sha1")
    r = base64.b64encode(r).decode()
    r = [r[i:i + 76] for i in range(0, len(r), 76)]
    return '\n'.join(r)

```
