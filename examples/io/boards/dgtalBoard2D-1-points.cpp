
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
 * @file io/boards/dgtalBoard2D-1-points.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/11/26
 *
 * An example file named dgtalBoard2D-1-points.
 * 
 */

/**
 *   \example io/boards/dgtalBoard2D-1-points.cpp
 *
 * This simple example shows the basic usage of a Board2D to
 * export graphical representations of dgtal objects (here, a
 * HyperRectDomain and three points exported as SVG and EPS).
 * \image html  dgtalboard-1-points.png  "visualization of one of the  resulting export."
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example dgtalBoard2D-1-points" );

  Point p1( -3, -2 );
  Point p2( 7, 3 );
  Point p3( 0, 0 );
  Domain domain( p1, p2 );
  
  Board2D board;
  board << domain << p1 << p2 << p3;

  board.saveSVG("dgtalBoard2D-1-points.svg");
  board.saveEPS("dgtalBoard2D-1-points.eps");
  board.saveTikZ("dgtalBoard2D-1-points.tikz");

#ifdef WITH_CAIRO
  board.saveCairo("dgtalBoard2D-1-points-cairo.pdf", Board2D::CairoPDF);
  board.saveCairo("dgtalBoard2D-1-points-cairo.png", Board2D::CairoPNG);
  board.saveCairo("dgtalBoard2D-1-points-cairo.ps", Board2D::CairoPS);
  board.saveCairo("dgtalBoard2D-1-points-cairo.svg", Board2D::CairoSVG);
#endif
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
