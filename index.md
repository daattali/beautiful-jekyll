---
layout: base
title: "Statistics"
---

<div class="banner" style="padding:5px; text-align:center;">
  <div class="banner-content">
  <p>This webpage is a simple collection of detailed resources and information I use for my phd work, as part of the statistics network and other research projects.  I hope with time these resources will develop into a learning resource for researchers and small business owners, regardless of statistical knowledge.</p><p>The resources here are open-source and can be accessed <a href="https://github.com/davan690/" class="btn btn-primary">here</a></p><p>I post some of the interesting social media posts <a href="https://www.facebook.com/StatisticsNetwork/" class="btn btn-primary">here</a></p
</div>

## So far

[General statistics](./_posts/2019-04-29-General-statistics/)
Resources I use for statistics support

[Ecological statistics]("")
Resources I use for my PhD

[Invasive species research]("")
My phd research
Draft manuscripts

## Coming soon

[Reproducibility]("")

[Coding Sessions]("")

[Bio-informatics]("")

Here is the [webpage]("https://github.com/davan690/davan690.github.io/") repository for more computer minded (open-source resources and my research), and a [facebook]("https://www.facebook.com/StatisticsNetwork/")/[twitter]("") feed for new blog posts about statistics and ecology (not all from me). Welcome to the "Pit of Success!" ^[Wickham quote]

[Image from a great talk Hadley Wickham gave last year]("")

# News Feed

<div class="posts-list">
  {% for post in paginator.posts %}
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
      <a href="{{ site.baseurl }}/tags#{{- tag -}}">{{- tag -}}</a>
      {% endfor %}
      {% else %}
        {{ post.tags | join: ", " }}
      {% endif %}
    </div>
    {% endif %}

   </article>
  {% endfor %}
</div>

{% if paginator.total_pages > 1 %}
<ul class="pager main-pager">
  {% if paginator.previous_page %}
  <li class="previous">
    <a href="{{ paginator.previous_page_path | prepend: site.baseurl | replace: '//', '/' }}">&larr; Newer Posts</a>
  </li>
  {% endif %}
  {% if paginator.next_page %}
  <li class="next">
    <a href="{{ paginator.next_page_path | prepend: site.baseurl | replace: '//', '/' }}">Older Posts &rarr;</a>
  </li>
  {% endif %}
</ul>
{% endif %}

# Feedback and comments

[Draft for comments](): Here is the first chapter draft finally.