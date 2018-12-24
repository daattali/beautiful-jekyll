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
 * @file topology/trackImplicitPolynomialSurfaceToOFF.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * A simple marching cube algorithm based on digital surfaces.
 *
 * This file is part of the DGtal library.
 */


/** 
 * Implicit polynomial surface defined on the command-line by the
 * user (as "(x^2+y^2+2z^2-1)*(z^2x-0.1)"), then extracted using digital
 * surface tracking and converted into the corresponding combinatorial
 * surface.
 * 
 * @see \ref dgtal_mpolynomial_sec3
 * @see \ref dgtal_digsurf_sec4_3
 *
 * @verbatim
 * $ ./examples/topology/trackImplicitPolynomialSurfaceToOFF "(x^2+y^2+2*z^2-1)*(z^2x-0.1)" -2 -2 -2 2 2 2 0.02
 * # Digital surface has 112826 surfels.
 * # output in marching-cube.off (in 1809ms)
 * # You may display it with your favorite OFF displayer (like geomview, etc).
 * $ ctmviewer marching-cube.off
 * @endverbatim
 *
 * @image html nice-mpolynomial.png "Implicit polynomial surface (x^2+y^2+2*z^2-1)*(z^2x-0.1) between [-2,-2,-2] and [2,2,2], step 0.02."
 * @image latex nice-mpolynomial.png width=0.5\textwidth "Implicit polynomial surface (x^2+y^2+2*z^2-1)*(z^2x-0.1) between [-2,-2,-2] and [2,2,2], step 0.02."
 *
 * \example topology/trackImplicitPolynomialSurfaceToOFF.cpp
 */


///////////////////////////////////////////////////////////////////////////////
//! [trackImplicitPolynomialSurfaceToOFF-basicIncludes]
#include <iostream>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/shapes/implicit/ImplicitFunctionDiff1LinearCellEmbedder.h"
#include "DGtal/io/readers/MPolynomialReader.h"
//! [trackImplicitPolynomialSurfaceToOFF-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////


void usage( int /*argc*/, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <Polynomial> <Px> <Py> <Pz> <Qx> <Qy> <Qz> <step>" << std::endl;
  std::cerr << "\t - displays the boundary of a shape defined implicitly by a 3-polynomial <Polynomial>." << std::endl;
  std::cerr << "\t - P and Q defines the bounding box." << std::endl;
  std::cerr << "\t - step is the grid step." << std::endl;
  std::cerr << "\t - You may try x^3y+xz^3+y^3z+z^3+5z or (y^2+z^2-1)^2 +(x^2+y^2-1)^3 " << std::endl;
  std::cerr << "\t - See http://www.freigeist.cc/gallery.html" << std::endl;
}

