---
layout: page

title: Latest News
subtitle: Events and Publications
permalink: "latest"
excerpt: "Group meetings, seminars, latest publications."
#image: "/img/image/ps-journey.jpg"
show-avatar: true
bigimg:	# /path/to/img - or multiple entries <- "Path": "Description">
  - "/assets/img/astroWHUheader.jpg" : "Photo by Xiaoming Jiang (蒋效铭)"
# category: Resources
tags: [News]
googlefonts: ["Share+Tech+Mono"]
comments: true
# custom page vars
edit: "04-06-2020"
---
<div class="spacer"></div>


<ul class="pager main-pager">
  <li>
    <a href="{{site.baseurl}}/blog">Archive </a>
  </li>
</ul>

<div class="posts-list">
  {% for post in site.posts limit:15 %}
  <article class="post-preview">
    <a href="{{ post.url | prepend: site.baseurl }}">
      <h2 class="post-title">{{ post.title }}</h2>

      {% if post.subtitle %}
      <h3 class="post-subtitle">
        {{ post.subtitle }}
      </h3>
      {% endif %}
    </a>

    <p class="post-meta">
      Posted on {{ post.date | date: "%B %-d, %Y" }}
    </p>

    <div class="post-entry-container">
      {% if post.image %}
      <div class="post-image">
        <a href="{{ post.url | prepend: site.baseurl }}">
          <img src="{{ post.image }}">
        </a>
      </div>
      {% endif %}
      <div class="post-entry">
        {{ post.excerpt | strip_html | xml_escape | truncatewords: site.excerpt_length }}
        {% assign excerpt_word_count = post.excerpt | number_of_words %}
        {% if post.content != post.excerpt or excerpt_word_count > site.excerpt_length %}
          <a href="{{ post.url | prepend: site.baseurl }}" class="post-read-more">[Read&nbsp;More]</a>
        {% endif %}
      </div>
    </div>

    {% if post.tags.size > 0 %}
    <div class="blog-tags">
      Tags:
      {% if site.link-tags %}
      {% for tag in post.tags %}
      <a href="{{ site.baseurl }}/tags#{{ tag }}">{{ tag }}</a>
      {% endfor %}
      {% else %}
        {{ post.tags | join: ", " }}
      {% endif %}
    </div>
    {% endif %}

   </article>
  {% endfor %}
</div>
