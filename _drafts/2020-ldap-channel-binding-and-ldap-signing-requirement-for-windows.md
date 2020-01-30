---
layout: post
title: 2020 LDAP channel binding and LDAP signing requirement for Windows
DATE: 

---
In summer 2019 Microsoft [announced ](https://support.microsoft.com/en-ca/help/4520412/2020-ldap-channel-binding-and-ldap-signing-requirement-for-windows)an update scheduled for January 2020 that would change the default behavior of domain controllers with regards to the security of LDAP communications. After this change, domain controllers reject insecure LDAP communications. To quote Microsoft:

> ...reject Simple Authentication and Security Layer (SASL) LDAP binds that do not request signing (integrity verification) or to reject LDAP simple binds that are performed on a clear text (non-SSL/TLS-encrypted) connection.

The change has been delayed to March 2020 because too many customers and vendors didn't react and would face serious problems in production, and VMware is no exception. In order to avoid issues with your VMware environment, let's have a look at it.

#### vCenter

If your identity sources are configured as "Active Directory (Windows integrated)" or "LDAPS" you don't need to change anything.

If you have an identity source configured with "simple" LDAP you will face failed logins after the update. You need to [enable LDAPS](https://docs.vmware.com/en/VMware-vSphere/6.5/com.vmware.psc.doc/GUID-98B36135-CDC1-435C-8F27-5E0D0187FF7E.html). To enable LDAPS you will need the certificates of the domain controllers, the procedure is described [here](https://ldapwiki.com/wiki/Obtain%20a%20Certificate%20from%20Server).

#### Horizon

The VDI solution is [compatible ](https://kb.vmware.com/s/article/76062)with the update so nothing to do here. However you need to ensure that Horizon connects to vCenter using a secure identity source, otherwise the vCenter object will be in red in the Horizon manager health pane.

#### App Volumes