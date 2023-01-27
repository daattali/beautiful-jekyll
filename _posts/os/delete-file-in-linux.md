---
title: Linux 通过rm命令删除文件后磁盘空间没有释放问题
date: 2019-07-12 16:52:55
updated: 2019-07-12 16:52:55
tags: ['linux删除','磁盘未释放']
categories: 
 - OS
 - Linux
---

# 背景

执行自动化用例的时候，给应用推了一条成功的消息，可是消息没有正常被接收，导致自动化用例执行失败。

查一下日志：

>[2019-07-12 00:41:40,701] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-3] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:00,196] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-9] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:18,721] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-5] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:20,685] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-10] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:38,725] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-8] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:40,742] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-3] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)
[2019-07-12 00:42:58,752] [WARN] org.springframework.boot.actuate.health.DiskSpaceHealthIndicator [http-nio-11088-exec-9] [] lark silvergrd-notify - Free disk space below threshold. Available: 0 bytes (threshold: 10485760 bytes)

剩余空间不足，磁盘爆了。

> df -hl

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190712165035310.png)

## 尝试解决

从经验而言， 一般都是日志文件。
查找占磁盘大于`1G`的文件
![查找容量大于1G的文件](https://img-blog.csdnimg.cn/2019071216372181.png)

测试环境日志的作用不是特别大，可以考虑删掉。

>[root@release-silvergrd-21-13 logs]# rm out.log 
rm: remove regular file `out.log'? yes

删除之后再查一下磁盘占用情况，可用依然还是`0`。 虽然该log文件没在该路径了，但是实际并未真正删除。

>rm只是将文件链接解除，如果此时有进程打开文件，系统是不会回收文件。说白就是，你删除的文件被放入了“回收站”，但是你看不这个“回收站”，但文件还占用着磁盘空间

`文件并未真正删除`，得想办法：

>lsof |grep deleted

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190712164358934.png)
这不正是刚才删除的两个文件么？

重启占用被删除文件的应用，使该log文件被应用释放，然后被系统自动删除。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190712164607169.png)

## 补充

如果不想这么麻烦，建议采用此方式：

>$ \>out.log

清空log文件里的内容。

参考出处 & 感谢作者
《[Linux 通过rm命令删除文件后磁盘空间没有释放问题](https://www.jianshu.com/p/fd2eee044d62)》
