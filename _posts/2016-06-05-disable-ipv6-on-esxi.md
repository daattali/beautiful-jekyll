---
layout: post
published: false
title: disable-ipv6-on-esxi
---
Since ESXi 5.1 IPv6 is enabled by default on new hosts, this can be seen in the DCUI interface below the IPv4 address or in the web client in networking (I won't mention the C# client as it is now officially dead).

By now this is probably a well known thing but better safe than sorry. If you disable or enable IPv6 through the DCUI interface, as stated in the warning message, a restart of the host will be performed if you hit YES along with a **graceful shut down of all the VMs running on it** so be careful.

![ipv6restart.jpg]({{site.baseurl}}/img/ipv6restart.jpg)

If you are going to disable or enable IPv6 on your host via the DCUI make sure you've migrated you're VMs to another host. If you make the change in the web client or by command line (esxcli) the change won't be effective until you restart the host yourself.

I am not going to go through how to disable IPv6 using the clients as a quick peak at the KB will tell you everything you need to know: [KB1021769](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=1021769)

However, [PowerCLI 6.3 R1](http://blogs.vmware.com/PowerCLI/2016/03/new-release-powercli-6-3-r1download-today.html) released on march 16th 2016 brought a really cool feature to the Get-ESXCli cmdlet. And as it is still pretty new, most of the articles online mentionning it are still referring to the awful "V1" instead of the new V2. You can find out more about this in this really good [post from Alan Renouf](http://blogs.vmware.com/PowerCLI/2016/04/powercli-6-3-r1-get-esxcli-why-the-v2.html).

### Esxcli command to disable IPv6

```
esxcli system module parameters set -m tcpip4 -p ipv6=0
```

### PowerCLI 6.3 R1 to disable IPv6
Note the V2 at the end of the command.
  
```
$esxcli = Get-EsxCli -VMHost (Get-VMHost "MyESXHostname) -V2
```
  
Create a variable to host the parameters that will be used in your esxcli command.
  
```
$argument = $esxcli.system.module.parameters.set.CreateArgs()
```
  
If you look into this $argument variable you will find the option that you would have using the host's shell:
![arg.jpg]({{site.baseurl}}/img/arg.jpg)


Now we set the variable's properties according to the esxcli command above and we use it with the "Invoke" code property.

```
$argument.module = "tcpip4"
$argument.parameterstring = "ipv6=0"
$esxcli.system.module.parameters.set.Invoke($argument)
```

After restarting the host manually, we can see that IPv6 is disabled as there is no IPv6 IP below the IPv4 one anymore.

```
$argument = $esxcli.system.module.parameters.set.CreateArgs()
```
  
If you look into this $argument variable you will find the option that you would have using the host's shell:
![arg.jpg]({{site.baseurl}}/img/arg.jpg)


Now we set the variable's properties according to the esxcli command above and we use it with the "Invoke" code property.

```
$argument.module = "tcpip4"
$argument.parameterstring = "ipv6=0"
$esxcli.system.module.parameters.set.Invoke($argument)
```

After restarting the host manually, we can see that IPv6 is disabled as there is no IPv6 IP below the IPv4 one anymore.