---
layout: page
permalink: /Test__/
show-avatar: true
display_categories: [work]
---
<!DOCTYPE html>
<html>
<head><title>vtk.js</title></head>
<body>
<script type="text/javascript" src="https://unpkg.com/@babel/polyfill@7.0.0/dist/polyfill.js"></script>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance();
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance();
  var cone = vtk.Filters.Sources.vtkConeSource.newInstance();
  actor.setMapper(mapper);
  mapper.setInputConnection(cone.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render();
</script>
</body>
</html>
