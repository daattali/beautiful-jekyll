<<<<<<< HEAD
// Dean Attali / Beautiful Jekyll 2015

=======
>>>>>>> 63a9ef8e17c3e72d70bcea12730100613ffcc6a8
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
})
$('#main-navbar').on('hidden.bs.collapse', function () {
  $(".navbar").removeClass("top-nav-expanded");
<<<<<<< HEAD
})

// 2fc73a3a967e97599c9763d05e564189
=======
})
>>>>>>> 63a9ef8e17c3e72d70bcea12730100613ffcc6a8
