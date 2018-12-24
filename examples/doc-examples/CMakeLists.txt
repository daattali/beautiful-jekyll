SET(DGTAL_DOC_EX_SRC
  demo-kernel-1
  kernelDomain
  range
  labelledMapBestParameters
  exampleCatch
  )

if( WITH_VISU3D_QGLVIEWER  )
  SET(DGTAL_DOC_EX_SRC_QGL
     )

FOREACH(FILE ${DGTAL_DOC_EX_SRC_QGL})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE}  DGtal)
ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER )


FOREACH(FILE ${DGTAL_DOC_EX_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal )
ENDFOREACH(FILE)

