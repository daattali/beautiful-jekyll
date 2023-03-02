---
layout: page
title: Research Areas
subtitle:
---

Many of our research projects are in one of the following general themes:

# Deformable object manipulation

Deformable objects are challenging from both a perceptual and dynamic perspective: a crumpled cloth has many self-occlusions and its configuration is hard to infer from observations; further, the dynamics of a cloth are complex to model and incorporate into planning algorithms.  We develop algorithms to handle deformable object manipulation tasks, such as cloth, liquids, dough, and articulated objects.

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'deformable' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# 3D affordance reasoning for object manipulation

In order for a robot to interact with an object, the robot must infer its “affordances”: how the object moves as the robot interacts with it and how the object can interact with other objects in the environment. We develop robot perception algorithms that learn to estimate these affordances and then use such inferences to learn to manipulate objects to achieve a task.

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'affordance' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Multimodal learning

Robots should use all of the sensors available to them, such as depth, RGB, and tactile data.  We have developed methods to intelligently integrate these sensor modalities.

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'multimodal' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Reinforcement learning algorithms

Robots can use data, either from the real world or from a simulator, to learn how to perform a task.  This is especially important for tasks which are difficult for robots to achieve via traditional techniques such as motion planning, such as deformable object manipulation.  We have developed novel reinforcement learning algorithms to more effectively learn from data.

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'rl' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Autonomous driving

In the domain of autonomous driving, we have developed novel methods for every part of the perception pipeline: segmentation, object detection, tracking, and velocity estimation.  

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'autonomous-driving' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Active Perception

Rather than statically observing a scene, robots can take actions to enable them to better perceive a scene, known as “active perception.”

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'active-perception' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Self-Supervised Learning for Robotics

Rather than relying on hand-annotated data, self-supervised learning can enable robots to learn from large unlabeled datasets.

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'self-supervised' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>

# Previous Directions

## Object tracking

Tracking involves consistently locating an object as it moves across a scene, or consistently locating a point on an object as it moves.  In order to understand how robots should interact with objects, the robot must be able to track them as they change in position, viewpoint, lighting, occlusions, and other factors.  Improvements in this area should enable autonomous vehicles to interact more safely around dynamic objects (e.g. pedestrians, bicyclists, and other vehicles).

<details>
<summary style="display: list-item;"><b>Relevant Publications</b></summary>
<div>
    <table cellpadding="10" width="100%">
        {% assign pubs = site.data.pubs | where: 'tags', 'object-tracking' %}
        {% for pub in pubs %}
            {% include pub.html %}
        {% endfor %}
    </table>
    </div>
</details>