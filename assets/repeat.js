/* Research page: grow a CAG repeat in HTT */
(function () {
  'use strict';
  var slider = document.getElementById('cag-slider');
  if (!slider) return;
  var row = document.getElementById('cag-row'), end = row.querySelector('.flank:last-child');
  var count = document.getElementById('cag-count'), label = document.getElementById('zone-label');
  var text = document.getElementById('zone-text'), swatch = document.getElementById('zone-swatch');
  var units = [];
  function zoneOf(i) { return i >= 40 ? 'z3' : i >= 36 ? 'z2' : i >= 27 ? 'z1' : (i % 2 ? '' : 'alt'); }
  function render() {
    var n = parseInt(slider.value, 10) || 18;
    while (units.length < n) { var u = document.createElement('span'); u.textContent = 'CAG'; row.insertBefore(u, end); units.push(u); }
    while (units.length > n) units.pop().remove();
    units.forEach(function (u, idx) { u.className = zoneOf(idx + 1); });
    var zone = n >= 40 ? ['Full penetrance', 'At 40 or more repeats, Huntington\u2019s disease is expected to develop.', 'z3']
      : n >= 36 ? ['Reduced penetrance', 'Between 36 and 39 repeats, some people develop Huntington\u2019s disease and some don\u2019t.', 'z2']
      : n >= 27 ? ['Intermediate', 'Between 27 and 35 repeats, disease isn\u2019t expected, but the repeat can grow when passed to children.', 'z1']
      : ['Typical range', 'Most people carry 26 or fewer CAG repeats in HTT.', ''];
    count.textContent = n; label.textContent = zone[0]; text.textContent = zone[1];
    swatch.className = 'swatch ' + zone[2];
    row.setAttribute('aria-label', 'A CAG repeat drawn with ' + n + ' units. ' + zone[0] + '.');
  }
  slider.addEventListener('input', render);
  render();
})();
