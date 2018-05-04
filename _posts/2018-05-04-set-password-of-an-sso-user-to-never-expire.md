---
layout: post
published: true
title: Set password of an sso user to never expire
---
In vCenter, users created on the vSphere SSO domain (vphere.local by default) all share the same password policy defined in **Single Sign-On** > **Configuration** > **Policies** > **Password Policy** with a default password expiration after 90 days. For "interactive" users it's probably a good thing to keep them on their game, but if you are using sso users for services (not that you should, that's what AD service accounts are for but you know...) their password will expire after 90 days and the service will break. _Note that you can change the password policy to "never expire" by setting it to 0 day._

![vcenter-pass-policy.jpg]({{site.baseurl}}/img/vcenter-pass-policy.jpg)

There is a way to force the password of an SSO user to never expire with the **dir-cli** command line tool on the vCenter server.

- Windows vCenter : C:\Program Files\VMware\vCenter Server\vmafdd\

- VCSA : /usr/lib/vmware-vmafd/bin/

## Edit the sso user

- Log on your vCenter and browse to the location mentioned above

- Check the name of the sso user:

```
./dir-cli user find-by-name --account srv-my-user
Enter password for administrator@vsphere.local:
Account: srv-my-user
UPN: srv-my-user@vsphere.local
```

Note that if the password already expired you need to reset it. You can do it in the web client or via the following command:

```
./dir-cli password reset --account srv-my-user --password OldPassw0rd --new NewPassw0rd
Password was reset successfully for [srv-my-user]
```

- Set the password to never expire:

```
./dir-cli user modify --account srv-my-user --password-never-expires
Enter password for administrator@vsphere.local:
Password set to never expire for [srv-my-user]
```
