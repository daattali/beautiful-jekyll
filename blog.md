---
layout: page
title: "Blog"
permalink: /blog/
---
Welcome to my blog! Here, I share articles, insights, and tutorials on data science and machine learning.


{% for post in site.posts %}
<div class="post-preview" style="display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 20px;">
  <div style="flex: 1; padding-right: 15px;">
    <h2 style="margin: 0;">
      <a href="{{ post.url | relative_url }}" style="text-decoration: none; color: #333;">{{ post.title }}</a>
    </h2>
    <p>{{ post.excerpt }}</p>
    <small>Posted on {{ post.date | date: "%B %-d, %Y" }} by {{ post.author }}</small>
  </div>
  {% if post.image %}
    <img src="{{ post.image | relative_url }}" alt="Post Image" style="width: 100px; height: 100px; object-fit: cover;">
  {% endif %}
</div>
<hr>
{% endfor %}
