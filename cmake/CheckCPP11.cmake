# -----------------------------------------------------------------------------
# Test some c++11 functionalities
# -----------------------------------------------------------------------------

try_compile( CPP11_COMPATIBLE_FLAG_SET_BY_USER
  ${CMAKE_BINARY_DIR}/CMakeTmp
  ${CMAKE_SOURCE_DIR}/cmake/src/cpp11/cpp11_check.cpp
  CMAKE_FLAGS "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}"
  OUTPUT_VARIABLE OUTPUT
  )

IF (CPP11_COMPATIBLE_FLAG_SET_BY_USER)
  MESSAGE(STATUS "  CPP11 enabled compiler by default.") 
ENDIF()

IF (NOT CPP11_COMPATIBLE_FLAG_SET_BY_USER)
  try_compile( CPP11_COMPATIBLE_FLAG_SET_BY_DGTAL
    ${CMAKE_BINARY_DIR}/CMakeTmp
    ${CMAKE_SOURCE_DIR}/cmake/src/cpp11/cpp11_check.cpp
    COMPILE_DEFINITIONS "-std=c++11"
    OUTPUT_VARIABLE OUTPUT
    )
ENDIF()

SET(CPP11_COMPATIBLE CPP11_COMPATIBLE_FLAG_SET_BY_USER OR CPP11_COMPATIBLE_FLAG_SET_BY_DGTAL)

