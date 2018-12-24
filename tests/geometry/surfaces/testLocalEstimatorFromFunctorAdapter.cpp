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
 * @file testLocalEstimatorFromFunctorAdapter.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/28
 *
 * Functions for testing class LocalEstimatorFromFunctorAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/graph/DistanceBreadthFirstVisitor.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/BasicEstimatorFromSurfelsFunctors.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/CLocalEstimatorFromSurfelFunctor.h"

#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"

#include "DGtal/geometry/surfaces/estimation/estimationFunctors/ElementaryConvolutionNormalVectorEstimator.h"


#ifdef WITH_CGAL
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingGaussianCurvatureEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingMeanCurvatureEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/LinearLeastSquareFittingNormalVectorEstimator.h"
#endif

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LocalEstimatorFromFunctorAdapter.
///////////////////////////////////////////////////////////////////////////////



template <typename TPoint3>
struct ImplicitDigitalEllipse3 {
  typedef TPoint3 Point;
  inline
  ImplicitDigitalEllipse3( double a, double b, double c )
  : myA( a ), myB( b ), myC( c )
  {}
  inline
  bool operator()( const TPoint3 & p ) const
  {
    double x = ( (double) p[ 0 ] / myA );
    double y = ( (double) p[ 1 ] / myB );
    double z = ( (double) p[ 2 ] / myC );
    return ( x*x + y*y + z*z ) <= 1.0;
  }
  double myA, myB, myC;
};


/**
 * Example of a test. To be completed.
 *
 */
bool testLocalEstimatorFromFunctorAdapter()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing init ..." );

  using namespace Z3i;
  typedef ImplicitDigitalEllipse3<Point> ImplicitDigitalEllipse;
  typedef LightImplicitDigitalSurface<KSpace,ImplicitDigitalEllipse> SurfaceContainer;
  typedef DigitalSurface< SurfaceContainer > Surface;
  typedef SurfaceContainer::SurfelConstIterator ConstIterator;
  typedef SurfaceContainer::Surfel Surfel;


  trace.beginBlock("Creating Surface");
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;
  ImplicitDigitalEllipse ellipse( 6.0, 4.5, 3.4 );
  Surfel bel = Surfaces<KSpace>::findABel( K, ellipse, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, ellipse, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired
  unsigned int nbsurfels = 0;
  for ( ConstIterator it = surface.begin(), it_end = surface.end();
       it != it_end; ++it )
  {
    ++nbsurfels;
  }
  trace.info() << nbsurfels << " surfels found." << std::endl;
  trace.endBlock();

  trace.beginBlock("Creating  adapter");
  typedef DGtal::functors::DummyEstimatorFromSurfels<Surfel, CanonicSCellEmbedder<KSpace> > Functor;
  typedef DGtal::functors::ConstValue< double > ConvFunctor;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, 
                                                 Functor, ConvFunctor> Reporter;

  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, 
                                                 Functor, DGtal::functors::GaussianKernel> ReporterGaussian;

  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
  Functor estimator(embedder, 1);

  ConvFunctor convFunc(1.0);
  Reporter reporter;//(surface,l2Metric,estimator,convFunc);
  reporter.attach(surface);
  reporter.setParams(l2Metric,estimator,convFunc, 5);

  //We just test the init for Gaussian
  DGtal::functors::GaussianKernel gaussKernelFunc(1.0);
  ReporterGaussian reporterGaussian;
  reporterGaussian.attach(surface);
  reporterGaussian.setParams(l2Metric,estimator,gaussKernelFunc, 5.0);
  reporterGaussian.init(1, surface.begin(), surface.end());

  reporter.init(1.0, surface.begin(), surface.end());
  Functor::Quantity val = reporter.eval( surface.begin() );
  trace.info() <<  "Value with radius 5= "<<val << std::endl;
  nbok += ((fabs((double)val - 124.0)) < 40) ? 1 : 0;
  nb++;

  reporter.setParams(l2Metric,estimator,convFunc, 20.0);
  reporter.init(1, surface.begin(), surface.end());
  Functor::Quantity val2 = reporter.eval( surface.begin() );
  trace.info() <<  "Value with radius 20= "<<val2 << std::endl;

  nbok += ((fabs((double)val2 - 398.0)) < 120) ? 1 : 0;
  nb++;

  trace.endBlock();
  trace.endBlock();

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;

  return nbok == nb;
}


bool testConcepts()
{
  typedef Z3i::KSpace::Surfel Surfel;
  typedef CanonicSCellEmbedder<Z3i::KSpace> Embedder;
  trace.beginBlock("Checking concepts");
  BOOST_CONCEPT_ASSERT(( concepts::CLocalEstimatorFromSurfelFunctor< functors::DummyEstimatorFromSurfels<Surfel,Embedder > >));
  BOOST_CONCEPT_ASSERT(( concepts::CLocalEstimatorFromSurfelFunctor< functors::ElementaryConvolutionNormalVectorEstimator<Surfel,Embedder > >));

#ifdef WITH_CGAL
  BOOST_CONCEPT_ASSERT((  concepts::CLocalEstimatorFromSurfelFunctor< functors::MongeJetFittingNormalVectorEstimator<Surfel,Embedder > >));
  BOOST_CONCEPT_ASSERT((  concepts::CLocalEstimatorFromSurfelFunctor< functors::MongeJetFittingMeanCurvatureEstimator<Surfel,Embedder > >));
  BOOST_CONCEPT_ASSERT((  concepts::CLocalEstimatorFromSurfelFunctor< functors::MongeJetFittingGaussianCurvatureEstimator<Surfel,Embedder > >));
  BOOST_CONCEPT_ASSERT((  concepts::CLocalEstimatorFromSurfelFunctor< functors::LinearLeastSquareFittingNormalVectorEstimator<Surfel,Embedder > >));
#endif

  trace.endBlock();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class LocalEstimatorFromFunctorAdapter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testConcepts() &&  testLocalEstimatorFromFunctorAdapter(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
