---
layout: page
title: Dealers & Artists
subtitle: Here are all of our dealers featured at this year's convention!
css:
    - "/assets/css/dealer-list.css"
    - "/assets/css/live_feed.css"
---

# Artist & Dealer Multi Stream
<div class="live-feed-container">
    <div class="feed-box">
        <div class="video-feed">
            <div class="video-box">
                <iframe
                    src="https://player.twitch.tv/?channel=fursquared&parent=fursquared.com&parent=dev.fursquared.com"
                    width="768"
                    height="432"
                    allowfullscreen="true">
                </iframe>
            </div>
        </div>

        <div class="chat-feed">
            <iframe src="https://titanembeds.com/embed/737134155028103238?defaultchannel=757326737280467006" frameborder="0"></iframe>
        </div>
    </div>
</div>

<br/>
<h2><a href="/dealer-onboard">Need to know how to join? Click here!</a></h2>
<br/>

{% assign dealers = site.data.dealers %}
{% assign alphabetical_dealers = dealers | sort: 'display_name' %}

<div class="dealer-list-container">
{% for dealer in alphabetical_dealers %}
    <div class="dealer-card-container">
        {% include dealer-card.html dealer=dealer %}
    </div>
{% endfor %}
</div>
