---
title: "DSSE->News"
layout: textlay
excerpt: "DSSE -- News"
sitemap: false
permalink: /allnews.html
---

# News and Activities

{% for article in site.data.news %}
<span style="color: #7a0000;">[{{ article.date }}]</span>
<p><em>{{ article.headline }}</em></p>
{% endfor %}
