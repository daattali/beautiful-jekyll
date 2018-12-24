SET(DGTAL_TESTS_SRC_IO_READERS
       testPNMReader
       testVolReader
       testRawReader
       testGenericReader
       testPointListReader
       testTableReader
       testMeshReader
       testMPolynomialReader )


FOREACH(FILE ${DGTAL_TESTS_SRC_IO_READERS})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} DGtal  ${DGtalLibDependencies})
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


IF(MAGICK++_FOUND)

  SET(DGTAL_TESTS_SRC_IO_READERS_Magick
    testMagickReader
    )

  FOREACH(FILE ${DGTAL_TESTS_SRC_IO_READERS_Magick})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)

ENDIF(MAGICK++_FOUND)


IF(HDF5_FOUND)

  SET(DGTAL_TESTS_SRC_IO_READERS_HDF5
    testHDF5Reader
    )

  FOREACH(FILE ${DGTAL_TESTS_SRC_IO_READERS_HDF5})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)

ENDIF(HDF5_FOUND)

IF(ITK_FOUND)

  SET(DGTAL_TESTS_SRC_IO_READERS_DICOM
    testDicomReader
    testITKReader
  )

  FOREACH(FILE ${DGTAL_TESTS_SRC_IO_READERS_DICOM})
    add_executable(${FILE} ${FILE})
    target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    add_test(${FILE} ${FILE})
  ENDFOREACH(FILE)

ENDIF(ITK_FOUND)
