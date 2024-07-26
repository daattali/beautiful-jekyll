---
layout: page
title: Tags
permalink: /tags/
---

<h1>Tags</h1>
<div class="tags-container">
  {% for tag in site.tags %}
    <div class="tag-section">
      <h2>{{ tag[0] }}</h2>
      <ul>
        {% for post in tag[1] %}
          <li>
            <a href="{{ post.url }}">
              {% if post.thumbnail-img %}
                <img src="{{ post.thumbnail-img }}" alt="{{ post.title }} thumbnail" class="thumbnail">
              {% endif %}
              {{ post.title }}
            </a>
          </li>
        {% endfor %}
      </ul>
    </div>
  {% endfor %}
</div>
