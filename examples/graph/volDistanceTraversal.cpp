/**
 * @file graph/volDistanceTraversal.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named volDistanceTraversal.
 *
 * This file is part of the DGtal library.
 */
/**

  Displays the Euclidean distance to a starting surfel on the boundary
  of a vol shape (traversal by mix distance/breadth-first, see
  \ref DGtal::DistanceBreadthFirstVisitor).

@see \ref dgtal_graph_def_2_4

@verbatim
# Commands
$ ./examples/graph/volDistanceTraversal ../examples/samples/cat10.vol 0 255 100
@endverbatim

@image html volDistanceTraversal-cat10.png "Coloring vertices of a vol boundary according to the Euclidean distance to a starting surfel (distance breadth-first traversal)."

\example graph/volDistanceTraversal.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [volDistanceTraversal-basicIncludes]
#include <iostream>
#include <queue>
#include <QImageReader>

#include "DGtal/base/BasicFunctors.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/graph/DistanceBreadthFirstVisitor.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
//! [volDistanceTraversal-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> <maxT> <idxP>" << std::endl;
  std::cerr << "\t - displays the Euclidean distance to the specified surfel on the boundary of the shape stored in vol file <fileName.vol>." << std::endl;
  std::cerr << "\t - the shape is defined implicitly: voxel v belongs to the shape iff its value I(v) follows minT < I(v) <= maxT." << std::endl;
  std::cerr << "\t - starts from the <idxP>-th surfel or first one if invalid." << std::endl;
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
  unsigned int idxP = (argc <= 4) ? 0 : atoi( argv[ 4 ] );

  //! [volDistanceTraversal-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [volDistanceTraversal-readVol]


  //! [volDistanceTraversal-KSpace]
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
  //! [volDistanceTraversal-KSpace]

  //! [volDistanceTraversal-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  //! [volDistanceTraversal-SurfelAdjacency]

  //! [volDistanceTraversal-SetUpDigitalSurface]
  trace.beginBlock( "Set up digital surface." );
  typedef LightImplicitDigitalSurface<KSpace, DigitalSet >
    MyDigitalSurfaceContainer;
  typedef DigitalSurface<MyDigitalSurfaceContainer> MyDigitalSurface;
  SCell bel = Surfaces<KSpace>::findABel( ks, set3d, 100000 );
  MyDigitalSurfaceContainer* ptrSurfContainer =
    new MyDigitalSurfaceContainer( ks, set3d, surfAdj, bel );
  MyDigitalSurface digSurf( ptrSurfContainer ); // acquired
  trace.endBlock();
  // Find first bel.
  MyDigitalSurface::ConstIterator it = digSurf.begin();
  for ( idxP = idxP % digSurf.size(); idxP != 0; --idxP ) ++it;
  bel = *it;
  //! [volDistanceTraversal-SetUpDigitalSurface]

  //! [volDistanceTraversal-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by distance tracking from an initial bel." );
  typedef CanonicSCellEmbedder<KSpace> SCellEmbedder;
  typedef SCellEmbedder::Value RealPoint;
  typedef RealPoint::Coordinate Scalar;
  typedef ExactPredicateLpSeparableMetric<Space,2> Distance;
  using DistanceToPoint = std::function<double(const Space::Point &)>;
  typedef DGtal::functors::Composer<SCellEmbedder, DistanceToPoint, Scalar> VertexFunctor;
  typedef DistanceBreadthFirstVisitor< MyDigitalSurface, VertexFunctor, std::set<SCell> >
    MyDistanceVisitor;
  typedef MyDistanceVisitor::Node MyNode;
  typedef MyDistanceVisitor::Scalar MySize;

  SCellEmbedder embedder( ks );
  Distance distance;
  DistanceToPoint distanceToPoint = std::bind( distance, embedder( bel ), std::placeholders::_1 );
  VertexFunctor vfunctor( embedder, distanceToPoint );
  MyDistanceVisitor visitor( digSurf, vfunctor, bel );

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
  //! [volDistanceTraversal-ExtractingSurface]

  //! [volDistanceTraversal-DisplayingSurface]
  trace.beginBlock( "Displaying surface in Viewer3D." );
  QApplication application(argc,argv);
  Viewer3D<> viewer( ks );
  viewer.show();
  HueShadeColorMap<MySize,1> hueShade( 0, maxDist );
  MyDistanceVisitor visitor2( digSurf, vfunctor, bel );
  viewer << SetMode3D( bel.className(), "Basic" );
  viewer << CustomColors3D( Color::Black, Color::White )
         << bel;
  visitor2.expand();
  std::vector< MyDistanceVisitor::Node > layer;
  while ( ! visitor2.finished() )
    {
      MyNode n = visitor2.current();
      Color c = hueShade( n.second );
      viewer << CustomColors3D( Color::Red, c )
             << n.first;
      visitor2.expand();
    }
  viewer << Viewer3D<>::updateDisplay;
  trace.info() << "nb surfels = " << nbSurfels << std::endl;
  trace.endBlock();
  return application.exec();
  //! [volDistanceTraversal-DisplayingSurface]
}

