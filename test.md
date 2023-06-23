---
layout: page
permalink: /Test/
show-avatar: true
display_categories: [work]
---
<script>

import '@kitware/vtk.js/favicon';

// Load the rendering pieces we want to use (for both WebGL and WebGPU)
import '@kitware/vtk.js/Rendering/Profiles/Geometry';
import '@kitware/vtk.js/Rendering/Profiles/Molecule'; // vtkSphereMapper + vtkStickMapper

import vtkFullScreenRenderWindow from '@kitware/vtk.js/Rendering/Misc/FullScreenRenderWindow';
import vtkActor from '@kitware/vtk.js/Rendering/Core/Actor';
import vtkPDBReader from '@kitware/vtk.js/IO/Misc/PDBReader';
import vtkSphereMapper from '@kitware/vtk.js/Rendering/Core/SphereMapper';
import vtkStickMapper from '@kitware/vtk.js/Rendering/Core/StickMapper';
import vtkMoleculeToRepresentation from '@kitware/vtk.js/Filters/General/MoleculeToRepresentation';

// ----------------------------------------------------------------------------
// Standard rendering code setup
// ----------------------------------------------------------------------------

const fullScreenRenderer = vtkFullScreenRenderWindow.newInstance({
  background: [0, 0, 0],
});
const renderer = fullScreenRenderer.getRenderer();
const renderWindow = fullScreenRenderer.getRenderWindow();

// ----------------------------------------------------------------------------
// Example code
// ----------------------------------------------------------------------------

const reader = vtkPDBReader.newInstance();
const filter = vtkMoleculeToRepresentation.newInstance();
const sphereMapper = vtkSphereMapper.newInstance();
const stickMapper = vtkStickMapper.newInstance();
const sphereActor = vtkActor.newInstance();
const stickActor = vtkActor.newInstance();

filter.setInputConnection(reader.getOutputPort());
filter.setHideElements(['H']);

// render sphere
sphereMapper.setInputConnection(filter.getOutputPort(0));
sphereMapper.setScaleArray(filter.getSphereScaleArrayName());
sphereActor.setMapper(sphereMapper);

// render sticks
stickMapper.setInputConnection(filter.getOutputPort(1));
stickMapper.setScaleArray('stickScales');
stickMapper.setOrientationArray('orientation');
stickActor.setMapper(stickMapper);

// reader.setUrl(`${__BASE_PATH__}/data/molecule/pdb/caffeine.pdb`).then(() => {
reader.setUrl(`${__BASE_PATH__}/data/molecule/pdb/2LYZ.pdb`).then(() => {
  renderer.resetCamera();
  renderWindow.render();
});

renderer.addActor(sphereActor);
renderer.addActor(stickActor);
renderer.resetCamera();
renderWindow.render();

// -----------------------------------------------------------
// Make some variables global so that you can inspect and
// modify objects in your browser's developer console:
// -----------------------------------------------------------

global.reader = reader;
global.filter = filter;
global.sphereMapper = sphereMapper;
global.stickMapper = stickMapper;
global.sphereActor = sphereActor;
global.stickActor = stickActor;
global.renderer = renderer;
global.renderWindow = renderWindow;

</script>
