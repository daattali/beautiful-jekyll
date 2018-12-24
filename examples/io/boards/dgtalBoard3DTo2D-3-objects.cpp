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
 * @file io/boards/dgtalBoard3DTo2D-3-objects.cpp
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 25 mai 2011
 * 
 * @brief
 *
 * Simple example of class Board3DTo2D.
 *
 * This file is part of the DGtal library.
 */

/**
 * Example of 6-18 digital Adjacencies visualization  with Board3DTo2D.
 * @see \ref DGtalGLV_ModeEx
 * \example io/boards/dgtalBoard3DTo2D-3-objects.cpp
 * \image html dgtalBoard3DTo2D-3-objects.png " 6-18 digital Adjacencies visualization  with Board3DTo2D."
 *
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/io/boards/Board3DTo2D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main()
{
  Board3DTo2D<Space, KSpace> board;

  Point p1( 0, 0, 0 );
  Point p2( 10, 10 , 10 );
  Domain domain( p1, p2 );

  DigitalSet shape_set( domain );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( 5, 5, 5 ), 2 );
  Shapes<Domain>::addNorm2Ball( shape_set, Point( 3, 3, 3 ), 2 );
  board <<  CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 25));
  board << shape_set;  

  Object6_18 shape( dt6_18, shape_set );
  board << SetMode3D( shape.className(), "DrawAdjacencies" );
  board << shape;

  Object18_6 shape2( dt18_6, shape_set );
  board << SetMode3D( shape2.className(), "DrawAdjacencies" );
  //board << shape2;
  
  board << CameraPosition(4.000000, 4.000000, 17.578199)
   << CameraDirection(0.000000, 0.000000, -1.000000)
   << CameraUpVector(0.000000, 1.000000, 0.000000);
  
  //board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-3-objects.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600, 400);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////




