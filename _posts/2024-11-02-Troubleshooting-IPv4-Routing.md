---
layout: post
title: Trubleshooting IPv4 Routing
subtitle: A topic from CCNA.
#cover-img: /assets/img/trubleshooting.jpg
#thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [blogs]
author: Baltej Giri
---
# Trubleshooting IPv4 Routing

### _A CCNA topic_
Hello Fellow Learner, The topic "Trubleshooting IPv4 Routing" is from CCNA leaning. This blog will cover tools like ping, traceroute and Telnet and SSH.

## Ping Command
- The **ping** command uses _Internet Control Protocol(ICMP)_.
- ICMP uses echo request and ICMP echo reply messages.
- ICMP does not rely on TCP or UDP nor it uses any application layer protocol.
- It functions as part of Layer 3, as a control protocol to assist IP by helping manage the IP network functions.
  
### How ping works?
The ping command is supported on many different operating systems and devices. In Windows, user can open Windows Terminal app and start typing ```ping 1.1.1.1``` command. Output from ping command will disply Packets: sent and received as well as lost along with trip time in milli-seconds.
