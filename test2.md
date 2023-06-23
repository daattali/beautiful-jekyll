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
	var renderer = fullScreenRenderer.getRenderer();
	var renderWindow = fullScreenRenderer.getRenderWindow();
	vtk.IO.Core.DataAccessHelper.get('http').fetchBinary(`05-test-grid.vtp`).then((binary)=>{
		const reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
		reader.parseAsArrayBuffer(binary);
		mapper.setInputData(reader.getOutputData());
		console.log(vtk.Rendering.Core.vtkColorTransferFunction.vtkColorMaps.rgbPresetNames);
		const vtkColorMaps = vtk.Rendering.Core.vtkColorTransferFunction.vtkColorMaps;
		const cmap = vtkColorMaps.getPresetByName('Cool to Warm');
		const lut = vtk.Rendering.Core.vtkColorTransferFunction.newInstance();
		// FIXME: for some reason, the colormap seems not to respect the mapping range much
		// and the mesh only uses its beginning, without mapping -0.1…0.1 → 0…1
		lut.setMappingRange(-0.1,0.1);
		lut.updateRange();
		lut.applyColorMap(cmap);
		lut.build();
		mapper.setLookupTable(lut);
		  actor.setMapper(mapper);
		  renderer.addActor(actor);
		  renderer.resetCamera();
		  renderWindow.render();
	});
</script>
</body>
</html>
