---
layout: page title: Hi, I'm Richard 
subtitle: "ML Engineer for Climate Change"
css: "/css/index.css"
meta-title: "Richard Decal - world traveller"
meta-description: "World traveller and digital nomad."
---

<div class="list-filters">
  <a href="/" class="list-filter">All posts</a>
  <a href="/popular" class="list-filter">Most Popular</a>
  <span class="list-filter filter-selected">Travel</span>
</div>

<img src="http://chart.apis.google.com/chart?cht=map:fixed=-70,-180,80,180&chs=450x300&chf=bg,s,336699&chco=d0d0d0,cc0000&chd=s:99999999999999999999999999&chld=MX|US|EC|CA|BR|UY|AR|CN|LA|MM|SG|TH|TW|AU|VU|NZ|DK|FI|FR|IT|NO|SE|CH|GB|VA|BS" width="450" height="300" ><br/>
visited 26 states (11.5%)<br/>

<div class="posts-list">
  {% for post in site.tags.travel %}
  <article>
    <a class="post-preview" href="{{ post.url | prepend: site.baseurl }}">
	    <h2 class="post-title">{{ post.title }}</h2>

	    {% if post.subtitle %}
	    <h3 class="post-subtitle">
	      {{ post.subtitle }}
	    </h3>
	    {% endif %}
      <p class="post-meta">
        Posted on {{ post.date | date: "%B %-d, %Y" }}
      </p>

      <div class="post-entry">
        {{ post.content | truncatewords: 50 | strip_html | xml_escape}}
        <span href="{{ post.url | prepend: site.baseurl }}" class="post-read-more">[Read&nbsp;More]</span>
      </div>
    </a>
  </article>
  {% endfor %}
</div>

