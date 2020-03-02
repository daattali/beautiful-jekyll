---
layout: post
published: true
title: Using self-hosted GitHub runner
tags:
  - GitHub
  - ADO
  - CICD
subtitle: CI/CD in GitHub.
date: '2020-03-02'
---
## In case you haven't heard - Microsoft now has two great DevOps products. 
- [Azure DevOps](https://azure.microsoft.com/en-us/services/devops/)
- [GitHub](https://azure.microsoft.com/en-us/solutions/devops/#github)

Both are still very well supported and I have a number of conversations day to day with people who use both GitHub and Azure DevOps.

This post is a quick intro into running a self-hosted agent in GitHub. For those who are used to Azure DevOps the steps are familiar but the UI is differrent. 

## Differences between Azure DevOps and GitHub
- Azure DevOps has **Pipelines** for CI/CD, GitHub has **Actions**
- Azure DevOps has [Microsoft-hosted and self-hosted Pipeline](https://docs.microsoft.com/en-us/azure/devops/pipelines/agents/agents?view=azure-devops&tabs=browser) **Agents**, GitHub has [GitHub-hosted and self-hosted](https://help.github.com/en/actions/hosting-your-own-runners/about-self-hosted-runners) **runners**

The steps are pretty simple:
- Open your GitHub account and copy script from settings
- Add a new workflow to your GitHub repository to use your agent

## Add your runner in GitHub settings | Actions
1) Select Settings | Actions then **Add runner**
![Image of GitHub Settings page with Actions menu selected]({{site.baseurl}}/img/github-runner.png)

2) Copy the Download script (note it includes the token to authenticate)
![github-runner2a.png]({{site.baseurl}}/img/github-runner2a.png)

3) Run on your VM
![github-runner3.png]({{site.baseurl}}/img/github-runner3.png)

4) Your runner should show in self-hosted runner
![github-runner4.png]({{site.baseurl}}/img/github-runner4.png)

5) Create a new workflow and add your code
![github-runner-workflow1.png]({{site.baseurl}}/img/github-runner-workflow1.png)

6) Select **Set up a workflow yourself**
![github-runner-workflow2.png]({{site.baseurl}}/img/github-runner-workflow2.png)

7) Enter a sample script (uses YAML - if you are new to YAML use a [YAML verifier](https://codebeautify.org/yaml-validator/))

```yaml
name: CI-Self-Hosted

on: [push]

jobs:
  build:

    runs-on: self-hosted

    steps:
    - uses: actions/checkout@v2
    - name: Run a multi-line script
      run: |
        echo Hello from Workflow!
        hostname
```

8) Commit it
![github-runner-workflow-commit.png]({{site.baseurl}}/img/github-runner-workflow-commit.png)

9) Review the output
![github-runner-workflow-results.png]({{site.baseurl}}/img/github-runner-workflow-results.png)

## Summary
For those used to the simplicity of configuring Azure DevOps Pipelines visually losing this option and moving to YAML may be a little scary at first however once you get used to it I believe GitHub Actions will be a great engine for both your opensource and enterprise applications.
