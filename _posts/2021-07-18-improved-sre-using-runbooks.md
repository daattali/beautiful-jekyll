---
layout: post
title: Improved SRE using runbooks
subtitle: Incident Management
date: 2021-07-18
image: /assets/img/template-1-.png
share-img: /assets/img/template-1-.png
tags:
  - tips
  - sre
  - production
published: true
---
There are systems that can't afford downtime and Site Reliability Engineering (SRE) is that set of practices and techniques that contribute to build and maintain reliable systems. Runbooks can be one of those practices that allow you to keep your systems reliable. But why are they necessary? Let me get into that. 

SRE is also a job title, which means that there is someone whose responsibility it is to keep the systems working properly (reliable systems). To achieve this, monitoring is crucial to solving incidents before it causes a total system outage.

But being aware of the problem is only half the job, now we need to be able to solve it. If we consider that an SRE does not necessarily know everything about all the services, then the resolution may require a considerable amount of time to simply investigate the appropriate set of actions to alleviate the situation. That's where runbooks can help.

## Why runbooks can be useful?

There are processes that cannot be automated or it is very difficult to do so. And even those processes that can be automated sometimes require human judgment to decide between different options. So manual interaction is required.

That's when runbooks can save a lot of time on incident resolution. The runbooks are just a list of possible incidents with a list of action points to mitigate the problem. Note that SRE does not need to fully resolve the issue, but only needs to control the situation to reduce the damage until the service owners are back and can delve into the issue.

## How to implement runbooks?

I have seen 3 different options:

* **Markdown in the service repository**: It helps to keep the actions to perform close to the service it relates.
* **Wiki page**: Companies usually have some kind of internal wiki for shared documentation. This can be also a place to keep your runbooks. 
* **[Jupyter Notebooks](https://jupyter.org/)**: Can be used as markdown documentation with the possibility to execute commands directly from the notebook itself.

Each one has pros and cons, discuss with your team to choose what best suits your needs, but the most important thing is to commit to keeping it up to date. Outdated runbooks instead of helping with incident management can cause more problems.

As a service owner, it is important to not just write the runbook and hope that any SRE can understand it. It might be worth discussing the runbook with SRE to make sure everyone is on the same page and that it is understandable to them.