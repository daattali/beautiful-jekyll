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

/*licenses*
 * @file testSimpleBoard.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/16
 *
 * Functions for testing class SimpleBoard.
 *
 * This file is part of the DGtal library.
 */

//////////////////////////////
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"
#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;
  
///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SimpleBoard.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleBoard()
{
  unsigned int nbok = 0;
  unsigned int nb = 2;

  trace.beginBlock ( "Testing class SimpleBoard" );
  
  Board2D board;

  board.setPenColorRGBi( 0, 0, 0);
  board.drawRectangle( -1, 1, 2.0, 2.0 );
  board.setPenColorRGBi( 0, 0, 255 );
  board.fillCircle( 2, 2, 1 );
  
  

  board.saveSVG( "simpleboard.svg" );
  board.saveFIG( "simpleboard.fig" );
  board.saveEPS( "simpleboard.eps" );
  board.saveTikZ( "simpleboard.tikz" );
  nbok++;

  typedef  PointVector<2,int> Point2D;
  Point2D apoint, p2;
  apoint[0] = 5;
  p2[0] = 1;
  apoint[1] = 8;
  p2[1] = 1;

  board.setPenColorRGBi( 255, 0, 255 );
  board << apoint;

  board.setPenColorRGBi( 255, 0, 0 );
  Display2DFactory::draw(board, apoint, p2);

  board.scale(10);

  board.saveSVG( "pointsimpleboard.svg" );
  board.saveFIG( "pointsimpleboard.fig" );
  board.saveEPS( "pointsimpleboard.eps" );
  board.saveTikZ( "pointsimpleboard.tikz" );
  nbok++;
  trace.endBlock();
  return nbok == nb;
}

bool testDomain()
{
    typedef SpaceND<2> TSpace;
    typedef TSpace::Point Point;
    Point a ( 1, 1);
    Point b ( 15, 15);

    trace.beginBlock ( "HyperRectDomain Iterator" );
    HyperRectDomain<TSpace> myDomain ( a,b );
    
    Board2D board;
    
    board << SetMode( myDomain.className(), "Grid" ) << myDomain;
    board.scale(10);
    board.saveSVG( "domain-grid.svg" );
    board.saveTikZ( "domain-grid.tikz" );
    
    Board2D b2;
    b2 << SetMode( myDomain.className(), "Paving" ) << myDomain;
    b2.scale(10);
    b2.saveSVG( "domain-paving.svg" );
    b2.saveTikZ( "domain-paving.tikz" );
    trace.endBlock();

    PointVector<3,int> pl;
    //An assert should be raised 
    //Display2DFactory::draw(b2, pl);

    return true;
}


bool testImage()
{
  unsigned int nbok = 0;
  unsigned int nb = 1;
  trace.beginBlock ( "Testing Display Image with Board " );
  Board2D board;

  std::string filenameImage1 = testPath + "samples/contourS.png";    
  board.drawImage(filenameImage1, 0, 85, 185, 85); 
  board.saveFIG("boardTestDisplayImage.fig");
  board.saveSVG("boardTestDisplayImage.svg");
  board.saveTikZ("boardTestDisplayImage.tikz" );
#ifdef WITH_CAIRO
  board.saveCairo("boardTestDisplayImageCAIRO.eps", Board2D::CairoEPS );
  board.saveCairo("boardTestDisplayImageCAIRO.pdf", Board2D::CairoPDF );
  board.saveCairo("boardTestDisplayImageCAIRO.png", Board2D::CairoPNG );
#endif
  nbok++;
  trace.endBlock();
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SimpleBoard" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  bool res = testSimpleBoard() && testDomain() && testImage(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
