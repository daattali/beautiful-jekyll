/* Home page mini game: guess the mosaic fraction */
(function () {
  'use strict';
  var root = document.getElementById('game');
  if (!root) return;
  var COLS = 14, ROWS = 9;
  var state = { seed: 7, level: 'moderate', guess: null, streak: 0 };
  var tissue = root.querySelector('.tissue');
  var cells = [];
  for (var i = 0; i < COLS * ROWS; i++) {
    var c = document.createElement('span');
    c.style.transitionDelay = ((i % COLS) + Math.floor(i / COLS)) * 22 + 'ms';
    tissue.appendChild(c); cells.push(c);
  }
  var readout = root.querySelector('.game-readout');
  var guessBox = root.querySelector('.guesses');
  var message = root.querySelector('.game-message');
  var streakEl = root.querySelector('.streak');

  function rng(seed) {
    var s = seed % 4294967296;
    return function () { s = (s * 1664525 + 1013904223) % 4294967296; return s / 4294967296; };
  }
  function sample() {
    var rand = rng(state.seed * 2654435761);
    var n = state.level === 'low' ? 2 : state.level === 'high' ? 5 : 3;
    var sprinkle = state.level === 'low' ? 0.01 : state.level === 'high' ? 0.04 : 0.02;
    var clones = [], types = [], exp = 0, con = 0, k, x, y;
    for (k = 0; k < n; k++) clones.push({ x: rand() * COLS, y: rand() * ROWS, r: 1.1 + rand() * 1.7, t: rand() < 0.55 ? 'exp' : 'con' });
    for (y = 0; y < ROWS; y++) for (x = 0; x < COLS; x++) {
      var t = null;
      for (k = 0; k < n; k++) if (Math.hypot(x + .5 - clones[k].x, y + .5 - clones[k].y) < clones[k].r && rand() < 0.88) t = clones[k].t;
      if (!t && rand() < sprinkle) t = rand() < 0.5 ? 'exp' : 'con';
      if (t === 'exp') exp++; else if (t === 'con') con++;
      types.push(t);
    }
    return { types: types, exp: exp, con: con, pct: Math.round((exp + con) / (COLS * ROWS) * 100) };
  }
  function render() {
    var s = sample(), revealed = state.guess !== null;
    s.types.forEach(function (t, idx) { cells[idx].className = t === 'exp' ? 'h' : t === 'con' ? 'a' : ''; });
    tissue.setAttribute('aria-label', revealed
      ? 'Illustration of a tissue: ' + s.pct + ' percent of 126 cells carry a mosaic repeat.'
      : 'Illustration of a tissue of 126 cells, some carrying a mosaic repeat. Guess the share below.');
    readout.textContent = revealed ? s.pct + '%' : '?';
    // four options: the answer plus three decoys
    var rand = rng((state.seed + 101) * 2246822519), offs = [-14, -9, -5, 4, 7, 11, 16], picks = [s.pct], tries = 0;
    while (picks.length < 4 && tries++ < 60) {
      var v = s.pct + offs[Math.floor(rand() * offs.length)];
      if (v >= 0 && v <= 70 && picks.every(function (p) { return Math.abs(p - v) >= 3; })) picks.push(v);
    }
    picks.sort(function (a, b) { return a - b; });
    guessBox.innerHTML = '';
    picks.forEach(function (v) {
      var b = document.createElement('button');
      b.type = 'button'; b.textContent = v + '%'; b.disabled = revealed;
      if (revealed) b.className = v === s.pct ? 'right' : v === state.guess ? 'chosen' : 'dim';
      b.addEventListener('click', function () {
        state.streak = v === s.pct ? state.streak + 1 : 0; state.guess = v; render();
      });
      guessBox.appendChild(b);
    });
    var detail = ' (' + s.exp + ' cells gained a unit, ' + s.con + ' lost one).';
    message.textContent = !revealed ? 'Make your guess to reveal the answer.'
      : state.guess === s.pct ? 'Spot on: ' + s.pct + '%' + detail + ' prancSTR would be proud.'
      : 'Not quite, it\u2019s ' + s.pct + '%' + detail + ' Eyeballing is hard, which is why prancSTR uses statistics.';
    streakEl.hidden = state.streak === 0;
    streakEl.textContent = 'Streak: ' + state.streak;
    root.querySelectorAll('[data-level]').forEach(function (b) { b.setAttribute('aria-pressed', b.getAttribute('data-level') === state.level ? 'true' : 'false'); });
  }
  root.querySelectorAll('[data-level]').forEach(function (b) {
    b.addEventListener('click', function () { state.level = b.getAttribute('data-level'); state.seed++; state.guess = null; render(); });
  });
  root.querySelector('.new-tissue').addEventListener('click', function () { state.seed++; state.guess = null; render(); });
  render();
})();
