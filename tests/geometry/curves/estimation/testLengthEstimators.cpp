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
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr ) 
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/07/07
 *
 * Functions for testing classes of length estimators.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include "DGtal/base/Common.h"

//space / domain
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"

//shape and digitizer
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"

#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/geometry/curves/GridCurve.h"

//estimators
#include "DGtal/geometry/curves/estimation/TrueLocalEstimatorOnPoints.h"
#include "DGtal/geometry/curves/estimation/TrueGlobalEstimatorOnPoints.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeCurvatureFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeTangentFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeArcLengthFunctor.h"

#include "DGtal/geometry/curves/estimation/L1LengthEstimator.h"
#include "DGtal/geometry/curves/estimation/TwoStepLocalLengthEstimator.h"
#include "DGtal/geometry/curves/estimation/BLUELocalLengthEstimator.h"
#include "DGtal/geometry/curves/estimation/RosenProffittLocalLengthEstimator.h"

#include "DGtal/geometry/curves/estimation/MLPLengthEstimator.h"
#include "DGtal/geometry/curves/estimation/FPLengthEstimator.h"
#include "DGtal/geometry/curves/estimation/DSSLengthEstimator.h"

#include "ConfigTest.h"

#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////
// Functions for testing Length Estimator classes.
///////////////////////////////////////////////////////////////////////////////

bool testLengthEstimatorsOnBall(double radius, double h)
{

  // Types
  typedef SpaceND<2,int> Space;  
  typedef Ball2D<Space> Shape;
  typedef Space::Point Point;
  typedef Space::RealPoint RealPoint;
  typedef Space::Integer Integer;
  typedef HyperRectDomain<Space> Domain;
  typedef KhalimskySpaceND<Space::dimension,Integer> KSpace;
  typedef KSpace::SCell SCell;
  typedef GridCurve<KSpace>::PointsRange PointsRange;
  typedef GridCurve<KSpace>::ArrowsRange ArrowsRange;


  //Forme
  Shape aShape(Point(0,0), radius);

  trace.info() << "#ball created, r=" << radius << endl;

  // Window for the estimation
  RealPoint xLow ( -radius-1, -radius-1 );
  RealPoint xUp( radius+1, radius+1 );
  GaussDigitizer<Space,Shape> dig;  
  dig.attach( aShape ); // attaches the shape.
  dig.init( xLow, xUp, h ); 
  // The domain size is given by the digitizer according to the window
  // and the step.
  Domain domain = dig.getDomain();
  // Create cellular space
  KSpace K;
  bool ok = K.init( dig.getLowerBound(), dig.getUpperBound(), true );
  if ( ! ok )
    {
      std::cerr << " "
                << " error in creating KSpace." << std::endl;
      return false;
    }

  SurfelAdjacency<KSpace::dimension> SAdj( true );
  SCell bel; 
  try 
    {
      bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
    }    
  catch ( InputException e )
    {
      std::cerr << " "
                << " error in finding a bel." << std::endl;
      return false;
    }

    // Getting the consecutive surfels of the 2D boundary
    std::vector<Point> points;
    Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
    trace.info() << "#tracking..." << endl;
    // Create GridCurve
    GridCurve<KSpace> gridcurve;
    gridcurve.initFromVector( points );
    trace.info() << "#grid curve created, h=" << h << endl;

    //ranges
    ArrowsRange ra = gridcurve.getArrowsRange(); 
    PointsRange rp = gridcurve.getPointsRange(); 

    ////////////////////////////////////////estimations
    double trueValue = M_PI*2*radius;
    L1LengthEstimator< GridCurve<KSpace>::ArrowsRange::ConstCirculator > l1length;
    l1length.init(h, ra.c(), ra.c());
    TwoStepLocalLengthEstimator< GridCurve<KSpace>::ArrowsRange::ConstIterator > locallength(1.0,sqrt(2.0));
    locallength.init(h, ra.begin(), ra.end(), gridcurve.isClosed());
    BLUELocalLengthEstimator< GridCurve<KSpace>::ArrowsRange::ConstIterator > BLUElength;
    BLUElength.init(h, ra.begin(), ra.end(), gridcurve.isClosed());
    RosenProffittLocalLengthEstimator< GridCurve<KSpace>::ArrowsRange::ConstIterator > RosenProffittlength;
    RosenProffittlength.init(h, ra.begin(), ra.end(), gridcurve.isClosed());
    DSSLengthEstimator< GridCurve<KSpace>::PointsRange::ConstCirculator > DSSlength;
    DSSlength.init(h, rp.c(), rp.c());
    // MLPLengthEstimator< GridCurve<KSpace>::PointsRange::ConstIterator > MLPlength;
    // MLPlength.init(h, rp.begin(), rp.end(), gridcurve.isClosed());
    // FPLengthEstimator< GridCurve<KSpace>::PointsRange::ConstIterator > FPlength;
    // FPlength.init(h, rp.begin(), rp.end(), gridcurve.isClosed());

    trace.info() << "#Estimations" <<std::endl;
    trace.info() << "#h true naive 1-sqrt(2) BLUE RosenProffitt DSS MLP FP " <<std::endl;
    trace.info() << h << " " << trueValue  
                 << " " << l1length.eval() 
                 << " " << locallength.eval() 
                 << " " << BLUElength.eval() 
                 << " " << RosenProffittlength.eval() 
		 <<  " " << DSSlength.eval() 
                 // << " " << MLPlength.eval() 
                 // <<  " " << FPlength.eval() 
		 << std::endl;



  return true;
}



