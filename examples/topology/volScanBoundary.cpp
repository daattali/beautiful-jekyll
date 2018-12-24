/**
 * @file topology/volScanBoundary.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named volScanBoundary.
 *
 * This file is part of the DGtal library.
 */

/**
 * Given a domain and a predicate telling whether we are inside or
 * outside the object of interest, it is easy to determine the set of
 * surfels by a simple scanning of the space. This is done for you by
 * static methods Surfaces::uMakeBoundary and Surfaces::sMakeBoundary.
 * 
 * @see \ref dgtal_digsurf_sec2_1
 * 
 * On the lobser.vol volume, volScanBoundary.cpp extracts 155068 surfels
 * in 3866ms
 * 
 * @verbatim
 * # Commands
 * $ ./examples/topology/volScanBoundary ../examples/samples/lobster.vol 50 255
 * @endverbatim
 * 
 * @image html volTrackBoundary-lobster.png "Digital surface that is the boundary of a (6,18)-connected component in image lo bster.vol, extracted by scanning the whole space in 3866ms."
 * 
 * \example topology/volScanBoundary.cpp 
 */


///////////////////////////////////////////////////////////////////////////////
//! [volScanBoundary-basicIncludes]
#include <iostream>
#include <queue>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/io/viewers/Viewer3D.h"
//! [volScanBoundary-basicIncludes]

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

  //! [volScanBoundary-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [volScanBoundary-readVol]


  //! [volScanBoundary-KSpace]
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
  //! [volScanBoundary-KSpace]

  //! [volScanBoundary-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by scanning the space. " );
  KSpace::SCellSet boundary;
  Surfaces<KSpace>::sMakeBoundary( boundary, ks, set3d,
                                   image.domain().lowerBound(),
                                   image.domain().upperBound() );
  trace.endBlock();
  //! [volScanBoundary-ExtractingSurface]

  //! [volScanBoundary-DisplayingSurface]
  trace.beginBlock( "Displaying surface in Viewer3D." );
  QApplication application(argc,argv);
  Viewer3D<> viewer( ks );
  viewer.show();
  KSpace::SCell dummy_scell;
  viewer << SetMode3D( dummy_scell.className(), "Basic" );
  viewer << CustomColors3D(Color(250, 0, 0 ), Color( 128, 128, 128 ) );
  unsigned long nbSurfels = 0;
  for ( KSpace::SCellSet::const_iterator it = boundary.begin(),
          it_end = boundary.end(); it != it_end; ++it, ++nbSurfels )
    viewer << *it;
  viewer << Viewer3D<>::updateDisplay;
  trace.info() << "nb surfels = " << nbSurfels << std::endl;
  trace.endBlock();
  return application.exec();
  //! [volScanBoundary-DisplayingSurface]
}

