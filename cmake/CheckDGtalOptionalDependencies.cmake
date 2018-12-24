# -----------------------------------------------------------------------------
# Check Optional Dependencies
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Global options
# -----------------------------------------------------------------------------
message(STATUS "-------------------------------------------------------------------------------")
message(STATUS "DGtal Library optional configuration:")
message(STATUS "   (to change these values, use ccmake, a graphical")
message(STATUS "   cmake frontend, or define cmake commandline variables")
message(STATUS "   -e.g. '-DWITH_GMP:string=true'-, cf documentation)")
message(STATUS "")

OPTION(WITH_OPENMP "With OpenMP (compiler multithread programming) features." OFF)
OPTION(WITH_GMP "With Gnu Multiprecision Library (GMP)." OFF)
OPTION(WITH_EIGEN "With Eigen3 Linear Algebra Library." OFF)
OPTION(WITH_CGAL "With CGAL." OFF)
OPTION(WITH_MAGICK "With GraphicsMagick++." OFF)
OPTION(WITH_ITK "With Insight Toolkit ITK." OFF)
OPTION(WITH_CAIRO "With CairoGraphics." OFF)
OPTION(WITH_HDF5 "With HDF5." OFF)
OPTION(WITH_QGLVIEWER "With LibQGLViewer for 3D visualization (Qt4 required)." OFF)
OPTION(WITH_PATATE "With Patate library for geometry OFF (Eigen required)." processing)
OPTION(WITH_QT5 "Using Qt5." OFF)
OPTION(WITH_BENCHMARK "With Google Benchmark." OFF)
OPTION(WITH_FFTW3 "With FFTW3 discrete Fourier Transform library." OFF)

