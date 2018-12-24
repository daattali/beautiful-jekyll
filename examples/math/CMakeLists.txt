SET(DGTAL_EXAMPLES_MATH_SRC
        polynomial-derivative
        polynomial2-derivative
	polynomial-read
)

FOREACH(FILE ${DGTAL_EXAMPLES_MATH_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
ENDFOREACH(FILE)
