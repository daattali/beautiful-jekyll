---
layout: post
title: VCSA update with IIS repository - Fix "Download failed" error
DATE: 

---
Whenever I have a boring task to do I try to find ways to make it a little more interesting. Usually there's some PowerCLI involved but not here. I needed to patch a vCenter Appliance (VCSA). It's not something you do often but I have quite a few vCenters. I also have a UMDS server with IIS on it for host patching so I thought why not use it as a repository for VCSA updates as well, instead of mounting an ISO like it's 1996. (Note that the vCenters have no access to internet so online repository is not an option).

Download the Appliance Update Bundle that comes as a zip file and contains 2 folders named "manifest" and "package-pool".

Go to the IIS server and extract the 2 folders from the zip file in the folder served by the web server. Something like "c:\\inetpub\\wwwroot\\vc-update-repo". Though as long as it's accessible in http you can put it wherever, I personally leave it in the UMDS_Store folder for simplicity's sake.

Then I typed the path in the custom repository field in the vCenter VAMI interface.

Which got me a "Download Failed" error under available updates.

To fix that one, go to your IIS server and add a "MIME Type" with the values "sign" / "text/html".

Once that's done the appliance accepts the repository and shows the available update. However when I tried to update I got a "Download Failed" error once again but in the next window. 

[https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5](https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5 "https://stackoverflow.com/questions/18625362/allowing-plus-character-in-path-in-asp-net-and-iis7-5")