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
