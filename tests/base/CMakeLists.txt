SET(DGTAL_TESTS_SRC
   testBasicBoolFunctors
   testOrderedAlphabet
   testCirculator
   testConstIteratorAdapter
   testProgressBar
   testBasicFunctors
   testConstRangeAdapter
   testOutputIteratorAdapter
   testClock
   testTrace
   testCountedPtr
   testCountedPtrOrPtr
   testCountedConstPtrOrConstPtr
   testBits
   testIndexedListWithBlocks
   testLabels
   testLabelledMap
   testLabelledMap-benchmark
   testMultiMap-benchmark
   testOpenMP
   testIteratorFunctions
   testIteratorCirculatorTraits
   testCloneAndAliases
   testClone2
   testOwningOrAliasingPtr
   testPartialTemplateSpecialization
   testContainerTraits
   testSetFunctions
   testSimpleRandomAccessRangeFromPoint)

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


#--- Benchmark specific
if (WITH_BENCHMARK)
  set(DGTAL_TESTS_SRC_BENCHMARK
    ${DGTAL_TESTS_SRC_BENCHMARK}
    testBenchmark)

  FOREACH(FILE ${DGTAL_TESTS_SRC_BENCHMARK})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
    ADD_DEPENDENCIES(benchmark ${FILE})
  ENDFOREACH(FILE)

endif (WITH_BENCHMARK)
