---
layout: page
title: About me
subtitle: A little more about me
---

{% capture aboutme %}{% include aboutme.md %}{% endcapture %}
{{ aboutme | markdownify }}
