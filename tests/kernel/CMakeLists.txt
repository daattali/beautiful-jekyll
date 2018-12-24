SET(DGTAL_TESTS_SRC_KERNEL
   testDigitalSet
   testDomainSpanIterator
   testHyperRectDomain
   testInteger
   testPointVector
   testLinearAlgebra
   testImagesSetsUtilities
   testBasicPointFunctors
   testEmbedder
   testPointPredicateConcepts
   testPointHashFunctions
   testLinearizer
   )


FOREACH(FILE ${DGTAL_TESTS_SRC_KERNEL})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


IF(WITH_BENCHMARK)
  SET(DGTAL_BENCH_SRC
    benchmarkSetContainer
    )
  #Benchmark target
  FOREACH(FILE ${DGTAL_BENCH_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
    ADD_DEPENDENCIES(benchmark ${FILE})
  ENDFOREACH(FILE)
ENDIF(WITH_BENCHMARK)


#-----------------------
#GMP based tests
#----------------------
IF(GMP_FOUND)
  SET(DGTAL_TESTS_GMP_SRC testDGtalGMP)

  FOREACH(FILE ${DGTAL_TESTS_GMP_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)
ENDIF(GMP_FOUND)
