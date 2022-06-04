---
title: "Effective_python"
layout: archive
permalink: categories/effective_python
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['effective_python'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}