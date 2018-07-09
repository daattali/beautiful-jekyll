---
layout: post
published: false
title: 'Certificate replacement: PSC UI vs certificate-manager'
---
If you ever had to replace certificates in vSphere 6.0 and 6.5 you may know that there are two different ways to do it. The first one using the PSC web UI and the second one using the embedded _certificate-manager_ utility. Now you may also think that these 2 methods produce a similar result. And why shouldn't you? Well, unfortunately it is not the case.

The Lookup service is a PSC service that maintains a table of all the services registered. It contains their URL, certificate, solution user and a bunch of info.