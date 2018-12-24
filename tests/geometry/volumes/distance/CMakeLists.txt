SET(DGTAL_TESTS_SRC
  testDistanceTransformation
  testDistanceTransformationND
  testDistanceTransformationMetrics
  testReverseDT
  testFMM
  testVoronoiMap
  testMetrics
  testMetricBalls
  testPowerMap
  testReducedMedialAxis
  testSeparableMetricAdapter
  testChamferDT
  testChamferVoro
  testDigitalMetricAdapter
  )


FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
 
SET(DGTAL_BENCH_SRC
  testMetrics-benchmark
  )

IF(BUILD_BENCHMARKS)
  #Benchmark target
  FOREACH(FILE ${DGTAL_BENCH_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal)
    add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
    ADD_DEPENDENCIES(benchmark ${FILE}-benchmark)
  ENDFOREACH(FILE)
ENDIF(BUILD_BENCHMARKS)

