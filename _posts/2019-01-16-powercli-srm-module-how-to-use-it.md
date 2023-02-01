---
layout: post
title: 'PowerCLI SRM module: How to use it'
DATE: 2019-01-16 12:00:00 +0100
date: 2019-01-16 11:41:16 +0100

---
![](/img/srm-pcli.JPG)

If you have Site Recovery Manager in your environment and you are a scripting freak like me who wants to do everything from a Powershell window, you found the right place! You can already do a lot of things with the built-in PowerCLI modules in a "vanilla" environment made of vCenter servers and vSphere hosts. However when you start going off tracks you will find that things require a little bit more work to get the job done.

For instance, you can use the _Get-VMHost_ cmdlet to list your vSphere hosts. However, there is no _Get-InstantClones_ cmdlet for Horizon View nor a _Get-ProtectionGroup_ for SRM.

A cmdlet is essentially a simplified way, provided by VMware, of doing something that you could do in a more convoluted way. Well, when you work with SRM you have no choice but to go with the latter. But that's fine because it is a very interesting and instructional process.

I wrote a short 3 parts guide to help folks who want to get started with the SRM module that I tried to make it as educational as possible in my approach of the matter. I did it for BDRSuite as a guest blogger but I thought it would fit well in my blog posts so I will redirect from here. I also provide a few functions I wrote that I needed for my scripting and also to serve as an example to help understand the whole thing. 

[SRM in PowerCLI: Part 1 – Introduction](https://www.bdrsuite.com/blog/srm-powercli-introduction/ "SRM in PowerCLI part 1")

* Introduction to the SRM module.
* Reminder on installing/updating PowerCLI.
* How to connect to SRM.

[SRM in PowerCLI Part 2 – How it works](https://www.bdrsuite.com/blog/srm-powercli-how-it-works/ "SRM in Powercli part 2")

* How to locate the information with Get-Member.
* Methods vs Properties and how to use them.
* API developer's guide.

[SRM in PowerCLI Part 3 – How to use it](https://www.bdrsuite.com/blog/srm-powercli-how-to-use-part-3/ "SRM in PowerCLI part 3")

* How to use the module through detailed examples.

Happy scripting :)