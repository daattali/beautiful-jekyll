SET(DGTAL_EXAMPLES_SRC
        approximation
        convergents
        fraction
        pattern
        lower-integer-convex-hull
)

FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries ( ${FILE} DGtal 
                          ${DGtalLibDependencies})

ENDFOREACH(FILE)

if ( WITH_GMP )
   SET( DGTAL_EXAMPLES_GMP_SRC
        convergents-biginteger
        extended-euclid
   )
  FOREACH(FILE ${DGTAL_EXAMPLES_GMP_SRC})
   add_executable(${FILE} ${FILE})
   target_link_libraries ( ${FILE} DGtal 
                           ${DGtalLibDependencies})
  ENDFOREACH(FILE)

endif ( WITH_GMP )
