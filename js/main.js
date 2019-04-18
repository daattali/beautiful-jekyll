function isCurrentUrl(incomingURL) {

  var currentURL = window.location.href;

  var lastStringURLDimension = -incomingURL.length;

  return currentURL.trim().slice(lastStringURLDimension) === incomingURL;
}

function fadeOnScroll() {
  var windowHeight = $('.homeContainer').height();
  if (!isCurrentUrl("team") && !isCurrentUrl("contact") && !isCurrentUrl("career"))
    $(window).scroll(function (event) {
      var scrollValue = $(window).scrollTop();
      if (scrollValue < 1000) {
        var padding = scrollValue / 20;
        var homeTypographyOpacity = 1 - scrollValue / (windowHeight * 0.75);

        $('.homeTypography').css('opacity', homeTypographyOpacity);
        $('.homeTypography').css('padding-top', '' + padding + 'em');
        if (homeTypographyOpacity < 0) {
          $('.homeTypography').css('visibility', 'hidden');
        }
        else {
          $('.homeTypography').css('visibility', 'visible');
        }
      }
    });
}

function getFixedNavigationBar(navBar, navImg, navLogo, navItems, navMobileMenu) {
  navBar.style.position = "fixed";
  navBar.style.height = "4em";
  navBar.style.opacity = "0.9";
  navBar.style.backgroundColor = "black";

  navImg.style.display = "none";
  navLogo.src = "/img/logo.svg";

  navBar.classList.add('slideDown');
  navLogo.classList.add("slideDownItems");
  navItems.classList.add("slideDownItems3");
  navMobileMenu.classList.add("slideDownItems2");
}

function getTopNavigatioBar(body, navBar, navImg, navLogo, navItems, navMobileMenu) {
  navBar.style.position = "absolute";
  navBar.style.opacity = "1";
  navBar.style.backgroundColor = "transparent";

  navLogo.src = "/img/logoCS.svg";
  navImg.style.display = "flex";

  navBar.className = "navBar";
  navLogo.className = "navLogo";
  navItems.className = "navItems";
  navMobileMenu.className = "navMobileMenu";
}

function scroll() {
  var body = document.getElementById("body").offsetWidth;
  var windowHeight = $(window).height();
  // Team
  var teamTitleHeight = $("#teamPage").height();
  var teamMemberProfileHeight = $(".member-profile").height();
  var teamMaxHeight = teamTitleHeight + teamMemberProfileHeight * 2 + windowHeight * 0.06;
  // Career
  var careerTitleHeight = $(".career-page-title").height();
  var careerPositionsHeight = $("#positionsHeight").height();
  var careerMaxHeight = careerTitleHeight + careerPositionsHeight + 115;

  var navBar = document.getElementById("navBar");
  var navImg = document.getElementById("navImg");

  if (isCurrentUrl("team")) {
    if ((document.body.scrollTop > teamMaxHeight || document.documentElement.scrollTop > teamMaxHeight) && $('.mobile-profile').html() == "") {
      getFixedNavigationBar(navBar, navImg, navLogo, navItems, navMobileMenu);
    } else {
      getTopNavigatioBar(body, navBar, navImg, navLogo, navItems, navMobileMenu);
    }
  } else if (isCurrentUrl("career")) {
    if (document.body.scrollTop > careerMaxHeight || document.documentElement.scrollTop > careerMaxHeight) {
      getFixedNavigationBar(navBar, navImg, navLogo, navItems, navMobileMenu);
    } else {
      getTopNavigatioBar(body, navBar, navImg, navLogo, navItems, navMobileMenu);
    }
  } else {
    if (document.body.scrollTop > windowHeight || document.documentElement.scrollTop > windowHeight) {
      getFixedNavigationBar(navBar, navImg, navLogo, navItems, navMobileMenu);
    } else {
      getTopNavigatioBar(body, navBar, navImg, navLogo, navItems, navMobileMenu);
    }
  }
}

