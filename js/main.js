// Dean Attali / Beautiful Jekyll 2015

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

// 2fc73a3a967e97599c9763d05e564189
