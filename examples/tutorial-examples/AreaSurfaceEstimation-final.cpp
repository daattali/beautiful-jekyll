/// @file tutorial-examples/AreaSurfaceEstimation-final.cpp
/// Shape
/**
 Example of tutorial 4: Surface area estimation
 @see @ref tutoAreaSurface
 \example tutorial-examples/AreaSurfaceEstimation-final.cpp
**/

#include "DGtal/shapes/parametric/Ball3D.h"

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

int main( int argc, char** argv )
{
	const double h = 1;
	const double radiusBall = 12.0;
	const double radiusII = 6;
	const double trueAreaSurface = 4.0*M_PI*radiusBall*radiusBall;

	trace.beginBlock( "Make parametric shape..." );

	typedef Ball3D< Z3i::Space > Shape;

	Z3i::RealPoint center( 0.0, 0.0, 0.0 );
	Shape ball( center, radiusBall );

	trace.endBlock();

	trace.beginBlock( "Make digital shape..." );

	typedef GaussDigitizer< Z3i::Space, Shape > DigitalShape;
	typedef DigitalShape::Domain Domain;

	DigitalShape digitalBall;
	digitalBall.attach( ball );
	digitalBall.init( ball.getLowerBound() - Z3i::RealPoint( 1.0, 1.0, 1.0 ), 
					  ball.getUpperBound() + Z3i::RealPoint( 1.0, 1.0, 1.0 ),
					  h );
	Domain domain = digitalBall.getDomain();
	Z3i::KSpace kspace;
	kspace.init( domain.lowerBound(), domain.upperBound(), true );

	trace.endBlock();

	trace.beginBlock( "Make digital surface..." );

	typedef LightImplicitDigitalSurface< Z3i::KSpace, DigitalShape > LightDigitalSurface;
	typedef DigitalSurface< LightDigitalSurface > DigitalSurface;
	typedef DepthFirstVisitor< DigitalSurface > DepthFirstVisitor;
	typedef GraphVisitorRange< DepthFirstVisitor > GraphVisitorRange;
	typedef GraphVisitorRange::ConstIterator SurfelConstIterator;
	typedef Z3i::KSpace::Surfel Surfel;

	Surfel bel = Surfaces< Z3i::KSpace >::findABel( kspace, digitalBall, 500 );
	SurfelAdjacency< Z3i::KSpace::dimension > surfelAdjacency( true );
	LightDigitalSurface lightDigitalSurface( kspace, digitalBall, surfelAdjacency, bel );
	DigitalSurface digitalSurface( lightDigitalSurface );

	GraphVisitorRange graphVisitorRange( new DepthFirstVisitor( digitalSurface, *digitalSurface.begin() ) );
	SurfelConstIterator sbegin = graphVisitorRange.begin();
    SurfelConstIterator send = graphVisitorRange.end();
    std::vector< Surfel > v_border;
    while( sbegin != send )
    {
    	v_border.push_back( *sbegin );
    	++sbegin;
    }

	trace.endBlock();

	trace.beginBlock( "Computation with normal estimation ..." );

	typedef IIGeometricFunctors::IINormalDirectionFunctor< Z3i::Space > NormalFunctor;
	typedef IntegralInvariantCovarianceEstimator< Z3i::KSpace, DigitalShape, NormalFunctor > IINormalEstimator;

	NormalFunctor normalFunctor;
	IINormalEstimator normalEstimator( normalFunctor );
	normalEstimator.attach( kspace, digitalBall );
	normalEstimator.setParams( radiusII / h );
	normalEstimator.init( h, v_border.begin(), v_border.end() );

	double areaSurfaceEstimated = 0.0;

	for( unsigned int i_position = 0; i_position < v_border.size(); ++i_position )
	{
		Z3i::RealPoint normalEstimated = normalEstimator.eval( &(v_border[i_position]) );
		Z3i::RealPoint normalSurfel = kspace.sKCoords( kspace.sDirectIncident( v_border[i_position], kspace.sOrthDir( v_border[i_position] ))) - kspace.sKCoords( v_border[i_position] ); 
		normalEstimated = normalEstimated.getNormalized();
		areaSurfaceEstimated += std::abs( normalEstimated.dot( normalSurfel )) * h * h;
	}

	trace.endBlock();

	trace.info() << "Area Surface estimated : " << areaSurfaceEstimated << std::endl;
	trace.info() << "True areaSurface : " << trueAreaSurface << std::endl;
	trace.info() << "Ratio : " << areaSurfaceEstimated / trueAreaSurface << std::endl;

	return 0;
}
