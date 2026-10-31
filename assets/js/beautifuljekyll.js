// Dean Attali / Beautiful Jekyll 2023

let BeautifulJekyllJS = {

  bigImgEl : null,
  numImgs : null,
  themeMedia : null,

  init : function() {
    setTimeout(BeautifulJekyllJS.initNavbar, 10);

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

    // On mobile, collapse the navbar after selecting a menu item
    $('#main-navbar a:not(.dropdown-toggle)').click(function() {
      $('#main-navbar').collapse('hide');
    });

    // show the big header image
    BeautifulJekyllJS.initImgs();

    BeautifulJekyllJS.initSearch();
    BeautifulJekyllJS.initThemeToggle();
  },

  initThemeToggle : function() {
    const toggle = document.getElementById('theme-toggle');
    if (!toggle) {
      return;
    }

    BeautifulJekyllJS.themeMedia = window.matchMedia
      ? window.matchMedia('(prefers-color-scheme: dark)')
      : null;

    const getSavedTheme = function() {
      try {
        const theme = localStorage.getItem('site-theme');
        return theme === 'light' || theme === 'dark' ? theme : null;
      } catch (error) {
        return null;
      }
    };

    const applyTheme = function(theme) {
      const isDark = theme === 'dark';
      document.documentElement.setAttribute('data-theme', isDark ? 'dark' : 'light');
      toggle.setAttribute('aria-pressed', String(isDark));
      toggle.setAttribute('aria-label', isDark ? 'Switch to light mode' : 'Switch to dark mode');
      toggle.title = isDark ? 'Switch to light mode' : 'Switch to dark mode';
      toggle.querySelector('i').className = isDark
        ? 'fa-solid fa-sun'
        : 'fa-solid fa-moon';
      toggle.querySelector('span').textContent = isDark ? 'Light mode' : 'Dark mode';
    };

    const applyPreferredTheme = function() {
      const savedTheme = getSavedTheme();
      applyTheme(savedTheme || (BeautifulJekyllJS.themeMedia && BeautifulJekyllJS.themeMedia.matches
        ? 'dark'
        : 'light'));
    };

    toggle.addEventListener('click', function() {
      const nextTheme = document.documentElement.getAttribute('data-theme') === 'dark'
        ? 'light'
        : 'dark';
      applyTheme(nextTheme);
      try {
        localStorage.setItem('site-theme', nextTheme);
      } catch (error) {
        // The current page still changes theme when storage is disabled.
      }
    });

    if (BeautifulJekyllJS.themeMedia) {
      const handleSystemThemeChange = function() {
        if (!getSavedTheme()) {
          applyPreferredTheme();
        }
      };
      if (BeautifulJekyllJS.themeMedia.addEventListener) {
        BeautifulJekyllJS.themeMedia.addEventListener('change', handleSystemThemeChange);
      } else if (BeautifulJekyllJS.themeMedia.addListener) {
        BeautifulJekyllJS.themeMedia.addListener(handleSystemThemeChange);
      }
    }

    window.addEventListener('storage', function(event) {
      if (event.key === 'site-theme') {
        applyPreferredTheme();
      }
    });

    applyPreferredTheme();
  },

  initNavbar : function() {
    // Set the navbar-dark/light class based on its background color
    const rgb = $('.navbar').css("background-color").replace(/[^\d,]/g,'').split(",");
    const brightness = Math.round(( // http://www.w3.org/TR/AERT#color-contrast
      parseInt(rgb[0]) * 299 +
      parseInt(rgb[1]) * 587 +
      parseInt(rgb[2]) * 114
    ) / 1000);
    if (brightness <= 125) {
      $(".navbar").removeClass("navbar-light").addClass("navbar-dark");
    } else {
      $(".navbar").removeClass("navbar-dark").addClass("navbar-light");
    }
  },

  initImgs : function() {
    // If the page was large images to randomly select from, choose an image
    if ($("#header-big-imgs").length > 0) {
      BeautifulJekyllJS.bigImgEl = $("#header-big-imgs");
      BeautifulJekyllJS.numImgs = BeautifulJekyllJS.bigImgEl.attr("data-num-img");

      // 2fc73a3a967e97599c9763d05e564189
      // set an initial image
      const imgInfo = BeautifulJekyllJS.getImgInfo();
      const src = imgInfo.src;
      const desc = imgInfo.desc;
      BeautifulJekyllJS.setImg(src, desc);

      // For better UX, prefetch the next image so that it will already be loaded when we want to show it
      const getNextImg = function() {
        const imgInfo = BeautifulJekyllJS.getImgInfo();
        const src = imgInfo.src;
        const desc = imgInfo.desc;

        const prefetchImg = new Image();
        prefetchImg.src = src;
        // if I want to do something once the image is ready: `prefetchImg.onload = function(){}`

        setTimeout(function(){
          const img = $("<div></div>").addClass("big-img-transition").css("background-image", 'url(' + src + ')');
          $(".intro-header.big-img").prepend(img);
          setTimeout(function(){ img.css("opacity", "1"); }, 50);

          // after the animation of fading in the new image is done, prefetch the next one
          //img.one("transitioned webkitTransitionEnd oTransitionEnd MSTransitionEnd", function(){
          setTimeout(function() {
            BeautifulJekyllJS.setImg(src, desc);
            img.remove();
            getNextImg();
          }, 1000);
          //});
        }, 6000);
      };

      // If there are multiple images, cycle through them
      if (BeautifulJekyllJS.numImgs > 1) {
        getNextImg();
      }
    }
  },

  getImgInfo : function() {
    const randNum = Math.floor((Math.random() * BeautifulJekyllJS.numImgs) + 1);
    const src = BeautifulJekyllJS.bigImgEl.attr("data-img-src-" + randNum);
    const desc = BeautifulJekyllJS.bigImgEl.attr("data-img-desc-" + randNum);

    return {
      src : src,
      desc : desc
    }
  },

  setImg : function(src, desc) {
    $(".intro-header.big-img").css("background-image", 'url(' + src + ')');
    if (typeof desc !== typeof undefined && desc !== false) {
      $(".img-desc").text(desc).show();
    } else {
      $(".img-desc").hide();
    }
  },

  initSearch : function() {
    if (!document.getElementById("beautifuljekyll-search-overlay")) {
      return;
    }

    $("#nav-search-link").click(function(e) {
      e.preventDefault();
      $("#beautifuljekyll-search-overlay").show();
      $("#nav-search-input").focus().select();
      $("body").addClass("overflow-hidden");
    });
    $("#nav-search-exit").click(function(e) {
      e.preventDefault();
      $("#beautifuljekyll-search-overlay").hide();
      $("body").removeClass("overflow-hidden");
    });
    $(document).on('keyup', function(e) {
      if (e.key == "Escape") {
        $("#beautifuljekyll-search-overlay").hide();
        $("body").removeClass("overflow-hidden");
      }
    });
  }
};

// 2fc73a3a967e97599c9763d05e564189

document.addEventListener('DOMContentLoaded', BeautifulJekyllJS.init);
