#CMakeLists associated to the examples subdir

# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
include_directories (${PROJECT_BINARY_DIR}/src)

# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/examples/)
include_directories (${PROJECT_BINARY_DIR}/examples/)


# Make sure the linker can find the Hello library once it is built.
link_directories (${PROJECT_BINARY_DIR})

# ConfigExamples.h instanciation.
configure_file(${PROJECT_SOURCE_DIR}/examples/ConfigExamples.h.in 
  ${PROJECT_BINARY_DIR}/examples/ConfigExamples.h)

#------Examples subdirectories ------

add_subdirectory(images)
add_subdirectory(io)
add_subdirectory(geometry)
add_subdirectory(doc-examples)
add_subdirectory(tutorial-examples)
add_subdirectory(topology)
add_subdirectory(math)
add_subdirectory(arithmetic)
add_subdirectory(shapes)
add_subdirectory(graph)
add_subdirectory(dec)
add_subdirectory(base)
