---
categories:
  - blog
title: Full Featured IDE For Bash Scripting
subtitle: How to get a full featured IDE for bash
tags: [sysadmin, linux, bash, debug]
comments: false
header:
  teaser: /img/bide/debug.png
---

# Introduction
I've had a few collegues ask me how I have a full featured Bash IDE for courses I have developed; So I thought i'd make a post to show people how to do it.

## Features
* Full Bash Debugging (Built into the IDE)

  ![debug.png](/img/bide/debug.png)

* Linting 

  ![lint.png](/img/bide/lint.png)

* Command Suggestions
  
  ![suggestions.png](/img/bide/suggestions.png)

[*Back to table of contents*](#)

## Requirements
1. Ubuntu 18.04 +
2. Snap
3. VSCode V 1.4.5+ standard vscode version on snap store (See Issue [133](https://github.com/rogalmic/vscode-bash-debug/issues/133) under bash-debug)

[*Back to table of contents*](#)

# Instructions
* Open your Extentions in vscode and search for bash
  
  ![extentions.png](/img/bide/extentions.png)
  
* Select Bash debug, then select install
  * Open your debug tab, and select create a launch.json file
    
      ![debug1.png](/img/bide/debug1.png)
    
  * Select Bash Debug
   
      ![debug2.png](/img/bide/debug2.png)
   
  * Customise your launch.jsonfile and add a comma to the end of line 11 (Program line) and create a new line with `"terminalKind": "Integrated"`
   
      ![debug3.png](/img/bide/debug3.png)
   
  	* this will enable you to use stdin on the integrated vscode terminal
    
* Select Bash IDE, then select install

* Install the shellcheck ubuntu package (Pre-Requisite for vscode extension)

  * `sudo apt install shellcheck`

* Search for Shellcheck, select it, then select install

  * Once shell check is installed click on the settings cog, and select extention settings
  
    ![extentionsettings.png](/img/bide/extentionsettings.png)
  
  * Enable the quick fix feature
  
    ![quickfix.png](/img/bide/quickfix.png)
  
* Your good to go :-) **happy scripting**

[*Back to table of contents*](#)


