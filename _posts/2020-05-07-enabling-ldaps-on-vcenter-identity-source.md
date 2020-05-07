---
layout: post
title: Enabling LDAPS on vCenter identity source
DATE: 

---
Most environments used to use the Integrated Windows Authentication (IWA) as an identity source for vCenter. However with Microsoft tightening the screw on LDAP signing and VMware deprecating IWA in versions 7 and above, many will have to bite the bullet and move to LDAPS.

It's not a big deal to set up, it will however add some administrative overhead whenever a domain controller is expired, replaced or a new DC is added. Note that the permissions will be persisted if you are moving from IWA so you won't need to recreate them. You can delete the IWA identity source and add the LDAPS one.

This blog is an extract of a blog written for Altaro Software, you can find the full length article [here](https://www.altaro.com/vmware/understanding-ldap-binding-signing/). Let's go through the steps :

1. List the domain controllers in the domain that should be the identity source.

<code>nltest /dclist:xav.test</code>

![](/img/1.-List-all-domain-controllers-in-the-domain.png)

2. Run this command against each domain controller to retrieve their certificates and store them in .cer files.

<code>openssl s_client -connect xav-win-dc.xav.test:636 -showcerts</code>

![](/img/2.-Retrieve-the-certificates-of-each-domain-controller.png)

3. Log in vCenter using an SSO admin (administrator@vsphere.local) > Administration > Configuration > Identity sources.

![](/img/4.-Log-in-vCenter-using-an-SSO-admin.png)

4. Edit or create an LDAP source > Enable LDAPs on the identity source by checking “_Protect LDAP communication using SSL certificate (LDAPS)_” and click “_Next”_.

If you have an existing ldap source, clear the _primary server url field_ or it will incorrectly show _ldap_ instead of _ldaps_ even after the change.

![](/img/5.-Edit-the-LDAP-source.png)

5. Add each DC certificate in the list.

![Click 22Next22 and finish](https://s25967.pcdn.co/vmware/wp-content/uploads/2020/03/Click-22Next22-and-finish.png "Click Next and finish" =939x547)

The identity source should now show ldaps.

![](/img/7.-Complete-the-wizard.png)