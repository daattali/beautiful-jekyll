SET(DGTAL_EXAMPLES_TOPO_SRC
  ctopo-1
  ctopo-2
  ctopo-fillContours
  khalimskySpaceScanner
  volMarchingCubes
  volToOFF  
  trackImplicitPolynomialSurfaceToOFF
  generateSimplicityTables2D
  generateSimplicityTables3D
  generateVoxelComplexTables
  digitalSetToCubicalComplexes2D
  cubical-complex-illustrations
  cubicalComplexThinning
  area-estimation-with-digital-surface
  area-estimation-with-indexed-digital-surface
)

FOREACH(FILE ${DGTAL_EXAMPLES_TOPO_SRC}) 
  add_executable(${FILE} ${FILE})
  target_link_libraries ( ${FILE}  DGtal
    ${DGtalLibDependencies})   
ENDFOREACH(FILE)


if (  WITH_VISU3D_QGLVIEWER )
   SET(DGTAL_EXAMPLES_QGL_SRC
     cubical-complex-collapse
     homotopicThinning3D
     3dBorderExtraction
     3dBorderExtractionImg
     ctopo-1-3d
     ctopo-1s-3d
     ctopo-2-3d
     3dKSSurfaceExtraction
     volScanBoundary
     volTrackBoundary
     volBreadthFirstTraversal
     frontierAndBoundary
     digitalSurfaceSlice
   )
  FOREACH(FILE ${DGTAL_EXAMPLES_QGL_SRC}) 
   add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE}  DGtal
                            ${DGtalLibDependencies})   
  ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER   )

