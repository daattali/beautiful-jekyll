---
title: "Dataset"
layout: archive
permalink: categories/dataset
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['dataset'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}