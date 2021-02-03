---
title: "DSSE->Events"
layout: default 
excerpt: "DSSE -- Events."
sitemap: false 
permalink: /events/
---


<h1 style="font-family: 'Roboto', sans-serif; font-weight: 500; font-size: 32px;">Events</h1>

<div class="row" style="margin-bottom: 0">
<div id="filterEventByYear" class="filters">
<!-- year button will be added dynamically-->
</div>
</div>

<!-- <div class="row">
<div id="filterByEventDomain" class="filters">
{% for event_type in site.data.event_types %}
<button class="btn  filterBtn " id="{{event_type.type_id}}">{{event_type.broad_event_name}}</button>
{% endfor %}
</div>
</div>
 -->
<br>
<div id="events_space">
{% for event in site.data.event_list %}
<div class="events {{ event.year }} {{ event.type_id }}">
<div class="col-sm-2" style="padding:0px">
  {% if event.type == "Workshop" %} 
  <div class="box" style="background-color: #C32B72;"></div>
  <p style="display:inline-block;">[Workshop] </p>
  {% endif %}
  {% if event.type <> "Workshop" %} 
  <div class="box"></div>
  <p style="display:inline-block;">[Other] </p>
  {% endif %}
</div>
<div class="col-sm-10">
  <p>
  **{{ event.title }}** <br/>
  <em>{{ event.authors }} </em><br/>
  {{ event.booktitle }} <b>[{{event.year}}]</b> <br>
  <a href="{{ event.register_link }}" target="_blank">Register</a>
  {% if event.detail_page %} | 
    {% for page in site.posts %} {% if page.path contains '/event/' %} <a href="{{ page.url | absolute_url }}" target="_blank">detail</a>

        {% if page.url == event.detail_page %}[Detail]({{ page.url }}){% endif %}
     {% endif %} 

    {% endfor %}
  {% endif %} 
  {% if event.pdf and event.doi %} | {% endif %}  
  {% if event.pdf %} <a href="{{ event.pdf }}" target="_blank">Paper PDF</a> {% endif %} {% if event.pdf and event.doi %} | {% endif %} {% if event.doi %} <a href="{{ event.doi }}" target="_blank">DOI</a> {% endif %} {% if event.pdf and event.code_link %} | {% endif %}  {% if event.code_link %} <a href="{{ event.code_link }}" target="_blank">Code</a> {% endif %}
  </p>
</div>
</div>
{% endfor %}
</div>

<br><br>
<style>
.container {
  height: 200px;
  position: relative;
  border: 3px solid green;
}

.vertical-center {
  margin: 0;
  position: absolute;
  top: 50%;
  -ms-transform: translateY(-50%);
  transform: translateY(-50%);
}

.box {
  display:inline-block;
  width:8px;
  height:8px;
  background-color: grey;
  margin-right:6px;
}
</style>
<br><br>
