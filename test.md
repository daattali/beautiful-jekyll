---
layout: page
permalink: /Test/
show-avatar: true
display_categories: [work]
---
<html>
 <center>
<body>
<script type="text/javascript" src="https://unpkg.com/@babel/polyfill@7.0.0/dist/polyfill.js"></script>
<script type="text/javascript" src="https://unpkg.com/vtk.js"></script>
<script type="text/javascript">  
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    containerStyle: { width: '400px', height: "600px" } });
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance();
  var reader = vtk.IO.Legacy.vtkPolyDataReader.newInstance();
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  const url              = '/assets/img/sub-sub-035_hole__filled.vtk';
  //var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  //
  //reader.setUrl('https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/blob/master/assets/img/ImageToStl.com_deterministicatlas__estimatedparameters__template_img.vtp')
  reader.setUrl(url);
  reader.update();
  mapper.setInput(reader.getOutput()); 
  actor.setMapper(mapper);  
  //mapper.setInputData(polydata);
  //var polydata = reader.getOutputData(0); or getOuput()??
  //mapper.setInputConnection(reader.getOutputPort());
  var renderer = fullScreenRenderer.getRenderer();
  renderer.addActor(actor);
  renderer.resetCamera();
  camera.zoom(1);
  renderer.setActiveCamera(camera);
  var renderWindow = fullScreenRenderer.getRenderWindow();
  renderWindow.render(); 
</script>
</body>
</center>
</html>
