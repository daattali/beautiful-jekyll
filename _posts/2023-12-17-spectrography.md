---
layout: post
title: Fourier Time Series Analysis In Python
subtitle: Data Segmentation with the Spectrogram and DBSCAN Clustering
gh-repo: cormazz/spectrography
gh-badge: [star, fork, follow]
tags: [test]
comments: true
author: Corrado R. Mazzarelli
---

{: .box-success}
All the material used to create this is within the GitHub repository linked above. I strongly encourage you to explore the [resources](#resources) linked below. They have guided me on my data science journey and it is truly some remarkable information, all available for free.

# Concept
While working at GE, I did my best to seek out fun data science projects to sate intellectual curiosity. Two years ago, someone approached me and asked if there was a way to cluster periodic data based on its frequency. The goal was to turn a plot of data that looked like this:

{% include bp.spectrography/initial_data.html %}

into this

{% include bp.spectrography/clustered_data.html %}

{: .box-note}
**Note:** If you like these plots, look into [Plotly](https://plotly.com/python/) which allows you to save interactive plots as html files.

## Context
I'm not going to go too in depth here regarding what testing GE was doing. However, the data was from a wear test rig where different samples of material were rubbed against each other and properties such as load and displacement were recorded. This data could be used to help describe material properties to let engineers predict the life of different gas turbine components. In this case, there were low-frequency, high-amplitude sections of the data interspersed between high-frequency, low-amplitude sections. If you need a refresher on those, [check this out](https://www.mathsisfun.com/algebra/amplitude-period-frequency-phase-shift.html). 

## Here is a secondary heading

[This is a link to a different site](https://deanattali.com/) and [this is a link to a section inside this page](#local-urls).

Here's a table:

| Number | Next number | Previous number |
| :------ |:--- | :--- |
| Five | Six | Four |
| Ten | Eleven | Nine |
| Seven | Eight | Six |
| Two | Three | One |

How about a yummy crepe?

![Crepe](https://beautifuljekyll.com/assets/img/crepe.jpg)

It can also be centered!

![Crepe](https://beautifuljekyll.com/assets/img/crepe.jpg){: .mx-auto.d-block :}

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

## Local URLs in project sites {#local-urls}

When hosting a *project site* on GitHub Pages (for example, `https://USERNAME.github.io/MyProject`), URLs that begin with `/` and refer to local files may not work correctly due to how the root URL (`/`) is interpreted by GitHub Pages. You can read more about it [in the FAQ](https://beautifuljekyll.com/faq/#links-in-project-page). To demonstrate the issue, the following local image will be broken **if your site is a project site:**

![Crepe](/assets/img/crepe.jpg)

If the above image is broken, then you'll need to follow the instructions [in the FAQ](https://beautifuljekyll.com/faq/#links-in-project-page). Here is proof that it can be fixed:

![Crepe]({{ '/assets/img/crepe.jpg' | relative_url }})

{% include bp.spectrography/spectrogram.html %}

# Resources