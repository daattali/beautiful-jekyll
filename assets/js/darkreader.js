// Enable when system color scheme is dark

$(function() {
  var root = $(":root")
  const dr_settings = {
        brightness: 100,
        contrast: 100,
        sepia: 0
  };

  if (
    localStorage.getItem('color-mode') === 'light' ||
    (window.matchMedia('prefers-color-scheme: light').matches &&
    !localStorage.getItem('color-mode'))) {

    root.setAttribute("color-mode", "light");
  }

  if (!root.getAttribute("color-mode") === 'light') {
    DarkReader.enable(dr_settings);
  }  

  $("js-dark-toggle").on("click", (e) => {
    var root = $(":root");
    var mode = root.getAttribute("color-mode");

    if (mode === "light") {
      root.setAttribute("color-mode", "dark");
      localStorage.setItem("color-mode", "dark");
      DarkReader.disable();
    } else {
      root.setAttribute("color-mode", "light");
      localStorage.setItem("color-mode", "light");
      DarkReader.enable(dr_settings);
    }
  
  } );
})
