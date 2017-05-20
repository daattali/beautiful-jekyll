---
layout: page
title: Blue Zone IT
subtitle: Insights 
use-site-title: true
bigimg:
    - "/img/big-imgs/dragons.jpg" : "Sant Jordi, 2017"
    - "/img/big-imgs/penguin.jpg" : "Beaches, 2017"
    - "/img/big-imgs/flowers.jpg" : "Flowers, 2017"
tag: random
---


## Featured Article

 <article class="post-preview">
    <a href="/jlastwood.github.io/2015-02-26-flake-it-till-you-make-it/">
	  <h2 class="post-title">Flake it till you make it</h2>
    </a>

    <div class="post-entry-container">
      <div class="post-entry">
        Under what circumstances should we step off a path? When is it essential that we finish what we start? If I bought a bag of peanuts and had an allergic reaction, no one would fault me if I threw it out. If I ended a relationship with a woman who...
        
        
          <a href="/jlastwood.github.io/2015-02-26-flake-it-till-you-make-it/" class="post-read-more">[Read&nbsp;More]</a>
        
      </div>
    </div>

   </article>
 
## Other News

{% for post in site.posts  %}
  * {{ post.date | date_to_string }} &raquo; [ {{ post.title }} ]({{ post.url }})
{% endfor %}
