---
layout: post
title: Ubuntu 18.04/19.04 LAMP Server
subtitle: Setup a Linux Apache MySQL PHP Server in Ubuntu 18.04/19.04
bigimg: /img/path.jpg
tags:
  - Ubuntu
  - Apache
  - MySQL
  - PHP
published: false
---
### Install TaskSel

The tasksel package is available under default repositories on most of Ubuntu, Debian, and LinuxMint operating systems. Use the following command to install it.

```console
sudo apt-get install tasksel
```

### Installing LAMP Using TaskSel

After installing tasksel package on your system, let’s install LAMP setup on your Ubuntu, Debian, and LinuxMint system. Execute tasksel command in the terminal with sudo access to install lamp-server.

```console
sudo tasksel install lamp-server
```

Setup will be completed within few minutes. The MySQL server is installed without any password configured for the root user. You can simply access MySQL without any password.

Then execute the below command to set a new password and secure MySQL installation through a command line wizard.

```console
sudo mysql_secure_installation
```


 
