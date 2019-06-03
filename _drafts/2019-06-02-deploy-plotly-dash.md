---
layout: post
title: Deploying Plotly Dash app to the cloud
subtitle: Lessons learned 
tags: [code]
comments: true
---

Plotly is great
Flask locally
However, I ran into issues just following the documentation and boilerplate examples.

Deploying continuous, autorestart etc.

Caprover was really easy,
now, Caprover is available for deploying other dash apps to the running instance!
Turns out you can't run with python. need gunicorn.
Here is my example captain file:


"App needs to be callable"
need a dockerfile
ports.
didnt upgrade pip. this made my pandas dependencies silently not get updated correctly. Also, make sure to run this all as one line or it might not work.

```python
import flask

server = flask.Flask(__name__)
app = dash.Dash(__name__, server=server)
```

The port of the 

You can write regular [markdown](http://markdowntutorial.com/) here and Jekyll will automatically convert it to a nice webpage.  I strongly encourage you to [take 5 minutes to learn how to write in markdown](http://markdowntutorial.com/) - it'll teach you how to transform regular text into bold/italics/headings/tables/etc.

**Here is some bold text**

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
