# Generate doc only if Doxygen is present.
set( PACKAGE ${PROJECT_NAME} )
set( VERSION ${PROJECT_VERSION} )
set( DOC_DIR ${PROJECT_SOURCE_DIR}/doc )
set( top_srcdir ${PROJECT_SOURCE_DIR} )
set( top_bindir ${PROJECT_BINARY_DIR} )
set( HAVE_DOT YES )
find_program(DOT_EXE dot)
if ( DOT_EXE )
  message (STATUS "dot found: ${DOT_EXE}. Installing doc in ${INSTALL_DOC_PATH}")
else ( DOT_EXE )
  message( WARNING "Note: dot program not found in environment. If you wish to use it in doxygen, you should add its path to the variable PATH." )
  message( STATUS "disabling dot." )
  set( HAVE_DOT NO )
endif ( DOT_EXE )
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/doc/html)
  file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html)
endif (NOT EXISTS ${PROJECT_SOURCE_DIR}/doc/html)

## Installation target
install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html DESTINATION ${INSTALL_DOC_PATH})

