---
layout: post
published: true
title: Getting Started with Leaflet
tags:
  - General
  - Blog
comments: true
date: '2019-05-21'
---
![](https://thepracticaldev.s3.amazonaws.com/i/1bnfsz7moboq2ngou41i.png)

Start a basic HTML template
```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Getting Started with Leaflet JS</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
  </body>
</html>
```

Include Leaflet CSS file in the head section of your document:
```html
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.5.1/leaflet.css">
```

Include Leaflet JavaScript file after Leaflet’s CSS (before the closing `</body>` tag):
```html
<script src='https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.5.1/leaflet.js'></script>
```

Put a div element with the id `map` where you want your map to be:
```html
<div id="map"></div>
```

Make sure the map container has a defined height, for example by setting it in CSS:
```css
body {
  padding: 0;
  margin: 0;
}
html,
body,
#map {
  height: 100%;
}
```

Now you’re ready to initialize the map and do some stuff with it.

Lets start by setting up the BaseMap services. See ([Docs](https://leafletjs.com/reference-1.5.0.html#map)) for more info:
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
```

Next we setup the map options such as center and zoom.
```javascript
//Map Options
var mapOptions = {
  zoomControl: false,
  attributionControl: false,
  center: [-29.0529434318608, 152.01910972595218],
  zoom: 10,
  layers: [basemaps.OpenStreetMaps]
};
```

Finally we can initialise the map
```javascript
//Render Main Map
var map = L.map("map", mapOptions);
```

Besides tile layers, you can easily add other things to your map, including markers, polylines, polygons, circles, and popups. Let’s add a marker:
```javascript
var marker = L.marker([-29.0529434318608, 152.01910972595218]).addTo(map);
```

Popups are usually used when you want to attach some information to a particular object on a map. Leaflet has a very handy shortcut for this:
```javascript
marker.bindPopup("<b>Hello world!</b><br>I am a popup.").openPopup();
```

For more information please see the [Leaflet Quick Start Guide](https://leafletjs.com/examples/quick-start/)

See it in action on CodePen {% codepen https://codepen.io/ItsMeStevieG/pen/YbQKMQ %}
