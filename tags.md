---
layout: page
title: Tags
permalink: /tags/
---

<h1>Tags</h1>
<ul>
  {% for tag in site.tags %}
    <li><a href="{{ site.baseurl }}/tags/{{ tag[0] }}">{{ tag[0] }}</a></li>
  {% endfor %}
</ul>
