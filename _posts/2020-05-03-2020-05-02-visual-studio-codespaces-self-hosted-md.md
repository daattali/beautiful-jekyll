---
layout: post
published: false
title: 2020-05-02-visual-studio-codespaces-self-hosted.md
---
## Visual Studio Codespaces

If you didn't see the [news](https://devblogs.microsoft.com/visualstudio/introducing-visual-studio-codespaces/) - Microsoft have made Visual Studio Code available online using nothing but your web browser. There are 3 great plans for running the remote environments which offer small, medium and large CPU/Memory combinations and these should suit most simple updates to your code on the run. The environments are charged by the minute and I set mine to auto shutdown 30 minutes after i stop using them.

What really got me excited is the ability to self host a codespace environment - you can use your web browser to securely develop software from your own Virtual Machine, server or desktop.

### Great things about Visual Studio codespaces
- Use Visual Studo Code from your browser
- Use extenstions for Visual Studio code in your browser
- Easy to edit code or documentation without the need for time consuming local installs
- Want to update your code using Visual Studio Code from your iPad, tablet or phone? You can just open the web browser and you will have access to your development environment
- Because Visual Studio codespaces is authenticated using Azure AD you get all the benefits of [MFA](https://docs.microsoft.com/en-us/azure/active-directory/authentication/concept-mfa-howitworks) and [Azure AD Conditional Access](https://docs.microsoft.com/en-us/azure/active-directory/conditional-access/overview) to protect your development environment 

### Benefits of self hosted
- Use hardware you already have so you don't pay
- setup networking connectivity to your own database servers etc...

## Setting up a self-hosted Ubuntu 19.01

Sign up for preview then visit to create a codespaces to create a plan e.g. vso-myplan
https://online.visualstudio.com/environments

Go to https:portal.azure.com and use the search box to find the visual studio online plan by name - vso-myplan 

Select Raw details and copy the 
![screenshot of azure portal - raw detail tab ]({{site.baseurl}}/img/Screenshot 2020-05-03 at 09.34.45.png)

### Example
"/subscriptions/c931ad62-62d8-4f25-a0d3-c88aaaaabbbbb/resourceGroups/vso-rg-e315e92/providers/Microsoft.VSOnline/plans/vso-plan-eastus",

On your Ubuntu 19.01 VM use the following refer to the [instructions](https://docs.microsoft.com/en-us/visualstudio/online/reference/vsonline-cli#installation)

### Issue
For Ububntu 19.01 we dont't have instructions - I expected something like this would work but it didn't work for me sudo add-apt-repository https://packages.microsoft.com/ubuntu/19.01/prod/ - I therefor followed the generic Linux installation



1. Add the key