(function () {
  var headings = document.querySelectorAll('h1[id],h2[id],h3[id],h4[id],h5[id],h6[id]');
  for (var i = 0; i < headings.length; i++) {
    var img = document.createElement('img');
    img.setAttribute('src', '/assets/img/link-symbol.svg');

    var a = document.createElement('a');
    a.setAttribute('href', '#' + headings[i].getAttribute('id'));
    a.classList.add('anchor');
    a.appendChild(img);

    headings[i].insertBefore(a, headings[i].firstChild);
  }
})();
