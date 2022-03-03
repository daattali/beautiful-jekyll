---
layout: page
permalink: /Research/
title: Research
show-avatar: true
display_categories: [work]
---

<div align="center"><img src="/assets/img/output-onlinegiftools(14).gif" width="200"/><br /><a href="https://www.deformetrica.org/"> 
    <img src="https://img.shields.io/badge/Made with Deformetrica-656262.svg" width="110"/></a><img src="/assets/img/deformetrica.png" alt="drawing" width="30"/></div>

### Journal articles
<b>Analysis of the Anatomical Variability of Fetal Brains with Corpus Callosum Agenesis</b><br>
     <font size="3"> Fleur Gaudfernau, Eleonore Blondiaux, Stéphanie Allassonniere</font><br>
      <a href="https://hal.archives-ouvertes.fr/hal-03546165v1/"> <img src="https://img.shields.io/badge/Read on HAL-ff5e3b.svg" /> </a> <img src="https://img.shields.io/badge/Preprint-F4BB44.svg" width="60" height="20"> 

<b>Characteristics associated with feeding organic foods during complementary feeding: the nationwide Étude Longitudinale Française depuis l’Enfance (ELFE) birth cohort<br></b>
     <font size="3"> Blandine de Lauzon-Guillain, Fleur Gaudfernau, Aurore Camier, Camille Davisse-Paturet, Sandrine Lioret, Sophie Nicklaus, Marie-Aline Charles, Emmanuelle Kesse-Guyot<br>
     British Journal of Nutrition, Cambridge University Press (CUP), 2021, 126 (8), pp.1215-1224.</font><br>
     [![DOI:10.1017/S0007114520005097](https://zenodo.org/badge/DOI/10.1017/S0007114520005097.svg)](https://doi.org/10.1017/S0007114520005097)
    
<hr style="border:1px solid #2b6777"/>

### Conference articles

<b>Analysis of the Anatomical Variability of Fetal Brains with Corpus Callosum Agenesis</b><br>
     <font size="3"> Fleur Gaudfernau, Eleonore Blondiaux, Stéphanie Allassonniere <br>
     MICCAI 2021 – Perinatal, Preterm and Paediatric Image Analysis Workshop, Oct 2021, Strasbourg.</font><br>
     [![DOI:10.1007/978-3-030-87735-4_26](https://zenodo.org/badge/DOI/10.1007/978-3-319-76207-4_15.svg?colorB=7289da)](https://doi.org/10.1007/978-3-030-87735-4_26)   

<hr style="border:1px solid #2b6777"/>

#### Talks
<dl>
<dt>
    <img src="https://img.shields.io/badge/Oct. 2021-00a19e.svg"></dt>
    
<dd>  Talk at the MICCAI-PIPPI (Perinatal, Preterm and Paedriatric Image Analysis) workshop  <a href="https://pippiworkshop.github.io/"> <img src="/assets/img/PIPPI-Logo2021.png" alt="drawing" width="110"/> </a> <br> <a href="/assets/img/zoom_4.mp4"> <img src="https://img.shields.io/badge/Link to my presentation-a18aab.svg" /> </a> </dd>
    </dl>
    
<hr style="border:1px solid #2b6777"/>

### Awards
    
<dl>
<dt>
    <img  src="https://img.shields.io/badge/Oct. 2021-00a19e.svg"/></dt>
<dd> MICCAI-PIPPI workshop Best Paper Award
 <a href="/assets/img/PIPPI2021_Best_Presentation.png">
    <img src="/assets/img/PIPPI2021_Best_Presentation.png" 
        alt="PIPPI2021_Best_Presentation"
        width="100">
</a> </dd>
    </dl>
 
<hr style="border:1px solid #2b6777"/>

### Code

Upcoming.

<div class="projects">
  {% if site.enable_project_categories and page.display_categories %}
  <!-- Display categorized projects -->
    {% for category in page.display_categories %}
      {% assign categorized_projects = site.projects | where: "category", category %}
      {% assign sorted_projects = categorized_projects | sort: "importance" %}
      <!-- Generate cards for each project -->
      {% if page.horizontal %}
        <div class="container">
          <div class="row row-cols-2">
          {% for project in sorted_projects %}
            {% include projects_horizontal.html %}
          {% endfor %}
          </div>
        </div>
      {% else %}
        <div class="grid">
          {% for project in sorted_projects %}
            {% include projects.html %}
          {% endfor %}
        </div>
      {% endif %}
    {% endfor %}

  {% else %}
  <!-- Display projects without categories -->
    {% assign sorted_projects = site.projects | sort: "importance" %}
    <!-- Generate cards for each project -->
    {% if page.horizontal %}
      <div class="container">
        <div class="row row-cols-2">
        {% for project in sorted_projects %}
          {% include projects_hrz.html %}
        {% endfor %}
        </div>
      </div>
    {% else %}
      <div class="grid">
        {% for project in sorted_projects %}
          {% include projects.html %}
        {% endfor %}
      </div>
    {% endif %}

  {% endif %}

</div>
