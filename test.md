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
    rootContainer: document.body,
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
  //actor.getProperty().setColor(1.0, 0.0, 0.0);
  camera.zoom(0.05)
  camera.setViewAngle(30.0);
  renderer.setActiveCamera(camera)
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render(); 
</script>
</body>
</html>



