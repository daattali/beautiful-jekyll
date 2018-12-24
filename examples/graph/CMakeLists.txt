SET(DGTAL_EXAMPLES_TOPO_SRC
  graphTraversal
)

FOREACH(FILE ${DGTAL_EXAMPLES_TOPO_SRC}) 
  add_executable(${FILE} ${FILE})
  target_link_libraries ( ${FILE}  DGtal
    ${DGtalLibDependencies})   
ENDFOREACH(FILE)


if ( WITH_VISU3D_QGLVIEWER )
   SET(DGTAL_EXAMPLES_QGL_SRC
     volDistanceTraversal
   )
   FOREACH(FILE ${DGTAL_EXAMPLES_QGL_SRC}) 
     add_executable(${FILE} ${FILE})
     target_link_libraries ( ${FILE}  DGtal
                             ${DGtalLibDependencies})   
   ENDFOREACH(FILE)
endif ( WITH_VISU3D_QGLVIEWER   )

