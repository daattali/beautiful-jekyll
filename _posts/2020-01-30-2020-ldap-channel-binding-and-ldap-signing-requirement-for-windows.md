---
layout: post
title: 2020 LDAP channel binding and LDAP signing requirement for Windows
DATE: 

---
In summer 2019 Microsoft [announced ](https://support.microsoft.com/en-us/help/4520412/2020-ldap-channel-binding-and-ldap-signing-requirement-for-windows)an update scheduled for January 2020 that would change the default behavior of domain controllers with regards to the security of LDAP communications. After this change, domain controllers will reject insecure LDAP communications regarding [LDAP signing](https://support.microsoft.com/en-us/help/935834/how-to-enable-ldap-signing-in-windows-server-2008) and [LDAP Channel binding](https://support.microsoft.com/en-us/help/4034879/how-to-add-the-ldapenforcechannelbinding-registry-entry). To quote Microsoft:

> ...reject Simple Authentication and Security Layer (SASL) LDAP binds that do not request signing (integrity verification) or to reject LDAP simple binds that are performed on a clear text (non-SSL/TLS-encrypted) connection.

The change has been delayed to March 2020 to wait after the 2019 holidays. Many administrators restrict configuration changes during the holiday season and they needed to give them more time to prepare and test...

***

_EDIT 14/02/2020:_

Microsoft pushed the date to later in 2020 in an updated advisory [ADV190023](https://portal.msrc.microsoft.com/en-us/security-guidance/advisory/ADV190023) stating that:

> ...The Updates in March 2020 add new audit events, additional logging, and a remapping of Group Policy values that will enable hardening LDAP Channel Binding and LDAP Signing. The March 2020 updates do not make changes to LDAP signing or channel binding policies or their registry equivalent on new or existing domain controllers.

The change that will enable LDAP signing and channel binding on domain controllers configured with default values is now scheduled for '_the second half of calendar year 2020_'.

***

#### vCenter

If your identity sources are configured as "Active Directory (Windows integrated)" or "LDAPS" you don't need to change anything.

If you have an identity source configured with "simple" LDAP you will face failed logins after the update. You need to [enable LDAPS](https://docs.vmware.com/en/VMware-vSphere/6.5/com.vmware.psc.doc/GUID-98B36135-CDC1-435C-8F27-5E0D0187FF7E.html). To enable LDAPS you will need the certificates of the domain controllers, the procedure is described [here](https://ldapwiki.com/wiki/Obtain%20a%20Certificate%20from%20Server).

***

#### Horizon

The VDI solution is [compatible ](https://kb.vmware.com/s/article/76062)with the update so nothing to do here. However you need to ensure that Horizon connects to vCenter using a secure identity source, otherwise the vCenter object will be in red in the Horizon manager health pane.

***

#### App Volumes

_EDIT 03/02/2020:_

_As I observed in my lab, App Volumes is not compatible with Channel binding as of version 2.18. See_ [_KB77093_](https://kb.vmware.com/s/article/77093)_. VMware is working on a fix, in the meantime it is recommended by VMware to set the registry key LdapEnforceChannelBinding to 0._

Like with vCenter, you need to enable LDAPS or TLS encryption in the AD domain pane. Otherwise you will also fail to connect to it using domain credentials. Find the procedure to enable LDAPS [here](https://docs.vmware.com/en/VMware-App-Volumes/2.18/com.vmware.appvolumes.admin.doc/GUID-4EA6EF73-7800-4241-9162-2C407AC4AA7A.html). Note that it is recommended to enable certificate verification but it will still work without it.

***

#### Other software

This does not only affect VMware but any solution that talks with a Windows domain controller. Microsoft explains [here ](https://support.microsoft.com/en-ca/help/935834/how-to-enable-ldap-signing-in-windows-server-2008)who to identify who in your network is making insecure communications.