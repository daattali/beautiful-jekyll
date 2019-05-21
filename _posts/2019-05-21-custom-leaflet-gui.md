---
layout: post
published: true
title: Custom Leaflet GUI
tags:
  - Dev
  - Leaflet
  - Map
  - Mapping
  - GIS
  - Bootstrap
  - jQuery
  - Custom
comments: true
date: '2019-05-21'
---
![](https://thepracticaldev.s3.amazonaws.com/i/h3a3v1a7dvgpbj2burvh.png)

Lets take a look at how to customise Leaflet mapping and add a sidebar interface.
<!--more-->

**Prerequites:**

- [Font Awesome](https://fontawesome.com/)
- [Bootstrap 4](https://getbootstrap.com/)
- [jQuery](https://jquery.com/)
- [LeafletJS](https://leafletjs.com/)
- [Leaflet Draw](https://github.com/Leaflet/Leaflet.draw)
- [Leaflet Sidebar v2](https://github.com/nickpeihl/leaflet-sidebar-v2)

Firstly start a basic HTML5 Template page.
```html
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Leaflet JS Customisation Demo</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
  </body>
</html>
```
Inside the `</head>` closing tag, include the following CSS Libraries:
```html
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto+Mono">
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.2/css/all.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.5.1/leaflet.css">
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/leaflet.draw/1.0.4/leaflet.draw.css">
<link rel="stylesheet" href="https://gitcdn.link/repo/nickpeihl/leaflet-sidebar-v2/master/css/leaflet-sidebar.min.css">
```
Include the following JavaScript libraries just before the `</body>` closing tag:
```html
<script src='https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js'></script>
<script src='https://use.fontawesome.com/releases/v5.8.2/css/all.css'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.3.1/js/bootstrap.min.js'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.5.1/leaflet.js'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/leaflet.draw/1.0.4/leaflet.draw.js'></script>
<script src='https://gitcdn.link/repo/nickpeihl/leaflet-sidebar-v2/master/js/leaflet-sidebar.min.js'></script>
```
Create the Sidebar and the Map Canvas by inserting the following code inside the `<body></body` tags
```html
<div id="sidebar" class="leaflet-sidebar collapsed">
  <!-- Nav tabs -->
  <div class="leaflet-sidebar-tabs">
    <ul role="tablist">
      <li><a href="#home" role="tab"><i class="fa fa-bars"></i></a></li>
      <li class="disabled"><a href="#profile" id="toggledraw" role="tab"><i class="fa fa-pen"></i></a></li>
    </ul>
  </div>

  <!-- Tab panes -->
  <div class="leaflet-sidebar-content">
    <div class="leaflet-sidebar-pane" id="home">
      <h1 class="leaflet-sidebar-header">
        Layers
        <span class="leaflet-sidebar-close"><i class="fa fa-caret-right"></i></span>
      </h1>
      <span id="layercontrol"></span>
      <div id="latlng"></div>

    </div>

    <div class="leaflet-sidebar-pane" id="profile">
      <h1 class="leaflet-sidebar-header">Profile<span class="leaflet-sidebar-close"><i class="fa fa-caret-right"></i></span></h1>
    </div>
  </div>
</div>

<div id="map"></div>
```

You will need to define the following CSS to set the page and map size:
```css
body {
  padding: 0;
  margin: 0;
}
html,
body,
#map {
  height: 100%;
  font-family: "Roboto", sans-serif;
}
```

Initialise Leaflet Map options and setup any map baselayers and overlays

```javascript
//Init Overlays
var overlays = {};

//Init BaseMaps
var basemaps = {
  "OpenStreetMaps": L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
    {
      minZoom: 2,
      maxZoom: 19,
      id: "osm.streets"
    }
  ),
  "Google-Map": L.tileLayer(
    "https://mt1.google.com/vt/lyrs=r&x={x}&y={y}&z={z}",
    {
      minZoom: 2,
      maxZoom: 19,
      id: "google.street"
    }
  ),
  "Google-Satellite": L.tileLayer(
    "https://mt1.google.com/vt/lyrs=s&x={x}&y={y}&z={z}",
    {
      minZoom: 2,
      maxZoom: 19,
      id: "google.satellite"
    }
  ),
  "Google-Hybrid": L.tileLayer(
    "https://mt1.google.com/vt/lyrs=y&x={x}&y={y}&z={z}",
    {
      minZoom: 2,
      maxZoom: 19,
      id: "google.hybrid"
    }
  )
};

//Map Options
var mapOptions = {
  zoomControl: false,
  attributionControl: false,
  center: [-29.0529434318608, 152.01910972595218],
  zoom: 10,
  layers: [basemaps.OpenStreetMaps]
};
```

Initialise the Leaflet map
```javascript
//Render Main Map
var map = L.map("map", mapOptions);
```

We must modify the CSS to prepare the layer control to be separated and placed into the sidebar
```css
/* Leaflet Layers Control */

.leaflet-control-layers {
  border-radius: none;
  box-shadow: none;
}

.leaflet-control-layers-expanded {
  width: 100% !important;
  padding: 0px;
  background-color: transparent;
  border: none !important;
}

#layercontrol {
  display: inline-block;
  width: 100%;
  padding: 10px;
  background-color: transparent;
  -webkit-border-radius: 4px;
  -moz-border-radius: 4px;
  border-radius: 4px;
}

#layercontrol .title {
  font-size: 16px;
  font-weight: bold;
  margin-bottom: 5px;
}
```

Next we initialise the Map zoom control, sidebar and separating the layer control into the sidebar
```javascript
//Render Zoom Control
L.control
  .zoom({
    position: "topleft"
  })
  .addTo(map);

var sidebar = L.control
  .sidebar({
    autopan: false,
    container: "sidebar",
    position: "right"
  })
  .addTo(map);

//Render Layer Control & Move to Sidebar
var layerControl = L.control
  .layers(basemaps, overlays, {
    position: "topright",
    collapsed: false
  })
  .addTo(map);
var oldLayerControl = layerControl.getContainer();
var newLayerControl = $("#layercontrol");
newLayerControl.append(oldLayerControl);
$(".leaflet-control-layers-list").prepend("<strong class='title'>Base Maps</strong><br>");
$(".leaflet-control-layers-separator").after("<br><strong class='title'>Layers</strong>");
//$(".leaflet-control-layers-separator").remove();
```

Before we initialise the Leaflet Draw control we need to add some CSS to hide the control by default
```css
/* Leaflet Draw */

.leaflet-draw {
  display: none;
}

.leaflet-draw-toolbar {
  display: none;
}
```

Initialise the Editable Cosmetic Layer and Leaflet Draw control
```javascript
//######## Leaflet Draw
var editableLayers = new L.FeatureGroup();
layerControl.addOverlay(editableLayers, "Cosmetic Layer");
map.addLayer(editableLayers);

var drawOptions = {
  position: "topleft",
  draw: {
    polyline: true,
    polygon: {
      allowIntersection: false, // Restricts shapes to simple polygons
      drawError: {
        color: "#e1e100", // Color the shape will turn when intersects
        message: "<strong>Oh snap!<strong> you can't draw that!" // Message that will show when intersect
      }
    },
    circle: true, // Turns off this drawing tool
    rectangle: true,
    marker: true
  },
  edit: {
    featureGroup: editableLayers, //REQUIRED!!
    remove: true
  }
};

var drawControl = new L.Control.Draw(drawOptions);
map.addControl(drawControl);

map.on(L.Draw.Event.CREATED, function(e) {
  var type = e.layerType,
    layer = e.layer;

  if (type === "marker") {
    layer
      .bindPopup(
        "LatLng: " + layer.getLatLng().lat + "," + layer.getLatLng().lng
      )
      .openPopup();
  }

  editableLayers.addLayer(layer);
  $(".drawercontainer .drawercontent").html(
    JSON.stringify(editableLayers.toGeoJSON())
  );
});

map.on(L.Draw.Event.EDITSTOP, function(e) {
  $(".drawercontainer .drawercontent").html(
    JSON.stringify(editableLayers.toGeoJSON())
  );
});

map.on(L.Draw.Event.DELETED, function(e) {
  $(".drawercontainer .drawercontent").html("");
});
```

Next create a jQuery event handler for the toggling of the draw controls
```javascript
//Edit Button Clicked
$('#toggledraw').click(function(e) {
  $(".leaflet-draw").fadeToggle("fast", "linear");
  $(".leaflet-draw-toolbar").fadeToggle("fast", "linear");
  this.blur();
  return false;
});
```

Before we can capture map clicks to get the coordinates into the sidebar we need to setup the CSS
```css
#latlng {
  position: absolute;
  right: 0px;
  bottom: 0px;
  font-size: 12px;
  font-weight: bold;
  padding: 2px 7px 1px 3px;
  margin-left: auto;
  margin-right: auto;
  color: black;
  background-color: white;
  -webkit-border-top-left-radius: 5px;
  -webkit-border-top-right-radius: 5px;
  -moz-border-radius-topleft: 5px;
  -moz-border-radius-topright: 5px;
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
  -webkit-box-shadow: 0px -2px 5px 0px rgba(0, 0, 0, 0.75);
  -moz-box-shadow: 0px -2px 5px 0px rgba(0, 0, 0, 0.75);
  box-shadow: 0px -2px 5px 0px rgba(0, 0, 0, 0.75);
  z-index: 1000;
  display: none;
}
```

Finally we can add the jQuery map click event handler for the capture of coordinates and also create the click event handler for the clipboard copy when the coordinates are clicked in the sidebar
```javascript
//Handle Map click to Display Lat/Lng
map.on('click', function(e) {
  $("#latlng").html(e.latlng.lat + ", " + e.latlng.lng);
	$("#latlng").show();
});

//Handle Copy Lat/Lng to clipboard
$('#latlng').click(function(e) {
  var $tempElement = $("<input>");
	$("body").append($tempElement);
	$tempElement.val($("#latlng").text()).select();
	document.execCommand("Copy");
	$tempElement.remove();
	alert("Copied: "+$("#latlng").text());
	$("#latlng").hide();
});
```

You are all done! Feel free to further customise this and show me your creations!

See it in Action on CodePen
<p class="codepen" data-height="465" data-theme-id="dark" data-default-tab="result" data-user="ItsMeStevieG" data-slug-hash="QRgWNR" style="height: 465px; box-sizing: border-box; display: flex; align-items: center; justify-content: center; border: 2px solid; margin: 1em 0; padding: 1em;" data-pen-title="Getting Started with Leaflet">
  <span>See the Pen <a href="https://codepen.io/ItsMeStevieG/pen/QRgWNR/">
  Getting Started with Leaflet</a> by Stevie G (<a href="https://codepen.io/ItsMeStevieG">@ItsMeStevieG</a>)
  on <a href="https://codepen.io">CodePen</a>.</span>
</p>

and Dark Mode
<p class="codepen" data-height="465" data-theme-id="dark" data-default-tab="result" data-user="ItsMeStevieG" data-slug-hash="QRgjmL" style="height: 465px; box-sizing: border-box; display: flex; align-items: center; justify-content: center; border: 2px solid; margin: 1em 0; padding: 1em;" data-pen-title="Getting Started with Leaflet">
  <span>See the Pen <a href="https://codepen.io/ItsMeStevieG/pen/QRgjmL/">
  Getting Started with Leaflet</a> by Stevie G (<a href="https://codepen.io/ItsMeStevieG">@ItsMeStevieG</a>)
  on <a href="https://codepen.io">CodePen</a>.</span>
</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>