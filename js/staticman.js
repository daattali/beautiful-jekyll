---
layout: null
---

(function ($) {
  var $comments = $('.js-comments');

  $('#new_comment').submit(function () {
    var form = this;

    $(form).addClass('disabled');

    {% assign sm = site.staticman -%}
    var endpoint = '{{ sm.endpoint | default: "https://staticman3.herokuapp.com/v3/entry/github/" }}';
    var repository = '{{ sm.repository }}';
    var branch = '{{ sm.branch }}';

    $.ajax({
      type: $(this).attr('method'),
      url: endpoint + repository + '/' + branch + '/comments',
      data: $(this).serialize(),
      contentType: 'application/x-www-form-urlencoded',
      success: function (data) {
        $('#comment-form-submit').addClass('hidden');
        $('#comment-form-submitted').removeClass('hidden');
        $('.page__comments-form .js-notice').removeClass('notice--danger');
        $('.page__comments-form .js-notice').addClass('notice--success');
        showAlert('success');
      },
      error: function (err) {
        console.log(err);
        $('#comment-form-submitted').addClass('hidden');
        $('#comment-form-submit').removeClass('hidden');
        $('.page__comments-form .js-notice').removeClass('notice--success');
        $('.page__comments-form .js-notice').addClass('notice--danger');
        showAlert('failure');
        $(form).removeClass('disabled');
      }
    });

    return false;
  });

  function showAlert(message) {
    $('.page__comments-form .js-notice').removeClass('hidden');
    if (message == 'success') {
      $('.page__comments-form .js-notice-text-success').removeClass('hidden');
      $('.page__comments-form .js-notice-text-failure').addClass('hidden');
    } else {
      $('.page__comments-form .js-notice-text-success').addClass('hidden');
      $('.page__comments-form .js-notice-text-failure').removeClass('hidden');
    }
  }
})(jQuery);
