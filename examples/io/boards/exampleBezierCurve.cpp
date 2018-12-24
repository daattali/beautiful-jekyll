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
 * @file io/boards/exampleBezierCurve.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/04/28
 *
 * An example file named exampleBezierCurve.
 *
 * This file is part of the DGtal library.
 */

/**
 * Example of bezier curve display in Board2D
 * 
 *   @image html exampleBezierCurve.png "visualization of resulting export."
 *  @example io/boards/exampleBezierCurve.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example exampleBezierCurve" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //control points
  typedef PointVector<2,int> Point;
  Point P(0,0), Q(4,4), R(8,0); 

  //display
  Board2D board; 

  //with fill
  board << SetMode(P.className(), "Grid") << P << Q << R; 
  board.drawQuadraticBezierCurve(P[0], P[1], Q[0], Q[1], R[0], R[1]); 

  board.saveSVG("BezierCurve.svg", Board2D::BoundingBox, 5000 ); 
  board.saveEPS("BezierCurve.eps", Board2D::BoundingBox, 5000 ); 
  board.saveTikZ("BezierCurve.tikz", Board2D::BoundingBox, 5000 ); 
  board.saveFIG("BezierCurve.fig", Board2D::BoundingBox, 5000 ); 
#ifdef WITH_CAIRO
  board.saveCairo("BezierCurve.pdf", Board2D::CairoPDF); 
#endif

  board.clear(); 
  //without fill
  board << SetMode(P.className(), "Grid") << P << Q << R; 
  board.setFillColor(Color::None); 
  board.drawQuadraticBezierCurve(P[0], P[1], Q[0], Q[1], R[0], R[1]); 

  board.saveSVG("BezierCurve2.svg", Board2D::BoundingBox, 5000 ); 
  board.saveEPS("BezierCurve2.eps", Board2D::BoundingBox, 5000 ); 
  board.saveTikZ("BezierCurve2.tikz", Board2D::BoundingBox, 5000 ); 
  board.saveFIG("BezierCurve2.fig", Board2D::BoundingBox, 5000 ); 
#ifdef WITH_CAIRO
  board.saveCairo("BezierCurve2.pdf", Board2D::CairoPDF); 
#endif

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
