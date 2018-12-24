SET(DGTAL_TESTS_SRC
  test2x2DetComputers
  testInHalfPlane)

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)



#Benchmark target
IF(BUILD_BENCHMARKS)
  SET(DGTAL_BENCH_SRC
    testInHalfPlane-benchmark
    )
  FOREACH(FILE ${DGTAL_BENCH_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal )
    add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
    ADD_DEPENDENCIES(benchmark ${FILE}-benchmark)
  ENDFOREACH(FILE)
ENDIF(BUILD_BENCHMARKS)