---
layout: page
title: Kontakt
subtitle: Jeśli masz do mnie pytanie to pytaj 
use-site-title: true
---
<meta name="referrer" content="origin" />
<main class="container">
  <header class="page-header">
  </header>
  <div class="contact">
      <div class="col-lg-6">
        <form method="POST" role="form" action="http://formspree.io/lukasz@zulnowski.com">
          <input type="hidden" name="_subject" value="Mail z me.zulnowski.com" />
          <input type="text" name="_gotcha" style="display:none" />
          <div class="form-group">
            <label for="InputName">Imię i Nazwisko</label>
            <input type="text" class="form-control" name="name" id="InputName" placeholder="Wprowadz Imię i Nazwisko" required>
          </div>
          <div class="form-group">
            <label for="InputEmail">Email</label>

            <input type="email" class="form-control" id="InputEmail" name="_replyto" placeholder="Wprowadź Email" required>
          </div>
          <div class="form-group">
            <label for="InputMessage">Wiadomość</label>

            <textarea name="InputMessage" id="InputMessage" class="form-control" rows="5" required></textarea>
          </div>
          <input type="submit" name="submit" id="submit" value="Wyślij" class="btn btn-info pull-right"> 
      </form>
    </div>
    <hr class="hidden-lg">
    </div>
</main>

