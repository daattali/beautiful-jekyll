---
layout: post
title: Visualization: Atlantic Hurricanes
subtitle: 100 years of data animated
gh-repo: pixelatedbrian/pixelated-hurricanes
gh-badge: [star, fork, follow]
---

Hurricane data from [NOAA](https://www.ncdc.noaa.gov/ibtracs/index.php?name=wmo-data)

Visualizations inspired by [/r/dataisbeauitful](https://www.reddit.com/r/dataisbeautiful/comments/6y0h2q/100_years_of_hurricane_paths_animated_oc/)

<iframe src='https://gfycat.com/ifr/MeatyShamelessHedgehog' frameborder='0' scrolling='no' allowfullscreen width='640' height='360'></iframe>

~~~

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

![Crepe](http://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg)

Here's a code chunk:
~~~

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
