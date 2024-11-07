---
layout: page
title: "Blog"
permalink: /blog/
---
<h1>Blog</h1>
Welcome to my blog! Here, I share articles, insights, and tutorials on data science and machine learning.

{% for post in site.posts %}
<div class="post-preview">
  <h2><a href="{{ post.url | relative_url }}">{{ post.title }}</a></h2>
  <p>{{ post.excerpt }}</p>
  <small>Posted on {{ post.date | date: "%B %-d, %Y" }} by {{ post.author }}</small>
  <hr>
</div>
{% endfor %}
