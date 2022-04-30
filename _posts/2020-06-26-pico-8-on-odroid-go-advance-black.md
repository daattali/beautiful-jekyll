---
layout: post
title: PICO-8 on an ODROID-GO Advance Black Edition
date: '2020-06-26T20:54:00.005+02:00'
author: Morten
tags:
- Programming
- howto
- Linux
- Hardware
- Pi
- game
- fix
- video games
modified_time: '2021-06-30T14:07:43.200+02:00'
thumbnail: https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s72-c/IMG_1731.HEIC
blogger_id: tag:blogger.com,1999:blog-6967032375013519080.post-5007627471392150187
blogger_orig_url: https://m635j520.blogspot.com/2020/06/pico-8-on-odroid-go-advance-black.html
cover-img: https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s4032/IMG_1731.HEIC
thumbnail-img: https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s500/IMG_1731.HEIC
share-img: https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s320/IMG_1731.HEIC
---

_**UPDATE 2021/06/30**: This whole procedure is now super simple if you go the EmuELEC way following this guide: [https://retrogamecorps.com/2020/11/12/guide-pico-8-on-retro-handhelds/#EmuELEC](https://retrogamecorps.com/2020/11/12/guide-pico-8-on-retro-handhelds/#EmuELEC) It's basically just to put the pico-8 in a specific folder, and any roms (unless you just use splore) in another._

Last weekend I built the [ODROID-GO Advance Black Edition](https://www.hardkernel.com/shop/odroid-go-advance-black-edition/) with my daughter. (Apart from re-experiencing my childhood's Commodore 64 an Amiga games,) One of our goals was to run [PICO-8](https://www.lexaloffle.com/pico-8.php), the great little fantasy console, on it. That seemed possible, given that it shares a similar CPU to the Raspberry PIs – where it runs great.

[![](https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s320/IMG_1731.HEIC)](https://1.bp.blogspot.com/-Gn8bcLL2FP0/XvZBS3Ej_UI/AAAAAAADYtI/l8XAD3vzjM0vDD5shZW9QtJJV24f0zZFgCK4BGAsYHg/s4032/IMG_1731.HEIC)

However, it was not _that_ easy to get it up and running. Here’s what worked, but first, what didn’t…

## Official image

First we installed the [official image](https://wiki.odroid.com/odroid_go_advance/make_sd_card) from HardKernel on it. But alas, no luck getting things to run properly.

## EmuELEC

Next up was [EmuELEC](https://github.com/EmuELEC/EmuELEC/releases/tag/v3.6). There we managed to get PICO-8 to run in all it’s 8-bit glory! But! Controls didn’t work when launching from [EmulationStation](https://emulationstation.org/)… What worked though, was to go to bash mode, ssh in from another device and launch joy2key.py and then PICO-8… What also worked was to plug an external controller into the device _before_ launching PICO-8 from EmulationStation… This made me suspect that PICO-8 didn’t have the right SDL joystick config file. I couldn’t find the config for this new odroid online, but! I found this forum post on batocera linux: [https://forum.odroid.com/viewtopic.php?f=193&t=37256&start=800#p295789](https://forum.odroid.com/viewtopic.php?f=193&t=37256&start=800#p295789)

## Batocera

So, I installed [batocera](https://batocera.org/) and followed the steps outlined in the link above. Basically:

1.  Create folder `/userdata/roms/pico-8` (for the carts)
2.  Create folder `/userdata/bios/pico-8` and extract the contents of the Raspberry Pi version of PICO-8 here. (As of this writing: pico-8_0.2.0i_raspi.zip)
3.  Make `pico8_dyn` executable by [ssh’ing into the odroid](https://wiki.batocera.org/access_the_batocera_via_ssh) and running:
    
	```bash
	chmod a+x /userdata/bios/pico-8/pico8_dyn  
	```

4.  Create a file called `pico-8.sh` in `/userdata/roms/ports` with the following bash script in it:
    ```bash
    #!/bin/bash  
    /userdata/bios/pico-8/pico8_dyn -splore -home /userdata/bios/pico-8 -root_path /userdata/roms/pico-8 -joystick 0  
    
    This makes Batocera’s emulation station add pico-8 to the “Ports” part of the launcher.
    ```
    Nice!
5.  PICO-8 still wouldn’t get signals from the controller, so we need add this to `/userdata/bios/pico-8/sdl_controllers.txt`:
    ```bash
    // add SDL2 game controller mappings to this file  
    19000000010000000100000001010000,odroidgo2_joypad,a:b1,b:b0,x:b2,y:b3,leftshoulder:b4,rightshoulder:b5,dpdown:b9,dpleft:b10,dpright:b11,dpup:b8,leftx:a0,lefty:a1,guide:b17,leftstick:b13,lefttrigger:b6,rightstick:b16,righttrigger:b7,start:b12,platform:Linux,  
    ```
    This is a slight adaptation of the config outlined in the forum post mentioned above – to handle the extra buttons on the BE version of the Odroid-GO Advance. Basically it seems that the two new trigger buttons has, bizarrely, gotten codes that used to be taken by up and down ('b6' and 'b7') – even though the ID of the controller has been kept the same… (To make the UI of Batocera work properly you need to do a similar remapping there... and that is actually how I found the proper button numbers -- from the config file resulting from remapping the buttons.)

So, there goes. PICO-8 on a handheld device.