#----------------------------------
# Removing -frounding-math compile flag for clang
#----------------------------------
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE( STATUS "Removing -frounding-math flag when compiling with Clang" )
    STRING( REPLACE "-frounding-math" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
    MESSAGE( STATUS " " )
ENDIF()
#---------------------------------

IF(WITH_OPENMP)
SET (LIST_OPTION ${LIST_OPTION} [OpenMP]\ )
message(STATUS "      WITH_OPENMP        true    (OpenMP multithread features)")
ELSE(WITH_OPENMP)
message(STATUS "      WITH_OPENMP        false   (OpenMP multithread features)")
ENDIF(WITH_OPENMP)

IF(WITH_GMP)
SET (LIST_OPTION ${LIST_OPTION} [GMP]\ )
message(STATUS "      WITH_GMP           true    (Gnu Multiprecision Library)")
ELSE(WITH_GMP)
message(STATUS "      WITH_GMP           false   (Gnu Multiprecision Library)")
ENDIF(WITH_GMP)

IF(WITH_EIGEN)
SET (LIST_OPTION ${LIST_OPTION} [EIGEN]\ )
message(STATUS "      WITH_EIGEN         true    (Eigen3)")
ELSE(WITH_EIGEN)
message(STATUS "      WITH_EIGEN         false   (Eigen3)")
ENDIF(WITH_EIGEN)

IF(WITH_CGAL)
SET (LIST_OPTION ${LIST_OPTION} [CGAL]\ )
message(STATUS "      WITH_CGAL          true    (cgal)")
ELSE(WITH_CGAL)
message(STATUS "      WITH_CGAL          false   (cgal)")
ENDIF(WITH_CGAL)

IF(WITH_PATATE)
SET (LIST_OPTION ${LIST_OPTION} [PATATE]\ )
message(STATUS "      WITH_PATATE        true    (Patate geometry library)")
ELSE(WITH_PATATE)
message(STATUS "      WITH_PATATE        false   (Patate geometry library)")
ENDIF(WITH_PATATE)


IF(WITH_ITK)
SET (LIST_OPTION ${LIST_OPTION} [ITK]\ )
message(STATUS "      WITH_ITK           true    (Insight Toolkit ITK image wrapper)")
ELSE(WITH_ITK)
message(STATUS "      WITH_ITK           false   (Insight Toolkit ITK image wrapper)")
ENDIF(WITH_ITK)

IF(WITH_CAIRO)
SET (LIST_OPTION ${LIST_OPTION} [CAIRO]\ )
message(STATUS "      WITH_CAIRO         true    (CairoGraphics drawing features)")
ELSE(WITH_CAIRO)
message(STATUS "      WITH_CAIRO         false   (CairoGraphics drawing features)")
ENDIF(WITH_CAIRO)

IF(WITH_HDF5)
SET (LIST_OPTION ${LIST_OPTION} [HDF5]\ )
message(STATUS "      WITH_HDF5          true    (HDF5 image i/o)")
ELSE(WITH_HDF5)
message(STATUS "      WITH_HDF5          false   (HDF5 image i/o)")
ENDIF(WITH_HDF5)

IF(WITH_MAGICK)
SET (LIST_OPTION ${LIST_OPTION} [MAGICK]\ )
message(STATUS "      WITH_MAGICK        true    (GraphicsMagick based 2D image i/o)")
ELSE(WITH_MAGICK)
message(STATUS "      WITH_MAGICK        false   (GraphicsMagick based 2D image i/o)")
ENDIF(WITH_MAGICK)

If(WITH_QGLVIEWER)
SET (LIST_OPTION ${LIST_OPTION} [QGLVIEWER]\ )
message(STATUS "      WITH_QGLVIEWER     true    (QGLViewer based 3D Viewer -- Qt4 by default)")
ELSE(WITH_QGLVIEWER)
message(STATUS "      WITH_QGLVIEWER     false   (QGLViewer based 3D Viewer -- Qt4 by default)")
ENDIF(WITH_QGLVIEWER)

if (WITH_QT5)
  set(LIST_OPTION ${LIST_OPTION} [QT5]\ )
  message(STATUS "      WITH_QT5           true    (Using of Qt5 instead of Qt4)")
else (WITH_QT5)
  message(STATUS "      WITH_QT5           false   (Using of Qt5 instead of Qt4)")
endif (WITH_QT5)

if (WITH_FFTW3)
  set(LIST_OPTION ${LIST_OPTION} [FFTW3]\ )
  message(STATUS "      WITH_FFTW3         true    (FFTW3 discrete Fourier transform library)")
else (WITH_FFTW3)
  message(STATUS "      WITH_FFTW3         false   (FFTW3 discrete Fourier transform library)")
endif (WITH_FFTW3)

message(STATUS "")
message(STATUS "For Developpers:")
IF(WITH_BENCHMARK)
SET (LIST_OPTION ${LIST_OPTION} [GoogleBenchmark]\ )
message(STATUS "      WITH_BENCHMARK     true    (Google Benchmark)")
ELSE(WITH_HDF5)
message(STATUS "      WITH_BENCHMARK     false   (Google Benchmark)")
ENDIF(WITH_BENCHMARK)
message(STATUS "")
message(STATUS "Checking the dependencies: ")



# -----------------------------------------------------------------------------
# Look for GMP (The GNU Multiple Precision Arithmetic Library)
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(GMP_FOUND_DGTAL 0)
IF(WITH_GMP)
  FIND_PACKAGE(GMP REQUIRED)
  IF(GMP_FOUND)
    INCLUDE_DIRECTORIES(${GMP_INCLUDE_DIR})
    SET(GMP_FOUND_DGTAL 1)
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${GMPXX_LIBRARIES} ${GMP_LIBRARIES})
    message(STATUS "GMP and GMPXX found." )
    ADD_DEFINITIONS("-DWITH_GMP ")
    SET(DGtalLibInc ${DGtalLibInc} ${GMP_INCLUDE_DIR})
  ELSE(GMP_FOUND)
    message(FATAL_ERROR "GMP not found. Check the cmake variables associated to this package or disable it." )
  ENDIF(GMP_FOUND)

  try_compile(
    GMP_HAS_IOSTREAM
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/cmake/src/gmp/gmpstream.cpp
    CMAKE_FLAGS
    -DINCLUDE_DIRECTORIES:STRING=${GMP_INCLUDE_DIR}
    -DLINK_LIBRARIES:STRING=${GMPXX_LIBRARIES}\;${GMP_LIBRARIES}
    OUTPUT_VARIABLE OUTPUT
    )

  if ( GMP_HAS_IOSTREAM )
    add_definitions("-DGMP_HAS_IOSTREAM")
    message(STATUS "   * GMPXX has iostream capabilities")
  ELSE(GMP_HAS_IOSTREAM)
    message(STATUS ${OUTPUT})
    message(STATUS "   * GMPXX does not have iostream capabilities")
    message(FATAL_ERROR "GMP has been found but there is a link isuse with some g++ versions. Please check your system or disable the GMP dependency." )
  endif (GMP_HAS_IOSTREAM )
