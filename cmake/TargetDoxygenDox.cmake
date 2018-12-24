#make dox target

FIND_PACKAGE(Doxygen)


IF (DOXYGEN_FOUND)
  
  # click+jump in Emacs and Visual Studio (for doxy.config) (jw)
  IF    (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
    SET(DOXY_WARN_FORMAT "\"$file($line) : $text \"")
  ELSE  (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
    SET(DOXY_WARN_FORMAT "\"$file:$line: $text \"")
  ENDIF (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
  
  # we need latex for doxygen because of the formulas
  FIND_PACKAGE(LATEX)
  IF    (NOT LATEX_COMPILER)
    MESSAGE(STATUS "latex command LATEX_COMPILER not found but usually required. You will probably get warnings and user interaction on doxy run.")
  ENDIF (NOT LATEX_COMPILER)
  IF    (NOT MAKEINDEX_COMPILER)
    MESSAGE(STATUS "makeindex command MAKEINDEX_COMPILER not found but usually required.")
  ENDIF (NOT MAKEINDEX_COMPILER)
  IF    (NOT DVIPS_CONVERTER)
    MESSAGE(STATUS "dvips command DVIPS_CONVERTER not found but usually required.")
  ENDIF (NOT DVIPS_CONVERTER)
  
  IF   (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in")
    MESSAGE(STATUS "configured ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in --> ${CMAKE_CURRENT_BINARY_DIR}/doxy.config.dox")
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in 
      ${CMAKE_CURRENT_BINARY_DIR}/doxy.config.dox
      @ONLY )
    # use (configured) doxy.config from (out of place) BUILD tree:
    SET(DOXY_CONFIG_DOX "${CMAKE_CURRENT_BINARY_DIR}/doxy.config.dox")
  ELSE (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in")
    # use static hand-edited doxy.config from SOURCE tree:
    SET(DOXY_CONFIG_DOX "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox")
    IF   (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox")
      MESSAGE(STATUS "WARNING: using existing ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox instead of configuring from doxy.config.dox.in file.")
    ELSE (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox")
      IF   (EXISTS "${CMAKE_MODULE_PATH}/doc/doxy.config.dox.in")
        # using template doxy.config.dox.in
        MESSAGE(STATUS "config.doxured ${CMAKE_CMAKE_MODULE_PATH}/doc/doxy.config.dox.in --> ${CMAKE_CURRENT_BINARY_DIR}/doc/doxy.config.dox")
        CONFIGURE_FILE(${CMAKE_MODULE_PATH}/doc/doxy.config.dox.in 
          ${CMAKE_CURRENT_BINARY_DIR}/doxy.config.dox
          @ONLY )
        SET(DOXY_CONFIG_DOX "${CMAKE_CURRENT_BINARY_DIR}/doxy.config.dox")
      ELSE (EXISTS "${CMAKE_MODULE_PATH}/doc/doxy.config.dox.in")
        # failed completely...
        MESSAGE(SEND_ERROR "Please create ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in (or doxy.config.dox as fallback)")
      ENDIF(EXISTS "${CMAKE_MODULE_PATH}/doc/doxy.config.dox.in")

    ENDIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox")
  ENDIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy.config.dox.in")

  
  ADD_CUSTOM_TARGET(dox ${DOXYGEN_EXECUTABLE} ${DOXY_CONFIG_DOX})

 
  # create a windows help .chm file using hhc.exe
  # HTMLHelp DLL must be in path!
  # fallback: use hhw.exe interactively
  IF    (WIN32)
    FIND_PACKAGE(HTMLHelp)
    IF   (HTML_HELP_COMPILER)      
      SET (TMP "${CMAKE_CURRENT_BINARY_DIR}\\Doc\\html\\index.hhp")
      STRING(REGEX REPLACE "[/]" "\\\\" HHP_FILE ${TMP} )
      # MESSAGE(SEND_ERROR "DBG  HHP_FILE=${HHP_FILE}")
      ADD_CUSTOM_TARGET(winhelp ${HTML_HELP_COMPILER} ${HHP_FILE})
      ADD_DEPENDENCIES (winhelp doc)
     
      IF (NOT TARGET_DOC_SKIP_INSTALL)
      # install windows help?
      # determine useful name for output file 
      # should be project and version unique to allow installing 
      # multiple projects into one global directory      
      IF   (EXISTS "${PROJECT_BINARY_DIR}/Doc/html/index.chm")
        IF   (PROJECT_NAME)
          SET(OUT "${PROJECT_NAME}")
        ELSE (PROJECT_NAME)
          SET(OUT "Documentation") # default
        ENDIF(PROJECT_NAME)
        IF   (${PROJECT_NAME}_VERSION_MAJOR)
          SET(OUT "${OUT}-${${PROJECT_NAME}_VERSION_MAJOR}")
          IF   (${PROJECT_NAME}_VERSION_MINOR)
            SET(OUT  "${OUT}.${${PROJECT_NAME}_VERSION_MINOR}")
            IF   (${PROJECT_NAME}_VERSION_PATCH)
              SET(OUT "${OUT}.${${PROJECT_NAME}_VERSION_PATCH}")      
            ENDIF(${PROJECT_NAME}_VERSION_PATCH)
          ENDIF(${PROJECT_NAME}_VERSION_MINOR)
        ENDIF(${PROJECT_NAME}_VERSION_MAJOR)
        # keep suffix
        SET(OUT  "${OUT}.chm")
        
        #MESSAGE("DBG ${PROJECT_BINARY_DIR}/Doc/html/index.chm \n${OUT}")
        # create target used by install and package commands 
        INSTALL(FILES "${PROJECT_BINARY_DIR}/Doc/html/index.chm"
          DESTINATION "doc"
          RENAME "${OUT}"
        )
      ENDIF(EXISTS "${PROJECT_BINARY_DIR}/Doc/html/index.chm")
      ENDIF(NOT TARGET_DOC_SKIP_INSTALL)

    ENDIF(HTML_HELP_COMPILER)
    # MESSAGE(SEND_ERROR "HTML_HELP_COMPILER=${HTML_HELP_COMPILER}")
  ENDIF (WIN32) 

ENDIF(DOXYGEN_FOUND)

