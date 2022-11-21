---
layout: post
title: Why Google Cloud?
subtitle: "Part 1: Security"
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/cloud-babble-low-resolution-logo-color-on-transparent-background (1).png
#share-img: /assets/img/path.jpg
readtime: true
share-title: Why Google Cloud?
share-description: My first blog post summarising why I choose Google Cloud, starting with Security.
share-img: /assets/img/cloud-babble-low-resolution-logo-color-on-transparent-background (1).png
tags: [security, network, encryption, GFE]
---

In today’s world with the ever increasing threat, volume and sophistication of cyber-attacks, when migrating your data and applications to the public cloud, you need to ensure you can trust your service provider to offer adequate security and strong protection for your data and systems. One of the great things about Google Cloud is their approach to security. Google has designed Google Cloud with protection of customers data at the forefront. In fact, many of the products and services offered by Google Cloud, are the same products and services Google have developed internally and used for many years to protect and run their own data and applications, used by billions of users globally for the likes of Google Search, Gmail, YouTube etc. With Google Cloud, security is baked into the platform from the ground up, rather than something that has been bolted on as an afterthought.

A properly designed Google Cloud architecture can deliver better security than many on-premise approaches thanks to Google’s scale, range of product offerings and continuous investments in security. In this blog, I highlight some of the core security features of Google Cloud and its infrastructure that help protect your data and applications.

### Custom Hardware

Google takes defence in depth to the next level, from designing physical security across their global data centres to custom building their own servers and hardware security chips. The Titan security chips are used for authentication at the hardware layer, serving as hardware roots of trust. All servers securely boot, with cryptographic signatures for baseboard management controllers, BIOS, bootloader, kernel and base operating system images. I can’t remember the exact position (within the top 5 I believe), but there is an interesting fact that Google is one of the largest server manufacturers globally despite not selling a single server which shows the scale of their infrastructure!

![Google Cloud Titan Chip](/assets/img/titan-chip.png "Google Cloud Titan Chip")
*Google Cloud Titan Security Chip*

### Global Network

Then there is Google’s global network- the largest private network in the world, enabling customers to privately route traffic, globally without having to traverse the public internet. This network enables a single VPC to span multiple regions and can deliver more than 1Pbps total bisection bandwidth! 

![Google Cloud Network Edge Points of Presence](/assets/img/networkedgepointofpresence.png "Google Cloud Network Points of Presence")
*Google Cloud Network Points of Presence*

Routing traffic across Google’s private network reduces latency, leading to faster response times, and avoids the additional complexities and challenges of securing and maintaining traffic routing over the internet to components within another region. Google’s network currently spans data centres across 35 regions (plus another 12 planned coming soon!).

![Google Cloud Global Network Regions](/assets/img/regions.png "Google Cloud Global Regions")
*Google Cloud Global Network Regions*

### Encryption

All data stored within Google is encrypted by default at the storage layer with AES256 encryption. Google manages the default encryption keys, but also facilitates customers managing encryption keys themselves with envelope encryption and Cloud Key Management Service. For customers requiring even greater control, they can opt to use their own customer supplied encryption keys. 

Google Cloud also provides hardware security modules to protect your keys and Cloud External Key Manager for integration with vendors like Thales, Fortanix, Futurex and Virtru. Customers can also deploy their own certificate authority within Google Cloud with Certificate Authority Service offering, further protecting applications within Google Cloud.

All traffic between the user and the Google Front End is secured using TLS. This encryption in transit protects your data if communications are intercepted, by encrypting the data before transmission, authenticating the endpoints, and decrypting and verifying that the data was not modified on arrival.

![Google Cloud Default Encryption at Rest](/assets/img/Encryption-at-rest-default-google-cloud.png "Google Cloud Default Encryption at Rest")
*Google Cloud Default Encryption at Rest*

Google also developed the Application Layer Transport Security (ALTS) protocol for securing RPC communications within Google’s infrastructure. This is similar to mutual TLS (mTLS) but optimised to meet the needs of Google’s data centre environments.

