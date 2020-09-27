// Enable when system color scheme is dark

$(function() {
  var root = $(":root")
  const dr_settings = {
        brightness: 100,
        contrast: 100,
        sepia: 0
  };
  // Helps embedded DR fetch x-origin resources
  DarkReader.setFetchMethod(window.fetch);
  if (
    localStorage.getItem('color-mode') === 'light' ||
    (window.matchMedia('prefers-color-scheme: light').matches &&
    !localStorage.getItem('color-mode'))) {

    root.attr("color-mode", "light");
  } else {
    root.attr("color-mode", "dark");
  }

  if (!root.attr("color-mode") === 'light') {
    DarkReader.enable(dr_settings);
  }  

  $(".js-dark-toggle").on("click", (e) => {
    var root = $(":root");
    var mode = root.attr("color-mode");

    if (mode === "light") {
      root.attr("color-mode", "dark");
      localStorage.setItem("color-mode", "dark");
      DarkReader.enable();
    } else {
      root.attr("color-mode", "light");
      localStorage.setItem("color-mode", "light");
      DarkReader.disable(dr_settings);
    }
  
  } );
})
