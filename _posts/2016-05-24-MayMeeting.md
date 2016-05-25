---
layout: post
title: 'Recap: PowerShell - Back to Basics'
---

### [Slides](http://cincypowershell.org/presentations/2016-05)
### [Code](http://cincypowershell.org/presentations/2016-05/demo.md)

### PowerShell Versions
Latest version is 5.0 and comes built in to Windows 10. Windows PowerShell is bundled Windows Management Framework 5.0.
Windows Management Framework 5.0 includes updates to Windows PowerShell, Windows PowerShell Desired State Configuration (DSC), Windows Remote Management (WinRM), Windows Management Instrumentation (WMI).
[Download it here](https://www.microsoft.com/en-us/download/details.aspx?id=50395)


### Command Discovery
PowerShell uses a verb-noun naming convention. There are a list of approved verbs

### Help System
```powershell
Get-Help 
```

### Cmdlet Basics
Show Command
Mandatory Parameters
Parameter Value Types
Parameter Sets

### Providers
```powershell
Get-Help about_providers
```
BUILT-IN PROVIDERS
Windows PowerShell includes a set of built-in providers that you can use
to access the different types of data stores.

Provider      | Drive         | Data store
--------      | -----         | ----------
Alias         | Alias:        | Windows PowerShell aliases
Certificate   | Cert:         | x509 certificates for digital signatures
Environment   | Env:          | Windows environment variables
FileSystem    | *             | File system drives, directories, and files
Function      | Function:     | Windows PowerShell functions
Registry      | HKLM:, HKCU:  | Windows registry
Variable      | Variable:     | Windows PowerShell variables
WSMan         | WSMan:        | WS-Management configuration information
* The FileSystem drives vary on each system.

You can also create your own Windows PowerShell providers, and you can
install providers that others develop. To list the providers that are
available in your session, type:
```powershell
get-psprovider
```

### Pipeline
```powershell
Get-Help about_pipeline
```
A pipeline is a series of commands connected by pipeline operators 
(|)(ASCII 124). Each pipeline operator sends the results of the preceding
command to the next command.
You can use pipelines to send the objects that are output by one command
to be used as input to another command for processing. And you can send the
output of that command to yet another command. The result is a very powerful
command chain or "pipeline" that is comprised of a series of simple commands.

For example: `Command-1 | Command-2 | Command-3`

In this example, the objects that Command-1 emits are sent to Command-2.
Command-2 processes the objects and sends them to Command-3. Command-3 processes
the objects and send them down the pipeline. Because there are no more commands in
the pipeline, the results are displayed at the console.

In a pipeline, the commands are processed from left to right in the order
that they appear. The processing is handled as a single operation and
output is displayed as it is generated.

Here is a simple example. The following command gets the Notepad process
and then stops it.
```powershell
get-process notepad | stop-process
```
The first command uses the Get-Process cmdlet to get an object representing
the Notepad process. It uses a pipeline operator (|) to send the process object
to the Stop-Process cmdlet, which stops the Notepad process. Notice that the
Stop-Process command does not have a Name or ID parameter to specify the process,
because the specified process is submitted through the pipeline.