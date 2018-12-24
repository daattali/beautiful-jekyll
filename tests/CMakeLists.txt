#CMakeLists associated to the tests subdir
#David Coeurjolly <david.coeurjolly@liris.cnrs.fr>

# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
include_directories (${PROJECT_BINARY_DIR}/src/)

# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/tests/)
include_directories (${PROJECT_BINARY_DIR}/tests/)



# Make sure the linker can find the Hello library once it is built.
link_directories (${PROJECT_BINARY_DIR})

# ConfigTest.h instanciation.
configure_file(${PROJECT_SOURCE_DIR}/tests/ConfigTest.h.in
  ${PROJECT_BINARY_DIR}/tests/ConfigTest.h)


# If google-benchmark is enabled, we have a specific target
add_custom_target(benchmark)


#------TESTS subdirectories ------
add_subdirectory(base)
add_subdirectory(kernel)
add_subdirectory(math)
add_subdirectory(arithmetic)
add_subdirectory(geometry)
add_subdirectory(graph)
add_subdirectory(topology)
add_subdirectory(io)
add_subdirectory(images)
add_subdirectory(helpers)
add_subdirectory(shapes)
add_subdirectory(dec)
