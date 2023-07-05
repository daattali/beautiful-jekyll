---
layout: page
permalink: /Test_/
show-avatar: true
display_categories: [work]
---
<html>
<body>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    //rootContainer: document.body,
    containerStyle: { width: '1000px', height: "800px" } 
  });
  var renderWindow = fullScreenRenderer.getRenderWindow();
  //var renderWindow = vtk.Rendering.Core.vtkRenderWindow.newInstance();
  var renderer = fullScreenRenderer.getRenderer();
  //var renderer = vtk.Rendering.Core.vtkRenderer.newInstance();
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  renderer.addActor(actor);
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance(); // this is the right mapper
  actor.setMapper(mapper);  
  var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  var url              = '/assets/img/sub-sub-035_hole_filled.vtp'; 
  reader.setUrl(url);
  mapper.setInputConnection(reader.getOutputPort());
  // Camera settings
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  camera.setViewAngle(30.0);
  camera.zoom(4);
  renderer.setActiveCamera(camera);
  actor.getProperty().setColor(1, 1, 1);
  renderWindow.render();
  //renderer.resetCamera(); // after adding actor resetCamera() so that resetCamera() can take into consideration the bounds of all actors in the scene.
 // var renderWindow = fullScreenRenderer.getRenderWindow();
  // add axes
  // Use OpenGL as the backend to view all this
  var openGLRenderWindow = vtk.Rendering.OpenGL.vtkRenderWindow.newInstance();
  renderWindow.addView(openGLRenderWindow);
  // Create a div section to put this into
  var container = document.createElement('div');
  document.querySelector('body').appendChild(container);
  openGLRenderWindow.setContainer(container);
  // Capture size of the container and set it to the renderWindow
  var { width, height } = container.getBoundingClientRect();
  openGLRenderWindow.setSize(width, height);
  //Setup an interactor to handle mouse events
  var interactor = vtk.Rendering.Core.vtkRenderWindowInteractor.newInstance();
  interactor.setView(openGLRenderWindow);
  interactor.initialize();
  interactor.bindEvents(container);
  interactor.setInteractorStyle(vtk.Interaction.Style.vtkInteractorStyleTrackballCamera.newInstance());
  // create orientation widget - add orientation axes
  var axesActor = vtk.Rendering.Core.vtkAxesActor.newInstance();
  var orientationWidget = vtk.Interaction.Widgets.vtkOrientationMarkerWidget.newInstance({
  actor: axesActor, interactor: renderWindow.getInteractor(), renderer: renderer, 
  });
  orientationWidget.setEnabled(true);
  orientationWidget.setViewportCorner(vtk.Interaction.Widgets.vtkOrientationMarkerWidget.Corners.BOTTOM_RIGHT);
  orientationWidget.setViewportSize(0.15);
  //renderer.resetCamera();
  //renderWindow.render();
  // add a control panel
  var controlPanel = "<html><table> <tr>  <td> <label for='timeslider'>Gestational age:</label> <input id='timeslider' type='range' min='20' max='36' step='0.1' /> </td> </tr> <tr> <td> <p><span id='timevalue'>...</span></p> </td> </tr></table></html>";
  fullScreenRenderer.addController(controlPanel);
function setVisibleDataset(ds) {
  mapper.setInputData(ds);
  renderer.resetCamera();
  renderWindow.render();
}
// UI control handling
function uiUpdateSlider(max) {
  var timeslider = document.querySelector('#timeslider');
  timeslider.min = 20;
  timeslider.max = 36;
  timeslider.step = 0.1;
}
let timeSeriesData = [];
var timeslider = document.querySelector('#timeslider');
var timevalue = document.querySelector('#timevalue');
timeslider.addEventListener('input', (e) => {
  var i = e.target.value;
  var t = (i-20)*10;
  var c = 0;
  if (i.toFixed(1) >= 24.0) {c = c+1;}
  if (i.toFixed(1) >= 28.0) {c = c+1;}
  if (i.toFixed(1) >= 32.0) {c = c+1;}
  timevalue.innerText = i;
  var file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_' + c + "__tp_"+ t +"__age_" + i.toFixed(1) + "0.vtp";
  console.log("selected file", file);
  binary = vtk.IO.Core.DataAccessHelper.get('http').fetchBinary(`${file}`);
var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
reader.parseAsArrayBuffer(binary);
  setVisibleDataset(reader.getOutputData(0));
  });
const time_0 = 20;
uiUpdateSlider(160);
timeslider.value = 20;
//var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
const file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.00.vtp';
//reader.setUrl(file);    
renderer.getActiveCamera().setPosition(0, 55, -22);
renderer.getActiveCamera().setViewUp(0, 0, -1);
console.log("set up first view", file);
binary = vtk.IO.Core.DataAccessHelper.get('http').fetchBinary(`${file}`);
var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
reader.parseAsArrayBuffer(binary);
  setVisibleDataset(reader.getOutputData(0));
//setVisibleDataset(reader.getOutputPort());
  console.log("first view set", file);
timevalue.innerText = time_0;

</script>
</body>
</html>



