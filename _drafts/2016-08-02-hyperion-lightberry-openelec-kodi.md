---
layout: post
published: false
title: Hyperion + Lightberry + OpenElec + Kodi
---
These last few weeks I got more and more interested in home automation and other cool to do with like so I thought I'd deviate from virtualization the time of a tutorial. 

I did this project to create a mood lighting behind the TV that "follows" the colors displayed on the screen and enhance the experience of movie watching. It is pretty much an open source version of Philips' Ambilight except it can work on a wide range of devicew and is much cheaper (with a little bit of hardware and a bit more elbow grease).

# Some theory

The system is made up of 4 main components.  I won't get into the details of raspberry or the TV as I assume you already have your media center running Kodi.

Here are the different components of the system and what they do.

- **Hyperion** : [Website](https://hyperion-project.org/wiki/Main)

yperion is an open source _Ambilight implementation_ under MIT license. It is the software that controls the LEDs independently by sending the right signals to the hardware interface of the lights. There are other similar softwares such as Boblight but I chose Hyperion for some reason.

- **Lightberry** : [Website](http://lightberry.eu/)

Lightberry is the hardware bit that acts as an interface between Hyperion and the LED strip. It converts the commands sent by hyperion into a gibbrish understandable by the pixels. Lightberry offers multiple devices and packs that offer a different level of integration.  
In this tutorial I am only focusing on the USB converter. There is a version with a GPIO interface as well but I already have a case that closes the top of the raspberry. I bought the power supply with lightberry by convenience and to support them, but any 5V power supply with jack 5,5 should do really.

This converter alone will only make the LEDs work with the Raspberry PI. If you have other devices that you would like to integrate like a DVD player or a Xbox and such you will need the HDMI kit along with an HDMI switch.

- **OpenElec installed on a Raspberry Pi**[Website](http://openelec.tv/) 

My OpenElec is on version 6.0.3 and runs Kodi 15 on a Raspberry Pi 2, at the time of this article you can get a Raspberry Pi 3 with better hardware for about £30. 

Lightberry offers a custom image of OpenElec that you can download on their website. I kept my "stock" OpenElec as I have never restored the backup and don't want to try (too much borring config).

- **RGB LED strip individually addressable (WS2801)**

The ones you want for use with hyperion need to be individually addressable, meaning you can control the LEDs independently (color, intensity). Each LED is equipped with a micro controller that sends it the RGB values, and of course the software (Hyperion) needs to have the drivers for these controllers. That's why you need compatible LEDs. There are several but I chose the WS2801 which seem to be the most common one.

In summary:

![schema-hyperion.jpg]({{site.baseurl}}/img/schema-hyperion.jpg)

- Kodi plays your video on the TV (on OpenElec),
- OpenElec runs Hyperion,
- Hyperion tells the USB converter which pixels to turn on, etc...
- The Lightberry USB converter translates it into RGB-ish and sends it to the LED strip,

# 1 - The hardware part

## What you need

- LED strips

I got a WS2801 LED strip, you can check the type on the tiny controllers located next to each LED.

![Led-WS2801.jpg]({{site.baseurl}}/img/Led-WS2801.jpg)

- USB converter
- A longer cable to connect the lightberry to the LEDs
- A bunch of hooks for the back of the TV (If you don't want to do a caveman setup like mine)
- A power supply

You can get the whole lot directly as a kit from lightberry. It costs about 90€ and contains everything you need. [Lightberry HD Kit](https://lightberry.eu/shop/shop/lightberry-hd/)

## Some DIY

# 2 - The software part

Thanks to the guys of the Hyperion project and lightberry it is super easy to set up.

## Install Hyperion

- First Connect to your OpenElec via SSH using your favorite SSH client (Putty). Default Username/Password are root/openelec.

- Download the Hyperion project script.

```
curl -L --output install_hyperion.sh --get https://raw.githubusercontent.com/tvdzwan/hyperion/master/bin/install_hyperion.sh
```

- Install Hyperion, the raspberry pi will reboot.

```
sh ./install_hyperion.sh
```

Your SSH session should look like this.

![ssh-hyperion.JPG]({{site.baseurl}}/img/ssh-hyperion.JPG)

## Configure Hyperion

- First download the Hyperion Configurator plugin for Kodi on the [website of lightberry](http://lightberry.eu/).

Scroll all the way down to the downloads and grab the Config generator plugin. It's a tiny zip file of about 44KB.

![Hyperion-config-addon.jpg]({{site.baseurl}}/img/Hyperion-config-addon.jpg)

- Transfer the zip file somewhere OpenElec has access. I used WinSCP to copy the file in the rom.

![zip-winscp.JPG]({{site.baseurl}}/img/zip-winscp.JPG)

- Go back to Kodi > Add on > Install from zip file

![Install-from-zip.jpg]({{site.baseurl}}/img/Install-from-zip.jpg)

- browse to the location of the zip file

![Zip-home-folder.jpg]({{site.baseurl}}/img/Zip-home-folder.jpg)

![hyperion-zip-plugin.jpg]({{site.baseurl}}/img/hyperion-zip-plugin.jpg)

![select-hyperion-plugin.jpg]({{site.baseurl}}/img/select-hyperion-plugin.jpg)

- Select the zip file containing the Hyperion plugin and check that it installs correctly

![hyperion-plugin-installed.jpg]({{site.baseurl}}/img/hyperion-plugin-installed.jpg)
