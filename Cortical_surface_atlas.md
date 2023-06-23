---
layout: page
permalink: /Cortical_surface_atlas/
show-avatar: true
display_categories: [work]
---

### style means css part
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

### another slider

<html>

<section class="timemachine">
<form action="">
  <input type="range" />
</form>
</section>

<script>

var images;
function jsonFlickrApi(data) {
  console.log(data);
  images = data.photos.photo.map(function(photo){return photo.url_z});
  image_elements = images.map(function(mg, i) {
    var img = document.createElement('img');
    img.src = mg;
    var numb = document.createElement('h2');
    numb.textContent = i+1;
    var fig = document.createElement('figure');
    fig.appendChild(img);
    fig.appendChild(numb);
    document.querySelector('section').appendChild(fig); 
    return fig;
  });
   var slider = document.querySelector('input');
  slider.min = 0;
  slider.max = slider.value = images.length - 1;
  image_elements[slider.max].style.opacity = 1;
  // slider.step = 0.01;
  slider.addEventListener('input', function(e) {
  // console.log(Math.floor(e.target.value));
    image_elements.forEach(function(e){e.style.opacity=0;
                                       // e.style.zIndex=-100;
                                      });
    image_elements[Math.floor(e.target.value)].style.opacity = 1;
    // image_elements[Math.floor(e.target.value)].style.zIndex=100;
   
}); 
}
 
</script>
<script src="https://api.flickr.com/services/rest/?method=flickr.people.getPublicPhotos&api_key=603db98e0031fb25a3e3a6fc44502683&user_id=25053835@N03&per_page=50&format=json&extras=description,license,date_upload,date_taken,owner_name,icon_server,original_format,last_update,geo,tags,machine_tags,o_dims,views,media,path_alias,url_sq,url_t,url_s,url_q,url_m,url_n,url_z,url_c,url_l,url_o">
</script>
</html>

