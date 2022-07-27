---
layout: page
title: Robot Demos
subtitle:
projects:
  - title: Multi-Modal Transfer Learning for Grasping Transparent and Specular Objects
    arxiv_url: https://arxiv.org/abs/2006.00028
    pdf: https://arxiv.org/pdf/2006.00028.pdf
    site: https://sites.google.com/view/transparent-specular-grasping/home
    code: 
    authors: Thomas Weng, Amith Pallankize, Yimin Tang, Oliver Kroemer, David Held
    venue: Robotics and Automation Letters (RA-L) with presentation at the International Conference of Robotics and Automation (ICRA), 2020
    short_id: weng2020ral
    bibtex: "@ARTICLE{9001238, \n
      author={Thomas Weng and Amith Pallankize and Yimin Tang and Oliver Kroemer and David Held}, \n
      journal={IEEE Robotics and Automation Letters}, \n
      title={Multi-Modal Transfer Learning for Grasping Transparent and Specular Objects}, \n
      year={2020}, \n
      volume={5}, \n
      number={3}, \n
      pages={3791-3798}, \n
      doi={10.1109/LRA.2020.2974686}}"
    abstract: 
      "State-of-the-art object grasping methods rely on depth sensing to plan robust grasps, but commercially available depth sensors fail to detect transparent and specular objects. To improve grasping performance on such objects, we introduce a method for learning a multi-modal perception model by bootstrapping from an existing uni-modal model. This transfer learning approach requires only a pre-existing uni-modal grasping model and paired multi-modal image data for training, foregoing the need for ground-truth grasp success labels nor real grasp attempts. Our experiments demonstrate that our approach is able to reliably grasp transparent and reflective objects. Video and supplementary material are available at <a href=\"https://sites.google.com/view/transparent-specular-grasping\">https://sites.google.com/view/transparent-specular-grasping</a>."
    video_embed: 
      <iframe width="560" height="315" src="https://www.youtube.com/embed/rYRPWe0xLVo" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
---

<table>
{% for project in page.projects %}
  <tr>  
    <td><a href="{{ project.arxiv_url }}">{{ project.title }}</a><br>
      <div class="pubauthor">
        {{ project.authors }}<br>
      </div>
      <div class="pubjournal">
        {{ project.venue }}
      </div>
      <div id="bib{{ project.short_id }}" style="display:none">
        <blockquote>
          <pre>{{project.bibtex}}</pre>
        </blockquote>
        </div>
        <div id="abs{{ project.short_id }}" style="display:none">
          <blockquote>
            {{project.abstract}}
          </blockquote>
        </div>
        <div style="font-size:small">
          <a href="{{ project.site }}">[Project Page]</a>
          <!-- <a href="">[Code]</a> -->
          <a href="javascript:copy(div{{ project.short_id }}, bib{{ project.short_id }})">[Bibtex]</a>
          <a href="javascript:copy(div{{ project.short_id }}, abs{{ project.short_id}})">[Abstract]</a>
          <a href="{{ project.pdf }}">[PDF]</a>
        </div>
        <div id="div{{ project.short_id }}" class="pubInfo"></div>
        <div class='video_embed'>
          {{ project.video_embed }}
        </div>
      </td>
    </tr>
{% endfor %}
</table>