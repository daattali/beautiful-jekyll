MESSAGE(STATUS "Generating DGtalConfig files")

export(TARGETS  DGtal FILE "${PROJECT_BINARY_DIR}/DGtalLibraryDepends.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
# export(PACKAGE DGtal)
# Not working on cmake 2.6, I remove this option but keep the codeline (DC)

# Create a DGtalConfig.cmake file for the use from the build tree
set(DGTAL_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}/src")
set(DGTAL_LIB_DIR "${PROJECT_BINARY_DIR}/src")
set(DGTAL_CMAKE_DIR "${PROJECT_BINARY_DIR}")

configure_file(${PROJECT_SOURCE_DIR}/cmake/DGtalConfig.cmake.in
  "${PROJECT_BINARY_DIR}/DGtalConfig.cmake" @ONLY)

configure_file(${PROJECT_SOURCE_DIR}/cmake/DGtalConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/DGtalConfigVersion.cmake" @ONLY)
# Copy also the cpp11_check.cpp for the build tree.
file(COPY ${PROJECT_SOURCE_DIR}/cmake/src/cpp11/cpp11_check.cpp
     DESTINATION ${PROJECT_BINARY_DIR})

# Install the export set for use with the install-tree
install(EXPORT DGtalLibraryDepends DESTINATION
  "${INSTALL_DATA_DIR}"
  COMPONENT dev)

# Create a DGtalConfig.cmake file for the use from the install tree
# and install it
set(DGTAL_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
set(DGTAL_LIB_DIR "${INSTALL_LIB_DIR}")
set(DGTAL_CMAKE_DIR "${INSTALL_DATA_DIR}")
configure_file(${PROJECT_SOURCE_DIR}/cmake/DGtalConfig.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfig.cmake" @ONLY)

configure_file(${PROJECT_SOURCE_DIR}/cmake/DGtalConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfigVersion.cmake" @ONLY)
install(FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfig.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfigVersion.cmake"
  "${PROJECT_SOURCE_DIR}/cmake/src/cpp11/cpp11_check.cpp"
  DESTINATION "${DGTAL_CMAKE_DIR}" COMPONENT dev)
