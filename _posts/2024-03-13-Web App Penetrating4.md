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

## OWASP webGoat A1 - Broken Access Control | Spoofing an Authentification Cookie🍪

![index](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.00.53.png)

![information](/assets/img/spoofing/Screenshot%202024-03-13%20at%2018.31.13.png)

Any values stored in the authentication cookie should be secure and not easily guessable. If they are predictable, attackers could potentially generate authentication cookies for different users.

In this task, I used Base64 and hexadecimal strings to decode the cookie value because, to my knowledge, there isn't a direct method to decode from Base64 to a plain text string (in a human-understandable format).

### what is Base64?

It is a binary-to-text encoding scheme and is used to represent binary data in an ASCII string format.

Base64 encoding schemes are commonly used when there is a need to encode binary data, especially when that data needs to be stored and transferred over media that are designed to deal with text.

## Steps to attack

1. I logged in with the given accounts.

![users](/assets/img/spoofing/Screenshot%202024-03-14%20at%2018.34.50.png)

`webgoat` - `webgoat`
`admin` - `admin`

When I attempted to login under admin, I got the cookie value.

![admin](/assets/img/spoofing/Screenshot%202024-03-14%20at%2018.35.14.png)

```
"Cookie details for user admin:<br \\/>spoof_auth=NTk1MTZlNGQ0NTQ1NDE0OTRiNzM2ZTY5NmQ2NDYx"
```

When I attempted to login under webgoat, I got the cookie value.

![webgoat](/assets/img/spoofing/Screenshot%202024-03-14%20at%2018.35.37.png)

```
"Cookie details for user webgoat:<br \\/>spoof_auth=NTk1MTZlNGQ0NTQ1NDE0OTRiNzM3NDYxNmY2NzYyNjU3Nw=="
```

I could know it was encoded by base64. I had solved a similar task in the bandit game.

So I decoded the BS64 value into human-readable text string.

I decoded the BS64 value to the hexdecimal string.

`webgoat` - `59516e4d454541494b7374616f67626577`

`admin` - `59516e4d454541494b736e696d6461`

And then the hex value into text value.

`webgoat` - `59516e4d454541494b7374616f67626577` - `YQnMEEAIKstaogbew`

`admin` - `59516e4d454541494b736e696d6461` - `YQnMEEAIKsnimda`

So I could find the pattern for these cookie values

`YQnMEEAIKs` was followed with the reversed username.

Since I needed to find the cookie value of `tom`, I tried to encode the `YQnMEEAIKsmot` value into hexdecimal and then BS64.

`YQnMEEAIKsmot`
`59516E4D454541494B736D6F74`

![encode](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.02.19.png)

`NTk1MTZFNEQ0NTQ1NDE0OTRCNzM2RDZGNzQ=`

And then, I made a `POST` request to be user `Tom`.

![tom](/assets/img/spoofing/Screenshot%202024-03-13%20at%2016.00.33.png)

Success!

### How to defend?
