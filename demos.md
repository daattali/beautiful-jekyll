---
layout: page
title: Robot Demos
subtitle:
---

<div style='margin-bottom: 10px'>This page is under construction, more video demos will be added shortly.</div>

<table>
{% assign sorted = site.data.pubs | sort: 'date' | reverse %}
{% for pub in sorted %}
  {% if pub.video_embed %}
    <tr>
      <td><a href="{{ pub.arxiv_url }}">{{ pub.title }}</a><br>
        <div class="pubauthor">
          {{ pub.authors }}<br>
        </div>
        <div class="pubjournal">
          {{ pub.venue }}
        </div>
        <div id="bib{{ pub.short_id }}" style="display:none">
          <blockquote>
            <pre>{{pub.bibtex}}</pre>
          </blockquote>
        </div>
        <div id="abs{{ pub.short_id }}" style="display:none">
          <blockquote>
            {{pub.abstract}}
          </blockquote>
        </div>
        <div style="font-size:small">
          <a href="{{ pub.site }}">[Project Page]</a>
          <!-- <a href="">[Code]</a> -->
          <a href="javascript:copy(div{{ pub.short_id }}, bib{{ pub.short_id }})">[Bibtex]</a>
          <a href="javascript:copy(div{{ pub.short_id }}, abs{{ pub.short_id}})">[Abstract]</a>
          <a href="{{ pub.pdf }}">[PDF]</a>
        </div>
        <div id="div{{ pub.short_id }}" class="pubInfo"></div>
        <div class='video_embed'>
          {{ pub.video_embed }}
        </div>
      </td>
    </tr>
  {% endif %}
{% endfor %}
</table>
