---
layout: post
published: true
title: 'Certificates: Don''t use common name as identifier'
---
I recently encountered a certificate issue while working on a project when the certificate was being rejected in a web browser. At first my certificate looked fine, the FQDN was in the common name field (CN) and I had a bunch of Subject Alternative Names (SAN) as well. When I accessed the resource on one of the SANs it would work fine, but the certificate would be in error whenever I used the FQDN (CN).

I am far from being an expert or even proficient with PKIs, however I was aware that putting a server name in the CN field is not best practice but never really paid attention to it when dealing with internal servers. It actually comes from [RFC2818](https://tools.ietf.org/html/rfc2818) released in May 2000 which states the following:

> If a subjectAltName extension of type dNSName is present, that MUST be used as the identity. Otherwise, the (most specific) Common Name field in the Subject field of the certificate MUST be used. Although the use of the Common Name is existing practice, it is deprecated and Certification Authorities are encouraged to use the dNSName instead.

I never encountered the issue in the past but it turns out web browsers started enforcing this very recently (Chrome in version 58). It means that if the certificate has Subject Alternative Names populated, the Common Name will be ignored.

![cert-san-cn.jpg]({{site.baseurl}}/img/cert-san-cn.jpg)

Once I figured this out I requested the exact same certificate, except I also added the FQDN to the list of SubjectAltName.

**Bottom line: Common Name is only a Label. Any server name that should be valid in a web browser MUST be in the SubjectAltName.**

Thanks to this [Stackoverflow post](https://stackoverflow.com/questions/25970714/invalid-common-name-when-using-a-san-certificate).