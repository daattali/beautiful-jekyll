SET(DGTAL_EXAMPLES_SRC
  exampleCurvature
  exampleLMST2D
  exampleLMST3D
)


FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)
