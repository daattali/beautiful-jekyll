---
layout: post
published: false
title: vCenter 6.5 hybrid certificates with Microsoft Standalone CA
---
The hybrid mode is currently VMware's recommended deployment model for certificates as it procures a good level of security while not being too cumbersome to implement. In this model only the Machine SSL certificate is signed by the CA and replaced on the vCenter. The solution user and ESXi host certificates are distributed by the VMCA. If you look into one of them you'll see that the end of the certificate chain is the VMCA. As opposed to the "VMCA as an intermediate CA" model where the certificate chain goes all the way up to the Root CA via the VMCA.

When playing with certificates in vCenter I read a lot of articles online but a lot of them were very similar and didn't cover the whole picture: Generate a .csr in certificate-manager, make a request on the CA's web page, download the cert and install it > done. Don't get me wrong it's still good content and for some it might be enough but most of them skipped the Windows CA part and didn't go all the way to the GPOs and properly identified VMCA certs. I'm also not a big fan of the "next next next" approach without explaining and understanding what's what.

For this how-to I tried to do something a little different than most articles stated above that would also fit my lab needs. We will cover the following:

1.Install a Microsoft standalone CA and distribute the root CA certificate via GPO.
2.Generate a certificate request in certificate manager.
3.Obtain a vCenter machine SSL certificate from the CA with the mmc (no web enrollment).
4.Install the certificate in vCenter.
5.Customize the VMCA attributes and renew the solution users and Hosts certificates.
6.Make the VMCA a trusted root CA (the holy green lock).

Before starting make sure you have a working Active Directory and vCenter 6.5.

## Install a Microsoft standalone CA and distribute the root CA certificate via GPO.

This part of the article is focused at understanding how CAs and certificates work, it is not a "Microsoft CA best practices" as this is not my area of expertise.

In this step we install a Microsoft Standalone Root CA and we set up a GPO to distribute it to the domain computers. The main differentiator of a Standalone CA compared to an Enterprise one is that it is not integrated to the domain. that means you need to distribute the Root CA yourself. It is better suited for environment with non-AD entities and a little less flexible for admins (no templates). However I chose this one to make it different and the fact that it is more "manual" makes it better to fully understand how it works for people like me who weren't born and molded by certificates.

### Install the Microsoft CA

-Start Server manager and add the "Active Directory Certificate Services" role.
-In AD CS role services check "Certificate Authority" only.
-After the role is added click on the flag with a warning and click "Configure Active Directory Certificate Services ..."
-I leave the domain admin for the configuration (not sure of the best practices here).
-Check Certificate Authority (no other choice) and next.
-Select "Standalone CA"
-Check "Root CA"
-Leave "Private Key" and "Cryptography" as defaults.
-Enter a Common name for your CA. This is the name that will appear as issuer in your client certs so don't go too crazy on the creativity here.
-I leave the default 5 years validy period.

Note that this is the validity of the CA, not the certificates it will sign so it should have a fairly long validity.

Note also that it can not issue certificates with a validity longer than itself.

-The rest is default clickodrome until the end.

That's your CA nice and shiny ready to sign some stuff. 

### 1. Distribute the Root CA cert to the domain computers

This step would not be necessary if we configured an Enterprise CA as Active Directory would do it for us, but that's not how we do things in'it ?

-Start the "Certification Authority" console
-Open the properties of the CA and click "View Certificate"

Again you can see that I'm cruising through the defaults, a proper PKI admin would probably go and touch some settings.

-Go to "Details" > "Copy to File..." > At the file format page chose "Base-64 encoded X.509"

The Base-64 format makes it possible to open and read the certificate with notepad for example, which will be usefull when we put our certificate chain together. The Der format would just spit some crypto garbage.

-Specify a location and name for the file and click finish. an "Export was successful" should appear.
-Start the "Group Policy Management" console and create a GPO linked to the domain.
-Edit the GPO and browse to "Computer management" > "Policies" > "Windows Settings" > "Security Settings" > "Public Key Policies" > "Trusted Root Certification Authoriy" > Right click "Import".
-Click Next and Browse to the certificate location.
-Make sure the certificate goes to the Trusted Root CA store and click Next > Finish.
-The Root CA certificate should appear on the right pane.
-Run "gpupdate /force" on all your systems and check that the certificate appears in Certificate Manager.

## 2. Generate a certificate request in certificate manager.

The certificate request is a file generally with the .csr extension containing all the properties the certificate should have and is used by the CA to generate the said certificate. There are different ways to create a csr (openssl, certmgr, some dodgy tools online) but the easiest in this case is to use VMware's script "certificate-manager".

**Windows vCenter Server**: ```C:\Program Files\VMware\vCenter Server\vmcad\certificate-manager```

**vCenter Server Appliance**: ```/usr/lib/vmware-vmca/bin/certificate-manager```

