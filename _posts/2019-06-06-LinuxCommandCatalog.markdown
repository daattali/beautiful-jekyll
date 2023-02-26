---
layout: post
title:  "Linux Command Catalog"
date:   2019-06-06 11:12:00 AM
categories: Linux
---

I am writing this blog to help me rememeber the linux commands I use. At home I switched to using my Ubuntu Machine as my main machine. I love my Lenovo T430 which I bought from ebay at a cheap price. Ubuntu works nicely on it.

Lot of time on linux you want to know which services are running or start/restart/stop services. 

This returns the status of the units. Units is something that systemd knows about and can manage, example : Services, Sockets etc.

```
systemctl status 
```

To View the status of a single service
```
systemctl status ssh

    ● ssh.service - OpenBSD Secure Shell server
    Loaded: loaded (/lib/systemd/system/ssh.service; enabled; vendor preset: enabled)
    Active: active (running) since Wed 2019-06-05 18:13:55 UTC; 24h ago
    Main PID: 4132 (sshd)
        Tasks: 1 (limit: 2256)
    CGroup: /system.slice/ssh.service
            └─4132 /usr/sbin/sshd -D

    Jun 06 17:50:50 yashubuntu sshd[83945]: PAM service(sshd) ignoring max retries; 6 > 3
    Jun 06 17:55:18 yashubuntu sshd[84214]: Did not receive identification string from 134.209.40.67 port 47312
    Jun 06 18:21:39 yashubuntu sshd[85661]: Received disconnect from 185.244.25.218 port 33072:11: Bye Bye [preauth]
    Jun 06 18:21:39 yashubuntu sshd[85661]: Disconnected from 185.244.25.218 port 33072 [preauth]
    Jun 06 18:22:36 yashubuntu sshd[85714]: pam_unix(sshd:auth): authentication failure; logname= uid=0 euid=0 tty=ssh ruser
    Jun 06 18:22:38 yashubuntu sshd[85714]: Failed password for yash from 131.107.147.30 port 1351 ssh2
    Jun 06 18:22:46 yashubuntu sshd[85714]: Accepted password for yash from 131.107.147.30 port 1351 ssh2
    Jun 06 18:22:46 yashubuntu sshd[85714]: pam_unix(sshd:session): session opened for user yash by (uid=0)
    Jun 06 18:46:32 yashubuntu sshd[101112]: Accepted password for yash from 131.107.147.30 port 55558 ssh2
    Jun 06 18:46:32 yashubuntu sshd[101112]: pam_unix(sshd:session): session opened for user yash by (uid=0)
```

To Start a Service
```
    sudo systemctl start ssh
```

To View the logs you can use the command journalctl
```
    journalctl | grep failed
```





