---
layout: post
title: Tryhackme - Agent Sudo
subtitle: tryhackme agent sudo walkthrough
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/tryhackme/agentSudo/agent.png
# share-img: /assets/img/path.jpg
tags: [linux, priviliege escalation, tryhackme, sudo agent, image reversing]
comments: true
author: Lantana Park
---

Let's attack target ip `10.10.221.94`

![agent](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.32.41.png)

1. How many open ports?

   Answer: 3

   At first, I used `nmap` to scan the port

   ![nmap](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2011.48.39.png)

2. How you redirect yourself to a secret page?

   Answer: user-agent

   Since I could know there is http service (web service), I visited the website. There was information about the secret page.

   **What is user-agent?**

   ![userAgent](/assets/img/tryhackme/agentSudo/User-Agent.png)

   - It is a piece of text that tells the website what kind of device and browser you are using. This information helps the website understand how to show the page correctly on your device. For example, if you're using a phone, the website might want to show you a version that looks good on a small screen.

   ![secretPage](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.38.26.png)

3. What is the agent name?

   Answer: chris

   
