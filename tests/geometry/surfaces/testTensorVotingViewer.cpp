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

#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

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
bool testLocalEstimatorFromFunctorAdapter(int argc, char **argv)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing init ..." );

  using namespace Z3i;
 
  typedef GaussDigitizer<Space,Shape> Gauss;

  typedef LightImplicitDigitalSurface<KSpace,Gauss> SurfaceContainer;
  typedef DigitalSurface<SurfaceContainer> Surface;
  //typedef Surface::SurfelConstIterator ConstIterator;
  //typedef Surface::Tracker Tracker;
  typedef typename Surface::Surfel Surfel;


  trace.beginBlock("Creating Surface");
  Point p1( -100, -100, -100 );
  Point p2( 100, 100, 100 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;

  //Shape
  Shape shape(RealPoint::diagonal(0.0), 30.0 );
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

  ConvFunctor convFunc(4.0);
  Reporter reporter;
  reporter.attach(surface);
  reporter.setParams(l2Metric, estimator , convFunc, 5.0);

  reporter.init(1, surface.begin() , surface.end());

  std::vector<double> values;
  reporter.eval( surface.begin(), surface.end(), std::back_insert_iterator<std::vector<double> >(values));

  double maxval = *std::max_element(values.begin(), values.end());
  double minval = *std::min_element(values.begin(), values.end());
  trace.info() << "Min/max= "<< minval<<"/"<<maxval<<std::endl;
  QApplication application( argc, argv );
  typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
  Viewer viewer( K );
  viewer.setWindowTitle("Features from Tensor Voting");
  viewer.show();

  typedef GradientColorMap< double > Gradient;
  Gradient cmap_grad( minval, maxval );
  cmap_grad.addColor( Color( 50, 50, 255 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 10 ) );


  viewer << SetMode3D((*(surface.begin())).className(), "Basic" );
  unsigned int i=0;
  
  for(typename Surface::ConstIterator it = surface.begin(), itend=surface.end();
      it!= itend;
      ++it, ++i)
    {
      viewer << CustomColors3D( Color::Black, cmap_grad( values[ i ] ))
             <<  *it ;    
    }
  
  
  viewer << Viewer3D<>::updateDisplay;
  
  trace.endBlock();
  application.exec();

  return true;
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

  bool res = testLocalEstimatorFromFunctorAdapter<ImplicitHyperCube<Z3i::Space> >(argc,argv)
    && testLocalEstimatorFromFunctorAdapter<ImplicitBall<Z3i::Space> >(argc,argv);
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
