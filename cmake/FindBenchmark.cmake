# Try to find the Google Benchmark Library and headers.
#  BENCHMARK_FOUND - system has BENCHMARK lib
#  BENCHMARK_INCLUDE_DIR - the BENCHMARK include directory
#  BENCHMARK_LIBRARIES - Libraries needed to use BENCHMARK

# Copyright (c) 2014, David Coeurjolly <david.coeurjolly@liris.cnrs.fr>
#

find_package(Threads REQUIRED)

if (BENCHMARK_INCLUDE_DIR AND BENCHMARK_LIBRARIES)
  # Already in cache, be silent
  set(BENCHMARK_FIND_QUIETLY TRUE)
endif (BENCHMARK_INCLUDE_DIR AND BENCHMARK_LIBRARIES)

find_path(BENCHMARK_INCLUDE_DIR NAMES benchmark/benchmark.h
    /usr/local/include/benchmark
    /usr/local/include/
    /usr/include/benchmark
    /usr/include
    /opt/local/include
    /opt/include)
find_library(BENCHMARK_LIBRARIES NAMES libbenchmark.a)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BENCHMARK DEFAULT_MSG BENCHMARK_INCLUDE_DIR BENCHMARK_LIBRARIES)

mark_as_advanced(BENCHMARK_INCLUDE_DIR BENCHMARK_LIBRARIES)
