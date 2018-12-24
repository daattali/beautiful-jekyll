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
 * @file io/boards/dgtalBoard3DTo2D-4-modes.cpp
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
 * Example of default visualization of a digital point sets with the associated domain (with Board3DTo2D)
 * @see \ref DGtalGLV_ModeExamplesDomain
 * \example io/boards/dgtalBoard3DTo2D-4-modes.cpp
 *\image html visuModeDefault.png "Default visualization of a digital point sets with the associated domain (with Board3DTo2D) "
 *
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/io/boards/Board3DTo2D.h"
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

  //board << SetMode3D( p1.className(), "Grid" );

  board << p1 << p2 << p3 << p4 << p5 << p6 << p0;

  //board << SetMode3D(domain.className(), "PavingGrids");
  board << domain;
  
  board << CameraPosition(0.500000, 0.500000, 11.274194)
   << CameraDirection(0.000000, 0.000000, -1.000000)
   << CameraUpVector(0.000000, 1.000000, 0.000000);
  
  //board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-4-modes.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600, 400);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////




