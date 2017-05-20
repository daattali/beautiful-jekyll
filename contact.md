---
layout: page
title: Blue Zone IT
subtitle: How Can We Help You? 
---

### Services

- Project Management
- Talent Acquisition
- Editing/Proofreading
- Business Process Consulting

<form id="contactform" method="POST">

<input type="text" name="name" cols="30" placeholder="Name"> 
<br>
<input type="email" name="_replyto" cols="30" placeholder="Email"> 
<br>
<textarea name="message" placeholder="Message" cols="30"></textarea> 
<input type="text" name="_gotcha" style="display:none" />
<input type="hidden" name="_subject" value="Website contact" />
<br>
<input type="submit" value="Send">:
</form>

<script>
    var contactform =  document.getElementById('contactform');
    contactform.setAttribute('action', '//formspree.io/' + 'jlastwood' + '@' + 'gmail' + '.' + 'com');
</script>

<div class="home">
  <section class="banner">
    <div class="wrapper">
      <h1>Open Data Handbook</h1>
      <p>{{ site.description }}</p>
    </div>
  </section>

  <div class="wrapper">

      <div>
        <h2>Open Data Guide</h2>
        <p>This guide discusses the legal, social and technical aspects of open data. It can be used by anyone but is especially designed for those seeking to open up data. It discusses why to go open, what open is, and the how to 'open' data.</p>
        <a href="{{ site.baseurl | append: 'guide/'| append: page.lang | append: '/'}}">Start Reading</a>
      </div>

      <div>
        <div>
          <h2>Value Stories</h2>
          <p>Use cases, stories and case studies highlighting the social and economic value, the impact and the varied applications of open data from cities and countries across the globe.</p>
          <a href="{{ site.baseurl | append: 'value-stories/' | append: page.lang | append: '/' }}">Value Stories</a>
       </div>
      </div>
      <div>
        <div>
          <h2>Resource Library</h2>
          <p>A curated collection of open data resources, including articles, longer publications, how to guides, presentations and videos, produced by the global open data community.</p>
          <a href="{{ site.baseurl | append: 'resources/' }}">Open Data Resources</a>
        </div>
      </div>

  </div>
</div>
