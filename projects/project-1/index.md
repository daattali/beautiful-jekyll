---
layout: page
title: "Project 1"
permalink: /projects/project-1/
---

# Project 1
This page contains blog-style entries detailing the progress and updates for Project 1.

## Blog Entries
{% for post in site.project_posts %}
- [{{ post.title }}]({{ post.url | relative_url }})
{% endfor %}

[GitHub Repository for Project 1](https://github.com/yourusername/project-1)