int main( int argc, char** argv )
{
  if ( argc < 9 )
    {
      usage( argc, argv );
      return 1;
    }
  double p1[ 3 ];
  double p2[ 3 ];
  for ( unsigned int i = 0; i < 3; ++i )
    {
      p1[ i ] = atof( argv[ 2+i ] );
      p2[ i ] = atof( argv[ 5+i ] );
    }
  double step = atof( argv[ 8 ] );

  //! [trackImplicitPolynomialSurfaceToOFF-makeSurface]
  trace.beginBlock( "Making polynomial surface." );
  typedef Space::RealPoint RealPoint;
  typedef RealPoint::Coordinate Ring;
  typedef MPolynomial<3, Ring> Polynomial3;
  typedef MPolynomialReader<3, Ring> Polynomial3Reader;
  typedef ImplicitPolynomial3Shape<Space> ImplicitShape;
  typedef GaussDigitizer<Space,ImplicitShape> DigitalShape; 
  typedef DigitalShape::PointEmbedder DigitalEmbedder;

  // See http://www.freigeist.cc/gallery.html
  Polynomial3 P;
  Polynomial3Reader reader;
  std::string poly_str = argv[ 1 ];
  std::string::const_iterator iter 
    = reader.read( P, poly_str.begin(), poly_str.end() );
  if ( iter != poly_str.end() )
    {
      std::cerr << "ERROR: I read only <" 
                << poly_str.substr( 0, iter - poly_str.begin() )
                << ">, and I built P=" << P << std::endl;
      return 1;
    }
  // Durchblick x3y+xz3+y3z+z3+5z = 0

    //   MPolynomial<3, double> P = mmonomial<double>( 3, 1, 0 )
    // + mmonomial<double>( 1, 0, 3 )
    // + mmonomial<double>( 0, 3, 1 )
    // + mmonomial<double>( 0, 0, 3 )
    // + 5 * mmonomial<double>( 0, 0, 1 );
  // Crixxi (y2+z2-1)2 +(x2+y2-1)3 = 0
  // developed = y4 +2y2z2+z4-2z2 -y2 + x6+3x4y2+3x2y4+y6-3x4-6x2y2-3y4+3x2
  // MPolynomial<3, double> P = mmonomial<double>(0,4,0)
  //   + 2 * mmonomial<double>(0,2,2)
  //   + mmonomial<double>(0,2,0)
  //   + mmonomial<double>(0,0,4)
  //   - 2 * mmonomial<double>(0,0,2)
  //   + mmonomial<double>(6,0,0)
  //   + 3 * mmonomial<double>(4,2,0)
  //   + 3 * mmonomial<double>(2,4,0)
  //   + mmonomial<double>(0,6,0)
  //   - 3 * mmonomial<double>(4,0,0)
  //   - 6 * mmonomial<double>(2,2,0)
  //   - 3 * mmonomial<double>(0,4,0)
  //   + 3 * mmonomial<double>(2,0,0);
  
  trace.info() << "P( X_0, X_1, X_2 ) = " << P << std::endl;
  ImplicitShape ishape( P );
  DigitalShape dshape;
  dshape.attach( ishape );
  dshape.init( RealPoint( p1 ), RealPoint( p2 ), step );
  Domain domain = dshape.getDomain();
  trace.endBlock();
  //! [trackImplicitPolynomialSurfaceToOFF-makeSurface]

  //! [trackImplicitPolynomialSurfaceToOFF-KSpace]
  // Construct the Khalimsky space from the image domain
  KSpace K;
  // NB: it is \b necessary to work with a \b closed cellular space
  // since umbrellas use separators and pivots, which must exist for
  // arbitrary surfels.
  bool space_ok = K.init( domain.lowerBound(), 
                          domain.upperBound(), true // necessary
                          );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  //! [trackImplicitPolynomialSurfaceToOFF-KSpace]

  //! [trackImplicitPolynomialSurfaceToOFF-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  //! [trackImplicitPolynomialSurfaceToOFF-SurfelAdjacency]

  //! [trackImplicitPolynomialSurfaceToOFF-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by tracking the space. " );
  typedef KSpace::Surfel Surfel;
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;

  // The surfels are tracked from an initial surfel, which is found by
  // try/error.
  MySetOfSurfels theSetOfSurfels( K, surfAdj );
  Surfel bel = Surfaces<KSpace>::findABel( K, dshape, 100000 );
  Surfaces<KSpace>::trackBoundary( theSetOfSurfels.surfelSet(),
                                   K, surfAdj, 
                                   dshape, bel );
  trace.endBlock();
  //! [trackImplicitPolynomialSurfaceToOFF-ExtractingSurface]

  //! [trackImplicitPolynomialSurfaceToOFF-makingOFF]
  trace.beginBlock( "Making OFF surface <marching-cube.off>. " );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  // The cell embedder is used to place vertices closer to the set
  // P(x,y,z)=0
  typedef 
    ImplicitFunctionDiff1LinearCellEmbedder< KSpace, 
                                             ImplicitShape, 
                                             DigitalEmbedder >
    CellEmbedder;
  CellEmbedder cellEmbedder;
  cellEmbedder.init( K, ishape, dshape.pointEmbedder() );
  ofstream out( "marching-cube.off" );
  if ( out.good() )
    digSurf.exportEmbeddedSurfaceAs3DOFF( out, cellEmbedder );
  out.close();
  trace.endBlock();
  //! [trackImplicitPolynomialSurfaceToOFF-makingOFF]
  trace.beginBlock( "Making NOFF surface <marching-cube.noff>. " );
  ofstream out2( "marching-cube.noff" );
  if ( out2.good() )
    digSurf.exportEmbeddedSurfaceAs3DNOFF( out2, cellEmbedder );
  out2.close();
  trace.endBlock();

  return 0;
}
