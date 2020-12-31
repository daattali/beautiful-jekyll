---
title: "DSSE->Publications"
layout: publications 
excerpt: "DSSE -- Publications."
sitemap: false 
permalink: /publications/
---


<h1 style="font-family: 'Roboto', sans-serif; font-weight: 500; font-size: 32px;">Publications</h1>

(For a full list, please go to [DBLP](https://dblp.uni-trier.de/pid/33/8657.html)
or [Google Scholar](https://scholar.google.com/citations?hl=en&user=G88J0-EAAAAJ&view_op=list_works&sortby=pubdate))

<div class="row" style="margin-bottom: 0">
<div id="filterByYear" class="filters">
<!-- year button will be added dynamically-->
</div>
</div>

<div class="row">
<div id="filterByDomain" class="filters">
<!-- research domains will be added dynamically-->
{% for res_area in site.data.research_domains %}<button class="btn  filterBtn " id="{{res_area.domain_id}}">{{res_area.broad_domain_name}}</button>
{% endfor %}
</div>
</div>

<br>
<div id="publications_space">
{% for publi in site.data.publication_list %}
<div class="papers {{ publi.year }} {{ publi.domain_id }}">
<div class="col-sm-1" style="padding:0px">
  {% if publi.type == "Journal" %} 
  <div class="box" style="background-color: #C32B72;"></div>
  <p style="display:inline-block;">[Journal] </p>
  {% endif %}
  {% if publi.type == "Conference" %} 
  <div class="box" style="background-color: #196CA3;"></div>
  <p style="display:inline-block;">[Conf-{{publi.publication_no}}] </p>
  {% endif %}
  {% if publi.type == "Arxiv" %} 
  <div class="box" style="background-color: #606B70;"></div>
  <p style="display:inline-block;">[Arxiv] </p>
  {% endif %}
  {% if publi.type == "Editorship" %} 
  <div class="box" style="background-color: #33C3BA;"></div>
  <p style="display:inline-block;">[Editor] </p>
  {% endif %}
  {% if publi.type <> "Journal" and publi.type <> "Conference" and publi.type <> "Arxiv" and publi.type <> "Editorship" %} 
  <div class="box"></div>
  <p style="display:inline-block;">[Other] </p>
  {% endif %}
</div>
<div class="col-sm-11">
  <p>
  **{{ publi.title }}** <br/>
  <em>{{ publi.authors }} </em><br/>
  {{ publi.publisher }} ( {% if publi.pdf %} <a href="{{ publi.pdf }}" target="_blank">Paper PDF</a> {% endif %} {% if publi.pdf and publi.doi %} | {% endif %} {% if publi.doi %} <a href="{{ publi.doi }}" target="_blank">DOI</a> {% endif %} {% if publi.pdf and publi.code %} | {% endif %}  {% if publi.code %} <a href="{{ publi.code }}" target="_blank">Code</a> {% endif %} )
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
