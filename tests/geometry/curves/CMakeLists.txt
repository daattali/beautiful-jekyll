add_subdirectory(estimation)

SET(DGTAL_TESTS_SRC
  testArithDSS3d
  testFreemanChain
  testSegmentation
  testFP
  testGridCurve
  testCombinDSS
  testStabbingLineComputer
  testStabbingCircleComputer
  testBinomialConvolver
  testFrechetShortcut	
  testArithmeticalDSS
  testArithmeticalDSLKernel
  testArithmeticalDSSComputer
  testArithmeticalDSL
  testDSLSubsegment
  testArithDSSIterator
  testArithmeticalDSSConvexHull
  testAlphaThickSegmentComputer
  )


FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


