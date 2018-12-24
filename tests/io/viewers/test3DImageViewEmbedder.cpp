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
 * @file test3DImageViewEmbedder.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/11/25
 *
 * Functions for testing class Viewer3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/io/viewers/DrawWithViewer3DModifier.h"
#include "ConfigTest.h"

#include <limits>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;




///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Viewer3D.
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{

  typedef DGtal::ImageContainerBySTLVector< DGtal::Z3i::Domain, unsigned char>  Image3D;
  typedef DGtal::ConstImageAdapter<Image3D, Z2i::Domain, DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain>,
                                   Image3D::Value,  DGtal::functors::Identity >  ImageAdapterExtractor;

 QApplication application(argc,argv);
 Viewer3D<> viewer;
 viewer.setWindowTitle("simpleViewer");
 viewer.show();

 trace.beginBlock("Testing Viewer with Image Embedder ");
 Point pcenter( 10, 20, 20 );
 Point pcenterImg( 10, 20, 20 );

 std::string filename =  testPath + "samples/cat10.pgm3d";
 Image3D image = DGtal::GenericReader<Image3D>::import(filename);

 const int IMAGE_PATCH_WIDTH = 80;
 // Setting the image domain of the resulting image to be displayed in 3D:
 DGtal::Z2i::Domain domainImage2D (DGtal::Z2i::Point(0,0),
                                   DGtal::Z2i::Point(IMAGE_PATCH_WIDTH, IMAGE_PATCH_WIDTH));

 DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder(image.domain(),
                                                           pcenterImg, Z3i::RealPoint(1, 1, 1),
                                                           IMAGE_PATCH_WIDTH);
 DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder2(image.domain(),
                                                           pcenterImg, Z3i::RealPoint(1, 0, 0),
                                                           IMAGE_PATCH_WIDTH);
  DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder3(image.domain(),
                                                           pcenterImg, Z3i::RealPoint(0, 1, 0 ),
                                                           IMAGE_PATCH_WIDTH);
  DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder4(image.domain(),
                                                           pcenterImg, Z3i::RealPoint(0, 0, 1 ),
                                                           IMAGE_PATCH_WIDTH);

 functors::Identity idV;
 ImageAdapterExtractor extractedImage(image, domainImage2D, embedder, idV);
 ImageAdapterExtractor extractedImage2(image, domainImage2D, embedder2, idV);
 ImageAdapterExtractor extractedImage3(image, domainImage2D, embedder3, idV);
 ImageAdapterExtractor extractedImage4(image, domainImage2D, embedder4, idV);

 viewer << extractedImage;
 viewer << extractedImage2;
 viewer << extractedImage3;
 viewer << extractedImage4;
 viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(0,
                                                                  embedder(Z2i::RealPoint(0,0),false),
                                                                  embedder(Z2i::RealPoint(IMAGE_PATCH_WIDTH,0),false),
                                                                  embedder(domainImage2D.upperBound(), false),
                                                                  embedder(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH), false));
 viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(1,
                                                                  embedder2(Z2i::RealPoint(0,0),false),
                                                                  embedder2(Z2i::RealPoint(IMAGE_PATCH_WIDTH,0),false),
                                                                  embedder2(domainImage2D.upperBound(), false),
                                                                  embedder2(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH), false));
 viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(2,
                                                                  embedder3(Z2i::RealPoint(0,0),false),
                                                                  embedder3(Z2i::RealPoint(IMAGE_PATCH_WIDTH,0),false),
                                                                  embedder3(domainImage2D.upperBound(), false),
                                                                  embedder3(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH), false));
 viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(3,
                                                                  embedder4(Z2i::RealPoint(0,0),false),
                                                                  embedder4(Z2i::RealPoint(IMAGE_PATCH_WIDTH,0),false),
                                                                  embedder4(domainImage2D.upperBound(), false),
                                                                  embedder4(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH), false));
 viewer.setFillColor(DGtal::Color(250,20,20,255));
 viewer << pcenter;



 viewer << Viewer3D<>::updateDisplay;


 bool res = application.exec();
 trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
 trace.endBlock();
 return res ? 0 : 1;

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

