---
layout: post
title: How to Clear 301 Redirect Cache Chrome
subtitle: Solution to Google Chrome's 301 redirect cache issue
tags: [Tips, Tricks, Chrome]
comments: true
---

Let's see what is the issue first. If you are in a hurry, go to the [solution](#solution)

## What is 301 Redirect Cache issue of Chrome?

Let's see an example because example is better than explanation. ;)

I started working on this site as Github's pages feature. It has a custom domain support.

I used a subdomain of a domain for another purpose to test the custom domain feature. After setting up the subdomain, it worked fine. But github sets up a redirection rule to redirect to the custom domain with 301 http status. Http 301 status means *permenantly moved*.

After the testing was done, I have removed the custom domain. And found that Chrome is still redirecting me to that custom domain. Tried to force reload, closing and reopening Chrome etc but no luck. It is because Chrome caches the 301 redirection rule for indefinite time.

This behaviour is okay according to [RFC-7231](https://tools.ietf.org/html/rfc7231#section-6.4.2)

> A 301 response is cacheable by default; i.e., unless otherwise indicated by the method definition or explicit cache controls (see Section 4.2.2 of [RFC7234]).



## Solution

This neat method allows you to clear the *Google Chrome*'s Cache Data for a specific URL. 

It can also be used with other browsers, such as *Mozilla Firefox* and *Edge*, as long as they support the same features explained below.

### Step-1: Open devtool
Press ***SHIFT+CTRL+I*** to open the Google Chrome Developer Tools panel.

### Step-2: Disable cache
Go to the Network tab and select the Disable cache checkbox to bypass the redirect cache.

### Step-3: Visit URL
Type the URL you want to clear from the browser cache in the address bar and press Enter.
Click and hold the reload button until a modal window pops up, the select the Empty Cache and Hard Reload hidden option.

### Step-4: Enable cache
As soon as the page has been fully reloaded, you can unselect the Disable cache checkbox and disable that feature.

**N.B.** It's worth noting that the *Developer Tools panel* must remain open for the whole process, otherwise Chrome won't let you to use Empty Cache and Hard Reload feature.
