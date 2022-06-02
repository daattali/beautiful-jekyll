---
title: "Jupyter"
layout: archive
permalink: categories/jupyter
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['jupyter'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}