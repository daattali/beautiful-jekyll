---
layout: page
title: "My Projects"
permalink: /projects/
---

## My Projects

Here are some of the projects I've worked on:

<ul>
  {% for post in site.posts %}
    {% if post.categories contains 'projects' %}
      <li><a href="{{ post.url }}">{{ post.title }}</a> - {{ post.date | date: "%B %d, %Y" }}</li>
    {% endif %}
  {% endfor %}
</ul>
