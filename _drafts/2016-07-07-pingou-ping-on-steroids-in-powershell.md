---
layout: post
published: false
title: 'Pingou: ping on steroids in powershell'
---
Pingou is a powershell script that allows to test connectivity with ICMP and open ports with TCP. This command is meant to be easy to use, intuitive and faster than the built in test-connection and test-netconnection.

![pingou.jpg]({{site.baseurl}}/img/pingou.jpg)

I took inspiration on a great script that one of my colleagues wrote "[tPing](http://www.nimbus117.co.uk/powershell/2015/07/06/tPing.html)". But because there is no better way to learn than to do it myself so I took a few ideas and wrote mine from scratch.


**ICMP**

Pingou www.google.fr

![pingou-www.google.fr.jpg]({{site.baseurl}}/img/pingou-www.google.fr.jpg)

**Hostname resolve**

The script resolves automatically the hostname to ping. According to your DNS settings, a hostname can resolve one or multiple IPs (apologies for the screenshots in french but you'll get it).

Nslookup using my ISP's DNS : cache1.service.virginmedia.net

![nslookup-virgindns.jpg]({{site.baseurl}}/img/nslookup-virgindns.jpg)

Nslookup using google's DNS (the one I use) : google-public-dns-a.google.com

![nslookup-googledns.jpg]({{site.baseurl}}/img/nslookup-googledns.jpg)

As you can see for some reason the Virgin DNS resolves only one IP when google's ones resolve a lot. That is why in case it happens, the test will be issued to the first IP in the list (62.252.232.30).

**Parameters**

- DESTINATION: Remote IP or hostname to test.

- COUNT: (-t) Number of test issued.

- PORT: TCP port to check on the remote host, validate range is 1 to 65535.

- CONTINUOUS: (-n) Number of tests infinite. can be stopped with ctrl+c or by closing the invite.

- TIMEOUT: (-w) Number of milliseconds after which a timeout is issued for each test.

- DELAYMS: Number of milliseconds between each test.

- HOPS: (-i) Number of hops after which the packet is dropped (TTL expired). Works only with ICMP tests.

- BUFFER: (-l) Size in bytes of the buffer to send. Works only with ICMP tests.