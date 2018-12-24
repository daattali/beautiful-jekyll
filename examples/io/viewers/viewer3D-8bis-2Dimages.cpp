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
 * @file io/viewers/viewer3D-8bis-2Dimages.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/11/18
 *
 * An example file named viewer3D-8bis-2Dimages.
 *
 * This file is part of the DGtal library.
 */

/**
 *  Example of 2D image display in 3D by 3D embedding.
 *
 * \image html viewer3D-8bis.png "Illustration of multiple 2D image extraction and visualisation  from 3D embedding"
 * \example io/viewers/viewer3D-8bis-2Dimages.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageHelper.h"
#include "ConfigExamples.h"
#include "DGtal/io/viewers/Viewer3D.h"
//! [ExampleViewer3D2DImagesExtractImagesNonSliceHeader]
#include "DGtal/kernel/BasicPointFunctors.h"
//! [ExampleViewer3D2DImagesExtractImagesNonSliceHeader]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{

  typedef DGtal::ImageContainerBySTLVector<DGtal::Z3i::Domain,  unsigned char > Image3D;
  //! [ExampleViewer3D2DImagesExtractImagesNonSliceType]
  typedef DGtal::ConstImageAdapter<Image3D, Z2i::Domain, DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain>,
                                   Image3D::Value,  DGtal::functors::Identity >  ImageAdapterExtractor;

  //! [ExampleViewer3D2DImagesExtractImagesNonSliceType]
  QApplication application(argc,argv);
  typedef Viewer3D<> MyViewer;
  MyViewer viewer;
  viewer.show();
  std::string inputFilename = examplesPath + "samples/lobster.vol";
  Image3D imageVol = VolReader<Image3D>::importVol(inputFilename);
  DGtal::functors::Identity idV;



  //! [ExampleViewer3D2DImagesExtractImagesNonSliceParam]
  DGtal::Z3i::Point ptCenter(50, 62, 28);
  const int IMAGE_PATCH_WIDTH = 20;
  // Setting the image domain of the resulting image to be displayed in 3D:
  DGtal::Z2i::Domain domainImage2D (DGtal::Z2i::Point(0,0),
                                    DGtal::Z2i::Point(IMAGE_PATCH_WIDTH, IMAGE_PATCH_WIDTH));
  //! [ExampleViewer3D2DImagesExtractImagesNonSliceParam]



  unsigned int pos=0;
  for (double alpha = 0; alpha< 1.54; alpha+= 0.01){
    //! [ExampleViewer3D2DImagesExtractImagesNonSliceExtract]
    // Extracting images from 3D embeder
    DGtal::functors::Point2DEmbedderIn3D<DGtal::Z3i::Domain >  embedder(imageVol.domain(),
                                                              ptCenter+DGtal::Z3i::RealPoint(200.0*cos(alpha),100.0*sin(alpha)),
                                                              DGtal::Z3i::RealPoint(cos(alpha),sin(alpha),cos(2.0*alpha)),
                                                              IMAGE_PATCH_WIDTH);
    ImageAdapterExtractor extractedImage(imageVol, domainImage2D, embedder, idV);
    //! [ExampleViewer3D2DImagesExtractImagesNonSliceExtract]

    //! [ExampleViewer3D2DImagesExtractImagesNonSliceDisplay]
    //Display image and update its position with embeder
    viewer << extractedImage;
    viewer << DGtal::UpdateImage3DEmbedding<Z3i::Space, Z3i::KSpace>(pos,
                                                                     embedder(Z2i::RealPoint(0,0)),
                                                                     embedder(Z2i::RealPoint(IMAGE_PATCH_WIDTH,0)),
                                                                     embedder(domainImage2D.upperBound()),
                                                                     embedder(Z2i::RealPoint(0, IMAGE_PATCH_WIDTH)));
    //! [ExampleViewer3D2DImagesExtractImagesNonSliceDisplay]
    pos++;
  }


  viewer << MyViewer::updateDisplay;


  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
