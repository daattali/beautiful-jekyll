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
 * @file io/boards/dgtalBoard3DTo2D-KSCell.cpp
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 31 aout 2011
 * 
 * @brief
 *
 * Simple example of class Board3DTo2D to display KSCell.
 *
 * This file is part of the DGtal library.
 */


/**
 * Khalimsky Signed Cell Visualization (with Board3DTo2D)
 * \image html dgtalBoard3DTo2D-KSCell.png "Khalimsky Signed Cell Visualization (with Board3DTo2D)"
 * \example io/boards/dgtalBoard3DTo2D-KSCell.cpp
 *
 */

///////////////////////////////////////////////////////////////////////////////
//#include <iostream>
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


  KSpace K;
  Point plow(0,0,0);  
  Point pup(3,3,2);
  Domain domain( plow, pup );
  K.init( plow, pup, true );

  Board3DTo2D<> board(K);

  board << SetMode3D( domain.className(), "Paving" );
  board << domain;

  // Drawing cell of dimension 3
  Cell voxelA = K.uCell(Point(1,1,1));
  SCell voxelB = K.sCell(Point(1,1,3));
  board << voxelB << voxelA;

  // drawing cells of dimension 2
  SCell surfelA = K.sCell( Point( 2, 1, 3 ) ); 
  SCell surfelB = K.sCell( Point( 1, 0, 1 ), false ); 
  Cell surfelC = K.uCell( Point( 1, 2, 1 ) ); 
  SCell surfelD = K.sCell( Point( 1, 1, 0 ) );
  Cell surfelE = K.uCell( Point( 1, 1, 2 ) ); 
  board << surfelA << surfelB << surfelC << surfelD << surfelE;

  Cell linelA = K.uCell(Point(2,1 ,2));
  SCell linelB = K.sCell(Point(2,2 ,1));
  SCell linelC = K.sCell(Point(1,2 ,2), false);
  board << linelA << linelB << linelC;

  Cell center = K.uCell(Point(5,5,5));

  // Testing display of oriented surfels:
  SCell ssurfelXZ = K.sCell( Point( 5, 6, 5 ), false ); 
  SCell ssurfelXY = K.sCell( Point( 5, 5, 6 ), false ); 
  SCell ssurfelZY = K.sCell( Point( 6, 5, 5 ), false ); 
  board << center;

  SCell ssurfelXZo = K.sCell( Point( 5, 4, 5 ), false ); 
  SCell ssurfelXYo = K.sCell( Point( 5, 5, 4 ), false ); 
  SCell ssurfelZYo = K.sCell( Point( 4, 5, 5 ), false );  

  board << ssurfelXZ << ssurfelXY << ssurfelZY;
  board << ssurfelXZo << ssurfelXYo << ssurfelZYo;

  // Testing display oriented pointels

  Cell pointelA = K.uCell(Point(2, 2, 2));
  SCell pointelB = K.sCell(Point(4, 4, 4), true);
  SCell pointelC = K.sCell(Point(6, 4, 4), false);
  SCell linelAC = K.sCell(Point(5, 4, 4), false);
  board  << pointelA << pointelB << pointelC << linelAC;

  /*board << CameraPosition(2.69044, 1.73705, -1.89961)
    << CameraDirection(-0.515153, -0.212857, 0.830247)
    << CameraUpVector(0.48806, -0.869135, 0.0800053);*/
    
  board << CameraPosition(3.49239, 3.04746, -1.40276)
    << CameraDirection(-0.605129, -0.454197, 0.653853)
    << CameraUpVector(0.516135, -0.84913, -0.112173);

  //board << SetMode3D(board.className(), "WireFrameMode");
  board.saveCairo("dgtalBoard3DTo2D-KSCell.png", Board3DTo2D<Space, KSpace>::CairoPNG, 600, 400);

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
