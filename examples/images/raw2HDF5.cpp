/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file images/raw2HDF5.cpp
 * @ingroup Examples
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/08/28
 *
 * @brief A raw to HDF5 converter example (first version, restriction: only 3D UInt8 data input file, HDF5 output file with ZLIB compression activated)
 *
 * This file is part of the DGtal library.
 */

/**
 *  Example of image format transformation from raw to HDF5.
 *   @see @ref  dgtalBigImagesAbstract   
 *  \example images/raw2HDF5.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include <hdf5.h>

#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageFactoryFromHDF5.h"
#include "DGtal/io/writers/VolWriter.h"

#include "ConfigExamples.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

#define DATASETNAME_3D    "UInt8Array3D"
#define RANK_3D           3

bool raw2HDF5_3D(char *rawFilename, int sizeX, int sizeY, int sizeZ, int sizeChunk, char *HDF5Filename)
{
  trace.beginBlock("raw2HDF5_3D");
  
  trace.info() << "begin" << endl;
  
  hid_t               file, dataset;                // file and dataset handles
  hid_t               datatype, dataspace;          // handles
  hsize_t             dimsf[RANK_3D];               // dataset dimensions
  herr_t              status;
  DGtal::uint8_t      *data;
  
  // compressed dataset
  hid_t plist_id;
  hsize_t cdims[RANK_3D];
  // compressed dataset
  
  // Data and output buffer initialization.
  FILE* fd = NULL;
  fd = fopen(rawFilename, "rb");
  if (fd == NULL)
  {
    trace.error() << " fopen error" << endl;
    return false;
  }
  trace.info() << " open raw_file: " << rawFilename << " size_X: " << sizeX << " size_Y: " << sizeY << " size_Z: " << sizeZ << " size_CHUNK: " << sizeChunk << endl;
  
  data = (DGtal::uint8_t*)malloc(sizeZ*sizeY*sizeX * sizeof(DGtal::uint8_t));
  if (data == NULL)
  {
    trace.error() << " malloc error" << endl;
    fclose(fd);
    return false;
  }
  
  trace.info() << " begin read" << endl;
  if (fread(data, 1, sizeZ*sizeY*sizeX, fd) != (unsigned)sizeZ*sizeY*sizeX)
  {
    trace.error() << " fread failed" << endl;
    fclose(fd);
    return false;
  }
  trace.info() << " end read" << endl;
  
  fclose(fd);
  
  /*
   * Create a new file using H5F_ACC_TRUNC access,
   * default file creation properties, and default file
   * access properties.
   */
  file = H5Fcreate(HDF5Filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  
  // Describe the size of the array and create the data space for fixed size dataset.
  dimsf[0] = sizeZ;
  dimsf[1] = sizeY;
  dimsf[2] = sizeX;
  dataspace = H5Screate_simple(RANK_3D, dimsf, NULL);
  
  // compressed dataset
  plist_id  = H5Pcreate(H5P_DATASET_CREATE);
  
  // Dataset must be chunked for compression.
  cdims[0] = sizeChunk;
  cdims[1] = sizeChunk;
  cdims[2] = sizeChunk;
  status = H5Pset_chunk(plist_id, RANK_3D, cdims);
  if (status)
  {
    trace.error() << " H5Dchunck error" << std::endl;
    free(data);
    return false;
  }
  
  // --> Compression levels :
  // 0            No compression
  // 1            Best compression speed; least compression
  // 2 through 8  Compression improves; speed degrades
  // 9            Best compression ratio; slowest speed
  //
  // Set ZLIB / DEFLATE Compression using compression level 6.
  status = H5Pset_deflate(plist_id, 6);
  if (status)
  {
    trace.error() << " H5Ddeflate error" << std::endl;
    free(data);
    return false;
  }
  // compressed dataset
  
  /*
   * Define datatype for the data in the file.
   */
  datatype = H5Tcopy(H5T_NATIVE_UINT8);
  status = H5Tset_order(datatype, H5T_ORDER_LE);
  if (status)
  {
    trace.error() << " H5Dset_order error" << std::endl;
    free(data);
    return false;
  }
  
  /*
   * Create a new dataset within the file using defined dataspace and
   * datatype and default dataset creation properties.
   */
  dataset = H5Dcreate2(file, DATASETNAME_3D, datatype, dataspace,
                       H5P_DEFAULT, /*H5P_DEFAULT*/plist_id, H5P_DEFAULT); // here to activate compressed dataset
  
  // Write the data to the dataset using default transfer properties.
  trace.info() << " begin write hdf5_file: " << HDF5Filename << endl;
  status = H5Dwrite(dataset, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
  if (status)
  {
    trace.error() << " H5Dwrite error" << std::endl;
    free(data);
    return false;
  }
  else
    trace.info() << " end write hdf5_file" << endl;
  
  // Close/release resources.
  H5Sclose(dataspace);
  H5Tclose(datatype);
  H5Dclose(dataset);
  // compressed dataset
  H5Pclose(plist_id);
  // compressed dataset
  H5Fclose(file);
  
  free(data);
  
  trace.info() << "end" << endl;
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}

bool HDF5_3D2vol(char *HDF5Filename, char *volFileName)
{
  trace.beginBlock("HDF5_3D2vol");
  
  typedef ImageSelector<Z3i::Domain, DGtal::uint8_t>::Type Image;
  
  typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
  MyImageFactoryFromHDF5 factImage(HDF5Filename, DATASETNAME_3D);
  
  typedef MyImageFactoryFromHDF5::OutputImage OutputImage;
  
  OutputImage *volImage = factImage.requestImage( factImage.domain() );
  bool res = VolWriter<OutputImage>::exportVol(volFileName, *volImage);
  factImage.detachImage(volImage);
  
  trace.endBlock();
  
  return res;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  if (argc==7 || argc==8)
  {
    raw2HDF5_3D(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    
    if (argc==8) // TEMP_MT, just for test
      HDF5_3D2vol(argv[6], argv[7]);
  }
  else
  {
    trace.info() << "A raw to HDF5 converter (first version, restriction: only 3D UInt8 data input file, HDF5 output file with ZLIB compression activated)" << endl;
    trace.info() << "Usage: raw2HDF5 <raw_file> <size_X> <size_Y> <size_Z> <size_CHUNK> <hdf5_file>" << endl;
  }
  
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
