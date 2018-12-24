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
 * @file testNormalVectorEstimatorEmbedder.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/08
 *
 * Functions for testing class NormalVectorEstimatorEmbedder.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iterator>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/topology/CanonicDigitalSurfaceEmbedder.h"
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

#include "DGtal/images/ImageSelector.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/CanonicEmbedder.h"

#include "DGtal/geometry/surfaces/estimation/CNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/BasicConvolutionWeights.h"
#include "DGtal/geometry/surfaces/estimation/LocalConvolutionNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/DigitalSurfaceEmbedderWithNormalVectorEstimator.h"
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
bool testLocalConvolutionNormalVectorEstimator ( int /*argc*/, char**/*argv*/ )
{
    trace.beginBlock ( "Testing convolution neighborhood ..." );

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
        return 2;
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
    trace.endBlock();

    trace.beginBlock ( "Compute and output surface <cat10-constant.off> with trivial normals." );
    //Convolution kernel
    deprecated::ConstantConvolutionWeights<MyDigitalSurface::Size> kernel;

    //Estimator definition
    typedef deprecated::LocalConvolutionNormalVectorEstimator
      < MyDigitalSurface,
        deprecated::ConstantConvolutionWeights<MyDigitalSurface::Size> > MyConstantEstimator;
    BOOST_CONCEPT_ASSERT ( ( concepts::CNormalVectorEstimator< MyConstantEstimator > ) );
    MyConstantEstimator myNormalEstimator ( digSurf, kernel );

    // Embedder definition
    typedef CanonicDigitalSurfaceEmbedder<MyDigitalSurface> SurfaceEmbedder;
    SurfaceEmbedder surfaceEmbedder ( digSurf );
    typedef DigitalSurfaceEmbedderWithNormalVectorEstimator
    < SurfaceEmbedder, MyConstantEstimator > SurfaceEmbedderWithTrivialNormal;
    SurfaceEmbedderWithTrivialNormal mySurfelEmbedder ( surfaceEmbedder,
            myNormalEstimator );

    // Compute normal vector field and displays it.
    myNormalEstimator.init ( 1.0, 2 );

    MyConstantEstimator::Quantity res = myNormalEstimator.eval ( it );
    trace.info() << "Normal vector at begin() : "<< res << std::endl;

    ofstream out ( "cat10-constant.off" );
    if ( out.good() )
        digSurf.exportAs3DNOFF ( out,mySurfelEmbedder );
    out.close();
    trace.endBlock();

    trace.beginBlock ( "Compute and output surface <cat10-gaussian.off> with gaussian convoluted normals." );

    //Convolution kernel
    deprecated::GaussianConvolutionWeights < MyDigitalSurface::Size > Gkernel ( 4.0 );

    //Estimator definition
    typedef deprecated::LocalConvolutionNormalVectorEstimator  < MyDigitalSurface,
                                                                 deprecated::GaussianConvolutionWeights< MyDigitalSurface::Size>  > MyGaussianEstimator;
    BOOST_CONCEPT_ASSERT ( ( concepts::CNormalVectorEstimator< MyGaussianEstimator > ) );
    MyGaussianEstimator myNormalEstimatorG ( digSurf, Gkernel );

    // Embedder definition
    typedef DigitalSurfaceEmbedderWithNormalVectorEstimator<SurfaceEmbedder,MyGaussianEstimator> SurfaceEmbedderWithGaussianNormal;
    SurfaceEmbedderWithGaussianNormal mySurfelEmbedderG ( surfaceEmbedder, myNormalEstimatorG );

    // Compute normal vector field and displays it.
    myNormalEstimatorG.init ( 1.0, 5 );

    MyGaussianEstimator::Quantity res2 = myNormalEstimatorG.eval ( it );
    trace.info() << "Normal vector at begin() : "<< res2 << std::endl;
    std::vector<MyGaussianEstimator::Quantity> allNormals;
    myNormalEstimatorG.evalAll ( std::back_inserter ( allNormals ) );
    trace.info() << "Normal vector field of size "<< allNormals.size() << std::endl;

    ofstream out2 ( "cat10-gaussian.off" );
    if ( out2.good() )
        digSurf.exportAs3DNOFF ( out2 ,mySurfelEmbedderG );
    out2.close();

   trace.endBlock();

    return true;
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

    return res ? 0 : 1;

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
