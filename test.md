---
layout: page
permalink: /Test/
show-avatar: true
display_categories: [work]
---
<html>
<body>
<script type="text/javascript" src="https://unpkg.com/@babel/polyfill@7.0.0/dist/polyfill.js"></script>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">  
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    //rootContainer: document.body,
    containerStyle: { width: '1000px', height: "800px" } 
  });
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance(); // this is the right mapper
  var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  const url              = '/assets/img/sub-sub-035_hole_filled.vtp'; 
  actor.setMapper(mapper);  
  reader.setUrl(url);
  mapper.setInputConnection(reader.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  //renderer.resetCamera(); // after adding actor resetCamera() so that resetCamera() can take into consideration the bounds of all actors in the scene.
  actor.getProperty().setColor(1.0, 1.0, 1.0);
  camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  camera.setViewAngle(30.0);
  camera.zoom(4);
  renderer.setActiveCamera(camera);
  var renderWindow = fullScreenRenderer.getRenderWindow();
  // add axes
  // Use OpenGL as the backend to view all this
  const openGLRenderWindow = vtk.Rendering.OpenGL.vtkOpenGLRenderWindow.newInstance();
  renderWindow.addView(openGLRenderWindow);
  // Create a div section to put this into
  const container = document.createElement('div');
document.querySelector('body').appendChild(container);
openGLRenderWindow.setContainer(container);
  // Capture size of the container and set it to the renderWindow
const { width, height } = container.getBoundingClientRect();
openGLRenderWindow.setSize(width, height);
  //Setup an interactor to handle mouse events
  const interactor = vtk.Rendering.Core.vtkRenderWindowInteractor.newInstance();
  interactor.setView(openGLRenderWindow);
  interactor.initialize();
  interactor.bindEvents(container);
  interactor.setInteractorStyle(vtk.Interaction.Style.vtkInteractorStyleTrackballCamera.newInstance());
  // this was part of original code
  //renderWindow.render(); 
  // create orientation widget - add orientation axes
  const axesActor = vtk.Rendering.Core.vtkAxesActor.newInstance();
  const orientationWidget = vtk.Interaction.Widgets.vtkOrientationMarkerWidget.newInstance({
  actor: axesActor,
  interactor: interactor,
  renderer: renderer,
  });
  orientationWidget.setEnabled(true);
  orientationWidget.setViewportCorner(vtk.Interaction.Widgets.vtkOrientationMarkerWidget.Corners.BOTTOM_RIGHT);
//orientationWidget.setViewportSize(0.15);
//orientationWidget.setMinPixelSize(100);
//orientationWidget.setMaxPixelSize(300);
//renderer.resetCamera();
renderWindow.render();
</script>
</body>
</html>



