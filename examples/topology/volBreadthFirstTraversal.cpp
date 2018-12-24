/**
 * @file topology/volBreadthFirstTraversal.cpp
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
 * Examples of breadth-first traversal on a digital surface
 * You can use these commands:
 * @verbatim
 * # Commands
 * $ ./examples/topology/volBreadthFirstTraversal ../examples/samples/lobster.vol 50 255
 * $ ./examples/topology/volBreadthFirstTraversal ../examples/samples/cat10.vol 1 255
 * @endverbatim
 * 
 * to get these pictures:
 *   @image html digital-surface-bfv-all.png "Examples of breadth-first traversal on a digital surface."
 *   @example topology/volBreadthFirstTraversal.cpp
 */

///////////////////////////////////////////////////////////////////////////////
//! [volBreadthFirstTraversal-basicIncludes]
#include <iostream>
#include <queue>
#include <QImageReader>

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/io/viewers/Viewer3D.h"

//! [volBreadthFirstTraversal-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> <maxT>" << std::endl;
  std::cerr << "\t - displays the boundary of the shape stored in vol file <fileName.vol>." << std::endl;
  std::cerr << "\t - voxel v belongs to the shape iff its value I(v) follows minT <= I(v) <= maxT." << std::endl;
}

int main( int argc, char** argv )
{
  if ( argc < 4 )
    {
      usage( argc, argv );
      return 1;
    }
  std::string inputFilename = argv[ 1 ];
  unsigned int minThreshold = atoi( argv[ 2 ] );
  unsigned int maxThreshold = atoi( argv[ 3 ] );

  //! [volBreadthFirstTraversal-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [volBreadthFirstTraversal-readVol]


  //! [volBreadthFirstTraversal-KSpace]
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace ks;
  bool space_ok = ks.init( image.domain().lowerBound(),
                           image.domain().upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  trace.endBlock();
  //! [volBreadthFirstTraversal-KSpace]

  //! [volBreadthFirstTraversal-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  //! [volBreadthFirstTraversal-SurfelAdjacency]

  //! [volBreadthFirstTraversal-SetUpDigitalSurface]
  trace.beginBlock( "Set up digital surface." );
  typedef LightImplicitDigitalSurface<KSpace, DigitalSet >
    MyDigitalSurfaceContainer;
  typedef DigitalSurface<MyDigitalSurfaceContainer> MyDigitalSurface;
  SCell bel = Surfaces<KSpace>::findABel( ks, set3d, 100000 );
  MyDigitalSurfaceContainer* ptrSurfContainer =
    new MyDigitalSurfaceContainer( ks, set3d, surfAdj, bel );
  MyDigitalSurface digSurf( ptrSurfContainer ); // acquired
  trace.endBlock();
  //! [volBreadthFirstTraversal-SetUpDigitalSurface]

  //! [volBreadthFirstTraversal-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by tracking from an initial bel." );
  typedef BreadthFirstVisitor<MyDigitalSurface> MyBreadthFirstVisitor;
  typedef MyBreadthFirstVisitor::Node MyNode;
  typedef MyBreadthFirstVisitor::Size MySize;
  MyBreadthFirstVisitor visitor( digSurf, bel );
  unsigned long nbSurfels = 0;
  MyNode node;
  while ( ! visitor.finished() )
    {
      node = visitor.current();
      ++nbSurfels;
      visitor.expand();
    }
  MySize maxDist = node.second;
  trace.endBlock();
  //! [volBreadthFirstTraversal-ExtractingSurface]

  //! [volBreadthFirstTraversal-DisplayingSurface]
  trace.beginBlock( "Displaying surface in Viewer3D." );
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  HueShadeColorMap<MySize,1> hueShade( 0, maxDist );
  MyBreadthFirstVisitor visitor2( digSurf, bel );
  viewer << CustomColors3D( Color::Black, Color::White )
         << ks.unsigns( bel );
  visitor2.expand();
  while ( ! visitor2.finished() )
    {
      node = visitor2.current();
      Color c = hueShade( node.second );
      viewer << CustomColors3D( Color::Red, c )
             << ks.unsigns( node.first );
      visitor2.expand();
    }
  viewer << Viewer3D<>::updateDisplay;
  trace.info() << "nb surfels = " << nbSurfels << std::endl;
  trace.endBlock();
  return application.exec();
  //! [volBreadthFirstTraversal-DisplayingSurface]
}

