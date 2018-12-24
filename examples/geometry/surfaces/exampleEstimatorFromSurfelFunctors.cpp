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
 * @file geometry/surfaces/exampleEstimatorFromSurfelFunctors.cpp
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/28
 *
 * Header file for module LocalEstimatorFromSurfelFunctorAdapter.cpp
 *
 * This file is part of the DGtal library.
 */
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

// Shape constructors
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/shapes/Shapes.h"

#include "DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h"
#ifdef WITH_CGAL
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingGaussianCurvatureEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingMeanCurvatureEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/MongeJetFittingNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/LinearLeastSquareFittingNormalVectorEstimator.h"
#endif
#include "DGtal/geometry/surfaces/estimation/estimationFunctors/ElementaryConvolutionNormalVectorEstimator.h"
#include "DGtal/base/BasicFunctors.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

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


int main(  )
{
  //! [SurfelFunctorsInit]
  using namespace Z3i;
  typedef ImplicitDigitalEllipse3<Point> ImplicitDigitalEllipse;
  typedef LightImplicitDigitalSurface<KSpace,ImplicitDigitalEllipse> SurfaceContainer;
  typedef DigitalSurface< SurfaceContainer > Surface;
  typedef SurfaceContainer::Surfel Surfel;

  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  K.init( p1, p2, true );
  ImplicitDigitalEllipse ellipse( 6.0, 4.5, 3.4 );
  Surfel bel = Surfaces<KSpace>::findABel( K, ellipse, 10000 );
  SurfaceContainer* surfaceContainer = new SurfaceContainer
    ( K, ellipse, SurfelAdjacency<KSpace::dimension>( true ), bel );
  Surface surface( surfaceContainer ); // acquired
  //! [SurfelFunctorsInit]


  //! [SurfelFunctorsType]
#ifdef WITH_CGAL
  typedef DGtal::functors::MongeJetFittingGaussianCurvatureEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorGaussian;
  typedef functors::MongeJetFittingMeanCurvatureEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorMean;
  typedef functors::MongeJetFittingNormalVectorEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorNormal;
  typedef functors::LinearLeastSquareFittingNormalVectorEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorNormalLeast;

  //constant convolution functor
  typedef functors::ConstValue<double> ConstFunctor;

  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorGaussian, ConstFunctor> ReporterK;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorMean, ConstFunctor> ReporterH;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorNormal, ConstFunctor> ReporterNormal;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric, FunctorNormalLeast, ConstFunctor> ReporterNormalLeast;
#endif

  ///For Elmentary convolution, we specify a Gaussian convolution
  ///kernel from the BasicFunctors.h file
  typedef functors::ElementaryConvolutionNormalVectorEstimator<Surfel, CanonicSCellEmbedder<KSpace> > FunctorNormalElem;
  typedef LocalEstimatorFromSurfelFunctorAdapter<SurfaceContainer, Z3i::L2Metric,
                                                 FunctorNormalElem, DGtal::functors::GaussianKernel> ReporterNormalElem;
  //! [SurfelFunctorsType]


  //! [SurfelFunctorsInstances]
  CanonicSCellEmbedder<KSpace> embedder(surface.container().space());
#ifdef WITH_CGAL
  ///Creating functors for h=1.0
  FunctorGaussian estimatorK(embedder,1.0);
  FunctorMean estimatorH(embedder, 1.0);
  FunctorNormal estimatorN(embedder,1.0);
  FunctorNormalLeast estimatorL(embedder,1.0);

  ConstFunctor constFunctor(1.0);

  ReporterK reporterK;
  ReporterH reporterH;
  ReporterNormal reporterN;
  ReporterNormalLeast reporterL;
#endif

  FunctorNormalElem estimatorNormalElem(embedder,1.0);
  ///sigma = 2.0 for the gaussian smoothing
  DGtal::functors::GaussianKernel gaussian(2.0);
  ReporterNormalElem reporterElem(surface, l2Metric,
                                  estimatorNormalElem, gaussian);
  //! [SurfelFunctorsInstances]

  //! [SurfelFunctorsEstim]
#ifdef WITH_CGAL
  reporterK.attach(surface);
  reporterH.attach(surface);
  reporterN.attach(surface);
  reporterL.attach(surface);

  reporterK.init(1, surface.begin(), surface.end());
  reporterH.init(1, surface.begin(), surface.end());
  reporterN.init(1, surface.begin(), surface.end());
  reporterL.init(1, surface.begin(), surface.end());

  reporterK.setParams(l2Metric, estimatorK, constFunctor, 5.0);
  reporterH.setParams(l2Metric, estimatorH, constFunctor, 5.0);
  reporterN.setParams(l2Metric, estimatorN, constFunctor, 5.0);
  reporterL.setParams(l2Metric, estimatorL, constFunctor, 5.0);

  FunctorGaussian::Quantity valK = reporterK.eval( surface.begin());
  FunctorMean::Quantity valH = reporterH.eval( surface.begin());
  FunctorNormal::Quantity valN = reporterN.eval( surface.begin());
  FunctorNormalLeast::Quantity valL = reporterL.eval( surface.begin());
#endif
  
  reporterElem.attach(surface);
  reporterElem.setParams(l2Metric,
                         estimatorNormalElem, gaussian, 5.0);
  reporterElem.init(1.0, surface.begin(), surface.end());
  FunctorNormalElem::Quantity valElem = reporterElem.eval( surface.begin());

#ifdef WITH_CGAL
  trace.info() << "Gaussian = "<<valK <<std::endl;
  trace.info() << "Mean = "<<valH<< std::endl;
  trace.info() << "Normal Vector (from Monge form) = "<<valN<< std::endl;
  trace.info() << "Normal Vector (linear least square) = "<<valL<< std::endl;
#endif
  trace.info() << "Normal Vector (Elementary conv) = "<<valElem<< std::endl;
  //! [SurfelFunctorsEstim]

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
