#Back to Basics Demo
```powershell
#region Basic Concepts before Discovery
    #Console and ISE

    #Console - cmdline environment

    start-process Powershell.exe -ArgumentList '-noprofile'
  
    #Tab completion / Intelisense

    Get-Service -Name LanmanWorkstation -

    dir c:

    #What Version?

    $PSVersionTable

    Start-Process powershell.exe -ArgumentList '-version 4'

#endregion

#region Command Discovery
    #Verb-Noun - Approved Verbs?
    # You will see warnings when using unapproved verbs 
    # Nouns should not be plural

        Get-Verb | Out-GridView

        get-Command -Verb get

        Get-Command Get-EventLog

        get-command export

#endregion

#region Help System

    Get-Help -Name Get-EventLog
    Get-help Get-EventLog -Full
    Help Get-EventLog -Full 
    #Help is actually a function Get-Help @PSBoundParameters | more
    #puts in paging for you!
    ###Advanced tip (Get-Command Help).scriptblock to see what this function is doing exactly
    Get-help Get-EventLog -ShowWindow # Pop up window, shows full help, filterable
    Get-help Get-EventLog -Online #goes to the online documentation for the command

    Update-Help

    #Parameters and Syntax Help

        #Mandatory or Optional

        #Positional vs Not - Use positional sparingly, your relying on memory

        Get-Command Get-EventLog -Syntax
    
    <#
        .Mandatory 
        -ParameterName <Value>

        .Mandatory Positional
        [-ParameterName] <Value>

        .Optional
        [-ParameterName and <Value>]

        .Optional Positional
        [[-ParameterName] <Value>]
    #>
    
    Show-Command Get-EventLog

    function Show-Parameters
    {
    Param
    (
        [Parameter(Mandatory,
                   Position=1)]
        $MandatoryPositional,

        [Parameter(Mandatory)]
        $Mandatory,
        
        [Parameter(Position=2)]
        $OptionalPositional,

        [Parameter()]
        $Optional,

        [Parameter()]
        [switch]$switch
        
    )

    }

    #About Topics
        #search for help if you don't know what your looking for, help will look for a match, if not found, it will search about topics, then if no match, search content!

        Get-help *common*
        get-help about_commonParameters -ShowWindow

    #PowerShell Offers all of this for you too.  As you learn to build commands, you get help for free!

#endregion Help

#region Providers
    #FileSystem is the main Provider we are familiar with
    # CD = set-location, mkdir = new-item -type Directory
    #there are many others and its extensible (IIS,SQL,AD,SCCM, etc)

    Get-command -Noun *item* | where {$_.Source -like '*Microsoft*'}

    #Item(Files and Folders), ItemProperty (atrributes) ItemPropertyValue, ChildItems (inside an item)

    #Wildcards  * (match multiple) and ? (match single)
    dir D*
    dir Document?
    
    Get-PSProvider

    cd hklm:
    
#endregion Providers

#region Pipeline

    #What is the pipeline?  The most powerful part about powershell
    #Strings the outputs of one command to the inputs of others.  
    #This is the "Glue" and allows for very simple commands to do complex tasks that would take hundreds of lines in other languages.

    # Represented by | (Vertical Bar)

    # Same concept as dir | more

    #Pipes Objects to Objects!

    get-eventlog -LogName System -Newest 10 
    # What we see is text representation of under the cover objects

    get-eventlog -LogName System -Newest 10 | Export-Csv .\myevents.csv -NoTypeInformation 
    notepad .\myevents.csv

    get-eventlog -LogName System -Newest 10 | Select-Object EventID,TimeGenerated,Source,Message | Export-Csv .\myevents.csv -NoTypeInformation -Force

    get-eventlog -LogName System -Newest 10 | Where-Object {$_.EventID -eq '7040'} | Select-Object EventID,TimeGenerated,Source,Message | Export-Csv .\myevents.csv -NoTypeInformation -Force

    #Explore these commands

        #Importing

        get-command -Verb import

        get-command -Verb Convertfrom

        # Objects

        get-command -Noun Object

        #Outputing / Formatting

        get-command -Verb Export

        get-command -Verb Out

        get-command -verb Format

        get-command -Verb Convertto

    # Create pipelines in thought contexts.
        # I want to GET HR users and MOVE them to the HR OU
        # I need to IMPORT the CSV of Purchase Orders, GROUP them by vendor, SORT them by cost, and PRINT them to my printer

    #Powerful - look out!

        # get-process | stop-process

        # Get-Service | Stop-Service

        # Get-childitem *.* | remove-item 

        # get-ADUser | remove-ADUser

        #Use the common parameters if supported -Confirm -Whatif
    
#endregion Pipeline

```