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
 * @file testImageFactoryFromHDF5.cpp
 * @ingroup Tests
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/16
 *
 * @brief A test file for ImageFactoryFromHDF5.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageFactoryFromHDF5.h"
#include "DGtal/images/ImageCache.h"
#include "DGtal/images/TiledImage.h"

#include "ConfigTest.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImageFactoryFromHDF5.
///////////////////////////////////////////////////////////////////////////////

#define H5FILE_NAME     "testImageFactoryFromHDF5.h5"

#define DATASETNAME_2D  "Int32Array2D"
#define NX_2D           6       // dataset dimensions
#define NY_2D           5
#define RANK_2D         2

bool writeHDF5_2D()
{
    hid_t               file, dataset;          // file and dataset handles
    hid_t               datatype, dataspace;    // handles
    hsize_t             dimsf[RANK_2D];         // dataset dimensions
    herr_t              status;
    DGtal::int32_t      data[NY_2D][NX_2D];     // data to write
    int         i, j;

    // Data  and output buffer initialization.
    for(j = 0; j < NY_2D; j++)
        for(i = 0; i < NX_2D; i++)
            data[j][i] = j + i;
    /*
     * 0 1 2 3 4 5
     * 1 2 3 4 5 6
     * 2 3 4 5 6 7
     * 3 4 5 6 7 8
     * 4 5 6 7 8 9
     */

    /*
     * Create a new file using H5F_ACC_TRUNC access,
     * default file creation properties, and default file
     * access properties.
     */
    file = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Describe the size of the array and create the data space for fixed size dataset.
    dimsf[0] = NY_2D;
    dimsf[1] = NX_2D;
    dataspace = H5Screate_simple(RANK_2D, dimsf, NULL);

    /*
     * Define datatype for the data in the file.
     */
    datatype = H5Tcopy(H5T_NATIVE_INT32);
    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspace and
     * datatype and default dataset creation properties.
     */
    dataset = H5Dcreate2(file, DATASETNAME_2D, datatype, dataspace,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the data to the dataset using default transfer properties.
    status = H5Dwrite(dataset, H5T_NATIVE_INT32, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status)
    {
      trace.error() << " H5Dwrite error" << std::endl;
      return false;
    }

    // Close/release resources.
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return true;
}

#define DATASETNAME_2D_TILED    "Int64Array2D"
#define RANK_2D_TILED           2
#define _NX_2D_TILED		16
#define _NY_2D_TILED		16

bool writeHDF5_2D_TILED(const std::string & _H5FILE_NAME_2D_TILED)
{
    hid_t               file, dataset;                          // file and dataset handles
    hid_t               datatype, dataspace;                    // handles
    hsize_t             dimsf[RANK_2D_TILED];                   // dataset dimensions
    herr_t              status;
    DGtal::int64_t      data[_NY_2D_TILED][_NX_2D_TILED];       // data to write
    int         i, j;

    int ii=1;
    // Data  and output buffer initialization.
    for(j = 0; j < _NY_2D_TILED; j++)
        for(i = 0; i < _NX_2D_TILED; i++)
            data[j][i] = ii++;

    /*
     * Create a new file using H5F_ACC_TRUNC access,
     * default file creation properties, and default file
     * access properties.
     */
    file = H5Fcreate(_H5FILE_NAME_2D_TILED.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Describe the size of the array and create the data space for fixed size dataset.
    dimsf[0] = _NY_2D_TILED;
    dimsf[1] = _NX_2D_TILED;
    dataspace = H5Screate_simple(RANK_2D_TILED, dimsf, NULL);

    /*
     * Define datatype for the data in the file.
     */
    datatype = H5Tcopy(H5T_NATIVE_INT64);
    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspace and
     * datatype and default dataset creation properties.
     */
    dataset = H5Dcreate2(file, DATASETNAME_2D_TILED, datatype, dataspace,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the data to the dataset using default transfer properties.
    status = H5Dwrite(dataset, H5T_NATIVE_INT64, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status)
    {
      trace.error() << " H5Dwrite error" << std::endl;
      return false;
    }

    // Close/release resources.
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return true;
}

#define H5FILE_NAME_3D_TILED_EASY_READING       "testImageFactoryFromHDF5_TILED_3D_for_easy_reading.h5"
#define H5FILE_NAME_3D_TILED                    "testImageFactoryFromHDF5_TILED_3D.h5"

#define DATASETNAME_3D_TILED    "DoubleArray3D"
#define NX_3D_TILED             10      // dataset dimensions
#define NY_3D_TILED             8
#define NZ_3D_TILED             6
#define RANK_3D_TILED           3

bool writeHDF5_3D_TILED_for_easy_reading()
{
    hid_t       file, dataset;                                  // file and dataset handles
    hid_t       datatype, dataspace;                            // handles
    hsize_t     dimsf[RANK_3D_TILED];                           // dataset dimensions
    herr_t      status;
    double      data[NY_3D_TILED][NX_3D_TILED][NZ_3D_TILED];    // data to write
    int         i, j, k;

    int ii=1;
    // Data  and output buffer initialization.
    for(k = 0; k < NZ_3D_TILED; k++)
      for(j = 0; j < NY_3D_TILED; j++)
        for(i = 0; i < NX_3D_TILED; i++)
          data[j][i][k] = ii++;

    /*
     * Create a new file using H5F_ACC_TRUNC access,
     * default file creation properties, and default file
     * access properties.
     */
    file = H5Fcreate(H5FILE_NAME_3D_TILED_EASY_READING, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Describe the size of the array and create the data space for fixed size dataset.
    dimsf[0] = NY_3D_TILED;
    dimsf[1] = NX_3D_TILED;
    dimsf[2] = NZ_3D_TILED;
    dataspace = H5Screate_simple(RANK_3D_TILED, dimsf, NULL);

    /*
     * Define datatype for the data in the file.
     */
    datatype = H5Tcopy(H5T_NATIVE_DOUBLE);
    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspace and
     * datatype and default dataset creation properties.
     */
    dataset = H5Dcreate2(file, DATASETNAME_3D_TILED, datatype, dataspace,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the data to the dataset using default transfer properties.
    status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status)
    {
      trace.error() << " H5Dwrite error" << std::endl;
      return false;
    }

    // Close/release resources.
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return true;
}

bool writeHDF5_3D_TILED()
{
    hid_t       file, dataset;                                  // file and dataset handles
    hid_t       datatype, dataspace;                            // handles
    hsize_t     dimsf[RANK_3D_TILED];                           // dataset dimensions
    herr_t      status;
    double      data[NZ_3D_TILED][NY_3D_TILED][NX_3D_TILED];    // data to write
    int         i, j, k;

    int ii=1;
    // Data  and output buffer initialization.
    for(k = 0; k < NZ_3D_TILED; k++)
      for(j = 0; j < NY_3D_TILED; j++)
        for(i = 0; i < NX_3D_TILED; i++)
          data[k][j][i] = ii++;

    /*
     * Create a new file using H5F_ACC_TRUNC access,
     * default file creation properties, and default file
     * access properties.
     */
    file = H5Fcreate(H5FILE_NAME_3D_TILED, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Describe the size of the array and create the data space for fixed size dataset.
    dimsf[0] = NZ_3D_TILED;
    dimsf[1] = NY_3D_TILED;
    dimsf[2] = NX_3D_TILED;
    dataspace = H5Screate_simple(RANK_3D_TILED, dimsf, NULL);

    /*
     * Define datatype for the data in the file.
     */
    datatype = H5Tcopy(H5T_NATIVE_DOUBLE);
    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspace and
     * datatype and default dataset creation properties.
     */
    dataset = H5Dcreate2(file, DATASETNAME_3D_TILED, datatype, dataspace,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the data to the dataset using default transfer properties.
    status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status)
    {
      trace.error() << " H5Dwrite error" << std::endl;
      return false;
    }

    // Close/release resources.
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return true;
}

bool test2D_int32()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock("Testing ImageFactoryFromHDF5 (2D)");

  typedef ImageSelector<Z2i::Domain, DGtal::int32_t>::Type Image;

  // 1) ImageFactoryFromHDF5
  typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
  MyImageFactoryFromHDF5 factImage(H5FILE_NAME, DATASETNAME_2D);

  typedef MyImageFactoryFromHDF5::OutputImage OutputImage;

  Z2i::Domain domain1(Z2i::Point(0,0), Z2i::Point(1,1));
  OutputImage *image1 = factImage.requestImage(domain1);
  OutputImage::ConstRange r1 = image1->constRange();
  cout << "image1: "; std::copy( r1.begin(), r1.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  Z2i::Domain domain1b(Z2i::Point(0,0), Z2i::Point(2,2));
  OutputImage *image1b = factImage.requestImage(domain1b);
  OutputImage::ConstRange r1b = image1b->constRange();
  cout << "image1b: "; std::copy( r1b.begin(), r1b.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  Z2i::Domain domain2(Z2i::Point(2,0), Z2i::Point(3,1));
  OutputImage *image2 = factImage.requestImage(domain2);
  OutputImage::ConstRange r2 = image2->constRange();
  cout << "image2: "; std::copy( r2.begin(), r2.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  Z2i::Domain domain3(Z2i::Point(0,2), Z2i::Point(1,3));
  OutputImage *image3 = factImage.requestImage(domain3);
  OutputImage::ConstRange r3 = image3->constRange();
  cout << "image3: "; std::copy( r3.begin(), r3.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  Z2i::Domain domain4(Z2i::Point(2,2), Z2i::Point(3,3));
  OutputImage *image4 = factImage.requestImage(domain4);
  OutputImage::ConstRange r4 = image4->constRange();
  cout << "image4: "; std::copy( r4.begin(), r4.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  Z2i::Domain domain5(Z2i::Point(3,2), Z2i::Point(5,4));
  OutputImage *image5 = factImage.requestImage(domain5);
  OutputImage::ConstRange r5 = image5->constRange();
  cout << "image5: "; std::copy( r5.begin(), r5.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;

  // 2) ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WT
  trace.info() << endl << "ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WT" << endl;

  typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyLAST;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromHDF5> MyImageCacheWritePolicyWT;
  MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);

  typedef ImageCache<OutputImage, MyImageFactoryFromHDF5, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyImageCache;
  MyImageCache imageCache(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT);
  OutputImage::Value aValue;

  trace.info() << "READING from cache (empty cache): " << imageCache << endl;
  if (imageCache.read(Z2i::Point(2,2), aValue))
    trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "READ: Point 2,2 is not in an image from cache." << endl;
  nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  imageCache.update(domain1); // image1

  trace.info() << "READING from cache (not empty but wrong domain): " << imageCache << endl;
  if (imageCache.read(Z2i::Point(2,2), aValue))
    trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "READ: Point 2,2 is not in an image from cache." << endl;
  nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  imageCache.update(domain4); // image4

  trace.info() << "READING from cache (not empty but good domain): " << imageCache << endl;
  if (imageCache.read(Z2i::Point(2,2), aValue))
    trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "READ: Point 2,2 is not in an image from cache." << endl;
  nbok += ( (imageCache.read(Z2i::Point(2,2), aValue) && (aValue == 4)) == true ) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.info() << "WRITING from cache (not empty but good domain): " << imageCache << endl;
  aValue = 22;
  if (imageCache.write(Z2i::Point(2,2), aValue))
    trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl;
  nbok += ( (imageCache.read(Z2i::Point(2,2), aValue) && (aValue == 22)) == true ) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  imageCache.update(domain3); // image3

  trace.info() << "WRITING from cache (not empty but wrong domain): " << imageCache << endl;
  aValue = 22;
  if (imageCache.write(Z2i::Point(2,2), aValue))
    trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl;
  nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  imageCache.update(domain1); // image1

  trace.info() << "WRITING from cache (not empty but good domain): " << imageCache << endl;
  aValue = 7;
  if (imageCache.write(Z2i::Point(0,0), aValue))
    trace.info() << "WRITE: Point 0,0 is in an image from cache, value: " << aValue << endl;
  else
    trace.info() << "WRITE: Point 0,0 is not in an image from cache." << endl;
  nbok += ( (imageCache.read(Z2i::Point(0,0), aValue) && (aValue == 7)) == true ) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();

  return nbok == nb;
}

bool testTiledImage2D_int64()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing TiledImage with ImageFactoryFromHDF5 (2D)");

    typedef ImageSelector<Z2i::Domain, DGtal::int64_t>::Type Image;

    typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
    MyImageFactoryFromHDF5 factImage("testImageFactoryFromHDF5_TILED_2D.h5", DATASETNAME_2D_TILED);

    typedef MyImageFactoryFromHDF5::OutputImage OutputImage;

    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyFIFO;
    typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromHDF5> MyImageCacheWritePolicyWT;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(factImage, 2);
    MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);

    typedef TiledImage<Image, MyImageFactoryFromHDF5, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImage;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
    MyTiledImage tiledImage(factImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWT, 4);

    typedef MyTiledImage::OutputImage OutputImage;
    OutputImage::Value aValue;

    trace.info() << "Read value for Point 3,1: " << tiledImage(Z2i::Point(3,1)) << endl;
    nbok += (tiledImage(Z2i::Point(3,1)) == 20) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 9,5: " << tiledImage(Z2i::Point(9,5)) << endl;
    nbok += (tiledImage(Z2i::Point(9,5)) == 90) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 1; tiledImage.setValue(Z2i::Point(10,6), aValue);
    trace.info() << "Write value for Point 10,6: " << aValue << endl;
    nbok += (tiledImage(Z2i::Point(10,6)) == 1) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 1,2: " << tiledImage(Z2i::Point(1,2)) << endl;
    nbok += (tiledImage(Z2i::Point(1,2)) == 34) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 15,0: " << tiledImage(Z2i::Point(15,0)) << endl;
    nbok += (tiledImage(Z2i::Point(15,0)) == 16) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 128; tiledImage.setValue(Z2i::Point(15,0), aValue);
    trace.info() << "Write value for Point 15,0: " << aValue << endl;
    nbok += (tiledImage(Z2i::Point(15,0)) == 128) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.endBlock();

    return nbok == nb;
}

bool testTiledImage3D_double()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing TiledImage with ImageFactoryFromHDF5 (3D)");

    typedef ImageSelector<Z3i::Domain, double>::Type Image;

    typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
    MyImageFactoryFromHDF5 factImage(H5FILE_NAME_3D_TILED, DATASETNAME_3D_TILED);

    typedef MyImageFactoryFromHDF5::OutputImage OutputImage;

    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyFIFO;
    typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromHDF5> MyImageCacheWritePolicyWT;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(factImage, 2);
    MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);

    typedef TiledImage<Image, MyImageFactoryFromHDF5, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImage;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
    MyTiledImage tiledImage(factImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWT, 2);

    typedef MyTiledImage::OutputImage OutputImage;
    OutputImage::Value aValue;

    trace.info() << "Read value for Point 0,0,0: " << tiledImage(Z3i::Point(0,0,0)) << endl;
    nbok += (tiledImage(Z3i::Point(0,0,0)) == 1) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 3,1,0: " << tiledImage(Z3i::Point(3,1,0)) << endl;
    nbok += (tiledImage(Z3i::Point(3,1,0)) == 14) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 9,5,2: " << tiledImage(Z3i::Point(9,5,2)) << endl;
    nbok += (tiledImage(Z3i::Point(9,5,2)) == 220) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 1.1; tiledImage.setValue(Z3i::Point(3,6,5), aValue);
    trace.info() << "Write value for Point 3,6,5: " << aValue << endl;
    nbok += (tiledImage(Z3i::Point(3,6,5)) == 1.1) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 1,2,4: " << tiledImage(Z3i::Point(1,2,4)) << endl;
    nbok += (tiledImage(Z3i::Point(1,2,4)) == 342) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 8,6,3: " << tiledImage(Z3i::Point(8,6,3)) << endl;
    nbok += (tiledImage(Z3i::Point(8,6,3)) == 309) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 125.5; tiledImage.setValue(Z3i::Point(8,6,3), aValue);
    trace.info() << "Write value for Point 8,6,3: " << aValue << endl;
    nbok += (tiledImage(Z3i::Point(8,6,3)) == 125.5) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.endBlock();

    return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
    trace.beginBlock ( "Testing class ImageFactoryFromHDF5" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    bool res = true;
    res = res && writeHDF5_2D() && test2D_int32();

    res = res && writeHDF5_2D_TILED("testImageFactoryFromHDF5_TILED_2D.h5") && testTiledImage2D_int64();

    res = res && writeHDF5_3D_TILED_for_easy_reading();
    res = res && writeHDF5_3D_TILED();
    res = res && testTiledImage3D_double();

    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
