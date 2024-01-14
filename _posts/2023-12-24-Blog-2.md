---
layout: post
title: Dec 24, 8:29 PM - Blog #2
subtitle: Progress Update on the Carbon Calculator
gh-repo: your-repo-name
gh-badge: [star, fork, follow]
tags: [carbon calculator, coding, development]
comments: true
author: Your Name
---

{: .box-note}
**Note:** This blog post updates our progress on the carbon calculator.

# Dec 24, 8:29 PM - Blog #2

Hello! This is my second blog post updating our progress on the carbon calculator.

A lot has happened since my last post on Dec 5, so let's get started.

On Dec 5, we had no lines of code written and zero idea how to get this built in Wix Velo, but now we are making serious progress and should have an MVP in the next 2 weeks.

In the past two weeks, I have been taking Replit lessons to improve my coding skills. I have been able to build some cool programs in Python. Here is my Twitter and replied.

This was a few days at our new office.

> Day 21 of [#Replit100DaysOfCode](https://twitter.com/hashtag/Replit100DaysOfCode?src=hash&ref_src=twsrc%5Etfw) [#100DaysOfCode](https://twitter.com/hashtag/100DaysOfCode?src=hash&ref_src=twsrc%5Etfw)  
> We are in our new office learning to code and listening to great insights by [@ycombinator](https://twitter.com/ycombinator?ref_src=twsrc%5Etfw)  
> Check out my project for Day 21 it’s just a quiz about carbon emissions. [Project Link](https://t.co/HTDEtOJQJK) [![pic.twitter.com/sUxLQw4dTU](https://t.co/sUxLQw4dTU)](https://twitter.com/jpear715/status/1736812430079176812?ref_src=twsrc%5Etfw)  
> — Jack Pearson (@jpear715) December 18, 2023

So we all have been learning to code and working at the offices. Yesterday Joe and I had a full 12-hour coding day where we began the first efforts to build our site out into Velo. We learned a lot and I hope to outline where we are now and the product's next steps.

Quick shoutout to the first tutorial we watched as it was really comprehensive and helped us with the first steps. Its by the Wix Wix -> [link](link)

We also followed along the Wix Velo Dev Docs -> [link](link)

After following this we were able to get it working to have our user's inputs collected on a Google sheet! We were pretty excited.

> [@forevergreenapp](https://www.tiktok.com/@forevergreenapp?refer=embed) Joe and I made some serious breakthroughs yesterday 💪 we suck but lesrn pretty quick! [#forevergreen](https://www.tiktok.com/tag/forevergreen?refer=embed) [♬ Last Christmas (Pudding Mix) - Wham!](https://www.tiktok.com/music/Last-Christmas-Pudding-Mix-6696416702155982849?refer=embed)

For the rest of the day, I continued to build out the code on this site. I will add the backend code below.

```javascript
import { getValuesfromGoogleSheet, addValuesToGoogleSheet } from 'backend/calc1';

$w.onReady(function () {
    $w("#insertbutton").onClick(async ()=>{
        const firstName = $w('#firstnameinput').value;
        const lastName = $w('#lastnameinput').value;
        const email = $w('#emailinput').value;
        const emissions = $w('#emissions').value;
        const values = ["17", firstName, lastName, email, emissions];
        const result = await addValuesToGoogleSheet(values);

        if(result.status == 200){
            console.log("added");
        }
    })
});
``` 

The main accomplishment I had was to use these in each of the 5 pages.

We actually ended up writing a decent bit of code.

Here are a few other APIs I want to integrate moving forward...

- [Send Emails using the SendGrid NPM Package](https://dev.wix.com/docs/develop-websites/articles/getting-started/code-tutorials/send-emails-using-the-send-grid-npm-package)
- [Using OAuth SSO with Velo](https://dev.wix.com/docs/develop-websites/articles/getting-started/code-tutorials/using-oauth-sso-with-velo)
- [Chart.js Custom Element](https://www.wix.com/velo/example/chart.js-custom-element)

Additionally, we are now going to be working with S9 consulting to build our first version. I found them through the Wix Velo Marketplace and they will be very helpful to guide our coding moving forward. We are excited to use their knowledge to improve our platform.

Thanks for checking in on my second blog!

## Blog Navigation

- [Previous Blog](/blog1)
- [Next Blog](/blog3)

## Footer

- [Home](/home)

© 2024 Carbon Calc. All rights reserved.
