---
layout: page
title: Read later
subtitle: All my "read later" articles
published: true
---

This page is automatically updated with all the articles that I save in [my pocket](https://app.getpocket.com/) to read later. 

|Date                |Article             |
|-------------------|--------------------|
{% for article in site.data.articles.rows -%}

{% if article.article -%}
| {{ article.date }} | <a href="{{ article.url }}"> {{ article.article }}  </a>|
{% endif %}

{%- endfor -%}
|--------------------|--------------------|