var main = {
  bigImgEl: null,
  numImgs: null,

  highlightNavigationItems: function highlightNavigationItems(docHref) {
    var navItems = $(".navItems a");
    var navMobileItems = $("#navMobileItems a");
    for (var i = 0; i < navItems.length; i++) {
      if (navItems[i].href == docHref || navMobileItems[i].href == docHref) {
        $(navItems[i]).css("opacity", "1");
        $(navMobileItems[i]).css("opacity", "1");
      } else {
        $(navItems[i]).css("opacity", "0.7");
        $(navMobileItems[i]).css("opacity", "0.7");
      }
    }
    if (isCurrentUrl("team")) {
      configPopups();
    }
  },

  openNavMobileItems: function openNavMobileItems() {
    var currentURL = window.location.href;
    var body = document.getElementById("body").offsetWidth;
    var windowHeight = $(window).height();

    // Team
    var teamTitleHeight = $("#teamPage").height();
    var teamMemberProfileHeight = $(".member-profile").height();
    var teamMaxHeight = teamTitleHeight + teamMemberProfileHeight * 2 + windowHeight * 0.06;

    // Career
    var careerTitleHeight = $(".career-page-title").height();
    var careerPositionsHeight = $("#positionsHeight").height();
    var careerMaxHeight = careerTitleHeight + careerPositionsHeight + 115;

    var display = document.getElementById("navMobileItems");

    if (display.style.zIndex === "1") {
      display.style.zIndex = "-1";
      display.style.visibility = "hidden";
      display.className = display.className.replace(/\bnavMobileItems\b/g, "");
      document.getElementById("body").style.overflowY = "visible";
      document.getElementById('navImg').className = "navImg";
      document.getElementById('navItemMob1').className = "";
      document.getElementById('navItemMob2').className = "";
      document.getElementById('navItemMob3').className = "";
      document.getElementById('navItemMob4').className = "";
      document.getElementById("navMobileMenuImg").src = "/img/menuIcon.svg";
      if (isCurrentUrl("team") && (document.body.scrollTop > teamMaxHeight
        || document.documentElement.scrollTop > teamMaxHeight) || isCurrentUrl("career")
        && (document.body.scrollTop > careerMaxHeight || document.documentElement.scrollTop > careerMaxHeight)
        || !isCurrentUrl("team") && !isCurrentUrl("career") && (document.body.scrollTop > windowHeight
          || document.documentElement.scrollTop > windowHeight)) {
        document.getElementById('navBar').style.backgroundColor = "black";
      } else {
        document.getElementById('navBar').style.backgroundColor = "transparent";
      }
    } else {
      display.style.zIndex = "1";
      display.style.visibility = "visible";
      display.className += "navMobileItems";
      document.getElementById('navImg').classList.add("navMobileMenuAnimation");
      document.getElementById('navItemMob1').classList.add("navMobileMenuAnimationItems");
      document.getElementById('navItemMob2').classList.add("navMobileMenuAnimationItems");
      document.getElementById('navItemMob3').classList.add("navMobileMenuAnimationItems");
      document.getElementById('navItemMob4').classList.add("navMobileMenuAnimationItems");
      document.getElementById('navItemMob5').classList.add("navMobileMenuAnimationItems");
      document.getElementById("body").style.overflowY = "hidden";
      document.getElementById("navMobileMenuImg").src = "/img/closeButtonWhite.svg";
      document.getElementById('navBar').style.backgroundColor = "transparent";
      document.getElementById("navLogo").src = "/img/logoCS.svg";

      document.getElementById("body").style.overflowY = "hidden";
    }
  },

  init: function () {
    // Shorten the navbar after scrolling a little bit down
    $(window).scroll(function () {
      if ($(".navbar").offset().top > 50) {
        $(".navbar").addClass("top-nav-short");
        $(".navbar-custom .avatar-container").fadeOut(500);
      } else {
        $(".navbar").removeClass("top-nav-short");
        $(".navbar-custom .avatar-container").fadeIn(500);
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
    $('#main-navbar').on("click", ".navlinks-parent", function (e) {
      var target = e.target;
      $.each($(".navlinks-parent"), function (key, value) {
        if (value == target) {
          $(value).parent().toggleClass("show-children");
        } else {
          $(value).parent().removeClass("show-children");
        }
      });
    });

    // Ensure nested navbar menus are not longer than the menu header
    var menus = $(".navlinks-container");
    if (menus.length > 0) {
      var navbar = $("#main-navbar ul");
      var fakeMenuHtml = "<li class='fake-menu' style='display:none;'><a></a></li>";
      navbar.append(fakeMenuHtml);
      var fakeMenu = $(".fake-menu");

      $.each(menus, function (i) {
        var parent = $(menus[i]).find(".navlinks-parent");
        var children = $(menus[i]).find(".navlinks-children a");
        var words = [];
        $.each(children, function (idx, el) { words = words.concat($(el).text().trim().split(/\s+/)); });
        var maxwidth = 0;
        $.each(words, function (id, word) {
          fakeMenu.html("<a>" + word + "</a>");
          var width = fakeMenu.width();
          if (width > maxwidth) {
            maxwidth = width;
          }
        });
        $(menus[i]).css('min-width', maxwidth + 'px')
      });

      fakeMenu.remove();
    }
    main.initImgs();
  },

  initImgs: function () {
    // If the page was large images to randomly select from, choose an image
    if ($("#header-big-imgs").length > 0) {
      main.bigImgEl = $("#header-big-imgs");
      main.numImgs = main.bigImgEl.attr("data-num-img");

      // 2fc73a3a967e97599c9763d05e564189
      // set an initial image
      var imgInfo = main.getImgInfo();
      var src = imgInfo.src;
      var desc = imgInfo.desc;
      main.setImg(src, desc);

      // For better UX, prefetch the next image so that it will already be loaded when we want to show it
      var getNextImg = function () {
        var imgInfo = main.getImgInfo();
        var src = imgInfo.src;
        var desc = imgInfo.desc;

        var prefetchImg = new Image();
        prefetchImg.src = src;
        // if I want to do something once the image is ready: `prefetchImg.onload = function(){}`

        setTimeout(function () {
          var img = $("<div></div>").addClass("big-img-transition").css("background-image", 'url(' + src + ')');
          $(".intro-header.big-img").prepend(img);
          setTimeout(function () { img.css("opacity", "1"); }, 50);

          // after the animation of fading in the new image is done, prefetch the next one
          //img.one("transitioned webkitTransitionEnd oTransitionEnd MSTransitionEnd", function(){
          setTimeout(function () {
            main.setImg(src, desc);
            img.remove();
            getNextImg();
          }, 1000);
          //});
        }, 6000);
      };

      // If there are multiple images, cycle through them
      if (main.numImgs > 1) {
        getNextImg();
      }
    }
  },

  getImgInfo: function () {
    var randNum = Math.floor((Math.random() * main.numImgs) + 1);
    var src = main.bigImgEl.attr("data-img-src-" + randNum);
    var desc = main.bigImgEl.attr("data-img-desc-" + randNum);

    return {
      src: src,
      desc: desc
    }
  },

  setImg: function (src, desc) {
    $(".intro-header.big-img").css("background-image", 'url(' + src + ')');
    if (typeof desc !== typeof undefined && desc !== false) {
      $(".img-desc").text(desc).show();
    } else {
      $(".img-desc").hide();
    }
  }

}

// 2fc73a3a967e97599c9763d05e564189
document.addEventListener('DOMContentLoaded', main.init);
