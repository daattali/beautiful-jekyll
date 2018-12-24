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
 * @file geometry/surfaces/exampleIntegralInvariantCurvature3D.cpp
 * @ingroup Examples
 * @author Jérémy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/12/17
 *
 * An example file named exampleIntegralInvariantCurvature3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

// Shape construction
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"

/// Estimator
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantVolumeEstimator.h"

// Drawing
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    if ( argc != 4 )
    {
        trace.error() << "Usage: " << argv[0]
                               << " <fileName.vol> <threshold> <radius>" << std::endl;
        trace.error() << "Example : "<< argv[0] << " Al.150.vol 0 7" << std::endl;
        return 0;
    }

    trace.beginBlock ( "Example IntegralInvariantCurvature3D" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    double h = 1.0;
    unsigned int threshold = std::atoi( argv[ 2 ] );

    /// Construction of the shape from vol file
    typedef ImageSelector< Z3i::Domain, bool >::Type Image;
    typedef functors::SimpleThresholdForegroundPredicate< Image > ImagePredicate;
    typedef LightImplicitDigitalSurface< Z3i::KSpace, ImagePredicate > MyLightImplicitDigitalSurface;
    typedef DigitalSurface< MyLightImplicitDigitalSurface > MyDigitalSurface;

    std::string filename = argv[1];
    Image image = VolReader<Image>::importVol( filename );
    ImagePredicate predicate = ImagePredicate( image, threshold );

    Z3i::Domain domain = image.domain();

    Z3i::KSpace KSpaceShape;

    bool space_ok = KSpaceShape.init( domain.lowerBound(), domain.upperBound(), true );
    if (!space_ok)
    {
      trace.error() << "Error in the Khalimsky space construction."<<std::endl;
      return 2;
    }

    SurfelAdjacency< Z3i::KSpace::dimension > SAdj( true );
    Z3i::KSpace::Surfel bel = Surfaces< Z3i::KSpace >::findABel( KSpaceShape, predicate, 100000 );
    MyLightImplicitDigitalSurface LightImplDigSurf( KSpaceShape, predicate, SAdj, bel );
    MyDigitalSurface digSurf( LightImplDigSurf );

    typedef DepthFirstVisitor< MyDigitalSurface > Visitor;
    typedef GraphVisitorRange< Visitor > VisitorRange;
    typedef VisitorRange::ConstIterator SurfelConstIterator;

    VisitorRange range( new Visitor( digSurf, *digSurf.begin() ) );
    SurfelConstIterator abegin = range.begin();
    SurfelConstIterator aend = range.end();

    /// Integral Invariant stuff
    //! [IntegralInvariantUsage]
    double radius = std::atof(argv[3]);

    typedef functors::IIMeanCurvature3DFunctor<Z3i::Space> MyIICurvatureFunctor;
    typedef IntegralInvariantVolumeEstimator< Z3i::KSpace, ImagePredicate, MyIICurvatureFunctor > MyIICurvatureEstimator;

    // For computing Gaussian curvature instead, for example, change the two typedef above by :
    // typedef functors::IIGaussianCurvature3DFunctor<Z3i::Space> MyIICurvatureFunctor;
    // typedef IntegralInvariantCovarianceEstimator< Z3i::KSpace, ImagePredicate, MyIICurvatureFunctor > MyIICurvatureEstimator;
    // and it's done. The following part is exactly the same.

    typedef MyIICurvatureFunctor::Value Value;

    MyIICurvatureFunctor curvatureFunctor; // Functor used to convert volume -> curvature
    curvatureFunctor.init( h, radius ); // Initialisation for a grid step and a given Euclidean radius of convolution kernel

    MyIICurvatureEstimator curvatureEstimator( curvatureFunctor );
    curvatureEstimator.attach( KSpaceShape, predicate ); // Setting a KSpace and a predicate on the object to evaluate
    curvatureEstimator.setParams( radius / h ); // Setting the digital radius of the convolution kernel
    curvatureEstimator.init( h, abegin, aend ); // Initialisation for a given h, and a range of surfels

    std::vector< Value > results;
    std::back_insert_iterator< std::vector< Value > > resultsIt( results ); // output iterator for results of Integral Invariant curvature computation
    curvatureEstimator.eval( abegin, aend, resultsIt ); // Computation
    //! [IntegralInvariantUsage]

    /// Drawing results
    Value min = numeric_limits < Value >::max();
    Value max = numeric_limits < Value >::min();
    for ( unsigned int i = 0; i < results.size(); ++i )
    {
        if ( results[ i ] < min )
        {
            min = results[ i ];
        }
        else if ( results[ i ] > max )
        {
            max = results[ i ];
        }
    }

    QApplication application( argc, argv );
    typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
    Viewer viewer( KSpaceShape );
    viewer.setWindowTitle("example Integral Invariant 3D");
    viewer.show();

    typedef GradientColorMap< Value > Gradient;
    Gradient cmap_grad( min, max );
    cmap_grad.addColor( Color( 50, 50, 255 ) );
    cmap_grad.addColor( Color( 255, 0, 0 ) );
    cmap_grad.addColor( Color( 255, 255, 10 ) );

    VisitorRange range2( new Visitor( digSurf, *digSurf.begin() ) );
    abegin = range2.begin();

    Z3i::KSpace::Cell dummy_cell;
    viewer << SetMode3D( dummy_cell.className(), "Basic" );

    for ( unsigned int i = 0; i < results.size(); ++i )
    {
        viewer << CustomColors3D( Color::Black, cmap_grad( results[ i ] ))
               << KSpaceShape.unsigns( *abegin );
        ++abegin;
    }

    viewer << Viewer3D<>::updateDisplay;

    trace.endBlock();
    return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
