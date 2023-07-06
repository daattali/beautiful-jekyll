---
layout: page
permalink: /Atlas/
show-avatar: true
display_categories: [work]
---
<html>
  <head>
    <style>
      .btn {
  background-color:#3e5741;
  border: none;
  color: white;
  padding: 12px 16px;
  font-size: 16px;
  cursor: pointer;
}
.btn:hover {
  background-color: RoyalBlue;
}
      .slidecontainer {
  width: 100%;
  background: #f0e7ce;
}
.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 15px;
  border-radius: 5px;
  background: #000000;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
  margin: 0;
}
.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #3e5741;
  cursor: pointer;
}
.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #3e5741;
  cursor: pointer;
}
.ticks {
  display: flex;
  justify-content: space-between;}
.tick {
  position: relative;
  display: flex;
  justify-content: center;
  width: 1px;
  height: $unit;
  line-height: $unit * 5;
  margin-bottom: $unit;
}
</style>
  </head>
<body>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    containerStyle: { width: '1200px', height: "800px", marginLeft: "300px"} 
  });
  var renderWindow = fullScreenRenderer.getRenderWindow();
  var renderer = fullScreenRenderer.getRenderer();
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  renderer.addActor(actor);
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance(); // this is the right mapper
  actor.setMapper(mapper);  
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  // create orientation widget - add orientation axes
  var axesActor = vtk.Rendering.Core.vtkAxesActor.newInstance();
  var orientationWidget = vtk.Interaction.Widgets.vtkOrientationMarkerWidget.newInstance({
  actor: axesActor, interactor: renderWindow.getInteractor(), renderer: renderer, });
  orientationWidget.setEnabled(true);
  orientationWidget.setViewportCorner(vtk.Interaction.Widgets.vtkOrientationMarkerWidget.Corners.BOTTOM_RIGHT);
  orientationWidget.setViewportSize(0.25);
  // add a control panel
  var controlPanel = "<html><div class='slidecontainer'><label for='zoomslider'>Zoom:</label> <input id='zoomslider' type='range' class='slider' min='3' max='7' step='0.5'/><p>" + "<label for='timeslider'>Gestational age:</label> <input id='timeslider' type='range' class='slider' min='20' max='36' step='0.1'/><div class='ticks'> <span class='tick'>22</span> <span class='tick'>24</span> <span class='tick'>26</span> <span class='tick'>28</span> <span class='tick'>30</span> <span class='tick'>32</span> <span class='tick'>34</span> <span class='tick'>36</span></div> <p><span id='timevalue'>...</span></p>  <button id='play' class='btn'><i class='fa fa-play-circle'></i>Play</button>  </div> </html>";
  fullScreenRenderer.addController(controlPanel);
  var zoomslider = document.querySelector('#zoomslider');
  zoomslider.addEventListener('input', (e) => {
    camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
//  camera.setViewAngle(30.0);
  camera.zoom(Number(e.target.value));
 renderer.setActiveCamera(camera);
      renderWindow.render();
    });
var timeslider = document.querySelector('#timeslider');
var timevalue = document.querySelector('#timevalue');
timeslider.addEventListener('input', (e) => {
  var i = Number(e.target.value);
  var t = Math.round((i-20)*10);
  var c = 0;
  if (i >= 24.0) {c = c+1;}
  if (i >= 28.0) {c = c+1;}
  if (i >= 32.0) {c = c+1;}
  timevalue.innerText = e.target.value + " weeks";
  var file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_' + c + "__tp_"+ t +"__age_" + i.toFixed(1) + "0.vtp";
  console.log("selected file", file);
  var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  reader.setUrl(file);
  mapper.setInputConnection(reader.getOutputPort());
  renderWindow.render();
  });
// time slider features
timeslider.value = 20;
timevalue.innerText = timeslider.value + " weeks";
var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
const file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.00.vtp';
reader.setUrl(file);
mapper.setInputConnection(reader.getOutputPort());
  camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  camera.setViewAngle(30.0);
  camera.zoom(5);
 renderer.setActiveCamera(camera);
  actor.getProperty().setColor(1, 1, 1);
  // add a button
  const vrbutton = document.querySelector('play');
  vrbutton.addEventListener('click', (e) => {
  });
  renderWindow.render();
</script>
</body>
</html>



