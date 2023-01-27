---
title: centos安装glibc2.14/How to update glibc to 2.14 in CentOS
date: 2018-04-11 12:28:00
tags: ['linux','glibc','安装glibc']
categories: 
 - OS
 - Linux
---

## 说明
看到网上有些人发的帖子很明显是错的，害人不浅啊。

## 参考

出处：[how-to-update-glibc-to-2-14-in-centos-6-5](https://unix.stackexchange.com/questions/176489/how-to-update-glibc-to-2-14-in-centos-6-5)

有任何问题欢迎留言。

```
mkdir ~/glibc_install; cd ~/glibc_install 

wget http://ftp.gnu.org/gnu/glibc/glibc-2.14.tar.gz

tar zxvf glibc-2.14.tar.gz

cd glibc-2.14

mkdir build

cd build

../configure --prefix=/opt/glibc-2.14

make -j4

sudo make install

export LD_LIBRARY_PATH=/opt/glibc-2.14/lib
```