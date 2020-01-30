---
layout: post
title: 2020 LDAP channel binding and LDAP signing requirement for Windows
DATE: 

---
In summer 2019 Microsoft [announced ](https://support.microsoft.com/en-ca/help/4520412/2020-ldap-channel-binding-and-ldap-signing-requirement-for-windows)an update scheduled for January 2020 that would change the default behavior of domain controllers with regards to the security of LDAP communications. After this change, domain controllers reject insecure LDAP communications. To quote Microsoft:

> ...reject Simple Authentication and Security Layer (SASL) LDAP binds that do not request signing (integrity verification) or to reject LDAP simple binds that are performed on a clear text (non-SSL/TLS-encrypted) connection.

The change has been delayed to March 2020 because too many customers and vendors didn't react and would face serious problems in production.