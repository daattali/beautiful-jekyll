---
ID: 379
post_title: DGtal release 0.5 is available
author: David Coeurjolly
post_date: 2012-05-10 16:34:44
post_excerpt: ""
layout: post
permalink: >
  http://dgtal.org/dgtal-release-0-5-is-available/
published: true
---
We are pleased to announce the release 0.5 of the DGtal library. Here you have the complete Changelog of this release with plenty of new cool features ;) <!--more--> Many changes have been pushed to this release with a lot of nice tools. Before going into details component by component, we would like to focus on a couple of new cool features: 

*    new arithmetic package (fractions, models of fraction, Stern-Brocot, continued fraction,...)
*   new nD DigitalSurface model (collections of (n-1) topological cells with many  tools/utilities to track surface elements)
*   update of the build system to make easier the use of DGtal in your projects.
*   DGtal and DGtalTools (see below)
*   many bugfixes.. * Overall Project - In previous DGtal releases, tools were given in the source "tools/" folder. In this release, we have chosen to move the tools to another GitHub project (http://github.com/DGtal-team/DGtalTools) with a specific development process. Please have a look to this project to get nice tools built upon the DGtal library. 

*   cmake scripts and DGtalConfig have been widely updated to make easier the use of the  library in your own code
*   We are debugging both the code and the scripts to make it compile on windows. We still have couple of issues but most of DGtal compiles.
*   Again, efforts have been done on the documentation. * Package Topology:   

*   Creation of the graph concept (see Doxygen documentation)
*   Graph tools have been added: breadth first visitor for any model of graph
*   Creation of high-level classes to represent several kinds of digital surfaces. Surfaces are n-1 dimensional objetcs and may be open or closed. There are several models of digital surface containers: boundary of a set of points, explicit set of surfels, boundary of a digital object defined by a predicate, frontier between two regions, light containers that are discovered on traversal but not stored explicitly, etc.
*   All these digital surfaces can be manipulated through the same object (DigitalSurface), whichever the container.
*   DigitalSurface is a model of a graph whose vertices are the surfels and whose arcs are the connections between surfels.
*   Definition of umbrellas over digital surfaces, that forms faces onthe surface graph.
*   In 3D, digital surface form combinatorial 2-manifolds with boundary.
*   Digital surface can be exported in OFF format.
*   Several examples using digital surfaces are provided, like extracting isosurfaces from images or volume files defining surfaces in labelled images. * Package Algebraic (new package) 

*    Definition of n-variate polynomial as a one-dimensional polynomial whose coefficients are n-1-variate polynomials. Coefficient ring and dimension are templated.
*   Creation of a reader that can transform a string representation of multivariate polynomial  into such polynomial object. Use boost::spirit.
*   Example using package Topology to extract and display implicit polynomial surfaces in 3D. * Package Arithmetic (new package) 

*    Standard arithmetic computations are provided: greatest common divisor, Bézout vectors, continued fractions, convergent.
*   Several representations of irreducible fractions are provided. They are based on the Stern-Brocot tree structure. With these fractions, amortized constant time operations are provided for computing reduced fractions.
*   An implementation of patterns and subpatterns is provided, based on the irreducible fractions.
*   A representation of digital standard line in the first quadrant is provided, as well as fast algorithms to recognize digital straight subsegments. * Package Image 

*   Complete refactoring of Images and ImageContainers (more consistent design)
*   Documentation added
*   Graph of concepts added in the documentation * Package Geometry 

*    New SegmentComputer (a.k.a. geometrical primitives to use for recognition, curve decomposition,...) : ArithDSS3D (3D DSS), DCA (Digital Circular Arcs), CombinatorialDSSS, ...
*   New normal vector field estimation based on elementary normal vector convolution in n-D
*    Distance Transformation by Fast Marching Method added. * Package IO 

*   Complete refactoring of the way a DGtal object is displayed in boards/viewers.
*   New 2D board backend: you can export your drawning in TikZ for latex includes.