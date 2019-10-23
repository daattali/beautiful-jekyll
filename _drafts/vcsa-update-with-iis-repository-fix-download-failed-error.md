---
layout: post
title: VCSA update with IIS repository - Fix "Download failed" error
DATE: 

---
Recently I needed to patch a vCenter Appliance (VCSA). It's not something we do often but I have quite a few vCenters. I also have a UMDS server with IIS on it for host patching so I thought why not use it as a repository for VCSA updates instead of mounting an ISO like it's 1996. (Note that the vCenters have no access to internet so online repository is not an option).

Download the Appliance Update Bundle that comes as a zip file and contains 2 folders named "manifest" and "package-pool".

![](/img/repo-iis-vcsa1.JPG)

Go to the IIS server and extract the 2 folders from the zip file in the folder served by the web server. Something like "c:\\inetpub\\wwwroot\\vc-update-repo". Though as long as it's accessible in http you can put it wherever, I personally leave it in the UMDS_Store folder for simplicity's sake.

Then I typed the path in the custom repository field in the vCenter VAMI interface.

#### Download Failed #1

Which got me a "Download Failed" error under available updates.

To fix that one, go to your IIS server and add a "MIME Type" with the values "sign" / "text/html".

Once that's done the appliance accepts the repository and shows the available update.

#### Download Failed #2

When I tried to update I got a "Download Failed" error once again but in the next window.  I looked in the IIS logs and noticed that most files of the update were [returning ](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)http 200 (OK) except one http 404 (not found). I immediately saw that it is the only one with "+" in its name which is a special character (which have always caused problems everywhere...).

After some digging I discovered that specials characters are rejected by default as a security measure (paranoia?) since IIS 7.

In order to allow the 'plus' characters, edit the "web.config" file located in the root directory.

    <system.webServer>
        <security>
            <requestFiltering allowDoubleEscaping="true"/>
        </security>
    </system.webServer>

Then restart the IIS website or service and VCSA can finally update from your IIS repository.