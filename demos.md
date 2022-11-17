---
layout: page
title: Robot Demos
subtitle:
---

<table>
{% for pub in site.data.pubs %}
  {% if pub.video_embed %}
    <tr>
      <td><a href="{{ pub.arxiv_url }}">{{ pub.title }}</a><br>
        <div class="pubauthor">
          {{ pub.authors }}<br>
        </div>
        <div class="pubjournal">
          {{ pub.venue }}
        </div>
        <div id="bib{{pub.short_id}}" style="display:none">
            <blockquote>
                <pre>
                    {{pub.bib}}
                </pre>
            </blockquote>
        </div>
        <div id="abs{{pub.short_id}}" style="display:none">
            <blockquote>
                {{pub.abs}}
            </blockquote>
        </div>
        <div style="font-size:small">
          {% if pub.site != null %}
              <a href="{{pub.site}}">[Project Page]</a>
          {% endif %}
          {% if pub.bib != null %}
              <a href="javascript:copy(div{{pub.short_id}}, bib{{pub.short_id}})">[Bibtex]</a>
          {% endif %}
          {% if pub.abs != null %}
              <a href="javascript:copy(div{{pub.short_id}}, abs{{pub.short_id}})">[Abstract]</a>
          {% endif %}
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
