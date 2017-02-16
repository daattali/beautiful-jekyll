---
layout: post
title: HTMLConsole.js
category: posts
customjs:
 - https://jsfiddle.net/riftrid3r/pr3c0fhp/embed/
---
{% for js in page.customjs %}
<script async type="text/javascript" src="{{ js }}"></script>
{% endfor %}
