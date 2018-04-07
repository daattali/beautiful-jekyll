// Dean Attali / Beautiful Jekyll 2016

var main = {

  bigImgEl : null,
  numImgs : null,

  init : function() {
    // Shorten the navbar after scrolling a little bit down
    $(window).scroll(function() {
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

    // show the big header image
    main.initImgs();

    // show Scroll To Top
    main.initScrollToTop();
  },

  initImgs : function() {
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
  	  var getNextImg = function() {
  	    var imgInfo = main.getImgInfo();
  	    var src = imgInfo.src;
  	    var desc = imgInfo.desc;
    		var prefetchImg = new Image();
      		prefetchImg.src = src;
		    // if I want to do something once the image is ready: `prefetchImg.onload = function(){}`

    		setTimeout(function(){
          var img = $("<div></div>").addClass("big-img-transition").css("background-image", 'url(' + src + ')');
    		  $(".intro-header.big-img").prepend(img);
    		  setTimeout(function(){ img.css("opacity", "1"); }, 50);

    		  // after the animation of fading in the new image is done, prefetch the next one
      		//img.one("transitioned webkitTransitionEnd oTransitionEnd MSTransitionEnd", function(){
    		  setTimeout(function() {
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

  getImgInfo : function() {
  	var randNum = Math.floor((Math.random() * main.numImgs) + 1);
    var src = main.bigImgEl.attr("data-img-src-" + randNum);
	  var desc = main.bigImgEl.attr("data-img-desc-" + randNum);

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

  // Start Code For Scroll To Top
  initScrollToTop : function() {
    var backTop = document.getElementsByClassName('js-cd-top')[0],
		// browser window scroll (in pixels) after which the "back to top" link is shown
		offset = 300,
		//browser window scroll (in pixels) after which the "back to top" link opacity is reduced
		offsetOpacity = 1200,
		scrollDuration = 700
		scrolling = false;
  	if( backTop ) {
  		//update back to top visibility on scrolling
  		window.addEventListener("scroll", function(event) {
  			if( !scrolling ) {
  				scrolling = true;
  				(!window.requestAnimationFrame) ? setTimeout(checkBackToTop, 250) : window.requestAnimationFrame(checkBackToTop);
  			}
      });
      
  		//smooth scroll to top
  		backTop.addEventListener('click', function(event) {
  			event.preventDefault();
  			(!window.requestAnimationFrame) ? window.scrollTo(0, 0) : scrollTop(scrollDuration);
  		});
  	}

  	function checkBackToTop() {
  		var windowTop = window.scrollY || document.documentElement.scrollTop;
  		( windowTop > offset ) ? addClass(backTop, 'cd-top--show') : removeClass(backTop, 'cd-top--show', 'cd-top--fade-out');
  		( windowTop > offsetOpacity ) && addClass(backTop, 'cd-top--fade-out');
  		scrolling = false;
  	}
  	
  	function scrollTop(duration) {
  	    var start = window.scrollY || document.documentElement.scrollTop,
  	        currentTime = null;
  	        
  	    var animateScroll = function(timestamp){
  	    	if (!currentTime) currentTime = timestamp;        
  	        var progress = timestamp - currentTime;
  	        var val = Math.max(Math.easeInOutQuad(progress, start, -start, duration), 0);
  	        window.scrollTo(0, val);
  	        if(progress < duration) {
              window.requestAnimationFrame(animateScroll);
  	        }
  	    };

  	    window.requestAnimationFrame(animateScroll);
  	}

  	Math.easeInOutQuad = function (t, b, c, d) {
   		t /= d/2;
  		if (t < 1) return c/2*t*t + b;
  		t--;
  		return -c/2 * (t*(t-2) - 1) + b;
  	};

  	//class manipulations - needed if classList is not supported
  	function hasClass(el, className) {
  	  	if (el.classList) return el.classList.contains(className);
  	  	else return !!el.className.match(new RegExp('(\\s|^)' + className + '(\\s|$)'));
  	}
  	function addClass(el, className) {
  		var classList = className.split(' ');
  	 	if (el.classList) el.classList.add(classList[0]);
  	 	else if (!hasClass(el, classList[0])) el.className += " " + classList[0];
  	 	if (classList.length > 1) addClass(el, classList.slice(1).join(' '));
  	}
  	function removeClass(el, className) {
  		var classList = className.split(' ');
  	  	if (el.classList) el.classList.remove(classList[0]);	
  	  	else if(hasClass(el, classList[0])) {
  	  		var reg = new RegExp('(\\s|^)' + classList[0] + '(\\s|$)');
  	  		el.className=el.className.replace(reg, ' ');
  	  	}
  	  	if (classList.length > 1) removeClass(el, classList.slice(1).join(' '));
  	}
  }
};

// 2fc73a3a967e97599c9763d05e564189

document.addEventListener('DOMContentLoaded', main.init);
