/**
  * This program is free software : you can redistribuate it and/or modify
  * it under the terms of the GNU Lesser General Public License as
  * published by the Free Software Foundation, either version 3 of the
  * License, or (at you option) any later version.
  *
  * This program is distributed int the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, set <http://www.gnu.org/license/>.
 **/

/// @file dec/exampleHeatLaplace.cpp
/**
   Example of the Heat Laplace Operator.
   @see \ref secHowToHeatLaplace
   \example dec/exampleHeatLaplace.cpp
**/

////////// INCLUDES /////////

#include <DGtal/helpers/StdDefs.h>

#include <DGtal/topology/DigitalSurface.h>
#include <DGtal/topology/DigitalSetBoundary.h>
#include <DGtal/topology/SetOfSurfels.h>
#include <DGtal/topology/LightImplicitDigitalSurface.h>

#include <DGtal/math/linalg/EigenSupport.h>

#include <DGtal/dec/DiscreteExteriorCalculus.h>
#include <DGtal/dec/DiscreteExteriorCalculusFactory.h>
#include <DGtal/dec/DiscreteExteriorCalculusSolver.h>
#include <DGtal/dec/VectorField.h>

#include <DGtal/geometry/surfaces/estimation/LocalEstimatorFromSurfelFunctorAdapter.h>
#include <DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h>
#include <DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.h>

#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/colormaps/ColorBrightnessColorMap.h>
#include <DGtal/io/viewers/Viewer3D.h>
#include <DGtal/io/colormaps/TickedColorMap.h>
#include "DGtal/io/readers/GenericReader.h"

#include <DGtal/images/IntervalForegroundPredicate.h>
#include <DGtal/images/imagesSetsUtils/SetFromImage.h>

#include <DGtal/shapes/parametric/Ball3D.h>
#include <DGtal/shapes/Shapes.h>
#include <DGtal/shapes/GaussDigitizer.h>

struct Options
{
  double h;
  double normal_radius;
  double convolution_radius;
};

////////// NAMESPACES /////////

using namespace DGtal;
using namespace Eigen;

////////// TYPEDEFS /////////

typedef Z3i::Space Space;
typedef Z3i::RealVector RealVector;
typedef Z3i::RealPoint RealPoint;
typedef Z3i::Point Point;

////////// UTILITY FUNCTIONS /////////

RealPoint cartesian_to_spherical( const RealPoint& a )
{
  return RealPoint( a.norm(), atan2( a[1], a[0] ), acos( a[2] ) );
}

//! [heat_functions]
std::function<double(const RealPoint&)> xx_function =
  [] ( const RealPoint& p )
{
  const RealPoint p_sphere = p / p.norm();
  return p_sphere[0] * p_sphere[0];
};

std::function<double(const RealPoint&)> xx_derivative =
  [] ( const RealPoint& p )
{
  const RealPoint p_s = cartesian_to_spherical( p );
  return 2. * cos( p_s[1] ) * cos( p_s[1] ) * ( 2 * cos( p_s[2] ) * cos( p_s[2] ) - sin( p_s[2] ) * sin( p_s[2] ) )
    + 2. * ( sin( p_s[1] ) * sin( p_s[1] ) - cos( p_s[1] ) * cos( p_s[1] ) );
};
//! [heat_functions]

