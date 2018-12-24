/**
 * @file arithmetic/lower-integer-convex-hull.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named lower-integer-convex-hull.
 *
 * This file is part of the DGtal library.
 */
/**
   This example shows how to create a LatticePolytope2D that
   represents a square. Then given integer parameters \a a, \a b, \a
   c, it cuts the polygon by the half-plane \f$ ax+by \le c \f$. It
   also outputs some statistics.

@see \ref dgtal_lattice_polytope_2d_sec6

@verbatim
$ ./examples/arithmetic/lower-integer-convex-hull -5 8 41
Number of vertices        = 8
Area                      = 299.5
Number of interior points = 273
Number of boundary points = 55
# The animation below was created by this script (needs ImageMagick)
$ let x=130; while test $x -ge -130; do echo "--- $x ---"; ./examples/arithmetic/lower-integer-convex-hull -5 8 $x; let z=x+130; y=`printf "%03d" $z`; convert -resize 300x300 -background white -layers flatten lower-integer-convex-hull-cut.eps lower-integer-convex-hull-$y.gif; let x=x-2; done
...
$ convert -delay 20 -loop 0 lower-integer-convex-hull-*.gif lower-animation.gif
$ animate lower-animation.gif 
@endverbatim

@image html lower-integer-convex-hull-cut-2.png "Square of side 20 cut by the half-plane -5x+8y <= 41"
@image latex lower-integer-convex-hull-cut-2.png "Square of side 20 cut by the half-plane -5x+8y <= 41" width=5cm

@image html lower-animation.gif "Square cut by the half space -5x+8y <= c, for c from -130 to 130"

\example arithmetic/lower-integer-convex-hull.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [lower-integer-convex-hull-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
//! [lower-integer-convex-hull-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <a> <b> <c>" << std::endl;
  std::cerr << "\t - Cuts a square by ax+by <= c. Displays everything in files "
            << "lower-integer-convex-hull*.eps" << std::endl;
}

/**
   Main.
*/
int main( int argc, char** argv )
{
  if ( argc < 4 )
    {
      usage( argc, argv );
      return 0;
    }

  //! [lower-integer-convex-hull-types]
  using namespace Z2i;
  typedef LatticePolytope2D<Space> CIP;
  //! [lower-integer-convex-hull-types]

  //! [lower-integer-convex-hull-instantiation]
  CIP cip;
  cip.push_front( Point( -10, -10 ) );
  cip.push_front( Point( -10, 10 ) );
  cip.push_front( Point( 10, 10 ) );
  cip.push_front( Point( 10, -10 ) );
  Domain domain = cip.boundingBoxDomain();
  Board2D board;
  board << domain 
        << CustomStyle( cip.className(), 
                        new CustomColors( Color::Red, Color::None ) )
        << cip;
  board.saveEPS( "lower-integer-convex-hull.eps" );
  board.clear();
  //! [lower-integer-convex-hull-instantiation]

  int a = atoi( argv[ 1 ] );
  int b = atoi( argv[ 2 ] );
  int c = atoi( argv[ 3 ] );

  //! [lower-integer-convex-hull-process]
  typedef LatticePolytope2D<Z2>::HalfSpace HalfSpace;
  HalfSpace hs( Vector( a, b ), c );
  cip.cut( hs );
  DigitalSet aSet( domain );
  Shapes<Domain>::makeSetFromPointPredicate( aSet, hs );
  board << domain 
        << CustomStyle( aSet.className(), 
                        new CustomColors( Color::Green, Color::Green ) )
        << SetMode( Point().className(), "Grid" )
        << aSet
        << CustomStyle( cip.className(), 
                        new CustomColors( Color::Red, Color::None ) )
        << cip;
  board.saveEPS( "lower-integer-convex-hull-cut.eps" );
  //! [lower-integer-convex-hull-process]

  //! [lower-integer-convex-hull-stats]
  std::cout << "Number of vertices        = " << cip.size() << std::endl;
  std::cout << "Area                      = " << (((double)cip.twiceArea())/2.0) << std::endl;
  std::cout << "Number of interior points = " << cip.numberInteriorPoints() << std::endl;
  std::cout << "Number of boundary points = " << cip.numberBoundaryPoints() << std::endl;
  //! [lower-integer-convex-hull-stats]
  return 0;
}

