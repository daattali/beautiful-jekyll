/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

/**
* @file testHeatLaplace.cpp
* @ingroup Tests
* @author Thomas Caissard (\c thomas.caissard@liris.cnrs.fr )
*
* @date 2018/02/02
*
* Tests of the heat Laplace operator from DEC
*
* This file is part of the DGtal library.
*/

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/math/linalg/EigenSupport.h"

#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"

#include "DGtal/shapes/parametric/Ball3D.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/ImplicitDigitalSurface.h"

#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.h"

#include "DGtalCatch.h"

using namespace DGtal;

typedef EigenLinearAlgebraBackend::SparseMatrix SparseMatrix;
typedef EigenLinearAlgebraBackend::DenseMatrix DenseMatrix;

bool test_operator( const DenseMatrix& M )
{
  bool test = true;

  for( int i = 0; i < M.rows(); i++ )
  {
    for( int j = 0; j < M.cols(); j++ )
    {
      if( i == j && M(i, j) > 0 ) test = false;
      if( i != j && M(i, j) < 0 )  test = false;
    }

    if( M.row(i).sum() >= 1e-10 )  test = false;
  }

  return test;
}

bool laplace_sphere( const double& h )
{
  typedef Z3i::Space Space;
  typedef Z3i::KSpace KSpace;
  typedef Z3i::Domain Domain;
  typedef Z3i::Point Point;
  typedef Z3i::Vector Vector;
  typedef Ball3D<Space> Ball;
  typedef GaussDigitizer<Space, Ball> GaussDigitizer;
  typedef ImplicitDigitalSurface<KSpace, GaussDigitizer> MyImplicitDigitalSurface;
  typedef DigitalSurface<MyImplicitDigitalSurface> MyDigitalSurface;

  Ball ball( Point(0, 0, 0), 1.0 );

  GaussDigitizer digitizer;
  digitizer.attach( ball );
  digitizer.init( ball.getLowerBound() + Vector(-1, -1, -1), ball.getUpperBound() + Vector(1, 1, 1), h );

  Domain domain = digitizer.getDomain();

  KSpace kspace;
  kspace.init( domain.lowerBound(), domain.upperBound(), true );

  SurfelAdjacency<KSpace::dimension> SAdj( true );
  KSpace::Surfel bel = Surfaces<KSpace>::findABel( kspace, digitizer, 10000 );
  MyImplicitDigitalSurface ImpSurf( kspace, digitizer, SAdj, bel );
  MyDigitalSurface digSurf( ImpSurf );

  typedef functors::IINormalDirectionFunctor<Space> MyIINormalFunctor;
  typedef IntegralInvariantCovarianceEstimator<KSpace, GaussDigitizer, MyIINormalFunctor> MyIINormalEstimator;

  MyIINormalFunctor normalFunctor;
  normalFunctor.init( h, 3.5 * pow( h, 1. / 3. ) );

  MyIINormalEstimator normalEstimator( normalFunctor );
  normalEstimator.attach( kspace, digitizer );
  normalEstimator.setParams( 3.5 * pow( h, 1. / 3. ) / h );
  normalEstimator.init( h, digSurf.begin(), digSurf.end() );

  typedef DiscreteExteriorCalculus<2, 3, EigenLinearAlgebraBackend> Calculus;
  typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;

  const Calculus calculus = CalculusFactory::createFromNSCells<2>( digSurf.begin(), digSurf.end(), normalEstimator, h );

  const double t = 0.1 * pow( h, 2./3. );
  const double cut_locus = log( - log1p( t ) ) + 2.;
  const Calculus::PrimalIdentity0 laplace_primal = calculus.heatLaplace<PRIMAL>( h, t, cut_locus );
  const Calculus::DualIdentity0   laplace_dual   = calculus.heatLaplace<DUAL>( h, t, cut_locus );

  return test_operator( laplace_primal.myContainer ) && test_operator( laplace_dual.myContainer );
}

TEST_CASE( "Operator Test" )
{
  SECTION( "Test" )
  {
    REQUIRE( laplace_sphere( 1.0 ) );
    REQUIRE( laplace_sphere( 0.5 ) );
    REQUIRE( laplace_sphere( 0.2 ) );
  }
}