ENDIF(WITH_GMP)

# -----------------------------------------------------------------------------
# Look for GraphicsMagic
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(MAGICK++_FOUND_DGTAL 0)
IF(WITH_MAGICK)
  FIND_PACKAGE(Magick REQUIRED)
  IF(MAGICK++_FOUND)
     SET(MAGICK++_FOUND_DGTAL 1)
     INCLUDE_DIRECTORIES(${MAGICK++_INCLUDE_DIR})
    message(STATUS "GraphicsMagick++ found." )
    ADD_DEFINITIONS("-DWITH_MAGICK ")
    SET(DGtalLibInc ${DGtalLibInc} ${MAGICK++_INCLUDE_DIR})
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${MAGICK++_LIBRARIES})
  ELSE(MAGICK++_FOUND)
    message(FATAL_ERROR "GraphicsMagick++ not found. Check the cmake variables associated to this package or disable it." )
  ENDIF(MAGICK++_FOUND)
ELSE(WITH_MAGICK)
  UNSET(MAGICK++_INCLUDE_DIR)
  UNSET(MAGICK++_LIBRARIES)
ENDIF(WITH_MAGICK)

# -----------------------------------------------------------------------------
# Look for ITK
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(ITK_FOUND_DGTAL 0)
IF(WITH_ITK)
  FIND_PACKAGE(ITK REQUIRED)
  IF(ITK_FOUND)
    SET(ITK_FOUND_DGTAL 1)
    INCLUDE(${ITK_USE_FILE})
    MESSAGE(STATUS "ITK found ${ITK_USE_FILE}.")

   SET(DGtalLibDependencies ${DGtalLibDependencies} ${ITK_LIBRARIES})
    ADD_DEFINITIONS(" -DWITH_ITK ")
    SET(DGtalLibInc ${DGtalLibInc} ${ITK_INCLUDE_DIRS})


    ## We test if ITK build accepts cpp11 compilers
    try_compile( CPP11_ITK
      ${CMAKE_BINARY_DIR}/CMakeTmp
      ${CMAKE_SOURCE_DIR}/cmake/src/ITKcpp11Bug/
      ITKCPP11BUG
      CMAKE_FLAGS "-DITK_DIR=${ITK_DIR}"
      OUTPUT_VARIABLE OUTPUT )
    if ( CPP11_ITK )
      message(STATUS "ITK accepts [c++11]" )
    else ( CPP11_ITK )
      message(STATUS "ITK does not accept [c++11]" )
      MESSAGE(FATAL_ERROR "ITK was found but it appears that the package was not built with std-cpp11 extension and DGtal will not compile.")
    endif ( CPP11_ITK )

    # -------------------------------------------------------------------------
    # This test is for instance used for ITK v3.x. ITK forces a limited
    # template depth. We remove this option.
    # --------------------------------------------------------------------------
    if (CMAKE_CXX_FLAGS MATCHES "-ftemplate-depth-[0-9]*")
       message( "Warning: some package has enabled a limited template depth for the C++ compiler." )
       message( "         Disabling option -ftemplate-depth-xx in CMAKE_CXX_FLAGS." )
       set( CMAKE_CXX_FLAGS_TMP ${CMAKE_CXX_FLAGS} )
       STRING( REGEX REPLACE "-ftemplate-depth-[0-9]*" ""
   CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP}" )
       message ("         CMAKE_CXX_FLAGS=" ${CMAKE_CXX_FLAGS} )
     endif (CMAKE_CXX_FLAGS MATCHES "-ftemplate-depth-[0-9]*")

  ELSE(ITK_FOUND)
    MESSAGE(FATAL_ERROR "ITK not found. Check the cmake variables associated to this package or disable it.")
  ENDIF(ITK_FOUND)
