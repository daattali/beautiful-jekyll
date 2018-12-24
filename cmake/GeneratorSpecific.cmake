#------------------------------------------------------------------------------
#--- Headers for IDE Generators
#
# The following lines add fake targets to register the .h and .ih files in the
# overall project.
# For IDE generators (Xcode, ...), all H and IH will be recognized as project
# headers and will thus be parsed and analyzed correctly (e.g. follow declaration
#/implementation, ...)
#
#------------------------------------------------------------------------------
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//base/*h)
add_custom_target(_base SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//math/*h)
add_custom_target(_math SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//kernel/*h)
add_custom_target(_kernel SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//topology/*h)
add_custom_target(_topology SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//geometry/*h)
add_custom_target(_geometry SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//io/*h)
add_custom_target(_io SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//images/*h)
add_custom_target(_images SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//shapes/*h)
add_custom_target(_shapes SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//arithmetic/*h)
add_custom_target(_arithmetic SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//graph/*h)
add_custom_target(_graph SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//helpers/*h)
add_custom_target(_helpers SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
FILE(GLOB_RECURSE DGTAL_MYHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/DGtal//dec/*h)
add_custom_target(_dec SOURCES ${DGTAL_MYHEADERS})
SET(DGTAL_MYHEADERS "")
