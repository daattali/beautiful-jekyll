---
layout: post
title: Progfun, Eclipse, JDKs, and Platform Agnosticism
date: '2012-09-22T17:05:00.000+02:00'
author: Morten
tags:
- eclipse
- JDK
- Scala
- Progfun
- Coursera
- OSs
modified_time: '2012-09-22T17:05:50.088+02:00'
blogger_id: tag:blogger.com,1999:blog-6967032375013519080.post-54829833926944643
blogger_orig_url: https://m635j520.blogspot.com/2012/09/progfun-eclipse-jdks-and-platform.html
cover-img: http://farm8.staticflickr.com/7241/7180310736_85ace2a37a.jpg
thumbnail-img: http://farm8.staticflickr.com/7241/7180310736_85ace2a37a.jpg
share-img: http://farm8.staticflickr.com/7241/7180310736_85ace2a37a.jpg
---

[![Fattigfolket @ Periscope, Lyon](http://farm8.staticflickr.com/7241/7180310736_85ace2a37a.jpg)](http://www.flickr.com/photos/mortenjohs/7180310736/ "Fattigfolket @ Periscope, Lyon by mortenjohs, on Flickr")

I'll be following the [Functional Programming Principles in Scala](https://class.coursera.org/progfun-2012-001/auth/auth_redirector?type=login&subtype=normal) course offered by Coursera this Autumn. To get you started the good folks behind the course have provided lots of info on how to install necessary software etc. However, I ran into a problem, and it's subsequent solution, that I would like to document here.  
  
I'll be following the course a bit from here and a bit from there. Sometimes on my mac, sometimes on a linux laptop, sometimes on a windows machine. Anyway, I have my course files in my Dropbox and pick them up from there as needed on the various OSes. Problem was when opening the my scala projects in eclipse in OSX after compiling them under Windows, I got a cryptic "error in scala compiler null" and was unable to clean and (re)compile my scala programs. I realised that I was running JDK 6 on my mac and JDK 7 on anything else, so I figured that might have something to do with it.  
  
After following [Mary Hamlin](http://stackoverflow.com/users/426700/mary-hamlin)'s answer here: [http://stackoverflow.com/questions/7669899/how-to-run-eclipse-indigo-on-jdk-1-7-on-osx](http://stackoverflow.com/questions/7669899/how-to-run-eclipse-indigo-on-jdk-1-7-on-osx) my problems seems to be over. Thanks Mary!  
  
To the functional programming mobile!