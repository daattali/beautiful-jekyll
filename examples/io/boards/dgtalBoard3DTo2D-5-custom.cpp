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
 * @file io/boards/dgtalBoard3DTo2D-5-custom.cpp
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
 * Example of a custom display (with Board3DTo2D)
 * @see \ref DGtalGLV_Custom
 * \example io/boards/dgtalBoard3DTo2D-5-custom.cpp
 * \image html dgtalBoard3DTo2D-5-custom.png "Example of several custom display  (with Board3DTo2D)." width=5cm
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/io/boards/Board3DTo2D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
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

  Point p1( -1, -1, -2 );
  Point p2( 2, 2, 3 );
  Domain domain( p1, p2 );

  Point p3( 1, 1, 1 );
  Point p4( 2, -1, 3 );
  Point p5( -1, 2, 3 );
  Point p6( 0, 0, 0 );
  Point p0( 0, 2, 1 );

  board << SetMode3D( p1.className(), "PavingWired" );
  board << p1 << p2 << p3;

  //board << SetMode3D( p1.className(), "Grid" );
  board << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  board << p4 << p5 ;
  board << SetMode3D( p1.className(), "Both" );
  board << CustomColors3D(Color(250, 200,0, 100),Color(250, 0,0, 100));
  board << p6;
  board << CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 20));
  board << p0;

  board << SetMode3D(domain.className(), "Paving");
  board << domain;
  board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-5-custom-wireframe.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600*2, 400*2);
  
  board << SetMode3D(board.className(), "SolidMode");
  board.saveCairo("dgtalBoard3DTo2D-5-custom.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600*2, 400*2);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////




