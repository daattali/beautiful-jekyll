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
  <p>Summary</p> </div>
</div>

<!-- Jump to [Research Staff and PhD Students](#research-staff-and-phd-students), [Master and Bachelor Students](#master-and-bachelor-students), [Alumni](#alumni), [administrative support](#administrative-support), [lab visitors](#lab-visitors). -->


## Members
{% assign number_printed = 0 %}
{% for member in site.data.members %}

{% assign even_odd = number_printed | modulo: 2 %}

{% if even_odd == 0 %}
<div class="row">
{% endif %}

<div class="col-sm-6 clearfix">

  {% if member.photo%}
  <img src="{{ site.url }}{{ site.baseurl }}/images/group-members/current_members/{{ member.photo }}" class="img-responsive" width="30%" style="float: left" />
  {% endif %}


  <h4>{{ member.name }}</h4>
  {{ member.info }}<br>
  <i>{{ member.email }}</i>
  
  <ul class="fa-ul">

  {% if member.number_educ == 1 %}
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education1 }} </li>
  {% endif %}

  {% if member.number_educ == 2 %}
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education1 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education2 }} </li>
  {% endif %}

  {% if member.number_educ == 3 %}
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education1 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education2 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education3 }} </li>
  {% endif %}

  {% if member.number_educ == 4 %}
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education1 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education2 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education3 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education4 }} </li>
  {% endif %}

  {% if member.number_educ == 5 %}
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education1 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education2 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education3 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education4 }} </li>
    <li><img class="fa-li"><i class='fas fa-graduation-cap' style='font-size:13px;color:black'></i> {{ member.education5 }} </li>
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

## Current Members

## Alumni

## Administrative Support
If you need to update your information, feel free to contact <a href="bsse0516@iit.du.ac.bd">Md Rakib Hossain (Misu)</a>.
<br>
<br>
<br>
<style>
  @media (max-width: 420px) {.fa-ul::before{content: "\A";white-space: pre;}}
</style>