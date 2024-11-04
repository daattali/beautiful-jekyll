---
layout: base
---

{% include header.html type="post" %}

<main class="{% if page.full-width %} container-fluid {% else %} container-md {% endif %}">
  <div class="row">
    <div class="{% if page.full-width %} col {% else %} col-xl-8 offset-xl-2 col-lg-10 offset-lg-1 {% endif %}">

      {% if page.gh-repo %}
        {% assign gh_split =  page.gh-repo | split:'/'  %}
        {% assign gh_user =  gh_split[0]  %}
        {% assign gh_repo =  gh_split[1]  %}

        <div id="header-gh-btns">
          {% if page.gh-badge.size > 0 %}
            {% for badge in page.gh-badge %}
              {% case badge %}
                {% when 'star'%}
                  <iframe src="https://ghbtns.com/github-btn.html?user={{ gh_user }}&repo={{ gh_repo }}&type=star&count=true" frameborder="0" scrolling="0" width="120px" height="20px"></iframe>
                {% when 'watch'%}
                  <iframe src="https://ghbtns.com/github-btn.html?user={{ gh_user }}&repo={{ gh_repo }}&type=watch&v=2&count=true" frameborder="0" scrolling="0" width="120px" height="20px"></iframe>
                {% when 'fork'%}
                  <iframe src="https://ghbtns.com/github-btn.html?user={{ gh_user }}&repo={{ gh_repo }}&type=fork&count=true" frameborder="0" scrolling="0" width="120px" height="20px"></iframe>
                {% when 'follow'%}
                  <iframe src="https://ghbtns.com/github-btn.html?user={{ gh_user }}&type=follow&count=true" frameborder="0" scrolling="0" width="220px" height="20px"></iframe>
              {% endcase %}
            {% endfor %}
          {% endif %}
        </div>
      {% endif %}

      {% if page.before-content %}
        <div class="before-content">
          {% for file in page.before-content %}
            {% include {{ file }} %}
          {% endfor %}
        </div>
      {% endif %}

      <div class="blog-post">
        {{ content }}
      </div>

      {% if page.tags.size > 0 %}
        <div class="blog-tags">
          <span>Tags:</span>
          {% for tag in page.tags %}
            <a href="{{ '/tags' | relative_url }}#{{- tag -}}">{{- tag -}}</a>
          {% endfor %}
        </div>
      {% endif %}

      {% if page.after-content %}
        <div class="after-content">
          {% for file in page.after-content %}
            {% include {{ file }} %}
          {% endfor %}
        </div>
      {% endif %}

      {% if page.social-share %}
        {% include social-share.html %}
      {% endif %}

      <ul class="pagination blog-pager">
        {% if page.previous.url %}
        <li class="page-item previous">
          <a class="page-link" href="{{ page.previous.url | relative_url }}" data-toggle="tooltip" data-placement="top" title="{{page.previous.title | strip_html | xml_escape}}">
            <i class="fas fa-arrow-left" alt="Previous Post"></i>
            <span class="d-none d-sm-inline-block">Previous Post</span>
          </a>
        </li>
        {% endif %}
        {% if page.next.url %}
        <li class="page-item next">
          <a class="page-link" href="{{ page.next.url | relative_url }}" data-toggle="tooltip" data-placement="top" title="{{page.next.title | strip_html | xml_escape}}">
            <span class="d-none d-sm-inline-block">Next Post</span>
            <i class="fas fa-arrow-right" alt="Next Post"></i>
          </a>
        </li>
        {% endif %}
      </ul>
      {% include comments.html %}
    </div>
  </div>
</main>
