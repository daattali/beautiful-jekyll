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
 * @file testTrueLocalEstimator.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/06/30
 *
 * Functions for testing class TrueLocalEstimator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"

#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/estimation/CCurveLocalGeometricEstimator.h"
#include "DGtal/geometry/curves/estimation/TrueLocalEstimatorOnPoints.h"
#include "DGtal/geometry/curves/estimation/TrueGlobalEstimatorOnPoints.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeCurvatureFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeTangentFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeArcLengthFunctor.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"
#include "DGtal/geometry/curves/estimation/CompareLocalEstimators.h"


#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TrueLocalEstimator.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testTrueLocalEstimator(const std::string &filename)
{
  trace.info() << "Reading GridCurve " << endl;
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  typedef KhalimskySpaceND<2> Kspace; //space
  GridCurve<Kspace> c; 
  c.initFromVectorStream(instream); //building grid curve
  typedef GridCurve<Kspace >::PointsRange Range;//range
  Range r = c.getPointsRange();//building range

  
  typedef Ball2D<Z2i::Space> Shape;
  typedef GridCurve<KhalimskySpaceND<2> >::PointsRange Range;
  typedef Range::ConstIterator ConstIteratorOnPoints;
  typedef ParametricShapeCurvatureFunctor< Shape > Curvature;
  typedef ParametricShapeTangentFunctor< Shape > Tangent;
  typedef ParametricShapeArcLengthFunctor< Shape > Length;

  Shape ball(Z2i::Point(0,0), 30);

   
  typedef TrueLocalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Curvature  > TrueCurvatureEstimator;
  typedef TrueLocalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Tangent  > TrueTangentEstimator;
  typedef TrueGlobalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Length  >  TrueLengthEstimator;

  BOOST_CONCEPT_ASSERT(( concepts::CCurveLocalGeometricEstimator< TrueCurvatureEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CCurveLocalGeometricEstimator< TrueTangentEstimator > ));
  TrueCurvatureEstimator curvatureEstimator;
  TrueTangentEstimator tangentEstimator;
  TrueLengthEstimator lengthEstimator;

  curvatureEstimator.init( 1, r.begin(), r.end() );
  curvatureEstimator.attach( &ball );
  tangentEstimator.init( 1, r.begin(), r.end() );
  tangentEstimator.attach( &ball );
 

  ConstIteratorOnPoints it = r.begin();
  ConstIteratorOnPoints it2 = it+15;
  lengthEstimator.init( 1, it, it2, &ball, true);
  
  
  trace.info() << "Current point = "<<*it<<std::endl;
  trace.info() << "Current point+15 = "<<*it2<<std::endl;
  trace.info() << "Eval curvature (begin, h=1) = "<< curvatureEstimator.eval(it2)<<std::endl;
  trace.info() << "Eval tangent (begin, h=1) = "<< tangentEstimator.eval(it2)<<std::endl;
  trace.info() << "Eval length ( h=1) = "<< lengthEstimator.eval(it,it2)<<std::endl;
  
  return true;

}

template <typename Shape>
bool 
testTrueLocalEstimatorOnShapeDigitization( const string & name,
             Shape & aShape, double h )
{
  using namespace Z2i;

  trace.beginBlock ( ( "Testing TrueLocalEstimator on digitization of "
           + name ). c_str() );
  
  // Creates a digitizer on the window (xLow, xUp).
  typedef Space::RealPoint RealPoint;
  RealPoint xLow( -10.0, -10.0 );
  RealPoint xUp( 10.0, 10.0 );
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
      std::cerr << "[testTrueLocalEstimatorOnShapeDigitization]"
    << " error in creating KSpace." << std::endl;
    }
  else
    try {
      // Extracts shape boundary
      SurfelAdjacency<KSpace::dimension> SAdj( true );
      SCell bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
      // Getting the consecutive surfels of the 2D boundary
      std::vector<Point> points;
      Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
      // Create GridCurve
      GridCurve<KSpace> gridcurve;
      gridcurve.initFromVector( points );
      typedef GridCurve<KhalimskySpaceND<2> >::PointsRange Range;
      typedef Range::ConstIterator ConstIteratorOnPoints;
      typedef ParametricShapeCurvatureFunctor< Shape > Curvature;
      TrueLocalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Curvature  >  curvatureEstimator;
      Range r = gridcurve.getPointsRange();//building range
      curvatureEstimator.init( h, r.begin(), r.end() );
      curvatureEstimator.attach( &aShape ); 
      std::cout << "# idx x y kappa" << endl;
      unsigned int i = 0;
      for ( ConstIteratorOnPoints it = r.begin(), ite = r.end();
      it != ite; ++it, ++i )
  {
    RealPoint x = *it;
    double kappa = curvatureEstimator.eval( it );
    std::cout << i << " " << x[ 0 ] << " " << x[1] 
        << " " << kappa << std::endl;
  }
    }    
    catch ( InputException e )
      {
  std::cerr << "[testTrueLocalEstimatorOnShapeDigitization]"
      << " error in finding a bel." << std::endl;
  ok = false;
      }
  trace.emphase() << ( ok ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return ok;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class TrueLocalEstimator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;



  std::string sinus2D4 = testPath + "samples/sinus2D4.dat";

  bool res = testTrueLocalEstimator(sinus2D4); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  typedef Ellipse2D< Z2i::Space > MyEllipse;
  MyEllipse ellipse( 1.2, 0.1, 4.0, 3.0, 0.3 );
  res = res && 
    testTrueLocalEstimatorOnShapeDigitization<MyEllipse>
    ( "Ellipse-4-3-0.3-s1", ellipse, 1 );
  res = res && 
    testTrueLocalEstimatorOnShapeDigitization<MyEllipse>
    ( "Ellipse-4-3-0.3-s0.5", ellipse, 0.5 );

  typedef Flower2D< Z2i::Space > MyFlower;
  MyFlower flower( 0.5, -2.3, 5.0, 0.7, 6, 0.3 );
  res = res && 
    testTrueLocalEstimatorOnShapeDigitization<MyFlower>
    ( "Flower-5-0.3-6-0.3-s1", flower, 1 );
  res = res && 
    testTrueLocalEstimatorOnShapeDigitization<MyFlower>
    ( "Flower-5-0.3-6-0.3-s0.25", flower, 0.25 );

  return res ? 0 : 1;

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
