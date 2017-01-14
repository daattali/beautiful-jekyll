---
layout: default
---
<section class="previews">
  <div>
    {% for post in paginator.posts %}
      <figure class="absolute-bg preview__img" style="background-image: url('{{ post.image }}');"></figure>
    {% endfor %}
    <div class="previews__container">
      <span>Welcome to</span>
      <h1>{{ site.title }}</h1>
    </div>
  </div>

  <div>
    <header>
      <ul class="tabs">
        <li class="tabs__item">Posts</li>
        <li class="tabs__item">Categories</li>
      </ul>
    </header>

    <div class="tab">
      <ul itemscope itemtype="http://schema.org/Blog">
        {% for post in paginator.posts %}
          <li class="preview" itemprop="blogPost" itemscope itemtype="http://schema.org/BlogPosting">
            <a class="preview__link" href="{{ post.url | prepend: site.baseurl }}" itemprop="url">
              <span class="preview__date" itemprop="datePublished" datetime="{{ post.date | date_to_xmlschema }}">{{ post.date | date: "%b %-d, %Y" }}</span>
              <h2 class="preview__header" itemprop="name">{{ post.title }}</h2>
              <p class="preview__excerpt" itemprop="description">{{ post.content | strip_html | truncatewords: 30 }}</p>
              <span class="preview__more">Read More</span>
            </a>
          </li>
        {% endfor %}
      </ul>

      {% if paginator.total_pages > 1 %}
        <div class="pagination">
          {% if paginator.previous_page %}
            <a href="{{ paginator.previous_page_path | prepend: site.baseurl }}">Previous</a>
          {% endif %}

          {% if paginator.next_page %}
            <a href="{{ paginator.next_page_path | prepend: site.baseurl }}">Next</a>
          {% endif %}
        </div>
      {% endif %}

      {% include archive-link.html %}
    </div>

    {% include categories-tab.html %}

  </div>

</section>
