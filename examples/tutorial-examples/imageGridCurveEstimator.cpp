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
 * @file tutorial-examples/imageGridCurveEstimator.cpp
 * @ingroup tutorial-examples
 * @author Tristan Roussillon (tristan.roussillon@liris.cnrs.fr)
 *
 *
 * @date 2010/10/17
 * 
 * @brief An example of extracting a grid curve from an image iso-contour
 * and estimating its length. 
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <algorithm>
///////////////////////////////////////////////////////////////////////////////

//! [imageGridCurveEstimator-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
//! [imageGridCurveEstimator-basicIncludes]

//! [imageGridCurveEstimator-imageIncludes]
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
//! [imageGridCurveEstimator-imageIncludes]

//! [imageGridCurveEstimator-trackingIncludes]
#include "DGtal/topology/helpers/Surfaces.h"
//! [imageGridCurveEstimator-trackingIncludes]

//! [imageGridCurveEstimator-estimatorIncludes]
#include "DGtal/geometry/curves/estimation/DSSLengthEstimator.h"
//! [imageGridCurveEstimator-estimatorIncludes]

//display
#include "DGtal/io/boards/Board2D.h"

//segmentation
#include "DGtal/geometry/curves/GreedySegmentation.h"

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;
using namespace DGtal::functors;

int main()
{
  //image import
  typedef DGtal::ImageContainerBySTLVector< Z2i::Domain, int> Image;
  std::string filename =  examplesPath + "samples/contourS.pgm";
  Image image = DGtal::PGMReader<Image>::importPGM(filename); 

  //! [imageGridCurveEstimator-predicate] 
  //predicate from the image
  typedef DGtal::functors::IntervalThresholder<Image::Value> Binarizer;
  Binarizer b(1, 135); 
  PointFunctorPredicate<Image,Binarizer> predicate(image, b); 
  //! [imageGridCurveEstimator-predicate]

  //! [imageGridCurveEstimator-prepareTracking]
  Z2i::KSpace ks;                                            //Khalimsky space 
  ks.init( image.domain().lowerBound(), image.domain().upperBound(), true );
  SurfelAdjacency<2> sAdj( true );                           //adjacency
  //! [imageGridCurveEstimator-prepareTracking]

  //! [imageGridCurveEstimator-tracking]
  //extraction of all the contours
  std::vector< std::vector< Z2i::SCell > > contours;
  Surfaces<Z2i::KSpace>
    ::extractAll2DSCellContours( contours, ks, sAdj, predicate );
  //! [imageGridCurveEstimator-tracking]

  if (contours.size() > 0)
  {
    
    //! [imageGridCurveEstimator-instantiation]
    //init grid curve from the first retrieved contour
    Z2i::Curve c;
    c.initFromSCellsVector( contours.at(1) );  
    //! [imageGridCurveEstimator-instantiation]

    //! [imageGridCurveEstimator-getRange]
    //range of points
    typedef Z2i::Curve::PointsRange Range; 
    Range r = c.getPointsRange(); 
    //! [imageGridCurveEstimator-getRange]

    //! [imageGridCurveEstimator-lengthEstimation]
    //length estimation based on a DSS segmentation
    DSSLengthEstimator< Range::ConstCirculator > DSSlength;
    DSSlength.init(1, r.c(), r.c());
    trace.info() << "Length: " << DSSlength.eval() << std::endl; 
    //! [imageGridCurveEstimator-lengthEstimation]

    //DSS segmentation display
    typedef ArithmeticalDSSComputer<Range::ConstCirculator,int,4> SegmentComputer;
    typedef GreedySegmentation<SegmentComputer> Segmentation;

    Segmentation theSegmentation( r.c(), r.c(), SegmentComputer() );
    Segmentation::SegmentComputerIterator i = theSegmentation.begin();
    Segmentation::SegmentComputerIterator end = theSegmentation.end();
    
    DGtal::Board2D aBoard;
    aBoard << SetMode("PointVector", "Grid");
    for ( ; i != end; ++i) {
      SegmentComputer::Primitive dss = i->primitive(); 
      aBoard << SetMode(dss.className(), "Points") << dss; 
      aBoard << SetMode(dss.className(), "BoundingBox") << dss; 
    } 
    aBoard.saveEPS("DisplayDSSSegmentationTuto3.eps");
  
  } else trace.info() << "no contour" << std::endl; 
  
  return 0;

}

///////////////////////////////////////////////////////////////////////////////
