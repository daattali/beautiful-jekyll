document.addEventListener("DOMContentLoaded", function() {
  const toggleButton = document.getElementById("theme-toggle");

  // Check if a preferred theme is saved in localStorage
  if (localStorage.getItem("theme") === "dark") {
    document.body.classList.add("dark-mode");
  }

  toggleButton.addEventListener("click", function() {
    document.body.classList.toggle("dark-mode");

    // Save the current theme preference to localStorage
    if (document.body.classList.contains("dark-mode")) {
      localStorage.setItem("theme", "dark");
    } else {
      localStorage.setItem("theme", "light");
    }
  });
});
