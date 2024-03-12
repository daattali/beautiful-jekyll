---
layout: post
title: What is threat modeling?
subtitle: concept of threat modeling
# gh-repo: daattali/beautiful-jekyll
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/overthewire.jpeg
# gh-badge: [star, fork, follow]
tags: [security, threat modeling, article, agile]
comments: true
author: Lantana Park
---

# what is threat modeling?

It is to understand causes in relation to cyber security losses. It is about using that understanding to protect the system in a risk-based way.

### Start from the technology

The first recommendation is to focus primarily on technical rather than broad threats, at least at first.
Technical threats and vulnerabilities are much more granular, such as particular weaknesses in software or missing security controls such as encryption or authorisation. These kinds of threats emerge from the structure and data-flow inherent in the system your team is building. Usually a bunch of technical threats combine together to allow a broad threat to impact your system.

### Take a collaborative approach

The second recommendation is to adopt a collaborative, team based approach. So bringing a wide variety of perspectives to the exercise makes brainstorming more robust. It also increases the likelihood you will identify the most important threats. Threat modelling in a group helps address risk holistically and helps the whole team to learn how to think and talk effectively about security.

### Threat modelling 'little and often'

The third recommendation is to start threat modelling 'little and often'. Rather than trying to analyse your entire system upfront, build your team's muscle memory with threat modelling a little bit at a time.

For information, you can visit [article](https://martinfowler.com/articles/agile-threat-modelling.html)

On the 5th class, I got a chance to get feedback about my code from peers. It was really appreciated time because while developing this website alone, I could not have a real-discussion and get feedback and cheers from diverse people. Here I am going to share some feedback I got during the class.

1. Set the time limiting from when users get the token url to click the token url

2. when I save password on the database, I need to delete the password2 (because it does not need)

3. Validate the form in server and also use middleware when user attempts to resent password

4. When user reset the password, do not let users reset previous password

5. Password string length limitation