ENDIF(WITH_ITK)

# -----------------------------------------------------------------------------
# Look for Cairo (2D graphics library)
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(CAIRO_FOUND_DGTAL 0)
IF(WITH_CAIRO)
  FIND_PACKAGE(Cairo REQUIRED)
  IF(CAIRO_FOUND)
    INCLUDE_DIRECTORIES(${CAIRO_INCLUDE_DIRS})
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${CAIRO_LIBRAIRIES})
    message(STATUS "cairo found")
    SET(CAIRO_FOUND_DGTAL 1)
    SET(DGtalLibInc ${DGtalLibInc} ${CAIRO_INCLUDE_DIRS})
    ADD_DEFINITIONS("-DWITH_CAIRO ")
  ELSE(CAIRO_FOUND)
    message(FATAL_ERROR "cairo not found. Check the cmake variables associated to this package or disable it." )
  ENDIF(CAIRO_FOUND)
ELSE(WITH_CAIRO)
  unset(CAIRO_INCLUDE_DIRS)
  unset(CAIRO_LIBRAIRIES)
ENDIF(WITH_CAIRO)

# -----------------------------------------------------------------------------
# Look for HDF5 (data model and file format for storing and managing data)
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(HDF5_FOUND_DGTAL 0)
IF(WITH_HDF5)
  FIND_PACKAGE (HDF5 REQUIRED HL C)
  IF(HDF5_FOUND)
    INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
    message(STATUS "HDF5 found")
    SET(HDF5_FOUND_DGTAL 1)
    SET(DGtalLibInc ${DGtalLibInc} ${HDF5_INCLUDE_DIRS})
    ADD_DEFINITIONS("-DWITH_HDF5 ")
  ELSE(HDF5_FOUND)
    message(FATAL_ERROR "HDF5 not found. Check the cmake variables associated to this package or disable it." )
  ENDIF(HDF5_FOUND)
ELSE(WITH_HDF5)
  unset(HDF5_INCLUDE_DIRS)
  unset(HDF5_LIBRARIES)
ENDIF(WITH_HDF5)


# -----------------------------------------------------------------------------
# Look for Qt (needed by libqglviewer visualization).
# -----------------------------------------------------------------------------
set(QT4_FOUND_DGTAL 0)
set(QT5_FOUND_DGTAL 0)
if (WITH_QGLVIEWER)
  if (WITH_QT5)
    find_package(Qt5 COMPONENTS Widgets OpenGL Xml REQUIRED)

    if (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND AND Qt5Xml_FOUND)
      set(QT5_FOUND_DGTAL 1)
      message(STATUS "Qt5 (Widgets, OpenGL and Xml modules) found (needed by QGLViewer compiled with Qt5).")

      add_definitions("-DWITH_QT5")

      set(DGtalLibDependencies ${DGtalLibDependencies}
                               ${Qt5Widgets_LIBRARIES}
                               ${Qt5OpenGL_LIBRARIES}
                               ${Qt5Xml_LIBRARIES})
      set(DGtalLibInc ${DGtalLibInc}
                      ${Qt5Widgets_INCLUDES_DIRS}
                      ${Qt5OpenGL_INCLUDES_DIR}
                      ${Qt5Xml_INCLUDES_DIR})
    else (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND AND Qt5Xml_FOUND)
      message(STATUS "One of Qt5's modules was not found (needed by QGLViewer).")
    endif (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND AND Qt5Xml_FOUND)

  else (WITH_QT5)
    if (APPLE)
      message(STATUS "Warning: on recent MacOs Sierra, Qt4 is no longer supported.")
      message(STATUS "         Please consider switching to Qt5 and define WITH_QT5.")
      message(STATUS "         Otherwise you may have cmake errors while generating the project.")
    endif (APPLE)

    find_package(Qt4 COMPONENTS QtCore QtGUI QtXml QtOpenGL REQUIRED)

    if (QT4_FOUND)
      set(QT4_FOUND_DGTAL 1)
      message(STATUS  "Qt4 found (needed by QGLVIEWER).")
      set(QT_USE_QTXML 1)
      add_definitions("-DWITH_QT4")
      include(${QT_USE_FILE})
      set(DGtalLibDependencies ${DGtalLibDependencies} ${QT_LIBRARIES} )
      set(DGtalLibInc ${DGtalLibInc} ${QT_INCLUDE_DIR})
    else (QT4_FOUND)
      message(FATAL_ERROR "Qt4 not found (needed by QGLVIEWER). Check the cmake variables associated to this package or disable it.")
    endif (QT4_FOUND)
  endif (WITH_QT5)
