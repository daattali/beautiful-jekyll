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
 * @file testVoronoiCovarianceMeasure.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/02/09
 *
 * Functions for testing class VoronoiCovarianceMeasure, and also IntegralInvariantEstimator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/Statistic.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/CSurfelLocalEstimator.h"
#include "DGtal/geometry/surfaces/estimation/CDigitalSurfaceLocalEstimator.h"
#include "DGtal/geometry/surfaces/estimation/VoronoiCovarianceMeasureOnDigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/VCMDigitalSurfaceLocalEstimator.h"
#include "DGtal/geometry/surfaces/estimation/TrueDigitalSurfaceLocalEstimator.h"
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantVolumeEstimator.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/ShapeGeometricFunctors.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/io/readers/MPolynomialReader.h"

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class VoronoiCovarianceMeasureOnSurface
///////////////////////////////////////////////////////////////////////////////


/**
 * Example of a test. To be completed.
 *
 */
bool testVoronoiCovarianceMeasureOnSurface()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  using namespace DGtal;
  using namespace DGtal::Z3i; // gets Space, Point, Domain

  typedef MPolynomial< 3, double > Polynomial3;
  typedef MPolynomialReader<3, double> Polynomial3Reader;
  typedef ImplicitPolynomial3Shape<Z3i::Space> ImplicitShape;
  typedef GaussDigitizer< Z3i::Space, ImplicitShape > ImplicitDigitalShape;
  typedef LightImplicitDigitalSurface<KSpace,ImplicitDigitalShape> SurfaceContainer;
  typedef DigitalSurface< SurfaceContainer > Surface;
  typedef Surface::ConstIterator ConstIterator;
  typedef SurfaceContainer::Surfel Surfel;
  typedef ExactPredicateLpSeparableMetric<Space,2> Metric;
  // typedef functors::HatPointFunction<Point,double> KernelFunction;
  typedef functors::BallConstantPointFunction<Point,double> KernelFunction;
  typedef VoronoiCovarianceMeasureOnDigitalSurface<SurfaceContainer,Metric,KernelFunction> VCMOnSurface;
  trace.beginBlock("Creating Surface");
  // std::string poly_str = "1.0-0.16*x^2+0.22*y^2+0.3*z^2";
  std::string poly_str = "-81.0+x^2+y^2+z^2";
  // NB (JOL): II is sensitive to orientation !!
  // std::string poly_str = "81.0-x^2-y^2-z^2"; 
  Polynomial3 poly;
  Polynomial3Reader reader;
  std::string::const_iterator iter = reader.read( poly, poly_str.begin(), poly_str.end() );
  if ( iter != poly_str.end() )
    {
      std::cerr << "ERROR: I read only <"
                << poly_str.substr( 0, iter - poly_str.begin() )
                << ">, and I built P=" << poly << std::endl;
      return 1;
    }
  CountedPtr<ImplicitShape> shape( new ImplicitShape( poly ) );

  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;

  // Digitizer
  CountedPtr<ImplicitDigitalShape> dshape( new ImplicitDigitalShape() );
  dshape->attach( *shape );
  dshape->init( p1, p2, 1.0 );
  Surfel bel = Surfaces<KSpace>::findABel( K, *dshape, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, *dshape, SurfelAdjacency<KSpace::dimension>( true ), bel );
  CountedConstPtrOrConstPtr<Surface> ptrSurface( new Surface( surfaceContainer ) ); // acquired
  trace.endBlock();

  trace.beginBlock("Computing VCM on surface." );
  KernelFunction chi( 1.0, 7.0 );
  CountedPtr<VCMOnSurface> vcm_surface( new VCMOnSurface( ptrSurface, Pointels, 
                                                          5.0, 7.0, chi, 7.0, Metric(), true ) );
  trace.endBlock();

  trace.beginBlock("Wrapping normal estimator." );
  typedef functors::VCMNormalVectorFunctor<VCMOnSurface> NormalVectorFunctor;
  typedef VCMDigitalSurfaceLocalEstimator<SurfaceContainer,Metric,
                                          KernelFunction, NormalVectorFunctor> VCMNormalEstimator;
  VCMNormalEstimator estimator( vcm_surface );
  estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  trace.endBlock();

  trace.beginBlock("Computing II normals on surfels of volume." );
  typedef functors::IINormalDirectionFunctor<Space> IINormalFunctor;
  typedef IntegralInvariantCovarianceEstimator<KSpace, ImplicitDigitalShape,
                                               IINormalFunctor> IINormalEstimator;
  IINormalEstimator ii_estimator( K, *dshape );
  ii_estimator.setParams( 5.0 );
  ii_estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  trace.endBlock();

  trace.beginBlock("Evaluating normals wrt true normal." );
  typedef ShapeGeometricFunctors::ShapeNormalVectorFunctor<ImplicitShape> NormalFunctor;
  typedef TrueDigitalSurfaceLocalEstimator<KSpace, ImplicitShape, NormalFunctor> TrueNormalEstimator;
  
  BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator< IINormalEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceLocalEstimator< VCMNormalEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator< TrueNormalEstimator > ));

  TrueNormalEstimator true_estimator;
  true_estimator.setParams( K, NormalFunctor() );
  true_estimator.attach( shape );
  true_estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  Statistic<double> error_true;
  Statistic<double> error_triv_true;
  Statistic<double> error_ii_true;
  for ( ConstIterator it = ptrSurface->begin(), itE = ptrSurface->end(); it != itE; ++it )
    {
      RealVector n_est  = estimator.eval( it );
      RealVector n_true = true_estimator.eval( it );
      RealVector n_triv = - vcm_surface->mapSurfel2Normals().find( *it )->second.trivialNormal;
      RealVector n_ii = ii_estimator.eval( it );
      error_true.addValue( n_est.dot( n_true ) );
      error_triv_true.addValue( n_triv.dot( n_true ) );
      if ( n_ii.dot( n_triv ) < 0 ) n_ii = -n_ii;
      error_ii_true.addValue( n_ii.dot( n_true ) );
    }
  error_true.terminate();
  error_triv_true.terminate();
  error_ii_true.terminate();
  trace.info() << "VCM/true  cos angle avg = " << error_true.mean() << std::endl;
  trace.info() << "VCM/true  cos angle dev = " << sqrt( error_true.unbiasedVariance() ) << std::endl;
  trace.info() << "II/true cos angle avg = " << error_ii_true.mean() << std::endl;
  trace.info() << "II/true cos angle dev = " << sqrt( error_ii_true.unbiasedVariance() ) << std::endl;
  trace.info() << "triv/true cos angle avg = " << error_triv_true.mean() << std::endl;
  trace.info() << "triv/true cos angle dev = " << sqrt( error_triv_true.unbiasedVariance() ) << std::endl;
  nbok += error_true.mean() > 0.95 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "VCM/true cos angle avg > 0.95" << std::endl;
  nbok += sqrt( error_true.unbiasedVariance() ) < 0.05 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "VCM/true cos angle dev < 0.05" << std::endl;
  // nbok += error_true.mean() > error_triv_true.mean() ? 1 : 0;
  // nb++;
  // trace.info() << "(" << nbok << "/" << nb << ") "
  //              << "VCM/true is closer to 1.0 than triv/true." << std::endl;

  nbok += error_ii_true.mean() > 0.95 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "II/true cos angle avg > 0.95" << std::endl;
  nbok += sqrt( error_ii_true.unbiasedVariance() ) < 0.05 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "II/true cos angle dev < 0.05" << std::endl;
  nbok += error_ii_true.mean() > error_triv_true.mean() ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "II/true is closer to 1.0 than triv/true." << std::endl;

  trace.endBlock();

  trace.beginBlock("Computing II mean curvatures." );
  typedef functors::IIMeanCurvature3DFunctor<Space> IICurvatureFunctor;
  typedef IntegralInvariantVolumeEstimator<KSpace, ImplicitDigitalShape,
                                           IICurvatureFunctor> IICurvatureEstimator;
  IICurvatureEstimator ii_curv_estimator( K, *dshape );
  ii_curv_estimator.setParams( 5.0 );
  ii_curv_estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  trace.endBlock();

  trace.beginBlock("Computing VCM mean curvatures." );
  typedef functors::VCMMeanAbsoluteCurvatures3DFunctor<VCMOnSurface> VCMCurvatureFunctor;
  typedef VCMDigitalSurfaceLocalEstimator<SurfaceContainer,Metric,
                                          KernelFunction, VCMCurvatureFunctor> VCMCurvatureEstimator;
  VCMCurvatureEstimator vcm_curv_estimator( vcm_surface );
  vcm_curv_estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  trace.endBlock();

  trace.beginBlock("Computing ground truth mean curvatures." );
  typedef ShapeGeometricFunctors::ShapeMeanCurvatureFunctor<ImplicitShape> CurvatureFunctor;
  typedef TrueDigitalSurfaceLocalEstimator<KSpace, ImplicitShape, CurvatureFunctor> TrueCurvatureEstimator;
  
  TrueCurvatureEstimator true_curv_estimator;
  true_curv_estimator.setParams( K, CurvatureFunctor() );
  true_curv_estimator.attach( shape );
  true_curv_estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );
  trace.endBlock();

  BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator< IICurvatureEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceLocalEstimator< VCMCurvatureEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator< TrueCurvatureEstimator > ));

  
  trace.beginBlock("Evaluating curvatures." );
  Statistic<double> stat_vcm_curv;
  Statistic<double> stat_ii_curv;
  Statistic<double> stat_true_curv;
  for ( ConstIterator it = ptrSurface->begin(), itE = ptrSurface->end(); it != itE; ++it )
    {
      stat_ii_curv.addValue( ii_curv_estimator.eval( it ) );
      stat_vcm_curv.addValue( vcm_curv_estimator.eval( it ) );
      stat_true_curv.addValue( true_curv_estimator.eval( it ) );
    }
  stat_ii_curv.terminate();
  stat_vcm_curv.terminate();
  stat_true_curv.terminate();
  trace.info() << "- II curv: E[X]=" << stat_ii_curv.mean()
               << " min=" << stat_ii_curv.min()
               << " max=" << stat_ii_curv.max() << std::endl;
  trace.info() << "- VCM curv: E[X]=" << stat_vcm_curv.mean()
               << " min=" << stat_vcm_curv.min()
               << " max=" << stat_vcm_curv.max() << std::endl;
  trace.info() << "- TRUE curv: E[X]=" << stat_true_curv.mean()
               << " min=" << stat_true_curv.min()
               << " max=" << stat_true_curv.max() << std::endl;
  nbok += ( std::abs( stat_ii_curv.mean() - 0.11 ) < 0.05 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "mean of II curv is around 0.11: " 
               << std::abs( stat_ii_curv.mean() - 0.11 ) << std::endl;
  nbok += ( std::abs( stat_vcm_curv.mean() - 0.11 ) < 0.05 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "mean of VCM curv is around 0.11: "
               << std::abs( stat_vcm_curv.mean() - 0.11 ) << std::endl;

  trace.endBlock();
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /* argc */, char** /* argv */ )
{
  using namespace std;
  using namespace DGtal;
  trace.beginBlock ( "Testing VoronoiCovarianceMeasureOnSurface ..." );
  bool res = testVoronoiCovarianceMeasureOnSurface();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
