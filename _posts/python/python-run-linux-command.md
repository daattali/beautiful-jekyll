---
title: Python远程执行Linux命令
date: 2017-07-13 10:35:35
tags: ['python','linux','远程shell','py远程ssh']
categories: 
 - 开发语言
 - Python
---

最开始的版本
```python
# coding:utf-8
import paramiko
def start_up(host,user,pwd,path):
"""启动服务"""

    # paramiko.util.log_to_file('paramiko_startup.log')
    ssh = paramiko.SSHClient()
    # ssh.load_system_host_keys()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(host,22,user,pwd,timeout=10)
    #找出当前linux服务器的java目录
    find_java ="echo $JAVA_HOME"
    stdin,stdout,stderr = ssh.exec_command(find_java)
    java_home = stdout.readlines()[0]
    command ="sudo sh {1}bin/startup.sh".format(java_home,path)
    print command
    (stdin,stdout,stderr) = ssh.exec_command(command=command)
    stdin.write('Y')
    ut = stdout.readlines()
    for i in out:
    print i
    ssh.close()
```

定义一个方式远程启动tomcat，但是报错
报错如下

    Neither the JAVA_HOME nor the JRE_HOME environment variable is defined
    At least one of these environment variable is needed to run this program

怎么办 ？ 问里群里大神，需要在执行shell的时候加入JAVA_HOME路径。于是获取JAVA_HOME路径，于是就有了上面的代码，但是还是不行，因为这样还是获取不到java路径。问题困扰很久，暂时改用其他模块。

第二个版本

```python
# coding:utf-8
from fabric.api import run, env, hosts

def start_up_fabric(host, user, pwd, path):
    """启动服务"""
    host_ = host + ':22'
    env.hosts = [host_]
    env.user = user
    env.password = pwd
    # output = run('echo $JAVA_HOME')
    # print output
    command = 'sh {0}bin/startup.sh'.format(path)
    run(command)
```

最开始使用的是env.hosts = [host,]，依然有问题, 因为其他方法调用这个方法的时候，仍然需要手动输入host。

继续查，继续修改，于是问题终于搞定。

下面的代码，可以远程执行shell ，启动tomcat不需要指定java/jre路径，而且不会再需要手动输入host。

```python
# coding:utf-8
from fabric.api import run, env, hosts

def start_up_fabric(host, user, pwd, path):
    """启动服务"""
    host_ = host + ':22'
    env.host_string = host_
    env.user = user
    env.password = pwd
    # output = run('echo $JAVA_HOME')
    # print output
    command = 'sh {0}bin/startup.sh'.format(path)
    run(command,pty=False)
```
