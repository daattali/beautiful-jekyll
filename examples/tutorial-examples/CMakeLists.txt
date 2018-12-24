
SET(DGTAL_TUTO_EXAMPLES_SRC
  imageSetDT
  fileGridCurveRanges
  imageGridCurveEstimator
  shapeGridCurveEstimator
  freemanChainFromImage
  FMMErosion
  2DSliceImageFromVol
  shortcuts
  shortcuts-geometry
)


FOREACH(FILE ${DGTAL_TUTO_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)




if (  WITH_VISU3D_QGLVIEWER )
   SET(DGTAL_TUTO_EXAMPLES_QGL_SRC
   shapeDTViewer
   volDTGranulo
   polyhedralizer
   )
  FOREACH(FILE ${DGTAL_TUTO_EXAMPLES_QGL_SRC}) 
   add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE} DGtal 
                            ${DGtalLibDependencies})   
  ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER   )

