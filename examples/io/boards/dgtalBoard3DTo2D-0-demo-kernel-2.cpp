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
 * @file io/boards/dgtalBoard3DTo2D-0-demo-kernel-2.cpp
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 25 mai 2011
 * 
 * @brief
 *
 * An example file named demo-kernel-domain.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/io/boards/Board3DTo2D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  typedef DGtal::SpaceND<3, DGtal::int32_t> MySpace;
  typedef MySpace::Point MyPoint;
  typedef HyperRectDomain<MySpace> MyDomain;

  MyPoint p1( 0, 0, 0 );
  MyPoint p2( 5, 5 ,5 );
  MyPoint p3( 2, 3, 4 );
  MyDomain domain( p1, p2 );

  Board3DTo2D<> board;

  board << domain;  
  board << p1 << p2 << p3;
  
  board << CameraPosition(2.500000, 2.500000, 16.078199)
   << CameraDirection(0.000000, 0.000000, -1.000000)
   << CameraUpVector(0.000000, 1.000000, 0.000000);
  
  board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-0-demo-kernel-2.png", Board3DTo2D<>::CairoPNG, 600, 400);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
