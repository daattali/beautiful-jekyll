SET(DGTAL_TESTS_SRC
  testMeasureSet
  testVoronoiCovarianceMeasure
  )

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
