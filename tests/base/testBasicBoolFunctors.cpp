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
 * @file testBasicBoolFunctors.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Functions for testing class BasicBoolFunctors.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicBoolFunctors.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

#define INBLOCK_TEST(x) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
         << #x << std::endl;

#define INBLOCK_TEST2(x,y) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
  << y << std::endl;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class BasicBoolFunctors.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testBasicBoolFunctors()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );
  // true()
  nbok += trueBF0() == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true() == true" << std::endl;

  // false()
  nbok += falseBF0() == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "false() == false" << std::endl;

  // id( b )
  nbok += identityBF1( true ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "id(true) == true" << std::endl;
  nbok += identityBF1( false ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "id(false) == false" << std::endl;

  // not( b )
  nbok += notBF1( true ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "not(true) == false" << std::endl;
  nbok += notBF1( false ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "not(false) == true" << std::endl;

  // and( b1, b2 )
  nbok += andBF2( true, true ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "and( true, true ) == true" << std::endl;
  nbok += andBF2( false, true ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "and( false, true ) == false" << std::endl;
  nbok += andBF2( true, false ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "and( true, false ) == false" << std::endl;
  nbok += andBF2( false, false ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "and( false, false ) == false" << std::endl;

  // or( b1, b2 )
  nbok += orBF2( true, true ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "or( true, true ) == true" << std::endl;
  nbok += orBF2( false, true ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "or( false, true ) == true" << std::endl;
  nbok += orBF2( true, false ) == true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "or( true, false ) == true" << std::endl;
  nbok += orBF2( false, false ) == false ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "or( false, false ) == true" << std::endl;

  // xor( b1, b2 )
  INBLOCK_TEST2( xorBF2( true, true ) == false, "xor( true, true ) == false" );
  INBLOCK_TEST2( xorBF2( false, true ) == true, "xor( false, true ) == true" );
  INBLOCK_TEST2( xorBF2( true, false ) == true, "xor( true, false ) == true" );
  INBLOCK_TEST2( xorBF2( false, false ) == false, "xor( false, false ) == false" );

  // implies( b1, b2 )
  INBLOCK_TEST2( impliesBF2( true, true ) == true, 
     "implies( true, true ) == true" );
  INBLOCK_TEST2( impliesBF2( false, true ) == true, 
     "implies( false, true ) == true" );
  INBLOCK_TEST2( impliesBF2( true, false ) == false, 
     "implies( true, false ) == false" );
  INBLOCK_TEST2( impliesBF2( false, false ) == true, 
     "implies( false, false ) == true" );
  
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class BasicBoolFunctors" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testBasicBoolFunctors(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
