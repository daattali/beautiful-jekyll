
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
 * @file io/boards/dgtalBoard3D-1-points.cpp
 * @ingroup Examples
 * @author Aline MARTIN (\c aline.martin@insa-lyon.fr )
 *
 * @date 2013/06/16
 *
 * An example file named dgtalBoard3D-1-points.
 *
 */

/**
 * Example of digital point export with Display3D.
 *  @see \ref DGtalGLV_OBJExport
 *  \image html  dgtalBoard3D-1-points.png  "Illustration of the resulting exported file (OBJ format visualized with blender)."
 * \example io/boards/dgtalBoard3D-1-points.cpp
 *
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board3D.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example dgtalBoard3D-1-points" );


  Point p1( -3, -2, 0 );
  Point p2( 7, 3 , 6);
  Point p3( -1, -1, -1);
  Point p4(-1, -1, 0 );
  Point p5( 5, 2 , 4);
  Point p6(-3, -6, 0 );
  Point p7( 5, 2 , 3);

  Domain domain(p4, p5);
  DigitalSet shape_set( domain );
  shape_set.insertNew(p6);
  shape_set.insertNew(p7);

  //! [ExampleBoard3DExport]
  Board3D<> board;
  board << SetMode3D(domain.className(), "Paving");
  board << p1 << p2 << p3;
  board << shape_set;
  board.saveOBJ("dgtalBoard3D-1-points.obj");
  //! [ExampleBoard3DExport]

  trace.info()<<" Second"<<std::endl;
  Board3D<> board2;
  board2 << SetMode3D(domain.className(), "Paving");
  board2 << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  board2 << p1 ;
  board2 << CustomColors3D(Color(0, 255,0),Color(0, 0,255));
  board2 << p2 << p3;
  board2 <<  CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  board2 << p6;
  board2.saveOBJ("dgtalBoard3D-1bis-points.obj");



  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
