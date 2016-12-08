# Beautiful-Jekyll Theme (beautiful-jekyll-theme gem)

[![Gem Version](https://badge.fury.io/rb/beautiful-jekyll-theme.svg)](https://badge.fury.io/rb/beautiful-jekyll-theme)

> *Copyright 2016 [Dean Attali](http://deanattali.com). Licensed under the MIT license.*

**Beautiful-Jekyll** is a ready-to-use Jekyll theme to help you create an awesome website quickly. Perfect for personal blogs or simple project websites, with a focus on responsive and clean design. You can look at [my personal website](http://deanattali.com) to see it in use, or see examples of websites other people created using this theme [here](https://github.com/daattali/beautiful-jekyll#showcased-users-success-stories).

If you need a bit of help or have comments, feel free to [contact me](http://deanattali.com/aboutme#contact). Even if you don't have anything important to say but found this useful, I'd love to [hear about it](http://deanattali.com/aboutme#contact). Lastly, if you like this theme, please consider [supporting me](https://www.paypal.me/daattali/20) if you want to make me extra happy. :)

![Screenshot](./screenshot.png)

## Prerequisites

To use this theme's gem, you need to first have a functioning Jekyll website. If you don't, there are many resources online for how to set up a Jekyll site. Here are the basic commands to get a minimal Jekyll site set up in Ubuntu:

```
sudo apt-get install ruby ruby-dev make gcc
sudo gem install jekyll bundler
jekyll new ~/mysite
```

## Installation

To use the Beautiful-Jekyll theme, add this line to your Jekyll site's `Gemfile`:

```ruby
gem "beautiful-jekyll-theme"
```

Then add this line to your Jekyll site's `_config.yml`:

```yaml
theme: beautiful-jekyll
```

And finally execute:

    $ bundle

To preview your site, run `bundle exec jekyll serve` (optionally with the `--host 0.0.0.0` flag if needed) and open your browser at `http://localhost:4000`.

## Usage


```
navbar-links:
  About Me: "aboutme"
  Resources:
    - Beautiful Jekyll: "http://deanattali.com/beautiful-jekyll/"
    - Learn markdown: "http://www.markdowntutorial.com/"
    - GitHub Pages: "https://pages.github.com/"
  Author's home: "http://deanattali.com"
```

```
avatar: "/img/avatar-icon.png"
```

```
author:
  name: Some Person
  email: "youremail@domain.com"
  facebook: yourname  # eg. daattali
  github: yourname    # eg. daattali
  twitter: yourname   # eg. daattali
  reddit: yourname    # eg. daattali
  google-plus: +yourname   # eg. +DeanAttali or 109424658772469020925
  linkedin: yourname  # eg. daattali
  xing: yourname      # eg. daattali
  stackoverflow: yourlink  # eg. "3943160/daattali"
  snapchat: yourname  # eg. daattali
  instagram: yourname # eg. daattali
  youtube: yourlink   # eg. user/daattali or channel/daattali
  spotify: yourname   # eg. daattali
```

```
# Select which share links to show in posts
share-links-active:
  twitter: true
  facebook: true
  google: false
  linkedin: true
```

```
url-pretty: "MyWebsite.com
```

```
disqus: ""
```

```
google_analytics
```


```
defaults:
  -
    scope:
      path: ""
      type: "posts"
    values:
      layout: "post"
  -
    scope:
      path: "" # all files
    values:
      layout: "page"
```


### Adding an index page

paginate: 5
gems:
  - jekyll-paginate
  
```
---
title: My Website
subtitle: Some short description of my site
---

<div class="posts-list">
  {% for post in paginator.posts %}
  <article class="post-preview">
    <a href="{{ post.url }}">
      <h2 class="post-title">{{ post.title }}</h2>
        {% if post.subtitle %}
          <h3 class="post-subtitle">{{ post.subtitle }}</h3>
        {% endif %}
    </a>

    <p class="post-meta">
      Posted on {{ post.date | date: "%B %-d, %Y" }}
    </p>

    <div class="post-entry">
      {{ post.excerpt | strip_html | xml_escape | truncatewords: 50 }}
      {% assign excerpt_word_count = post.excerpt | number_of_words %}
      {% if post.content != post.excerpt or excerpt_word_count > 50 %}
        <a href="{{ post.url }}" class="post-read-more">[Read&nbsp;More]</a>
      {% endif %}
    </div>

    {% if post.tags.size > 0 %}
    <div class="blog-tags">
      Tags:
      {{ post.tags | join: ", " }}
    </div>
    {% endif %}

   </article>
  {% endfor %}
</div>

{% if paginator.total_pages > 1 %}
<ul class="pager main-pager">
  {% if paginator.previous_page %}
  <li class="previous">
    <a href="{{ paginator.previous_page_path | replace: '//', '/' }}">&larr; Newer Posts</a>
  </li>
  {% endif %}
  {% if paginator.next_page %}
  <li class="next">
    <a href="{{ paginator.next_page_path | replace: '//', '/' }}">Older Posts &rarr;</a>
  </li>
  {% endif %}
</ul>
{% endif %}

```

## Contributions

If you find anything wrong or would like to contribute in any way, feel free to submit a pull request/open an issue [on GitHub](https://github.com/daattali/beautiful-jekyll), or [send me a message](http://deanattali.com/contact).

Thank you to [all contributors](https://github.com/daattali/beautiful-jekyll/graphs/contributors). Special thanks to the following people with non-trivial contributions (in chronological order): [@hristoyankov](https://github.com/hristoyankov), [@jamesonzimmer](https://github.com/jamesonzimmer), [@XNerv](https://github.com/XNerv), [@epwalsh](https://github.com/epwalsh), [@rtlee9](https://github.com/rtlee9).

## Credits

This template was not made entirely from scratch. I would like to give special thanks to:
- [Barry Clark](https://github.com/barryclark) and his project [Jekyll Now](https://github.com/barryclark/jekyll-now), from whom I've taken several ideas and code snippets, as well as some documenation tips.
- [Iron Summit Media](https://github.com/IronSummitMedia) and their project [Bootstrap Clean Blog](https://github.com/IronSummitMedia/startbootstrap-clean-blog), from which I've used some design ideas and some of the templating code for posts and pagination.

I'd also like to thank [Dr. Jekyll's Themes](http://drjekyllthemes.github.io/), [Jekyll Themes](http://jekyllthemes.org/), and another [Jekyll Themes](http://jekyllrc.github.io/jekyllthemes/) for featuring Beautiful Jekyll in their Jekyll theme directories.
