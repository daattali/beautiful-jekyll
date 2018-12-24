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
 * @file topology/volToOFF.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * A simple marching cube algorithm for vol files based on digital surfaces.
 *
 * This file is part of the DGtal library.
 */


/**
 * Marching-cube like surface extracted using the combinatorial
 * manifold structure of digital surfaces.
 * 
 * @see \ref dgtal_digsurf_sec4_3
 * 
 * On the lobser.vol volume, volToOFF.cpp builds an OFF surface of
 * 155068 vertices, 154910 faces, 310136 edges in 3879ms+1646ms.
 * 
 * @verbatim
 * # Commands
 * $ ./examples/topology/volToOff ../examples/samples/cat10.vol 1 255 0
 * $ ./examples/topology/volToOff ../examples/samples/lobster.vol 50 255 0
 * @endverbatim
 * 
 * @image html digital-surface-mc-cat10.png "Marching-cube surface of cat10.vol file."
 * @image html digital-surface-mc-lobster.png "Marching-cube surface of lobster.vol file."
 *
 * \example topology/volToOFF.cpp
 */


///////////////////////////////////////////////////////////////////////////////
//! [volToOff-basicIncludes]
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
//! [volToOff-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////


void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> <maxT> <int=0|ext=1>" << std::endl;
  std::cerr << "\t - displays the boundary of the shape stored in vol file <fileName.vol> as an OFF geomview surface file. It is a kind of marching-cube surface, defined by duality with respect to the digital surface." << std::endl;
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

  //! [volToOff-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [volToOff-readVol]

  //! [volToOff-KSpace]
  // Construct the Khalimsky space from the image domain
  KSpace K;
  bool space_ok = K.init( image.domain().lowerBound(),
                          image.domain().upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  //! [volToOff-KSpace]

  //! [volToOff-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( intAdjacency ); // interior in all directions.
  //! [volToOff-SurfelAdjacency]

  //! [volToOff-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by scanning the space. " );
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;

  MySetOfSurfels theSetOfSurfels( K, surfAdj );
  Surfaces<KSpace>::sMakeBoundary( theSetOfSurfels.surfelSet(),
                                   K, set3d,
                                   image.domain().lowerBound(),
                                   image.domain().upperBound() );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  trace.endBlock();
  //! [volToOff-ExtractingSurface]

  //! [volToOff-makingOFF]
  trace.beginBlock( "Making OFF surface <marching-cube.off>. " );
  ofstream out( "marching-cube.off" );
  if ( out.good() )
    digSurf.exportSurfaceAs3DOFF( out );
  out.close();
  trace.endBlock();
  //! [volToOff-makingOFF]

  return 0;
}
