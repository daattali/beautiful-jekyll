#David Coeurjolly - it03/2012
PROJECT(ITKCPP11BUG)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})
include_directories(${ITK_INCLUDE_DIRS})
add_executable(itkcpp11 itkcpp11.cpp)
target_link_libraries(itkcpp11  ${ITK_LIBRARIES})
