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
 * @file testPolarPointComparatorBy2x2DetComputer.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/04
 *
 * Functions for testing class PolarPointComparatorBy2x2DetComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class PolarPointComparatorBy2x2DetComputer.
///////////////////////////////////////////////////////////////////////////////
/**
 *
 */
bool testPolarPointComparatorBy2x2DetComputer()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );

  typedef PointVector<2,DGtal::int32_t> Point;
 
  Point origin(0,0); 
  functors::PolarPointComparatorBy2x2DetComputer<Point> comp( origin ); 
  trace.info() << comp << endl;

  //same half-plane
  trace.info() << "same half-plane" << endl;
  if ( comp( Point(2,1), Point(1,2) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( ! comp( Point(1,2), Point(2,1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(2,1), Point(-1,2) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(1,-2), Point(2,-1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;
 
  //different half-plane
  trace.info() << "different half-plane" << endl;
  if ( comp( Point(1,2), Point(2,-1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( ! comp( Point(2,-1), Point(1,2) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //y-coordinate equal to 0
  trace.info() << "y-coordinate == 0" << endl;
  if ( comp( Point(1,0), Point(3,3) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( ! comp( Point(3,3), Point(1,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(3,3), Point(-1,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(1,0), Point(3,-3) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //aligned
  trace.info() << "aligned points" << endl;
  if ( ! comp( Point(3,3), Point(1,1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(1,1),  Point(3,3) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( ! comp( Point(-3,-3), Point(1,1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //y-coordinate equal to 0 AND aligned
  trace.info() << "aligned points on the horizontal axis" << endl;
  if ( comp( Point(1,0),  Point(5,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

 if ( ! comp( Point(5,0),  Point(1,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

 if ( comp( Point(1,0),  Point(-5,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

 if ( comp( Point(5,0),  Point(-5,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

 if ( ! comp( Point(-5,0),  Point(5,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

 if ( comp( Point(-1,0),  Point(-5,0) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //degenerated
  trace.info() << "point equality" << endl;
  if ( comp( Point(0,0),  Point(3,3) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( comp( Point(0,0),  Point(-3,-3) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if ( ! comp( Point(2,1),  Point(2,1) ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();
  
  return nbok == nb;
}

/**
 *
 */
bool testSort()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );

  typedef PointVector<2,DGtal::int32_t> Point;
  Point origin(0,0); 
 
  std::vector<Point> g, v; 
  //data
  v.push_back( Point(3,4) );
  v.push_back( Point(5,0) ); 
  v.push_back( Point(4,3) );
  v.push_back( Point(0,5) ); 
  v.push_back( Point(-3,-4) );
  v.push_back( Point(-5,0) ); 
  v.push_back( Point(-4,-3) );
  v.push_back( Point(0,-5) );
  v.push_back( Point(3,-4) );
  v.push_back( Point(4,-3) );
  v.push_back( Point(-3,4) );
  v.push_back( Point(-4,3) );
  //ground truth
  g.push_back( Point(5,0) ); 
  g.push_back( Point(4,3) );
  g.push_back( Point(3,4) );
  g.push_back( Point(0,5) ); 
  g.push_back( Point(-3,4) );
  g.push_back( Point(-4,3) );
  g.push_back( Point(-5,0) ); 
  g.push_back( Point(-4,-3) );
  g.push_back( Point(-3,-4) );
  g.push_back( Point(0,-5) );
  g.push_back( Point(3,-4) );
  g.push_back( Point(4,-3) );
  
  //sort
  functors::PolarPointComparatorBy2x2DetComputer<Point> comp( origin ); 
  std::sort(v.begin(), v.end(), comp); 
  std::copy(v.begin(), v.end(), ostream_iterator<Point>( std::cout, " " ) ); 
  std::cout << std::endl; 

  if ( std::equal(v.begin(), v.end(), g.begin()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //with a different pole
  comp.setPole( Point(5,0) ); 
  std::sort(v.begin(), v.end(), comp); 
  std::copy(v.begin(), v.end(), ostream_iterator<Point>( std::cout, " " ) ); 
  std::cout << std::endl; 

  if ( std::equal(v.begin(), v.end(), g.begin()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class PolarPointComparatorBy2x2DetComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testPolarPointComparatorBy2x2DetComputer()
    && testSort(); 

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
