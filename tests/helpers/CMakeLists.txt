SET(DGTAL_TESTS_SRC_HELPERS
  testParametricShape
  testImplicitShape
  )

FOREACH(FILE ${DGTAL_TESTS_SRC_HELPERS})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

