
SET(DGTAL_EXAMPLES_SRC
	exampleIntegralInvariantCurvature2D
	exampleEstimatorFromSurfelFunctors
        dvcm-2d-curvature
)

FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)


### with QGLViewer
if (  WITH_VISU3D_QGLVIEWER )
   SET(DGTAL_EXAMPLES_QGL_SRC
	greedy-plane-segmentation
	greedy-plane-segmentation-ex2
	greedy-plane-segmentation-ex3
	exampleIntegralInvariantCurvature3D
        dvcm-3d
   )
  FOREACH(FILE ${DGTAL_EXAMPLES_QGL_SRC})
   add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE}  DGtal)
  ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER   )
