add_subdirectory(distance)

SET(DGTAL_EXAMPLES_SRC
        dvcm-2d
)

FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)

