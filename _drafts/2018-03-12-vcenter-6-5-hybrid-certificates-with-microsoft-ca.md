---
layout: post
published: false
title: vCenter 6.5 hybrid certificates with Microsoft CA
---
When playing with certificates in vCenter I read a lot of articles online but a lot of them were similar and didn't cover the whole picture: Generate a .csr in certificate-manager, make a request on the CA web page, download the cert and install it > done. Don't get me wrong it's still good content and for some it might be what they are after but I was after a procedure that would get me from 0 to the holy green lock icon in the url bar.

The hybrid mode is currently VMware's recommended deployment model for certificates as it procures a good level of security while not being too cumbersome to implement. In this model only the Machine SSL certificate is signed by the CA and replaced on the vCenter. The solution user and ESXi host certificates are distributed by the VMCA. If you look into one of them you'll see that the end of the certificate chain is the VMCA. As opposed to the "VMCA as an intermediate CA" model where the certificate chain goes all the way up to the Root CA via the VMCA.

For this how-to I tried to do something a little different from most articles stated above that would fit my lab needs so we will cover the following:

1. Install a Microsoft standalone CA and distribute the root CA via GPO.
2. Generate a certificate request in certificate manager.
3. Obtain a vCenter machine SSL certificate from the CA with the mmc (no web enrollment).
4. Install the certificate and customize the VMCA attributes.
5. Make the VMCA a trusted root CA (the holy green lock).

Before starting make sure you have a working Active Directory and vCenter 6.5.

## Install a Microsoft Standalone CA

