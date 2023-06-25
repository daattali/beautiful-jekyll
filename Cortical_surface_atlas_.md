---
layout: page
permalink: /Cortical_surface_atlas_/
show-avatar: true
display_categories: [work]
---

<html>
  <style> 
.rangeslider {
  width: 400px;
  margin: 0 auto;
}
.myslider {
  -webkit-appearance: none;
  background: #FCF3CF;
  width: 100%;
  height: 20px;
  opacity: 0.8;
  margin-top: 100px;
}
.myslider::-webkit-slider-thumb {
  -webkit-appearance: none;
  cursor: pointer;
  background: #34495E;
  width: 33%;
  height: 20px;
}

.myslider:hover {
  opacity: 1;
}

.image {
  position: relative;
  width: 400px;
  margin: 0 auto;
}

.image>img {
  position: absolute;
  display: none;
}

.image>img.visible,
.image>img:first-child {
  display: block;
}

.sliderOutput>div {
  margin: 5px;
  width: 120px;
  display: inline-block;
  vertical-align: top;
  text-align: center;
}

.sliderOutput h6,
.sliderOutput p {
  margin: 5px;
}

</style> 



<div class="rangeslider">
    <input type="range" min="1" max="3" value="3" class="myslider" id="sliderRange">
    <div class="row mt-3">
        <div class="col-4">
            <h6 class="display-6">Starting From Scratch</h6>
        </div>
        <div class="col-4">
            <p class="demo">I'm designing around a few pieces I already own</p>
        </div>
        <div class="col-4">
            <h6 class="display-6">Mostly Furnished</h6>
        </div>
    </div>
</div>

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

<div class="image mt-3 mb-3">
    <img src="/assets/atlas/inner_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.00_smooth_300_.png">
    <img src="/assets/atlas/inner_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.10_smooth_300_.png">
    <img src="/assets/atlas/inner_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.20_smooth_300_.png">
</div>


<script> 
  var fs = require('fs');
var files = fs.readdirSync('/assets/atlas/inner_cortical_surface/');
  document.getElementById("demo").innerHTML = files; 
  
  var images = document.getElementById("sliderImages");

  rangeslider.addEventListener('input', function() {
    for (var i = 0; i < images.children.length; i++) {
      images.children[i].style.display = 'none';
    }
    i = Number(this.value) - 1;
    images.children[i].style.display = 'block';
  });
</script> 
</html>


