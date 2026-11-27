/* Shared behaviour: theme toggle, copy buttons, publication filters, back-to-top, mobile menu */
(function () {
  'use strict';
  var root = document.documentElement;

  // ---- Light / dark theme ----
  var SUN = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" aria-hidden="true"><circle cx="12" cy="12" r="4.5"/><path d="M12 2v2M12 20v2M4.9 4.9l1.4 1.4M17.7 17.7l1.4 1.4M2 12h2M20 12h2M4.9 19.1l1.4-1.4M17.7 6.3l1.4-1.4"/></svg>';
  var MOON = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><path d="M20 14.5A8.5 8.5 0 0 1 9.5 4a8.5 8.5 0 1 0 10.5 10.5z"/></svg>';
  function currentTheme() {
    return root.getAttribute('data-theme') || (window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light');
  }
  var toggle = document.querySelector('.theme-toggle');
  function paintToggle() {
    if (!toggle) return;
    var dark = currentTheme() === 'dark';
    toggle.innerHTML = dark ? SUN : MOON;
    toggle.setAttribute('aria-label', dark ? 'Switch to light theme' : 'Switch to dark theme');
  }
  if (toggle) {
    paintToggle();
    toggle.addEventListener('click', function () {
      var next = currentTheme() === 'dark' ? 'light' : 'dark';
      root.setAttribute('data-theme', next);
      try { localStorage.setItem('theme', next); } catch (e) {}
      paintToggle();
      document.dispatchEvent(new Event('themechange'));
    });
    window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', function () {
      paintToggle(); document.dispatchEvent(new Event('themechange'));
    });
  }

  // ---- Mobile menu: bring the current page into view ----
  var nav = document.querySelector('.nav'), here = nav && nav.querySelector('[aria-current="page"]');
  if (nav && here && nav.scrollWidth > nav.clientWidth) nav.scrollLeft = here.offsetLeft - (nav.clientWidth - here.offsetWidth) / 2;

  // ---- Copy buttons: any element with data-copy ----
  function toast(msg) {
    var t = document.createElement('div');
    t.className = 'toast'; t.setAttribute('role', 'status'); t.textContent = msg;
    document.body.appendChild(t); setTimeout(function () { t.remove(); }, 1800);
  }
  function copy(text) {
    if (navigator.clipboard && window.isSecureContext) return navigator.clipboard.writeText(text);
    var ta = document.createElement('textarea'); ta.value = text; ta.style.position = 'fixed'; ta.style.opacity = '0';
    document.body.appendChild(ta); ta.select();
    try { document.execCommand('copy'); } finally { ta.remove(); }
    return Promise.resolve();
  }
  document.querySelectorAll('[data-copy]').forEach(function (btn) {
    btn.addEventListener('click', function () {
      var label = btn.textContent;
      copy(btn.getAttribute('data-copy')).then(function () {
        btn.textContent = 'Copied'; toast(btn.getAttribute('data-copy-msg') || 'Copied to clipboard');
        setTimeout(function () { btn.textContent = label; }, 1600);
      });
    });
  });

  // ---- Publication filters (hide empty year groups too) ----
  var chips = document.querySelectorAll('[data-filter]');
  chips.forEach(function (chip) {
    chip.addEventListener('click', function () {
      var f = chip.getAttribute('data-filter'), shown = 0;
      chips.forEach(function (c) { c.setAttribute('aria-pressed', c === chip ? 'true' : 'false'); });
      document.querySelectorAll('[data-tags]').forEach(function (item) {
        var on = f === 'all' || item.getAttribute('data-tags').split(' ').indexOf(f) !== -1;
        item.hidden = !on; if (on) shown++;
      });
      document.querySelectorAll('.year-group').forEach(function (g) { g.hidden = !g.querySelector('[data-tags]:not([hidden])'); });
      var count = document.getElementById('pub-count');
      if (count) count.textContent = shown + (shown === 1 ? ' entry' : ' entries');
    });
  });

  // ---- Back to top ----
  var top = document.querySelector('.to-top');
  if (top) {
    var onScroll = function () { top.classList.toggle('show', window.scrollY > 600); };
    window.addEventListener('scroll', onScroll, { passive: true }); onScroll();
    top.addEventListener('click', function () { window.scrollTo({ top: 0 }); });
  }
})();
