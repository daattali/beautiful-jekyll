---
layout: post
published: true
title: Generate a random password in Powershell
---
I recently needed to generate random password for an PowerCLI automation project. However, although there is a Get-Random cmdlet, it is limited to generate random numbers. Not good enough for a password, so I decided to write my own.

This function allows you to choose what types of characters to use, the number of characters and optionally what characters NOT to use.

Why do I want to exclude characters? Sometimes (especially in a script) I want to exclude the characters used by Powershell for formatting like " ' $ { [ |  
Sometimes it will save the day, sometimes it won't make a difference, but I like to be on the safe side.

I put a top limit of 30 characters just because I wanted a low limit of 6 and I needed a number, but if you need to create a 50 characters passowrd (you need Jesus) you can just change the validaterange or the parameter.

## Usage

Generate an ultra secure 30 characters with upper-case, lower-case, numbers and special chars with exclusion of $ € and £.

```Powershell
New-RandomPassword -length 30 -uppercase -lowercase -numbers -special -excludedchars "$","€","£"

\+v:(?*[FCPpg|3N6!+9efA:,]fw+L
```

Generate a basic 12 characters password with lowercase and numbers. Here you don't need to specify the length as 12 is default.

```Powershell
New-RandomPassword -length 6 -lowercase -numbers

4cp54hme5sbj
```

## Script

You can find the ps1 [here on Github](https://github.com/vxav/Scripting/blob/master/New-RandomPassword.ps1).

```Powershell
Function New-RandomPassword {

param(
    [ValidateRange(6,30)]
    [int]$length = 12,
    [switch]$uppercase,
    [switch]$lowercase,
    [switch]$numbers,
    [switch]$special,
    [string[]]$excludedchars
)

IF (!$uppercase -and !$lowercase -and !$numbers -and !$special) {write-warning "Please specify characters to use";break}

$upperID   = 65..90
$lowerID   = 97..122
$numberID  = 48..57
$specialID = 33..47+58..64+91..96+123..126

IF ($uppercase) {$range += $upperID}
IF ($lowercase) {$range += $lowerID}
IF ($numbers) {$range += $numberID}
IF ($special) {$range += $specialID}

$allowedchar = @()

foreach ($i in $range) {
    
    IF ([char]$i -notin $excludedchars) {$allowedchar += [char]$i}

}

$BadPass = "I don't want to be bad"

while ($BadPass) {
    
    if ($BadPass) {Clear-Variable badpass}
    if ($RandomPassword) {Clear-Variable RandomPassword}

    for ($i = 1; $i –le $length; $i++) {

        $randomIndex = Get-Random -Maximum $allowedchar.count

        $RandomPassword += $allowedchar[$randomIndex]

    }

    IF ($lowercase) {IF ($RandomPassword -cnotmatch "[a-z]") {$BadPass++}}
    IF ($uppercase) {IF ($RandomPassword -cnotmatch "[A-Z]") {$BadPass++}}
    IF ($numbers)   {IF ($RandomPassword -notmatch "[0-9]") {$BadPass++}}
    IF ($special)   {IF ($RandomPassword -cnotmatch '[^a-zA-Z0-9]') {$BadPass++}}

}

Return $RandomPassword

}
```