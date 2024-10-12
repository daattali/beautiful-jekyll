---
layout: post
title: dual boot windows and arch linux
subtitle: with fixes
tags: [arch-linux]
comments: true
---

Recently I bought a new SSD. I haven't looked inside a computer since high school. Things have changed a lot!

**prep**

The first task was finding the motherboard manual to see what slots I have on my motherboard since I bought a pre-built PC. I have two nvme slots, which means I can keep using the nvme SSD that came with my PC. I then bought a 2TB nvme drive with dram cache because apparently that helps with boot times and a precision screwdriver set to spin any tiny screws I might need to. I also created Window installation USB drive.

**installation** 

The nvme slot that held my previous OS is hiding under my gigantic gpu. Luckily, the free nvme slot is the faster slot, with pci 4.0 instead of 3.0, which is perfect for my new drive. It was easy to open up the computer, unscrew the tiny screw on the 2nd nvme slot, gently slide in the SSD and screw the tiny screw back in to hold it in place.

From here  I booted into BIOS and changed the boot config to load from the USB first. I booted the USB and installed Windows onto my new SSD. I encountered a boot loop issue here, which was solved by deleting the Windows partition on my old SSD, then installing Windows on the new SSD.

Once Windows was running, I downloaded Arch Linux as an .iso file and used rufus to create a bootable USB drive for Arch. I rebooted into the USB drive and ran the "archinstall" command to install Arch Linux on my old SSD. I did follow a tutorial for this part as there were many options I was unsure of.

Again I changed the BIOS settings to prioritise the Arch bootloader to configure Arch linux.

Installation on Arch Linux involves opening the terminal and using "sudo pacman -S packagename" to install packages (programs). With this knowledge it's fairly easy to migrate to Arch as a longtime Windows user.

**time fix**

Rebooting into Windows, I noticed that my system time was wrong. This was an easy fix with this tutorial: https://itsfoss.com/wrong-time-dual-boot/
In case this tutorial has been removed, it was as simple as running this command in Linux "sudo timedatectl set-local-rtc 1" to stop Linux from changing the system time, which messes up how Windows keeps the time.

**dual booting**

My main motivation for installing Arch Linux is to use it to learn programming. It needs to be easy for me to switch between Windows and Linux. However, with this setup, the only way to do that is to manually change the boot priority in BIOS each time I want to swap between operating systems.

After a bit of back and forth, I found an easy fix on Arch:

1. Install grub and os-prober
>sudo pacman -S grub
>sudo pacman -S os-prober

2. Run os-prober
>sudo os-prober

This should show the Windows partition. If not, right click on your drive with Windows on it (on your desktop) and click 'mount'.

3. Run grub
>sudo grub

This shows the bootable partitions. You might see that Windows is not listed. You may need to edit a file to allow grub to add partitions from other drives.

4. Uncomment the grub config file

Open the file manager and navigate to /etc/detault/grub. Find the line:
>#GRUB_DISABLE_OS_PROBER=false
and remove the "#" to uncomment the line. Note that this file should be read-only and you need to give yourself root privileges to edit it. I opened up a terminal and opened up the file with a text editor with sudo added to the command.
>sudo -S vim /etc/default/grub
Make sure you save the file

5. Update grub with your Windows installation
>sudo grub-mkconfig -o /boot/grub/grub.cfg
Alternatively, follow this tutorial to create a update-grub command (found in Ubuntu) https://itsfoss.com/update-grub-command-not-found/

Run sudo grub again to see if Windows is now listed in the grub bootloader.

Reboot your PC. The grub bootloader should load and you now should be able to choose between Linux, Windows and BIOS upon startup. 


