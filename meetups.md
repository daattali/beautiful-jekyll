---
layout: page
title: MeetUps
subtitle: I've attended
published: true
---

This page is automatically updated with every meetup I assist.

{% for meetup in site.data.meetups.rows -%}
{% if meetup.event -%}
------
**{{ meetup.event }}**: {{ meetup.description }} 

{% endif %}
{%- endfor -%}
