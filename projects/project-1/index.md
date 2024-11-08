---
layout: page
title: "Project 1"
permalink: /projects/project-1/
---
This page contains blog-style entries detailing the progress and updates for Project 1.

{% for post in site.project_posts %}
<div class="post-preview" style="margin-bottom: 20px;">
  <div style="padding-right: 15px;">
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
