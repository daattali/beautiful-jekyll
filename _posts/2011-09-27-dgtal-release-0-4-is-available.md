---
ID: 280
post_title: DGtal release 0.4 is available
author: David Coeurjolly
post_date: 2011-09-27 10:42:39
post_excerpt: ""
layout: post
permalink: >
  http://dgtal.org/dgtal-release-0-4-is-available/
published: true
---
We are pleased to announce that the release 0.4 of the DGtal library is available for download. Here you have a copy of the ChangeLog: 
*   Global changes:
*   A better decomposition of DGtal algorithms and data structures into packages.
*   By default, DGtal is built with minimal dependencies.
*   Concepts and concept checking mechanism have been considerably improved.

*   Kernel Package: refactoring of Integer types considered in DGtal.
*   Topology Package: Interpixel/cellular topological models, boundary tracking tools, ...
*   Geometry Package: many things have been added in the 1D contour analysis module:
*   multi-modal representation of 1D contours and curves (GridCurve facade)
*   decomposition/segmentation into primitives,
*   many differential estimators added, helpers for multigrid comparison of estimators
*   multigrid digital set generators from implicit and parametric shapes in dimension 2.

*   I/O Package: refactoring/enhancements of DGtal boards and viewers, enhancement of 2D boards with libcairo and a new Board3Dto2D board has been added.
*   Tools: multigrid shapeGenerator/contourGenerator added, lengthEstimator/estimatorComparator added for differential estimator multigrid comparison, connected components extraction in 3D, ...
*   Documentation: User guide has been improved thanks to a decomposition of the library into packages.