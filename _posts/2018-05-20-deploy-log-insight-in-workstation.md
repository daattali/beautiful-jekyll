---
layout: post
published: true
title: Deploy Log Insight in Workstation
---
If you want to run Log Insight in Workstation (most likely for a lab), you will realise that once you deployed the appliance, all the settings you configured in the wizard have been diregarded. Note that the following is not supported by VMware and should only be used for labs and such.

- Once you deployed the OVA, get in the console and press ALT+F1 to open the Shell.
- Enter "Root" as login and leave blank for the password.
- It will ask for a new password, leave blank again for "Old Password" and type in your new password.
- Set the IP configuration as needed: ```vi /etc/sysconfig/networking/ifcfg-eth0/devices/ifcfg-eth0"```

```
DEVICE=eth0
BOOTPROTO=static
STARTMODE=auto
IPADDR=192.168.174.30
NETMASK=255.255.255.0
ONBOOT=yes
```

- Set the default gateway: ```vi /etc/sysconfig/network/routes"```

```
default 192.168.174.2
```

- Set DNS servers: ```vi /etc/resolv.conf``` Change nameserver and search accordingly
- Reboot the appliance

You should then be able to access the web interface on https://192.168.174.30/admin
