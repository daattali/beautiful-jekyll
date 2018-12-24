add_subdirectory(estimation)
add_subdirectory(distance)


SET(DGTAL_TESTS_VOLUMES_SRC
  testKanungo
  )

FOREACH(FILE ${DGTAL_TESTS_VOLUMES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

