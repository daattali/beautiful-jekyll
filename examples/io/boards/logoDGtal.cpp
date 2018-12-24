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
 * @file io/boards/logoDGtal.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * CNRS, LIRIS UMR 5205, Université de Lyon, France
 *
 * @date 2012/04/19
 * 
 */


/**
 *  \example io/boards/logoDGtal.cpp
 * 
 *  Simple example to generate DGtal logo in DGtal.
 *  \image html  logo_DGtal_small.png   "visualization of resulting export."
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
  trace.beginBlock ( "Generate DGtal logo (without drop shadow)" );

  //! [logoDGtal-main]
  Point p1( 0,0 );
  Point p2( 26, 8 );
  Domain domain( p1, p2 );
 
  Board2D board;
  board << SetMode( domain.className(), "Paving" ) << domain;
  board << CustomStyle( p1.className(), 
                        new CustomPen( Color(0,0,0), Color(180,180,180), 2.5, 
                                       Board2D::Shape::SolidStyle,
                                       Board2D::Shape::RoundCap,
                                       Board2D::Shape::RoundJoin ))
        << Point(1,1) << Point(1,2) << Point(1,3)
        << Point(1,4) << Point(1,5) << Point(1,6)
        << Point(1,7) << Point(2,1) << Point(3,1) << Point(4,1)
        << Point(4,2) << Point(5,2) << Point(5,3)
        << Point(5,4) << Point(5,5) << Point(5,6)
        << Point(4,6) << Point(4,7) << Point(3,7) 
        << Point(2,7) << Point(9,1) << Point(9,2)
        << Point(8,2) << Point(8,3)
        << Point(8,4) << Point(8,5) << Point(8,6) 
        << Point(9,6) << Point(9,7) << Point(10,7) 
        << Point(11,7) << Point(10,1) << Point(11,1) << Point(12,1)
        << Point(12,2) << Point(12,3) << Point(12,4) << Point(11,4);      
  
  board << CustomStyle( p1.className(), 
                        new CustomPen( Color(0,0,0), Color(0,0,0), 1.0, 
                                       Board2D::Shape::SolidStyle,
                                       Board2D::Shape::RoundCap,
                                       Board2D::Shape::RoundJoin ))
        << Point(15,1) << Point(16,1) << Point(17,1)
        << Point(15,2) << Point(15,3) << Point(15,4)
        << Point(15,5) << Point(16,4)
        << Point(19,1) << Point(21,1) << Point(20,1) << Point(22,1)
        << Point(19,2) << Point(21,2)
        << Point(19,3) << Point(20,3) << Point(21,3)
        << Point(24,1) << Point(25,1)
        << Point(24,2) << Point(24,3) << Point(24,4) << Point(24,5);
  
  board.saveSVG("logoDGtal.svg");
  //! [logoDGtal-main]

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
