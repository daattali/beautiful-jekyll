---
layout: null
---

(function ($) {
  $('#new_comment').submit(function () {
    const form = this;

    $(form).addClass('disabled');

    {% assign sm = site.staticman -%}
    const endpoint = '{{ sm.endpoint }}';
    const repository = '{{ sm.repository }}';
    const branch = '{{ sm.branch }}';
    const url = endpoint + repository + '/' + branch + '/comments';
    const data = $(this).serialize();

    const xhr = new XMLHttpRequest();
    xhr.open("POST", url);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
    xhr.onreadystatechange = function () {
      if(xhr.readyState === XMLHttpRequest.DONE) {
        const status = xhr.status;
        if (status >= 200 && status < 400) {
          formSubmitted();
        } else {
          formError();
        }
      }
    };

    function formSubmitted() {
      $('#comment-form-submit').addClass('d-none');
      $('#comment-form-submitted').removeClass('d-none');
      $('.page__comments-form .js-notice').removeClass('alert-danger');
      $('.page__comments-form .js-notice').addClass('alert-success');
      showAlert('success');
    }

    function formError() {
      $('#comment-form-submitted').addClass('d-none');
      $('#comment-form-submit').removeClass('d-none');
      $('.page__comments-form .js-notice').removeClass('alert-success');
      $('.page__comments-form .js-notice').addClass('alert-danger');
      showAlert('failure');
      $(form).removeClass('disabled');
    }

    xhr.send(data);

    return false;
  });

  function showAlert(message) {
    $('.page__comments-form .js-notice').removeClass('d-none');
    if (message == 'success') {
      $('.page__comments-form .js-notice-text-success').removeClass('d-none');
      $('.page__comments-form .js-notice-text-failure').addClass('d-none');
    } else {
      $('.page__comments-form .js-notice-text-success').addClass('d-none');
      $('.page__comments-form .js-notice-text-failure').removeClass('d-none');
    }
  }
})(jQuery);
