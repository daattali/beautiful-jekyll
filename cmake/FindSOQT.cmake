# Try to find SoQt
# Once done this will define
#
# SOQT_FOUND        - system has SOQT - needs Coin3D - Open Inventor
# SOQT_INCLUDE_DIR  - where the SoQt include directory can be found
# SOQT_LIBRARY      - Link this to use SoQt
#
 

IF (WIN32)
  IF (CYGWIN)

    FIND_PATH(SOQT_INCLUDE_DIR Inventor/Qt/SoQt.h)

    FIND_LIBRARY(SOQT_LIBRARY SoQt)

  ELSE (CYGWIN)
    message("[xx] Unchecked system." )
    FIND_PATH(SOQT_INCLUDE_DIR Inventor/Qt/SoQt.h
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SIM\\SoQt\\2;Installation Path]/include"
    )

    FIND_LIBRARY(SOQT_LIBRARY_DEBUG soqtd
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SIM\\SoQt\\2;Installation Path]/lib"
    )

    FIND_LIBRARY(SOQT_LIBRARY_RELEASE soqt
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SIM\\SoQt\\2;Installation Path]/lib"
    )

    IF (SOQT_LIBRARY_DEBUG AND SOQT_LIBRARY_RELEASE)
      SET(SOQT_LIBRARY optimized ${SOQT_LIBRARY_RELEASE}
                         debug ${SOQT_LIBRARY_DEBUG})
    ELSE (SOQT_LIBRARY_DEBUG AND SOQT_LIBRARY_RELEASE)
      IF (SOQT_LIBRARY_DEBUG)
        SET (SOQT_LIBRARY ${SOQT_LIBRARY_DEBUG})
      ENDIF (SOQT_LIBRARY_DEBUG)
      IF (SOQT_LIBRARY_RELEASE)
        SET (SOQT_LIBRARY ${SOQT_LIBRARY_RELEASE})
      ENDIF (SOQT_LIBRARY_RELEASE)
    ENDIF (SOQT_LIBRARY_DEBUG AND SOQT_LIBRARY_RELEASE)

    IF (SOQT_LIBRARY)
      ADD_DEFINITIONS ( -DSOQT_NOT_DLL )
    ENDIF (SOQT_LIBRARY)

  ENDIF (CYGWIN)

ELSE (WIN32)
  IF(APPLE)
    FIND_PATH(SOQT_INCLUDE_DIR Inventor/Qt/SoQt.h
     /Library/Frameworks/Inventor.framework/Headers 
    )
    FIND_LIBRARY(SOQT_LIBRARY SoQt
      /Library/Frameworks/Inventor.framework/Libraries
    )   
    SET(SOQT_LIBRARY "-framework SoQt" CACHE STRING "SoQt library for OSX")
   ELSE(APPLE)
       FIND_PATH(SOQT_INCLUDE_DIR Inventor/Qt/SoQt.h
	/home/lachaud/local/include)
       FIND_LIBRARY(SOQT_LIBRARY SoQt
	/home/lachaud/local/lib)   
  ENDIF(APPLE)

ENDIF (WIN32)

# handle the QUIETLY and REQUIRED arguments and set SOQT_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SoQt DEFAULT_MSG SOQT_LIBRARY SOQT_INCLUDE_DIR)

MARK_AS_ADVANCED(SOQT_INCLUDE_DIR SOQT_LIBRARY )


