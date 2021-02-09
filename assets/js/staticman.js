---
layout: null
---

(function ($) {
  var $comments = $('.js-comments');

  $('#new_comment').submit(function () {
    var form = this;

    $(form).addClass('disabled');

    {% assign sm = site.staticman -%}
    var endpoint = '{{ sm.endpoint }}';
    var repository = '{{ sm.repository }}';
    var branch = '{{ sm.branch }}';
    let url = endpoint + repository + '/' + branch + '/comments';
    let data = $(this).serialize();

    fetch(url, {
      method: "POST",
      body: data,
      headers: {
        "Content-Type": "application/x-www-form-urlencoded"
      }
    }).then(function(res) {
      if (res.ok) {
        formSubmitted();
      } else {
        formError();
      }
    }).catch(function(error) {
      formError();
      console.log(error);
    });

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
