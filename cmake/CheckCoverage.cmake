# -----------------------------------------------------------------------------
# Coverage brute-froce discovery
# -----------------------------------------------------------------------------
ADD_CUSTOM_TARGET(lcov)
OPTION(WITH_COVERAGE "Enable lcov code coverage." OFF)
IF (WITH_COVERAGE) 
  MESSAGE(STATUS "Code coverage enabled")
  message(STATUS "-------------------------------------------------------------------------------")
  SET(DGTAL_PATTERN "*/src/DGtal/*")
  ADD_CUSTOM_COMMAND(TARGET lcov
    COMMAND mkdir -p coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
  ADD_CUSTOM_COMMAND(TARGET lcov
    COMMAND lcov --directory . --capture --output-file ./coverage/stap_all.info --no-checksum 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
  ADD_CUSTOM_COMMAND(TARGET lcov
    COMMAND lcov --directory . --extract ./coverage/stap_all.info ${DGTAL_PATTERN} --output-file ./coverage/stap.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
ENDIF()