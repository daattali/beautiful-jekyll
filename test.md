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
  //var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  reader.setUrl('https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/tree/master/assets/img');
  var polydata = reader.getOutputData(0);  
  actor.setMapper(mapper);  
  mapper.setInputData(polydata);
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render(); 
  
</script>
</body>
</html>
