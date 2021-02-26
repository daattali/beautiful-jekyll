---
layout: page
title: Dealers
subtitle: Here are all of our dealers featured at this year's convention!
css:
    - "/assets/css/dealer-list.css"
---

<iframe
    src="https://player.twitch.tv/?channel=fursquared&parent=fursquared.com&parent=dev.fursquared.com"
    width="768"
    height="432"
    allowfullscreen="true">
</iframe>

<div class="chat-feed">
    <iframe src="https://titanembeds.com/embed/737134155028103238?defaultchannel=757326769308172309" frameborder="0"></iframe>
</div>

{% assign dealers = site.data.dealers %}
{% assign alphabetical_dealers = dealers | sort: 'display_name' %}

<div class="dealer-list-container">
{% for dealer in alphabetical_dealers %}
    <div class="dealer-card-container">
        {% include dealer-card.html dealer=dealer %}
    </div>
{% endfor %}
</div>
