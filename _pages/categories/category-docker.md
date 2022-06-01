---
title: "Docker"
layout: archive
permalink: categories/docker
author_profile: true
sidebar_main: true
---

{% assign posts = site.categories['docker'] %}
{% for post in posts %} {% include archive-single2.html type=page.entries_layout %} {% endfor %}