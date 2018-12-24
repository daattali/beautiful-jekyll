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
 * @file testTickedColorMap.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/04/04
 *
 * Functions for testing class TickedColorMap.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/colormaps/TickedColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TickedColorMap.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testTickedColorMap()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing TickedCMAP..." );
  
  TickedColorMap<double, HueShadeColorMap<double, 1> > ticked(0.0,100.0);

  ticked.addTick(5.0, 1.0);
  ticked.addTick(9.0, 1.0);
  ticked.finalize();
  trace.info()<<ticked<<std::endl;
  
  Color c = ticked(4.5);
  nbok += (c == Color::White) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "c == white on tick inf.."<< std::endl;

  c = ticked(5.5);
  nbok += (c == Color::White) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "c == white on tick sup.."<< std::endl;
 
  c = ticked(9.5);
  nbok += (c == Color::White) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "c == white on tick sup.. "<< std::endl;

  c = ticked(8.5);
  nbok += (c == Color::White) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "c == white on tick sup.. "<< std::endl;

  
  c = ticked(20.0);
  nbok += (c != Color::White) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "c != white outside.. "<< std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

bool testCMAP()
{
  Board2D board;
  TickedColorMap<double, HueShadeColorMap<double, 1> > ticked(0.0,100.0);
  ticked.addTick(5.0,1.2);
  ticked.addTick(19.0,3);
  ticked.addTick(69.0,3.0);
  ticked.finalize();
  trace.info() << ticked<<std::endl;
  Z2i::Point p;
  
  for(unsigned int i=0; i < 100; i++)
    board<< CustomStyle(p.className(),new CustomColors(ticked(i),ticked(i)))
    << Z2i::Point(i,0);
  board.saveEPS("testTicked.eps");
  
  board.clear();
  TickedColorMap<double, HueShadeColorMap<double, 1> > ticked2(0.0,100.0);
  ticked2.addRegularTicks(10, 1.0);
  ticked2.finalize();
  for(unsigned int i=0; i < 100; i++)
    board<< CustomStyle(p.className(),new CustomColors(ticked2(i),ticked2(i)))
    << Z2i::Point(i,0);
  board.saveEPS("testTicked-regular.eps");
 
  //same with gradient colormap (and ticked.colormap() accessor)
  board.clear();
  TickedColorMap<double, GradientColorMap<double> > ticked3(0.0,100.0);
  ticked3.addRegularTicks(10, 1.0);
  ticked3.finalize();
  ticked3.colormap()->addColor( Color::Black );
  ticked3.colormap()->addColor( Color::Red );
  for(unsigned int i=0; i < 100; i++)
    board<< CustomStyle(p.className(),new CustomColors(ticked3(i),ticked3(i)))
    << Z2i::Point(i,0);
  board.saveEPS("testTicked-gradient-regular.eps");
  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class TickedColorMap" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testTickedColorMap() && testCMAP(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
