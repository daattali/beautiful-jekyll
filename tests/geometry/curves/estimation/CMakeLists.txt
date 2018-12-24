SET(DGTAL_TESTS_SRC
  testLengthEstimators
  testTrueLocalEstimator
  testEstimatorComparator
  testSegmentComputerEstimators
  testMostCenteredMSEstimator
  testLambdaMST2D
  testLambdaMST3D
  )

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
