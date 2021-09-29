---
layout: post
title: vSphere environments in the Ransomware landscape
DATE: 
subtitle: ''
metadescription: How does Ransomware attacks work and how to protect from ransomware
  attacks on VMware ESXi.

---
A sense of fear is glooming in corporate organizations with the threat of Ransomware attacks in these last few years and even ransomware attack on vmware esxi more recently. The number of horror stories about companies getting their datastores encrypted is growing. I have been following it from a distance but vSphere 7 Update 3 really hit home with the announcement of a new [VMware page dedicated to ransomware](https://core.vmware.com/ransomware).

The problem with ransomware is that everyone knows what it is but many don't know how to protect from it. Some tend to think you need some sort of anti-virus that protects from ransomware attacks but the reality is that ransomware is just the payload. The intrusion itself comes from the same channels as more traditional viruses. In which case, protecting from ransomware attack on vmware esxi should be as easy as following security best practices.

### VMware Ransomware Resource Center

You can tell that ransomware attack is topical and deserves our attention when software vendors such as VMware increase communication on the topic and deploy a dedicated page to it. [VMware Ransomware Resource Center](https://core.vmware.com/ransomware)

The resource center is a great way to offer administrators and management personal a centralized location with educational content and best practices to implement.

![Resource center to learn about ransomware attacks on vmware esxi](/img/ransom1.png)

You will find links to the VMware vSphere Security Configuration Guide (formerly hardening guide), a long list of [best practices ](https://core.vmware.com/ransomware)to adopt, how to properly patch environments as well as white papers and videos filled with valuable information.

I strongly suggest you have a look at that website and go through, at least, the first 3 links.

### How does a ransomware attack on vSphere work?

We will have a brief look at how ransomware attack on vmware esxi work. You can get more information in a blog I wrote for Altaro (I'll add the link when it's published).

![](/img/ransom2.png)

In a nutshell and like I mentioned earlier, the attack usually comes from the "traditional" channels of attacks. That being social engineering, phishing malware, publicly exposed remote servers and even vCenters, iDRAC... (check out [https://www.shodan.io/](https://www.shodan.io/ "https://www.shodan.io/"), it's mortifying!).

Anyway, once the attacker is in the network:

1. He/she will try to escalate privileges (with [CVE-2020-1472 ](https://msrc.microsoft.com/update-guide/vulnerability/CVE-2020-1472)for instance)
2. Get access to a management box, either get access to vCenter if the account can or use a vulnerability such as [CVE-2019-5544](https://www.vmware.com/security/advisories/VMSA-2019-0022.html), [CVE-2020-3992](https://www.vmware.com/security/advisories/VMSA-2020-0023.html) or [CVE-2021-21985](https://www.vmware.com/security/advisories/VMSA-2021-0010.html) for instance
3. Process to shut down the VMs and encrypt the content of the datastores with an [ELF executable](https://securelist.com/ransomexx-trojan-attacks-linux-systems/99279/) on each vSphere host and leave a ransom note in the datastore for the VI admin to find.

Now if it happens, **it is recommended against paying the ransom** as there is no garanty you will get your data back. Your best course of action is to do a deep anti-virus sweep across all of your IT environments (workstations especially) and restore the servers from Backup.

### How to protect from ransomware attacks on vSphere ESXi

As mentioned earlier, there is no magic anti-virus that will prevent ransomware or get rid of it should you get hit. The best way to protect from it is to implement industry standard best practices and harden your VMware environment.

* Follow the [**VMware security configuration guide** ]()(encompasses all the VMware related best practices).
* Do not expose any service to internet (obvious but hey...).
* Avoid third party vCenter plugins.
* Enable Secure Boot and vSphere Trust Authority in vSphere.
* Use different user/password for vCenter, hosts, out-of-band cards etc...
* **Educate your user** on virus, phishing and social engineering.
* **PATCH YOUR SYSTEMS... ALL OF THEM**.
* Use 2FA on vCenter and on a bastion (use a bastion).
* Restrict management network access to trusted admins (IP ranges etc...).
* **Secure Active Directory** (most attacks go for the AD first).
* Use syslog servers for audit trails.
* Use a solid and secure password manager (no browser saved credentials).
* Antivirus on workstations and servers.
* **Have a solid backup strategy** with good retention and make sure the [backups are protected](https://www.altaro.com/backup-dr/ransomware-best-practices-backup/) (air-gapped).

### Conclusion

Anyway, is there really a conclusion to this ever changing madness? Every organization wants to protect from ransomware attack on vmware esxi. You should be fine as long as you strictly follow the sensible best practices and don't cut corners to save time (ALLOW ANY ANY, we've all done it, don't lie to yourself...).

I think educating users, especially those with admin access, is as important, if not more, as all the other recommendations. It is also a way of putting best practices in everyone's mind and indrectly future proofing the population as a whole. That way you tackle the problem from the technical and the human angles.

Either way, keep your systems up to date... At least the security patches, come on!