---
layout: page 
permalink: /Datasets_to_download/
title: Some home-made toy datasets to download
---

### Cross-sectional dataset of 30 characters 
 
<a id="raw-url" href="https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/raw/master/assets/img/characters.zip" download>Download the dataset</a>
 
### Time-series dataset of 30 characters 
 
<a id="raw-url" href="https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/raw/master/assets/img/characters_.zip" download>Download the dataset</a>

<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>

<h1>Custom Range Slider</h1>
<p>Drag the slider to display the current value.</p>

<div class="slidecontainer">
  <input type="range" min="1" max="100" value="50" class="slider" id="myRange">
  <p>Value: <span id="demo"></span></p>
</div>

<script>
var slider = document.getElementById("myRange");
var output = document.getElementById("demo");
output.innerHTML = slider.value;

slider.oninput = function() {
  output.innerHTML = this.value;
}
</script>

</body>
</html>
