---
layout: post
title: Full Featured IDE For Bash Scripting
subtitle: How to get a full featured IDE for bash
tags: [sysadmin, linux, bash, debug]
comments: false
---

# Introduction
I've had a few collegues ask me how I have a full featured Bash IDE for courses I have developed, So I thought i'd make a post to show people how to do it.

## Features
1. Full Bash Debugging (Built into the IDE)

  ![debug.png](https://angry-bender.github.io/img/bide/debug.png)

2. Linting 

  ![lint.png](https://angry-bender.github.io/img/bide/lint.png)

3. Command Suggestions
  
  ![suggestions.png](https://angry-bender.github.io/img/bide/suggestions.png)


## Requirements
1. Ubuntu 18.04 +
2. Snap
3. VSCode V 1.4.5+ (As at 30/APR/20 this is the insiders version for vscode on the snap store (See Issue [133](https://github.com/rogalmic/vscode-bash-debug/issues/133) under bash-debug)

# Instructions
1. Open your Extentions in vscode and search for bash
  
  ![extentions.png](https://angry-bender.github.io/img/bide/extentions.png)
  
2. Select Bash debug, then select install
  * Open your debug tab, and select create a launch.json file
    
      ![debug1.png](https://angry-bender.github.io/img/bide/debug1.png)
    
  * Select Bash Debug
   
      ![debug2.png](https://angry-bender.github.io/img/bide/debug2.png)
   
  * Customise your launch.jsonfile and add a comma to the end of line 11 (Program line) and create a new line with `"terminalKind": "Integrated"`
   
      ![debug3.png](https://angry-bender.github.io/img/bide/debug3.png)
   
   this will enable you to use stdin on the integrated vscode terminal
    
3. Select Bash IDE, then select install

4. Search for Shellcheck, select it, then select install

  * Once shell check is installed click on the settings cog, and select extention settings
  
    ![extentionsettings.png](https://angry-bender.github.io/img/bide/extentionsettings.png)
  
  * Enable the quick fix feature
  
    ![quickfix.png](https://angry-bender.github.io/img/bide/quickfix.png)
  
5. Your good to go :-) happy scripting
