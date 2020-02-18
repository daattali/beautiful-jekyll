---
layout: post
title: How to sign a certificate with no template information on a Microsoft CA
DATE: 

---
If you have a basic Microsoft CA for lab or production purpose you cannot sign a certificate without a template. However the certificate manager utility included in vCenter or OpenSSL creates CSR file which is rejected by the Microsoft CA on the ground that it has no template extension.

> The request contains no certificate template information. 0x80094801 (--2146875391 CERTSRV_E_NOT_CERT_TYPE)

![](/img/certtemplate1.png)

There is a simple trick that consists in attributing a template to the csr during the signing process.

1. Open a command prompt as a domain user which has permissions to sign certificates
2. (Optional) You can get the list of templates using this command:

       certutil -CATemplates -Config Machine\CAName

![](/img/certtemplate2.png)

3. Run certreq with the attrib parameter and specify the template you want to apply (Usually _WebServer_ will do).

    certreq -attrib "CertificateTemplate:WebServer"

A popup then asks you to specify the csr file to sign.

![](/img/certtemplate3.png)

4. Then select the CA to use.

![](/img/certtemplate4.png)

5. Give a name and location to the certificate to produce.

![](/img/certtemplate5.png)

6. The output of the certreq command should like something like this.

![](/img/certtemplate6.png)

7. The certificate should new appear in the list of issued certificate in the CA's console.

![](/img/certtemplate7.png)