---
layout: post
title: Data Modeling - Comer project
subtitle: Practice to make data modeling for Comer project (web application)
# thumbnail-img: /assets/img/rootMe/11d59cb34397e986062eb515f4d32421.png
tags: [MongoDB, data modeling, user case, NOSQL]
comments: true
author: Lantana Park
---

## User Case

1. Users:

    They have the capability to create an account, view booked experiences, and access their previously opened sessions. To sign up, an individual is required to provide an email address, create a password, and confirm the password. Upon submitting this information, they will receive an email containing a verification token. This token is appended to a URL; clicking on the hyper linked URL from the sent email activates the user's account, enabling them to engage in any desired activity on this website.

2. Experiences:

    Users can create/edit events. They can upload image files, which are stored on AWS S3. The event details, including title, description, perks (such as food, beverages, transportation, equipment, and others), guest requirements (minimum age, allowance of kids and pets, maximum group size), languages spoken, general availability (start time, end time, date range), tags, price (with currency), additional notes for consideration by users, likes from other users, and cancellation policy, are stored in the database. To facilitate event location, information such as country, city, state, address (including street number), longitude, latitude, coordinates, and full address are also stored in the database. These location details are provided via the Mapbox library from the client side.

3. Comments:

    Users are able to create and delete comments on the detailed event pages. An experience page may contain multiple comments. When a comment is posted, the user ID and experience ID are stored as foreign keys, along with the comment's description.

4. Availiabilities:

    When a user opens their event, an availability entity is created based on data from the start time, end time, and date range (Experience entity). This entity includes the experience ID as a foreign key, dateMaxGuestPairs, booking information (to track who booked the event), and a timestamp. Within the dateMaxGuestPairs, objects are stored that include details such as the date, start time, end time, maximum number of guests allowed, price, and current status. When an event is booked by a user, the number of maximum guests allowed is accordingly decreased.

## Diagram

## ERD CODE
