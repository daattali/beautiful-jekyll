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
 * @file testMorton.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/10
 *
 * Functions for testing class Morton.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/images/Morton.h"
#include "DGtal/base/Bits.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Morton.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testMorton()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Morton codes ..." );
  
  typedef PointVector<2,DGtal::int32_t> Point;
  typedef DGtal::uint64_t HashKey;
  
  Point p(0,0), pbis;
  HashKey h, h2;
  HashKey children[4];

  Morton<HashKey,Point> morton;

  trace.info() << endl;
  
  morton.interleaveBits( p , h );
  trace.info() << p << h << " = "<< Bits::bitString( h )<<endl;
  trace.info() << "Key (level2)= "<< Bits::bitString(  h2=morton.keyFromCoordinates( 2, p ))<<endl;
  nbok += (h == 0) ? 1 : 0; 
  nb++;

  morton.coordinatesFromKey( h2 , pbis);
  trace.info() << "Point from code= "<<pbis<<endl;
  nbok += (p == pbis) ? 1 : 0; 
  nb++;

  trace.info()<<endl;

  Point p2(2,3);
  morton.interleaveBits( p2 , h );
  trace.info() << p2<<" "<< h << " = "<< Bits::bitString( h )<<endl;
  trace.info() << "Key (level2)= "<< Bits::bitString(  h2 = morton.keyFromCoordinates( 2, p2 ))<<endl;
   nbok += (h == 14) ? 1 : 0; 
  nb++;

  morton.coordinatesFromKey( h2 , pbis);
  trace.info() << "Point from code= "<<pbis<<endl;
  nbok += (p2 == pbis) ? 1 : 0; 
  nb++;

  trace.beginBlock("Testing children...");
  h2 = morton.keyFromCoordinates( 2, p2);
  morton.childrenKeys(h2, children);
  for(unsigned int k=0; k<4;k++)
    trace.info()<<"child["<<k<<"]= "<<children[k]<<"  "<< Bits::bitString( children[k])<<endl;
  trace.endBlock();

  trace.beginBlock("getKey Benchmark");

  Point p3(0,0);
  DGtal::uint64_t sum=0;
  for(unsigned int k=0; k < 1000000 ;k++)
    {
      p3[1] = k/1000;
      p3[0] = k %1000;
      sum += morton.keyFromCoordinates(32,p);
    }
  trace.endBlock();
  if (sum == 345)
    trace.info() << "Compiler trick"<<endl;
  
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  trace.warning() << "Log2(64)=" <<LOG2<64>::VALUE<<endl;
  trace.warning() << "Log2(1)=" <<LOG2<sizeof(int)>::VALUE<<endl;
 
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Morton" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMorton(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
