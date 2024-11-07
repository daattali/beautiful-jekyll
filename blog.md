@@ -1,19 +1,21 @@
---
layout: page
title: "Blog"
permalink: /blog/
---
Welcome to my blog! Here, I share articles, insights, and tutorials on data science and machine learning.

{% for post in site.posts %}
<div class="post-preview">
  <h2>
    <img src="/path/to/your/image.jpg" alt="Post Image" style="width: 40px; height: 40px; vertical-align: middle; margin-right: 10px;">
    {% if post.image %}
      <img src="{{ post.image | relative_url }}" alt="Post Image" style="width: 40px; height: 40px; vertical-align: middle; margin-right: 10px;">
    {% endif %}
    <a href="{{ post.url | relative_url }}">{{ post.title }}</a>
  </h2>
  <p>{{ post.excerpt }}</p>
  <small>Posted on {{ post.date | date: "%B %-d, %Y" }} by {{ post.author }}</small>
  <hr>
</div>
{% endfor %}
