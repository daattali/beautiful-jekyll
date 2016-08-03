---
layout: post
published: false
title: Hyperion + Lightberry + OpenElec + Kodi
---
These last few weeks I got more and more interested in home automation and other cool thing like LEDs so I thought I'd deviate from virtualization the time of a tutorial. 

I did this project to create a mood lighting behind the TV that "follows" the colors displayed on the screen and enhance the experience of movie watching. It is pretty much an open source version of Philips' Ambilight except it can work on a wide range of devicew and is much cheaper (with a little bit of hardware and a bit more elbow grease).

## What you need

The system is made up of 4 main components. I link the hardware I bought for this project but you're free to look elsewhere to see if you find better deals or other brands (like the power adapter).

- [Hyperion](https://hyperion-project.org/wiki/Main)

The software that controls the LEDs independently by sending the right signals to the hardware interface of the lights. Hyperion is an open source project under MIT license that can not only be used for the TV but to control lights in general. There are other similar softwares such as Boblight.

- [Lightberry](http://lightberry.eu/)

[USB Converter](https://lightberry.eu/shop/shop/converter-box/) 
[Power Supply](https://lightberry.eu/shop/shop/diy-lightberry-power-supply/)

Lightberry is the hardware bit that acts as an interface between Hyperion and the LED stripe. It converts the commands sent by hyperion into a gibbrish understandable by the lights. Lightberry offers multiple devices and packs that offer a different level of integration.  
In this tutorial I am only using the USB converter. There is a version with a GPIO interface as well but I already have a case that closes the top of the raspberry. I bought the power supply with lightberry by convenience and to support them, but any power supply should do really.

This converter alone will only make the LEDs work with the Raspberry PI. If you have other devices that you would like to integrate such as a DVC player or a Xbox and such you will need the HDMI kit with and HDMI switch.

- [OpenElec](http://openelec.tv/) installed on a Raspberry Pi

My OpenElec runs Kodi on a Raspberry Pi 2 but at the time of this article you can get a Raspberry Pi 3 with better hardware for about £30. 

Lightberry offer a custom image of OpenElec that you can download on their website. I kept my "stock" OpenElec as I have never restored the backup and don't want to try (too much borring config).

I don't think it is needed to present OpenElec anymore, the famous media center based on linux running Kodi. This system is a bit different from the other Raspbian and co. as it comes with a read-only file system which prevents messing with the OS.

- RGB LED strip individually addressable (WS2801)

Don't make the same mistake I did at the beginning thinking "an LED strip is an LED strip", no no. The ones you want for use with hyperion need to be individually addressable, meaning you can control the LEDs differently at the same time. Each LED is equipped with a micro controller that controls it, and of course the software (Hyperion) needs to have the drivers for these controllers. So there are a bunch of compatible LEDs but I chose the WS2801 which seem to be the most common one.
