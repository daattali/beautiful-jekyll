// theme-toggle.js

// Function to toggle theme
function toggleTheme() {
  const currentTheme = document.documentElement.getAttribute("data-theme");
  const newTheme = currentTheme === "dark" ? "light" : "dark";
  document.documentElement.setAttribute("data-theme", newTheme);
  localStorage.setItem("theme", newTheme);
}

// Apply saved theme on load
function loadTheme() {
  const savedTheme = localStorage.getItem("theme") || "light";
  document.documentElement.setAttribute("data-theme", savedTheme);
}

// Event listener for theme button
document.addEventListener("DOMContentLoaded", function() {
  loadTheme();
  document.getElementById("theme-button").addEventListener("click", toggleTheme);
});
