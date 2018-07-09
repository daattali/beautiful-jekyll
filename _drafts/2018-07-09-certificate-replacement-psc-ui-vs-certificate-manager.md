---
layout: post
published: false
title: 'Certificate replacement: PSC UI vs certificate-manager'
---
If you ever had to replace certificates in vSphere 6.0 and 6.5 you may know that there are two different ways to do it. The first one using the PSC web UI and the second one using the embedded _certificate-manager_ utility. Now you may also think that these 2 methods produce a similar result. And why shouldn't you? Well, unfortunately it is not the case.

The Lookup service is a PSC service that maintains a table of all the services registered. It contains their URL, certificate, solution user and a bunch of obscur things. It is used by services themselves so they can find one another and communicate securely with each other. I mentioned "certificates" in the list of properties registered in the Lookup service and this is where the issue is regarding the way we replace certificates.

## PSC UI vs certificate-manager
Both method will replace the machine SSL certificate and have the web client use it. Meaning you will not receive a certificate error when opening it in a browser (provided the signing root CA is in your trusted root CAs). It is why this issue is so confusing, the certificate appears changed but it may not be in the background!