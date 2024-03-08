---
layout: post
title: Web App Pentesting Labs - OWASP WEBGOAT
subtitle: Explore the way to attack web applications with kali linux and OWASP - hijacking session
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/OWASP_Logo.png
# share-img: /assets/img/path.jpg
tags: [web, security, linux, attack]
comments: true
author: Lantana Park
---

## OWASP webGoat A1 - Broken Access Control

![index](/assets/img/sessionhijacking/Screenshot%202024-03-08%20at%2018.03.44.png)

Sesstion ID should be complex and rendom. If not, the application is highly susceptible to session-based brute force attacks.

**What is session hijacking?**

It is a technique used by attackers to take over the internet session. This is the possible scenario that can be happened.

![possiblesenario](/assets/img/sessionhijacking/Screenshot%202024-03-06%20at%2017.30.34.png)

**Let's start from what is session?**

Our computer uses HTTP requests to communicate with users and websites. Unfortunately, HTTP requests are stateless, which means HTTP exchanges do not tell a website that went on before. So, even if you logged in (by matching user ID and password) and then want to navigate to a new page, this website does not know and then this would obviously make for an terrible user experience.

Session can be one of resolutions to this issue. A session referes to the interaction between a user and a website within a given timeframe until the users logs out or the session expires due to inactivity on the website.

To explain it further, when user log in, session is created on the server and then give users a session ID or session token. These are used to indentify the users and following requests. The ID or token can be stored in a cookie or included in the URL, as a query parameter.

**How does the session hijacking happen?**

Attackers can intercept user's session ID or token. By doing this, they can access user sessions and do some possilbe malicious activity in the website, from gaining sensitive information to escalating the privilieges within the system.

From now on, I want to focus on more this quest I was given,

GOAL: Gain access to an authenticated session belonging to someone else.

I have to intercept the HTTP request for login using burp suit and then going through the cookie value in this request, I need to differentiate the authenticated and anonymous users of this website.

![quest](/assets/img/sessionhijacking/Screenshot%202024-03-06%20at%2021.09.06.png)

## Steps to attack

1. Send login request many times using Burp repeater.

![repeater](/assets/img/sessionhijacking/Screenshot%202024-03-08%20at%2016.25.07.png)

While sending many login post request, I noticed that there is following rule on the hijack_cookie.

`hijack_cookie=6734358475426208554-1709916859980;`
`hijack_cookie=6734358475426208555-1709916877788;`
`hijack_cookie=6734358475426208557-1709916886839;`

First part of id was increased by 1 in every post request and second part of ID was increased `17099168%59980%`.

I noticed that when the session id was authenticated, it gives me 2 steps increased number of the first part.

So authenticated session id will be `6734358475426208556` in the first part and then second part will be from `1709916877788` to `1709916886839`

2. Make intruder to send many request with possible payload.

![intruder](/assets/img/sessionhijacking/Screenshot%202024-03-08%20at%2018.04.07.png)

With this assumption, I tried to make intruder with the possible payloads. At the end of this attack, I found the `1709916877788` can be authenticated session id of the second part.

Let's try post request with the value

`6734358475426208556-1709916877788`

3. Send post request with the authenticated session id

![success](/assets/img/sessionhijacking/Screenshot%202024-03-08%20at%2018.03.25.png)

Success! V

## How to defend from session hijacking attacks

Randomized(unpredictable) session ID or token value

--- Next Insecure Direct Object References ---
