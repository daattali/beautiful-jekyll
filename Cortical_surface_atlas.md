---
layout: page
permalink: /Cortical_surface_atlas/
show-avatar: true
display_categories: [work]
---

<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.slidecontainer {
  width: 100%;
}

.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 25px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  background: #04AA6D;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #04AA6D;
  cursor: pointer;
}
</style>
</head>
<body>

<h1>Custom Range Slider</h1>

<div class="slidecontainer">
  <p>Default range slider:</p>
  <input type="range" min="1" max="100" value="50">
  
  <p>Custom range slider:</p>
  <input type="range" min="1" max="100" value="50" class="slider" id="myRange">
</div>

</body>
</html>
