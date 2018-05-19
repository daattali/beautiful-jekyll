---
layout: default
permalink: "sitemap"
title: sitemap
show-avatar: true
---

### All Posts

| <i class="fa fa-calendar" aria-hidden="true"></i> Date | <i class="fa fa-pencil-square-o" aria-hidden="true"></i> Title | <i class="fa fa-hashtag" aria-hidden="true"></i> Tags |
| ---- | ----- | ---- |{% for post in site.posts %}
| {{ post.date | date: "%m/%d/%Y" }} | <a href="{{ url }}{{ post.url | remove: 'index.html' }}">{{ post.title }}</a> | {% for tag in post.tags %} <i class="fa fa-tag" aria-hidden="true"></i>{{ tag }} {% endfor %}| {% endfor %}

### All Pages
<ul>
{% for page in site.pages %}
    {% if page.layout != nil %}
        {% if page.layout != 'feed' %}
            {% if page.title != 'Sitemap' or page.title != nil%}
                {% if page.title != nil %}
                    {% if page.url contains 'tag/' or page.title contains '404' or page.url contains 'blog/page' %}
                    {% else %}
<li><a href="{{ url }}{{ page.url | remove: 'index.html' }}">{{ page.title }}</a> </li>
                    {% endif %}
                {% endif %}
            {% endif %}
        {% endif %}
    {% endif %}
{% endfor %}
</ul>
