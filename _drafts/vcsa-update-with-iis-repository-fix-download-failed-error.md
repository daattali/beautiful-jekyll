---
layout: post
title: VCSA update with IIS repository - Fix "Download failed" error
DATE: 

---
Whenever I have a boring task to do I try to find ways to make it a little more interesting. Usually there's some PowerCLI involved but not here. I needed to patch a vCenter Appliance (VCSA). It's not something you do often but I have quite a few vCenters. I also have a UMDS server with ISS for host patching so I thought why not use it as a repository for VCSA update as well instead of mounting an ISO like it's 1996. (Note that the vCenters have no access to internet so online repository is not an option).

[https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5](https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5 "https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5")