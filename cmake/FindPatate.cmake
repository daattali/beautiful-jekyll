# - Try to find Patate lib
#
# http://patate.gforge.inria.fr/html/index.html
#
# Once done this will define
#
#  PATATE_FOUND - system has patate lib with correct version
#  PATATE_INCLUDE_DIR - the patate include directory
#  PATATE_VERSION - patate version
#

find_path(PATATE_INCLUDE_DIR NAMES grenaille.h
  PATHS
  ${CMAKE_INSTALL_PREFIX}/include
  PATH_SUFFIXES Patate
  /usr/local/include/
  /usr/include/
  /opt/local/include
  /opt/include)



SET(PATATE_FOUND 0)
IF(PATATE_INCLUDE_DIR)
  SET(PATATE_FOUND 1)
ENDIF(PATATE_INCLUDE_DIR)

