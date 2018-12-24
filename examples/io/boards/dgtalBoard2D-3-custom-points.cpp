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
 * @file io/boards/dgtalBoard2D-3-custom-points.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/11/26
 *
 * An example file named dgtalboard-3-custom-points.
 *
 * This file is part of the DGtal library.
 */

/**
 *  \example io/boards/dgtalBoard2D-3-custom-points.cpp
 *
 * This example shows you how to modify the style of each drawable
 * elements. It is a matter of creating a custom style class which
 * gives in its method \c setStyle the specific style
 * parameters. Then, you attach this style to your drawable elements
 * with an instance of CustomStyle outputed in the Board2D
 * stream.
 *   \image html  dgtalboard-3-custom-points.png  "visualization of resulting export."
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

///////////////////////////////////////////////////////////////////////////////
struct MyDrawStyleCustomColor : public DrawableWithBoard2D
{
  Color myPenColor;
  Color myFillColor;
  MyDrawStyleCustomColor( const Color & penColor,
        const Color & fillColor )
    : myPenColor( penColor ), myFillColor( fillColor )
  {}

  virtual void setStyle( Board2D & aboard) const
  {
    aboard.setFillColor( myFillColor);
    aboard.setPenColor( myPenColor );
  }
};

int main()
{
  trace.beginBlock ( "Example dgtalBoard2D-3-custom-points" );

  Point p1( -3, -2 );
  Point p2( 7, 3 );
  Point p3( 0, 0 );
  Domain domain( p1, p2 );

  Color red( 255, 0, 0 );
  Color dred( 192, 0, 0 );
  Color green( 0, 255, 0 );
  Color dgreen( 0, 192, 0 );
  Color blue( 0, 0, 255 );
  Color dblue( 0, 0, 192 );
  
  Board2D board;
  board << domain 
  << CustomStyle( p1.className(), new MyDrawStyleCustomColor( red, dred ) )
  << p1
  << CustomStyle( p2.className(), new MyDrawStyleCustomColor( green, dgreen ) )
  << p2
  << CustomStyle( p3.className(), new MyDrawStyleCustomColor( blue, dblue ) )
  << p3;
  board.saveSVG("dgtalBoard2D-3-custom-points.svg");
  board.saveEPS("dgtalBoard2D-3-custom-points.eps");
  board.saveTikZ("dgtalBoard2D-3-custom-points.tikz");

#ifdef WITH_CAIRO
  board.saveCairo("dgtalBoard2D-3-custom-points-cairo.pdf", Board2D::CairoPDF);
  board.saveCairo("dgtalBoard2D-3-custom-points-cairo.png", Board2D::CairoPNG);
  board.saveCairo("dgtalBoard2D-3-custom-points-cairo.ps", Board2D::CairoPS);
  board.saveCairo("dgtalBoard2D-3-custom-points-cairo.svg", Board2D::CairoSVG);
#endif
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
