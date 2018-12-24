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
 * @file testBasicMathFunctions.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/26
 *
 * Functions for testing class BasicMathFunctions.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/BasicMathFunctions.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class BasicMathFunctions.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testBasicMathFunctions()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing power by  squaring ..." );

  trace.info() << "power(5,4)= "<< functions::power(5,4) <<std::endl;
  nbok += (functions::power(5,4)==625) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.info() << "power(5.0,4)= "<< functions::power(5.0,4) <<std::endl;
  nbok += (functions::power(5,4)==625.0) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.endBlock();
  trace.beginBlock ( "Testing roundToUpperPowerOfTwo ..." );

  trace.info() << "roundToUpperPowerOfTwo(200)= "<< functions::roundToUpperPowerOfTwo(200) <<std::endl;
  nbok += (functions::roundToUpperPowerOfTwo(200)==256) ? 1 : 0; 
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.info() << "roundToUpperPowerOfTwo(1000)= "<< functions::roundToUpperPowerOfTwo(1000) <<std::endl;
  nbok += (functions::roundToUpperPowerOfTwo(1000)==1024) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.info() << "power(5.0,4)= "<< functions::power(5.0,4) <<std::endl;
  nbok += (functions::power(5,4)==625.0) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class BasicMathFunctions" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testBasicMathFunctions(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
