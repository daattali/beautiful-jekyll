---
layout: post
published: false
title: vCenter 6.5 hybrid certificates with Microsoft Standalone CA
---
When playing with certificates in vCenter I read a lot of articles online but a lot of them were similar and didn't cover the whole picture: Generate a .csr in certificate-manager, make a request on the CA web page, download the cert and install it > done. Don't get me wrong it's still good content and for some it might be what they are after but I was after a procedure that would get me from 0 to the holy green lock icon in the url bar.

The hybrid mode is currently VMware's recommended deployment model for certificates as it procures a good level of security while not being too cumbersome to implement. In this model only the Machine SSL certificate is signed by the CA and replaced on the vCenter. The solution user and ESXi host certificates are distributed by the VMCA. If you look into one of them you'll see that the end of the certificate chain is the VMCA. As opposed to the "VMCA as an intermediate CA" model where the certificate chain goes all the way up to the Root CA via the VMCA.

For this how-to I tried to do something a little different from most articles stated above that would fit my lab need so we will cover the following:

1. Install a Microsoft standalone CA and distribute the root CA via GPO.
2. Generate a certificate request in certificate manager.
3. Obtain a vCenter machine SSL certificate from the CA with the mmc (no web enrollment).
4. Install the certificate and customize the VMCA attributes.
5. Make the VMCA a trusted root CA (the holy green lock).

Before starting make sure you have a working Active Directory and vCenter 6.5.

## Install a Microsoft Standalone CA

I stress the fact that this part of the article is focused at understanding how CAs and certificates work, it is not a "Microsoft CA best practices" as this is not my area of expertise.

In this step we install a Microsoft Standalone Root CA and we set up a GPO to distribute it to the domain computers. The main differentiator of a Standalone CA compared to an Enterprise one is that it is not integrated to the domain. that means you need to distribute the Root CA yourself. It is better suited for environment with non-AD entities and a little less flexible for admins (no templates). However I chose this one to make it different and the fact that it is more "manual" makes it better to fully understand how it works for people like me who weren't born and molded by certificates.

### Install the CA

- Start Server manager and add the "Active Directory Certificate Services" role.
- In AD CS role services check "Certificate Authority" only.
- After the role is added click on the flag with a warning and click "Configure Active Directory Certificate Services ..."
- I leave the domain admin for the configuration (not sure of the best practices here).
- Check Certificate Authority (no other choice) and next.
- Select "Standalone CA"
- Check "Root CA"
- Leave "Private Key" and "Cryptography" as defaults.
- Enter a Common name for your CA. This is the name that will appear as issuer in your client certs so don't go too crazy on the creativity here.
- I leave the default 5 years validy period.

Note that this is the validity of the CA, not the certificates it will sign so it should have a fairly long validity.

Note also that it can not issue certificates with a validity longer than itself.

- The rest is default clickodrome until the end.

That's your CA nice and shiny ready to sign some stuff. 

## Distribute the Root CA cert to the domain computers

This step would not be necessary if we configured an Enterprise CA as Active Directory would do it for us, but that's not how we do things in'it ?

- Start the "Certification Authority" console
- Open the properties of the CA and click "View Certificate"

Again you can see that I'm cruising through the defaults, a proper PKI admin would probably go and touch some settings.

- Go to "Details" > "Copy to File..." > At the file format page chose "Base-64 encoded X.509"

The Base-64 format makes it possible to open and read the certificate with notepad for example, which will be usefull when we put our certificate chain together. The Der format would just spit some crypto garbage.

- Specify a location and name for the file and click finish. an "Export was successful" should appear.
- Start the "Group Policy Management" console and create a GPO linked to the domain.
- Edit the GPO and browse to "Computer management" > "Policies" > "Windows Settings" > "Security Settings" > "Public Key Policies" > "Trusted Root Certification Authoriy"