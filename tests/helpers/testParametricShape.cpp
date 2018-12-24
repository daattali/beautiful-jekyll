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
 * @file testImplicitShape.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/22
 *
 * Functions for testing class ImplicitShape.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/parametric/Ball2D.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ParametricShape.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testParametricShape()
{
  trace.beginBlock ( "Testing parametric shaper ..." );
  Z2i::Point a(0,0);
  Z2i::Point b(64,64);
  Z2i::Space::RealPoint c(32.0,32.0);
  Z2i::Point cc(32,32);

  Board2D board;
  
  Z2i::Domain domain(a,b);
  Z2i::DigitalSet set(domain);
  
  Shapes<Z2i::Domain>::euclideanShaper( set,
                                        Ball2D<Z2i::Space>( cc, 10));
  
  Z2i::Point lower,upper;
  set.computeBoundingBox(lower,upper);

  trace.info()<<"Generated set: "<<set<<" lowerBound="<<lower
        <<" upperBound="<<upper<<std::endl;

  board << set;
  board.saveSVG("parametricball.svg");

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImplicitShape" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testParametricShape(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
