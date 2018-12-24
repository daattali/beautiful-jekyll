SET(DGTAL_TESTS_SRC_MATH
       testSimpleRegression
       testMeasure
       testSignal
       testStatistics
       testHistogram
       testMPolynomial
       testAngleLinearMinimizer
       testBasicMathFunctions
       testMultiStatistics
       testProfile
       testMeaningfulScaleAnalysis
       )

if (WITH_FFTW3)
  set (DGTAL_TESTS_SRC_MATH ${DGTAL_TESTS_SRC_MATH} testRealFFT)
endif (WITH_FFTW3)


FOREACH(FILE ${DGTAL_TESTS_SRC_MATH})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

add_subdirectory(linalg)
