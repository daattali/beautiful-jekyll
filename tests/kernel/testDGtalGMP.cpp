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
 * @file testDGtalGMP.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/12/13
 *
 * Functions for testing class DGtalGMP.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DGtalBIGINTEGER.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testDGtalBIGINTEGER()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "BIGINTEGER linking test..." );
 
  DGtal::BigInteger a, b, c;
  
  a = 1234;
  b = "-5678";
  c = a+b;
  trace.info() << "sum is " << c << "\n";
  trace.info() << "absolute value is " << abs(c) << "\n";

  nbok += (abs(c)==4444) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testBIGINTEGERSpace()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "BIGINTEGER Space test..." );
   
  //This space is weird...
  typedef SpaceND<2, DGtal::BigInteger> Space2;
  typedef Space2::Point Point;
  typedef Space2::Point::Coordinate Coordinate;
  typedef HyperRectDomain<Space2> Domain;

  DGtal::BigInteger a, b, c;
  
  a = 1234;
  b = "-5678";
  Point p(a,b);

  typedef FreemanChain<Coordinate> Contour;

  // Construct the Freeman chain
  std::stringstream ss(stringstream::in | stringstream::out);
  ss << "31 16 11121212121212212121212212122122222322323233323333333323333323303330330030300000100010010010001000101010101111" << endl;
  Contour theContour( ss );

  Point p1( 0, 0 );
  Point p2( 31, 31 );

  trace.info() <<"p2.norm()= "<< p2.norm()<<endl;

  Domain domain( p1, p2 );
  Board2D aBoard;
  aBoard << SetMode( domain.className(), "Grid" )
   << domain
   << theContour;

  aBoard.saveSVG("testgmpcontour.svg");


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
  trace.beginBlock ( "Testing class DGtalBIGINTEGER" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testDGtalBIGINTEGER() && testBIGINTEGERSpace(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
