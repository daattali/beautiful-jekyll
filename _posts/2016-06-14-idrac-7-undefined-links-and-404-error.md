---
layout: post
published: false
title: iDrac 7 undefined links and 404 error
---
I usually use Chrome or Firefox on my workstations but the other day I had to use IE11 to reach an iDrac 7 from a jump box in the DMZ and I bumped into this odd 404 error:  

![idrac-undefined.jpg]({{site.baseurl}}/img/idrac-undefined.jpg)

My first thought would be to try with ff or chrome but we try to avoid installing unnecessary softwares on production boxes including web browser as Internet Explorer is more than enough.

In order to fix this issue you just need to enable compatibility mode for the IP/Address of the iDrac:

- In IE go to Tools > Compatibility View Setting
- The address of your iDrac must be here already so just click Add to add it to the compatibility View
- Restart your browser and there you are.

![idrac-works.jpg]({{site.baseurl}}/img/idrac-works.jpg)