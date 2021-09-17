---
layout: page
title: About DGtal
---

# Project DGtal

The collaborative project DGtal aims at developing generic, efficient and reliable digital geometry data structures, algorithms and tools. It takes the form of an open-source C++ library DGtal and a set of tools and binaries DGtalTools.

# Overview of digital geometry

Digital geometry aims at defining proper geometric models and properties onto subsets of the integer plane/space ($$\mathbb{Z}^d$$). It is also interested in defining efficient algorithms for digital object topology and geometry processing. Natural applications of digital geometry are found in image analysis, since images are digital by nature. Digital geometry finds also applications in pattern recognition, computer graphics, biomedical  image analysis, OCR, 3D imaging.

Even if the domain emerged during the second half of the 20th century with the birth of computer graphics and digital image processing, many links have been demonstrated between Digital Geometry results and fundamental theorems in mathematics (arithmetic, geometry, topology…), discrete mathematics (word theory, combinatorics, graph theory…) or computer science (algorithmic, computational geometry, image processing…).

Have a look to the Gallery for digital geometry illustrations in DGtal.

# Objectives of DGtal Project

DGtal gathers in a unified setting many data structures and algorithms of digital geometry and related fields (digital topology, image processing, discrete geometry, arithmetic). It aims at fulfilling several objectives.

* It structures, in a unified and ready-to-use setting, different developments of the digital geometry and topology community.
* It makes easier the appropriation of our tools for neophytes (new PhD students, researchers from other fields, …).
* It allows fair comparisons of new methods with already existing approaches.
* It constructs a federative project that stimulates research in this field.
* It facilitates the dissemination of digital geometry in other academic fields or in industrial applications.
* It simplifies the construction of demonstration tools, so as to share new results or demonstrate the potential efficiency of new algorithms.

# Packages

The project is composed of two main packages: DGtal (main library) and DGtalTools which contains several tools built on DGtal.

# Features Digital Geometry Tools and Algorithms

[DGtal][1] offers concepts, data structures, algorithms for the following tasks: [digital spaces and sets][6] (integer plane and subsets, cellular grid space and subsets); [integers and fractions][7] (irreducible and continued fractions, Stern-Brocot tree); [digital straightness][8] (patterns, digital straight lines and subsegments); [grid curve representation][9] (points, pixel, interpixel, Freeman chaincode) and [analysis][10] (segmentation, covering); [primitives][11] (arithmetic, geometric and combinatorial digital straight segments, digital circular arc, digital planes);[ Euclidean and digital multigrid shape generation][12] (parametric and implicit curves and surfaces, Gauss digitization); [volumetric analysis with distance transformation][13] (DT and reverse DT, medial axis, digital Voronoi diagram); [geometric estimators][14] (tangent and curvature estimators along digital curves and surfaces); [digital topology][15] (adjacencies, objects, borders, simpleness, homotopic thinning); [digital surfaces][16] (implicit and explicit containers, neighborhood, tracking, dual surfaces, marching-cubes); [multi-variate polynomials][17]; [nD image processing][18] (readers, writers, vector, map and tree containers, ITK bridge); [export and visualization][19] (2D and 3D export and display stream mechanism; 3D interaction mechanism).

[1]: http://dgtal.org "DGtal"
[2]: http://en.wikipedia.org/wiki/Digital_geometry "Digital Geometry"
[3]: http://dgtal.org/gallery/ "Gallery"
[4]: http://dgtal.org/download/ "Download"
[5]: http://dgtal.org/tools/ "Tools"
[6]: http://dgtal.org/doc/stable/packageKernel.html "digital spaces and sets"
[7]: http://dgtal.org/doc/stable/moduleIrreducibleFraction.html "integers and fractions"
[8]: http://dgtal.org/doc/stable/moduleDigitalStraightness.html "digital straightness"
[9]: http://dgtal.org/doc/stable/moduleGridCurveAnalysis.html "grid curve representation"
[10]: http://dgtal.org/doc/stable/moduleGridCurveAnalysis.html "analysis"
[11]: http://dgtal.org/doc/stable/packageGeometry.html "primitives"
[12]: http://dgtal.org/doc/stable/moduleShape.html " Euclidean and digital multigrid shape generation"
[13]: http://dgtal.org/doc/stable/moduleVolumetric.html "volumetric analysis with distance transformation"
[14]: http://dgtal.org/doc/stable/packageGeometry.html "geometric estimators"
[15]: http://dgtal.org/doc/stable/moduleDigitalTopology.html "digital topology"
[16]: http://dgtal.org/doc/stable/moduleDigitalSurfaces.html "digital surfaces"
[17]: http://dgtal.org/doc/stable/modulePolynomial.html "multi-variate polynomials"
[18]: http://dgtal.org/doc/stable/packageImage.html "nD image processing"
[19]: http://dgtal.org/doc/stable/packageIO.html "export and visualization"
