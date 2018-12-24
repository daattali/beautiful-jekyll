
### Visu QGLViewer

SET(QGLVIEWER_TESTS_SRC
  testViewer3D
  testViewerQuad
  testBallQuadViewer
  testPolygon3D
  test3DImageView
  test3DImageViewEmbedder
  test3DImage3DView
  testDisplayKSCell
  test3DDomain2DView
  )

if (  WITH_VISU3D_QGLVIEWER )

  FOREACH(FILE ${QGLVIEWER_TESTS_SRC})
   add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE}  DGtal
                            ${DGtalLibDependencies})
  ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER   )
