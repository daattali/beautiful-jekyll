---
title: 在宝塔中使用webhook自动构建hexo
date: 2020-09-27 19:00:00
tags: ['hexo','宝塔','webhook']
categories: 
 - 博客
 - Hexo
---

## 前提

1. 你已经搭建好hexo环境：git hexo npm/nodejs 等等
2. 站点是通过nginx部署的，也就时nginx自动识别你生成的public文件夹
3. 你的服务器上面已经有安装过宝塔

## 登录宝塔

- 添加webhook
- 勾选在主页显示

![1.png](https://i.loli.net/2020/09/27/B9nxthzvK8d3rWw.png)

## 添加webhook

如图
![2.png](https://i.loli.net/2020/09/27/8QYwx3nCobUT7zA.png)

## webhook代码

将下面的blog_path,换成你本机的路径即可
```bash
#!/bin/bash
blog_path="/data/blog"
cd $blog_path
# 输出当前时间
date --date='0 days ago' "+%Y-%m-%d %H:%M:%S"
echo "开始拉取代码"
git pull
echo "开始重新构建"
hexo clean
hexo g
echo "hexo部署成功"
```
添加完之后，可以pull代码到你的仓库，然后再看看站点是不是已经自动更新啦。

## 注意事项

你博客主路径下的_config.yml需要将public配置为绝对路径，否则通过webhook执行之后，会将你的public生成到你npm安装的hexo底下
我的就被生成到了这里，之前还一直以为自动构建没成功
>/root/.nvm/versions/node/v14.12.0/bin/hexo

```yml
# Directory
public_dir: /data/blog/public
```