Confidential Computing provides encryption in use protection- data in memory is protected from compromise or exfiltration by encrypting the data whilst being processed. Confidential Computing enables customers to achieve encryption in use without needing to make any application code changes or compromise performance.

I’ll be covering more on encryption and certificate services in a deep dive technical blog at a later date.

### Google Front End

The Google Front End (GFE) protects traffic destined for services within Google Cloud from the internet with Cloud Armor. Before traffic reaches a customer’s VPC network, it must route via the GFE (unless a customer has exposed a service directly to the internet with a public IP/not using a Google Cloud load balancer). Here the GFE ensures that all TLS connections are terminated with correct certificates and following best practices such as supporting perfect forward secrecy, in addition to protecting customers from DDoS attacks. As traffic routes through load balancers in the GFE, incoming traffic information is sent to a central DoS service. When the DoS service detects an attack, it can configure the load balancers to throttle or drop the attack traffic. The scale of Google’s infrastructure means it can absorb virtually any size DoS attack before it impacts the customers application.

In June 2022, Google defended against the world’s largest known layer 7 HTTPS DDoS attack which peaked at 46 million requests per second. Google’s DDoS detection was so quick, it stopped the attack at Google’s edge avoiding customer impact. By configuring Adaptive Protection within their Cloud Armor security policy, the customer was alerted to the threat and Cloud Armor proposed a rule that could be deployed to quickly block the traffic before the attack ramped up and had a chance to impact the application. 

![Google Cloud DDoS 46m RPS Peak](/assets/img/DDoS_Attack_Graphic.jpg "Google Cloud DDoS Attack Peak")
*Google Cloud DDoS Attack Peak at 46 million RPS*

More info on this attack is available here on Google’s blog: [How Google Cloud blocked largest layer 7 DDoS attack at 46 million rps](https://cloud.google.com/blog/products/identity-security/how-google-cloud-blocked-largest-layer-7-ddos-attack-at-46-million-rps).

### Security Team

Google has various cyber security teams, each with their own role and responsibility ranging from detection and response, to a dedicated red team who attack Google's infrastructure to test defences in the same manner a real attacker would, through to a Project Zero team who are dedicated to researching zero-day vulnerabilities. 

Google's security teams engage in various security research across both Google and the wider community including various open source projects. The Project Zero team discovered threats including the Spectre exploit, the Meltdown exploit, the POODLE SSL 3.0 exploit and cipher suite weaknesses. 

The good news is these cyber security teams that protect Google’s own infrastructure, are the same teams that protect every organisation on Google Cloud.

### Conclusion

I've focussed on some of the core, foundational security features of Google Cloud in this blog post as part of my 'Why Google Cloud' blog series. Security is one of several reasons I have for 'Why Google Cloud'- I'll be highlighting my other reasons in coming blogs.

There are a myriad of additional Google Cloud products and services available that provide further protection ranging from Identity and Access Management, Google Cloud Resource Hierarchy, VPC Networks, VPC Service controls, Google Cloud Operations i.e. elements that form the Landing Zone. Then there are other offerings like Security Command Center, Google's Zero Trust implementation with BeyondCorp Enterprise, Chronicle, Virus Total, Secret Manager, Identity Aware Proxy, Data Loss Protection API, Container Analysis, Binary Authorisation, Assured Open Source Software... The list goes on. I'll be focussing on some of these products in subsequent blogs in greater detail.

If you've made it this far, thanks for taking the time to read Cloud Babble's first blog! I hope you have enjoyed it. Please feel free to share, [subscribe](https://www.cloudbabble.co.uk/subscribe) to be alerted to future posts, follow me on [LinkedIn](https://linkedin.com/in/jamiethompson85), and react/comment below! 

Do reach out if you would like me to cover any particular areas of Google Cloud products, concepts or certifications in future posts.

