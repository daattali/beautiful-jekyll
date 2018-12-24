add_subdirectory(curves)
add_subdirectory(volumes)
add_subdirectory(surfaces)
add_subdirectory(tools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")

SET(DGTAL_TESTS_SRC 
  testContourHelper)

FOREACH(FILE ${DGTAL_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

