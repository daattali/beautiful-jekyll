---
layout: post
title: Production Experimentation
subtitle: Making data-driven decision matters
date: 2021-06-18
image: /assets/img/laboratoy.png
share-img: /assets/img/laboratoy.png
tags:
  - Thoughts
  - experiments
  - engineering
published: true
---


> **“If we have data, let’s look at data. If all we have are opinions, let’s go with mine.”** 
>
> **― Jim Barksdale**

Businesses often make decisions based on opinion rather than facts. Why? I think it is mainly due to 3 main reasons:

1. **Bias** - If I think A, most certainly my users/clients also think A
2. **Speed** - Planning, experimenting, analysing takes time and resources
3. **Risk** - Experimenting imply risk of something going wrong

Let me elaborate I little more on this reasons:

#### Bias

> By following an empirical approach, we ensure that product changes are not driven by the most opinionated and vocal Netflix employees, but instead by actual data, allowing our members themselves to guide us toward the experiences they love.
>
> [**―**The Netflix Tech Blog](https://netflixtechblog.com/its-all-a-bout-testing-the-netflix-experimentation-platform-4e1ca458c15)

Couldn't say it better. But also keep in mind that [change is the only thing that it's constant](https://www.goodreads.com/quotes/336994-the-only-thing-that-is-constant-is-change--). So keep measuring even after your experimentation has finished, since what was true 2 years ago might not be true today.

#### Speed

Making a decision just for the sake of moving fast can backfire, as making a mistake can cause a greater delay than running an experiment to make a data-driven decision. 

#### Risk

You need to be very careful how you run your experiments, as doing something wrong can cause your customers to lose money, and consequently, you can lose customers and trust. This could lead managers to avoid making "big" changes and trying new things or simply trying things that can be done "safely." 

### Experimentation

Making experimentation easy and safe will increase innovation. Also, keep in mind that It's all about feedback and validating hypothesis. You can't get feedback until it's in your customer's hands.

Having barriers on innovation will have an impact on how fast your company grows. How to approach these issues? First, don't be afraid of your customer's feedback, use it to guide your product evolution. Second,  **make experiments safe and easy to measure**, which will lower the effort required to gather data to make informed decisions.

How do we do that? Having technology and mechanisms that allow you to:

1. Run your experiments on a small subset of customers. That will allow you to test your hypothesis but also reduce the impact of any possible issue on your experiment.
2. Monitor all relevant KPI. That allows you to have an eye on how the experiment is going and knowing if something is wrong at any given moment.
3. Make it easy to turn off any ongoing experiment. If you notice any undesired result from your metrics, you will be able to stop it before it has a greater impact on your customers.

Don't forget that simplicity is key for this to succeed. So avoid burying this under heavy processes and try to keep them as lightweight as possible, so engineers don't feel discouraged to run experiments.