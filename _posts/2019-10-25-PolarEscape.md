---
layout: post
title: PolarEscape
subtitle: A game by Eyal Golan, Yuval Kasner and Assaf Molad.
gh-repo: daattali/beautiful-jekyll
gh-badge: [star, fork, follow]
tags: [test]
comments: true
---

PolarEscpae is a race game in which penguins need to pass a ball through the finish line, while going through an obstacle course. The player that passes the ball through the finish line – wins.
The game consists of a menu screen, how to play screen, 2 "regular levels", a special fire level, a credit screen and an end screen.
In the “regular” levels, the ground and obstacles are made of ice, and in the fire level they are made of lava and fire. The first “regular” level is relatively easy, while the second level contains moving surfaces and a harder obstacle course.
The game contains several types of bonuses, some have a positive effect, and some a negative one. For example, a bonus with a positive effect is the extra speed bonus. In the fire level, there is a bonus with a negative effect that throws the penguin back to the start of the obstacle course.
The game contains and end screen which shows the player’s scores.
The game also contains background music and sound effects when the penguins hit the ball and the obstacles.

You can write regular [markdown](http://markdowntutorial.com/) here and Jekyll will automatically convert it to a nice webpage.  I strongly encourage you to [take 5 minutes to learn how to write in markdown](http://markdowntutorial.com/) - it'll teach you how to transform regular text into bold/italics/headings/tables/etc.

**Here is some bold text**

## Here is a secondary heading

Here's a useless table:

| Number | Next number | Previous number |
| :------ |:--- | :--- |
| Five | Six | Four |
| Ten | Eleven | Nine |
| Seven | Eight | Six |
| Two | Three | One |


How about a yummy crepe?

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg)

It can also be centered!

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg){: .center-block :}

Here's a code chunk:

~~~
var foo = function(x) {
  return(x + 5);
}
foo(3)
~~~

And here is the same code with syntax highlighting:

```javascript
var foo = function(x) {
  return(x + 5);
}
foo(3)
```

And here is the same code yet again but with line numbers:

{% highlight javascript linenos %}
var foo = function(x) {
  return(x + 5);
}
foo(3)
{% endhighlight %}

## Boxes
You can add notification, warning and error boxes like this:

### Notification

{: .box-note}
**Note:** This is a notification box.

### Warning

{: .box-warning}
**Warning:** This is a warning box.

### Error

{: .box-error}
**Error:** This is an error box.
