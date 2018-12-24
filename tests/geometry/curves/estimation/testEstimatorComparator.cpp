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
 * @file testEstimatorComparator.cpp
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

#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"

#include "DGtal/geometry/curves/estimation/TrueLocalEstimatorOnPoints.h"

#include "DGtal/geometry/curves/estimation/ParametricShapeCurvatureFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeTangentFunctor.h"
#include "DGtal/geometry/curves/estimation/ParametricShapeArcLengthFunctor.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"

#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/geometry/curves/GridCurve.h"

#include "DGtal/geometry/curves/estimation/CompareLocalEstimators.h"


#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


template <typename Shape>
bool testCompareEstimator(const std::string &name, Shape & aShape, double h)
{
  using namespace Z2i;

  trace.beginBlock ( ( "Testing CompareEstimator on digitization of "
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
      std::cerr << "[testCompareEstimators]"
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
      Range r = gridcurve.getPointsRange();//building range

      unsigned int nb = 0; 
      unsigned int nbok = 0; 
      //curvature
      typedef ParametricShapeCurvatureFunctor< Shape > Curvature;
      typedef TrueLocalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Curvature  >  TrueCurvature;
      TrueCurvature curvatureEstimator;
      TrueCurvature curvatureEstimatorBis;
      curvatureEstimator.init( h, r.begin(), r.end() );
      curvatureEstimator.attach( &aShape ); 
      curvatureEstimatorBis.init( h, r.begin(), r.end() );
      curvatureEstimatorBis.attach( &aShape ); 

      typedef CompareLocalEstimators< TrueCurvature, TrueCurvature> Comparator;

      trace.info()<< "True curvature comparison at "<< *r.begin() << " = "
		  << Comparator::compare(curvatureEstimator,curvatureEstimatorBis, r.begin())
		  << std::endl;
      
      typename Comparator::OutputStatistic error
	=Comparator::compare(curvatureEstimator, curvatureEstimatorBis, 
			     r.begin(),
			     r.end());
      
      trace.info() << "Nb samples= "<< error.samples()<<std::endl;
      trace.info() << "Error mean= "<< error.mean()<<std::endl;
      trace.info() << "Error max= "<< error.max()<<std::endl;
      nbok += ( ( ( (unsigned int)error.samples() ) == r.size())
                && (error.max() == 0) )
        ? 1 : 0; 
      nb++;
      trace.info() << nbok << "/" << nb << std::endl; 

      //tangents
      typedef ParametricShapeTangentFunctor< Shape > Tangent;
      typedef TrueLocalEstimatorOnPoints< ConstIteratorOnPoints, Shape, Tangent  >  TrueTangent;

      typedef ArithmeticalDSSComputer<ConstIteratorOnPoints,KSpace::Integer,4> 
  SegmentComputer;
      typedef TangentFromDSSEstimator<SegmentComputer> Functor;
      typedef MostCenteredMaximalSegmentEstimator<SegmentComputer,Functor> 
  MSTangentEstimator;

      SegmentComputer sc;
      Functor f; 
      
      TrueTangent tang1;
      MSTangentEstimator tang2(sc, f); 
    
      tang1.init( h, r.begin(), r.end() );
      tang1.attach( &aShape ); 
      tang2.init( h, r.begin(), r.end() );
      
      typedef CompareLocalEstimators< TrueTangent, MSTangentEstimator> ComparatorTan;

      trace.info()<< "Tangent comparison at "<< *r.begin() << " = " 
		  << ComparatorTan::compareVectors( tang1, tang2, r.begin())
		  << std::endl; 
      
      typename ComparatorTan::OutputVectorStatistic error2
	=ComparatorTan::compareVectors(tang1, tang2, 
				       r.begin(),
				       r.end());
      
      trace.info()<< "Nb samples= "<< error2.samples()<<std::endl;
      trace.info()<< "Error mean= "<< error2.mean()<<std::endl;
      trace.info()<< "Error max= "<< error2.max()<<std::endl;
      nbok += (error.samples() == r.size())?1:0; 
      nb++;
      trace.info() << nbok << "/" << nb << std::endl; 
      ok += (nb == nbok); 

     }    
    catch ( InputException e )
      {
  std::cerr << "[testCompareEstimator]"
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
  trace.beginBlock ( "Testing class CompareLocalEstimator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  typedef Flower2D< Z2i::Space > MyFlower;
  MyFlower flower( 0.5, -2.3, 5.0, 0.7, 6, 0.3 );
  bool res = testCompareEstimator<MyFlower>("Flower", flower, 0.25);
  return res ? 0 : 1;

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
