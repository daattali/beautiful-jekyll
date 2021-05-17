---
layout: post
published: true
title: List Azure DevOps Repos
date: '2021-05-17'
subtitle: Example of how to interact with Azure DevOps using the Azure CLI Example 
---

## Problem
How do I get all the URLs for my repos in Azure DevOps?

## Solution
Use the [Azure DevOps CLI extension](https://docs.microsoft.com/en-us/azure/devops/cli/?view=azure-devops#:~:text=%20To%20start%20using%20the%20Azure%20DevOps%20extension,you%20set%20the%20default%20configuration%20for...%20More%20)

This is a sample PowerShell script

```
param( [string]$Organization )

$orgUrl = "https://dev.azure.com/$Organization"

# Ensure  signed in to Azure
$AccountInfo = az account show 2>&1
try {
    $AccountInfo = $AccountInfo | ConvertFrom-Json -ErrorAction Stop
}
catch {
    az login --allow-no-subscriptions
}

$DevOpsExtension = az extension list --query '[?name == ''azure-devops''].name' -o tsv
if ($null -eq $DevOpsExtension) {
    $null = az extension add --name 'azure-devops'
}

$Projects = az devops project list --organization $orgUrl --query 'value[].name' -o tsv
foreach ($Proj in $Projects) {
    $Repos = az repos list --organization $orgUrl --project $Proj | ConvertFrom-Json
    foreach ($Repo in $Repos) {
        Write-Output $Repo.webUrl
    }
}
```

Here is a sample showing output.
```
PS C:\Dev\ado-api> & .\getRepos.ps1
https://dev.azure.com/exampleorg/java-jsf1/_git/java-jsf1
https://dev.azure.com/exampleorg/Jan2021Example/_git/Jan2021Example
https://dev.azure.com/exampleorg/B2C%20Brownbag/_git/B2C%20Brownbag
```
## Credits
Thanks to Simon Wahlinfor the [post](https://blog.simonw.se/cloning-all-repositories-from-azure-devops-using-azure-cli/)

