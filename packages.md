---
layout: page
title: Packages
---



<div>
  The DGtal library is composed of several main packages focusing on specific topics in Digital Geometry. Such packages are introduced below and are also documented in the <a href="http://dgtal.org/doc/stable">DGtal documentation main pages</a>
</div>

<div>
</div>

* * *

*   [Preliminaries][1]
    *   This package describes the main DGtal philosophy, its design and several technical comments to download, compile and install DGtal.
    *   *David Coeurjolly, Bertrand Kerautret*
    *   LGPL

* * *

*   [Base Package][2]
    *   This package gathers many concepts and stand-alone classes that are used in other packages, likes basic types, functions, functors, iterators, ranges, containers, concept check, trace and exception, timings, and smart pointers.
    *   *David Coeurjolly, Jacques-Olivier Lachaud, Tristan Roussillon*
    *   LGPL

* * *

*   [Kernel Package][3] <img class="wp-image-201 size-thumbnail" title="3D Domain visualization with some elements" src="http://dgtal.org/wp/wp-content/uploads/2010/10/Capture-d’écran-2011-03-19-à-01.45.24-150x150.png" alt="" width="150" height="150" />
    *   This package contains core concepts, objects and methods which are used in other higher level packages. For example, it defines number types considered in DGtal, fundamental structures such as the digital space, the digital domain, as well as basic linear algebra tools.
    *   *Jacques-Olivier Lachaud, David Coeurjolly, Guillaume Damiand, Sebastien Fourey*
    *   LGPL

* * *

*   [Arithmetic Package][5]
    *   This package gathers tools to perform arithmetic computations.

    <img class="   wp-image-556" title="dsl-standard-s" src="http://dgtal.org/wp/wp-content/uploads/2010/10/dsl-standard-s-300x255.png" alt="Standard digital straight line" width="126" height="107" />

    Standard arithmetic computations are provided: greatest common divisor, Bézout vectors, continued fractions, convergent, intersection of integer half-spaces. Several representations of irreducible fractions are provided. They are based on the Stern-Brocot tree structure. With these fractions, amortized constant time operations are provided for computing reduced fractions. A representation of digital standard line in the first quadrant is provided, as well as fast algorithms to recognize digital straight subsegments. Furthermore, it provides classes for representing 2D lattice polytopes (convex integer polygons) as well as methods to perform linear integer programming in the plane.
    *   *Jacques-Olivier Lachaud, Xavier Provençal, Mouhammad Said, Emilie Charrier, Lilian Buzer*
    *   LGPL

* * *

*   [Topology Package][7] <img class="wp-image-249 size-thumbnail" title="Tracking 2D surfel boundary from single surfel Cell of 3D Khalimsky Space" src="http://dgtal.org/wp/wp-content/uploads/2010/10/surfelTracking-150x150.png" alt="Tracking 2D surfel boundary from single surfel Cell of 3D Khalimsky Space" width="150" height="150" />

    *   This package contains digital topology related concepts, objects and methods which are used in other higher level packages. For example, it contains the classical topology tools (à la Rosenfeld), cartesian cellular topology, and digital surface topology (à la Herman). Generic tools and methods are provided for extracting connected components, identifying simple points, determining the neighborhood over a digital surface, tracking the boundary of a shape, defining cells and incidence operations. Several types of digital surfaces are provided (implicit, explicit, boundary, frontier) and the user can use them in a unified way. This package is notably used by the geometry package, especially to define curves and surfaces.
    *   *Jacques-Olivier Lachaud, Bertrand Kerautret*
    *   LGPL

* * *

*   [Geometry Package][9]
    *   This package contains geometry related concepts, objects and methods which are used in other higher level packages. It provides a generic framework for the segmentation of one-dimensional discrete structures, like strings, contours of 2d digital objects or nd digital curves. It has also limited support for digital plane recognition in 3d. It also provides a generic framework for the estimation of geometrical quantities, either global, like length, or local, like normal or curvature. Several estimators are built from some well chosen segmentations. On the other hand, this package contains tools for the analysis of volumes of arbitrary dimension, by the means of separable and incremental distance transforms.
    *   *Tristan Roussillon, David Coeurjolly, Jacques-Olivier Lachaud, Bertrand Kerautret*
    *   LGPL [caption id="attachment_117" align="alignright" width="150"][<img class="wp-image-117 size-thumbnail" title="exampleDSS-3" src="http://dgtal.org/wp/wp-content/uploads/2010/10/exampleDSS-3-150x118.png" alt="" width="150" height="118" />][10] Example of the decomposition of a simple 4-connected curve into maximal Discrete Straight Segments (greedy algorithm).[/caption] [caption id="attachment_259" align="alignright" width="150"][<img class="wp-image-259 size-thumbnail" title="Distance Transformation using the Euclidean distance " src="http://dgtal.org/wp/wp-content/uploads/2010/10/AlCaponeDistanceMap-150x150.png" alt="" width="150" height="150" />][11] Distance Transformation using the Euclidean distance[/caption]

* * *

*   [DEC Package][12]
    *   Discrete exterior calculus (DEC) provides an easy and efficient way to describe linear operator over various structure. Basic operators, such as Hodge duality operator or exterior derivative, can be combined to create classical vector analysis operator such as gradient, curl and divergence.
    *   *David Coeurjolly, Pierre Gueth*
    *   LGPL

