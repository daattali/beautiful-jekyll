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
 * @file testBoard3D.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/04/12
 *
 * Functions for testing class Board3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board3D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Board3D.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testBoard3D()
{
 trace.beginBlock ( "Testing Board3D ..." );

  Point p1( -3, -2, 0 );
  Point p2( 7, 3 , 6);
  Point p3( -1, -1, -1);
  Point p4(-1, -1, 0 );
  Point p5( 5, 2 , 4);
  Point p6(-3, -6, 0 );
  Point p7( 5, 2 , 3);

  Domain domain(p6, p7);
  DigitalSet shape_set( domain );
  shape_set.insertNew(p6);
  shape_set.insertNew(p7);

  Board3D<> board;
  board << SetMode3D(domain.className(), "Paving");
  board << p1 << p2 << p3;
  board << shape_set;
  board.saveOBJ("dgtalBoard3D-1-points.obj");

  trace.info()<<" Second"<<std::endl;
  Board3D<> board2;
  board2 << SetMode3D(domain.className(), "Paving");
  board2 << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  board2 << p1 ;
  board2 << CustomColors3D(Color(0, 255,0),Color(0, 255,0));
  board2 << p2 << p3;
  board2 <<  CustomColors3D(Color(0, 0,255),Color(0, 0,255));
  board2 << p6;
 
  board2.saveOBJ("dgtalBoard3D-1bis-points.obj");

  
  return true;
}

bool testQuadNorm()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing Board3D Quads ..." );



  Point p1( 0, 0, 0 );
  Point p2( 0, 1 , 0);
  Point p3( 1, 1, 0);
  Point p4(1, 0, 0 );
  Point p5( 2, 0 , 0);
  Point p6( 2, 1, 0);
  RealVector n(1,1,1);
  RealVector n2(0,1,1);

  KSpace k;

  k.init(Point(2,2,2), Point(4,4,4), true);

  Board3D<Space,KSpace> board(k);
  board << CustomColors3D(Color(0, 255,0),Color(0, 255, 0));
  board.addQuadWithNormal(p1,p2,p3,p4, n.getNormalized(), true);
  board << CustomColors3D(Color(0, 0, 255),Color(0, 0, 255));
  board.addQuadWithNormal(p4,p5,p6,p3, n2.getNormalized(), true);

  Cell surfel = k.uCell( Point( 4,5,5) );
  Display3DFactory<Space,KSpace>::drawUnorientedSurfelWithNormal( board, surfel, n2.getNormalized());

  board.saveOBJ("dgtalBoard3D.quad.obj");


  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}


bool testNormaliation()
{
  trace.beginBlock ( "Testing normalization ..." );

  Point p1( 0, 0, 0 );
  Point p2( 0, 10 , 0);
  Point p3( 10, 10, 0);
  Point p4(10, 0, 100 );
  Point p5( 20, 0 , 0);
  Point p6( 20, 10, 0);
  
  KSpace k;

  k.init(Point(2,2,2), Point(4,4,4), true);

  Board3D<Space,KSpace> board(k);
  
  board << p1<<p2<<p3<<p4; 

  board.saveOBJ("dgtalBoard3D-norm.obj", true);
  board.saveOBJ("dgtalBoard3D-wonorm.obj");

  trace.endBlock();

  return true;
}


bool testShapes()
{
 trace.beginBlock ( "Testing shapes ..." );

  RealPoint p1( 0, 0, 0 );
  RealPoint p2(10, 10, 0);

  Board3D<Space,KSpace> board;

  board.setLineColor(Color::Red);
  board.addLine(p1,p2, 0.5);
  
  board.saveOBJ("dgtalBoard3D-line.obj");

  trace.endBlock();

  return true;
}

  

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Board3D" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

bool res = testBoard3D() && testQuadNorm()
                  && testNormaliation()
                  && testShapes(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
