// Dean Attali / Beautiful Jekyll 2016

(function() {
  var init = function() {
    initNavBar();
    initNavLinks();
    initImages();
  };

  var initNavBar = function() {
    // Shorten the navbar after scrolling a little bit down
    $(window).scroll(function() {
        if ($(".navbar").offset().top > 50) {
            $(".navbar").addClass("top-nav-short");
        } else {
            $(".navbar").removeClass("top-nav-short");
        }
    });

    // On mobile, hide the avatar when expanding the navbar menu
    $('#main-navbar').on('show.bs.collapse', function () {
      $(".navbar").addClass("top-nav-expanded");
    });
    $('#main-navbar').on('hidden.bs.collapse', function () {
      $(".navbar").removeClass("top-nav-expanded");
    });

    // On mobile, when clicking on a multi-level navbar menu, show the child links
    $('#main-navbar').on("click", ".navlinks-parent", function(e) {
      var target = e.target;
      $.each($(".navlinks-parent"), function(key, value) {
        if (value == target) {
          $(value).parent().toggleClass("show-children");
        } else {
          $(value).parent().removeClass("show-children");
        }
      });
    });
  };

  var initNavLinks = function() {
    // Ensure nested navbar menus are not longer than the menu header
    var menus = $(".navlinks-container");
    if (menus.length > 0) {
      var navbar = $("#main-navbar ul");
      var fakeMenuHtml = "<li class='fake-menu' style='display:none;'><a></a></li>";
      navbar.append(fakeMenuHtml);
      var fakeMenu = $(".fake-menu");

      $.each(menus, function(i) {
        var parent = $(menus[i]).find(".navlinks-parent");
        var children = $(menus[i]).find(".navlinks-children a");
        var words = [];
        $.each(children, function(idx, el) { words = words.concat($(el).text().trim().split(/\s+/)); });
        var maxwidth = 0;
        $.each(words, function(id, word) {
          fakeMenu.html("<a>" + word + "</a>");
          var width =  fakeMenu.width();
          if (width > maxwidth) {
            maxwidth = width;
          }
        });
        $(menus[i]).css('min-width', maxwidth + 'px')
      });

      fakeMenu.remove();
    }
  };

  var initImages = function() {
    var urls = ($("#header-big-imgs").attr('data-urls') || '');
    urls = urls.split(',');

    // NO URLS - bail
    if (!urls || !urls.length) {
      return;
    }

    var $bigImg = $(".intro-header.big-img");
    var currentIndex = -1;
    var nextImageMillis = 6000;

    var insertImg = function(url) {
      var $img = $('<div></div>')
        .addClass('big-img-transition')
        .addClass('fade-in')
        .css('background-image', 'url(' + url + ')');

      // add new image over the big img. we will remove it later
      $bigImg.prepend($img);

      return $img;
    };
    var removeImg = function($img) {
      $img.remove();
    };
    var breath = function(fn) {
      setTimeout(fn, 50);
    };
    var fadeInImage = function(url, callback) {
      var $img = insertImg(url);
      var imgTransitionMillis = 1000;

      // once the image has faded in remove it
      setTimeout(function() {
        // set the big image's url
        $bigImg.css("background-image", 'url(' + url + ')');

        // give some time for the background to render on the big image
        breath(function() {
          removeImg($img);
          callback();
        });

      }, imgTransitionMillis);
    };


    var nextImage = function() {
      currentIndex = (++currentIndex % urls.length);
      var url = urls[currentIndex]
      var img = new Image();
      img.src = url;
      img.onload = function() {
        // wait for image to pre load, then fade in the image.
        fadeInImage(url, function() {
          setTimeout(nextImage, nextImageMillis);
        });
      };
    };

    nextImage();
  };


  init();
}());