bool testDisplay(double radius, double h)
{

  // Types
  typedef Ball2D<Z2i::Space> Shape;
  typedef Z2i::Space::Point Point;
  typedef Z2i::Space::RealPoint RealPoint;
  typedef Z2i::Space::Integer Integer;
  typedef HyperRectDomain<Z2i::Space> Domain;
  typedef KhalimskySpaceND<Z2i::Space::dimension,Integer> KSpace;
  typedef KSpace::SCell SCell;
  typedef GridCurve<KSpace>::PointsRange PointsRange;
  typedef GridCurve<KSpace>::ArrowsRange ArrowsRange;
  typedef GridCurve<KSpace>::SCellsRange SCellsRange;


  //Forme
  Shape aShape(Point(0,0), radius);

  trace.info() << "#ball created, r=" << radius << endl;

  // Window for the estimation
  RealPoint xLow ( -radius-1, -radius-1 );
  RealPoint xUp( radius+1, radius+1 );
  GaussDigitizer<Z2i::Space,Shape> dig;  
  dig.attach( aShape ); // attaches the shape.
  dig.init( xLow, xUp, h ); 
  // The domain size is given by the digitizer according to the window
  // and the step.
  Domain domain = dig.getDomain();
  // Create cellular space
  KSpace K;
  bool ok = K.init( dig.getLowerBound(), dig.getUpperBound(), true );
  if ( ! ok )
    {
      std::cerr << " "
                << " error in creating KSpace." << std::endl;
      return false;
    }
  try {
      
    // Extracts shape boundary
    SurfelAdjacency<KSpace::dimension> SAdj( true );
    SCell bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
    // Getting the consecutive surfels of the 2D boundary
    std::vector<Point> points;
    Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
    trace.info() << "# tracking..." << endl;
    // Create GridCurve
    GridCurve<KSpace> gridcurve;
    gridcurve.initFromVector( points );
    trace.info() << "#grid curve created, h=" << h << endl;
    
    //ranges
    ArrowsRange ra = gridcurve.getArrowsRange(); 
    PointsRange rp = gridcurve.getPointsRange(); 
    SCellsRange rc = gridcurve.getSCellsRange(); 
    
    //Explicit reshaping for drawing purposes
    Z2i::DigitalSet set(domain);
    Shapes<Z2i::Domain>::euclideanShaper( set, Shape(Point(0,0), radius/h));
         
    Board2D board;
    
    board << domain << set;
    board.saveSVG( "Ranges-Set.svg" );
    
    board.clear();
    board << domain;
    board << rp; 
    // for( PointsRange::ConstIterator it =rp.begin(), ite=rp.end();
    //      it != ite; ++it)
    //   board << (*it);
    board.saveSVG( "Ranges-Points.svg" );
    

    board.clear();
    board << domain;
    board << rc; 
    // for( SCellsRange::ConstIterator it =rc.begin(), ite=rc.end();
    //      it != ite; ++it)
    //   board << (*it);
    board.saveSVG( "Ranges-SCells.svg" );
    

    board.clear();
    board << domain;
    board << ra; 
    // Z2i::Space::Vector shift;
    // board.setPenColor( Color::Black );
    // for(  ArrowsRange::ConstIterator it = ra.begin(), itend = ra.end();
    //       it != itend;   
    //       ++it)
    //   {
    //     shift =   (*it).second ;
    //     draw(board, shift, (*it).first );
    //   }
    board.saveSVG( "Ranges-Arrows.svg" );

  }    
  catch ( InputException e )
    {
      std::cerr << " "
                << " error in finding a bel." << std::endl;
      return false;
    }



  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class LengthEstimators" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  double r = 5; 
  bool res = testLengthEstimatorsOnBall(r,1)
    && testLengthEstimatorsOnBall(r,0.1)
    && testLengthEstimatorsOnBall(r,0.01)
    && testLengthEstimatorsOnBall(r,0.001)
    && testDisplay(r,0.9);
  ;

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
