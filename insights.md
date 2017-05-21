---
layout: page
title: Blue Zone IT
subtitle: Insights 
use-site-title: true
bigimg:
    - "https://c1.staticflickr.com/3/2889/12842840854_1021db97e6.jpg" : "The Thinking Bull, Barcelona, 2012"
    - "https://c1.staticflickr.com/4/3759/12843118594_b27583e3a7.jpg" : "Laborinth Park, Barcelona, 2012"
tag: random
---

 <article class="post-preview">
    <a href="/jlastwood.github.io/2015-02-26-GettingStarted/">
	  <h2 class="post-title">Ready to start your next project?</h2>
    </a>

    <div class="post-entry-container">
      <div class="post-entry">
        Getting your project underway is a big task.  Here is a checklist to get your started.
             
          <a href="/jlastwood.github.io/2015-02-26-GettingStarted/" class="post-read-more">[Read&nbsp;More]</a>
        
      </div>
    </div>

   </article>
 
## Other Project Management News

{% for post in site.tags.tools  %}
  * {{ post.date | date_to_string }} &raquo; [ {{ post.title }} ]({{ post.url }})
{% endfor %}
