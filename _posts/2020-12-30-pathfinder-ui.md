---
layout: post
title: Route-finding with pathfinder-ui
tags: [tech]
comments: true
---

I recently needed a list of all the routes that were being used in a Node.js/Express application. After some
intense Googling, I found an npm package that would do exactly what I required.

All you need to do to use it is:

```javascript
npm i pathfinder-ui
```
and add a route similar to the below:

```javascript
var pathfinderUI = require('pathfinder-ui')
app.use('/pathfinder', function(req, res, next){
    pathfinderUI(app)
    next()
}, pathfinderUI.router)
```

This provides a wonderful tree and table view of all your routes.
![](https://s3.amazonaws.com/poly-screenshots.angel.co/Project/4b/154634/8a313313182b2bab4b0e00f483f647b7-original.png)

![](https://s3.amazonaws.com/poly-screenshots.angel.co/Project/4b/154634/8b4aff1d7a5b7a648773bd7915b19791-original.png)

It also says that it provides a way to test the APIs but it is slightly underbaked compared to their other offerings. 
I copy-pasted the table into excel and used Postman to test the APIs which was convenient for my usecase.
