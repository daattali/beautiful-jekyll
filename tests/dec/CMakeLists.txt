
if(WITH_EIGEN)

    add_executable(testDiscreteExteriorCalculus testDiscreteExteriorCalculus)
    target_link_libraries(testDiscreteExteriorCalculus DGtal)
    add_test(testDiscreteExteriorCalculus testDiscreteExteriorCalculus)

    add_executable(testLinearStructure testLinearStructure)
    target_link_libraries(testLinearStructure DGtal )
    add_test(testLinearStructure testLinearStructure)

    add_executable(testDiscreteExteriorCalculusExtended testDiscreteExteriorCalculusExtended)
    target_link_libraries(testDiscreteExteriorCalculusExtended DGtal)
    #add_test(testDiscreteExteriorCalculusExtended testDiscreteExteriorCalculusExtended)

    add_executable(testEmbedding testEmbedding)
    target_link_libraries(testEmbedding DGtal )
    add_test(testEmbedding testEmbedding)

    add_executable(testHeatLaplace testHeatLaplace)
    target_link_libraries(testHeatLaplace DGtal )
    add_test(testHeatLaplace testHeatLaplace)

endif(WITH_EIGEN)

