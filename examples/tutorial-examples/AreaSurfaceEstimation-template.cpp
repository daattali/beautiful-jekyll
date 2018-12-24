/// @file tutorial-examples/AreaSurfaceEstimation-template.cpp
/// Shape

#include "DGtal/shapes/parametric/Ball3D.h"

//! [areaSurface-basicIncludes]

/// Shape construction
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"

/// Estimation
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.h"

using namespace DGtal;
//! [areaSurface-basicIncludes]

int main( int argc, char** argv )
{
	const double h = 1;
	const double radiusBall = 12.0;
	const double radiusII = 6;
	const double trueAreaSurface = 4.0*M_PI*radiusBall*radiusBall;
	double areaSurfaceEstimated = 0.0;

	trace.beginBlock( "Make parametric shape..." );
	

	trace.endBlock();

	trace.beginBlock( "Make digital shape..." );

	
	trace.endBlock();
	
	trace.beginBlock( "Make digital surface..." );


	trace.endBlock();

	trace.beginBlock( "Computation with normal estimation ..." );


	trace.endBlock();

	trace.info() << "Area Surface estimated : " << areaSurfaceEstimated << std::endl;
	trace.info() << "True areaSurface : " << trueAreaSurface << std::endl;
	trace.info() << "Ratio : " << areaSurfaceEstimated / trueAreaSurface << std::endl;

	return 0;
}
