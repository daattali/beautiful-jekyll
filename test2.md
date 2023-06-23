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
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance();
  var actor              = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper             = vtk.Rendering.Core.vtkMapper.newInstance();
  var cone               = vtk.Filters.Sources.vtkConeSource.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  actor.setMapper(mapper);
  mapper.setInputConnection(cone.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  camera.zoom(5);
  renderer.setCamera(camera)
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render();
</script>
</body>
</html>
