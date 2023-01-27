---
title: Linux修改配置文件并重启脚本
date: 2017-09-07 11:45:43
updated: 2017-09-07 11:45:43
tags: ['linux','vim']
categories: 
 - OS
 - Linux
---

# 背景

做事的时候，经常需要修改程序调用的地址为MOCK地址，然后可能要修改回来。每次进入路径用vim修改后，还需要重启，感觉比较麻烦费事。于是有了下面的脚本内容。


## sh实现

```sh
#!/bin/sh
# s.sh
DIR_PATH=.         #目标文件所在目录 
OBJ_FILE=application.properties #目标文件名称

if [ "$1" == 1 ]
then
param='abc'
else
param='xyz'
fi

#下面改变的是13行的内容，原内容将被参数$param代替
echo  "the original content:"
echo " "

sed -n -e "13p" $DIR_PATH/$OBJ_FILE    #显示13行的内容

sed -i "13c$param" $DIR_PATH/$OBJ_FILE          #用$param替换13行的内容

echo "Now, the  content:"
sed -n -e "13p" $DIR_PATH/$OBJ_FILE        #再次显示69行的内容
echo " "

sh /xxx/xx/x/server.sh restart
```

脚本说明：

- 执行 `>./s.sh 1` 配置文件第13行的内容替换为abc，并重启服务
- 执行 `>./s.sh 2` 配置文件第13行的内容替换为xyz，并重启服务

## 遇到的问题

1. syntax error: unexpected end of file
解决办法: 因为脚本是先在windows上写好再传到linux上，于是会有格式的问题。

>$ vim s.sh
>$ :set fileformat=unix
>$ :wq! 

2. if条件语句一直报错
解决办法: [] 内左右侧必须是空格， == 左右侧必须是空格
