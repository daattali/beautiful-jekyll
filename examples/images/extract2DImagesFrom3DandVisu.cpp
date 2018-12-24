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
 * @file images/extract2DImagesFrom3DandVisu.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/04/24
 *
 * An example file named extract2DImagesFrom3D.
 *
 * This file is part of the DGtal library.
 */



/**
 *  Example of 2D images extraction from 3D images and 3D visualisation.
 *
 *  \image html lobsterVisu3DSlicesZ.png   "Example of 3D visualisation of 2D slices images of the sample/lobster.vol file."
 *
 * \example images/extract2DImagesFrom3DandVisu.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "ConfigExamples.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/kernel/BasicPointFunctors.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{


  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.setWindowTitle("simpleViewer");
  viewer.show();


  typedef ImageSelector < Z3i::Domain, unsigned char>::Type Image3D;
  typedef ImageSelector < Z2i::Domain, unsigned char>::Type Image2D;
  typedef DGtal::ConstImageAdapter<Image3D, Image2D::Domain, DGtal::functors::Projector< Z3i::Space>,
             Image3D::Value,  DGtal::functors::Identity >  SliceImageAdapter;

  typedef DGtal::ConstImageAdapter<Image3D, Z2i::Domain, DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain>,
             Image3D::Value,  DGtal::functors::Identity >  ImageAdapterExtractor;

  DGtal::functors::Projector<DGtal::Z2i::Space>  invFunctor(2);
  // Importing a 3D image
  std::string filename = examplesPath + "samples/lobster.vol";
  Image3D image = VolReader<Image3D>::importVol( filename );

  DGtal::Z2i::Domain domain(invFunctor(image.domain().lowerBound()),
          invFunctor(image.domain().upperBound()));
  DGtal::functors::Identity idV;

  trace.beginBlock ( "Example extract2DImagesFrom3D" );

  // Extracting 2D slices ... and visualisation on 3DViewer
  unsigned int pos=0;
  for (unsigned int i=0; i<30; i+=5){
    DGtal::functors::Projector<DGtal::Z3i::Space> aSliceFunctor(i); aSliceFunctor.initAddOneDim(2);
    SliceImageAdapter sliceImageZ(image, domain, aSliceFunctor, idV);
    viewer << sliceImageZ;
    viewer << DGtal::UpdateImagePosition<Z3i::Space, Z3i::KSpace>(pos, Viewer3D<>::zDirection,  i*20, i*20, i*20 );
    pos++;
  }

  // Visu extraction from points
  const int IMAGE_PATCH_WIDTH = 40;


  DGtal::Z3i::Point ptCenter(155, 155, 20);
  DGtal::Z2i::Domain domainImage2D (DGtal::Z2i::Point(0,0),
                                    DGtal::Z2i::Point(IMAGE_PATCH_WIDTH, IMAGE_PATCH_WIDTH));


  DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder(image.domain(), ptCenter,
                                                            DGtal::Z3i::RealPoint(1,-1,1),
                                                            IMAGE_PATCH_WIDTH);

  ImageAdapterExtractor extractedImage(image, domainImage2D, embedder, idV);
  viewer << extractedImage;
  viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(pos,
                                                                   embedder(Z2i::Point(0,0)),
                                                                   embedder(Z2i::Point(IMAGE_PATCH_WIDTH,0)),
                                                                   embedder(domainImage2D.upperBound()),
                                                                   embedder(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH)));



  viewer << DGtal::Viewer3D<>::updateDisplay;


  application.exec();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