Quick troll: In my lab I work with a Windows based vCenter, that's right!

-Go to the location of your OS and start the tool. "./certificate-manager" for linux and there is a .bat file for Windows.
-Chose option 1 > Then Option 1 again > Provide a directory to store the files > answer "Y" to reconfigure certool.cfg and configure your certificate.

For most fields you can put pretty much whatever you want but some of them should be done right:

-**Name** : FQDN of vCenter server
-**IPAddress** : IP of the vCenter server. Optional, if it is left blank the certificate check will error when you access vCenter on its IP.
-**Hostname** : FQDN or short name. This name is used to populate the Subject Alternative Names but it doesn't seem to pick up the short name. Certificate-manager also says that you can specify more than one names but... that doesn't work.
-**VMCA name**: Put a name that is relevant to you. It will be the issuer of the certificate. I used "xav.lab-VMCA".

Once the files are generated you can exit certificate-manager. 2 files are created at the location you specified. The certificate signing request and the private key (don't share it).

## 3. Obtain a vCenter machine SSL certificate from the CA with the mmc (no web enrollment).

This is where I found 98% of the how-tos on internet were using the web interface enrollment. I din't want to down the "IIS and 100 extra features" road to focus on vcenter and certificates. Because we can't request certificates on the web interface we need to use certreq.

-On the vCenter server start "certreq".
-Browse to the location you specified in certificate-manager and select the .csr (set file types to "All files *.*).
-Select your CA and click OK.

-On the PKI server launch the "Certification Authority".
-Go to "Pending Requests" > Right click on the certificate > "All tasks" > "Issue".
-Go to "Issued certificates" > Open the certificate > "Details" > "Copy to file" > Chose "Base 64 encoded X.509" and save it somewhere (I save it directly to a share \\srv-vcenter\certs\srv.cer).
-Right click on the CA > "Properties" > "View certificate" > Save it at the same location (\\srv-vcenter\certs\root.cer).
-You can now close the CA you won't need it anymore.

## 4. Install the certificate in vCenter.

-Go to the location where you stored the certificates and open them both in notepad.
-Copy the content of the CA root certificate, paste it at the end of the vCenter one and save it.
-(Once again that step doesn't work in certficate-manager so we go for the web UI) Open the PSC web management page: https://srv.xav.lab/psc
-Go to certificate management and punch in your credentials.
-In "Machine certificate" click "Replace" (Sorry my UI is half french half english.. weird).
-Browse to srv.cer containing the chain of certificates and to the .key file generated earlier.
-Once you get the popup for successful replacement you can close your browser.

That's the certificate replaced in vCenter. In the next step we configure VMCA to issue certificates with the right properties.

## 5. Customize the VMCA attributes and renew the solution users and Hosts certificates.

If you stopped here, VMCA would keep issuing certificates with the default VMware fields to the solution users and the hosts. Customizing them makes it much cleaner.

### Renew solution users certificates

-Start certificate-manager again and choose Option 4 > Press Y to reconfigure > Answer the prompt the same way we did earlier on.
-Press Y again to confirm the certificate regeneration and wait for it to finish, it can take some time. Monitor the prompt to make sure no error appears. If you get an error it might be because you made a mistake filling it in, remember the Hostname field can only take ONE record regardless of what the tool says.

That's now the solution certificates replaced by proper ones that you and your (paranoid) PKI team can identify, sweet.

But if you log on vCenter you still won't get the beloved green lock icon in the url bar. It is because the VMCA is not known by your client, hence not trusted. In the next step we will retrieve it and deploy it via GPO.

### Renew hosts certificates

-In vCenter right click on your hosts > "Certificate" > "Renew certificate"

That's it, your hosts now have certificates with the fields specified previously.

## 6. Make the VMCA a trusted root CA (the holy green lock).

-Open a browser to your vCenter: https://srv-vcenter.xav.lab
-On the right pane click on "Download Trusted Root certificate" and open the zip file. 
-In the "Win" folder you will find the original default vmca "CA" cert (not used anymore) and the one we modified "xav.lab-VMCA". Open the .crt files to find the latter.
-Save the certificate of the modified VMCA somewhere and copy it to your domain controller.
-Create another GPO to deploy the cert. I call it "xav.lab-VMCA Root CA".
-Edit it the same way we did the first time and pick the cert we downloaded from vCenter.
-Run "Gpupdate /force" on your clients and log back in vCenter.

You are now blessed by the VMCA and your connections are trusted.

The certificate will also be valid if you connect directly to an ESXi host.

And that's about it. You now have trusted certificates and a vCenter machine cert signed by the CA.

**Caveats:**

-The certificate won't be valid if you use short names on vCenter or ESXi.
-The certificate won't be valid on ESXi if you connect with the IP. It will be ok on vCenter unless you skipped the IP in certificate-manager.