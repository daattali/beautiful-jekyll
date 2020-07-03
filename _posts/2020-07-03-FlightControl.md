---
layout: post
title: FlightControl RESTful web application
subtitle: A flight control web app created by Almog Lev, Eyal Golan, Sapir Deutscher and Ofir Netzer.
gh-repo: eyalgolan/FlightControl
gh-badge: [star, fork, follow]
tags: [C#, ASP.NET Core, Entity Framework, SQL, Javascript, JQuery, bootstrap, html, css]
comments: true
---


We built our frontend using Javascript, JQuery, bootstrap, html and css. 

The backend was built using C#, ASP.NET Core, and Entity Framework (with in-memory SQL DB). We created a RESTful API using WebAPI.
For unit testing we used Moq.

The web application features a flight control system that shows active flights, enables adding new flight plans and shows details about each flight. Upon clicking on a flight, its path is shown on the map.

![WebApplicationFlightControl](img/WebApplicationFlightControl.JPG)
