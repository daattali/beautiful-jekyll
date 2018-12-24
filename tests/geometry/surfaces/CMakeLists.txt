SET(TESTS_SRC
  testChordGenericStandardPlaneComputer
  )

FOREACH(FILE ${TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

SET(TESTS_SURFACES_SRC
  testNormalVectorEstimatorEmbedder
  testIntegralInvariantVolumeEstimator
  testIntegralInvariantCovarianceEstimator
  testLocalEstimatorFromFunctorAdapter
  ##testVoronoiCovarianceMeasureOnSurface
  testTensorVoting
  testEstimatorCache
  testSphericalHoughNormalVectorEstimator
  )

FOREACH(FILE ${TESTS_SURFACES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


if (  WITH_CGAL )
  SET(CGAL_TESTS_SRC
    testMonge )
  FOREACH(FILE ${CGAL_TESTS_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)
endif ( WITH_CGAL )


if (  WITH_VISU3D_QGLVIEWER )
  SET(QGLVIEWER_TESTS_SRC
    testLocalConvolutionNormalVectorEstimator
    testTensorVotingViewer)

  FOREACH(FILE ${QGLVIEWER_TESTS_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
  ENDFOREACH(FILE)
endif ( WITH_VISU3D_QGLVIEWER   )



if ( WITH_PATATE )
    SET(PATATE_TESTS_SRC
      testSphereFitting )
    FOREACH(FILE ${PATATE_TESTS_SRC})
      add_executable(${FILE} ${FILE})
      target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
      add_test(${FILE} ${FILE})
    ENDFOREACH(FILE)
endif()

#-----------------------
#GMP based tests
#----------------------
SET(DGTAL_TESTS_GMP_SRC
  testCOBANaivePlaneComputer
  testCOBAGenericStandardPlaneComputer
  testChordNaivePlaneComputer
  )

IF(GMP_FOUND)
  FOREACH(FILE ${DGTAL_TESTS_GMP_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)
ENDIF(GMP_FOUND)

SET(DGTAL_BENCH_GMP_SRC
  testCOBANaivePlaneComputer-benchmark
  testCOBAGenericNaivePlaneComputer-benchmark
  testChordNaivePlaneComputer-benchmark
  )


#Benchmark target
IF(BUILD_BENCHMARKS)
  IF(GMP_FOUND)
    FOREACH(FILE ${DGTAL_BENCH_GMP_SRC})
      add_executable(${FILE} ${FILE})
      target_link_libraries (${FILE} DGtal )
      add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
      ADD_DEPENDENCIES(benchmark ${FILE}-benchmark)
    ENDFOREACH(FILE)
  ENDIF(GMP_FOUND)
ENDIF()