endif(WITH_QGLVIEWER)

# -----------------------------------------------------------------------------
# Look for QGLViewer for 3D display.
# (They are not compulsory).
# -----------------------------------------------------------------------------
set(QGLVIEWER_FOUND_DGTAL 0)
set(WITH_VISU3D 0)
if (WITH_QGLVIEWER)
  find_package(QGLVIEWER REQUIRED)
  if (QGLVIEWER_FOUND)

    find_package(OpenGL REQUIRED)
      message(STATUS  "libQGLViewer found.")
    if (OPENGL_GLU_FOUND)
      message(STATUS  "  (OpenGL-GLU ok) " ${OPENGL_INCLUDE_DIR})
    else (OPENGL_GLU_FOUND)
      message(FATAL_ERROR  "  libQGLViewer found but your system does not have OpenGL/GLU modules." )
    endif(OPENGL_GLU_FOUND)

    include_directories( ${QGLVIEWER_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    set(WITH_VISU3D_QGLVIEWER 1)
    set(QGLVIEWER_FOUND_DGTAL 1)
    add_definitions("-DWITH_VISU3D_QGLVIEWER ")
    set(DGtalLibDependencies ${DGtalLibDependencies} ${QGLVIEWER_LIBRARIES} ${OPENGL_LIBRARIES}  )
    set(WITH_VISU3D 1)
  else (QGLVIEWER_FOUND)
    message(FATAL_ERROR  "libQGLViewer not found.  Check the cmake variables associated to this package or disable it." )
  endif (QGLVIEWER_FOUND)
endif (WITH_QGLVIEWER)

# -----------------------------------------------------------------------------
# Look for OpenMP
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(OPENMP_FOUND_DGTAL 0)
IF(WITH_OPENMP)
  FIND_PACKAGE(OpenMP REQUIRED)
  IF(OPENMP_FOUND)
    SET(OPENMP_FOUND_DGTAL 1)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(DGtalLibDependencies ${DGtalLibDependencies} ${OpenMP_CXX_LIBRARIES})
    ADD_DEFINITIONS("-DWITH_OPENMP ")
    message(STATUS "OpenMP found. Libs: ${OpenMP_CXX_LIBRARIES}")
  ELSE(OPENMP_FOUND)
    message(FATAL_ERROR "OpenMP support not available.")
  ENDIF(OPENMP_FOUND)
ENDIF(WITH_OPENMP)

# -----------------------------------------------------------------------------
# Look for Eigen3
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(EIGEN_FOUND_DGTAL 0)
IF(WITH_EIGEN)
  FIND_PACKAGE(Eigen3 REQUIRED)
  IF(EIGEN3_FOUND)
    SET(EIGEN_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_EIGEN ")
    include_directories( ${EIGEN3_INCLUDE_DIR})
    message(STATUS "Eigen3 (version ${EIGEN3_VERSION}) found.")
  ELSE(EIGEN3_FOUND)
    message(FATAL_ERROR "Eigen3 is not found or the installed version (${EIGEN3_VERSION}) is below 3.2.1. ")
  ENDIF(EIGEN3_FOUND)
ENDIF(WITH_EIGEN)

# -----------------------------------------------------------------------------
# Look for CGAL
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(CGAL_FOUND_DGTAL 0)
IF(WITH_CGAL)
  IF (WITH_GMP AND  WITH_EIGEN)
    message(STATUS "GMP and Eigen3 detected for CGAL.")
  ELSE()
    message(FATAL_ERROR "CGAL needs GMP and Eigen3. You must activate  WITH_GMP and WITH_EIGEN flags and have the associated package installed.")
  ENDIF()

  find_package(CGAL COMPONENTS Core Eigen3 BLAS LAPACK)
  IF(CGAL_FOUND)
    include( ${CGAL_USE_FILE} )
    SET(CGAL_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DCGAL_EIGEN3_ENABLED   ")
    ADD_DEFINITIONS("-DWITH_CGAL ")
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${CGAL_LIBRARIES} ${CGAL_3D_PARTY-LIBRARIES} )
    ## Making sure that CGAL got the Eigen3 flag
    ADD_DEFINITIONS("-DWITH_Eigen3 -DWITH_LAPACK ")
    message(STATUS "CGAL found.")
  ENDIF(CGAL_FOUND)
ENDIF(WITH_CGAL)

# -----------------------------------------------------------------------------
# Look for Patate
# http://patate.gforge.inria.fr/html/index.html
# (they Are not compulsory).
# -----------------------------------------------------------------------------
SET(PATATE_FOUND_DGTAL 0)
IF(WITH_PATATE)
  IF (WITH_EIGEN)
    message(STATUS "Eigen3 detected for PATATE.")
  ELSE()
    message(FATAL_ERROR "PATATE needs  Eigen3. You must activate  WITH_EIGEN flags and have the associated package installed.")
  ENDIF()
  find_package(Patate)
  IF(PATATE_FOUND)
    SET(DGtalLibInc ${DGtalLibInc} ${PATATE_INCLUDE_DIR})
    INCLUDE_DIRECTORIES( ${PATATE_INCLUDE_DIR})
    SET(PATATE_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_PATATE ")
    ADD_DEFINITIONS("-DWITH_Eigen3 ")
    message(STATUS "PATATE found. ${PATATE_INCLUDE_DIR} ")
 ELSE(PATATE_FOUND)
   message(FATAL_ERROR "Patate headers not found.")
 ENDIF(PATATE_FOUND)
ENDIF(WITH_PATATE)

# -----------------------------------------------------------------------------
# Look for Google Benchmark
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(BENCHMARK_FOUND_DGTAL 0)
IF(WITH_BENCHMARK)
  FIND_PACKAGE(Benchmark REQUIRED)
  IF(BENCHMARK_FOUND)
    SET(BENCHMARK_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_BENCHMARK ")
    include_directories( ${BENCHMARK_INCLUDE_DIR})
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${BENCHMARK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
    message(STATUS "Google Benchmark found.   ${BENCHMARK_LIBRARIES}")
  ELSE(BENCHMARK_FOUND)
   message(FATAL_ERROR "Google benchmark not installed. Please disable WITH_BENCHMARK or install it.")
 ENDIF(BENCHMARK_FOUND)
ENDIF(WITH_BENCHMARK)

# -----------------------------------------------------------------------------
# Look for FFTW3.
# (They are not compulsory).
# -----------------------------------------------------------------------------
SET(FFTW3_FOUND_DGTAL 0)
IF(WITH_FFTW3)
  FIND_PACKAGE(FFTW3 REQUIRED)
  IF(FFTW3_FOUND)
    SET(FFTW3_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_FFTW3 ")
    INCLUDE_DIRECTORIES(${FFTW3_INCLUDES})
    SET(DGtalLibDependencies ${DGtalLibDependencies} ${FFTW3_LIBRARIES} ${FFTW3_DEP_LIBRARIES} )
    message(STATUS "FFTW3 is found : ${FFTW3_LIBRARIES}.")
  ELSE(FFTW3_FOUND)
    message(FATAL_ERROR "FFTW3 is not found.")
  ENDIF(FFTW3_FOUND)

  IF(FFTW3_FLOAT_FOUND)
    SET(FFTW3_FLOAT_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_FFTW3_FLOAT ")
  ENDIF(FFTW3_FLOAT_FOUND)

  IF(FFTW3_DOUBLE_FOUND)
    SET(FFTW3_DOUBLE_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_FFTW3_DOUBLE ")
  ENDIF(FFTW3_DOUBLE_FOUND)

  IF(FFTW3_LONG_FOUND)
    SET(FFTW3_LONG_FOUND_DGTAL 1)
    ADD_DEFINITIONS("-DWITH_FFTW3_LONG ")
  ENDIF(FFTW3_LONG_FOUND)

ENDIF(WITH_FFTW3)

message(STATUS "-------------------------------------------------------------------------------")
