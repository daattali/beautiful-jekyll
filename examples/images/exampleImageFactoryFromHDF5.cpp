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
 * @file images/exampleImageFactoryFromHDF5.cpp
 * @ingroup Examples
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/06/25
 *
 * @brief An example file for ImageFactoryFromHDF5.
 *
 * This file is part of the DGtal library.
 */


/**
*  Example of HDF5 ImageFactory.
   @see @ref dgtalBigImagesAbstract   

   \image html TiledImageFromImage-11-write.png "Example of writing in cache. "
*  \example images/exampleImageFactoryFromHDF5.cpp
**/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageFactoryFromImage.h"
#include "DGtal/images/ImageFactoryFromHDF5.h"
#include "DGtal/images/ImageCache.h"
#include "DGtal/images/TiledImage.h"

#include "ConfigExamples.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

#define H5FILE_NAME_3D_TILED    "exampleImageFactoryFromHDF5_TILED_3D.h5"

#define DATASETNAME_3D          "UInt8Array3D"
#define NX_3D_TILED             300//1980       // dataset dimensions
#define NY_3D_TILED             300//1980
#define NZ_3D_TILED             300//400
#define CHUNK_X_3D_TILED        50              // chunk dimensions
#define CHUNK_Y_3D_TILED        50
#define CHUNK_Z_3D_TILED        50
#define RANK_3D_TILED           3

