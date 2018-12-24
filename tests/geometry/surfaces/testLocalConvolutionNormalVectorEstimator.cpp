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
 * @file testLocalConvolutionNormalVectorEstimator.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/03
 *
 * Functions for testing class LocalConvolutionNormalVectorEstimator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigTest.h"
#include "DGtal/base/Common.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/ImplicitDigitalSurface.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/ExplicitDigitalSurface.h"
#include "DGtal/topology/LightExplicitDigitalSurface.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/topology/helpers/FrontierPredicate.h"
#include "DGtal/topology/helpers/BoundaryPredicate.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
#include "DGtal/graph/CUndirectedSimpleGraph.h"

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"

#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"


#include "DGtal/geometry/surfaces/estimation/BasicConvolutionWeights.h"
#include "DGtal/geometry/surfaces/estimation/LocalConvolutionNormalVectorEstimator.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LocalConvolutionNormalVectorEstimator.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testLocalConvolutionNormalVectorEstimator ( int argc, char**argv )
{
    trace.beginBlock ( "Testing convolution neighborhood ..." );

    QApplication application ( argc,argv );

    std::string filename = testPath + "samples/cat10.vol";

    typedef ImageSelector < Z3i::Domain, int>::Type Image;
    Image image = VolReader<Image>::importVol ( filename );
    trace.info() <<image<<std::endl;
    DigitalSet set3d ( image.domain() );
    SetFromImage<DigitalSet>::append<Image> ( set3d, image,
            0,256 );

    KSpace ks;
    bool space_ok = ks.init ( image.domain().lowerBound(),
                              image.domain().upperBound(), true );
    if ( !space_ok )
    {
        trace.error() << "Error in the Khamisky space construction."<<std::endl;
        return true; //2; (return a bool !!!)
    }
    trace.endBlock();
    typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
    MySurfelAdjacency surfAdj ( true ); // interior in all directions.

    trace.beginBlock ( "Set up digital surface." );
    typedef LightImplicitDigitalSurface<KSpace, DigitalSet >
      MyDigitalSurfaceContainer;
    typedef DigitalSurface<MyDigitalSurfaceContainer> MyDigitalSurface;
    SCell bel = Surfaces<KSpace>::findABel ( ks, set3d, 100000 );
    MyDigitalSurfaceContainer* ptrSurfContainer =
        new MyDigitalSurfaceContainer ( ks, set3d, surfAdj, bel );
    MyDigitalSurface digSurf ( ptrSurfContainer ); // acquired

    MyDigitalSurface::ConstIterator it = digSurf.begin();


    //Convolution kernel
    deprecated::ConstantConvolutionWeights< MyDigitalSurface::Size > kernel;

    //Estimator definition
    typedef deprecated::LocalConvolutionNormalVectorEstimator<MyDigitalSurface,
                                                  deprecated::ConstantConvolutionWeights< MyDigitalSurface::Size > > MyEstimator;
    MyEstimator myNormalEstimator ( digSurf, kernel );

    myNormalEstimator.init ( 1.0, 5 );

    MyEstimator::Quantity res = myNormalEstimator.eval ( it );
    trace.info() << "Normal vector at begin() : "<< res << std::endl;

    DGtal::Viewer3D<Space,KSpace> viewer(ks);
    viewer.show();

    DGtal::Color lineColorSave = viewer.getLineColor();
    viewer.setLineColor( DGtal::Color ( 20,200,20 ));
    for ( MyDigitalSurface::ConstIterator itbis = digSurf.begin(),itend=digSurf.end();
            itbis!=itend; ++itbis )
    {
        viewer << ks.unsigns ( *itbis );

        Point center = ks.sCoords ( *itbis );
        MyEstimator::Quantity normal = myNormalEstimator.eval ( itbis );

        viewer.addLine ( center,
                         DGtal::Z3i::RealPoint(center[0]-3*normal[0],
                 center[1]-3*normal[1],
                 center[2]-3*normal[2]) );
    }
    viewer.setLineColor( lineColorSave);
    viewer<< Viewer3D<>::updateDisplay;

    //Convolution kernel
    deprecated::GaussianConvolutionWeights< MyDigitalSurface::Size > Gkernel ( 14.0 );

    //Estimator definition
    typedef deprecated::LocalConvolutionNormalVectorEstimator<MyDigitalSurface,
                                                              deprecated::GaussianConvolutionWeights< MyDigitalSurface::Size > > MyEstimatorGaussian;
    MyEstimatorGaussian myNormalEstimatorG ( digSurf, Gkernel );

    myNormalEstimatorG.init ( 1.0, 15 );

    MyEstimatorGaussian::Quantity res2 = myNormalEstimatorG.eval ( it );
    trace.info() << "Normal vector at begin() : "<< res2 << std::endl;

    viewer<< CustomColors3D ( Color ( 200, 0, 0 ),Color ( 200, 0,0 ) );
    lineColorSave = viewer.getLineColor();
    viewer.setLineColor( DGtal::Color ( 200,20,20 ));
    for ( MyDigitalSurface::ConstIterator itbis = digSurf.begin(),itend=digSurf.end();
            itbis!=itend; ++itbis )
    {
        viewer << ks.unsigns ( *itbis );

        Point center = ks.sCoords ( *itbis );
        MyEstimatorGaussian::Quantity normal = myNormalEstimatorG.eval ( itbis );
        viewer.addLine ( center,
                         DGtal::Z3i::RealPoint(center[0]-3*normal[0],
                 center[1]-3*normal[1],
                 center[2]-3*normal[2]) );
    }
    viewer.setLineColor( lineColorSave);
    viewer<< Viewer3D<>::updateDisplay;

  return application.exec();
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main ( int argc, char** argv )
{
    trace.beginBlock ( "Testing class LocalConvolutionNormalVectorEstimator" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    bool res = testLocalConvolutionNormalVectorEstimator ( argc,argv ); // && ... other tests
    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    
    return (res ? 0:1);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
