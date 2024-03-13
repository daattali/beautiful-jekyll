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

![index](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.00.53.png)

![information](/assets/img/spoofing/Screenshot%202024-03-13%20at%2018.31.13.png)

Any values stored in the authentification cookie should be not easily guessable and secure. If it can be predictable by using Base64, hexdecimal, plain text string, attackers can generate authentification cookies for different users.

In this tasks, I used base64 and hex-decimal string to decode the cookie value. Because, as far I know, there is no straight way to decode from base64 to plain text string(human understanable).

### what is Base64?

It is a binary-to-text encoding scheme and is used to represent binary data in an ASCII string format.

Base64 encoding schemes are commonly used when there is a need to encode binary data, especially when that data needs to be stored and transferred over media that are designed to deal with text.

## Steps to attack

1. I logged in with the given account.

`webgoat` - `webgoat`
`admin` - `admin`

When I attempted to login under admin, I got the cookie value.

```
"Cookie details for user admin:<br \\/>spoof_auth=NTk1MTZlNGQ0NTQ1NDE0OTRiNzM2ZTY5NmQ2NDYx"
```

When I attemped to login under webgoat, I got the cookie value.

```
"Cookie details for user webgoat:<br \\/>spoof_auth=NTk1MTZlNGQ0NTQ1NDE0OTRiNzM3NDYxNmY2NzYyNjU3Nw=="
```

Because if the value from webgoat, I could know it is encoded by base64. I had solved similar task in the bandit game. 

So, from now on, I decoded the BS64 value into human-readabel text string.

I decoded the value to the hexdecimal string.

`webgoat` - `59516e4d454541494b7374616f67626577`

`admin` - `59516e4d454541494b736e696d6461`

And then the hex value into text value.

`webgoat` - `59516e4d454541494b7374616f67626577` - `YQnMEEAIKstaogbew`

`admin` - `59516e4d454541494b736e696d6461` - `YQnMEEAIKsnimda`

So I could find the pattern for these cookie values

`YQnMEEAIKs` was followed with the reversed username.

Since I need to find the cookie value of `tom`, I tried to encode the `YQnMEEAIKsmot` value into hexdecimal and then BS64.

`YQnMEEAIKsmot`
`59516E4D454541494B736D6F74`

![encode](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.02.19.png)

`NTk1MTZFNEQ0NTQ1NDE0OTRCNzM2RDZGNzQ=`

And then, I made `POST` to be user `Tom`.

![tom](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.00.33.png)


Success!









