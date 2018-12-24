

SET(DGTAL_TESTS_SRC_IOVIEWERS
  testColor
  testSimpleBoard
  testBoard2DCustomStyle
  testLongvol
  testArcDrawing )

if (WITH_ITK)
    set(DGTAL_TESTS_SRC_IOVIEWERS ${DGTAL_TESTS_SRC_IOVIEWERS} testITKio)
endif (WITH_ITK)

FOREACH(FILE ${DGTAL_TESTS_SRC_IOVIEWERS})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


add_subdirectory(viewers)
add_subdirectory(boards)
add_subdirectory(colormaps)
add_subdirectory(readers)
add_subdirectory(writers)