bool writeHDF5_3D_TILED()
{
  trace.beginBlock("Example : writeHDF5_3D (3D)");
  
  trace.info() << "begin" << endl;
  
  hid_t               file, dataset;                                  // file and dataset handles
  hid_t               datatype, dataspace;                            // handles
  hsize_t             dimsf[RANK_3D_TILED];                           // dataset dimensions
  herr_t              status;
  //DGtal::uint8_t      data[NZ_3D_TILED][NY_3D_TILED][NX_3D_TILED];    // data to write
  DGtal::uint8_t      *data;
  int                 i, j, k;
  
  // compressed dataset
  hid_t plist_id;
  hsize_t cdims[RANK_3D_TILED];
  // compressed dataset
  
  data = (DGtal::uint8_t*)malloc(NZ_3D_TILED*NY_3D_TILED*NX_3D_TILED * sizeof(DGtal::uint8_t));
  if (data == NULL)
  {
    trace.error() << " malloc error" << endl;
    return false;
  }
  
  // Data and output buffer initialization.
  for(k = 0; k < NZ_3D_TILED; k++)
    for(j = 0; j < NY_3D_TILED; j++)
      for(i = 0; i < NX_3D_TILED; i++)
        if (i>=15 && j>=15 && k>=15 && i<35 && j<35 && k<35)
          data[k*NY_3D_TILED*NX_3D_TILED + j*NX_3D_TILED + i] = 1;
        else
          data[k*NY_3D_TILED*NX_3D_TILED + j*NX_3D_TILED + i] = 0;
  
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
  
  // compressed dataset
  plist_id  = H5Pcreate (H5P_DATASET_CREATE);
  
  // Dataset must be chunked for compression.
  cdims[0] = CHUNK_Z_3D_TILED;
  cdims[1] = CHUNK_Y_3D_TILED;
  cdims[2] = CHUNK_X_3D_TILED;
  status = H5Pset_chunk (plist_id, RANK_3D_TILED, cdims);
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
  status = H5Pset_deflate (plist_id, 6);
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
    trace.error() << " H5Dsetorder error" << std::endl;
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
  status = H5Dwrite(dataset, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
  if (status)
  {
    trace.error() << " H5Dwrite error" << std::endl;
    free(data);
    return false;
  }
  
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

bool exampleImage3D()
{
  int i, j, k;
  
  trace.beginBlock("Example : ImageV (3D)");
  
  typedef ImageContainerBySTLVector<Z3i::Domain, DGtal::uint8_t> ImageV;
  typedef ImageV::Domain DomainV;
  typedef ImageV::Point PointV;
  DomainV domainV(PointV(0,0,0), PointV(NX_3D_TILED-1, NY_3D_TILED-1, NZ_3D_TILED-1));
  ImageV imageV(domainV);
  
  for(k = 0; k < NZ_3D_TILED; k++)
    for(j = 0; j < NY_3D_TILED; j++)
      for(i = 0; i < NX_3D_TILED; i++)
        if (i>=15 && j>=15 && k>=15 && i<35 && j<35 && k<35)
          imageV.setValue(PointV(i,j,k), 1);
        else
          imageV.setValue(PointV(i,j,k), 0);
  
  int cpt=0;
  trace.beginBlock("Counting ones in the original image (domain)");
  for(ImageV::Domain::ConstIterator it = imageV.domain().begin(), itend = imageV.domain().end();
      it != itend; ++it)
    if (imageV( *it ) == 1)
      cpt++;
  trace.info() << "imageV cpt: " << cpt << endl;
  trace.endBlock();
  
  cpt=0;
  trace.beginBlock("Counting ones in the original image (range)");
  for(ImageV::Range::ConstIterator it = imageV.range().begin(), itend = imageV.range().end();
      it != itend; ++it)
    if (( *it ) == 1)
      cpt++;
  trace.info() << "imageV cpt: " << cpt << endl;
  trace.endBlock();
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}

bool exampleTiledImageFromImage_1block3D()
{
  int i, j, k;
  
  trace.beginBlock("Example : TiledImage with ImageFactoryFromImage - 1 block (3D)");
  
  typedef ImageContainerBySTLVector<Z3i::Domain, DGtal::uint8_t> ImageV;
  typedef ImageV::Domain DomainV;
  typedef ImageV::Point PointV;
  DomainV domainV(PointV(0,0,0), PointV(NX_3D_TILED-1, NY_3D_TILED-1, NZ_3D_TILED-1));
  ImageV imageV(domainV);
  
  for(k = 0; k < NZ_3D_TILED; k++)
    for(j = 0; j < NY_3D_TILED; j++)
      for(i = 0; i < NX_3D_TILED; i++)
        if (i>=15 && j>=15 && k>=15 && i<35 && j<35 && k<35)
          imageV.setValue(PointV(i,j,k), 1);
        else
          imageV.setValue(PointV(i,j,k), 0);
  
  typedef ImageFactoryFromImage<ImageV> MyImageFactoryFromImage;
  MyImageFactoryFromImage factImage(imageV);
  
  typedef MyImageFactoryFromImage::OutputImage OutputImage;
  
  //typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
  typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyLAST;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
  //MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(factImage, 3);
  MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);
  
  typedef TiledImage<ImageV, MyImageFactoryFromImage, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyTiledImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
  MyTiledImage tiledImage1block(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT, 1);
  
  typedef MyTiledImage::OutputImage OutputImage;
  //OutputImage::Value aValue;
  
  trace.info() << tiledImage1block << std::endl;
  
  int cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 1x1x1 blocks - LAST/WT - TiledIterator");
  for(MyTiledImage::TiledIterator it = tiledImage1block.begin(), itend = tiledImage1block.end();
      it != itend; ++it)
    if ((*it) == 1)
      cpt++;
  trace.info() << "Cpt: " << cpt << " - cacheMissRead:" << tiledImage1block.getCacheMissRead() << " - cacheMissWrite:" << tiledImage1block.getCacheMissWrite() << endl;
  trace.endBlock();
  
  cpt=0; tiledImage1block.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 1x1x1 blocks - LAST/WT");
  for(ImageV::Domain::ConstIterator it = tiledImage1block.domain().begin(), itend = tiledImage1block.domain().end();
      it != itend; ++it)
    if (tiledImage1block(*it) == 1)
      cpt++;
  trace.info() << "Cpt: " << cpt << " - cacheMissRead:" << tiledImage1block.getCacheMissRead() << " - cacheMissWrite:" << tiledImage1block.getCacheMissWrite() << endl;
  trace.endBlock();
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}

bool exampleTiledImageFromHDF5_1block3D()
{
  trace.beginBlock("Example : TiledImage with ImageFactoryFromHDF5 - 1 block (3D)");
  
  typedef ImageSelector<Z3i::Domain, DGtal::uint8_t>::Type Image;
  
  typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
  MyImageFactoryFromHDF5 factImage(H5FILE_NAME_3D_TILED, DATASETNAME_3D);
  
  typedef MyImageFactoryFromHDF5::OutputImage OutputImage;
  
  //typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyFIFO;
  typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyLAST;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromHDF5> MyImageCacheWritePolicyWT;
  //MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(factImage, 3);
  MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);
  
  typedef TiledImage<Image, MyImageFactoryFromHDF5, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyTiledImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
  MyTiledImage tiledImage1block(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT, 1);
  
  typedef MyTiledImage::OutputImage OutputImage;
  //OutputImage::Value aValue;
  
  trace.info() << tiledImage1block << std::endl;
  
  int cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 1x1x1 blocks - LAST/WT - TiledIterator");
  for(MyTiledImage::TiledIterator it = tiledImage1block.begin(), itend = tiledImage1block.end();
      it != itend; ++it)
    if ((*it) == 1)
      cpt++;
  trace.info() << "Cpt: " << cpt << " - cacheMissRead:" << tiledImage1block.getCacheMissRead() << " - cacheMissWrite:" << tiledImage1block.getCacheMissWrite() << endl;
  trace.endBlock();
  
  cpt=0; tiledImage1block.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 1x1x1 blocks - LAST/WT");
  for(Image::Domain::ConstIterator it = tiledImage1block.domain().begin(), itend = tiledImage1block.domain().end();
      it != itend; ++it)
    if (tiledImage1block(*it) == 1)
      cpt++;
  trace.info() << "Cpt: " << cpt << " - cacheMissRead:" << tiledImage1block.getCacheMissRead() << " - cacheMissWrite:" << tiledImage1block.getCacheMissWrite() << endl;
  trace.endBlock();
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}

