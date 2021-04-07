---
layout: post
title: How to install VMware Tools on FreeBSD (OpnSense)
DATE: 
subtitle: ''
metadescription: Find out how to install VMware Tools on FreeBSD systems like OpnSense.

---
Recently I needed subnets in my nested lab to discover VMware Tanzu. I chose OpnSense, a pretty recent fork of PFSense based on FreeBSD that seems to be popular. I installed the VMware Tools like I do on all my VMs so I figured I'd write a short piece on how to do it since FreeBSD is not that common.

First off, only the open vm tools are supported for recent versions of Unix. Meaning you'll have to install it from the public repo, no more mounting the iso. You'll have to make sure the server has internet access and name resolution.

* Start by logging in the shell of your FreeBSD system. In OpnSense you press "8".
* Install the open vm tools package.

If you have a graphical interface:

    pkg install open-vm-tools

If you don't:

    pkg install open-vm-tools-nox11  

* The package is now installed but it doesn't start automatically. In order to do it, edit _/etc/rc.conf_ which controls the auto start of services, and press "i" to enter edit mode.

  

    vi /etc/rc.conf
    
    i

* Enable the vm tools service in the file.

  

    vmware-guestd_enable="YES"

* Leave edit mode and save the file.

  

    Press Escape
    
    :wq

* Restart the virtual machine. The VMware Tools should now start automatically.

![](/img/freebsdtools.png)