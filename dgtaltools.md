---
layout: page
title: DGtalTools
---


[DGtalTools][1] is a separate github project containing tools constructed using DGtal library. The main goal of this part is to gather simple and useful tools exploiting the structures and algorithms defined in DGtal. Note that in complement to DGtalTools, the [DGtalTools-contrib][2] project was added to gather specific research tools or prototypes. The resulting tools could be useful to:

* Share and apply DGtal algorithms to various data from different domains.
* Construct demonstration tools like online demonstrations (as for instance the one of the [Image Processing Online][3]).
* Simplify comparisons of different algorithms with an single framework.
* Provide useful tools of digital image related algorithms (extraction of connected components, digital contour/surface extraction, simple visualization tools...).

The source code of the tools can also be used to non DGtal familiar user to show how to include the DGtal library framework directly in their own source code (in complement of [ DGtal tutorial][4] ).

### DGtalTools content:
At the moment the DGTalTools project is organized as follows (<span style="color: #8b0000;">new</span> or <span style="color: #008b00;">improved</span> in 1.2):
(see also the nightly build doxygen [documentation of the tools](https://dgtal-team.github.io/doctools-nightly/))
* **converters/**: utilities to convert various simple file formats:
  * <span style="color: #00008b;">convertVol</span>: a simple generic volume image converters (can process actually pgm3d, vol, longvol, raw (for writing)).
  * <span style="color: #00008b;">dicom2vol</span>: convert dicom images into 3d volumic file (need itk option in DGtal).
  * <span style="color: #00008b;">freeman2img</span>: transform one or several freeman chains into a pgm file by filling their interior areas.
  - <span style="color: #00008b;">freeman2sdp</span>: convert freeman chain towards a Sequence of Discrete Points.
  - <span style="color: #00008b;"> HDF52vol</span>: convert HDF5 to vol file format.
  - <span style="color: #00008b;">heightfield2shading</span>: a new tool to render a 2D heightfield image into a shading one.
  - <span style="color: #00008b;">heightfield2vol</span>: a new tool to transform 2D heightmap into volumetric file.
  - <span style="color: #00008b;">img2freeman</span>: to extract a freeman chain contour from a grayscale image.
  - <span style="color: #00008b;">imgAddNoise</span>: a new tool to add noise (Kanungo's) to a binary 2D object.
  - <span style="color: #008b00;">itk2vol</span>: convert any image of itk format (mhd, mha, ...) to vol (available with the itk option in DGtal).
  - <span style="color: #00008b;">longvol2vol</span>: convert longvol to vol file using different conversion policies.
  - <span style="color: #00008b;">mesh2heightfield</span>: new tool to convert a mesh file into a 2D height map (from a normal direction N and from a starting point P).
  - <span style="color: #00008b;">mesh2vol</span>: Convert a mesh file into a 26-separated or 6-separated voxelization in a given resolution grid.
  - <span style="color: #00008b;">ofs2off</span>: convert OFS mesh format towards a OFF variant.
  - <span style="color: #00008b;"> raw2HDF5</span>: convert raw image to HDF5.
  - <span style="color: #00008b;">raw2vol</span> and <span style="color: #00008b;">vol2raw</span>: transform 3D volumes files from (resp. to) raw to vol.
  - <span style="color: #00008b;"> sdp2vol</span>: a simple tool to create a 3d vol image from 3d digital points.
  - <span style="color: #00008b;">slice2vol</span>: tool to merge slices into one 3d volumic file.
  - <span style="color: #00008b;">vol2heightfield</span>: a new tool to transform volumetric file into 2D heightmap.
  - <span style="color: #00008b;">vol2obj</span>: convert a volume file into OBJ format (all voxels belonging to threshold interval)
  - <span style="color: #00008b;">vol2raw</span>: convert a vol to a 8-bit raw file.
  - <span style="color: #00008b;">vol2sdp</span><span style="font-size: 16px;">: a simple tools to extract digital points from 3d vol files.</span></span>
  - <span style="color: #00008b;"> vol2slice</span>: tool to extract all slices from 3d volumic images.
  - <span style="color: #00008b;">vol2vox/vox2vol</span>: tools to convert vol file to a MagicaVoxel VOX file and conversly.
  - <span style="color: #00008b;">volAddNoise</span>: a new tool to add noise (Kanungo's) to a binary 3D object.
  - <span style="color: #00008b;"> volBoundary2obj</span>: a simple tool to export the boundary of a an object in a volumetric file to OBJ.

* * * *

* **estimators/**:
  - <span style="color: #00008b;">2dLocalEstimators</span>: program to compare local curvature/tangent estimators on implicit shapes:
    * Maximal DSS based estimators
    * Maximal DCA based estimators
    * Binomial convolver based estimators
    * Integral Invariants based estimators

  - <span style="color: #00008b;">3dCurveTangentEstimator</span>: to estimate the tangent vector to a set of 3D integer points, which are supposed to approximate a 3D curve.

  - <span style="color: #00008b;">3dLocalEstimators</span>: program to compare 3D local curvature estimators  (mean, gaussian and principal curvatures) on 3D implicit shapes  with integral invariant and monge via jet fitting (with also noise robustness measure).
  - <span style="color: #00008b;">curvatureBC</span>: curvature estimator using the Binomial convolver.
  - <span style="color: #00008b;">curvatureMCMS</span>: curvature estimator using the maximal segments cover (to be updated for current DGtal version).
  - <span style="color: #00008b;">curvatureScaleSpaceBCC</span>: a tool to display the curvature scale space of a given contour with the Binomial Convolver Curvature Estimator.
  - <span style="color: #00008b;"> euleurCharacteristic </span>: bruteforce tool to extract (volumetric) Euler characteristic from volumetric binary object.
  - <span style="color: #00008b;">lengthEstimator</span>: program to generate multigrid analysis of length estimators.
  - <span style="color: #00008b;"> generic3dNormalEstimators</span>: Computes a normal vector field over a digitized 3D implicit surface for several estimators (II\|VCM\|Trivial\|True).
  - <span style="color: #00008b;">statisticsEstimators</span>: compute satistics (L1, L2, Loo) from results of two estimators.
  - <span style="color: #00008b;">tangentBC</span>: tangent estimator using the Binomial convolver.
  - <span style="color: #00008b;">vol2normalField</span>: compute the normal vector field of a given vol file.
  - <span style="color: #00008b;">volSurfaceRegularization</span>: Regularize a cubical complex into a smooth quadrangulated complex.


* * * *

* **image processing/**:
  - <span style="color: #00008b;">at-u2-v0</span>: computes a piecewise smooth approximation of a grey-level or color image, by optimizing the Ambrosio-Tortorelli functional (with u a 2-form and v a 0-form).
  - <span style="color: #00008b;">at-u0-v1</span>: Computes a piecewise smooth approximation of a grey-level or color image, by optimizing the Ambrosio-Tortorelli functional (with u a 0-form and v a 1-form).

* * * *

* **<span style="color: #00008b;">shapeGenerator</span>/**:
  - <span style="color: #00008b;">3dParametricCurveDigitizer</span>: a tool for digitization of 3D parametric curves.
  - <span style="color: #00008b;">shapeGenerator</span>: generate multigrid shape.
  - <span style="color: #00008b;">contourGenerator</span>: generate multigrid shape contours.

* * * *

* **visualization/**:
  - <span style="color: #00008b;"> 2dCompImage</span>: Computes and displays image comparisons (squared and absolute differences.
  - <span style="color: #00008b;">3dCompSurfelData</span>: a tool to compare generic surfel data informations given from two data files.
  - <span style="color: #00008b;">3dCurvatureViewer</span>: permits to compute and visualize mean or gaussian curvature and principal curvature directions of  binary shape.
  - <span style="color: #00008b;">3dCurvatureViewerNoise</span>: same as 3dCurvatureViewer, but allows to add some noise to objects.
  - <span style="color: #00008b;">3dCurveViewer</span>: A tool for visualizing the tangential cover of 3d curves.
  - <span style="color: #00008b;">3dDisplaySurfelData</span>: display surfel data from SDP file with color attributes given as scalar interpreted as color.
  - <span style="color: #00008b;">3dHeightMapViewer</span>: display a 2D image as heightmap by using QGLviewer.
  - <span style="color: #00008b;">3dImageViewer</span>: new tool to display slice image with interactive translatations or rotations (can open dicom format if WITH_ITK is set to true).
  - <span style="color: #00008b;">3dImplicitSurfaceExtractorBy4DExtension</span>: a tool to visualize 3d polynomial implicit surface defined as some f(x,y,z)=0.
  - <span style="color: #00008b;">3dImplicitSurfaceExtractorByThickening</span>: a tool to visualize 3d polynomial implicit surface defined as some f(x,y,z)=0.
  - <span style="color: #00008b;">3dSDPViewer</span>: basic display of a sequence of 3d points (as voxel or sphere) and vectors by using QGLviewer.
  - <span style="color: #008b00;">3dVolBoundaryViewer</span>: Display the boundary of a volume file by using QGLviewer.
  - <span style="color: #008b00;">3dVolViewer</span>: volume file (.vol and .pgm3d) viewer with QGLViewer.
  - <span style="color: #00008b;">displayContours</span>: display discrete contours from various format (.fc (freemanchain), .sdp).
  - <span style="color: #00008b;">meshViewer</span>: display 3D mesh from OFS or OFF format.
  - <span style="color: #00008b;">patternTriangulation</span>: a new tool that draws with Board2D the convex hull, the closest-point Delaunay triangulation or the farthest-point Delaunay triangulation of a pattern.
  - <span style="color: #00008b;">sliceViewer</span>: a new 2D and 3D slice viewer from 3D volumic files ( pgm3d, vol, longvol, and DICOM with ITK).

* * * *

* **volumetric/**:
  - <span style="color: #00008b;">3dVolMarchingCubes</span>: marching cubes form a Vol file
  - <span style="color: #00008b;">criticalKernelsThinning3D</span>: marching cubes form a Vol file
  - <span style="color: #00008b;">homotopicThinning3D</span>: ultimate skeleton from vol file
  - <span style="color: #00008b;">volAddBorder</span>: add a 1 voxel boundary with value 0 to a vol file.
  - <span style="color: #00008b;">volCComponentCounter</span>: a simple program to count the number of connected components in a 3D image.
  - <span style="color: #00008b;">volCrop</span>: crop an 3D vol image from to points.
  - <span style="color: #00008b;">volFillInterior</span>: tool to fill the interior of a voxel set.
  - <span style="color: #00008b;">volFlip</span>: tool to flip all volume slice images according a given dimension.

  - <span style="color: #00008b;">volImageMetrics</span>: apply basic measures from two volumetric images: RMSE and PSNR.
  - <span style="color: #00008b;">volIntensityScale</span>: a simple tool to apply a linear scale of the intensity given in a volumetric file.
  - <span style="color: #008b00;">volReSample</span>: apply a basic re sampling of a 3D volumetric image (.vol, .longvol, .pgm3d) with a given grid size.
  - <span style="color: #00008b;">volSegment</span>: Segment volumetric file from a simple threshold which can be set automatically from the otsu estimation.
  - <span style="color: #00008b;">volShapeMetrics</span>: apply shape measures for comparing two volumetric images A and B (shape defined from thresholds).
  - <span style="color: #00008b;">volSubSample</span>: sub sample a vol file (division by 2 in each direction)
  - Measures from voxel partition (true/false+-, precision recall, f-measure)
  - Measures bases on euclidean distance between the two Shape A and B.
  - <span style="color: #00008b;">volTrValues</span>: a basic tool to transform the voxel values from an input/output set.

### DGtalTools-contrib content:
At the moment the DFtalTools-contrib project is organized as follows (<span style="color: #8b0000;">new</span> or <span style="color: #00008b;">improved</span> in 1.0):

* **Geometry2d/**:
  - <span style="color: #00008b;">houghLineDetect</span>: to detect line segment from Hough transform (using OpenCV).
  - meaningFullThickness: to display the meaningful thickness of digital contour.
  - **<span style="color: #00008b;">distanceTransform/</span>**:
    - <span style="color: #00008b;">LUTBasedNSDistanceTransform</span>: Compute the 2D translated neighborhood-sequence distance transform of a binary imag
    - <span style="color: #00008b;">CumulativeSequenceTest</span> and <span style="color: #00008b;">RationalBeattySequenceTest</span>: tests from LUTBasedNSDistanceTransform.
  - <span style="color: #00008b;">thresholdRosin</span>: implementation of Rosin's algorithm to compute threshold of an unimodal intensity histogram

* * * *

* **Geometry3d/**:
  - <span style="color: #00008b;">basicEditMesh</span>: to apply basic mesh edition (scale change, mesh face contraction, face filtering).
  - <span style="color: #00008b;">basicMorphoFilter</span>: apply basic morpho filter from a ball structural element.
  - <span style="color: #00008b;">computeMeshDistances</span>: computes for each face of a mesh A the minimal distance to another mesh B.
  - <span style="color: #00008b;">off2obj</span>: tool to convert a mesh represented in off format into obj format.
  - <span style="color: #00008b;">off2sdp</span>: a tool to convert a mesh into a set of points (.sdp).
  - <span style="color: #00008b;">volLocalMax</span>: extract the local maximas of a vol image within a spherical kernel.
  - <span style="color: #00008b;">xyzScale</span>: a basic tool to adjust the scale of an xyz file.

* * * *

* **Visualisation/**:
  - <span style="color: #00008b;">displayLineSegments</span>: new tool allowing to display line segment in an output image.
  - <span style="color: #00008b;">displaySetOf2dPts</span>: tool to display sets of 2d points.
  - <span style="color: #00008b;">displayTgtCoverAlphaTS</span>: to display alpha-thick segment given on a simple contour.
  - <span style="color: #00008b;">graphViewer</span>: add a new tool allowing to display graph from edges, vertex and radii.
  - <span style="color: #00008b;">meshViewerEdit</span>: tool to visualize a mesh and to apply simple edits (face removal, color edits...).

### How to get and install DGtalTools (or DGtalTools-contrib)

You can get the DGtalTools by using git:

```git clone git://github.com/DGtal-team/DGtalTools.git``` or the source archive in the releases

or the DGtalTools-contrib:
```git clone git://github.com/DGtal-team/DGtalTools-contrib.git``` or the source archive in the releases

Installation:

* use cmake tool to generate a build script (MakeFile, VS project,..) from the CMakeLists.txt
* DGtal must be installed in your system. Concerning DGtal dependencies (boost, Qt,...), all the dependencies used to compile your DGtal library must be present to build the DGtalTools.

[1]: http://github.com/DGtal-team/DGtalTools
[2]: http://github.com/DGtal-team/DGtalTools-contrib
[3]: http://www.ipol.im
[4]: http://dgtal.org/doc/stable/packageTutorials.html
