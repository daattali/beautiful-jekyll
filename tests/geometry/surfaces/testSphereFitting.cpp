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
 * @file testSphereFitting.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/10/07
 *
 * Functions for testing class SphereFitting.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/graph/DistanceBreadthFirstVisitor.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/BasicEstimatorFromSurfelsFunctors.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/SphereFittingEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/ElementaryConvolutionNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/EstimatorCache.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LocalEstimatorFromFunctorAdapter.
///////////////////////////////////////////////////////////////////////////////


/**
 * Example of a test. To be completed.
 *
 */
bool testFitting()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing init ..." );

  using namespace Z3i;

  trace.beginBlock("Creating Surface");
  Point p1( -20, -20, -20 );
  Point p2( 20, 20, 20 );
   
  ImplicitBall<Z3i::Space> shape( RealPoint(6.0,0,0), 4);
  typedef GaussDigitizer<Z3i::Space, ImplicitBall<Z3i::Space> > Gauss;
  Gauss gauss;
  gauss.attach(shape);
  gauss.init(p1, p2, 1);
  
  typedef LightImplicitDigitalSurface<KSpace,  Gauss > SurfaceContainer;
  typedef DigitalSurface<SurfaceContainer> Surface;
  typedef Surface::Surfel Surfel;


  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;
  Surfel bel = Surfaces<KSpace>::findABel( K, gauss, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, gauss, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired
  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
  trace.endBlock();

  trace.beginBlock("Normal vector field computation");
  typedef functors::ElementaryConvolutionNormalVectorEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorNormal;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric,
                                                 FunctorNormal,
                                                 DGtal::functors::GaussianKernel> ReporterNormal;
  typedef EstimatorCache<ReporterNormal> NormalCache;

  //estimator
  DGtal::functors::GaussianKernel gaussKernelFunc(5.0);
  FunctorNormal functorNormal(embedder, 1.0);
  ReporterNormal reporterNormal;
  reporterNormal.attach(surface);
  reporterNormal.setParams(l2Metric, functorNormal, gaussKernelFunc, 5.0);

  //caching normal field
  NormalCache normalCache(reporterNormal);
  normalCache.init( 1, surface.begin(), surface.end());
  trace.info() << "Normal vector field cached... "<< normalCache << std::endl;
  trace.endBlock();

  trace.beginBlock("Creating  sphere fitting adapter from normal vector field");
  typedef functors::SphereFittingEstimator<Surfel, CanonicSCellEmbedder<KSpace> , NormalCache> Functor;
  typedef functors::ConstValue< double > ConvFunctor;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, Functor, ConvFunctor> Reporter;

  Functor fitter(embedder,1.0, 5.0, normalCache);
  ConvFunctor convFunc(1.0);
  Reporter reporter;
  reporter.attach(surface);
  reporter.setParams(l2Metric, fitter , convFunc, 15.0);
  
  reporter.init(1, surface.begin(), surface.end());
  for(Surface::ConstIterator it = surface.begin(), ite=surface.end(); it!=ite; ++it)
    {
      Functor::Quantity val = reporter.eval( it );
      trace.info() << "Fitting = "<<val.center <<" rad="<<val.radius<<std::endl;
    }
  trace.endBlock();


  trace.endBlock();

  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SphereFitting" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testFitting(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
