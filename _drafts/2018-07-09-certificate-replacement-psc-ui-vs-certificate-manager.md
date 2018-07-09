---
layout: post
published: false
title: 'Certificate replacement: PSC UI vs certificate-manager'
---
If you ever had to replace certificates in vSphere 6.0 and 6.5 you may know that there are two different ways to do it. The first one using the [PSC web UI](https://docs.vmware.com/en/VMware-vSphere/6.5/com.vmware.psc.doc/GUID-FEEAB88E-D888-403F-AA62-1074585F7FEB.html) and the second one using the embedded [certificate-manager utility](https://docs.vmware.com/en/VMware-vSphere/6.7/com.vmware.psc.doc/GUID-0CBFCF72-C6AD-4CF0-BF44-F4414BBDD91C.html). Now you may also think that these 2 methods produce a similar result. And why shouldn't you? Well, unfortunately it is not the case.

The Lookup service is a PSC service that maintains a table of all the services registered. It contains their URL, certificate, solution user and a bunch of obscur things. It is used by services themselves so they can find one another and communicate securely with each other. I mentioned "certificates" in the list of properties registered in the Lookup service and this is where the issue is regarding the way we replace certificates.

## PSC UI vs certificate-manager

Both method will replace the machine SSL certificate and have the web client use it. Meaning you will not receive a certificate error when opening it in a browser (provided the signing root CA is in your trusted root CAs). It is why this issue is so confusing, the certificate appears changed but it may not be in the background!

When you run the **certificate-manager** utility, you will see at the end that a number of services have been updated (more than 25). And if you look at the certificates in the registered services you will see the new one.

If you use the **PSC UI** however, a quick look at the registered services will show you that the old one is still being used. Which will lead to errors when external services try to interact with vCenter (check out [KB2109074](https://kb.vmware.com/s/article/2109074?lang=en_US)). Example below with Site Recovery Manager:

## You already replaced it with the PSC UI

Fortunately there is a way to update the certificate of the registered service using a python script embedded in vCenter. The script will locate the old certificates using its thumbprint and replace it with the new one.

The procedure looks cumbersome by the length of the KB but it's only one command that looks like so:

```Powershell
python ls_update_certs.py --url https://psc.vmware.com/lookupservice/sdk --fingerprint 11:11:AF:D8:CF:27:6B:EF:F7:49:20:3E:D7:90:8C:F6:A0:A2:E2:30 --certfile /certificates/new_machine.crt --user Administrator@vsphere.local --password "Password"
```

[Embedded PSC](https://kb.vmware.com/s/article/2121689?ui-force-components-controllers-hostConfig.HostConfig.getConfigData=1&r=2&other.KM_Utility.getArticleDetails=1&other.KM_Utility.getArticleMetadata=1&other.KM_Utility.getAllTranslatedLanguages=1&ui-comm-runtime-components-aura-components-siteforce-qb.Quarterback.validateRoute=1)

[External PSC](https://kb.vmware.com/s/article/2121701?ui-force-components-controllers-hostConfig.HostConfig.getConfigData=1&r=2&other.KM_Utility.getArticleDetails=1&other.KM_Utility.getArticleMetadata=1&other.KM_Utility.getAllTranslatedLanguages=1&ui-comm-runtime-components-aura-components-siteforce-qb.Quarterback.validateRoute=1)