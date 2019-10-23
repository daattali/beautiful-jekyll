---
layout: post
title: VCSA update with IIS repository - Fix "Download failed" error
DATE: 

---
Recently I needed to patch a vCenter Appliance (VCSA). It's not something we do often but I have quite a few vCenters. I also have a UMDS server with IIS 7 on it for host patching so I thought why not use it as a repository for VCSA updates instead of mounting an ISO like it's 1996. (Note that the vCenters have no access to internet so online repository is not an option).

Download the Appliance Update Bundle that comes as a zip file and contains 2 folders named "manifest" and "package-pool".

![](/img/repo-iis-vcsa1.JPG)

Go to the IIS server and extract the 2 folders from the zip file in the folder served by the web server. Something like "_c:\\inetpub\\wwwroot\\vc-update-repo_". Though as long as it's accessible in http by vCenter you can put it wherever, I personally leave it in the UMDS_Store folder for simplicity's sake.

Then go to the VAMI interface of the vCenter (https://srv-vcnt.local:5480) > **Update** > **Settings** > **Use specified repository** and type in the url where the 2 update folders are accessible.

![](/img/repo-iis-vcsa2.jpg)

![](/img/repo-iis-vcsa3.jpg)

#### Download Failed #1

When I validated I got a "Download Failed" error under available updates. This is because the "_Manifest_" folder contains files with the "_.sign_" extension which IIS does not know about and therefore returns a 404 error when trying to access it. [Credits to VMTN](https://communities.vmware.com/thread/533434).

![](/img/repo-iis-vcsa4.jpg)

![](/img/repo-iis-vcsa10-1.jpg)

To fix that one, go to your IIS server and add a "_MIME Type_" with the extension "_sign_" and type "_text/html_".

![](/img/repo-iis-vcsa5.jpg)

![](/img/repo-iis-vcsa6.jpg)

![](/img/repo-iis-vcsa7.jpg)

Once that's done the appliance accepts the repository and shows the available update.

#### Download Failed #2

When I tried to go ahead with the update I received a "Download Failed" error once again in the next window. I looked at the latest IIS logs and noticed that most files of the update were [returning ](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)http 200 (OK) except one http 404 (not found). I immediately saw that it is the only one with "+" in its name which is a special character (which are infamous troublemakers...).

located in **_c:\\inetpub\\logs\\LogFiles\\W3SVC1_**

![](/img/repo-iis-vcsa8-1.jpg)

If you try to open this file in a browser it results in a 404 as well.

![](/img/repo-iis-vcsa9.jpg)

After some digging I discovered that specials characters are rejected by default as a security measure (paranoia?) since IIS 7.

In order to allow the 'plus' characters, edit the "web.config" file located in the root directory of the website.

    <system.webServer>
        <security>
            <requestFiltering allowDoubleEscaping="true"/>
        </security>
    </system.webServer>

Restart the IIS website or service and VCSA can finally update from your IIS repository. As you can see my knowledge of IIS is function of my Googling skills but I got it to work in the end.