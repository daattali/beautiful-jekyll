---
layout: page
permalink: /Test_/
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
    containerStyle: { width: '400px', height: "600px" } });
  var actor              = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper             = vtk.Rendering.Core.vtkMapper.newInstance();
  var cone               = vtk.Filters.Sources.vtkConeSource.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  actor.setMapper(mapper);
  mapper.setInputConnection(cone.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  camera.zoom(15);
  //camera.setFocalPoint(380.97411895023845, 200.64760282840194, 94.93353212117555);
  //camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  //camera.setViewUp(0.46926601607332835, -0.3433504107607388, -0.81357230876493);
  //camera.setViewAngle(30.0);
  //renderer.setCamera(camera);
  renderer.setActiveCamera(camera);
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render();
  
</script>
</body>
</html>
