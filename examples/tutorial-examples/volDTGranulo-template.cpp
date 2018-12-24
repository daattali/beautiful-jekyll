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
 * @file tutorial-examples/volDTGranulo-template.cpp
 * @ingroup tutorial-examples
 * @author Tristan Roussillon (tristan.roussillon@liris.cnrs.fr)
 *
 *
 * @date 2010/10/17
 * 
 * @brief An example of generating a grid curve from a parametric shape
 * and estimating its length. 
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <algorithm>
///////////////////////////////////////////////////////////////////////////////

//! [volGranulo-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/images/ImageContainerBySTLVector.h"

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/VolWriter.h"

#include "DGtal/images/imagesSetsUtils/SimpleThresholdForegroundPredicate.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/base/BasicFunctors.h"
//! [volGranulo-basicIncludes]

//! [volGranulo-viewerIncludes]
#include <QtGui/qapplication.h>
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
//! [volGranulo-viewerIncludes]

using namespace DGtal;

int main(int argc, char ** argv)
{

  ////////////////
  //Load a vol image and store it into a ImageContainerBySTLVector
  //
  // ...
  //  


  ////////////////
  //Visualization 2
  //

  //! [volGranulo-viewer]
  //Create a new viewer instance
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  //! [volGranulo-viewer]

  // - iterate over the loaded image domain and send strictly positive
  //values to the viewer
  //
  // Do not forget a  viewer2 << DGtal::Viewer3D<>::updateDisplay;
  // when you're done.


  ////////////////
  //Distance transformation
  
  //Create a Point Predicate from the input image and a thresholder
  // (see SimpleThresholdForegroundPredicate)

  // ...


  // Compute the distance map for the L2 metric

  // ...

  ///////////////


  ////////////////
  //Visualization 2
  //

  // Create a new instance of Viewer3D

  //! [volGranulo-cmap]
  //Create the colormap from the maximal distance value
  //and a GradientColorMap
  DT::Value maxDT = (*std::max_element(distancemap.constRange().begin(), 
                                       distancemap.constRange().end()));
  GradientColorMap<DT::Value> gradient( 0, maxDT);
  gradient.addColor(DGtal::Color::Blue);
  gradient.addColor(DGtal::Color::Green);
  gradient.addColor(DGtal::Color::Yellow);
  gradient.addColor(DGtal::Color::Red);
  //! [volGranulo-cmap]

  
 
  //////////////////
  //Granulometry


  //Create an empty image with the same size as the input one
  
  //...


  //Compute the granulometry function
  
  //...

  
  //Export the granulometry map to a vol
  //! [volGranulo-export]
  VolWriter<Image, CastFunctor<unsigned char> >::exportVol("granulo.vol", imageGranulo);     
  //! [volGranulo-export]
  


  ////////////////
  //Visualization 3
  //
  //  Create a visualization of the granulometry function
  
  return 0;
}
