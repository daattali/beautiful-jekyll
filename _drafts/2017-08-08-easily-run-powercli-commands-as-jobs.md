---
layout: post
published: false
title: Easily run PowerCLI commands as jobs
---
Running PowerCLI jobs is not as straightforward as it is with regular Powershell commands. If you try to run  a command that requires to be connected to a vCenter you will receive an error saying that the command is not recognized.

Start a job to get datastores.  
![job-ds-fail-1.jpg]({{site.baseurl}}/img/job-ds-fail-1.jpg)

Wait for the job to finish and place the result into the $ds variable.  
![job-ds-fail-2.jpg]({{site.baseurl}}/img/job-ds-fail-2.jpg)

This error occurs because the job create creates a new session which is not connected to vCenter and doesn't even have the PowerCLI module loaded. 

In order to run PowerCLI commands in parallel you need to import the module and connect to vCenter for every job.