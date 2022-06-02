---
title: "Linux"
layout: archive
permalink: categories/linux
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['linux'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}