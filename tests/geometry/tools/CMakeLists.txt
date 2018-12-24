add_subdirectory(determinant)

SET(DGTAL_TESTS_SRC
  testRayIntersection
  testPreimage
  testSphericalAccumulator
  testHullFunctions2D
  testPolarPointComparatorBy2x2DetComputer
  testConvexHull2D
  testConvexHull2DThickness
  testConvexHull2DReverse)

SET(DGTAL_TESTS_QSRC
  testSphericalAccumulatorQGL)

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


IF (WITH_VISU3D_QGLVIEWER)
  FOREACH(FILE ${DGTAL_TESTS_QSRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
  ENDFOREACH(FILE)
ENDIF()
