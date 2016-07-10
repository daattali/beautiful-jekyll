---
layout: post
published: false
title: 'Pingou: ping on steroids in powershell'
---
Pingou is a powershell script that allows to test connectivity with ICMP and open ports with TCP. This command is meant to be easy to use, intuitive and faster than the built in test-connection and test-netconnection.

**Link to the script** : [Pingou](https://github.com/vxav/Scripting/blob/master/Pingou.ps1)

![pingou.jpg]({{site.baseurl}}/img/pingou.jpg)

I took inspiration on a great script that one of my colleagues wrote "[tPing](http://www.nimbus117.co.uk/powershell/2015/07/06/tPing.html)". But because there is no better way to learn than to do it myself so I took a few ideas and wrote mine from scratch.

**ICMP**

Pingou -destination www.google.fr

![pingou-www.google.fr.jpg]({{site.baseurl}}/img/pingou-www.google.fr.jpg)

**TCP**

Pingou -destination www.google.fr -port 80

![pingou-www.google.frhttp.jpg]({{site.baseurl}}/img/pingou-www.google.frhttp.jpg)

A status of true means the port is open, false means it is closed.
The parameters buffer and hops can't be used with the tcp ping as it is specific to icmp pings.

**Hostname resolve**

The script resolves automatically the hostname to ping. According to your DNS settings, a hostname can resolve one or multiple IPs (apologies for the screenshots in french but you'll get it).

Nslookup using my ISP's DNS : cache1.service.virginmedia.net

![nslookup-virgindns.jpg]({{site.baseurl}}/img/nslookup-virgindns.jpg)

Nslookup using google's DNS (the one I use) : google-public-dns-a.google.com

![nslookup-googledns.jpg]({{site.baseurl}}/img/nslookup-googledns.jpg)

As you can see for some reason the Virgin DNS resolves only one IP when google's ones resolve a lot. That is why in case it happens, the test will be issued to the first IP in the list (62.252.232.30).

**Parameters**

I could go through all the possibilities the script offers but the easiest is probably that you play with it.

- DESTINATION: Remote IP or hostname to test.

- COUNT: (-t) Number of test issued.

- PORT: TCP port to check on the remote host, validate range is 1 to 65535.

- CONTINUOUS: (-n) Number of tests infinite. can be stopped with ctrl+c or by closing the invite.

- TIMEOUT: (-w) Number of milliseconds after which a timeout is issued for each test.

- DELAYMS: Number of milliseconds between each test.

- HOPS: (-i) Number of hops after which the packet is dropped (TTL expired). Works only with ICMP tests.

- BUFFER: (-l) Size in bytes of the buffer to send. Works only with ICMP tests.

## Code

**Pingou function**

```Powershell
Function Pingou {

[CmdletBinding(DefaultParameterSetName=1)]  

param(
    [Parameter(Mandatory=$true,ValueFromPipeline = $True,position=0)]
    [string]
    $Destination,

    [parameter(position=1)]
    [ValidateRange(1,65535)]
    [int]
    $Port,

    [parameter(parametersetname=2)]
    [Alias('t')]
    [switch]
    $Continuous,

    [parameter(parametersetname=1)]
    [Alias('n')]
    [int]
    $Count = 4,

    [Alias('w')]
    [int]
    $Timeout = 1000,

    [ValidateRange(200,10000)]
    [int]
    $Delayms = 750,

    [ValidateRange(1,255)]
    [Alias('i')]
    [int]
    $Hops = 128,

    [ValidateRange(1,255)]
    [Alias('l')]
    [int]
    $Buffer = 32

)

#$ErrorActionPreference = "SilentlyContinue"

$Resolve = [System.Net.Dns]::GetHostAddresses($Destination).IPAddressToString
IF ($Resolve.count -gt 1) {$Resolve = $Resolve[0]}

IF ($Resolve) {

    IF ($Port) {

        While ($i -lt $Count) {

            Port-Ping -IP $Resolve -Port $Port -Timeout $Timeout
            IF (!$Continuous) {$i++}
            Sleep -Milliseconds $Delayms

        }

    } ELSE {

        $icmpping = New-Object system.Net.NetworkInformation.Ping

        $icmpoptions = New-Object System.Net.NetworkInformation.PingOptions($Hops,$false)

        While ($i -lt $Count) {

            Icmp-Ping -IP $Resolve -Timeout $Timeout -icmpOption $icmpoptions -Buffer $Buffer
            IF (!$Continuous) {$i++}
            Sleep -Milliseconds $Delayms

        }

    }

} ELSE { # ELSE RESOLVE

    Write-Warning "cannot resolve $Destination"

}

}
```

**ICMP and TCP Subfunctions**

```Powershell
Function Port-Ping {

param(
    [Parameter(ValueFromPipeline = $True)]
    [string]
    $IP,

    [ValidateRange(1,65535)]
    [int]
    $Port,

    [int]
    $Timeout

)

$before = get-date

$PortPing = New-Object System.Net.Sockets.TCPClient

$PortConnect = $PortPing.beginConnect("$IP",$Port,$null,$null)

While (((get-date) -lt $before.AddMilliseconds($Timeout)) -and ($PortPing.Connected -ne "true")) {}

$timems = [math]::round(((get-date) - $before).TotalMilliseconds,0)

[pscustomobject]@{

    LocalEndpoint   = $PortPing.Client.LocalEndPoint
    RemoteEndpoint  = $PortPing.Client.RemoteEndPoint
    Status          = $PortPing.Connected
    Timems          = $timems

}

$PortPing.Close()

} #Pingou subfunction

Function Icmp-Ping {

param(
    [Parameter(ValueFromPipeline = $True)]
    [string]
    $IP,

    [int]
    $Timeout,

    [int]
    $Buffer,

    [System.Net.NetworkInformation.PingOptions]
    $icmpOption

)

$icmpconnect = $icmpping.Send("$IP",$Timeout,$buffer,$icmpoptions)

[pscustomobject]@{

    RemoteEndpoint = $IP
    Bytes          = $buffer
    Time           = IF ($icmpconnect.Status -eq "Success") {$icmpconnect.RoundtripTime} ELSE {$icmpconnect.Status}
    TTL            = $icmpconnect.Options.Ttl

} 

}
```