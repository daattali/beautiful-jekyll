---
layout: post
title: Failed to deploy OVF package - The OVF descriptor is not available
DATE: 

---
Quick post about a silly issue I encountered that I want to document here. I was trying to deploy an OVA on a VCSA 6.7 with no success. You would wonder how hard can this be, we've been doing it for years and somehow I just now get the error described below...

In the HTML5 client the deployment just fails with no error. The failed task shows the following message:

> Transfer failed: The OVF descriptor is not available

Same issue in different browsers. I'd been deploying this OVA on other vCenters before with no issue but whatever, I tried the flash (flex) client, you never know these days...

In the flex client at least I would get a description. The helpful kind that VMware loves so much:

> The operation failed for an undetermined reason. Typically this problem occurs due to certificates that the browser does not trust. If you are using self-signed or custom certificates, open the URL below in a new browser tab and accept the certificate, then retry the operation.
>
> https://vCenter-FQDN
>
> If this does not resolve the problem, other possible solutions are shown in this KB article: 2147256.

At this point I know this is not going to help because my vCenter certificate is issued by a CA and the root is trusted. I tried what the KB mentions but it did nothing.

Credits to Sasha_G. for the solution in this [VMTN](https://communities.vmware.com/thread/573590?start=15&tstart=0). **That's right, I was using the short name to access vCenter (which is in the SAN of my certificate by the way). I tried with the FQDN and it worked.**

Turns out the error description contained the solution all along (Not on purpose though -> see url). Now I have no idea how I managed to live that long without ever encountering this issue, I guess I don't use short names as I often as I thought...