#------------------------------------------------------------------------------
# -- Environement variables
#------------------------------------------------------------------------------
if (UNIX)
  add_definitions(-DUNIX)
endif (UNIX)
if (WIN32)
  add_definitions(-DWIN32)
endif (WIN32)
if (APPLE)
  add_definitions(-DAPPLE)
endif (APPLE)

#------------------------------------------------------------------------------
# -- Removing some strange warnings when compiling with VS Express
#------------------------------------------------------------------------------
IF(MSVC)
 IF(NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
    SET(NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
  ENDIF(NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
ENDIF(MSVC)

#------------------------------------------------------------------------------
# Remove some MS Visual c++ flags
#------------------------------------------------------------------------------
IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
  #------------------------------------------------------------------------------
  # for GMP / MPIR (MT)
  #------------------------------------------------------------------------------
  SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"libcmtd.lib;libcmt.lib\")
ENDIF(MSVC)


#------------------------------------------------------------------------------
# Specific compiler options
#------------------------------------------------------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Qunused-arguments")
  message(STATUS "Clang compiler detected")
  if ( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdocumentation")
  endif( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
