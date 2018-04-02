---
layout: post
published: true
title: Passive node down in vCenter HA 6.5
---
_This issue is fixed in vCenter 6.5 update 1._

![vcha-issue-0.jpg](/img/vcha-issue-0.jpg)

I recently logged on a VCSA 6.5 that had been installed a while back with vCenter High Availability (VCHA) and noticed that the passive node was down. After a few checks, the VM is running, I can ping and ssh to it on its ha interface from the active node. I restart the passive node, it  goes "up" and then back to "Down" so what is going on here?

> A replication failure might be occuring at the moment. Automatic failover protection is disabled. If vCenter HA was recently enabled, initial replication might still be in progress and could take a few minutes.

This warning message led me to [KB2148675](https://kb.vmware.com/s/article/2148675).

When VCHA is enabled, a local user "vcha" is created on the appliance. 
The problem comes from the facts that the password of this user expires after 60 days by default, and when it does VHCA breaks...

So one can assume that vCenter HA worked for 2 months and went into space after that. Terrible default setting if you ask me.

## Fix

The fix is to change the expiry of the password on all the nodes of the vCenter HA and restart the passive one.

SSH must be enabled on all nodes.

### Active node

  * Connect to vCenter via SSH and type "shell" to enter the shell.
  * Check that the password is indeed expired:

`chage --list vcha`

![vcha-issue-1.jpg](/img/vcha-issue-1.jpg)

The screenshot shows that the password expired on the 2017/06/23 and had a validity of 60 days.

  * Reset the password:

`passwd vcha`

  * Give the password an ultra long validity (basically never expire):

`chage -m 0 -M 99999 vcha`

  * Check again the vcha account to make sure it worked:

`chage --list vcha`

![vcha-issue-2.jpg](/img/vcha-issue-2.jpg)

### Passive and Witness nodes

The same operation must be done on both the passive and witness nodes. Because the VCHA cluster only has one DNS name and one IP address you can't ssh to them from your management station. The trick is to ssh to the nodes on their VCHA interface in the isolated HA network (that is most likely not routed and for good reasons) from the active vCenter node. Alternatively you can use the virtual console if you decided to enable the shell.

  * **Wkstation --> Active node (management IP) --> passive node (HA IP)**

`ssh root@PassiveNodeHAIP`

You can check that you are actually on the right by looking for its HA address with `ifconfig`.

  * Repeat the steps done on the active node.

  * Go back to the active node

`Exit`

  * **Wkstation --> Active node (management IP) --> witness node (HA IP)**

`ssh root@WitnessNodeHAIP`

  * Repeat the steps done on the active node.

You can then close the ssh client.

  * Restart the passive node and give the cluster a few minutes to get everything sorted. Everything should then be green.

![vcha-issue-3.jpg](/img/vcha-issue-3.jpg)

As mentioned earlier this won't be an issue from 6.5u1 and onwards.

Here's what the default settings look like in these versions.

![vcha-issue-4.jpg](/img/vcha-issue-4.jpg)
