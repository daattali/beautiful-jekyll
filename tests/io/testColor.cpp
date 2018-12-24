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
 * @file testColor.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/11/16
 *
 * Functions for testing class Color.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/Color.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Color.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testColor()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Color ..." );

  Color b(0,0,0,255);
  Color g(32,32,32,255);
  Color gg(64,64,64,255);
  Color w(255,255,255,255);

  trace.info() << " B+G = g "<< b+g<<std::endl;
  nbok += ((b+g)==g) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "add" << std::endl;

  trace.info() << " g+g = gg "<< g*2<< " expected ="<<gg<<std::endl;
  nbok += ((g+g)==gg) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "add (bis)" << std::endl;

  trace.info() << " W+W = w "<< w+w<<std::endl;
  nbok += ((w+w)==w) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "max " << std::endl;

  trace.info() << " g*2 = gg "<< g*2<< " expected ="<<gg<<std::endl;
  nbok += ((g*2)==gg) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "coeff" << std::endl;

  trace.info() << " 1.*red = red "<< 1.0*Color::Red<< " expected ="<<Color::Red<<std::endl;
  nbok += ((1.0*Color::Red)==Color::Red) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "coeff" << std::endl;

  trace.info() << " 2*g = gg "<< 2.0*g<< " expected ="<<gg<<std::endl;
  nbok += ((2*g)==gg) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "coeff" << std::endl;

  //Checking alpha channel
  Color a(0,0,0,64);
  Color aa(0,0,0,32);
  Color c = a+aa;
#ifdef COLOR_WITH_ALPHA_ARITH
  trace.info() << " a+aa = "<< a+aa<<std::endl;
  nbok += (c == Color(0,0,0,96)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "alpha arith (enabled)" << std::endl;
#else
  trace.info() << " a+aa = "<< a+aa<<std::endl;
  nbok += (c == Color(0,0,0,64)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "alpha arith (disabled)" << std::endl;
#endif  

  Color val;
  val.setRGBi(0,0,0,255);
  val += 1.0*Color::Red;
  trace.info() << " val == Color::Red "<< val<<std::endl;
  nbok += (val==Color::Red) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "red" << std::endl;

  

  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Color" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testColor(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
