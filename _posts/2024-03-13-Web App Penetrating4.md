---
layout: post
title: Web App Pentesting Labs - OWASP WEBGOAT
subtitle: Explore the way to attack web applications with kali linux and OWASP - Spoofing an Authentication Cookie
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/OWASP_Logo.png
# share-img: /assets/img/path.jpg
tags: [web, security, session, attack, burp, owasp]
comments: true
author: Lantana Park
---

## OWASP webGoat A1 - Broken Access Control | Spoofinf an Authentification Cookie🍪

![information](/assets/img/spoofing/Screenshot%202024-03-13%20at%2018.31.13.png)

Any values stored in the authentification cookie should be not easily guessable and secure. If it can be predictable by using Base64, hexdecimal, plain text string, attackers can generate authentification cookies for different users.

If this tasks, I used base64 and hex-decimal string to decode the cookie value. Because, as far I know, there is no straight way to decode from base64 to plain text string(human understanable).

### what is Base64?

It is a binary-to-text encoding scheme and is used to represent binary data in an ASCII string format.

Base64 encoding schemes are commonly used when there is a need to encode binary data, especially when that data needs to be stored and transferred over media that are designed to deal with text.

## Steps to attack

1. 
