SET(DGTAL_TESTS_SRC
   testAdjacency
   testKhalimskySpaceND
   testCubicalComplex
   testVoxelComplex
   testDigitalSurface
   testDigitalTopology
   testObject
   testObjectBorder
   testSimpleExpander
   testSCellsFunctor
   testUmbrellaComputer
   testSurfaceHelper
   testDigitalSetToCellularGridConverter
   testNeighborhoodConfigurations
   testParDirCollapse
   testHalfEdgeDataStructure
   testIndexedDigitalSurface
)

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

SET(DGTAL_BENCH_SRC
   testObject-benchmark
   testImplicitDigitalSurface-benchmark
   testLightImplicitDigitalSurface-benchmark
)

#Benchmark target
IF (BUILD_BENCHMARKS)
  FOREACH(FILE ${DGTAL_BENCH_SRC})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal)
    add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
    ADD_DEPENDENCIES(benchmark ${FILE}-benchmark)
  ENDFOREACH(FILE)
ENDIF(BUILD_BENCHMARKS)
