---
title: "Make"
layout: archive
permalink: categories/make
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['make'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}