


SET(QGLVIEWER_EXAMPLES_SRC
   extract2DImagesFrom3DandVisu
  )

if (  WITH_VISU3D_QGLVIEWER )

  FOREACH(FILE ${QGLVIEWER_EXAMPLES_SRC}) 
   add_executable(${FILE} ${FILE})
    target_link_libraries ( ${FILE}  DGtal
                            ${DGtalLibDependencies})   
  ENDFOREACH(FILE)

endif ( WITH_VISU3D_QGLVIEWER   )




SET(DGTAL_EXAMPLES_SRC
  exampleConstImageAdapter
  exampleTiledImage
  extract2DImagesFrom3D
  extract2DSlicesImagesFrom3D
  imageBasicSubsampling
  exampleRigidtransformation2d
  exampleRigidtransformation3d
  exampleArrayImageAdapter
)

if( WITH_HDF5 )
  SET(DGTAL_EXAMPLES_SRC ${DGTAL_EXAMPLES_SRC} 
  raw2HDF5
  exampleImageFactoryFromHDF5)
endif( WITH_HDF5 )

FOREACH(FILE ${DGTAL_EXAMPLES_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  )
ENDFOREACH(FILE)
