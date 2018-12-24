#------------------------------------------------------------------------------
# -- Messages
#------------------------------------------------------------------------------
message(STATUS "-------------------------------------------------------------------------------")
message(STATUS "DGtal Version ${PROJECT_VERSION}")
message(STATUS "-------------------------------------------------------------------------------" )
message(STATUS "Source DIR is ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary/Build DIR is ${PROJECT_BINARY_DIR}")
message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")
message(STATUS "Installation prefix directory is " ${CMAKE_INSTALL_PREFIX})
message(STATUS "Host system is " ${CMAKE_HOST_SYSTEM} " with processor " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "Target system is " ${CMAKE_SYSTEM} " with processor " ${CMAKE_SYSTEM_PROCESSOR})

#------------------------------------------------------------------------------
# Offer the user the choice of overriding the installation directories
#------------------------------------------------------------------------------
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries.")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables.")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header file./")
set(INSTALL_DATA_DIR lib/DGtal CACHE PATH "Installation directory for DGtal cmake files.")
#------------------------------------------------------------------------------
# Make relative paths absolute (needed later on)
#------------------------------------------------------------------------------
foreach(p LIB BIN INCLUDE DATA)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# -----------------------------------------------------------------------------
# Doxygen targets
# -----------------------------------------------------------------------------
message(STATUS "-------------------------------------------------------------------------------")
message(STATUS "Checking if doxygen/dot is installed:")
message(STATUS " ")
set(INSTALL_DOC_PATH ${CMAKE_INSTALL_PREFIX}/share/DGtal CACHE PATH "Installation directory for DGtal documentation files.")
INCLUDE(doxygen)
INCLUDE(TargetDoxygenDoc OPTIONAL)
INCLUDE(TargetDoxygenDox OPTIONAL)

# -----------------------------------------------------------------------------
# uninstall target
# -----------------------------------------------------------------------------
CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetUninstall.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/TargetUninstall.cmake
  @ONLY)
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/TargetUninstall.cmake")

# -----------------------------------------------------------------------------
# Parsing cmake options
# -----------------------------------------------------------------------------
OPTION(BUILD_SHARED_LIBS "Build shared libraries." ON)
OPTION(BUILD_TESTING "Build testing." OFF)
OPTION(DEBUG_VERBOSE "Verbose debug messages." OFF)
OPTION(VERBOSE "Verbose messages." OFF)
OPTION(COLOR_WITH_ALPHA_ARITH "Consider alpha channel in color arithmetical operations." OFF)
OPTION(DGTAL_NO_ESCAPED_CHAR_IN_TRACE "Avoid printing special color and font weight terminal escaped char in program output." OFF)

SET(VERBOSE_DGTAL 0)
SET(DEBUG_VERBOSE_DGTAL 0)
SET(COLOR_WITH_ALPHA_ARITH_DGTAL 0)

IF (DEBUG_VERBOSE)
  SET(DEBUG_VERBOSE_DGTAL 1)
  ADD_DEFINITIONS(-DDEBUG_VERBOSE)
  MESSAGE(STATUS "Debug verbose mode activated")
ENDIF(DEBUG_VERBOSE)
IF (VERBOSE)
  SET(VERBOSE_DGTAL 1)
  ADD_DEFINITIONS(-DVERBOSE)
  MESSAGE(STATUS "Verbose mode activated")
ENDIF(VERBOSE)

IF(COLOR_WITH_ALPHA_ARITH)
  SET(COLOR_WITH_ALPHA_ARITH_DGTAL 1)
  ADD_DEFINITIONS(-DCOLOR_WITH_ALPHA_ARITH)
ENDIF(COLOR_WITH_ALPHA_ARITH)

# -----------------------------------------------------------------------------
# Benchmark target
# -----------------------------------------------------------------------------
OPTION(BUILD_BENCHMARKS "Build benchmarks." OFF)
IF(BUILD_BENCHMARKS)
  ADD_CUSTOM_TARGET(benchmark COMMAND echo "Benchmarks launched.....")
ENDIF(BUILD_BENCHMARKS)

#------------------------------------------------------------------------------
# Some directories and files should also be cleaned when invoking 'make clean'
#------------------------------------------------------------------------------
ADD_CUSTOM_TARGET(distclean
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/TargetDistclean.cmake")

#------------------------------------------------------------------------------
# Configuration of the Config.h
#------------------------------------------------------------------------------
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/src/DGtal/base/Config.h.in
  ${PROJECT_BINARY_DIR}/src/DGtal/base/Config.h)

#------------------------------------------------------------------------------
# Building in the source tree is forbidden
#------------------------------------------------------------------------------
IF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})
  MESSAGE(STATUS "Building in the source tree is not a good idea ! Remove the file 'CMakeCache.txt' and the folder 'CMakeFiles' an
d build outside the sources (for example 'mkdir build ; cmake <DGTAL_DIR>'.")
ENDIF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})


# -----------------------------------------------------------------------------
# Debug specific options
# -----------------------------------------------------------------------------
OPTION(WARNING_AS_ERROR "Transform compiler warnings as errors (in Debug build type)." OFF)
IF (WARNING_AS_ERROR)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
  MESSAGE(STATUS "Warnings as Errors ENABLED.")
ENDIF(WARNING_AS_ERROR)
