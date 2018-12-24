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
 * @file testBallQuad.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/04/14
 *
 * Functions for testing class BallQuad.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/ImplicitDigitalSurface.h"
#include "DGtal/io/boards/Board3D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class BallQuad.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
template <typename TPoint3>
struct ImplicitDigitalBall3 {
  typedef TPoint3 Point;
  inline
  ImplicitDigitalBall3( double r )
    : myR( r )
  {}
  inline
  bool operator()( const TPoint3 & p ) const
  {
    double x = ( (double) p[ 0 ]  );
    double y = ( (double) p[ 1 ]  );
    double z = ( (double) p[ 2 ]  );
    return ( x*x + y*y + z*z  -myR*myR) <= 0.0;
  }
  double myR;
};


bool testBallQuad()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing... Ball with quadnormal");
  using namespace Z3i;
  typedef ImplicitDigitalBall3<Point> ImplicitDigitalBall;
  typedef ImplicitDigitalSurface<KSpace,ImplicitDigitalBall> Boundary;
  typedef Boundary::SurfelConstIterator ConstIterator;
  typedef Boundary::Surfel Surfel;
  Point p1( -50, -50, -50 );
  Point p2( 50, 50, 50 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "K.init() is ok" << std::endl;
  ImplicitDigitalBall ball( 30.0 );
  Surfel bel = Surfaces<KSpace>::findABel( K, ball, 10000 );
  Boundary boundary( K, ball,
                     SurfelAdjacency<KSpace::dimension>( true ), bel );
  unsigned int nbsurfels = 0;

  Board3D<Space,KSpace> board(K);

  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      ++nbsurfels;

      Display3DFactory<>::drawOrientedSurfelWithNormal(board,
                                                       *it,
                                                       board.embedKS(*it).getNormalized());
    }

  trace.info() << nbsurfels << " surfels found." << std::endl;

  board.saveOBJ("testball.obj");


  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class BallQuad" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testBallQuad(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
