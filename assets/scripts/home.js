const SOCIAL_LIST = [
  {
    link: "https://mail.google.com/mail/u/0/?view=cm&fs=1&tf=1&to=lehoainam1998@gmail.com",
    iconClass: "fas fa-envelope",
  },
  {
    link: "https://www.linkedin.com/in/lehoainam1998/",
    iconClass: "fab fa-linkedin",
  },
  {
    link: "https://github.com/nhim411",
    iconClass: "fab fa-github",
  },
  {
    link: "https://fb.com/lhnam411",
    iconClass: "fab fa-facebook",
  },
  {
    link: "https://www.instagram.com/namlhh/",
    iconClass: "fab fa-instagram-square",
  },
  {
    link: "https://nhim411.github.io",
    iconClass: "fas fa-blog",
  },
];

$(document).ready(function () {
  // render social network list
  let xml = "";

  SOCIAL_LIST.forEach((item) => {
    xml += `<li class="social-item"><a href="${item.link}" target="_blank"><i class="${item.iconClass}"></i></a></li>`;
  });

  $("#socialNetwork").html(xml);
});
