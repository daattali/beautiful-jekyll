---
layout: page
title: Research Areas
subtitle:
---

Many of our research projects are in one of the following general themes. Note that this page is still being updated to include [all publications](../publications). 

<div>
{% for area in site.data.areas %}
    {% include area.html %}
{% endfor %}
</div>

# Previous Directions

## Object tracking

Tracking involves consistently locating an object as it moves across a scene, or consistently locating a point on an object as it moves.  In order to understand how robots should interact with objects, the robot must be able to track them as they change in position, viewpoint, lighting, occlusions, and other factors.  Improvements in this area should enable autonomous vehicles to interact more safely around dynamic objects (e.g. pedestrians, bicyclists, and other vehicles).

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'tracking' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>