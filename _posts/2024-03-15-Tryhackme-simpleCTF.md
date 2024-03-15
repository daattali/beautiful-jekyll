---
layout: post
title: Tryhackme - SimpeCTF
subtitle: tryhackme simpleCTF walkthrough
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/simpleCTF/logo.png
# share-img: /assets/img/path.jpg
tags: [linux, priviliege escalation, tryhackme]
comments: true
author: Lantana Park
---

Let's start to attack with the ip address `10.10.108.94'.

1. How many services are running under port 1000?

![first](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2023.36.40.png)

Answer: 2

`nmap -sTU -p 1000 10.10.108.94`

`nmap -sTU` is to find a service version detection scan for both TCP and UDP. and then `-p 1000` specifies the port number.

**What is TCP(Transmission Control Protocol)?**

- it is a connection-oriented protocol that establishes a two-way communication between hosts. It ensures the delivery of packets in the order they were sent, which is critical for applications where data must be received reliably and in order, such as web pages (HTTP), file transfers (FTP), and email (SMTP).

**What is UDP(User Datagram Protocol)?**

- It is a connectionless protocol that sends messages, called datagrams, without establishing a prior connection. This is useful for services that require speed and efficiency over reliability, such as video streaming or online gaming.
