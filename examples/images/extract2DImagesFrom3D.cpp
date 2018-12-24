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
 * @file images/extract2DImagesFrom3D.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/10/15
 *
 * An example file named extract2DImagesFrom3D.
 *
 * This file is part of the DGtal library.
 */


/**
 *  Example of 2D images extraction from 3D images.
 *
 * \image html lobster2DExtract.png "Example of one of the resulting
 * 2D images of the sample/lobster.vol file (with increased size)."
 *
 * \example images/extract2DImagesFrom3D.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/PGMWriter.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "ConfigExamples.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

const int IMAGE_PATCH_WIDTH = 70;

int main( int /*argc*/, char** /*argv*/ )
{
  //! [extract2DImagesFrom3DType]
   typedef ImageSelector < Z3i::Domain, unsigned char>::Type Image3D;
   typedef DGtal::ConstImageAdapter<Image3D, Z2i::Domain, DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain>,
                                    Image3D::Value,  DGtal::functors::Identity >  ImageAdapterExtractor;
   //! [extract2DImagesFrom3DType]

   //! [extract2DImagesFrom3DOrigin3D]
   DGtal::Z3i::Point origin(150, 150, 10);
   DGtal::Z3i::Point ptUpper1(220, 220, 10);
   DGtal::Z3i::Point ptUpper2(150, 150, 50);
   DGtal::Z2i::Domain domainImage2D (DGtal::Z2i::Point(0,0),
				     DGtal::Z2i::Point(static_cast<int>((ptUpper1-origin).norm()),
						       static_cast<int>((ptUpper2-origin).norm())));
   //! [extract2DImagesFrom3DOrigin3D]
   DGtal::Z3i::Point ptCenter(175, 175, 20);
   DGtal::Z2i::Domain domainImage2D2 (DGtal::Z2i::Point(0,0),
                                      DGtal::Z2i::Point(IMAGE_PATCH_WIDTH, IMAGE_PATCH_WIDTH));


   // Importing a 3D image
   std::string filename = examplesPath + "samples/lobster.vol";
   Image3D image = VolReader<Image3D>::importVol( filename );
   DGtal::Z3i::Domain domainImage3D = image.domain();
   DGtal::functors::Identity idV;

   trace.beginBlock ( "Example extract2DImagesFrom3D" );

   // Extracting 2D images ... and export them in the pgm format.
   for (unsigned int i=0; i<30; i+=10){
     std::stringstream name;
     name << "lobsterExtracted_"  << i << ".pgm";
     std::stringstream name2;
     name2 << "lobsterExtracted_"  << i << "V2.pgm";

     //! [extract2DImagesFrom3DOExtract]
     DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder(domainImage3D, origin+DGtal::Z3i::Point(i,i,0),
							       ptUpper1+DGtal::Z3i::Point(i,i,0),
							       ptUpper2+DGtal::Z3i::Point(i,i,0));

     ImageAdapterExtractor extractedImage(image, domainImage2D, embedder, idV);
     //! [extract2DImagesFrom3DOExtract]

     //! [extract2DImagesFrom3DOExtract2]
     DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder2(domainImage3D, ptCenter+DGtal::Z3i::Point(i,i,0),
								DGtal::Z3i::RealPoint(1,-1,0),
								IMAGE_PATCH_WIDTH);
     ImageAdapterExtractor extractedImage2(image, domainImage2D2, embedder2, idV);
     //! [extract2DImagesFrom3DOExtract2]

     PGMWriter< ImageAdapterExtractor>::exportPGM(name.str(), extractedImage);
     PGMWriter< ImageAdapterExtractor>::exportPGM(name2.str(), extractedImage2);
   }

   // trace.endBlock();
   return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
