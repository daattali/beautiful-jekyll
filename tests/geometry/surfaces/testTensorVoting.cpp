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
 * @file testTensorVoting.cpp
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
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/graph/DistanceBreadthFirstVisitor.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/BasicEstimatorFromSurfelsFunctors.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/TensorVotingFeatureExtraction.h"

#include "DGtal/shapes/implicit/ImplicitHyperCube.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/GaussDigitizer.h"
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
template<typename Shape>
bool testLocalEstimatorFromFunctorAdapter()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing init ..." );

  using namespace Z3i;
 
  typedef GaussDigitizer<Space,Shape> Gauss;

  typedef LightImplicitDigitalSurface<KSpace,Gauss> SurfaceContainer;
  typedef DigitalSurface<SurfaceContainer> Surface;
  typedef typename Surface::Surfel Surfel;


  trace.beginBlock("Creating Surface");
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;

  //Shape
  Shape shape(RealPoint::diagonal(0.0), 6.0 );
  Gauss gauss;
  gauss.attach(shape);
  gauss.init(p1,p2,1.0);

  //Surface
  Surfel bel = Surfaces<KSpace>::findABel( K, gauss, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, gauss, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired
  trace.endBlock();

  trace.beginBlock("Creating  adapters");
  typedef functors::TensorVotingFeatureExtraction<Surfel, CanonicSCellEmbedder<KSpace> > FunctorVoting;

  typedef functors::GaussianKernel ConvFunctor;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorVoting, ConvFunctor> Reporter;

  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
  FunctorVoting estimator(embedder,1);

  ConvFunctor convFunc(1.0);
  Reporter reporter;
  reporter.attach(surface);
  reporter.setParams(l2Metric, estimator , convFunc, 2.0);

  reporter.init(1, surface.begin(), surface.end());

  typename FunctorVoting::Quantity val = reporter.eval( surface.begin());
  trace.info() << "probing at "<< *(surface.begin())<<std::endl;

  trace.info() << "Voting = "<<val <<std::endl;

  trace.endBlock();
  trace.endBlock();

  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;

  return nbok == nb;
}
/**
 *
 */
bool testCube()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing cube ..." );

  using namespace Z3i;
  typedef ImplicitHyperCube<Space> Shape;
  typedef GaussDigitizer<Space,Shape> Gauss;

  typedef LightImplicitDigitalSurface<KSpace,Gauss> SurfaceContainer;
  typedef DigitalSurface<SurfaceContainer> Surface;
  typedef  Surface::Surfel Surfel;


  trace.beginBlock("Creating Surface");
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;

  //Shape
  Shape shape(RealPoint::diagonal(0.0), 6.0 );
  Gauss gauss;
  gauss.attach(shape);
  gauss.init(p1,p2,1.0);

  //Surface
  Surfel bel = Surfaces<KSpace>::findABel( K, gauss, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, gauss, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired
  trace.endBlock();

  trace.beginBlock("Creating  adapters");
  typedef functors::TensorVotingFeatureExtraction<Surfel, CanonicSCellEmbedder<KSpace> > FunctorVoting;

  typedef functors::GaussianKernel ConvFunctor;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorVoting, ConvFunctor> Reporter;

  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
  FunctorVoting estimator(embedder,1);

  ConvFunctor convFunc(1.0);
  Reporter reporter(surface, l2Metric, estimator , convFunc);
  reporter.attach(surface);
  reporter.setParams(l2Metric, estimator , convFunc, 2.0);
  reporter.init(1, surface.begin(),surface.end());
  trace.endBlock();

  trace.beginBlock("Probing ...");
  Z3i::KSpace::Point p(11,-12,1);
  for(Surface::ConstIterator it = surface.begin(), itend = surface.end(); it!= itend; ++it)
    {
      if (K.sKCoords(*it) == p)
        {
          Reporter::Quantity val = reporter.eval( it );
          trace.info() << "probing at "<< *it<<std::endl;
          trace.info() << "Voting = "<<val <<std::endl;
        }
    }
  trace.endBlock();
  trace.endBlock();

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class TensorVotingFeatureExtraction" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testLocalEstimatorFromFunctorAdapter<ImplicitHyperCube<Z3i::Space> >()
    && testLocalEstimatorFromFunctorAdapter<ImplicitBall<Z3i::Space> >()
  && testCube();// && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
