---
layout: post
title: How to fix VAMI stuck on "Update installation in progress"
DATE: 

---
If you ever get in a situation where an update of the vCenter Server Appliance is interrupted for any reason, you may get an error message "Update installation in progress" and find that you are unable to log in the VAMI. 

![](/img/updateinstallstuck.png)

In my case it was in my disposable Workstation lab; I started the update from 7.0.1.00100 to 7.0.1.00300 in the evening because it's a 5GB gig and I have a slow connection at the moment and I didn't want it to hinder my Netflix experience. Problem is I forgot to disable Windows' standby mode so workstation was stopped and the VMs with it, I know, silly...

Anyway, I found [KB67179 ](https://kb.vmware.com/s/article/67179)that describes the following procedure on how to fix it. 

1. **Make a copy of "/etc/applmgmt/appliance/software_update_.conf"_ you most likely won't need it.**

    cp /etc/applmgmt/appliance/software_update_state.conf /home/software_update_state.conf

2. **Stop the _applmgmt_ service which handles appliance configuration and provides public API endpoints for appliance lifecycle management.**

    service-control --stop applmgmt

![](/img/updateinstallstuck2.png)

3. **Remove the "_software_update_state.conf"_ file**

    rm /etc/applmgmt/appliance/software_update_state.conf

4. **Then start the applmgmt service back up.**

    service-control --start applmgmt

![](/img/updateinstallstuck3.png)

5. **Go back to the VAMI interface and try to log back in, it should work now.**

Note that when checking for update after logging back in I had to check for updates a few times before getting it back to normal. The first one I got was an error, then 7.0.1.00300 would not appear (only 7.0.1.00200) and on the third try everything was fine.