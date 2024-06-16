---
layout: page
title: Contact.
---
<header>
  <p>Feel free to reach out to me through any of the following methods:</p>
</header>

<div class="contact-container">
  <div class="contact-info">
    <p><strong>Email:</strong> <a href="mailto:micksoph@msu.edu">micksoph@msu.edu</a></p>
    <p><strong>Phone:</strong> (269) 635-0397</p>
  </div>

  <div class="contact-form">
    <form action="https://formspree.io/f/{your_form_id}" method="POST">
      <div>
        <div>
          <label for="name">Your Name:</label>
          <input type="text" id="name" name="name" required>
        </div>
        <div>
          <label for="email">Your Email:</label>
          <input type="email" id="email" name="email" required>
        </div>
      </div>
      <div>
        <label for="message">Your Message:</label>
        <textarea id="message" name="message" rows="5" required></textarea>
      </div>
      <button type="submit">Send</button>
    </form>
  </div>
</div>
