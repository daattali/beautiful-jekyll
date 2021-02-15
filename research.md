---
# layout: page
title: Research
# subtitle:
---
{% for post in site.posts limit:10 %}
  <item>
    <title>{{ post.title | xml_escape }}</title>
    <description>
      {% if post.subtitle %}{{ post.subtitle | xml_escape }} - {% endif %}
      {{ post.content | strip_html | xml_escape | truncatewords: excerpt_length }}
      </description>
      <pubDate>{{ post.date | date: "%a, %d %b %Y %H:%M:%S %z" }}</pubDate>
      <link>{{ post.url | absolute_url }}</link>
      <guid isPermaLink="true">{{ post.url | absolute_url }}</guid>
  </item>
 {% endfor %}

<!---
# ![ML to discover phase transitions](/assets/img/spin_extrapolation_prl.png){: style="float: right"}
# What if we could explore physical observables where data could not be aquired? 

# <img src="https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1">


# ## Potential energy surfaces with Gaussian Processes



# ## Inverse design of physical models
--->
