---
title: "DSSE->Photos"
layout: piclay 
excerpt: "DSSE -- Photos"
permalink: /photos/
---

<h1 style="font-family: 'Roboto', sans-serif; font-weight: 500; font-size: 32px;">Group Meetup and Moments</h1>

{% assign number_printed = 0 %} {% for pic in site.data.photos %}

{% assign even_odd = number_printed | modulo: 4 %}

{% if even_odd == 0 %}
<div class="row">
{% endif %}

<div class="col-sm-6 clearfix">
<img  src="{{ site.url }}{{ site.baseurl }}/images/dsse-group-pic/{{ pic.image }}" class="img-responsive" width="95%" style="float: left" />
<!-- <a>{{pic.title}}</a> -->
<!-- The Modal -->
</div>

{% assign number_printed = number_printed | plus: 1 %}

{% if even_odd > 2 %}
</div>
{% endif %}


{% endfor %}

{% assign even_odd = number_printed | modulo: 4 %} {% if even_odd == 1 %}
</div>
{% endif %}

{% if even_odd == 2 %}
</div>
{% endif %}

{% if even_odd == 3 %}
</div>
{% endif %}

<p> &nbsp; </p>