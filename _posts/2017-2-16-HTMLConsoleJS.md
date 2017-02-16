---
layout: post
comments: true
title: HTMLConsole.js
category: posts
customjs:
 - https://jsfiddle.net/riftrid3r/pr3c0fhp/embed/result/
---
We wanted a JavaScript console output while collaborating on JSFiddle. So I built one. Please use this freely. If you can think of additions, notice bugs, or just want to tell me how terrible I am at this, let me know in the comments.
{% for js in page.customjs %}
<script async type="text/javascript" src="{{ js }}"></script>
{% endfor %}
