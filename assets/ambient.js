/* Home page background: a faint field of "cells" where small mosaic clones
   slowly appear and fade, and cells near the pointer light up.
   Colours come from the CSS variables, so it follows the light/dark theme. */
(function () {
  'use strict';
  var layer = document.querySelector('.ambient');
  if (!layer) return;
  var canvas = layer.querySelector('canvas'), ctx = canvas.getContext('2d');
  var reduce = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
  var CELL = 20, STEP = 27, FRAME_MS = 1000 / 24, MAX_CLONES = 4;
  var w = 0, h = 0, cols = 0, rows = 0, colors = {}, clones = [], last = 0, visible = true, raf = 0;
  var pointer = { x: -9999, y: -9999 };

  function readColors() {
    var s = getComputedStyle(document.documentElement);
    colors.tile = s.getPropertyValue('--tile').trim() || '#E6E7F2';
    colors.a = s.getPropertyValue('--mosaic-a').trim() || '#3B3BD1';
    colors.h = s.getPropertyValue('--mosaic-h').trim() || '#F0A202';
  }
  function resize() {
    var r = layer.getBoundingClientRect(), dpr = Math.min(window.devicePixelRatio || 1, 2);
    w = r.width; h = r.height;
    canvas.width = Math.round(w * dpr); canvas.height = Math.round(h * dpr);
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    cols = Math.ceil(w / STEP) + 1; rows = Math.ceil(h / STEP) + 1;
  }
  function spawn(t, age) {
    // keep clones mostly in the margins so the text column stays calm
    var side = Math.random() < 0.5 ? Math.random() * 0.12 : 0.68 + Math.random() * 0.32;
    clones.push({ x: side * cols, y: Math.random() * rows * 0.8, r: 1.6 + Math.random() * 2.4,
      born: t - (age || 0), life: 7000 + Math.random() * 6000, c: Math.random() < 0.55 ? 'h' : 'a', seed: Math.random() * 1000 });
  }
  function cell(x, y) {
    if (ctx.roundRect) { ctx.beginPath(); ctx.roundRect(x, y, CELL, CELL, 4); ctx.fill(); }
    else ctx.fillRect(x, y, CELL, CELL);
  }
  function draw(t) {
    ctx.clearRect(0, 0, w, h);
    clones = clones.filter(function (c) { return t - c.born < c.life; });
    while (clones.length < MAX_CLONES) spawn(t);
    var offX = (w - (cols - 1) * STEP) / 2;
    for (var j = 0; j < rows; j++) {
      for (var i = 0; i < cols; i++) {
        var x = offX + i * STEP, y = 8 + j * STEP;
        ctx.globalAlpha = 0.38; ctx.fillStyle = colors.tile; cell(x, y);
        var best = 0, bestC = null;
        for (var k = 0; k < clones.length; k++) {
          var c = clones[k], d = Math.hypot(i + 0.5 - c.x, j + 0.5 - c.y);
          if (d < c.r) {
            // ragged clone edge: a fixed pseudo-random hole pattern per clone
            if (Math.sin(i * 12.9898 + j * 78.233 + c.seed) > 0.75) continue;
            var p = (t - c.born) / c.life, env = Math.sin(Math.PI * p);
            var v = env * (1 - 0.45 * d / c.r);
            if (v > best) { best = v; bestC = c.c; }
          }
        }
        var pd = Math.hypot(x + CELL / 2 - pointer.x, y + CELL / 2 - pointer.y);
        if (pd < 110) { var pv = (1 - pd / 110) * 0.8; if (pv > best) { best = pv; bestC = 'a'; } }
        if (bestC) { ctx.globalAlpha = best * 0.32; ctx.fillStyle = colors[bestC]; cell(x, y); }
      }
    }
    ctx.globalAlpha = 1;
  }
  function loop(t) {
    raf = 0;
    if (!visible || document.hidden) return;
    if (t - last >= FRAME_MS) { last = t; draw(t); }
    raf = requestAnimationFrame(loop);
  }
  function start() { if (!raf && !reduce) raf = requestAnimationFrame(loop); }

  readColors(); resize();
  if (reduce) {
    var now = performance.now();
    for (var n = 0; n < MAX_CLONES; n++) spawn(now, 3500);
    draw(now);
  } else {
    var t0 = performance.now();
    for (var m = 0; m < MAX_CLONES; m++) spawn(t0, Math.random() * 6000);
    start();
    window.addEventListener('pointermove', function (e) {
      var r = layer.getBoundingClientRect(); pointer.x = e.clientX - r.left; pointer.y = e.clientY - r.top;
    }, { passive: true });
    document.addEventListener('pointerleave', function () { pointer.x = pointer.y = -9999; });
    document.addEventListener('visibilitychange', start);
    if ('IntersectionObserver' in window) {
      new IntersectionObserver(function (entries) { visible = entries[0].isIntersecting; start(); }).observe(layer);
    }
  }
  var rt;
  window.addEventListener('resize', function () { clearTimeout(rt); rt = setTimeout(function () { resize(); draw(performance.now()); }, 150); });
  document.addEventListener('themechange', function () { readColors(); draw(performance.now()); });
})();
