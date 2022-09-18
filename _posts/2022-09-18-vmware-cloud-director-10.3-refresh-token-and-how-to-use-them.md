---
layout: post
title: VMware Cloud Director 10.3 refresh token and how to use them
description: "Learn how to use the new API tokens in VMware Cloud Director 10.3.1"
date: 2022-09-18T15:48:51.295Z
nobanner: "yes"
fb-img: /img/vcd-api-tokens.png
img: /img/vcd-api-tokens.png
---
In the previous release of VMware Cloud Director with VCD 10.3, a number of new features and improvements were introduced around Kubernetes integration, vAPP mobility, VM placement and a lot more. However, what we are talking about here was release in VMware Cloud Director 10.3.1 and offers authenticated users to generate their own API tokens to grant access for automation against VMware Cloud Director.

As a side note, if you are looking for options on how to protect your VMware Cloud Director workloads, [Nakivo Backup & Replication](https://www.nakivo.com/vmware-cloud-director-backup/) offers capabilities to back up VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event. Not a lot of vendors out there support VCD so kuddos to that.

## What are API tokens

Like the suggests, API tokens are artifacts that third party applications use to authenticate against the VCD API to make request on behalf of a specific user to facilitate automation tasks (especially when mechanisms like MFA are involved). Before VCD 10.3.1, automating tasks in VMware Cloud Director was tricky as you had to be creative with third party solutions managing or intercepting API tokens.

VMware Cloud Director 10.3.1 includes the possibility to generate an API token for an authenticated user. Meaning the properties attached with the profile directly apply (quotas, permissions...) and MFA/2FA is already handled when the user logs in.

Note that the API token usage follows the OAuth 2.0 specifications which means that VCD acts as an OAuth application once an API token is generated.

One of the use cases I have been involved with for API tokens in VMware Cloud Director is CAPVCD (Cluster API Provider VMware Cloud Director). it is an open source project driven by VMware to build a VCD provider for Cluster API (CAPI) so you can create Kubernetes clusters in VCD by defining them in a Kubernetes management cluster. I wrote a [blog about CAPVCD](https://www.vxav.fr/2022-05-15-cluster-api-with-vmware-cloud-director-10.3-(capvcd),-nsx-t-and-alb/) a few months ago but I used version `0.5` which is already outdated.

## Why are API tokens more secure

Well, first of all, no one wants to use credentials for automation, I hope we all agree on that. Nne of the critical benefits of this feature is that API tokens can be revoked. Meaning if a token is compromised because someone pushed it to a git repo by mistake or if it was stolen, the user or an admin can revoke the token and subsequent API requests using it will be rejected.

![VMware Cloud Director API Tokens can be rejected](/img/2022-09-17-11-56-06.png)

On top of that, API tokens in VMware Cloud Director 10.3.1 cannot perform certain tasks:

* Change the user password
* Perform user management tasks
* Create more tokens
* View or revoke other tokens

They only have read-only rights for resources such as `user`, `groups`, `roles`, `right bundles` and do not have `Token: Manage*` rights.

## Generating an API token

Before you go create your API token, make sure your user has the `Manage user's own API token` right, otherwise the menu will not show up in the UI.

![VCD API token require right Manage User's own API token](/img/2022-09-17-11-59-25.png)

* Once authenticated, click on your username in the top right corner and then `User preferences`.

![VCD User preferences](/img/2022-09-17-12-00-49.png)

* Scroll down to the `Access Tokens` sections and click `New`. Again, if you don't see this section it means you don't have the `Manage user's own API token` right.

![VCD access tokens](/img/2022-09-17-12-02-07.png)

* Give the token a name that means something to you and click `CREATE`. This step is fairly important if you'll be creating several tokens for various applications. In case a token gets compromised you need to know which one to revoke and you can't display a token again after its creation.

![VCD new token](/img/2022-09-17-12-04-07.png)

* At this point the API token is created and displayed on screen. Now, go and store this token somewhere safe like lastpass, 1password and whatnot as once you click `OK` you can no longer display it and you'll need to create a new one if you forget this one!

![VCD API token created](/img/2022-09-17-12-13-19.png)

## Use VCD API token in PowerShell

Since my blog was originally a PowerCLI shop and I haven't done much of it in a while I thought it'd be nice to do the demo in PowerShell to get back to my roots. Note that you won't be using the API token to directly authenticate your API calls. You will use it to generate an access token (also called refresh token) with a `POST` call and use this one instead.

* Generate an Access token with the API token and store it in a variable.

``` powershell
> $access_token = Invoke-RestMethod -Method Post -Uri "https://<vcd-endpoint>/oauth/tenant/<tenant-name>/token" -Body @{"grant_type"="refresh_token";"refresh_token"="ZYbx7CFLNieHtrsx4WRxKAnROjwH5CwK"} -Headers @{"Accept"="application/json";"Content-Type"="application/x-www-form-urlencoded";"Content-Length"=71}

> $access_token

access_token
------------
eyJhbGciOiJSUzI1NiJ9.eyJzdWIi.....
```

* Create the Headers to authenticate API calls.

``` Powershell
$Headers = @{"Authorization"="Bearer $($access_token.access_token)";"Accept"="application/*+xml;version=36.1"}
```

* Now you can use the Headers to authenticate your API calls against the VCD API (more info in the [API reference doc](https://developer.vmware.com/apis/1260/vmware-cloud-director)). An example below where we list all virtual machines and display them in a table.

``` Powershell
$VMs = Invoke-RestMethod -Method Get -Uri "https://<vcd-endpoint>/vms/query" -Headers $Headers

> $VMs.QueryResultRecords.VMRecord | Format-Table
```

![VMs list in VCD Rest API](/img/2022-09-18-17-06-30.png)

I wrapped the steps to generate the Headers into a short PowerShell function to simplify it for you.

``` Powershell
Function Create-VcdApiHeaders {

param(
    [string]$VCDEndpointurl,
    [string]$Tenant,
    [string]$ApiToken
)

$access_token = Invoke-RestMethod -Method Post -Uri "$VCDEndpointurl/oauth/tenant/$Tenant/token" -Body @{"grant_type"="refresh_token";"refresh_token"=$ApiToken} -Headers @{"Accept"="application/json";"Content-Type"="application/x-www-form-urlencoded";"Content-Length"=71}

$env:Headers = @{"Authorization"="Bearer $($access_token.access_token)";"Accept"="application/*+xml;version=36.1"}

}
```

To use it, you simply run the function with parameters for the VCD endpoint uri, the tenant name and the API token. If it is successful, it will populate an environment variable named `$Headers` that you can use in your subsequent API calls and notify that the variable was populated.

![VCD API token powershell function](/img/2022-09-18-17-25-23.png)

## Wrap up

API tokens are a great addition to the product since VMware Cloud Director 10.3.1. I'm actually a little surprised this wasn't released before but better late than never I guess. Tasks automation against the VCD API will be facilitated and more secure.

Again, check out Nakivo Backup and Replication to protect VMware Cloud Director workloads. You can try it out with the [free trial](https://www.nakivo.com/resources/download/trial-download/).
