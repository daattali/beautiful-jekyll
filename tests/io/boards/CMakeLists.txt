SET(DGTAL_TESTS_SRC_IO_BOARDS
       testBoard3D
       testBallQuad)


FOREACH(FILE ${DGTAL_TESTS_SRC_IO_BOARDS})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
