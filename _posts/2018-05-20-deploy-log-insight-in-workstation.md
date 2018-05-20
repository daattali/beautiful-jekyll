---
layout: post
published: false
title: Deploy Log Insight in Workstation
---
If you want to run Log Insight in Workstation (most likely for a lab), you will realise that once you deployed the appliance, all the settings you configured in the wizard have been diregarded. Note that the following is not supported by VMware and should only be used for labs and such.

- Once you deployed the OVA, get in the console and press ALT+F1 to open the Shell.
- Enter "Root" as login and leave blank for the password.
- It will ask for a new password, leave blank again for "Old Password" and type in your new password.
- Set the IP configuration as needed: ```ifconfig eth0 192.168.10.30 netmask 255.255.255.0```
- Set the default gateway: ```route add default gw 192.168.10.254 eth0```
- Change host name: ```vi /etc/HOSTNAME``` change the name accordingly
- Set DNS servers: ```vi /etc/resolv.conf``` Change nameserver and search accordingly
- Reboot the appliance

You should then be able to access the web interface on https://192.168.10.30/admin
