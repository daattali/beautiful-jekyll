/**
 * @file topology/frontierAndBoundary.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named qglViewer.
 *
 * This file is part of the DGtal library.
 */

/**
 * Frontiers and boundary of two intersecting balls. The first ball is
 * labelled 1 (red), the second 2 (yellow), their intersection 3
 * (orange). The frontier between 1 and 0 is displayed in red, the
 * frontier between 2 and 0 is displayed in yellow, the boundary of
 * region 3 is displayed in orange.
 * 
 * @see \ref dgtal_digsurf_sec3_5
 * 
 * @image html digital-surface-intersecting-balls.png
 * @image latex digital-surface-intersecting-balls.png width=0.5\textwidth
 *
 * \example topology/frontierAndBoundary.cpp
 */


///////////////////////////////////////////////////////////////////////////////
//! [frontierAndBoundary-basicIncludes]
#include <iostream>

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/ExplicitDigitalSurface.h"
#include "DGtal/topology/helpers/FrontierPredicate.h"
#include "DGtal/topology/helpers/BoundaryPredicate.h"
//! [frontierAndBoundary-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  //! [frontierAndBoundary-LabelledImage]
  typedef Space::RealPoint RealPoint;
  typedef ImplicitBall<Space> EuclideanShape;
  typedef GaussDigitizer<Space,EuclideanShape> DigitalShape;
  typedef ImageContainerBySTLVector<Domain,DGtal::uint8_t> Image;
  Point c1( 2, 0, 0 );
  int radius1 = 6;
  EuclideanShape ball1( c1, radius1 ); // ball r=6
  DigitalShape shape1;
  shape1.attach( ball1 );
  shape1.init( RealPoint( -10.0, -10.0, -10.0 ),
               RealPoint( 10.0, 10.0, 10.0 ), 1.0 );
  Point c2( -2, 0, 0 );
  int radius2 = 5;
  EuclideanShape ball2( c2, radius2 ); // ball r=6
  DigitalShape shape2;
  shape2.attach( ball2 );
  shape2.init( RealPoint( -10.0, -10.0, -10.0 ),
               RealPoint( 10.0, 10.0, 10.0 ), 1.0 );
  Domain domain = shape1.getDomain();
  Image image( domain ); // p1, p2 );
  std::cerr << std::endl;
  for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end();
        it != it_end; ++it )
    {
      DGtal::uint8_t label = shape1( *it ) ? 1 : 0;
      label += shape2( *it ) ? 2 : 0;
      image.setValue( *it, label );
      std::cerr << (int) image( *it );
    }
  std::cerr << std::endl;
  //! [frontierAndBoundary-LabelledImage]

  //! [frontierAndBoundary-KSpace]
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace K;
  bool space_ok = K.init( domain.lowerBound(), domain.upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  trace.endBlock();
  //! [frontierAndBoundary-KSpace]

  //! [frontierAndBoundary-SetUpDigitalSurface]
  trace.beginBlock( "Set up digital surface." );
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  typedef functors::FrontierPredicate<KSpace, Image> FSurfelPredicate;
  typedef ExplicitDigitalSurface<KSpace,FSurfelPredicate> FrontierContainer;
  typedef DigitalSurface<FrontierContainer> Frontier;
  typedef functors::BoundaryPredicate<KSpace, Image> BSurfelPredicate;
  typedef ExplicitDigitalSurface<KSpace,BSurfelPredicate> BoundaryContainer;
  typedef DigitalSurface<BoundaryContainer> Boundary;
  // frontier between label 1 and 0 (connected part containing bel10)
  SCell vox1  = K.sSpel( c1 + Point( radius1, 0, 0 ), K.POS );
  SCell bel10 = K.sIncident( vox1, 0, true );
  FSurfelPredicate surfPredicate10( K, image, 1, 0 );
  Frontier frontier10 =
    new FrontierContainer( K, surfPredicate10, surfAdj, bel10 );
  // frontier between label 2 and 0 (connected part containing bel20)
  SCell vox2  = K.sSpel( c2 - Point( radius2, 0, 0 ), K.POS );
  SCell bel20 = K.sIncident( vox2, 0, false );
  FSurfelPredicate surfPredicate20( K, image, 2, 0 );
  Frontier frontier20 =
    new FrontierContainer( K, surfPredicate20, surfAdj, bel20 );
  // boundary of label 3 (connected part containing bel32)
  SCell vox3  = K.sSpel( c1 - Point( radius1, 0, 0 ), K.POS );
  SCell bel32 = K.sIncident( vox3, 0, false );
  BSurfelPredicate surfPredicate3( K, image, 3 );
  Boundary boundary3 =
    new BoundaryContainer( K, surfPredicate3, surfAdj, bel32 );
  trace.endBlock();
  //! [frontierAndBoundary-SetUpDigitalSurface]

  //! [volBreadthFirstTraversal-DisplayingSurface]
  trace.beginBlock( "Displaying surface in Viewer3D." );
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  viewer << SetMode3D( domain.className(), "BoundingBox" )
         << domain;
  Cell dummy;
  // Display frontier between 1 and 0.
  unsigned int nbSurfels10 = 0;
  viewer << CustomColors3D( Color::Red, Color::Red );
  for ( Frontier::ConstIterator
          it = frontier10.begin(), it_end = frontier10.end();
        it != it_end; ++it, ++nbSurfels10 )
    viewer << *it;
  // Display frontier between 2 and 0.
  unsigned int nbSurfels20 = 0;
  viewer << CustomColors3D( Color::Yellow, Color::Yellow );
  for ( Frontier::ConstIterator
          it = frontier20.begin(), it_end = frontier20.end();
        it != it_end; ++it, ++nbSurfels20 )
    viewer << *it;
  // Display boundary of 3.
  unsigned int nbSurfels3 = 0;
  viewer << CustomColors3D( Color( 255, 130, 15 ), Color( 255, 130, 15 ) );
  for ( Boundary::ConstIterator
          it = boundary3.begin(), it_end = boundary3.end();
        it != it_end; ++it, ++nbSurfels3 )
    viewer << *it;
  trace.info() << "nbSurfels10 = " << nbSurfels10
               << ", nbSurfels20 = " << nbSurfels20
               << ", nbSurfels3 = " << nbSurfels3 << std::endl;
  viewer << Viewer3D<>::updateDisplay;
  trace.endBlock();
  return application.exec();
  //! [volBreadthFirstTraversal-DisplayingSurface]
}
