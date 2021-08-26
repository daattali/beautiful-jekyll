---
layout: post
title: Clear SharePoint Configuration Cache
subtitle: step by step to clear SharePoint configuration cache
gh-repo: lambertqin/lambertqin.github.io
gh-badge: [star, follow]
tags: [sharepoint, tools, cache]
comments: true
---

This is a post contains step-by-step guide to clear SharePoint configuration cache

1. Stop the Timer service. To do this, follow these steps:  
  a. Click Start, point to Administrative Tools, and then click Services.  
  b. Right-click SharePoint Timer Service, and then click Stop.  
  c. Close the Services console.  
2. On the computer that is running Microsoft Office SharePoint Server open Windows Explorer, locate %allusersprofile%\Microsoft\SharePoint\Config\GUID
3. Back up the Cache.ini file.
4. Delete all the XML configuration files in the GUID folder. Do this so that you can verify that the GUID folder is replaced by new XML configuration files when the cache is rebuilt. 
> Note: When you empty the configuration cache in the GUID folder, make sure that you do not delete the GUID folder and the Cache.ini file that is located in the GUID folder.
5. Double-click the Cache.ini file.
6. On the Edit menu, click Select All.
7. On the Edit menu, click Delete.
8. Type 1, and then click Save on the File menu.
9. On the File menu, click Exit.
10. Start the Timer service. To do this, follow these steps:  
  a. Click Start, point to Administrative Tools, and then click Services.  
  b. Right-click SharePoint Timer Service, and then click Start.  
  c. Close the Services console.  
> Note: The file system cache is re-created after you perform this procedure. Make sure that you perform this procedure on all servers in the server farm.


Besides the manually steps, you can try spcachecleaner [tool](https://github.com/DwayneSelsig/spcachecleaner)(https://github.com/DwayneSelsig/spcachecleaner) to clear the SharePoint Configuration Cache.
