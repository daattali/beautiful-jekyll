
# DGtal 1.0

## New Features / Critical Changes

- *Helpers*
  - Classes Shortcuts and ShortcutsGeometry to simplify coding with DGtal. Integrate a lot of volume, digital surfaces, mesh, surface, geometry, estimators functions, with many conversion and input/output tools. (Jacques-Olivier Lachaud, [#1357](https://github.com/DGtal-team/DGtal/pull/1357))

## Changes

- *Configuration/General*
  - Simplifying Travis CI scripts (David Coeurjolly, [#1371](https://github.com/DGtal-team/DGtal/pull/1371))

## Bug Fixes
- *Configuration/General*
  - Continuous integration AppVeyor fix
    [#1326](https://github.com/DGtal-team/DGtal/pull/1326)
  - Fixing documentation checks and updating Travis scripts
    (Roland Denis, [#1335](https://github.com/DGtal-team/DGtal/pull/1335))
  - Fixing warning of Clang when including GraphicsMagick v1.3.31
    (Roland Denis, [#1366](https://github.com/DGtal-team/DGtal/pull/1366))

- Miscellaneous
  - Fix Small bug in Integral Invariant Volume Estimator in 2D
    (Thomas Caissard, [#1316](https://github.com/DGtal-team/DGtal/pull/1316))

  - Change from private to public access of types Input and Output in SCellToPoint
    (Daniel Antunes, [#1346](https://github.com/DGtal-team/DGtal/pull/1346))

- *Base*
  - Fixing wrong members in PredicateCombiner (David Coeurjolly,
    [#1321](https://github.com/DGtal-team/DGtal/pull/1321))

- *Shapes*
  - Add two new star shapes: Astroid and Lemniscate
   (Adrien Krähenbühl, Chouaib Fellah,
   [#1325](https://github.com/DGtal-team/DGtal/pull/1325))
  - Fixing openmp flags (David Coeurjolly,
    [#1324](https://github.com/DGtal-team/DGtal/pull/1324))
  - Add assignment operator to ImageContainerByITKImage (Pablo Hernandez,
    [#1336](https://github.com/DGtal-team/DGtal/pull/1336))
  - Fix compilation warning: const qualifier ignored in cast (Pablo Hernandez,
    [#1337](https://github.com/DGtal-team/DGtal/pull/1337))
  - Filter data passed to acos in order to avoid division by zero or an argument
    out of range. (Kacper Pluta, [#1359](https://github.com/DGtal-team/DGtal/pull/1359))

- *IO*
  - Fix wrong typedef for double case in ITKReader (Adrien Krähenbühl,
    [#1259](https://github.com/DGtal-team/DGtal/pull/1322))
  - Fix safeguard when using ImageMagick without cmake activation (David Coeurjolly,
    [#1344](https://github.com/DGtal-team/DGtal/pull/1344))

- *Documentation*
  - Replacing html internal links by ref command in Digital Topology module
    documentation. Also ignoring doxygen warning when ref begins with a digit.
    (Roland Denis, [#1340](https://github.com/DGtal-team/DGtal/pull/1340))
  - Fix examples' filenames in Digital Topology module documentation (Isabelle
    Sivignon, [#1331](https://github.com/DGtal-team/DGtal/pull/1331))
  - Fix doc bug with Hull2D namespace, (Tristan Roussillon,
    [#1330](https://github.com/DGtal-team/DGtal/pull/1330))
  - Checking boost version when including boost/common_factor_rt (David Coeurjolly,
    [#1344](https://github.com/DGtal-team/DGtal/pull/1344))

- *DEC*
  - Adding missing headers in some files of DEC.
    (Roland Denis, [#1349](https://github.com/DGtal-team/DGtal/pull/1349))

- *Math*
  - Fix possible division by zero in the MultiStatistics class.
    (Kacper Pluta, [#1358](https://github.com/DGtal-team/DGtal/pull/1358))

- *Image*
  - Fix bug in ImageLinearCellEmbedder.
    (Jacques-Olivier Lachaud, [#1356](https://github.com/DGtal-team/DGtal/pull/1356))

- *Kernel*
  - Adding square norm method to Point/Vector class. (David Coeurjolly,
    [#1365](https://github.com/DGtal-team/DGtal/pull/1365))

- *Helpers*
  - Small fixes in Shortcuts and ShortcutsGeometry, doc, and colormaps.
    (Jacques-Olivier Lachaud, [#1364](https://github.com/DGtal-team/DGtal/pull/1364))


# DGtal 0.9.4.1

## Bug Fixes

- *Documentation*
  - Fixing path to Mathjax CDN in documentation (David Coeurjolly,
    [#1318](https://github.com/DGtal-team/DGtal/pull/1318))

# DGtal 0.9.4

## New Features / Critical Changes

- *Shapes*
  - Mesh Voxelizer using 6- or 26-separability templated
   (David Coeurjolly, Monir Hadji,
   [#1209](https://github.com/DGtal-team/DGtal/pull/1209))

- *Topology Package*
  - Adding the half-edge data structure to represent arbitrary
    two-dimensional combinatorial surfaces with or without boundary
    (Jacques-Olivier Lachaud
     [#1266](https://github.com/DGtal-team/DGtal/pull/1266))
  - Add VoxelComplex, an extension for CubicalComplex, implementing the Critical-Kernels
    framework, based on the work of M.Couprie and G.Bertrand on isthmus.
    (Pablo Hernandez, [#1147](https://github.com/DGtal-team/DGtal/pull/1147))

- *Shapes Package*
  - Adding classes and helpers to create triangulated surfaces and
    polygonal surfaces to convert them from/to mesh, as well as a conversion from digital
    surfaces to dual triangulated or polygonal surface (Jacques-Olivier
    Lachaud [#1266](https://github.com/DGtal-team/DGtal/pull/1266))

- *Geometry Package*
  - Laplace-Beltrami operators on digital surfaces. (Thomas Caissard,
    [#1303](https://github.com/DGtal-team/DGtal/pull/1303))



## Changes

- *Math package*
  - New SimpleMatrix constructor with a initializer_list argument
    (Nicolas Normand,
    [#1250](https://github.com/DGtal-team/DGtal/pull/1250))

- *IO*
  - New simple way to extend the QGLViewer-based Viewer3D interface,
    for instance to add callbacks to key or mouse events, or to modify
    what is drawn on the window.
    (Jacques-Olivier Lachaud, [#1259](https://github.com/DGtal-team/DGtal/pull/1259))
  - TableReader can now read all elements contained in each line of a file
    with the new method getLinesElementsFromFile().
    (Bertrand Kerautret,
    [#1260](https://github.com/DGtal-team/DGtal/pull/1260))
  - New ImageMagick writer to export images to PNG or JPG formats for
    instance.  (David Coeurjolly,
    [#1304](https://github.com/DGtal-team/DGtal/pull/1304))
  - SimpleDistanceColorMap new colormap to easily display distance maps.
    (David Coeurjolly, [#1302](https://github.com/DGtal-team/DGtal/pull/1302))   
  - Fix in MagicReader allowing to load colored images. (David
    Coeurjolly, [#1305](https://github.com/DGtal-team/DGtal/pull/1305))
  - Include New ImageMagick writer in GenericWriter.  (Bertrand Kerautret,
    [#1306](https://github.com/DGtal-team/DGtal/pull/1306))

## Bug Fixes

- *Build*
  - Fix compilation by using DGtal from swift wrapping (Bertrand Kerautret,
    [#1309](https://github.com/DGtal-team/DGtal/pull/1309))
  - Fix C++11 cmake flags and cmake >3.1 is now required (David Coeurjolly,
    Pablo H Cerdan, [#1290](https://github.com/DGtal-team/DGtal/pull/1290))
  - Fix HDF5 link missing in compilation (Bertrand Kerautret,
     [#1301](https://github.com/DGtal-team/DGtal/pull/1301))
  - Fix compilation with QGLViewer (2.7.x) and Qt5 (Boris Mansencal,
     [#1300](https://github.com/DGtal-team/DGtal/pull/1300))

- *Shapes Package*
  - Fix ImplicitPolynomial3Shape and TrueDigitalSurfaceLocalEstimator.
    Improves projection operator on implicit surface and curvature
    computations. (Jacques-Olivier Lachaud,
    [#1279](https://github.com/DGtal-team/DGtal/pull/1279))

- *Configuration/General*
  - Upgrading the benchmarks to match with the new google-benchmark API
   (David Coeurjolly,
     [#1244]((https://github.com/DGtal-team/DGtal/pull/1244))
  - The documentation mainpage now refers to the DGtalTools documentation
    (David Coeurjolly,
    [#1249]((https://github.com/DGtal-team/DGtal/pull/1249))
  - Fix ITK related try_compile command to work for non-default locations.
    (Pablo Hernandez,
    [#1286]((https://github.com/DGtal-team/DGtal/pull/1286))

- *IO*
  - Fix for compilation with 2.7.0 QGLViewer version.
   (Bertrand Kerautret, [#1280](https://github.com/DGtal-team/DGtal/pull/1280))
  - Fix on the ITK reader when used with a functor which is not able to
    handle 32/16 bits images. Also includes a new testITKReader and ITK tests in
    GenericReader.
    (Bertrand Kerautret, [#1255](https://github.com/DGtal-team/DGtal/pull/1255))
  - Viewer3D: fix bad light source move according X/Y mouse move and new Key_Z to
    move away/closer the light source.
    (Bertrand Kerautret, [#1262](https://github.com/DGtal-team/DGtal/pull/1262))
  - Fix ImageContainerByITKImage, fill the itk image buffer with 0 when using the
    domain constructor.
    (Pablo Hernandez, [#1307](https://github.com/DGtal-team/DGtal/pull/1307))

- *Kernel Package*
  - Fix testBasicPointFunctor. (Bertrand Kerautret
    [#1245](https://github.com/DGtal-team/DGtal/pull/1245))

- *Arithmetic Package*
 - Fix SternBrocot and variants static instanciations. (Jacques-Olivier Lachaud
   [#1293](https://github.com/DGtal-team/DGtal/pull/1293))

- *Topology Package*
  - Fix invalid KhalimskyCell coordinates in ctopo-fillContours.cpp example.
    (Roland Denis, [#1296](https://github.com/DGtal-team/DGtal/pull/1296))

- *Documentation*
  - Add import with functors in GenericReader in the main default reader.
    (mainly motivated to show documentation of specialized version of
    importWithValueFunctor and importWithColorFunctor). The tiff format
    was also added to the generic readers when ITK is present (Bertrand
    Kerautret [1251](https://github.com/DGtal-team/DGtal/pull/1245))
  - Fix exampleArithDSS3d compilation (which was not activated).
    (Bertrand Kerautret
    [#1254](https://github.com/DGtal-team/DGtal/pull/1254))

- *DEC*
  - Fix dependencies flags for DEC examples.
    (Jean-David Génevaux, [#1310](https://github.com/DGtal-team/DGtal/pull/1310))

# DGtal 0.9.3

## New Features / Critical Changes

- *Configuration/General*
  - The project has a now a unique compiled library: DGtal. The DGtalIO
   target has been removed. (David Coeurjolly,
   [#1226](https://github.com/DGtal-team/DGtal/pull/1226))
  - New mandatory dependency for DGtal: zlib must be installed in the system.
   (David Coeurjolly, [#1228](https://github.com/DGtal-team/DGtal/pull/1228))
  - Remove cpp11 deprecated usage of std::binder1st and std::binder2nd  --generates error with c++17 flag.
   (Pablo Hernandez, [#1287](https://github.com/DGtal-team/DGtal/pull/1287))
  - Remove cpp11 deprecated usage of std::unary_function and std::binary_function --generates error with c++17 flag.
   (Pablo Hernandez, [#1291](https://github.com/DGtal-team/DGtal/pull/1291))

- *Topology Package*
  -  Implementation of ParDirCollapse with CollapseSurface and CollapseIsthmus.
    (Mohamad ONAYSSI, Bibiana MARTINEZ, Mohamed MELLOULI, Kacper PLUTA,
    [#1199](https://github.com/DGtal-team/DGtal/pull/1199))

- *Geometry Package*
  - VoronoiMap, PowerMap, (Reverse)DistanceTransformation and ReducedMedialAxis
   now work on toric domains (with per-dimension periodicity specification).
   (David Coeurjolly, Roland Denis,
   [#1206](https://github.com/DGtal-team/DGtal/pull/1206))

- *IO*
  - New version (3) for the VOL file format that allows (zlib) compressed volumetric
   data. VolReady and VolWriter can still manage Version 2 Vols.
   (David Coeurjolly, [#1228](https://github.com/DGtal-team/DGtal/pull/1228))

## Changes

- *Configuration/General*
  - Continuous integration Travis bots are now based on ubunutu/trusty containers.
   (David Coeurjolly, [#1227](https://github.com/DGtal-team/DGtal/pull/1208))
  - Set flag -std=c++11 only if needed. Modern compilers set compatible flags
   by default (gnu++14, etc). (Pablo H Cerdan,
   [#1222](https://github.com/DGtal-team/DGtal/pull/1222))

- *Documentation*
   - All the example descriptions are now in their the examples file (instead in
    dox files).
    (Bertrand Kerautret, [#1240](https://github.com/DGtal-team/DGtal/pull/1240))

## Bug Fixes

- *Configuration/General*
  - Fixing errors and warnings raised by g++ 4.7.x.
   (Roland Denis, [#1202](https://github.com/DGtal-team/DGtal/pull/1202))
  - Explicit M_PI definition if needed.
   (David Coeurjolly, [#1208](https://github.com/DGtal-team/DGtal/pull/1208))
  - Continuous integration Travis bots are now based on ubunutu/trusty containers.
   (David Coeurjolly, [#1227](https://github.com/DGtal-team/DGtal/pull/1208))
  - Fix usage of DESTDIR at install time for linux packagers.
   (Pablo Hernandez, [#1235](https://github.com/DGtal-team/DGtal/pull/1235))
  - Fix, let CMake handle DESTDIR instead of manual manipulation.
   (Pablo Hernandez, [#1238](https://github.com/DGtal-team/DGtal/pull/1238))

- *Geometry Package*
  - ArithDSSIterator: fix missing postfix ++.
   (I. Sivignon, [#1187](https://github.com/DGtal-team/DGtal/pull/1187))
  - ContourHelper: add a method to transform a contour into a 8 connected path.
   (B. Kerautret, [#1127](https://github.com/DGtal-team/DGtal/pull/1127))

- *IO Package*
  - Missing TContainer template parameter for overloaded functions/methods that
   rely on PointVector.
   (Roland Denis, [#1232](https://github.com/DGtal-team/DGtal/pull/1232))
  - Viewer3D: fix bad rendering when changing the scale.
   (Bertrand Kerautret, [#1217](https://github.com/DGtal-team/DGtal/pull/1217))

- *Documentation*
  - Fixing various BibTeX references.
   (Bertrand Kerautret, [##1237](https://github.com/DGtal-team/DGtal/pull/1237))

# DGtal 0.9.2

## New Features / Critical Changes

- *Documentation*
  - Fixing all doxygen warnings.
   (Roland Denis, [#1182](https://github.com/DGtal-team/DGtal/pull/1182))
  - New "@seeDGtalTools" doxygen command to cite a DGtalTools tool in
   DGtal documentation (David Coeurjolly,
   [#1179](https://github.com/DGtal-team/DGtal/pull/1179))

- *Geometry Package*
  - New robust normal vector estimator using spherical accumulators and statistical
   voting (Boulc'h & Marlet, SGP 2012).
   (David Coeurjolly, [#1149](https://github.com/DGtal-team/DGtal/pull/1149))

- *Math Package*
  - New RealFFT class for in-place real-complex Fast Fourier Transform using
   fftw3 library.
   (Roland Denis, [#1185](https://github.com/DGtal-team/DGtal/pull/1185))

- *Topology Package*
  - Adding periodic closure for KhalimskySpaceND and per-dimension closure
   specification.
   (Roland Denis, [#1086](https://github.com/DGtal-team/DGtal/pull/1086))
  - Adding CPreCellularGridSpaceND concept and KhalimskyPreSpaceND model
   to manipulate unbounded Khalimsky space and cells.
   KhalimskySpaceND now checks that all given cells are within the bounds.
   (Roland Denis, [#1086](https://github.com/DGtal-team/DGtal/pull/1086))

## Changes
- *Configuration/General*
  - Travis Continuous integration will check that doxygen raises no warnings
   and that the documented file names are valid.
   (David Coeurjolly, Roland Denis,
        [#1182](https://github.com/DGtal-team/DGtal/pull/1182))
  - Cleaning remaining preprocessor directives related to C++11 features.
   (Roland Denis, [#1141](https://github.com/DGtal-team/DGtal/pull/1141))
  - Travis Continuous integration will check that DGtalTools still compiles with
   changes in new pull-requests. (David Coeurjolly,
   [#1133](https://github.com/DGtal-team/DGtal/pull/1133))
  - Add cmake configuration file NeighborhoodTablesConfig to
   decompress and install look up tables. (Pablo Hernandez-Cerdan,
   [#1155](https://github.com/DGtal-team/DGtal/pull/1155))
  - Documentation graphs are now in SVG instead of PNG. (David Coeurjolly,
   [#1192](https://github.com/DGtal-team/DGtal/pull/1192))
  - Check and add all DGtal examples in the Examples listing section.
   (Bertrand Kerautret,[#1166](https://github.com/DGtal-team/DGtal/pull/1166))))

- *Base Package*
  - Alias and ConstAlias now raise compilation error when using invalid
   constructor, like from a rvalue reference. Adding ConstAlias in many classes
   that need it.
   (Roland Denis, [#1140](https://github.com/DGtal-team/DGtal/pull/1140))
   (With ITK related compilation fix, Bertrand Kerautret
   [#1153](https://github.com/DGtal-team/DGtal/pull/1153))
  - Moving all base concepts into namespace concepts. Update doc and
   concepts graphs accordingly. (Jacques-Olivier Lachaud, [#1164]
   (https://github.com/DGtal-team/DGtal/pull/1164))

- *IO Package*
  - Viewer3D: improvement of the viewer state record by saving the rendering
   mode. A new setter was also added to desable/enable double face rendering.
   (Bertrand Kerautret [#1166](https://github.com/DGtal-team/DGtal/pull/1162))
  - Viewer3D: add a mode to display ball primitive with OpenGL point instead of
   quadrangulated mesh.
   (Bertrand Kerautret [#1162](https://github.com/DGtal-team/DGtal/pull/1162))
  - Viewer3D: add a new mode to have the light source position defined from the
   camera (default) or from the scene coordinate system (key P to change
   position mode). A new lambertian rendering mode was added.
   (Bertrand Kerautret [#1149](https://github.com/DGtal-team/DGtal/pull/1149))
  - Add the possibility to interact in QGLViewer Viewer3D class with the voxel
   primitive (was limited to surfel). As with surfel, the user may assign integer
   identifiers (OpenGL names) to voxel and callback functions, which are called
   when voxel are selected. The selected elements are now highlighted.
   (Bertrand Kerautret, [#1146](https://github.com/DGtal-team/DGtal/pull/1146))

- *Topology Package*
  - Add pre-calculated look up tables to speed up Object::isSimple calculations.
   (Pablo Hernandez-Cerdan, [#1155](https://github.com/DGtal-team/DGtal/pull/1155))

## Bug Fixes
- *Configuration/General*
  - Simplification of the windows build instructions. (David
   Coeurjolly, [#1160](https://github.com/DGtal-team/DGtal/pull/1160))
  - Various fixes in the documentation (e.g. links to concepts
   pages). (David Coeurjolly,
   [#1161](https://github.com/DGtal-team/DGtal/pull/1161))
  - Fixing issues raised on some algorithms when changing Euclidean ring
   for SpaceND and KhalimskySpaceND. (Jérémy Levallois,
   [#1163](https://github.com/DGtal-team/DGtal/pull/1163))
  - Moving last concepts to concepts:: namespace. (David Coeurjolly,
   [#1193](https://github.com/DGtal-team/DGtal/pull/1193))

- *DEC Package*
  - Fix compatibility with eigen 3.2.8 by changing default index type for sparse matrix.
   (Pierre Gueth, [#1197](https://github.com/DGtal-team/DGtal/pull/1197))
  - Fixing warnings in DiscreteExteriorCalculus and DiscreteExteriorCalculusFactory.
   (Roland Denis, [#1139](https://github.com/DGtal-team/DGtal/pull/1139))

- *Geometry Package*
  - VoronoiCovarianceMeasure: fix dimension-specific code.
   (Roland Denis, [#1145](https://github.com/DGtal-team/DGtal/pull/1145))
  - AlphaThickSegmentComputer: fix segment display errors which could appear
   when displaying a small segment. Fix a non initialized attribute with
   some improvements on bounding box computation with orientation check.
   (B. Kerautret, [#1123](https://github.com/DGtal-team/DGtal/pull/1123))
  - Frechet Shortcut: fix implicit rounding.
   (I. Sivignon, [#1180](https://github.com/DGtal-team/DGtal/pull/1180))

- *Image Package*
  - Fixing issue [#779](https://github.com/DGtal-team/DGtal/issues/779) by
   storing domain with smart pointer in ImageContainerBySTLMap.
   (Roland Denis [#1151](https://github.com/DGtal-team/DGtal/pull/1151))

- *IO Package*
  - Display3D: Fix embedder usage when using default constructor in Debug mode.
   (Roland Denis [#1143](https://github.com/DGtal-team/DGtal/pull/1143))
  - Viewer3D: Fix a problem when the show() method was called at the end of the
   main program (the list creation was not called).
   (Bertrand Kerautret [#1138](https://github.com/DGtal-team/DGtal/pull/1138))
  - Viewer3D: add three new modes for shape rendering (default, metallic and
   plastic). The rendering can be changed by using the key M. The user can
   also choose its own rendering with some setter/getter on the opengl
   lightning/properties. (B. Kerautret,
   [#1128](https://github.com/DGtal-team/DGtal/pull/1128))
  - readers: fix a vol/pgm/raw reading bug occurring on Windows 10 due to the
   different interpretations of end of line \r\n on Window versus \n on
   unix/mac. Changing reading mode with binary mode instead text mode fix
   the issue. (Bertrand Kerautret
   [#1130](https://github.com/DGtal-team/DGtal/pull/1130))
  - Fixing issue [#899](https://github.com/DGtal-team/DGtal/issues/899) in
   all color maps, (David Coeurjolly, Bertrand Kerautret
   [#1134](https://github.com/DGtal-team/DGtal/pull/1134))
  -  GenericReader: include longvol reader in GenericReader for 64 bit images.
   Update the test for 64 bit longvol. (Bertrand Kerautret
   [#1135](https://github.com/DGtal-team/DGtal/pull/1135))
  - Fix the extension removal in Obj filename export in Board3D. (David
   Coeurjolly,[#1154](https://github.com/DGtal-team/DGtal/pull/1154)))
  - Fix issue when drawing DSS with both points and bounding box. (David
   Coeurjolly,[#1186](https://github.com/DGtal-team/DGtal/pull/1186)))

- *Topology Package*
   - Fix wrong starting point for surface tracking in example code
    frontierAndBoundary.cpp.
    (Roland Denis, [#1144](https://github.com/DGtal-team/DGtal/pull/1144))
   - Fix interior/exterior fill methods of topology/helpers/Surfaces class which
    was wrong on 3d and on closed Khalimsky space.
    (Bertrand Kerautret, [#1156](https://github.com/DGtal-team/DGtal/pull/1156))
   - Fix issue [#1168]
    (https://github.com/DGtal-team/DGtal/issues/1168), related to bad
    linear interpolation for binary volume data in
    volMarchingCubes.cpp (Jacques-Olivier Lachaud,
    [#1169](https://github.com/DGtal-team/DGtal/pull/1169))

- *Shape Package*
   - Fix a tubular mesh construction problem (missing faces) which appears
    when the center line is oriented in a main axis direction (in
    createTubularMesh()). Also improves and fixes the face construction.
    (Bertrand Kerautret, [#1157](https://github.com/DGtal-team/DGtal/pull/1157))

# DGtal 0.9.1

## New Features / Critical Changes

- *Configuration/General*
  - A CONTRIBUTING.md file has been added to describe how to contribute
   to the library. (David Coeurjolly,
   [#1112](https://github.com/DGtal-team/DGtal/pull/1112))
  - DGtal requires now to have a C++11 enabled compiler (gcc>4.6,
   clang>2.9, VS14, ...).  This allows us to use new C++11 features in
   DGtal core and to have more generic and reliable code. (David
   Coeurjolly, [#1080](https://github.com/DGtal-team/DGtal/pull/1080))
  - DGtal core now compiles on Microsoft Windows, Visual Studio (only
   VS14 or above). Many issues have been fixed for compatibility with
   'cl' compiler. (David Coeurjolly, Jérémy Levallois,
   [#1074](https://github.com/DGtal-team/DGtal/pull/1074))
  - DGtal with QGLViewer option activated now compiles on Microsoft Windows,
   Visual Studio (only VS14 or above). (Bertrand Kerautret,
   [#1106](https://github.com/DGtal-team/DGtal/pull/1106))

- *Base Package*
  - Traits class for containers in order to probe their category at
   compile time.  (Jacques-Olivier Lachaud,
   [#1079](https://github.com/DGtal-team/DGtal/pull/1079))
  - Generic set operations for arbitrary containers. You may use
   overloaded operators like &, |,  -, ^ on arbitrary containers (list,
   vector, unordered_set, map, etc).  (Jacques-Olivier Lachaud,
   [#1079](https://github.com/DGtal-team/DGtal/pull/1079))

- *Geometry Package*
  - Hull2DHelpers: implementation of the rotating caliper algorithm to compute
   the width (vertical/horizontal or Euclidean) of a convex hull.
   (Bertrand Kerautret, [#1052](https://github.com/DGtal-team/DGtal/pull/1052))
  - MelkmanConvexHull: new reverse method to allow point insertions and convex
   hull computation on both side of a point sequence.
   (Bertrand Kerautret, [#1073](https://github.com/DGtal-team/DGtal/pull/1073))
  - LogScaleProfile: new class to represent a (multi)scale profile e.g. a sequence
   of statistics on digital lengths parameterized by a grid resolution.
   (Backport of the ScaleProfile class of
   [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene) ).
   (Bertrand Kerautret, Jacques-Olivier Lachaud
   [#1075](https://github.com/DGtal-team/DGtal/pull/1075))
  - IteratorCompletion provides iterators and ranges access from a basic set of methods.
   (Roland Denis, [#1029](https://github.com/DGtal-team/DGtal/pull/1029))

- *Image Package*
  - ArrayImageAdapter adds a read-write image adapter from any random-access iterator,
   e.g. from a C-array.
   (Roland Denis, [#1029](https://github.com/DGtal-team/DGtal/pull/1029))

- *Math Package*
  - MultiStatistics: new class to compute different statistics (like
   mean variance, median) on multiple variables.  (Backport of the
   Statistics class of
   [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene) ).
   (Bertrand Kerautret, Jacques-Olivier Lachaud
   [#1076](https://github.com/DGtal-team/DGtal/pull/1076))

- *Topology Package*
  - New class CubicalComplex and functions associated to
   it. Arbitrary cubical complexes can be represented, displayed and
   multiple operations are defined onto them: incidence, closing,
   opening, closure, star, link, interior, boundary, set operations
   and relations, as a collapse operation.
   (Jacques-Olivier Lachaud, [#1079](https://github.com/DGtal-team/DGtal/pull/1079))


## Changes
- *Configuration*
  - Types and classes in helper namespaces ```Z2i``` and ```Z3i``` for
   ```StdDefs.h``` header (2D and 3D digital geometry with
   computations on 32bit integers) are now explicitly instanciated in
   the compiled library. This reduces compilation time when such types
   are used. (David Coeurjolly,
   [#1117](https://github.com/DGtal-team/DGtal/pull/1117))

- *DEC Package*
  - DiscreteExteriorCalculus holds both primal and dual sizes of each cell.
   Subsequent changes have been made to insertSCell.
   (Pierre Gueth [#1082](https://github.com/DGtal-team/DGtal/pull/1082))
  - Convenient static members for KForm :
   KForm::ones(), KForm::zeros() and KForm::dirac(KSpace::Cell).
   (Pierre Gueth [#1082](https://github.com/DGtal-team/DGtal/pull/1082))
- *Base Package*
  - Enabling circulators in SimpleRandomAccessRangeFromPoint.
   (Roland Denis, [#1060](https://github.com/DGtal-team/DGtal/pull/1060))

- *Base*
  - Deprecated OldAlias, OldClone, OldConstAlias have been removed. (David
   Coeurjolly, [#1074](https://github.com/DGtal-team/DGtal/pull/1074))

- *IO*
  - By default, closing a Viewer3D does not save automatically the viewer
   state anymore (in a .qglviewer.xml file). The automatic save can be
   activated by a flag (myAutoSaveState). (Bertrand Kerautret
    [#1088](https://github.com/DGtal-team/DGtal/pull/1088))
  - In the Viewer3D, the light source position is now saved in the
    QGLViewer state file (.qglviewer.xml). (Bertrand Kerautret
    [#1087](https://github.com/DGtal-team/DGtal/pull/1087))
  - Minor improvements of default settings in Viewer3D. (David
   Coeurjolly, [#1066](https://github.com/DGtal-team/DGtal/pull/1066))
  - change the chronological order to display primitives (in the draw
   function) in order to see the cube primitive through the
   transparency of the ball primitives. (Bertrand Kerautret,
   [#1081](https://github.com/DGtal-team/DGtal/pull/1081))
  - New possibility to move the light source direction using the mouse move
   in Viewer3D (with the key SHIFT+CTRL (SHIFT+CMD on mac)). The light source
   direction is now defined according the main coordinate system (no more from
   the camera center).
   (Bertrand Kerautret [#1070](https://github.com/DGtal-team/DGtal/pull/1070))
  - Adding raw I/O capabilities for non integral types and signed integers.
   (Roland Denis [#1084](https://github.com/DGtal-team/DGtal/pull/1084))

- *Shapes Package*
  - New methods to remove faces from a Mesh  or to obtain the barycenter of a
   face.
   (Bertrand Kerautret [#1091](https://github.com/DGtal-team/DGtal/pull/1091))

## Bug Fixes

- *Configuration/General*
  - catch unit test framework upgraded to the develop version. (David
 Coeurjolly, [#1055](https://github.com/DGtal-team/DGtal/pull/1055))
  - Fixing boost include path issue when building tools using DGtal and
   its cmake DGtalConfig.cmake. (David Coeurjolly,
   [#1059](https://github.com/DGtal-team/DGtal/pull/1059))
  - Fixing parenthese warnings in Catch. Waiting for an official fix.
   (Roland Denis, [#1069](https://github.com/DGtal-team/DGtal/pull/1069))
  - Fix constness in selfDisplay and operator<<.  (Pierre Gueth
   [#1082](https://github.com/DGtal-team/DGtal/pull/1082))
  - DGtal cmake configuration scripts are now installed in the
   ```${PREFIX_PATH}/lib/DGtal/``` folder on linux systems (when
   running ```make install``` command). The documentation is copied to
   the folder ```${PREFIX_PATH}/share/DGtal/html/```. This fixes issue
   [#1095](https://github.com/DGtal-team/DGtal/issues/1095). (David
   Coeurjolly,
   [#1103](https://github.com/DGtal-team/DGtal/issues/1103))
  - Fix for swapped coordinates in TangentFromDSS2DFunctor. (Kacper
   Pluta,
   [#1083](https://github.com/DGtal-team/DGtal/issues/1083))
  - Update of the README.md page. (David Coeurjolly,
   [#1109](https://github.com/DGtal-team/DGtal/issues/1109))

- *Base Package*
  - Fix wrong initialization of reverse iterators in
   SimpleRandomAccess(Const)RangeFromPoint.  (Roland Denis,
   [#1060](https://github.com/DGtal-team/DGtal/pull/1060))

- *Geometry Package*
  - Fix pseudo-random number generator in KanungoNoise (David
   Coeurjolly,
   [#1078](https://github.com/DGtal-team/DGtal/pull/1078))

- *IO Package*
  - Fix line export in Board3D.
   (Bertrand Kerautret [##1119](https://github.com/DGtal-team/DGtal/pull/1119))
  - Fix viewer tests including qt4 headers even with configuring WITH_QT5=ON.
   (Pablo Hernandez-Cerdan, [#1100](https://github.com/DGtal-team/DGtal/pull/1100))
  - Fix Viewer3D axis display when they are included in a transparent element.
   (issue #873)
   (Bertrand Kerautret [##1108](https://github.com/DGtal-team/DGtal/pull/1108)))


# DGtal 0.9

## New Features / Critical Changes
- *Geometry Package*

- New segment computer allowing the recognition of thick digital segments,
  adapted to noisy contours (from a given thickness parameter). The current
  implementation (mainly a backport from imagene) is a model of
  CForwardSegmentComputer with a ParallelStrip primitive. This primitive is
  similar to the blurred segment of [Debled-Rennesson etal 2005] with isothetic
  thickness. It is also an implementation of the alpha-thick segment of Alexandre
  Faure and Fabien Feschet.
  (Bertrand Kerautret,  [#963](https://github.com/DGtal-team/DGtal/pull/963))


- *Configuration/General*
  - Continuous integration enabled on both linux and macosx
   systems. Furthermore, the nightly build documentation is
   automatically deployed.  (David Coeurjolly,
   [#955](https://github.com/DGtal-team/DGtal/pull/955))
  - New unit test framework based on
   [catch](https://github.com/philsquared/Catch). Catch allows to
   design quick and efficient unit tests with nice trace
   outputs. (David Coeurjolly,
   [#1019](https://github.com/DGtal-team/DGtal/pull/1019))
  - Documentation added for Catch. (David Coeurjolly,
   [#1042](https://github.com/DGtal-team/DGtal/pull/1042))


- *Kernel*
  - New template class DigitalSetlByAssociativeContainer allows to
   define digital sets from any associative container of the STL. For
   instance, using std::unordered_set (c++11) or boost::unordered_set (hash
   function based containers), speed-up up to 40% can be measured when
   processing digital sets. (David Coeurjolly,
   [#1023](https://github.com/DGtal-team/DGtal/pull/1023)
  - By default, Z2i::DigitalSet, Z3i::DigitalSet and digital set from
   DigitalSetSelector use the new hash function based
   container. (David Coeurjolly,
   [#1023](https://github.com/DGtal-team/DGtal/pull/1023)
  - Specializations of std::hash (c++11) and boost::hash to define a hash
   functions on DGtal points. (David Coeurjolly,
   [#1023](https://github.com/DGtal-team/DGtal/pull/1023)

## Changes

- *DEC Package*
  - Coherent signed cells support allows lower dimension manifold embedding.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - OppositeDuality struct allows generic hodge and laplace definition.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - Easy k-form and vector field transversal using .length() and .getSCell().
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - Unified operators interface :
   .hodge<order, duality>() replace primalHodge<order>() and dualHodge<order>(),
   .laplace<duality>() replace primalLaplace() and dualLaplace().
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - New antiderivative<order, duality>() operator.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - New flatDirectional<duality, direction>() and sharpDirectional<duality,
   direction>() operators defined as flat(vector_field_along_direction) and
   sharp(1-form).extractZeroForm(direction). (Pierre Gueth
   [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - DiscreteExteriorCalculus<dim_embedded, dim_ambient, Backend>
   takes 2 dimension template parameters for embedding
   manifold in ambient euclidean space.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - Basic openmp support for derivative computation.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - New propagation example and extended embedding tests.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - Improved operator generation using new CSparseMatrix concepts.
   (Pierre Gueth [#1007](https://github.com/DGtal-team/DGtal/pull/1007))
  - DEC constructors are replaced by static factory functions:
   DiscreteExteriorCalculusFactory::createFromDigitalSet and
   DiscreteExteriorCalculusFactory::createFromNSCells.
   (Pierre Gueth [#1008](https://github.com/DGtal-team/DGtal/pull/1008))
  - Mutable iterator on DiscreteExteriorCalculus.
   (Pierre Gueth [#1008](https://github.com/DGtal-team/DGtal/pull/1008))
  - Unary minus operators for k-forms, vector fields and linear operators.
   (Pierre Gueth [#1020](https://github.com/DGtal-team/DGtal/pull/1020))
  - Introduction of .updateIndexes() that needs to be called after any
   call to .insertSCell() or .eraseCell().
   (Pierre Gueth [#1020](https://github.com/DGtal-team/DGtal/pull/1020))
  - Transpose of linear operators.
   (Pierre Gueth [#1020](https://github.com/DGtal-team/DGtal/pull/1020))
  - Intensity operator on vector fields.
   (Pierre Gueth [#1020](https://github.com/DGtal-team/DGtal/pull/1020))
  - Reorder operators to remap indexes.
   (Pierre Gueth [#1020](https://github.com/DGtal-team/DGtal/pull/1020))

- *Geometry Package*
  - New EstimatorCache class to cache quantities estimated by a
   surfel local estimator. (David Coeurjolly,
   [#927](https://github.com/DGtal-team/DGtal/pull/927))
  - New digital surface local estimator that computes a sphere
  fitting. It requires to have the Patate library installed (and
  WITH_PATATE=true): http://patate.gforge.inria.fr/html/. See
  SphereFittingEstimator (David Coeurjolly,
  [#929](https://github.com/DGtal-team/DGtal/pull/929))
  - Algorithm to compute the union of two DSSs in logarithmic time
	(Isabelle Sivignon,
	[#949](https://github.com/DGtal-team/DGtal/pull/949))
  - InexactPredicateLpSeparableMetric class is now templated by an
   EuclideanRing type. (David Coeurjolly,
   [#1017](https://github.com/DGtal-team/DGtal/pull/1017))
  - Main example files of geometry/curves are introduced in the list of examples
   and briefly described.
   (Tristan Roussillon, [#1026](https://github.com/DGtal-team/DGtal/pull/1026))
  - New algorithms to compute the convex hull of planar point sets.
   (Tristan Roussillon, [#1028](https://github.com/DGtal-team/DGtal/pull/1028))
  - Lambda maximal segment tangent direction estimator 2D/3D: LambdaMST2D, LambdaMST3D.
   A fast tangent direction estimator which uses maximal digital straight segments.
   (Kacper Pluta, [#1021](https://github.com/DGtal-team/DGtal/pull/1021))
  - Segmentation of 3D digital curves by a combination of the segmentations of its 2D
   projections onto 2D base planes: XY, XZ, YZ. Notice that, only valid projections
   are used. By valid one understands that there are no two 3D points which are projected
   onto the same 2D point. A segment is computed as long as is extendable and at least
   two projections are valid.
 : NaiveDSS3DComputer.
   (Kacper Pluta, [#1021](https://github.com/DGtal-team/DGtal/pull/1021))

- *Math Package*
  - Utilities added (OrderedLinearRegression) to perform sequential
   linear model estimation of scalar data. (David Coeurjolly, Jérémy
   Levallois [#935](https://github.com/DGtal-team/DGtal/pull/935),
   backport from imagene)
  - New linear algebra concepts: CDenseVector, CDenseMatrix, CSparseMatrix.
   (Pierre Gueth [#1007](https://github.com/DGtal-team/DGtal/pull/1007))

- *Image Package*
  - Adding copy between images of different types. (Roland Denis [#1001]
   (https://github.com/DGtal-team/DGtal/pull/1001))

- *IO Package*
  - Fix RawWriter and RawReader. Added templated generic RawReader::importRaw
   and RawWriter::exportRaw.
   (Pierre Gueth [#1010](https://github.com/DGtal-team/DGtal/pull/1010))
  - New 2D DEC board style with orientated cells.
   (Pierre Gueth [#977](https://github.com/DGtal-team/DGtal/pull/977))
  - Limited interaction added to QGLViewer Viewer3D class. The user
   may assign integer identifiers (OpenGL names) to surfels and
   callback functions, which are called when surfels are
   selected. (Jacques-Olivier Lachaud
   [#942](https://github.com/DGtal-team/DGtal/pull/942))
  - Balls can be exported to OBJ in Board3D and ball resolution can now
   be specified in Viewer3D and Board3D (David Coeurjolly,
   [#945](https://github.com/DGtal-team/DGtal/pull/945))
  - Viewer3d cleanings with better organisation through the
   separation of all code generating the GL lists. (Bertrand Kerautret)
  ([#945](https://github.com/DGtal-team/DGtal/pull/945))
  - Operators added to perform computations on Color objects (addition,
   substraction scaling...). Color is now CopyConstructible and
   Assignable (David Coeurjolly
   [#940](https://github.com/DGtal-team/DGtal/pull/940))
  - Improvement of memory footprint of DGtal::Color (David Coeurjolly,
   [#961](https://github.com/DGtal-team/DGtal/pull/961))
  - New colormap adapter to add ticks/iso-contours (regularly spaced or
   specified by the user) to a given colormap. (David Coeurjolly,
   [#987](https://github.com/DGtal-team/DGtal/pull/987))
  - New flag (-DWITH_QT5) enables QT5 support in libqglviewer. (Nicolas
   Aubry, [#983](https://github.com/DGtal-team/DGtal/pull/983))
  - Board2D now supports quadratic Bezier curve drawing. (Tristan Roussillon,
   [#1002](https://github.com/DGtal-team/DGtal/pull/1002))
  - MeshWriter class can now export OBJ file including colors.
   (Bertrand Kerautret, [#1016](https://github.com/DGtal-team/DGtal/pull/1016))
  - Viewer3D: Shift-L / L key binding added to save and restore camera settings.
   (Bertrand Kerautret, [#1024](https://github.com/DGtal-team/DGtal/pull/1024))
  - Viewer3D:  change the chronological order to diplay primitives (in the draw
   function) in order to see see textured image primitives through the
   transparency of other 3D primitives. (Bertrand Kerautret,
   [#1041](https://github.com/DGtal-team/DGtal/pull/1041))


- *Kernel Package*
- HyperRectDomain can now be empty (lowerBound == upperBound + diagonal(1)).
    Warning about the use of lexicographical order in comparison operators of
    PointVector. (Roland Denis,
    [#996](https://github.com/DGtal-team/DGtal/pull/996))
   - Adds generic linearization (point to index) and reverse process (index to
    point), specialized for HyperRectDomain. (Roland Denis,
    [#1039](https://github.com/DGtal-team/DGtal/pull/1039))
  - HyperRectDomain can now be empty (lowerBound == upperBound +
    diagonal(1)). Warning about the use of lexicographical order in
    comparison operators of PointVector. (Roland Denis,
    [#996](https://github.com/DGtal-team/DGtal/pull/

- *Shapes Package*
  - Adds a vertex Iterator in the Mesh class in addition to the
   ConstIterator and adds a new method to change the color of a
   specific face. (Bertrand Kerautret,
   [#937](https://github.com/DGtal-team/DGtal/pull/937))
  - New methods to generate basic 3D tubular meshes and height
   fields. New mesh module documentation added. (Bertrand Kerautret,
   [#969](https://github.com/DGtal-team/DGtal/pull/969))
  - Refactoring of CSG operations on Euclidean / Digital shapes to easily
   combine several operations.
   EuclideanShapesUnion, EuclideanShapesIntersection and
   EuclideanShapesMinus are now deprecated. Use EuclideanShapesCSG
   instead.
   DigitalShapesUnion, DigitalShapesIntersection and
   DigitalShapesMinus are now deprecated. Use DigitalShapesCSG
   instead. (Jérémy Levallois
   [#962](https://github.com/DGtal-team/DGtal/pull/962))
  - Add various methods in the Mesh class to get the bounding box, to
   change the mesh scale or to subdivide triangular faces. (Bertrand
   Kerautret, [#990](https://github.com/DGtal-team/DGtal/pull/990) and
   [#992](https://github.com/DGtal-team/DGtal/pull/992))
  - New copy constructor and copy operator on Mesh object (and
   documentation added about vertex ordering for obj format).
   (Bertrand Kerautret,
   [#976](https://github.com/DGtal-team/DGtal/pull/976))

- *Arithmetic Package*
  - Algorithm to compute the fraction of smallest denominator in
	between two irreducible fractions (Isabelle Sivignon
	[#949](https://github.com/DGtal-team/DGtal/pull/949))

## Bug Fixes

- *Configuration*
   - Removing code coverage with coverall.io (David Coeurjolly,
  [1040](https://github.com/DGtal-team/DGtal/pull/1032)).
   - Forces Eigen 3.2.1 minimum (for a bug fix).  (Jacques-Olivier
    Lachaud, [1032](https://github.com/DGtal-team/DGtal/pull/1032)).
   - Fix issue #925, detection of Eigen3 (3.1 minimum) and also issue
    #924, DGtal configuration file when using Eigen3.  (Jacques-Olivier
    Lachaud, [#926](https://github.com/DGtal-team/DGtal/pull/926))
  - Backport of changes in google/benchmarck API for micro-benchmarking
   (David Coeurjolly, [#1014](https://github.com/DGtal-team/DGtal/pull/1014))
  - New travis configuration file to enable new travis Docker based
   container system (David Coeurjolly,
   [#1030](https://github.com/DGtal-team/DGtal/pull/1030))
  - Various fixes of compiler warnings due to unused paramters (David
   Coeurjolly, Roland Denis,
   [#1034](https://github.com/DGtal-team/DGtal/pull/1030))


- *Base Package*
  - Fix bug with LabelledMap copy constructor and copy iterator. (Roland
   Denis, [#973](https://github.com/DGtal-team/DGtal/pull/973))
  - Fix bug with Labels iterator when first index is set (Roland Denis,
 [#972](https://github.com/DGtal-team/DGtal/pull/972))
  - Iterator category fix for boost > 1.57 (David Coeurjolly,
 [#938](https://github.com/DGtal-team/DGtal/pull/938))
  - Cleanup of DGtal namespaces (David Coeurjolly,
 [#993](https://github.com/DGtal-team/DGtal/pull/993))


- *Geometry Package*
  - Fix bug occuring in the computation of the Faithful Polygon (class FP)
   in the closed case, ie. with circulators.
   (Tristan Roussillon, [#939](https://github.com/DGtal-team/DGtal/pull/939))
  - Fixing DSS based length estimator on open curves. (David
   Coeurjolly, [#941](https://github.com/DGtal-team/DGtal/pull/941))
  - Fix bug of method ArithmeticalDSL::getPoint with negative values
   of positions as input arguments.
   (Tristan Roussillon, [#944](https://github.com/DGtal-team/DGtal/pull/944))
  - Fix too restrictive asserts of methods
	ArithmeticalDSSConvexHull::smartCH and
	ArithmeticalDSSConvexHull::smartCHNextVertex to enable negative
	positions as input arguments. (Isabelle Sivignon,
	[#950](https://github.com/DGtal-team/DGtal/pull/950))
  - Fix Bezout Vector computation (Isabelle Sivignon,
 [#948](https://github.com/DGtal-team/DGtal/pull/948))
  - Fix issues with SphereFitting and TensorVoting local estimators on
   digital surfaces (Jérémy Levallois, David Coeurjolly
   [#970](https://github.com/DGtal-team/DGtal/pull/970))

- *IO Package*
  - Performance improvement of color managment in Display3D, Board3D
   and Viewer3D: no more "createNew...List" when setting a new
   color. (David Coeurjolly,
   [#958](https://github.com/DGtal-team/DGtal/pull/958))
  - Radius and resolution of balls have been fixed when used to
   represent a 3D point in grid mode (David Coeurjolly,
   [#978](https://github.com/DGtal-team/DGtal/pull/978))
  - Change in the mesh export in OFF format: now it tries by default to export
   colors (if stored). (Bertrand Kerautret,
   [#985](https://github.com/DGtal-team/DGtal/pull/985))
  - Bugfix in quad visualization in BoardD3D and Viewer3D (David
   Coeurjolly, [#980](https://github.com/DGtal-team/DGtal/pull/980))
  - Fix warnings message of std::abs in Display3D.    (Bertrand Kerautret,
   [#991](https://github.com/DGtal-team/DGtal/pull/991))
  - Fix memory leaks present in the Viewer3d.  (Bertrand Kerautret,
   [#995](https://github.com/DGtal-team/DGtal/pull/995))
  - Fix issues in OBJ color export when exporting voxels. (David
   Coeurjolly, [#1022](https://github.com/DGtal-team/DGtal/pull/1022))
  - Fix compilation issue on gentoo system related to MeshWriter
   (gcc version 4.9.2-r2). (Van Tho Nguyen,
   [#1035](https://github.com/DGtal-team/DGtal/pull/1035))
  - Fix deprecated usage of setMouseBindingDescription with QGLViewer >= 2.5.0.
   (Roland Denis, [#1036](https://github.com/DGtal-team/DGtal/pull/1036))

- *Kernel Package*
   - BasicDomainSubSampler can now handle non 0 origin point. This update also
    correct the search of point which are outside the source domain (it is now
    checked in testBasicPointFunctors). (Bertrand Kerautret,
    [989](https://github.com/DGtal-team/DGtal/pull/989)).

- *Topology  Package*
   - Fix loop bug in extractAllConnectedSCell of Surfaces from helpers.
    (Bertrand Kerautret, [994](https://github.com/DGtal-team/DGtal/pull/994)).

- *DEC  Package*
  - Fix missing include in testEigenSolver.
    (Jacques-Olivier Lachaud,
    [1032](https://github.com/DGtal-team/DGtal/pull/1032)).


# DGtal 0.8


## New Features / Critical Changes

- *General*
  - This Changelog has been ported to MarkDown (David Coeurjolly,
   [#846](https://github.com/DGtal-team/DGtal/pull/846))
  - The DGtal main website is now http://dgtal.org

 - Global refactoring of base functors (David Coeurjolly,
   [#861](https://github.com/DGtal-team/DGtal/pull/861))
    - BasicFunctor functors have been moved to functors:: namespace.
    - DefaultFunctor has been renamed functors::Identity.
    - xxxFunctor have been renamed to xxx.

  - Moving graph, topology, geometry/estimation concepts into
   namespace concepts::, also moving some functors into namespace
   functors:: (Jacques-Olivier Lachaud,
   [#912](https://github.com/DGtal-team/DGtal/pull/912)).

- *DEC Package*
  - DGtal 0.8 contains the first release of the Discrete Exterior
   Calculus Package. DEC provides an easy and efficient way to
   describe linear operator over various structure. Basic operators,
   such as Hodge duality operator or exterior derivative, can be
   combined to create classical vector analysis operator such as
   gradient, curl and divergence. (Pierre Gueth,
   [#877](https://github.com/DGtal-team/DGtal/pull/877))


- *Geometry Package*
  - Add digital nD Voronoi Covariance Measure support, as well as
  digital geometric estimators based on it. Add tests and examples of
  feature detection with VCM. (Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803))

  - Add Integral Invariant estimators so that they meet the concept of
  surface local estimator. Add geometric functors to define easily all
  the geometric estimators that can be built from the volume and
  coariance matrix. Previous estimators (IntegralInvariantMeanCurvatureEstimator
  and IntegralInvariantGaussianCurvatureEstimator) are removed. Please use
  the new ones instead. (Jeremy Levallois, Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803)
  [#856](https://github.com/DGtal-team/DGtal/pull/856)
  [#893](https://github.com/DGtal-team/DGtal/pull/893))

  - Various geometric predicates are now available in order to test the
  orientation of three points in the planes. Most classes are template
  classes parametrized by a type for the points (or its coordinates)
  and an integral type for the computations. They always return an
  exact value (or sign), provided that the integral type used for the
  computations is well chosen with respect to the coordinates of the
  points. Some implementations do not increase the size of the input
  integers during the computations. (Tristan Roussillon,
  [#755](https://github.com/DGtal-team/DGtal/pull/755))

  - Logarithmic construction of an arithmetical DSS of minimal
   parameters from a bounding DSL and two end points (ctor of
   ArithmeticalDSS) (Tristan Roussillon,
   [#819](https://github.com/DGtal-team/DGtal/pull/819))

  - Proof-of-concept that path-based norms can be implemented in a
   separable approach using logarithmic cost predicates
   (experimental::ChamferNorm2D). (David Coeurjolly,
   [#898](https://github.com/DGtal-team/DGtal/pull/898))

  - Logarithmic construction of an arithmetical DSS of minimal
   parameters from a bounding DSS (of known leaning points)
   and two end points (ctor of
    ArithmeticalDSS) (Tristan Roussillon,
    [#914](https://github.com/DGtal-team/DGtal/pull/914))

  - Feature extraction algorithm from Tensor Voting.(Jérémy Levallois,
   David Coeurjolly,
   [#895](https://github.com/DGtal-team/DGtal/pull/895))

  - Ray shooting intersection predicates (ray-triangle, ray-quad,
   ray-surfel) added in geometry/tools (David Coeurjolly,
   [#904](https://github.com/DGtal-team/DGtal/pull/904))


- *IO Package*
   - Now VolReader/VolWriter and LongvolReader/LongvolWriter support the
   usage of Center-(X,Y,Z) parameters, as described in Vol file
   specification. (Jérémy Levallois,
   [#879](https://github.com/DGtal-team/DGtal/pull/879))

- *Math Package*

     - New classes to compute nD eigen decomposition of symmetric
      matrix (class EigenDecomposition).  Add tests. (Jacques-Olivier
      Lachaud, #803)
     - Simple Linear Regression tool added (backport from
      imagene). (David
      Coeurjolly, [#794](https://github.com/DGtal-team/DGtal/pull/794))

- *Kernel package*
   - BasicPointFunctors functors have been moved in the functors::
    namespace (David Coeurjolly,
    [#863](https://github.com/DGtal-team/DGtal/pull/863))

- *For developpers*
     - Google Benchmark can be enabled to allow micro-benchmarking in
         some DGtal unit tests (https://github.com/google/benchmark)
         (David Coeurjolly,
         [#790](https://github.com/DGtal-team/DGtal/pull/790))

- *Images*
   - Classes to perform rigid transformations of 2D and 3D images
     (Kacper Pluta,
     [#869](https://github.com/DGtal-team/DGtal/pull/869))

## Changes

- *Base Package*
  - Add comparison operators in variants of CountedPtr. Improve
   coverage of these classes and fix compilation problem
   (Jacques-Olivier Lachaud)
  - Update doc of CountedPtr, CountedPtrOrPtr and
   CountedConstPtrOrConstPtr. Add asserts. Add tests. Fix issue 773
   (https://github.com/DGtal-team/DGtal/issues/773). (Jacques-Olivier
   Lachaud, [#894](https://github.com/DGtal-team/DGtal/pull/894)).
  - XXXOutputRangeYYY classes are now called
   XXXRangeWithWritableIteratorYYY (Tristan Roussillon,
   [#850](https://github.com/DGtal-team/DGtal/pull/850)).

- *Geometry Package*
  - Fix and add concept of CSurfelLocalEstimator and related ground
  truth estimators for implicit polynomial shapes
  (TrueDigitalSurfaceLocalEstimator). (Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803))
  - Random-access iterators added in ArithmeticalDSL. (Tristan
   Roussillon, [#801](https://github.com/DGtal-team/DGtal/pull/801))
  - Updates in Metric concepts: better and simpler concept structure
   and a new adapter to adapt any euclidean metric to a digital one
   (with values on Z) (David Coeurjolly,
   [#870](https://github.com/DGtal-team/DGtal/pull/870)
  - CubicalSudivision has been renamed SpatialCubicalSubdivision and
   moved to "geometry/tools" (David Coeurjolly,
   [#862](https://github.com/DGtal-team/DGtal/pull/862))

- *IO Package*
   - Better handling of materials in Board3D and OBJ exports. (David
    Coeurjolly,
    [#784](https://github.com/DGtal-team/DGtal/pull/784))
   - New 'basic' display mode for surfels (oriented or not), useful for
    large digital surface displays (quads instead of 3D prism)
    (Bertrand Kerautret,
    [#783](https://github.com/DGtal-team/DGtal/pull/783))
   - New clear() method to subclasses of Display3D (Viewer3D and
    Board3D) to clear the current drawning buffer. (Kacper Pluta,
    [#807](https://github.com/DGtal-team/DGtal/pull/807))
   - New draw() method for 3D display models (Viewer3D and Board3D) to
    display surfels with prescribed normal vectors (David Coeurjolly,
    [#802](https://github.com/DGtal-team/DGtal/pull/802)).
   - When exporting an 3D visualization to OBJ, a new option will
    rescale the geometry to fit in [-1/2,1/2]^3. (David Coeurjolly,
    [#820](https://github.com/DGtal-team/DGtal/pull/820))
   - New raw import/export for 32 bits images (Bertrand Kerautret,
	[#877](https://github.com/DGtal-team/DGtal/pull/876))

- *Kernel Package*

   - New functor DomainSubSampler allowing to apply different
    samplings with larger or smaller size on N dimensional domain. New tests
    and examples are given for 2D and 3D images (Bertrand Kerautret,
    [825](https://github.com/DGtal-team/DGtal/pull/825) and
    [882](https://github.com/DGtal-team/DGtal/pull/882)).

- *Shapes Package*
   - Shape concepts have been moved to concepts:: namespace (David
  Coeurjolly, [#871](https://github.com/DGtal-team/DGtal/pull/871))

- *Topology Package*
   - Surfaces::findABell accepts now arbitrary pair of points (Jacques-Olivier
    Lachaud, David Coeurjolly,
    [#851](https://github.com/DGtal-team/DGtal/pull/851))



## Bug Fixes


- *Base Package*

  - Fixing issue on Circulator/IteratorFunctions (related to #770 on
    MacOS).

- *Kernel Package*
  - BinaryPointPredicate is now specialized for DGtal::AndBoolFct2 and
    DGtal::OrBoolFct2 in order to guarantee that the second computation
    is not performed when the first point predicate return false (resp. true)
    with DGtal::AndBoolFct2 (resp. DGtal::OrBoolFct2) (Tristan Roussillon
    [#852](https://github.com/DGtal-team/DGtal/pull/852)).

- *Geometry Package*
  - Bug fix in PowerMap construction. (David Coeurjolly,
    [#814](https://github.com/DGtal-team/DGtal/pull/814))
  - Bug fix in 3d display of StandardDSS6Computer (Tristan Roussillon
    [#854](https://github.com/DGtal-team/DGtal/pull/854))

- *Topology Package*
  - small fix in ImplicitDigitalSurface. (Jacques-Olivier Lachaud,
    [#803](https://github.com/DGtal-team/DGtal/pull/803))
  - fix examples volTrackBoundary and volScanBoundary for DEBUG mode
    (Jacques-Olivier Lachaud, David Coeurjolly,
    [#851](https://github.com/DGtal-team/DGtal/pull/851))
  - New methods to fill the interior/exterior of digital contours
    (in the Surface class of topology/helpers).  (Bertrand Kerautret
    [#827](https://github.com/DGtal-team/DGtal/pull/827))


- *Graph Package*
  - fix examples volDistanceTraversal for DEBUG mode (Jacques-Olivier Lachaud,
    David Coeurjolly, [#851](https://github.com/DGtal-team/DGtal/pull/851))

- *Image Package*
  - Fixing template types in ImageAdapter (David Coeurjolly,
    [#835](https://github.com/DGtal-team/DGtal/pull/835))
  - Fixing image thresholders (SimpleThresholdForegroundPredicate and
    IntervalForegroundPredicate) which require CConstImage instead of
    CImage (David Coeurjolly,
    [#843](https://github.com/DGtal-team/DGtal/pull/843))

- *IO*
  - Bug fix for reading PGM(P2) 3D. (Kacper Pluta,
   [#853](https://github.com/DGtal-team/DGtal/pull/853))
  - Renaming BasicColorToScalarFunctors namespace to functors:: (David
    Coeurjolly,  [#857](https://github.com/DGtal-team/DGtal/pull/857))
  - Fix OpenGL warnings by redefining openGL primitive (glSphere) (Bertrand
    Kerautret [#981](https://github.com/DGtal-team/DGtal/pull/891))

=== DGtal 0.7 ===

*General*

  - Unit tests build is now disabled by default (to turn it on, run cmake with "-DBUILD_TESTING=on")

  - The "boost program option library" dependency was removed.

  - DGtal needs boost >= 1.46.

  - Thanks to new compiler warning option (-Wdocumentation), the doxygen documentation has been considerably improved.

*Base Package*

  - Complete rewriting of Clone, Alias and ConstAlias
    classes. Parameter passing is now documented with a standardized
    method to determine parameters unambiguously. Associated classed
    CowPtr, CountedPtrOrPtr and CountedConstPtrOrConstPtr are now used
    in conjunction with the previous classes.

  - Few improvments in Clock and Trace base classes.

*Kernel Package*

  - Two initialisation methods (initRemoveOneDim and initAddOneDim)
    for the Projector Functor from the BasicPointFunctors class in
    order to simplify the slice images (with example and test in 2D
    slice image extraction from 3D volume file).

  - New basic functors:
	- SliceRotator2D: to rotate 2D Slice images from 3D volume.
	- Point2DEmbedderIn3D: a simple functor to embed in 3d a 2d points
	  (useful to extract 2D image from 3D volume).

  - Sets have been updated to own their domain with a copy-on-write pointer,
    in order to avoid some inconsistencies.

*Topology Package*

  - Fixing bugs in Object::isSimple for some digital
    topologies. Speed of Object::isSimple has been improved. Homotopic
    thinning is much faster (even without a precomputed simplicity
    table).

  - Objects have been updated to use Clone services.

*Geometry Package*

  - New classes to deal with arithmetical digital straight segments.
    Now the representation of the primitives and their recognition
    along a discrete structure are separated. The unique class
    ArithmeticalDSS,  which was a segment computer, has been replaced by
    mainly three classes: ArithmeticalDSL, ArithmeticalDSS and
    ArithmeticalDSSComputer. This is described in a doc page of the geometry
    package. Note that Backward/Forward suffixes have been renamed into
    Back/Front. Moreover, get prefixes for data members accessors have been
    removed.

  - Generic adapter to transform a metric (model of CMetric) with
    monotonic (see doc) properties to a separable metric (model of
    CSeparableMetric) which can be used in
    VoronoiMap/DistanceTransformation algorithms.

  - New possibility to access the 3 2D ArithmeticDSS object within an
    ArithmeticDSS3d.

  - New local estimator adapter to make easy implementation of locally defined
    differential estimator on digital surfaces.

  - New documentation on local estimators from digital surface
    patches and surfel functors. New normal vector estimator from
    weighted sum of elementary surfel normal vectors added.

  - With an optional binding with CGAL and Eigen3, new curvature and
    normal vector estimators have been added. For instance, you can
    now estimate curvature from polynomial surface fitting (Jet
    Fitting) and Monge forms.

  - Minor improvements in the spherical accumulator.

  - Improvement of integral invariant estimators (better memory footprint,
	...).
    They also allow to estimate principal curvatures using Covariance matrix.
    Covariance matrix is also "masks" based, so the computation is efficient.

  - New algorithms to compute the minimal characteristics of a
    Digital Straight Line subsegment in logarithmic time using local
    convex hulls or Farey Fan. Also works when the DSL
    characteristics are not integers.

  - Chord algorithm for (naive) plane recognition and width computation.

  - New organization for computing primitives. Introduction of the concept
    of PrimitiveComputer and specialization. COBA algorithm and Chord
    algorithm are now models of AdditivePrimitiveComputer.

  - Introduction of the primitive ParallelStrip, computed by COBA and Chord
    algorithms

  - New documentation for planarity decision, plane recognition and width
    computation.
    Quantitative and qualitative evaluation of COBA and Chord algorithm.

  - Bug fix in COBA algorithm when extending an empty computer with a group of
    points.

  - add standard plane recognition with adapter classes both for COBA and
    Chord algorithm.

*Shape Package*

  - The class MeshFromPoints was transformed into Mesh (more from
    shapes/fromPoints to shapes/ directory), iterators on mesh
    points and mesh face.

*Topology Package*

  - The class SCellToMidPoint is now deprecated. Use CanonicSCellEmbedder
    instead to map a signed cell to its corresponding point in the Euclidean
    space

*IO Package*

  - Complete refactoring of 3D viewers and boards (Viewer3D, Board3DTo2D).
  - New Board3D to export 3D displays to OBJ 3D vector format.
  - A new display of 2D and 3D image in Viewer3D.
  - New reader: HDF5 file with 2D image dataset(s) (8-bit with palette and
    24-bit truecolor with INTERLACE_PIXEL).
  - New GenericReader and Generic Writer for both 2D, 3D and ND images.
  - Adding a Table Reader to extract objets given in a specific column from a
    text file.
  - Adding missing PPM Reader.
  - Adding missing DICOM reader (with ITK library)
  - Adding ITK reader and ITK writer
  - OpenInventor (SOQT/Coin3D) based viewer has been removed (please consider
    release <=0.6 if interested).

*Image Package*

  - New concepts : CImageFactory to define the concept describing an
    image factory and CImageCacheReadPolicy/CImageCacheWritePolicy
    to define the concept describing cache read/write policies.

  - New classes : ImageFactoryFromImage to implement a factory to
    produce images from a "bigger/original" one according to a given
    domain, ImageCache to implement an images cache with 'read and
    write' policies, TiledImageFromImage to implement a tiled image
    from a "bigger/original" one.

  - ImageContainerByITKImage complies with CImage.
    The container has been moved from the DGtal::experimental namespace to
    the main DGtal namespace.

*Graph Package*

  - New graph visitor, which allows to visit a graph according to
    any distance object (like the Euclidean distance to some point).

*Math Package*

  - add Histogram class and CBinner concept.
  - add math concepts diagram.


=== DGtal 0.6 ===

 *General*
  - Multithread capabilities via OpenMP are now detected during DGtal
    build. Example of usage can be found in the Volumetric module.

 *Documentation*
  - update documentation for boost concepts, so that subconcepts are
    displayed and html reference pages are pointed.
  - package/module documentation files are now in their associated
    package folder (e.g. kernel/doc/ for kernel package related
    documentation pages). The "make doc" command (or "make dox", see
    below) generates the documentation in the "html/" sub-folder of your
    current build folder.
  - latex citations within doxygen documents are now working

 *Base Package*
  - correct concept checks for some range concepts.
  - Statistic class moved to math package

 *Kernel Package*
  - digital sets are now also point predicates, update of
    DigitalSetDomain accordingly. As a consequence, SetPredicate is
    now deprecated.
  - exposed Compare template parameter of underlying std::set in
    DigitalSetBySTLSet class.

  - new documentation for module digital sets.

 *Arithmetic Package*
  - new class for representing lattice polytopes in 2D (with cut
    operations)
  - bugfix in LighterSternBrocot::Fraction
  - bugfix in ArithmeticalDSS (thanks, Kacper)

 *Image Package*
  - Update on image writers (no colormap required for scalar only writers).
    Documentation updated.
  - New image adapters to adapt both domains and values of an image
    (ImageAdapter and ConstImageAdapter).
  - several enhancements of the main image concept and its image
    container models

 *Geometry Package*
  - New primitives for digital plane recognition. Naive planes, and
    more generally planes with arbitrary axis-width can be detected
    and recognized incrementally. Based on a COBA algorithm
    implementation, which uses 2D lattice polytopes.
  - Fréchet segment computer added to compute bounded simplifications of
    digital curves for instance.
  - Complete rewritting of volumetric tools by separable processes:
    new generic algorithms (VoronoiMap, PowerMap) and metric
    concepts hierarchy (l_2, l_p, ...p) to efficiently compute
    DistanceTransformation, ReverseDistanceTransformation and
    preliminary medial axis extraction.
  - Separable volumetric tools are now multithread using OpenMP.
  - New curvature estimator in 2D/3D based on integral invariants
    (both mean and gaussian curvatures in 3D).

 *Shape Package*
  - New operators available on digital and Euclidean shapes (Union,
    Intersection, Minus)

 *Topology Package*
  - update documentation for digital surfaces and digital surface
    containers so as to emphasize the fact that the ranges are only
    single-pass.

 *Graph Package*
  - New package gathering graph related structures and algorithms
    (visitors, graph concepts, ...)
  - Add concepts for graph visitors
  - Add boost::graph support for DigitalSurface
  - Add documentation for graph package.

 *Math Package*
  - Exact exponentiation x^p by squaring on O(log p) added
    (BasicMathFunctions::power).

 *For developers*
  - new "make dox" target to only build dox file documentation
    ("make doc" for complete documentation build)


=== DGtal 0.5.1 ===
Posted on June, 6th, 2012 by David Coeurjolly

  - New way to cite package/module authors in the documentation
  - Improvement of DGtal::GridCurve ranges
  - Improvement of package concepts  in the  documentation
  - new documentation for DGTal build on MSWindows
  - arithmetic is now a main package (previously in math)
  - Specialized classes for classical metric adjacencies


=== DGtal 0.5 ===
Posted on May, 9th, 2012 by David Coeurjolly

Many changes have been pushed to this release with a lot of nice
tools.  Before going into details component by component, we would
like to focus on a couple of new cool features:

  - new arithmetic package (fractions, models of fraction,
  Stern-Brocot, continued fraction,...)
  - new nD DigitalSurface model (collections of (n-1) topological cells
  with many tools/utilities to track surface elements)
  - update of the build system to make easier the use of DGtal in your
  projects.
  - DGtal and DGtalTools
  - many bugfixes..

* Overall  Project

  - In previous DGtal releases, tools were given in the source
  "tools/" folder. In this release, we have chosen to move the
  tools to another GitHub project
  (http://github.com/DGtal-team/DGtalTools) with a specific
  development process. Please have a look to this project to get
  nice tools built upon the DGtal library.

  - cmake scripts and DGtalConfig have been widely updated to make
  easier the use of the library in your own code

  - We are debugging both the code and the scripts to make it compile
  on windows. We still have couple of issues but most of DGtal
  compiles.

  - Again, efforts have been done on the documentation.


* Package Topology:

 - Creation of the graph concept (see Doxygen documentation)

 - Graph tools have been added: breadth first visitor for any model of
   graph

 - Creation of high-level classes to represent several kinds of
   digital surfaces. Surfaces are n-1 dimensional objetcs and may be
   open or closed. There are several models of digital surface
   containers: boundary of a set of points, explicit set of surfels,
   boundary of a digital object defined by a predicate, frontier
   between two regions, light containers that are discovered on
   traversal but not stored explicitly, etc.

 - All these digital surfaces can be manipulated through the same
   object (DigitalSurface), whichever the container.

 - DigitalSurface is a model of a graph whose vertices are the surfels
   and whose arcs are the connections between surfels.

 - Definition of umbrellas over digital surfaces, that forms faces on
   the surface graph.

 - In 3D, digital surface form combinatorial 2-manifolds with boundary

 - Digital surface can be exported in OFF format

 - Several examples using digital surfaces are provided, like
   extracting isosurfaces from images or volume files defining
   surfaces in labelled images.

* Package Algebraic (new package)

 - Definition of n-variate polynomial as a one-dimensional polynomial
   whose coefficients are n-1-variate polynomials. Coefficient ring
   and dimension are templated.

 - Creation of a reader that can transform a string representation of
   multivariate polynomial into such polynomial object. Use
   boost::spirit.

 - Example using package Topology to extract and display implicit
   polynomial surfaces in 3D.

* Package Arithmetic (new package)

 - Standard arithmetic computations are provided: greatest common
   divisor, Bézout vectors, continued fractions,  convergent.

 - Several representations of irreducible fractions are provided. They
   are based on the Stern-Brocot tree structure. With these fractions,
   amortized constant time operations are provided for computing
   reduced fractions.

 - An implementation of patterns and subpatterns is provided, based on
   the irreducible fractions.
 - A representation of digital standard line in the first quadrant is
   provided, as well as fast algorithms to recognize digital straight
   subsegments.


* Package Image

  - Complete refactoring of Images and ImageContainers (more
  consistent design)

  - Documentation added

  - Graph of concepts added in the documentation


* Package Geometry

  - New SegmentComputer (a.k.a. geometrical primitives to use for
  recognition, curve decomposition,...) : ArithDSS3D (3D DSS), DCA
  (Digital Circular Arcs), CombinatorialDSSS, ...

  - New normal vector field estimation based on elementary normal
  vector convolution in n-D

  - Distance Transformation by Fast Marching Method added.

* Package IO

  - Complete refactoring of the way a DGtal object is displayed in
  boards/viewers.

  - New 2D board  backend: you can export your drawning in TikZ for
  latex includes.


=== DGtal 0.4 ===
Posted on September 26, 2011 by David Coeurjolly

	* Global changes:
	   - A better decomposition of DGtal algorithms and
	data structures into packages.
	   - By default, DGtal is built with minimal dependencies.
	   - Concepts and concept checking mechanism have been
	considerably improved.

	* Kernel Package: refactoring of Integer types considered in
	DGtal.

	* Topology Package: Interpixel/cellular topological model,
	boundary tracking tools, ...

	* Geometry Package:
	  - many things have been added in the 1D contour analysis module:
	multi-modal representation of 1D contours and curves (GridCurve facade),
	decomposition/segmentation into primitives, many differential
	estimators added, helpers for multigrid comparison of estimators
	  - multigrid digital set generators from implicit and parametric
	shapes in dimension 2.

	* I/O Package: refactoring/enhancements of DGtal boards and
	viewers,  enhancement of 2D boards with libcairo and a new
	Board3Dto2D board has been added.


	* Tools: multigrid shapeGenerator/contourGenerator added,
	lengthEstimator/estimatorComparator  added for differential
	estimator multigrid comparison, connected components extraction in
	3D, ...

	* Documentation: User guide has been improved thanks to a
	decomposition of the library into packages.

=== DGtal 0.3.1 ===
Posted on April 4, 2011 by David Coeurjolly

	* Quick release due to a build problem on linux. No more feature
	added.
	* Preliminary cellular grid documentation added.
	* Documentation cleanup.




=== DGtal 0.3.0 ===
Posted on April 1, 2011 by David Coeurjolly

Beside the DGtal presentation at DGCI 2011, we are pleased to announce a new
DGtal release 0.3.0.

New features:

  User-guide added (based on doxygen system)
  Kernel: new concepts and controls to enhance the Interger type management,
      new iterators (Range/SubRange) on HyperRectDomains.
  Topology: interpixel model added (cells, boundary tracking mechanisms,…)
  Geometry 2D: 2D curve primitive decomposition, tangential cover,
         convexity/concavity decomposition.
  Geometry nD: reverse Euclidean distance transformation
  Visualisation: stream mechanism to visualize 3D DGtal objects with
	       libQGLViewer (optional) Shape generator factory added in nD

BugFixes, enhancements:

  Many bugs have been fixed for this release.
  cmake DGtal dependency checking process is more stable now

Known problems:

  For technical reasons, we haven’t be able to verify that this release also
  compile on Windows Visual Studio systems (see ticket #87). A new release
  will fix this problem as soon as possible.





=== Older Releases ===





2011-04-01 dcoeurjo
	* Release 0.3.0
	* Kernel: global enhancement of different Integer types and
	associated concepts.
	* Topology: interpixel topology, cells, surface tracking
	* Geometry2D: contour primitive decomposition, tangential cover,
	convexity/concavity decomposition.
	* GeometrynD: Reverse DT transformation (Euclidean)
	* Infrastructure: 3D visualisation of DGtal objects with
	libQGLViewer, shape factory
	* IO: PointListReader added
	* Documentation: first DGtal user-guide


2010-01-12 dcoeurjo
	* Release 0.2
	* Kernel: DGtalBoard mechanism for 2D drawing of DGtal objects, ..
	* Geometry package
	   - Volumetric: distance transformation with separable	metric
	(l2, l1 and linfinity) in arbitrary dimension
	   - 2D: Arithmetical DSS, Greedy decomposition of a contour into
	primitives, FreemanChain code iterators
	* Topolopy package: Set, Adjacencies, Object, border extraction,
	connected components computation, ...
	* IO: 2D file formats with Magick++, Vol/Raw format in 3D, Raw
	format in n-D (non-portable)
	* Misc: Compiles on linux, MacOS and VisualStudio 2008


2010-21-05 dcoeurjo
	* Iterators added to PointVector
  * Debug methods removed in Trace class
  * Many bug fixes for VS compatibility

2010-05-15 dcoeurjo
  * Assert.h: added macro ASSERT() added based on the boost/assert.hpp (TODO:
	    implement a nice callback)
  * Point and Vector templated classes added
  * Space.*: skeleton of a DGtal::Space added

2010-03-03 dcoeurjo
	* math/MeasureOfStraightLines: new class to compute the measure of a set
	of Straight lines defined as a polygon in the (a,b) parameter space.
	* test_measure: added

2010-02-17 dcoeurjo
  * Trace: new class models for output streams in Trace class.
  * TraceWriter/TraceWriterTerm/TraceWriterFile: added

2010-02-12 dcoeurjo
  * models: bug fix  in INLINE commands
  * Trace/Clock: minor edit and bug report

2010-01-05 dcoeurjo
  * Trace can be initialized on diffrent output stream (e.g. std::cerr or a file
	  stream)
  * test_trace: update to test the new API

2010-01-04 dcoeurjo
  * Clock: no more static variables and methods (in order to have several
	   running clocks)
  * Trace: new interface and the endBlock displays and returns the
	   ellapsed time within the block

2009-12-28 dcoeurjo
  * Trace: a new class to trace out messages to the standard output. Four type
	   of messages are possible: info, debug, error and "emphased". On
	   color linux terminal, messages appears with an appropriate color
	   foreground.
  * test_trace: an illustration of the Trace interface

2009-12-14 dcoeurjo
  * CMakeLists, test_clock updates to ensure compatibility with VisualStudio
  * New cmake options
  - OPTION(BUILD_SHARED_LIBS "Build shared libraries." ON)
  - OPTION(BUILD_TESTS "Build tests." ON)

2009-12-11 dcoeurjo
	* CMakeLists scripts and first backport from imagene (Clock class)

2009-12-11 dcoeurjo
	* Repository cleanup:
		  - Modeles and genereateClass.sh removed
    - JOL scripts & templates added


2009-12-03 dcoeurjo
	* Modeles: class templates added with generateClass.sh script
