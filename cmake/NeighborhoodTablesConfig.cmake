#------------------------------------------------------------------------------
# DGtal Configuration file for LookUpTables
#------------------------------------------------------------------------------

# TABLE_DIR is the variable that NeighborhoodTables.h.in read.

# ------ Build Tree ------ #
#--- Configuration of the src/topology/tables/NeighborhoodTables.h.in
set(TABLE_DIR ${PROJECT_SOURCE_DIR}/src/DGtal/topology/tables)
configure_file(
  ${PROJECT_SOURCE_DIR}/src/DGtal/topology/tables/NeighborhoodTables.h.in
  ${PROJECT_BINARY_DIR}/src/DGtal/topology/tables/NeighborhoodTables.h)

# ------ Install Tree ------ #
#--- Configuration of the src/topology/tables/NeighborhoodTables.h.in for the install tree. Save to tmp file.
set(TABLE_DIR ${INSTALL_INCLUDE_DIR}/DGtal/topology/tables)
configure_file(
  ${PROJECT_SOURCE_DIR}/src/DGtal/topology/tables/NeighborhoodTables.h.in
  ${PROJECT_BINARY_DIR}/InstallFiles/NeighborhoodTables.h @ONLY)

#--- Install compressed tables and the header pointing to them ---#
set(table_folder_install ${INSTALL_INCLUDE_DIR}/DGtal/topology/tables)

#--- Install header pointing to tables. ---#
install(FILES ${PROJECT_BINARY_DIR}/InstallFiles/NeighborhoodTables.h
        DESTINATION "${table_folder_install}")
#--- Select all the tables and install ---#
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/DGtal/topology/tables/"
        DESTINATION "${table_folder_install}"
        FILES_MATCHING PATTERN "*.zlib")
