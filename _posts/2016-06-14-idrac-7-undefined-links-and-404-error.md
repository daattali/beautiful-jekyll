---
layout: post
published: true
title: iDrac 7 undefined links and blocked IP
---
**Undefined links with 404 error**

I usually use Chrome or Firefox on my workstations but the other day I had to use IE11 to reach an iDrac 7 from a jump box in the DMZ and I bumped into this odd 404 error:  

![idrac-undefined.jpg]({{site.baseurl}}/img/idrac-undefined.jpg)

My first thought would be to try with ff or chrome but we try to avoid installing unnecessary softwares on production boxes including web browser as Internet Explorer is more than enough.

In order to fix this issue you just need to enable compatibility mode for the IP/Address of the iDrac:

- In IE go to Tools > Compatibility View Setting
- The address of your iDrac must be here already so just click Add to add it to the compatibility View
- Log off / Log on and there you are.


**Blocked IP**

After failing a few times to log on the iDrac I noticed my connection dropped and I couldn't ping it anymore eventhough I could access it from other IPs. There is an advanced network setting that is not obvious at first glance that allows the iDrac to block an IP for a period of time after x failed attempts.

To modify that setting go to _iDRAC Settings > Network > Advanced Settings_

![idrac-adv-net.jpg]({{site.baseurl}}/img/idrac-adv-net.jpg)

You can display the help on the top right corner.

- **IP Range Enabled**: If this option is enabled, iDRAC cannot communicate using TCP/IP protocol with IP addresses that are outside the specified range. By default, this option is disabled.
- **IP Range Address**: This value determines the acceptable IP address. 
- **IP Range Subnet Mask**: Acceptable IP subnet address. This value defines the significant bit positions in the IP address.
- **IP Blocking Enabled**: Enables the IP address blocking feature, which limits the number of failed login attempts from a specific IP address for a pre-selected time span.
- **IP Blocking Fail Count**: Number of login failures attempted from an IP address before the login attempts are rejected from that address. The default value is 3.
- **IP Blocking Fail Window**: Time span (in seconds) within which IP Blocking Fail Count failures must occur to trigger the IP Blocking Penalty Time. The default value is 60.
- **IP Blocking Penalty Time**: Time span (in seconds) within which login attempts from an IP address with excessive failures are rejected. The default value is 300.