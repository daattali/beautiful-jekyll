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
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  // add axes
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
  actor: axesActor, interactor: renderWindow.getInteractor(), renderer: renderer, });
  orientationWidget.setEnabled(true);
  orientationWidget.setViewportCorner(vtk.Interaction.Widgets.vtkOrientationMarkerWidget.Corners.BOTTOM_RIGHT);
  orientationWidget.setViewportSize(0.25);
  // add a control panel
  var controlPanel = "<html><table> <tr>  <td> <label for='timeslider'>Gestational age:</label> <input id='timeslider' type='range' min='20' max='36' step='0.1' style='margin: 1; width: 200px;'/> </td> </tr> <tr> <td> <p><span id='timevalue'>...</span></p> </td> </tr></table></html>";
  fullScreenRenderer.addController(controlPanel);
var timeslider = document.querySelector('#timeslider');
var timevalue = document.querySelector('#timevalue');
timeslider.addEventListener('input', (e) => {
  var i = Number(e.target.value);
  var t = Math.round((i-20)*10);
  console.log("t",i,t)
  var c = 0;
  if (i >= 24.0) {c = c+1;}
  if (i >= 28.0) {c = c+1;}
  if (i >= 32.0) {c = c+1;}
  timevalue.innerText = e.target.value + "weeks";
  var file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_' + c + "__tp_"+ t +"__age_" + i.toFixed(1) + "0.vtp";
  console.log("selected file", file);
  var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  reader.setUrl(file);
  mapper.setInputConnection(reader.getOutputPort());
  renderWindow.render();
  });
// time slider features
//timeslider.min = 20;
//timeslider.max = 36;
//timeslider.step = 0.1;
timeslider.value = 20;
timevalue.innerText = "20 weeks";
var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
const file = '/assets/atlas/outer_cortical_surface/GeodesicRegression__GeodesicFlow__img__component_0__tp_0__age_20.00.vtp';
reader.setUrl(file);
mapper.setInputConnection(reader.getOutputPort());
  camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  camera.setViewAngle(30.0);
  camera.zoom(5);
 renderer.setActiveCamera(camera);
  actor.getProperty().setColor(1, 1, 1);
  renderWindow.render();
</script>
</body>
</html>



