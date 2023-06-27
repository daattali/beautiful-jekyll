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
  var fullScreenRenderer = vtk.Rendering.Misc.vtkFullScreenRenderWindow.newInstance({
    background: [0, 0, 0],
    //rootContainer: document.body,
    containerStyle: { width: '1000px', height: "800px" } 
  });
  var renderWindow = fullScreenRenderer.getRenderWindow();
  //var renderWindow = vtk.Rendering.Core.vtkRenderWindow.newInstance();
  var renderer = fullScreenRenderer.getRenderer();
  //var renderer = vtk.Rendering.Core.vtkRenderer.newInstance();
  var actor = vtk.Rendering.Core.vtkActor.newInstance();
  renderer.addActor(actor);
  var mapper = vtk.Rendering.Core.vtkMapper.newInstance(); // this is the right mapper
  actor.setMapper(mapper);  
  var reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
  const url              = '/assets/img/sub-sub-035_hole_filled.vtp'; 
  reader.setUrl(url);
  mapper.setInputConnection(reader.getOutputPort());
  // Camera settings
  var camera             = vtk.Rendering.Core.vtkCamera.newInstance();
  camera.setPosition(27.519753836746474, 604.1863725248345, -279.2425808488232);
  camera.setViewAngle(30.0);
  camera.zoom(4);
  renderer.setActiveCamera(camera);
  actor.getProperty().setColor(1, 1, 1);
  renderWindow.render();
  //renderer.resetCamera(); // after adding actor resetCamera() so that resetCamera() can take into consideration the bounds of all actors in the scene.
 // var renderWindow = fullScreenRenderer.getRenderWindow();
  // add axes
  // Use OpenGL as the backend to view all this
  const openGLRenderWindow = vtk.Rendering.OpenGL.vtkRenderWindow.newInstance();
  renderWindow.addView(openGLRenderWindow);
  // Create a div section to put this into
  const container = document.createElement('div');
  document.querySelector('body').appendChild(container);
  openGLRenderWindow.setContainer(container);
  // Capture size of the container and set it to the renderWindow
  const { width, height } = container.getBoundingClientRect();
  openGLRenderWindow.setSize(width, height);
  //Setup an interactor to handle mouse events
  const interactor = vtk.Rendering.Core.vtkRenderWindowInteractor.newInstance();
  interactor.setView(openGLRenderWindow);
  interactor.initialize();
  interactor.bindEvents(container);
  interactor.setInteractorStyle(vtk.Interaction.Style.vtkInteractorStyleTrackballCamera.newInstance());
  // create orientation widget - add orientation axes
  const axesActor = vtk.Rendering.Core.vtkAxesActor.newInstance();
  const orientationWidget = vtk.Interaction.Widgets.vtkOrientationMarkerWidget.newInstance({
  actor: axesActor,
  interactor: renderWindow.getInteractor(),
  renderer: renderer, 
  });
  orientationWidget.setEnabled(true);
  orientationWidget.setViewportCorner(vtk.Interaction.Widgets.vtkOrientationMarkerWidget.Corners.BOTTOM_RIGHT);
  orientationWidget.setViewportSize(0.15);
  //renderer.resetCamera();
  //renderWindow.render();
  // add a control panel
  const controlPanel = "<html><table> <tr>  <td> <label for='timeslider'>Gestational age:</label> <input id='timeslider' type='range' min='0' max='10' step='1' /> </td> </tr> <tr> <td> <p><span id='timevalue'>...</span></p> </td> </tr></table></html>";
  fullScreenRenderer.addController(controlPanel);
  // Manage which brain we see
  const BASE_URL = 'https://kitware.github.io/vtk-js-datasets/data/vtp/can/';
  const { fetchBinary } = vtk.IO.Core.DataAccessHelper.fetchBinary;
function downloadTimeSeries() {
  const files = ['can_0.vtp','can_5.vtp','can_10.vtp', 'can_15.vtp','can_20.vtp','can_25.vtp','can_30.vtp','can_35.vtp','can_40.vtp'];
  return Promise.all(
    files.map((filename) => fetchBinary(`${BASE_URL}/${filename}`).then((binary) => {
        const reader = vtk.IO.XML.vtkXMLPolyDataReader.newInstance();
        reader.parseAsArrayBuffer(binary);
        return reader.getOutputData(0); })
    )
  );
}
function getDataTimeStep(vtkObj) {
  const arr = vtkObj.getFieldData().getArrayByName('TimeValue');
  if (arr) {  return arr.getData()[0];  }
  return null; }
function setVisibleDataset(ds) {
  mapper.setInputData(ds);
  renderer.resetCamera();
  renderWindow.render();
}
// UI control handling
function uiUpdateSlider(max) {
  const timeslider = document.querySelector('#timeslider');
  timeslider.min = 0;
  timeslider.max = max - 1;
  timeslider.step = 1;
}
let timeSeriesData = [];
const timeslider = document.querySelector('#timeslider');
const timevalue = document.querySelector('#timevalue');
timeslider.addEventListener('input', (e) => {
  const activeDataset = timeSeriesData[Number(e.target.value)];
  if (activeDataset) {
    setVisibleDataset(activeDataset);
    timevalue.innerText = getDataTimeStep(activeDataset);
  }
});
downloadTimeSeries().then((downloadedData) => {
  timeSeriesData = downloadedData.filter((ds) => getDataTimeStep(ds) !== null);
  timeSeriesData.sort((a, b) => getDataTimeStep(a) - getDataTimeStep(b));
  uiUpdateSlider(timeSeriesData.length);
  timeslider.value = 0;
  // set up camera
  renderer.getActiveCamera().setPosition(0, 55, -22);
  renderer.getActiveCamera().setViewUp(0, 0, -1);
  setVisibleDataset(timeSeriesData[0]);
  timevalue.innerText = getDataTimeStep(timeSeriesData[0]);
});
</script>
</body>
</html>



