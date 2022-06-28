---
layout: page
title: Robot Demos
subtitle:
demos:
  - title: Multi-Modal Transfer Learning for Grasping Transparent and Specular Objects
    video_url: https://youtu.be/G3BpLlcwS1U
    web_url: https://sites.google.com/view/transparent-specular-grasping/home 
---

{% for demo in page.demos %}
<div class="row demo-row">
    <h1> {{demo.title}} </h1>
    <div class="embed-responsive embed-responsive-16by9">
      <iframe class="embed-responsive-item" src="{{ demo.video_url }}" allowfullscreen></iframe>
    </div>
    <a target="_blank" href="{{ demo.web_url }}">
      Website
    </a>
</div>
{% endfor %}
