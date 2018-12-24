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
 * @file testEstimatorCache.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/09/30
 *
 * Functions for testing class EstimatorCache.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/surfaces/estimation/EstimatorCache.h"
///
/// Shape
#include "DGtal/shapes/implicit/ImplicitBall.h"

 /// Digitization
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"

/// Estimator
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class EstimatorCache.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testEstimatorCache(double h)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
    
  typedef ImplicitBall<Z3i::Space> ImplicitShape;
  typedef GaussDigitizer<Z3i::Space, ImplicitShape> DigitalShape;
  typedef LightImplicitDigitalSurface<Z3i::KSpace,DigitalShape> Boundary;
  typedef DigitalSurface< Boundary > MyDigitalSurface;
  typedef DepthFirstVisitor< MyDigitalSurface > Visitor;
  typedef GraphVisitorRange< Visitor > VisitorRange;
  typedef VisitorRange::ConstIterator VisitorConstIterator;

  typedef functors::IIGaussianCurvature3DFunctor<Z3i::Space> MyIICurvatureFunctor;
  typedef IntegralInvariantCovarianceEstimator< Z3i::KSpace, DigitalShape, MyIICurvatureFunctor > MyIICurvatureEstimator;
//  typedef MyIICurvatureFunctor::Value Value;

  double re = 5.0;
  double radius = 5.0;

  trace.beginBlock( "Shape initialisation ..." );

  ImplicitShape ishape( Z3i::RealPoint( 0, 0, 0 ), radius );
  DigitalShape dshape;
  dshape.attach( ishape );
  dshape.init( Z3i::RealPoint( -10.0, -10.0, -10.0 ), Z3i::RealPoint( 10.0, 10.0, 10.0 ), h );

  Z3i::KSpace K;
  if ( !K.init( dshape.getLowerBound(), dshape.getUpperBound(), true ) )
  {
    trace.error() << "Problem with Khalimsky space" << std::endl;
    return false;
  }

  Z3i::KSpace::Surfel bel = Surfaces<Z3i::KSpace>::findABel( K, dshape, 10000 );
  Boundary boundary( K, dshape, SurfelAdjacency<Z3i::KSpace::dimension>( true ), bel );
  MyDigitalSurface surf ( boundary );

  trace.endBlock();

  trace.beginBlock( "Curvature estimator computation ...");
  
  VisitorRange range( new Visitor( surf, *surf.begin() ));
  VisitorConstIterator ibegin = range.begin();
  VisitorConstIterator iend = range.end();

  MyIICurvatureFunctor curvatureFunctor;
  curvatureFunctor.init( h, re );

  MyIICurvatureEstimator curvatureEstimator( curvatureFunctor );
  curvatureEstimator.attach( K, dshape );
  curvatureEstimator.setParams( re/h );
  curvatureEstimator.init( h, ibegin, iend );

  std::vector<MyIICurvatureEstimator::Quantity> results;
  std::back_insert_iterator< std::vector<MyIICurvatureEstimator::Quantity> > itback(results);

  curvatureEstimator.eval(ibegin,iend,itback);
  trace.info() << "Number of values = "<< results.size()<<std::endl;
  trace.endBlock();

  trace.beginBlock( "Caching values ...");
  VisitorRange range2( new Visitor( surf, *surf.begin() ));
  VisitorConstIterator ibegin2 = range2.begin();
  VisitorConstIterator iend2 = range2.end();
  
  typedef EstimatorCache<MyIICurvatureEstimator> GaussianCache;

  BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator<GaussianCache> ));
    
  GaussianCache cache( curvatureEstimator );
  cache.init( h, ibegin2, iend2 );
  trace.info() << "Number of cached values = "<< cache.size()<<std::endl;

  trace.info() << "Value at begin="<< cache.eval(surf.begin())<<"  expected = "<< curvatureEstimator.eval(surf.begin())<<std::endl;
  trace.endBlock();


  trace.beginBlock( "Complete test ...");
  bool ok=true;
  for(MyDigitalSurface::ConstIterator it = surf.begin(), itend=surf.end(); it != itend; ++it)
    {
      if (  cache.eval(it) != curvatureEstimator.eval(it) )
        {
          ok=false;
          trace.error() << "Incorrect values at "<<*it<<" read " <<cache.eval(it)<< " and expecting "<<curvatureEstimator.eval(it)<<std::endl;
        }
    }
  trace.endBlock();

  trace.beginBlock( "Timing cache access ...");
  for(MyDigitalSurface::ConstIterator it = surf.begin(), itend=surf.end(); it != itend; ++it)
    {
      if (  cache.eval(it) == 12345678 ) //making sure to visit
                                             //all surfels
        {
          ok=false;
          trace.error() << "Incorrect values at "<<*it<<std::endl;
        }
    }
  trace.endBlock();

  trace.beginBlock( "Copy construction and timing cache access ...");
  GaussianCache cache2(cache);
  trace.info() << "Number of cached values = "<< cache.size()<<std::endl;
  trace.info() << "Value at begin="<< cache2.eval(surf.begin())<<"  expected = "<< curvatureEstimator.eval(surf.begin())<<std::endl;
  for(MyDigitalSurface::ConstIterator it = surf.begin(), itend=surf.end(); it != itend; ++it)
    {
      if (  cache.eval(it) == 12345678 ) //making sure to visit
                                         //all surfels
        {
          ok=false;
          trace.error() << "Incorrect values at "<<*it<<std::endl;
        }
    }
  trace.endBlock();


  
  nbok += ok ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "cache == eval" << std::endl;
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class EstimatorCache" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testEstimatorCache( 0.8 ); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
