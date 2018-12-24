SET(DGTAL_TESTS_SRC
   dgtalBoard2D-1-points
   dgtalBoard2D-2-sets
   dgtalBoard2D-3-custom-classes
   dgtalBoard2D-3-custom-points
   dgtalBoard2D-4-colormaps
   dgtalBoard3D-1-points
   dgtalBoard3D-2-ks
   dgtalBoard3D-6-clipping
   logoDGtal
   exampleBezierCurve
   )


if( WITH_CAIRO )
  SET(DGTAL_TESTS_SRC
    ${DGTAL_TESTS_SRC}
    dgtalBoard3DTo2D-0-demo-kernel-2
    dgtalBoard3DTo2D-1-points
    dgtalBoard3DTo2D-2-sets
    dgtalBoard3DTo2D-2bis-sets
    dgtalBoard3DTo2D-3-objects
    dgtalBoard3DTo2D-4-modes
    dgtalBoard3DTo2D-5-custom
    dgtalBoard3DTo2D-6
    dgtalBoard3DTo2D-KSCell
  )
endif ( WITH_CAIRO )


FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
ENDFOREACH(FILE)


