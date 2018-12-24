#------------------------------------------------------------------------------
# DGtal Configuration file for the install target
#------------------------------------------------------------------------------

#--- Headers installation
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
  DESTINATION "${INSTALL_INCLUDE_DIR}/"
  FILES_MATCHING PATTERN "*.*h")

#-- specific install for Config.h.in
install(DIRECTORY "${PROJECT_BINARY_DIR}/src/DGtal/"
  DESTINATION "${INSTALL_INCLUDE_DIR}/DGtal/"
  FILES_MATCHING PATTERN "*.*h")
INCLUDE(DGtalConfigGenerator)
