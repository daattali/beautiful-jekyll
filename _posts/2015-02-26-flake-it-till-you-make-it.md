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
### Step 1: Update Software Packages

Before we install the LAMP stack, it’s a good idea to update repository and software packages. Run the following command on your Ubuntu 18.04/19.04 OS.

```console
sudo apt update && sudo apt upgrade
```


### Step 2: Install TaskSel

Instead of installing Apache, MySQL, and PHP separately, Tasksel offers a convenient way to get a LAMP stack running quickly.

```console
sudo apt-get install tasksel
```

### Step 3: Installing LAMP Using TaskSel

After installing tasksel package on your system, let’s install LAMP setup on your Ubuntu system. Execute tasksel command in the terminal with sudo access to install lamp-server.

```console
sudo tasksel install lamp-server
```

Setup will be completed within few minutes. The MySQL server is installed without any password configured for the root user. You can simply access MySQL without any password.

Then execute the below command to set a new password and secure MySQL installation through a command line wizard.

```console
sudo mysql_secure_installation
```

