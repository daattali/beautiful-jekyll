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
 * @file tutorial-examples/shapeGridCurveEstimator.cpp
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

//! [shapeGridCurveEstimator-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
//! [shapeGridCurveEstimator-basicIncludes]

//! [shapeGridCurveEstimator-shapeIncludes]
//shape and digitizer
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"
//! [shapeGridCurveEstimator-shapeIncludes]

//! [shapeGridCurveEstimator-trackingIncludes]
//tracking grid curve
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/geometry/curves/GridCurve.h"
//! [shapeGridCurveEstimator-trackingIncludes]

//! [shapeGridCurveEstimator-estimationIncludes]
//length estimation knowing the shape
#include "DGtal/geometry/curves/estimation/TrueGlobalEstimatorOnPoints.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeArcLengthFunctor.h"
//length estimation based on a DSS segmentation
#include "DGtal/geometry/curves/estimation/DSSLengthEstimator.h"
//! [shapeGridCurveEstimator-estimationIncludes]

#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

int main()
{
  //shape
  //! [shapeGridCurveEstimator-dig]
  //implicit digitization of a shape of type Flower 
  //into a digital space of type Space
  typedef Flower2D<Z2i::Space> Flower; 
  Flower2D<Z2i::Space> flower(Z2i::Point(0,0), 20, 5, 5, 0);
  
  double h = 1; 
  GaussDigitizer<Z2i::Space,Flower> dig;  
  dig.attach( flower );
  dig.init( flower.getLowerBound()+Z2i::Vector(-1,-1),
            flower.getUpperBound()+Z2i::Vector(1,1), h ); 
  //! [shapeGridCurveEstimator-dig]
  
  //! [shapeGridCurveEstimator-prepareTracking]
  //Khalimsky space
  Z2i::KSpace ks;
  ks.init( dig.getLowerBound(), dig.getUpperBound(), true );
  //adjacency (4-connectivity)
  SurfelAdjacency<2> sAdj( true );
  //! [shapeGridCurveEstimator-prepareTracking]

  //! [shapeGridCurveEstimator-tracking]
  //searching for one boundary element
  Z2i::SCell bel = Surfaces<Z2i::KSpace>::findABel( ks, dig, 1000 );
  //tracking
  std::vector<Z2i::Point> boundaryPoints;
  Surfaces<Z2i::KSpace>
    ::track2DBoundaryPoints( boundaryPoints, ks, sAdj, dig, bel );
  //! [shapeGridCurveEstimator-tracking]

  //! [shapeGridCurveEstimator-instantiation]
  Z2i::Curve c;
  c.initFromVector( boundaryPoints );  
  //! [shapeGridCurveEstimator-instantiation]
  
  DGtal::Board2D aBoard;
  aBoard << c; 
  aBoard.saveEPS("DisplayGridCurve1.eps");  
  
  //! [shapeGridCurveEstimator-getRange]
  //range of points
  typedef Z2i::Curve::PointsRange Range; 
  Range r = c.getPointsRange(); 
  //! [shapeGridCurveEstimator-getRange]
  
  //! [shapeGridCurveEstimator-lengthEstimation]
  //length estimation
  DSSLengthEstimator< Range::ConstCirculator > DSSlength;
  DSSlength.init( h, r.c(), r.c() );
  double length1 = DSSlength.eval();
  trace.info() << "Length (h=" << h << "): " << length1 << std::endl; 
  //! [shapeGridCurveEstimator-lengthEstimation]

//@TODO correct init method of trueLengthEstimator (remove &flower)
  //! [shapeGridCurveEstimator-trueLengthEstimation]
  typedef ParametricShapeArcLengthFunctor< Flower > Length;
  TrueGlobalEstimatorOnPoints< 
    Range::ConstIterator, 
    Flower, 
    Length  >  trueLengthEstimator;
  trueLengthEstimator.init( h, r.begin(), r.end(), &flower, c.isClosed());
  double trueLength = trueLengthEstimator.eval(); 
  trace.info() << "ground truth: " << trueLength << std::endl; 
  //! [shapeGridCurveEstimator-trueLengthEstimation]

  //! [shapeGridCurveEstimator-higher]
  //implicit digitization at higher resolution
  h = 0.1; 
  dig.init( flower.getLowerBound()+Z2i::Vector(-1,-1),
            flower.getUpperBound()+Z2i::Vector(1,1), h ); 
  //a greater domain is needed in the Khalimsky space
  ks.init( dig.getLowerBound(), dig.getUpperBound(), true );
  //searching for one boundary element
  bel = Surfaces<Z2i::KSpace>::findABel( ks, dig, 10000 );
  //tracking
  Surfaces<Z2i::KSpace>
    ::track2DBoundaryPoints( boundaryPoints, ks, sAdj, dig, bel );
  //reset grid curve and its points range
  c.initFromVector( boundaryPoints );
  Range r2 = c.getPointsRange(); 
  //estimate length
  DSSlength.init( h, r2.c(), r2.c() );
  double length2 = DSSlength.eval();
  trace.info() << "Length (h=" << h << "): " << length2 << std::endl;  
  //! [shapeGridCurveEstimator-higher]
  
  aBoard.clear(); 
  aBoard << c; 
  aBoard.saveEPS("DisplayGridCurve01.eps");  
  
  return 0;

}

///////////////////////////////////////////////////////////////////////////////