template <typename Shape>
void convergence(const Options& options, Shape& shape,
        const std::function< double(const RealPoint&) >& input_function,
        const std::function< double(const RealPoint&) >& result_function)
{
  trace.beginBlock("Laplacian 3D");

  trace.beginBlock("Extracting Digital Surface");

  typedef Z3i::KSpace KSpace;

//! [surface_extract]
  typedef GaussDigitizer<Z3i::Space, Shape> Digitizer;

  Digitizer digitizer;
  digitizer.attach(shape);
  digitizer.init(shape.getLowerBound() + Z3i::Vector(-1,-1,-1), shape.getUpperBound() + Z3i::Vector(1,1,1), options.h);

  Z3i::Domain domain = digitizer.getDomain();

  Z3i::KSpace kspace;
  bool ok = kspace.init(domain.lowerBound(), domain.upperBound(), true);
  if( !ok ) std::cerr << "KSpace init failed" << std::endl;

  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;

  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  MySetOfSurfels theSetOfSurfels( kspace, surfAdj );
  Surfaces<KSpace>::sMakeBoundary( theSetOfSurfels.surfelSet(),
                   kspace, digitizer,
                   domain.lowerBound(),
                   domain.upperBound() );
  MyDigitalSurface digSurf( theSetOfSurfels );
//! [surface_extract]
  trace.info() << "Digital Surface has " << digSurf.size() << " surfels." << std::endl;

  trace.endBlock();

  trace.beginBlock("Initializing Normal Functor");
//! [normal_estimation]
  typedef CanonicSCellEmbedder<KSpace> CanonicSCellEmbedder;
  CanonicSCellEmbedder canonicSCellEmbedder(kspace);

  typedef functors::IINormalDirectionFunctor<Space> MyIINormalFunctor;
  typedef IntegralInvariantCovarianceEstimator<KSpace, Digitizer, MyIINormalFunctor> MyIINormalEstimator;

  const double radius = options.normal_radius * pow(options.h, 1. / 3.);

  MyIINormalFunctor normalFunctor;
  normalFunctor.init(options.h, radius);

  MyIINormalEstimator normalEstimator(normalFunctor);
  normalEstimator.attach(kspace, digitizer);
  normalEstimator.setParams(radius / options.h);

  normalEstimator.init(options.h, digSurf.begin(), digSurf.end());
//! [normal_estimation]
  trace.endBlock();

  trace.beginBlock("Initializing DEC");
//! [init_dec]
  typedef DiscreteExteriorCalculus<2, 3, EigenLinearAlgebraBackend> Calculus;
  typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;

  const Calculus calculus = CalculusFactory::createFromNSCells<2>(digSurf.begin(), digSurf.end(), normalEstimator, options.h);
//! [init_dec]
  trace.info() << calculus << std::endl;

  trace.endBlock();
  trace.beginBlock("Computing the input function");
//! [input_function]
  Calculus::DualForm0 input_func(calculus);

  for(auto itb = digSurf.begin(), ite = digSurf.end(); itb != ite; itb++)
  {
    const Calculus::Index i_calc = calculus.getCellIndex( kspace.unsigns( *itb ) );
    input_func.myContainer( i_calc ) = input_function( options.h * canonicSCellEmbedder( *itb ) );
  }
//! [input_function]
  trace.endBlock();

  trace.beginBlock("Computing the Laplace operator");
//! [laplace_operator]
  const double t = options.convolution_radius * pow(options.h, 2. / 3.);
  const double K = log( - log1p( t ) ) + 2.;
  const Calculus::DualIdentity0 laplace = calculus.heatLaplace<DUAL>(options.h, t, K);
//! [laplace_operator]
  trace.info() << "Matrix has " << ((double)laplace.myContainer.nonZeros() / (double)laplace.myContainer.size() * 100.) << "% of non-zeros elements." << std::endl;
  trace.endBlock();

//! [operator_result]
  const Eigen::VectorXd laplace_result = (laplace * input_func).myContainer;
//! [operator_result]
  Eigen::VectorXd error( digSurf.size() );
  Eigen::VectorXd real_laplacian_values( digSurf.size() );
  Eigen::VectorXd estimated_laplacian_values( digSurf.size() );

  int i = 0;
  for(auto itb = digSurf.begin(), ite = digSurf.end(); itb != ite; itb++)
  {
    const Calculus::Index i_calc = calculus.getCellIndex( kspace.unsigns( *itb ) );

    const RealPoint p = options.h * canonicSCellEmbedder( *itb );
    const RealPoint p_normalized = p / p.norm();
    const RealPoint p_s = cartesian_to_spherical( p );

    const double real_laplacian_value = result_function( p_normalized );
    const double estimated_laplacian_value = laplace_result( i_calc );

    estimated_laplacian_values(i) = estimated_laplacian_value;
    real_laplacian_values(i) = real_laplacian_value;

    error(i) = estimated_laplacian_value - real_laplacian_value;

    ++i;
  }

  trace.info() << "Estimated Laplacian Range : " << estimated_laplacian_values.minCoeff() << " / " << estimated_laplacian_values.maxCoeff() << std::endl;
  trace.info() << "Real Laplacian Range : " << real_laplacian_values.minCoeff() << " / " << real_laplacian_values.maxCoeff() << std::endl;

  trace.info() << "h = " << options.h << " t = " << t << " K = " << K << std::endl;
  trace.info() << "Mean error = " << error.array().abs().mean() << " max error = " << error.array().abs().maxCoeff() << std::endl;

  trace.endBlock();
}

int main()
{
  Options options;

  options.h = 0.1;
  options.normal_radius = 2.0;
  options.convolution_radius = 0.1;

  typedef Ball3D<Z3i::Space> Ball;
  Ball ball(Point(0.0,0.0,0.0), 1.0);

  std::function<double(const RealPoint&, const RealPoint&)> l2_distance =
      [](const RealPoint& a, const RealPoint& b) { return (a - b).norm(); };

  convergence<Ball>(options, ball, xx_function, xx_derivative);

  return 0;
}
