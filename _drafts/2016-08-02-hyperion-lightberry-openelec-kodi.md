---
layout: post
published: false
title: Hyperion + Lightberry + OpenElec + Kodi
---
These last few weeks I got more and more interested in home automation and other cool thing like LEDs so I thought I'd deviate from virtualization the time of a tutorial. 

I did this project to create a mood lighting behind the TV that "follows" the colors displayed on the screen and enhance the experience of movie watching. It is pretty much an open source version of Philips' Ambilight except it can work on a wide range of devicew and is much cheaper (with a little bit of hardware and a bit more elbow grease).

## Some theory

The system is made up of 3 main components:

- [Hyperion](https://hyperion-project.org/wiki/Main)

The software that controls the LEDs independently by sending the right signals to the hardware interface of the lights. Hyperion is an open source project under MIT license that can not only be used for the TV but to control lights in general. There are other similar softwares such as Boblight.

- [Lightberry](http://lightberry.eu/)

Lightberry is the hardware bit that acts as an interface between Hyperion and the LED stripe. It converts the commands sent by hyperion into a gibbrish understandable by the lights. Lightberry offers multiple devices and packs that offer a different level of integration.  
In this tutorial I am only using the USB converter. There is a version with a GPIO interface as well but I already have a case that closes the top ofthe raspberry. 

This converter alone will only make the LEDs work with the Raspberry PI. If you have other devices that you would like to integrate such as a DVC player or a Xbox and such you will need the HDMI kit with and HDMI switch.

- [OpenElec](http://openelec.tv/)

I don't think it is needed to present OpenElec anymore, the famous media center based on linux running Kodi. This system is a bit different from the other Raspbian and co. as it comes with a read-only file system which prevents messing with the OS.