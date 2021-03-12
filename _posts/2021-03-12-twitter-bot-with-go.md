---
layout: post
published: true
title: 'Creating a Twitter Bot with Go'
subtitle: 'Automatically say hi to mentions on Twitter'
date: '2021-03-12'
image: /assets/img/twitter-logo.png
share-img: /assets/img/twitter-logo.png
tags: [golang, heroku, twitter, bot]
---

I keep experimenting with go and bots, so this week I decided to create a Twitter bot. It's not the typical bot that just publishes things or does some scraping, this one will react to mentions; each time someone mentions the bot, it will reply with a "hello". This is possible through the [Account Activity API](https://developer.twitter.com/en/docs/twitter-api/enterprise/account-activity-api/overview) of Twitter, which will call our service for every new event related to our bot.

## Brief explanation

The code is pretty simple and straightforward, so I will not get into too many details; there are 3 endpoints on our server:

### POST `/webhook/twitter`

This is where the behavior of our bot lives. So, in my case is only replying with "hello", but here is where you would make any customization in case you clone/fork it.

### GET `/webhook/twitter`

For security reasons, Twitter requires us to have an endpoint that will solve a CRC request. So we follow [Twitter guidelines](https://developer.twitter.com/en/docs/twitter-api/enterprise/account-activity-api/guides/securing-webhooks) and that's what this endpoint is doing.

### POST/GET... `/`

Nothing fancy. Just returning "Server is up and running" for you to make sure that the *server is up and running*.

## Fork it, clone it, use it!

Feel free to [clone/fork the repo](https://github.com/JosemyDuarte/TwitterGoBot) and customize it to your need. You will find instructions to deploy it on [Heroku](https://heroku.com/) or even try it on your machine if you want.


