# Beautiful Jekyll

**Beautiful Jekyll** is a ready-to-use template to help you create an awesome website quickly. Perfect for personal blogs or simple project websites. → [demo](https://deanattali.com/beautiful-jekyll/)
 [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/daattali/20) [![Gem Version](https://badge.fury.io/rb/beautiful-jekyll-theme.svg)](https://badge.fury.io/rb/beautiful-jekyll-theme)

# Local Build Instructions

1. Install dependencies:

``` sh
gem install bundler
# Alternatively, brew install brew-gem; brew-gem install bundler
gem install jekyll
bundle install
```

2. Build:

```sh
bundle exec jekyll build && bundle exec jekyll serve --watch
```

# Default frontmatter

```yaml
---
layout: # page | post (writing/) | minimal
title:  # Page or blog post title
subtitle: # Short description of page or blog post that goes under the title
image: # /path/to/img
show-avatar:  #(false) | true
bigimg: # /path/to/img - or multiple entries <- "Path": "Description">
category: # category-name
tags: # [tag1, tag2, tag3]

# ---- Personal optional vars ---- #
# modified: # When this was last modified. Format "MMM dd YYYY" to match default styling.

# ---- Jekyll optional vars ---- #
# date: # overrides tha tage from the file name YYYY-MM-DD HH:MM:SS
# permalink: # (default /year/month/day/title.html)
# published: # (true) | false

# ---- Theme based optional vars ---- #
# comments: # (false) | true
# use-site-title: # (false) | true
# social-share: # If you don't want to show buttons to share a blog post on social media, use social-share: false (this feature is turned on by default).
---
```
