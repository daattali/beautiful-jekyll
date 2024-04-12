---
layout: post
title: Web App Pentesting Labs - OWASP WEBGOAT
subtitle: Explore the way to attack web applications with kali linux and OWASP - Missing Functional Level Access Control
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/OWASP_Logo.png
# share-img: /assets/img/path.jpg
tags: [web, security, access-control, attack, burp, owasp]
comments: true
author: Lantana Park
---

## OWASP webGoat A1 - Broken Access Control | Missing Functional Level Access Control

![index](/assets/img/missing/Screenshot%202024-03-13%20at%2017.19.34.png)

In the quest, I needed to escalate priviliege to the admin and then get its hash data.

## Steps to attack

![first](/assets/img/missing/Screenshot%202024-03-13%20at%2009.24.41.png)

1. I needed to find hidden items of the hidden manu

When I open the inspection page and go through the source code, I could find the hidden manu items.

This task was too easy.

![hiddenManu](/assets/img/missing/Screenshot%202024-03-13%20at%2011.04.09.png)

2. I needed to pull the list of users and then input the hash value on my side.

With the urls that I got from the first task, I tries to make a `GET` request to get the list of users.

At first, I made `GET` request on the `access-control/users`, I could get the users' information.

And then input the Jarry's hash value on the task input.

![gotHash](/assets/img/missing/Screenshot%202024-03-13%20at%2011.20.06.png)

![taskinput](/assets/img/missing/Screenshot%202024-03-13%20at%2011.20.31.png)

3. In the last task, I needed to escalate priviliege to the admin, and then make `GET` request to `/access-control/users-admin-fix`.

Unfortunately, I could not get success from this success. Because, even though I could escalte into admin, but, when I attempt to do next `GET` request to get the hash value, I failed at the first attempt.

![lastTask](/assets/img/missing/Screenshot%202024-03-13%20at%2017.20.14.png)
