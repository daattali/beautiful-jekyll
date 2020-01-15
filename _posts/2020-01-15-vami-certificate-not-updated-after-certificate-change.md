---
layout: post
title: VAMI certificate not updated after certificate change
DATE: 

---
Super quick post today about certificates.. It seems to be a unbreakable law of the universe that when doing certificate stuff, it is impossible that everything works the first time.

After replacing the machine SSL certificate on a VCSA using the certificate-manager utility, you may notice when you log on the VAMI interface that the old certificate is still showing.

> https://srv-vcenter.local:5480

![](/img/vami-cert-1.jpg)

The solution to this is given in [KB2136693](https://kb.vmware.com/s/article/2136693). I thought the certificate-manager utility restarted all the services automatically but I guess not. All you need to do is to restart the vami-lighttp service. This is the workaround for 6.5 and 6.7, if you are running 6.0 a few extra steps are required (you should probably update by the way).

    /etc/init.d/vami-lighttp restart

![](/img/vami-cert-2.jpg)

Once the service is restarted just refresh the VAMI url and ensure that the new certificate is presented.

![](/img/vami-cert-3.jpg)