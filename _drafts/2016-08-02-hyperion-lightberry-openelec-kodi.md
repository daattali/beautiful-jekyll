---
layout: post
published: false
title: Hyperion + Lightberry + OpenElec + Kodi
---
These last few weeks I got more and more interested in home automation and other cool to do with like so I thought I'd deviate from virtualization the time of a tutorial. 

I did this project to create a mood lighting behind the TV that "follows" the colors displayed on the screen and enhance the experience of movie watching. It is pretty much an open source version of Philips' Ambilight except it can work on a wide range of devicew and is much cheaper (with a little bit of hardware and a bit more elbow grease).

**Scroll down to the end for the alternative without lightberry.**

The system is made up of 4 main components.  I won't get into the details of the raspberry or the TV as I assume you already have your media center running Kodi.

![schema-hyperion.jpg]({{site.baseurl}}/img/schema-hyperion.jpg)

Here are the different components of the system and what they do.

- **Hyperion** : [Website](https://hyperion-project.org/wiki/Main)

Hyperion is an open source _Ambilight implementation_ under MIT license. It is the software that controls the LEDs according to the colors detected with a clever algorithm. There are other similar projects such as Boblight but I chose Hyperion as it seems to be the most common.

- **Lightberry** : [Website](http://lightberry.eu/)

Lightberry is the hardware bit, based on an Arduino Leonardo, that acts as an interface between Hyperion and the LED strip. Lightberry offers multiple devices and packs that offer a different level of integration. In this tutorial I am only focusing on the USB converter. There is a version with a GPIO interface as well but I already have a case that closes the top of the raspberry. You could also do without the lightberry part by using the GPIO pins 19 and 23 for clock and data.

This converter alone will only make the LEDs work with the Raspberry PI. If you have other devices that you would like to integrate like a DVD player or a Xbox and such you will need more stuff (I'll cover the other possible scenarios at the end).

- **OpenElec installed on a Raspberry Pi** : [Website](http://openelec.tv/) 

My OpenElec is on version 6.0.3 and runs Kodi 15 on a Raspberry Pi 2, at the time of this article you can get a Raspberry Pi 3 with a better hardware for about £30. 

- **RGB LED strip individually addressable (WS2801)**

They must be individually addressable, meaning you can control the LEDs independently (color, intensity). Each LED is equipped with a micro controller that hyperion must have be compatible with. There are several types but I chose the WS2801. The controller is not always visible like on the APA102, but you can check wether it is independently addressable with the labels on the strip.
- 5V, CK, SI, GND : Independently addressable
- xV, R, G, B : Non Independently addressable

![Led-WS2801.jpg]({{site.baseurl}}/img/Led-WS2801.jpg)

I got my leds from a cheap chinese seller on amazon and I had issues with the LED strip which had the connector badly wired, so I had to redo it by desoldering and resoldering properly. Even though it works now it took me some time to get to figure out what was the issue, so going for the cheapest one might be a bet.

## Things to get

- [WS2801 LED strips](https://www.amazon.co.uk/MENGCORE%C2%AE-Addressable-WS2801-32Leds-non-Waterproof/dp/B01CFUI2NO/ref=sr_1_1?ie=UTF8&qid=1471249479&sr=8-1&keywords=ws2801+5m).
- [Lightberry USB converter](https://lightberry.eu/shop/shop/diy-lightberry-usb-level-converter/) (include the USB cable).
- [A 5V power supply](https://lightberry.eu/shop/shop/diy-lightberry-power-supply/), I've got 4A and that works fine.
- A soldering iron

You can get the whole lot directly as a kit from lightberry. It costs about 90€ and contains everything you need. [Lightberry HD Kit](https://lightberry.eu/shop/shop/lightberry-hd/)

## Things to download

Download and install these and store the lightberry firmware somewhere on your pc.

[Arduino software](https://www.arduino.cc/en/Main/Software)  
[Latest lightberry firmware]([http://update.lightberry.eu/](http://update.lightberry.eu/))  
[HyperCon](https://sourceforge.net/projects/hyperion-project/files/hypercon/HyperCon.jar)  
[Java](http://www.java.com/en/)

## Update firmware of the lightberry USB converter

I had an issue with a bunch a LEDs flickering like crazy all the time that is fixed by updating the firmware of the lightberry.

Follow this tutorial from lightberry to update the firmware : [http://update.lightberry.eu/](http://update.lightberry.eu/)

## Install the LEDs

When you order the kit from lightberry you get a bunch of hooks to run the led strip sideways without using the tape on the back and the need to cut the strip at every angle. If you don't get it there is a bit more work involved but it's worth the time spent.

You will need to cut 4 lengths of strip for each side of the TV.

- Find where to cut your LED strip by "simulating" the placement on your TV. Mine has 16 LEDs on the left and right sides, 29 LEDs on top and bottom for 42". Be sure to take into account that you can cut it only on the links.
- Cut the strip where you defined it.
- Solder the bits together with electric wires of about 5cm. If you have heat shrink it'll be cleaner to protect the soldered part, I don't have any so I just used tape.
- Take out the tape protection and stick it on the sides. I can remove the TV stand by just sliding it down so I ran my LED strip all the way through the bottom side of the TV and left the tape protection on the back of the strip so it doesn't stick to the stand (Red square). But if this would prevent you from taking out the stand you need to leave a gap the size of the stand and connect the to sides with whatever 4 pins connector.

The glue on the back of the strip isn't the best ever and the heat of the TV doesn't help, so I added a few ugly bits of tape to secure the led strip.

![ledbehindtv.jpg]({{site.baseurl}}/img/ledbehindtv.jpg)

- Connect the lightberry box to the LED strip, the raspberry pi and to the power supply.

## Prepare OpenElec / Kodi

**Check SSH is enabled:**

- Go to "OpenELEC Settings" -> "Services" -> Uncheck "Disable SSH Password"![]

![openelec-enable-ssh.png]({{site.baseurl}}/img/openelec-enable-ssh.png)

**Enable remote control of Kodi**

If you don't enable the remote control, Hyperion will fail to connect to Kodi and won't be able to switch off the leds when you don't want them (Menu, screensaver, pause, ...).

- Go to "System" > "Settings" > Set the Setting level to "Expert" > "Remote Control"
- Enable the 2 checkboxes.

![kodi-remote-ctrl.jpg]({{site.baseurl}}/img/kodi-remote-ctrl.jpg)

## Hyperion installation and configuration

**Creation of the configuration**

- Launch Hypercon.jar

_Hardware tab_

**Type** : Adalight  
**Output** : /dev/ttyACM0  
**Construction** : Select the one that applies to how you've installed your LED. The direction is facing the TV.  
**Direction** : Direction from start to end of the led strip.  
**LEDs** : Number of LEDs on each side.  
**Bottom Gap**: Number of LED top - Number of LEDs bottom.  
**1st LED offset**: Adjust this value so the 0 is at the start of your strip on the image.  
**Blackborder detection** : Enabled (makes the LEDs work even with black borders).  
**Threshold[%]**: 1 (Threshold under which the color is considered black).

![Hypercon-basic1.jpg]({{site.baseurl}}/img/Hypercon-basic1.jpg)

![blacborderdetection.jpg]({{site.baseurl}}/img/blacborderdetection.jpg)

_Process tab_

I change the "Time [ms]" value from 200ms to 75ms, otherwise it looks like there is a latency and the LEDs or not in sync with the TV especially in scenes with a lot of action.

![linear-smoothing.jpg]({{site.baseurl}}/img/linear-smoothing.jpg)

Skip the grabber tab as you shouldn't need to touch anything there.

_External tab_

Kodi checker allows hyperion to get the status of Kodi.  
Leave 9090 if you haven't changed the default port.

Uncheck the boxes for when you want the LEDs to be switched off.

Under "Effect" you can change the effect on the LEDs at the startup of Kodi.

![kodi-integration.jpg]({{site.baseurl}}/img/kodi-integration.jpg)