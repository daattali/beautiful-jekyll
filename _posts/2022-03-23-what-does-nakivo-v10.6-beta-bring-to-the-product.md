---
layout: post
title: What does Nakivo v10.6 Beta bring to the product
metadescription: null
date: 2022-03-23T14:35:01.438Z
fb-img: null
nobanner: "yes"
---

Nakivo has been rolling out releases at an impressive rate with 4 minor versions in 2021. The company starts 2022 with the latest Beta v10.6 that brings several interesting features to stay at the tip of the spear. With great processing power comes great attackability (if that is even a word), companies are consuming ever more cloud services and software attacks are increasing in number and sophistication. For that reason, every software vendor needs to step up and offer secure environments to their customers. Nakivo is doing just that with this new Beta v10.6 release which includes, among other things, security hardening and cloud services backup support, two areas that are being heavily invested in in recent years.

![try nakivo v10.6 beta](/img/2022-03-25-20-43-27.png)

## NAS Backup

While NAS devices (network shares) are often used as repositories when discussing backup topics, they also host critical company data that needs backing up one way or another. There are various ways to go about achieving this but you usually want to avoid extra third party software solutions or custom scripts. In which case, integrating the backup of your network shares to your backup solution improves visibility, traceability and maintainability of your environment. Nakivo Beta v10.6 offers the capability to back up file and folders within file shares on NAS devices and recover the entire share or specific files. This feature currently support NFS and CIFS (SMB) protocols.

## Hardened AMI

As mentioned earlier, the IT security landscape has been cripled by nasty ransomware attacks over the last few years and Backup solutions are a prime choice for bad actors as it will seriously jeopardize further data recovery attempts. Nakivo B&R v10.5 brought security features to mitigates these risks including hardened virtual appliance. Nakivo v10.6 beta introduces another feature following the same tracks with Hardened AMI (Amazon Machine Image). The point of Hardened AMI is to act as a safeguard against ransomware and accidental deletion. It is deployed as an Amazon Machine Image that runs Ubuntu Server and it will protect the backups sent to a repository that was deployed as part of the AMI against ransomware.

## Microsoft 365 Groups Backup

If protecting virtual machines is the bread and butter of Nakivo and what took the company where it is today, integration features such as file and item backup and restore have been must have features for a long time now. Being able to recover individual files, AD objects or other supported application items saved the day in many instances! Nakivo v10.6 beta brings these same capabilities to the cloud with Microsoft 365 Groups Backup, a feature that allows to back up and restore group mailboxes, including mail, files, and OneNote items, as well as group sites with document libraries, lists, and subsites.

## External Database for NAKIVO Backup & Replication

New features are cool, product stability is best! In some instances of clients running large environments, it appeared that the built-in database in NAKIVO Backup & Replication can end up corrupted or simply cannot cope with the demand, incurring disruptons and delays in the backup workflow. In order to tailor for these edge cases, Nakivo v10.6 beta offers the possibility to use an external database to offload the stress from the Backup servers.

## Backup from Nimble Storage Snapshots

While this feature will not be useful to everyone, those Nimble Storage customers will be happy to hear that Nakivo thinks about you. Nakivo B&R Bv10.6 beta with direct SAN access by leverage array volume snapshots instead of the traditional VM snapshots. This will have the benefit of reducing the processing power overhead on your infrastructure caused by the Backup solution, Backup Windows should be a lot more flexible since it will happen in the background and reduce the risk of VM snapshots leftovers.

## Claim your $20 Amazon Gift card

![Nakivo $20 amazon gift card beta 10.6](/img/2022-03-24-20-05-14.png)

Claim a $20 Amazon eGift card by downloading and testing [Nakivo v10.6 beta](https://www.nakivo.com/resources/releases/10.6-beta/). Follow these steps to get yours:

1. Download v10.6 Beta and proceed with one of the options in the download page.
2. Send the support bundle indicating the option you chose
3. to support@nakivo.com by April 15th, 2022.
4. Share your feedback by filling out a short survey.

## Wrap up

Another day, another version of Nakivo Backup and Replication. If you are interesting in latest features and want to treat yourself on Amazon, Nakivo currently offers a $20 voucher to anyone who will be willing to help the company in the testing effort along the way by downloading Nakivo v10.6 beta and sending a support bundle after testing specific features.
