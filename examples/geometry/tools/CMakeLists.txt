add_subdirectory(determinant)

SET(DGTAL_EXAMPLES_SRC
  examplePreimage
  exampleConvexHull2D
  exampleAlphaShape
)


FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)



