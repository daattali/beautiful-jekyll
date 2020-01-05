---
layout: post
title: DGtal + Polyscope
---

[Polyscope](http://polyscope.run) is a great C++ viewer and user
interface for the rapid prototyping and debugging of 3D geometric
algorithms. 

The key idea of [polyscope](http://polyscope.run) is to have the
notion of structures (e.g. pointclouds, meshes) and quantities
(scalar/vector attributes on faces, vertices...).

Thanks to a generic data adaptation framework,
[polyscope](http://polyscope.run) can be used to quickly to display
[DGtal](http://dgtal.org) data such as digital surfaces and quantities like curvature
estimation, normal vector fields (thanks to the brand new *Shortcuts*
helpers).

If you want a quick demo, just have a look to the
[polyscope-dgtal](https://github.com/dcoeurjo/polyscope-dgtal)
project. 

Last but not least, [DGtal](http://dgtal.org) is now listed on the
[polyscope](http://polyscope.run) web page in the
[integration list](http://polyscope.run/integrations/DGtal/).

![Polyscope](http://polyscope.run/media/teaser.svg)
