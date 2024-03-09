---
layout: post
title: Web App Pentesting Labs - OWASP WEBGOAT
subtitle: Explore the way to attack web applications with kali linux and OWASP - Insecure Direct Object References(IDOR)
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/OWASP_Logo.png
# share-img: /assets/img/path.jpg
tags: [web, security, session, attack, burp, owasp]
comments: true
author: Lantana Park
---

## OWASP webGoat A1 - Broken Access Control | Insecure Direct Object References

![index](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.33.50.png)

**What is insecure direct object references(IDOR)?**

IDOR occurs when an application provides direct access to objects based on user input. Imagine having a locker in a public place, such as a gym or library, where personal items can be stored. If the digital password for the locker is the number of the cabinet itself or is noted on the door, this setup could easily allow unauthorized access to the items inside.

Each cabinet should have its own unique key and its number should not be visible. However, this crucial information is often displayed in the website's address. For example, the URL `http://example.com/bankstatements?statementId=123` suggests that `123` could correspond to someone's cabinet number.

If someone realizes that changing the number `123` to `124` in the address (to `http://example.com/bankstatements?statementId=124`) bypasses security checks, allowing them to access information linked to `124` without authorization, they could potentially view another person's profile or even steal bank statements. This represents a significant security flaw, as it allows individuals to access information they should not be able to see.

## Steps to attach

1. Log in with authorized user

![login](/assets/img/IDOR/Screenshot%202024-03-09%20at%2018.52.28.png)

2-1. First, view tom's (authorized user) profile.

![profile](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.03.30.png)

2-2. Second, check out what values are not displayed on the browser using Burp Suit. Role and UserId was not shown in this profile.

![difference](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.03.09.png)

![secondFianl](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.03.30.png)

3. In this quest, I need to predict the patter of URL. I guessed possible URL to view tom's profile based on the GET Request I was given in the previous request. `http://localhost:8080/WebGoat/profile/2342384`

![prediction](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.14.10.png)

4. I needed to view other's profile. In order to do that, I   send some requests with the increased value of user Id. And the caught the profile of `Buffalo Bill`

![otherProfile](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.19.38.png)

4-1. I needed to modify his proflie information.
![modification](/assets/img/IDOR/Screenshot%202024-03-09%20at%2019.33.32.png)

In order to modify the content,

- It should be PUT request
- Content-Type: application/json
- Content-Length: 91
- {"role": 1, "color": "red", "size": "large", "name": "Buffalo Bill", "userId": "2342388"}
  for lowering role and then chaning color into "red"

Success!

**How to defend this attack**

1. **Proper Authorization Checks**
   Ensure users have the right permissions before allowing access to any data or functionality.

2. **Indirect Object References**
   Use non-guessable tokens instead of direct references like database IDs to refer to objects, enhancing security.

3. **Strong Session Management**
   Implement secure session management practices, including secure cookies and session timeouts, to prevent session hijacking.

4. **Input Validation**
   Validate and sanitize user inputs to prevent malicious data from being processed.

5. **Minimize Sensitive Information Exposure**
   Limit the exposure of sensitive information and avoid predictable IDs for user data.