bool exampleTiledImageFromImage_10blocks3D()
{
  int i, j, k;
  
  trace.beginBlock("Example : TiledImage with ImageFactoryFromImage - 10 blocks (3D)");
  
  typedef ImageContainerBySTLVector<Z3i::Domain, DGtal::uint8_t> ImageV;
  typedef ImageV::Domain DomainV;
  typedef ImageV::Point PointV;
  DomainV domainV(PointV(0,0,0), PointV(NX_3D_TILED-1, NY_3D_TILED-1, NZ_3D_TILED-1));
  ImageV imageV(domainV);
  
  for(k = 0; k < NZ_3D_TILED; k++)
    for(j = 0; j < NY_3D_TILED; j++)
      for(i = 0; i < NX_3D_TILED; i++)
        if (i>=15 && j>=15 && k>=15 && i<35 && j<35 && k<35)
          imageV.setValue(PointV(i,j,k), 1);
        else
          imageV.setValue(PointV(i,j,k), 0);
  
  typedef ImageFactoryFromImage<ImageV> MyImageFactoryFromImage;
  MyImageFactoryFromImage factImage(imageV);
  
  typedef MyImageFactoryFromImage::OutputImage OutputImage;
  
  typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
  typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyLAST;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
  MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO_A(factImage, 10);
  MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO_B(factImage, 5);
  MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);
  
  typedef TiledImage<ImageV, MyImageFactoryFromImage, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyTiledImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
  MyTiledImage tiledImage(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT, 10);
  
  typedef TiledImage<ImageV, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImageFIFO;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImageFIFO > ));
  MyTiledImageFIFO tiledImageFIFO_A(factImage, imageCacheReadPolicyFIFO_A, imageCacheWritePolicyWT, 10);
  MyTiledImageFIFO tiledImageFIFO_B(factImage, imageCacheReadPolicyFIFO_B, imageCacheWritePolicyWT, 10);
  
  typedef MyTiledImage::OutputImage OutputImage;
  //OutputImage::Value aValue;
  
  int cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(10)/WT - TiledIterator");
  for(MyTiledImageFIFO::TiledIterator it = tiledImageFIFO_A.begin(), itend = tiledImageFIFO_A.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImageFIFO_A.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(10)/WT");
  for(ImageV::Domain::ConstIterator it = tiledImageFIFO_A.domain().begin(), itend = tiledImageFIFO_A.domain().end();
      it != itend; ++it)
  {
    if (tiledImageFIFO_A(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  // ---
  
  cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(5)/WT - TiledIterator");
  for(MyTiledImageFIFO::TiledIterator it = tiledImageFIFO_B.begin(), itend = tiledImageFIFO_B.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImageFIFO_B.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(5)/WT");
  for(ImageV::Domain::ConstIterator it = tiledImageFIFO_B.domain().begin(), itend = tiledImageFIFO_B.domain().end();
      it != itend; ++it)
  {
    if (tiledImageFIFO_B(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  // ---
  
  cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - LAST/WT - TiledIterator");
  for(MyTiledImage::TiledIterator it = tiledImage.begin(), itend = tiledImage.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImage.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - LAST/WT");
  for(ImageV::Domain::ConstIterator it = tiledImage.domain().begin(), itend = tiledImage.domain().end();
      it != itend; ++it)
  {
    if (tiledImage(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}

bool exampleTiledImageFromHDF5_10blocks3D()
{
  trace.beginBlock("Example : TiledImage with ImageFactoryFromHDF5 - 10 blocks (3D)");
  
  typedef ImageSelector<Z3i::Domain, DGtal::uint8_t>::Type Image;
  
  typedef ImageFactoryFromHDF5<Image> MyImageFactoryFromHDF5;
  MyImageFactoryFromHDF5 factImage(H5FILE_NAME_3D_TILED, DATASETNAME_3D);
  
  typedef MyImageFactoryFromHDF5::OutputImage OutputImage;
  
  typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyFIFO;
  typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromHDF5> MyImageCacheReadPolicyLAST;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromHDF5> MyImageCacheWritePolicyWT;
  MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO_A(factImage, 10);
  MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO_B(factImage, 5);
  MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);
  
  typedef TiledImage<Image, MyImageFactoryFromHDF5, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyTiledImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
  MyTiledImage tiledImage(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT, 10);
  
  typedef TiledImage<Image, MyImageFactoryFromHDF5, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImageFIFO;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImageFIFO > ));
  MyTiledImageFIFO tiledImageFIFO_A(factImage, imageCacheReadPolicyFIFO_A, imageCacheWritePolicyWT, 10);
  MyTiledImageFIFO tiledImageFIFO_B(factImage, imageCacheReadPolicyFIFO_B, imageCacheWritePolicyWT, 10);
  
  typedef MyTiledImage::OutputImage OutputImage;
  //OutputImage::Value aValue;
  
  int cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(10)/WT - TiledIterator");
  for(MyTiledImageFIFO::TiledIterator it = tiledImageFIFO_A.begin(), itend = tiledImageFIFO_A.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImageFIFO_A.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(10)/WT");
  for(Image::Domain::ConstIterator it = tiledImageFIFO_A.domain().begin(), itend = tiledImageFIFO_A.domain().end();
      it != itend; ++it)
  {
    if (tiledImageFIFO_A(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  // ---
  
  cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(5)/WT - TiledIterator");
  for(MyTiledImageFIFO::TiledIterator it = tiledImageFIFO_B.begin(), itend = tiledImageFIFO_B.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImageFIFO_B.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - FIFO(5)/WT");
  for(Image::Domain::ConstIterator it = tiledImageFIFO_B.domain().begin(), itend = tiledImageFIFO_B.domain().end();
      it != itend; ++it)
  {
    if (tiledImageFIFO_B(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  // ---
  
  cpt=0;
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - LAST/WT - TiledIterator");
  for(MyTiledImage::TiledIterator it = tiledImage.begin(), itend = tiledImage.end();
      it != itend; ++it)
  {
    if ((*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  cpt=0; tiledImage.clearCacheAndResetCacheMisses();
  trace.beginBlock("Counting ones in the tiled image - 10x10x10 blocks - LAST/WT");
  for(Image::Domain::ConstIterator it = tiledImage.domain().begin(), itend = tiledImage.domain().end();
      it != itend; ++it)
  {
    if (tiledImage(*it) == 1)
      cpt++;
  }
  trace.endBlock();
  
  trace.endBlock();
  trace.info() << endl;
  
  return true;
}
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( /*int argc, char** argv*/ )
{
  //if (argc==1)
  writeHDF5_3D_TILED();
  
  exampleImage3D();
  
  exampleTiledImageFromImage_1block3D();
  exampleTiledImageFromHDF5_1block3D();
  
  exampleTiledImageFromImage_10blocks3D();
  exampleTiledImageFromHDF5_10blocks3D();
  
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
