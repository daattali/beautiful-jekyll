---
layout: post
title: 'ERROR certificate-manager ''lstool get'' failed: 1'
DATE: ''
date: 2019-04-02 15:24:47 +0200

---
The other day I had to replace the machine SSL certificate on a vCenter Server Appliance 6.5. Since vCenter 6.0 the process of replacing a certificate has been greatly simplified, the certificate-manager script basically takes care of everything which is really nice.

However, this time I encountered an error when replacing the certificate. Everything was going smoothly until the moment where the script threw an error and started a roolback.

> "2019-04-01T09:38:53.83Z  certificate-manager Error while replacing Machine SSL Cert, please see /var/log/vmware/vmcad/certificate-manager.log for more information."

So I looked into the certificate-manager.log logfile and found the following line:

> "2019-04-01T09:38:53.83Z ERROR certificate-manager 'lstool get' failed: 1"

I have no idea what this means so I googled it and ended up on [KB2150057](https://kb.vmware.com/s/article/2150057). The outcome of this KB is that this error occurs when there are third party extensions installed on the vCenter.

> "This issue occurs when there are third party extensions like nimble storage and veeambackupUI etc. with no valid certificates and failed to get the information for the service ID."

Sure enough there was an old Simplivity extension installed on the server that had been used at some point for a proof of concept but no longer needed. I found the procedure to remove the extension in an [HPE documentation](https://support.hpe.com/hpsc/doc/public/display?docId=emr_na-sv760_000259_aen_us&docLocale=en_US) (they bought the company in 2017), which I performed on the appliance.

> cd /opt/SimpliVity/SimpliVityExtensionForVSphereClient-10.23.8/
>
> ./uninstall
>
> Y
>
> service-control --stop vsphere-ui vsphere-client
>
> cd /etc/vmware/vsphere-client/vc-packages/vsphere-client-serenity
>
> rm -r com.simplivity.web-client-10.23.8
>
> cd /etc/vmware/vsphere-ui/vc-packages/vsphere-client-serenity
>
> rm -r com.simplivity.web-client-10.23.8
>
> service-control --start vsphere-ui vsphere-client

![](/img/lstoolget1.jpg)

I kept getting the same error after this so I proceeded to the Resolution section of the KB with [KB1025360](https://kb.vmware.com/s/article/1025360?CoveoV2.CoveoLightningApex.getInitializationData=1&r=0&ui-communities-components-aura-components-forceCommunity-seoAssistant.SeoAssistant.getSeoData=1&other.KM_Utility.getArticleDetails=1&other.KM_Utility.getArticleMetadata=2&other.KM_Utility.getUrl=1&ui-comm-runtime-components-aura-components-siteforce-recordservicecomponent.RecordServiceComponent.getArticleVersionId=2&other.KM_Utility.getUser=1&other.KM_Utility.getAllTranslatedLanguages=2&ui-comm-runtime-components-aura-components-siteforce-qb.Quarterback.validateRoute=1&ui-communities-components-aura-components-forceCommunity-navigationMenu.NavigationMenuDataProvider.getNavigationMenu=1) and unregistered the extension from the MOB (Managed Object Browser).

* Browse to http://vCenter_Server_name_or_IP/mob
* Click on **Content.**

![](/img/lstoolget2.jpg)

* Click on **ExtensionManager**.

![](/img/lstoolget3.jpg)

* Expand the list of properties and locate the extensions to remove. Here there are 3 Simplivity extensions being displayed. **Copy the part in double quotes**.

![](/img/lstoolget4.jpg)

* Click on **UnregisterExtension**.

![](/img/lstoolget5.jpg)

* Paste the string you copied without the double quotes in the string field and click **Invoke Method**.

![](/img/lstoolget6.jpg)

* Refresh the page and verify that the line is no longer in the list of properties.

![](/img/lstoolget7.jpg)

* Repeat these steps for all the extensions that need unregistered.

After I finished this task the certificate replacement completed successfully.