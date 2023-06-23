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
  const reader = vtkPOlyDataReader.newInstance();
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance();
  var actor              = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper             = vtk.Rendering.Core.vtkMapper.newInstance();
  var cone               = vtk.Filters.Sources.vtkConeSource.newInstance();
  reader.SetFileName("https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/tree/master/assets/img/GeodesicRegression__GeodesicFlow__img__component_3__tp_159__age_35.90_smooth_300.vtk")
  reader.Update()
  poly_data = reader.GetOutput()
  actor.setMapper(mapper);
  mapper.setInputConnection(reader.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render();
</script>
</body>
</html>
