---
layout: post
title: Installing Mosh server on AWS
subtitle: Also works for other VPS
tags: [vps]
comments: true
---

These instructions were were on a fresh instance of an Ubuntu AMI.

First, install and run mosh server:

~~~
sudo add-apt-repository ppa:keithw/mosh
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install mosh
mosh-server  # start the server
~~~

Next, we need to open up firewall rules. I tried running the following code from another guide, which did not work:

~~~
sudo iptables -I INPUT 1 -p udp --dport 60000:61000 -j ACCEPT
~~~

Instead, I had to go to the AWS EC2 console and to open the rules. On the left, go to "Security Groups". Select the group. Inside the Inbound tab, click "Edit" then "Add Rule". You want the following settings:

 * Type: "Custom UDP"
 * Port Range: 60000 - 61000
 * Source: leave alone (should automatically have "0.0.0.0/0; ::/0")

Save, and now you should be able to access your VPS with mosh. Good luck!
