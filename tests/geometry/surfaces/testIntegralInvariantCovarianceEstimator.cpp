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
 * @file testIntegralInvariantCovarianceEstimator.cpp
 * @ingroup Tests
 * @author Jérémy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2014/06/26
 *
 * Functions for testing class IntegralInvariantCovarianceEstimator and IIGeometricFunctor.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

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


using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class IntegralInvariantCovarianceEstimator and IIGeometricFunctor.
///////////////////////////////////////////////////////////////////////////////

bool testGaussianCurvature3d( double h, double delta )
{
  typedef ImplicitBall<Z3i::Space> ImplicitShape;
  typedef GaussDigitizer<Z3i::Space, ImplicitShape> DigitalShape;
  typedef LightImplicitDigitalSurface<Z3i::KSpace,DigitalShape> Boundary;
  typedef DigitalSurface< Boundary > MyDigitalSurface;
  typedef DepthFirstVisitor< MyDigitalSurface > Visitor;
  typedef GraphVisitorRange< Visitor > VisitorRange;
  typedef VisitorRange::ConstIterator VisitorConstIterator;

  typedef functors::IIGaussianCurvature3DFunctor<Z3i::Space> MyIICurvatureFunctor;
  typedef IntegralInvariantCovarianceEstimator< Z3i::KSpace, DigitalShape, MyIICurvatureFunctor > MyIICurvatureEstimator;
  typedef MyIICurvatureFunctor::Value Value;

  double re = 5.0;
  double radius = 5.0;
  double realValue = 1.0/(radius * radius);

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

  trace.beginBlock( "Curvature estimator initialisation ...");
  
  VisitorRange range( new Visitor( surf, *surf.begin() ));
  VisitorConstIterator ibegin = range.begin();
  VisitorConstIterator iend = range.end();

  MyIICurvatureFunctor curvatureFunctor;
  curvatureFunctor.init( h, re );

  MyIICurvatureEstimator curvatureEstimator( curvatureFunctor );
  curvatureEstimator.attach( K, dshape );
  curvatureEstimator.setParams( re/h );
  curvatureEstimator.init( h, ibegin, iend );

  trace.endBlock();

  trace.beginBlock( "Curvature estimator evaluation ...");

  std::vector< Value > results;
  std::back_insert_iterator< std::vector< Value > > resultsIt( results );
  curvatureEstimator.eval( ibegin, iend, resultsIt );

  trace.endBlock();

  trace.beginBlock ( "Comparing results of integral invariant 3D Gaussian curvature ..." );

  double mean = 0.0;
  unsigned int rsize = static_cast<unsigned int>(results.size());

  if( rsize == 0 )
  {
    trace.error() << "ERROR: surface is empty" << std::endl;
    trace.endBlock();
    return false;
  }

  for ( unsigned int i = 0; i < rsize; ++i )
  {
    mean += results[ i ];
  }
  mean /= rsize;

  if( mean != mean ) //NaN
  {
    trace.error() << "ERROR: result is NaN" << std::endl;
    trace.endBlock();
    return false;
  }

  double v = std::abs ( realValue - mean );

  trace.warning() << "True value: " << realValue << std::endl;
  trace.warning() << "Mean value: " << mean << std::endl;
  trace.warning() << "Delta: " << delta << " |true - mean|: " << v << std::endl;

  if( v > delta )
  {
    trace.endBlock();
    return false;
  }
  trace.endBlock();
  return true;
}

bool testPrincipalCurvatures3d( double h )
{
  typedef ImplicitBall<Z3i::Space> ImplicitShape;
  typedef GaussDigitizer<Z3i::Space, ImplicitShape> DigitalShape;
  typedef LightImplicitDigitalSurface<Z3i::KSpace,DigitalShape> Boundary;
  typedef DigitalSurface< Boundary > MyDigitalSurface;
  typedef DepthFirstVisitor< MyDigitalSurface > Visitor;
  typedef GraphVisitorRange< Visitor > VisitorRange;
  typedef VisitorRange::ConstIterator VisitorConstIterator;

  typedef functors::IIPrincipalCurvatures3DFunctor<Z3i::Space> MyIICurvatureFunctor;
  typedef IntegralInvariantCovarianceEstimator< Z3i::KSpace, DigitalShape, MyIICurvatureFunctor > MyIICurvatureEstimator;
  typedef MyIICurvatureFunctor::Value Value;

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

  trace.beginBlock( "Curvature estimator initialisation ...");
  
  VisitorRange range( new Visitor( surf, *surf.begin() ));
  VisitorConstIterator ibegin = range.begin();
  VisitorConstIterator iend = range.end();

  MyIICurvatureFunctor curvatureFunctor;
  curvatureFunctor.init( h, re );

  MyIICurvatureEstimator curvatureEstimator( curvatureFunctor );
  curvatureEstimator.attach( K, dshape );
  curvatureEstimator.setParams( re/h );
  curvatureEstimator.init( h, ibegin, iend );

  trace.endBlock();

  trace.beginBlock( "Curvature estimator evaluation ...");

  std::vector< Value > results;
  std::back_insert_iterator< std::vector< Value > > resultsIt( results );
  curvatureEstimator.eval( ibegin, iend, resultsIt );

  trace.endBlock();

  trace.beginBlock ( "Comparing results of integral invariant 3D Gaussian curvature ..." );

  unsigned int error_order = 0;
  unsigned int rsize = static_cast<unsigned int>(results.size());

  if( rsize == 0 )
  {
    trace.error() << "ERROR: surface is empty" << std::endl;
    trace.endBlock();
    return false;
  }

  for ( unsigned int i = 0; i < rsize; ++i )
  {
    if( std::abs(results[i].first) < std::abs(results[i].second) )
    {
      ++error_order;
    }
  }

  trace.warning() << "Error order: " << error_order << std::endl;
  trace.warning() << "If not equals to 0, something is wrong..." << std::endl;

  trace.endBlock();

  if( error_order != 0 )
  {
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class IntegralInvariantCovarianceEstimator and 3d functors" );
    bool res = testGaussianCurvature3d( 0.6, 0.007 ) && testPrincipalCurvatures3d( 0.6 );
    trace.emphase() << ( res ? "Passed." : "Error." ) << std::endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
