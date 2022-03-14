---
layout: post
title: Cool looking PowerShell with Oh-My-Posh
DATE: 
subtitle: ''
metadescription: Install Oh-My-Posh to customize and make your PowerShell prompt look
  better with system specific information
image: ''

---
I spent a lot less time in PowerCLI these days which means my profile hasn't changed much and my prompt was still the same as when I customized it several years ago. Because I use Linux in WSL, I have to get up to speed with it and customizing your prompt and profile is just part of the journey.

I work mostly in Windows Terminal and so far I'm using [Starship](https://starship.rs/) to customize WSL after being recommended by a colleague so I thought I'd try something else to refresh my PowerShell profile. I went for[ Oh My Posh](https://ohmyposh.dev/), a pretty similar shell customization tool and very easy to set up.

1. **Install** [**Windows Terminal**](https://www.microsoft.com/en-us/p/windows-terminal/9n0dx20hk701#activetab=pivot:overviewtab) if you don't already have it. (It doesn't have to be Windows Terminal).
2. **Install a** [**Nerd font**](https://www.nerdfonts.com/) to get icons support and set Windows Terminal to use it.
3. **Install** [**Oh My Posh**](https://ohmyposh.dev/docs/windows) in PowerShell.

<!-- I hate markdown -->

    Install-Module oh-my-posh -Scope CurrentUser

4. **Import the module** in your PowerShell profile ($PROFILE)

<!-- I hate markdown -->

    Import-Module oh-my-posh

5. **Set it up to use a** [**theme**]() of your choosing, Agnoster for instance. Add this to your PowerShell profile ($PROFILE).

<!-- I hate markdown -->

    Set-PoshPrompt -Theme agnoster

![](/img/ohmyposh1.png)

The prompt already looks cool but I want it to display which vCenter I am connected to. Something I used a lot in my previous profile. There is currently no support for this so we have to make our own.

6. **Export the current profile to a file**.

<!-- I hate markdown -->

    Export-PoshTheme -FilePath "~/.mytheme.omp.json" -Format json

7. **Edit the json file** and use the [TEXT](https://ohmyposh.dev/docs/text) feature to add a vCenter record next to the username. We will place the following fragment after the "sessions" section. This will check for an environment variable named ConnectedVCenter that we'll manage in the powershell profile.

<!-- I hate markdown -->

    {
    "background": "#cce9aa",
    "foreground": "#100e23",
    "powerline_symbol": "\ue0b0",
    "properties": {
    "template": "{{ if .Env.ConnectedVCenter }} \uf6a6 {{ .Env.ConnectedVCenter }} {{ end }}"
    },
    "style": "powerline",
    "type": "text"
    },

8. Now **edit your PowerShell profile** ($PROFILE). Remove or comment out the "Set-PoshPrompt" command and add the following fragment. This will populate an env variable when a vCenter is connected.

<!-- I hate markdown -->

    #Set-PoshPrompt -Theme agnoster
    
    oh-my-posh prompt init pwsh --config "~/.mytheme.omp.json" | Invoke-Expression
    
    function Set-EnvVar {
    $env:ConnectedVCenter = ($global:DefaultVIServers | where isconnected -eq $true).name
    }
    New-Alias -Name 'Set-PoshContext' -Value 'Set-EnvVar' -Scope Global -Force

Now the PowerShell prompt should show the connected vCenter(s). Pretty cool right?

![](/img/ohmyposh2.png)

Anyway, I played a bit with it so I thought I'd write a super short piece about it. A longer version of this article with a lot more details will come out on the Altaro blog at some point so watch this space.