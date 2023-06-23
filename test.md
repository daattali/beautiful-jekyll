---
layout: page
permalink: /Test/
show-avatar: true
display_categories: [work]
---
<html>
<body>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">  
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance();  
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance();
  var reader = vtk.IO.Legacy.vtkPolyDataReader.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  //var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  reader.setUrl('https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/tree/master/assets/img/GeodesicRegression__GeodesicFlow__img__component_3__tp_159__age_35.90_smooth_300.vtk');
  //
  //reader.setUrl('https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/blob/master/assets/img/ImageToStl.com_deterministicatlas__estimatedparameters__template_img.vtp')
  var polydata = reader.getOutputData(0);  
  actor.setMapper(mapper);  
  mapper.setInputData(polydata);
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  camera.zoom(5);
  renderer.setCamera(camera);
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render(); 
  
</script>
</body>
</html>
