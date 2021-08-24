---
layout: post
title: Collect SharePoint ULS Logs
subtitle: Some useful scripts to collect SharePoint ULS logs
gh-repo: lambertqin/lambertqin.github.io
gh-badge: [star, follow]
tags: [sharepoint, scripts, log]
comments: true
---

This is a post to list some useful scripts to collect SharePoint ULS logs.  

### Merge ULS logs with Time
~~~
$starttime = [DateTime]"2020-01-01 00:00:00"  
$endtime =  [DateTime]"2020-01-02 00:00:00"  
$logPath = "C:\Temp\merged_{0}_{1}.log" -f $starttime.ToString("yyyyMMddHHmmss"), $endtime.ToString("yyyyMMddHHmmss")  
Merge-SPLogFile -Path $logPath -StartTime $starttime -EndTime $endtime -Overwrite  
~~~

	
### Merge ULS logs by Correlation Id
~~~
$CorrelationId = ""  
Merge-SPLogFile -Path "C:\Temp\ULS_$CorrelationId.log" -Correlation $CorrelationId  
~~~



