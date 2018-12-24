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
 * @file testSphericalHoughNormalVectorEstimator.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2016/03/14
 *
 * Functions for testing class SphericalHoughNormalVectorEstimator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/implicit/ImplicitHyperCube.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/base/BasicFunctors.h"

#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/SphericalHoughNormalVectorEstimator.h"

#ifdef WITH_VISU3D_QGLVIEWER
#include "DGtal/io/viewers/Viewer3D.h"
#endif
#include "DGtal/io/boards/Board3D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SphericalHoughNormalVectorEstimator.
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing SphericalHoughNormalVectorEstimator" )
{
  typedef ImplicitBall<Space> Shape;
  typedef GaussDigitizer<Space,Shape> Gauss;
  
  typedef LightImplicitDigitalSurface<KSpace,Gauss> SurfaceContainer;
  typedef DigitalSurface<SurfaceContainer> Surface;
  typedef Surface::Surfel Surfel;
  
  
  Point p1( -50, -50, -50 );
  Point p2( 50, 50, 50 );
  KSpace K;
  REQUIRE( K.init( p1, p2, true ) );
  

  //Shape
  Shape shape(RealPoint::diagonal(0.0), 10.0 );
  Gauss gauss;
  gauss.attach(shape);
  gauss.init(p1,p2,1.0);
  
  //Surface
  Surfel bel = Surfaces<KSpace>::findABel( K, gauss, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer( K, gauss, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired

  
  typedef functors::SphericalHoughNormalVectorEstimator<Surfel, CanonicSCellEmbedder<KSpace> > SphericalHough;
  typedef functors::ConstValue<double> ConstFunctor;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, SphericalHough, ConstFunctor> Reporter;
  
  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
  SphericalHough estimator(embedder,1.0 , 0.001, 1000 , 10, 1);
  
  ConstFunctor constFunc(1.0);
  Reporter reporter(surface, l2Metric, estimator , constFunc);
  reporter.attach(surface);
  reporter.setParams(l2Metric, estimator , constFunc, 10.0);
  reporter.init(1, surface.begin(),surface.end());

  REQUIRE( reporter.isValid() );
  
  typedef  Reporter::Quantity Quantity;
  
  Quantity result = reporter.eval( surface.begin() );
  trace.info() << "Result at begin = "<< result <<std::endl;
 
  //true normal (implicitBall)
  RealPoint res = embedder( *(surface.begin()) ).getNormalized();
  trace.info() << "Expecting  = "<< res <<std::endl;
  
  REQUIRE( std::abs(result.dot(res)) > 0.9 );
  
  
#ifdef WITH_VISU3D_QGLVIEWER_TESTS
  int argc=0;
  char **argv;
  QApplication application(argc,argv);
  Viewer3D<Z3i::Space, KSpace> viewer(K);
  viewer.show();
  for(Surface::ConstIterator it = surface.begin(), itend=surface.end(); it != itend ;
      ++it)
  {
    Quantity normal = reporter.eval( it );
    viewer << CustomColors3D( DGtal::Color(static_cast<unsigned char>(255*abs(normal[0])),
                                           static_cast<unsigned char>(255*abs(normal[1])),
                                           static_cast<unsigned char>(255*abs(normal[2]))),
                              DGtal::Color(static_cast<unsigned char>(255*abs(normal[0])),
                                           static_cast<unsigned char>(255*abs(normal[1])),
                                           static_cast<unsigned char>(255*abs(normal[2]))));

    viewer << K.unsigns(*it) ;
    
    Point center = K.sCoords ( *it );
    }
  viewer<< Viewer3D<>::updateDisplay;
  application.exec();
#endif
}

/** @ingroup Tests **/
