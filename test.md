---
layout: page
permalink: /Test/
show-avatar: true
display_categories: [work]
---
<html>
 <center>
<body>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">  
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    containerStyle: { width: '400px', height: "600px" } });
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance();
  var reader = vtk.IO.Legacy.vtkPolyDataReader.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  const url              = '/assets/img/GeodesicRegression__GeodesicFlow__img__component_3__tp_159__age_35.90_smooth_300.vtk';
  //var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  //
  //reader.setUrl('https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/blob/master/assets/img/ImageToStl.com_deterministicatlas__estimatedparameters__template_img.vtp')
  reader.setUrl(url).then(() => {
  reader.update();
  mapper.setInput(reader.getOutput()); 
  actor.setMapper(mapper);  
  //mapper.setInputData(polydata);
  //var polydata = reader.getOutputData(0); or getOuput()??
  //mapper.setInputConnection(reader.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  camera.zoom(0.05);
  renderer.setActiveCamera(camera);
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render(); 
});

</script>
</body>
</center>
</html>
