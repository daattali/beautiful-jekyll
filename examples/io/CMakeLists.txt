SET(DGTAL_EXAMPLES_IO_SRC
	display3DToOFF
)

FOREACH(FILE ${DGTAL_EXAMPLES_IO_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal)
ENDFOREACH(FILE)


if (  WITH_VISU3D_QGLVIEWER )
  SET(DGTAL_EXAMPLES_QGL_SRC
    digitalSetFromVol
    digitalSetFromPointList
    meshFromOFF
    viewDualSurface
    )
  FOREACH(FILE ${DGTAL_EXAMPLES_QGL_SRC}) 
    add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE}  DGtal
      ${DGtalLibDependencies})   
  ENDFOREACH(FILE)
  
add_subdirectory(viewers)
endif ( WITH_VISU3D_QGLVIEWER   )

add_subdirectory(boards)

