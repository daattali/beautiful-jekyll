/**
 * @file topology/volMarchingCubes.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named volMarchingCubes.
 *
 * This file is part of the DGtal library.
 */


/**
 * Marching-cube like surface extracted using the combinatorial
 * manifold structure of digital surfaces.
 *
 * @see \ref dgtal_digsurf_sec4_3
 *
 * @verbatim
 * # Commands
 * $ ./examples/topology/volMarchingCubes  ../examples/samples/Al.100.vol 0 1 0 
 * @endverbatim
 * 
 * @image html digital-surface-mc-Al100.png "Marching-cube surface of Al.100.vol file."
 * 
 * \example topology/volMarchingCubes.cpp
 */


///////////////////////////////////////////////////////////////////////////////
//! [volMarchingCubes-basicIncludes]
#include <iostream>
#include <queue>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageLinearCellEmbedder.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
//! [volMarchingCubes-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> <maxT> <Adj>" << std::endl;
  std::cerr << "\t - displays the boundary of the shape stored in vol file <fileName.vol>." << std::endl;
  std::cerr << "\t - voxel v belongs to the shape iff its value I(v) follows minT <= I(v) <= maxT." << std::endl;
  std::cerr << "\t - 0: interior adjacency, 1: exterior adjacency." << std::endl;

}

int main( int argc, char** argv )
{
  if ( argc < 5 )
    {
      usage( argc, argv );
      return 1;
    }
  std::string inputFilename = argv[ 1 ];
  unsigned int minThreshold = atoi( argv[ 2 ] );
  unsigned int maxThreshold = atoi( argv[ 3 ] );
  bool intAdjacency = atoi( argv[ 4 ] ) == 0;

  //! [volMarchingCubes-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [volMarchingCubes-readVol]


  //! [volMarchingCubes-KSpace]
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
  //! [volMarchingCubes-KSpace]

  //! [volMarchingCubes-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( intAdjacency ); // interior in all directions.
  //! [volMarchingCubes-SurfelAdjacency]

  //! [volMarchingCubes-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by scanning the space. " );
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;
  MySetOfSurfels theSetOfSurfels( ks, surfAdj );
  Surfaces<KSpace>::sMakeBoundary( theSetOfSurfels.surfelSet(),
                                   ks, set3d,
                                   image.domain().lowerBound(),
                                   image.domain().upperBound() );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  trace.endBlock();
  //! [volMarchingCubes-ExtractingSurface]

  //! [volMarchingCubes-makingOFF]
  trace.beginBlock( "Making OFF surface <marching-cube.off>. " );
  typedef CanonicEmbedder< Space > MyEmbedder;
  typedef
    ImageLinearCellEmbedder< KSpace, Image, MyEmbedder > CellEmbedder;
  CellEmbedder cellEmbedder;
  MyEmbedder trivialEmbedder;
  // The +0.5 is to avoid isosurface going exactly through a voxel
  // center, especially for binary volumes.
  cellEmbedder.init( ks, image, trivialEmbedder, 
                     ( (double) minThreshold ) + 0.5 );
  ofstream out( "marching-cube.off" );
  if ( out.good() )
    digSurf.exportEmbeddedSurfaceAs3DOFF( out, cellEmbedder );
  out.close();
  trace.endBlock();
  //! [volMarchingCubes-makingOFF]
  return 0;
}

