(function( $, window, undefined ) {
  // Menu
  $("#menu").click(function() {
    $("body").addClass("push-menu-to-right");
    $("#sidebar").addClass("open");
    $(".overlay").addClass("show");
  });

  $("#mask").click(function() {
    $("body").removeClass("push-menu-to-right");
    $("#sidebar").removeClass("open");
    $(".overlay").removeClass("show");
  });

  // Header
  $(window).scroll(function () {
    var top = $(this).scrollTop();
    if (top > 0) {
      $("body").addClass("light");
    }
    else {
      $("body").removeClass("light");
    }
  });

  // Modals

  var $closeBtn = $('.modal .close');
  $closeBtn.on('click', function() {
      $closeBtn.parent().parent().addClass('closed');
  });

  var $exitModal = $('.modal.exit');
  if ($exitModal.length) {
    ouibounce($exitModal[0], {
      aggressive: true,
      callback: function() {
        $exitModal.find('.close').on('click', function() {
          $exitModal.hide();
        });
      }
    });
  }

  // Search
  var bs = {
    close: $(".icon-remove-sign"),
    searchform: $(".search-form"),
    canvas: $("body"),
    dothis: $('.dosearch')
  };

  bs.dothis.on('click', function() {
    $('.search-wrapper').toggleClass('active');
    bs.searchform.toggleClass('active');
    bs.searchform.find('input').focus();
    bs.canvas.toggleClass('search-overlay');
    $('.search-field').simpleJekyllSearch();
  });

  function close_search() {
    $('.search-wrapper').toggleClass('active');
    bs.searchform.toggleClass('active');
    bs.canvas.removeClass('search-overlay');
  }

  bs.close.on('click', close_search);

  // Closing menu with ESC
  document.addEventListener('keyup', function(e){
      if(e.keyCode == 27 && $('.search-overlay').length) {
          close_search();
      }
  });
  
  if (document.getElementsByClassName('home').length >=1 ) {
      new AnimOnScroll( document.getElementById( 'grid' ), {
        minDuration : 0.4,
        maxDuration : 0.7,
        viewportFactor : 0.2
      });
  }

  // Init smooth scroll
  smoothScroll.init({
      selectorHeader: '.bar-header', // Selector for fixed headers (must be a valid CSS selector)
      speed: 500, // Integer. How fast to complete the scroll in milliseconds
      updateURL: false // Boolean. Whether or not to update the URL with the anchor hash on scroll
  });

})( Zepto, window );
