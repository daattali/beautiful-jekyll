---
title: "DSSE->Members"
layout: gridlay
excerpt: "DSSE -- Members"
sitemap: false
permalink: /members/
---

<h1 style="font-family: 'Roboto', sans-serif; font-weight: 500; font-size: 32px;">Group Members</h1>

## Head of The DSSE Research Group 

<div class="row">
  <div class="col-sm-3 clearfix">
  <img src="{{ site.url }}{{ site.baseurl }}/images/group-members/current_members/Kazi_Muheymin_Us_Sakib.jpg" class="img-responsive" width="80%" style="float: center" />
  <br>
  <h4><a href="http://www.iit.du.ac.bd/about_iit/individual_teacher/47">Dr. Kazi Muheymin-Us-Sakib</a></h4>
  Professor<br>
  <i><sakib@iit.du.ac.bd></i><br>
  BSc(DU), MSc(DU) and PhD(RMIT)
  </div>
  <div class="col-sm-9"> 
  <p>David Lo is an ACM Distinguished Member (Scientist) and Associate Professor of Information Systems at Singapore Management University, leading the Software Analytics Research (SOAR) group. His research interest is in the intersection of software engineering and data science, encompassing socio-technical aspects and analysis of different kinds of software artefacts, with the goal of improving software quality and developer productivity. His work has been published in major and premier conferences and journals in the area of software engineering, AI, and cybersecurity attracting substantial interest from the community. He has won more than 10 international research and service awards including 6 ACM SIGSOFT Distinguished Paper awards. His work has been supported by NRF, MOE, NCR, AI Singapore, and several international research projects. He has served in more than 30 organizing committees and numerous program committees of research conferences including serving as general or program co-chairs of ASE 2020, SANER 2019, ICSME 2018, ICPC 2017, and ASE 2016. He is also serving in the editorial board of IEEE Transactions on Software Engineering, Empirical Software Engineering, IEEE Transactions on Reliability, Journal of Software: Evolution and Process, Information and Software Technology, Information Systems, and Neurocomputing (Software Section). His former PhD students have secured faculty positions (University of Melbourne, Australia; Queen’s University, Canada; Mississippi State University, USA; ITTelkom Surabaya, Indonesia) and employment at high-tech industries (Microsoft, Canada; Schroder Investment Management, Luxembourg; Hudson River Trading, Singapore; Veracode, Singapore) around the globe.</p> </div>
</div>

<!-- Jump to [Research Staff and PhD Students](#research-staff-and-phd-students), [Master and Bachelor Students](#master-and-bachelor-students), [Alumni](#alumni), [administrative support](#administrative-support), [lab visitors](#lab-visitors). -->


## Current Members

{% assign number_printed = 0 %}
{% for member in site.data.members %}

{% assign even_odd = number_printed | modulo: 2 %}

{% if even_odd == 0 %}
<div class="row">
{% endif %}

<div class="col-sm-6 clearfix">
  <img src="{{ site.url }}{{ site.baseurl }}/images/group-members/current_members/{{ member.photo }}"  width="128px" height="128px" style="float: left" />
  <h4><a href="{{ member.homepage }}" target="_blank">{{ member.name }}</a></h4>
  <i>{{ member.info }}<br>email: <{{ member.email }}></i>
  <ul style="overflow: hidden">

  {% if member.number_educ == 1 %}
  <li> {{ member.education1 }} </li>
  {% endif %}

  {% if member.number_educ == 2 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  {% endif %}

  {% if member.number_educ == 3 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  {% endif %}

  {% if member.number_educ == 4 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  <li> {{ member.education4 }} </li>
  {% endif %}

  {% if member.number_educ == 5 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  <li> {{ member.education4 }} </li>
  <li> {{ member.education5 }} </li>
  {% endif %}

  </ul>
</div>

{% assign number_printed = number_printed | plus: 1 %}

{% if even_odd == 1 %}
</div>
{% endif %}

{% endfor %}

{% assign even_odd = number_printed | modulo: 2 %}
{% if even_odd == 1 %}
</div>
{% endif %}

## Alumni

{% assign number_printed = 0 %}
{% for member in site.data.alumni %}

{% assign even_odd = number_printed | modulo: 2 %}

{% if even_odd == 0 %}
<div class="row">
{% endif %}

<div class="col-sm-6 clearfix">
  <img src="{{ site.url }}{{ site.baseurl }}/images/group-members/alumni/{{ member.photo }}" class="img-responsive" width="25%" style="float: left" />
  <h4><a href="{{ member.homepage }}" target="_blank">{{ member.name }}</a></h4>
  <i>{{ member.info }}<br>email: <{{ member.email }}></i>
  <ul style="overflow: hidden">

  {% if member.number_educ == 1 %}
  <li> {{ member.education1 }} </li>
  {% endif %}

  {% if member.number_educ == 2 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  {% endif %}

  {% if member.number_educ == 3 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  {% endif %}

  {% if member.number_educ == 4 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  <li> {{ member.education4 }} </li>
  {% endif %}

  {% if member.number_educ == 5 %}
  <li> {{ member.education1 }} </li>
  <li> {{ member.education2 }} </li>
  <li> {{ member.education3 }} </li>
  <li> {{ member.education4 }} </li>
  <li> {{ member.education5 }} </li>
  {% endif %}

  </ul>
</div>

{% assign number_printed = number_printed | plus: 1 %}

{% if even_odd == 1 %}
</div>
{% endif %}

{% endfor %}

{% assign even_odd = number_printed | modulo: 2 %}
{% if even_odd == 1 %}
</div>
{% endif %}


## Administrative Support
If you need to update your information, feel free to contact <a href="bsse0516@iit.du.ac.bd">Md Rakib Hossain (Misu)</a>.
<br>
<br>
<br>
<style>
  @media (max-width: 420px) {.fa-ul::before{content: "\A";white-space: pre;}}
</style>