* * *

*   [Boards & Viewers][13]
<img class="wp-image-558 size-thumbnail" title="visuVol3D" src="http://dgtal.org/wp/wp-content/uploads/2012/10/visuVol3D1-150x150.png" alt="lobster" width="150" height="150" />
    *   This package gathers tools and utilities to import/export images and visualize digital  data using interactive (viewers) and non-interactive (boards) mechanisms, in 2D and in 3D.
    *   *Bertrand Kerautret, Jacques-Olivier Lachaud, Nicolas Normand, Martial Tola, David Coeurjolly*
    *   LGPL (GPL if QGLViewer is used)

* * *

*   [Image Package][15] [caption id="attachment_97" align="alignright" width="150"][<img class="wp-image-97 size-thumbnail" title="Visualisation of some iso contours" src="http://dgtal.org/wp/wp-content/uploads/2010/10/contourS1-150x150.gif" alt="" width="150" height="150" />][16] Visualisation of some iso contours[/caption]
    *   This package aims to implement Image models and data-structures.
    *   *Tristan Roussillon, David Coeurjolly*
    *   LGPL

* * *

*   [Shapes Package][17]
    *   This package contains shape related concepts, models and algorithms. It provides a [caption id="attachment_560" align="alignright" width="150"][<img class="wp-image-560 size-thumbnail" title="accflower01" src="http://dgtal.org/wp/wp-content/uploads/2012/10/accflower01-150x150.png" alt="Flower" width="150" height="150" />][18] Digitization of a parametric 2D shape.[/caption] generic framework and tools to construct multigrid shapes in [DGtal][19]. More precisely, this package contains analytical objects (parametric, implicit, from point sets,...) with digitization schemes to make concrete such objects in a given grid step grid.
    *   *David Coeurjolly, Jacques-Olivier Lachaud*
    *   LGPL

* * *

*   [Graph Package][20]
    *   This package gathers concepts and classes related to graphs. Simple visitors are [caption id="attachment_562" align="alignright" width="150"][<img class="wp-image-562 size-thumbnail" title="graphTraversal-bfs" src="http://dgtal.org/wp/wp-content/uploads/2012/10/graphTraversal-bfs-150x150.png" alt="graph traversal" width="150" height="150" />][21] Breadth-first traversal of a digital object, which is a model of finite simple graph.[/caption] provided to traverse the graph. For more elaborate graph algorithm, this package offers wrappers to boost::graph.
    *   *Jacques-Olivier Lachaud, David Coeurjolly*
    *   LGPL

* * *

*   [Mathematical Package][22]
    *   This package gathers various mathematical subpackages and modules. For now, it [caption id="attachment_565" align="alignright" width="150"][<img class="wp-image-565 size-thumbnail" title="nice-mpolynomial" src="http://dgtal.org/wp/wp-content/uploads/2012/10/nice-mpolynomial-150x150.png" alt="3D implicit surface" width="150" height="150" />][23] Triangulation of a 3D implicit surface, a 3-variate polynomial.[/caption] consists essentially in a module for defining multivariate polynomials.
    *   *Jacques-Olivier Lachaud, Felix Fontein*
    *   LGPL

 [1]: http://dgtal.org/doc/stable/packageIntroduction.html
 [2]: http://dgtal.org/doc/stable/packageBase.html
 [3]: http://dgtal.org/doc/stable/packageKernel.html
 [4]: http://dgtal.org/wp/wp-content/uploads/2010/10/Capture-d’écran-2011-03-19-à-01.45.24-1024x775.png
 [5]: http://dgtal.org/doc/stable/packageArithmetic.html "Arithmetic Package"
 [6]: http://dgtal.org/wp/wp-content/uploads/2012/10/dsl-standard-s.png
 [7]: http://dgtal.org/doc/stable/packageTopology.html
 [8]: http://dgtal.org/wp/wp-content/uploads/2010/10/surfelTracking.png
 [9]: http://dgtal.org/doc/stable/packageGeometry.html
 [10]: http://dgtal.org/wp/wp-content/uploads/2010/10/exampleDSS-3.png
 [11]: http://dgtal.org/wp/wp-content/uploads/2010/10/AlCaponeDistanceMap.png
 [12]: http://dgtal.org/doc/stable/packageDEC.html
 [13]: http://dgtal.org/doc/stable/packageIO.html
 [14]: http://dgtal.org/wp/wp-content/uploads/2012/10/visuVol3D1.png
 [15]: http://dgtal.org/doc/stable/packageImage.html "Image Package"
 [16]: http://dgtal.org/wp/wp-content/uploads/2010/10/contourS1.gif
 [17]: http://dgtal.org/doc/stable/packageShapes.html "Shapes Package"
 [18]: http://dgtal.org/wp/wp-content/uploads/2012/10/accflower01.png
 [19]: http://dgtal.org/doc/stable/namespaces.html "DGtal is the top-level namespace which contains all DGtal functions and types."
 [20]: http://dgtal.org/doc/stable/packageGraph.html "Graph Package"
 [21]: http://dgtal.org/wp/wp-content/uploads/2012/10/graphTraversal-bfs.png
 [22]: http://dgtal.org/doc/stable/packageMath.html "Mathematical Package"
 [23]: http://dgtal.org/wp/wp-content/uploads/2012/10/
