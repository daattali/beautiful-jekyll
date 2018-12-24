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
 * @file io/boards/dgtalBoard3DTo2D-1-points.cpp
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
 * Example of digital point visualization with Board3DTo2D.
 * @see \ref DGtalGLV_VisualizationDigitalSet
 * \example io/boards/dgtalBoard3DTo2D-1-points.cpp
 * \image html dgtalBoard3DTo2D-1-points.png "Digital point visualization  with Board3DTo2D."
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/io/boards/Board3DTo2D.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main()
{

  Point p1( 0, 0, 0 );
  Point p2( 5, 5 ,5 );
  Point p3( 2, 3, 4 );
  Domain domain( p1, p2 );
  //! [ExampleBoard3DTo2D]
  Board3DTo2D<Space, KSpace> board;
  board << domain;  
  board << p1 << p2 << p3;
  
  board << CameraPosition(2.500000, 2.500000, 16.078199)
        << CameraDirection(0.000000, 0.000000, -1.000000)
        << CameraUpVector(0.000000, 1.000000, 0.000000);
  board << CameraZNearFar(4.578200, 22.578199);

  board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-1-points.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600*2, 400*2);
  //! [ExampleBoard3DTo2D]
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////




