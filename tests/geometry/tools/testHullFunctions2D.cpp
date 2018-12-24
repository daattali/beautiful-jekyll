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
 * @file testHullFunctions2D.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/03
 *
 * Functions for testing hull functions.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/Hull2DHelpers.h"

#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class HullFunctions2D.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testHullFunctions2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  typedef PointVector<2,DGtal::int32_t> Point; 
  typedef std::vector<Point> Container; 

  //orientation functor and predicate
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int32_t> OrientationFunctor; 
  OrientationFunctor orientationFunctor;
  PredicateFromOrientationFunctor2<OrientationFunctor> 
    predicate( orientationFunctor ); 

  //functions namespace
  using namespace functions::Hull2D;

  trace.beginBlock ( "Testing openGrahamScan" );

  trace.info() << "zero point" << endl;
  {
    Container input, output; 
    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if (output.size() == 0)
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "one point" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 1) &&
	 (output.back() == Point(1,1)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "two points" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    input.push_back( Point(1,2) ); 
    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 2) &&
	 (output.at(0) == Point(1,1)) &&
	 (output.at(1) == Point(1,2)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "three points" << endl;
  { 
    Container input, output; 

    //three points CCW-oriented
    input.push_back( Point(0,0) ); 
    input.push_back( Point(5,0) ); 
    input.push_back( Point(10,5) ); 
    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 3) &&
	 (output.at(0) == Point(0,0)) &&
	 (output.at(1) == Point(5,0)) &&
	 (output.at(2) == Point(10,5)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    //three points CW-oriented
    output.clear(); 
    input.at(2) = Point(10,-5);
    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 2) &&
	 (output.at(0) == Point(0,0)) && 
	 (output.at(1) == Point(10,-5)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "several points" << endl;
  {
    Container input, output; 
    input.push_back( Point(0,5) ); 
    input.push_back( Point(0,0) ); 
    input.push_back( Point(1,1) ); 
    input.push_back( Point(2,4) ); 
    input.push_back( Point(3,9) ); 
    input.push_back( Point(4,16) ); 
    input.push_back( Point(5,0) );
 
    openGrahamScan( (input.begin()+1), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 2) &&
	 (output.at(0) == Point(0,0)) &&
	 (output.at(1) == Point(5,0)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    output.clear(); 
    openGrahamScan( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 3) &&
	 (output.at(0) == Point(0,5)) &&
	 (output.at(1) == Point(0,0)) &&
	 (output.at(2) == Point(5,0)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  }

  trace.endBlock();

  trace.beginBlock ( "Testing closedGrahamScanFromVertex" );

  trace.info() << "zero point" << endl;
  {
    Container input, output; 
    closedGrahamScanFromVertex( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if (output.size() == 0)
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "one point" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    closedGrahamScanFromVertex( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 1) &&
  	 (output.back() == Point(1,1)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "two points" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    input.push_back( Point(1,2) ); 
    closedGrahamScanFromVertex( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 2) &&
  	 (output.at(0) == Point(1,1)) &&
  	 (output.at(1) == Point(1,2)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "three points" << endl;
  { 
    //three points CCW-oriented
    Container input, output; 
    input.push_back( Point(0,0) ); 
    input.push_back( Point(5,0) ); 
    input.push_back( Point(10,5) ); 
    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    closedGrahamScanFromVertex( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 3) &&
  	 (output.at(0) == Point(0,0)) &&
  	 (output.at(1) == Point(5,0)) &&
  	 (output.at(2) == Point(10,5)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "taking into account the first point" << endl;
  { 
    Container input, output; 
    input.push_back( Point(0,-1) ); 
    input.push_back( Point(1,0) ); 
    input.push_back( Point(1,5) ); 
    input.push_back( Point(-5,5) ); 
    input.push_back( Point(-5,0) ); 
    input.push_back( Point(-2,1) ); 
    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    closedGrahamScanFromVertex( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 5) &&
  	 (output.at(0) == Point(0,-1)) &&
  	 (output.at(1) == Point(1,0)) &&
  	 (output.at(2) == Point(1,5)) &&
  	 (output.at(3) == Point(-5,5))&&
  	 (output.at(4) == Point(-5,0)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.endBlock();

  trace.beginBlock ( "Testing closedGrahamScanFromAnyPoint" );

  trace.info() << "zero point" << endl;
  {
    Container input, output; 
    closedGrahamScanFromAnyPoint( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if (output.size() == 0)
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "one point" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    closedGrahamScanFromAnyPoint( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 1) &&
  	 (output.back() == Point(1,1)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "two points" << endl;
  {
    Container input, output; 
    input.push_back( Point(1,1) ); 
    input.push_back( Point(1,2) ); 
    closedGrahamScanFromAnyPoint( input.begin(), input.end(), back_inserter( output ), predicate ); 
    if ( (output.size() == 2) &&
  	 (output.at(0) == Point(1,1)) &&
  	 (output.at(1) == Point(1,2)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "three points" << endl;
  { 
    //three points CCW-oriented
    Container input, output; 
    input.push_back( Point(0,0) ); 
    input.push_back( Point(5,0) ); 
    input.push_back( Point(10,5) ); 
    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    closedGrahamScanFromAnyPoint( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 3) &&
  	 (output.at(0) == Point(0,0)) &&
  	 (output.at(1) == Point(5,0)) &&
  	 (output.at(2) == Point(10,5)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.info() << "taking into account the first point" << endl;
  { 
    Container input, output; 
    input.push_back( Point(3,2) ); 
    input.push_back( Point(2,2) ); 
    input.push_back( Point(2,1) ); 
    input.push_back( Point(1,1) );  
    input.push_back( Point(0,1) );
    input.push_back( Point(0,0) ); 
    input.push_back( Point(9,0) ); 
    input.push_back( Point(9,6) ); 
    input.push_back( Point(8,6) ); 
    input.push_back( Point(8,5) ); 
    input.push_back( Point(7,5) );
    input.push_back( Point(7,4) ); 
    input.push_back( Point(6,4) ); 
    input.push_back( Point(5,4) ); 
    input.push_back( Point(5,3) ); 
    input.push_back( Point(4,3) );
    input.push_back( Point(4,2) ); 

    copy( input.begin(), input.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    closedGrahamScanFromAnyPoint( input.begin(), input.end(), back_inserter( output ), predicate ); 

    copy( output.begin(), output.end(), ostream_iterator<Point>( cout, " " ) );
    cout << endl; 

    if ( (output.size() == 5) &&
  	 (output.at(0) == Point(0,0)) &&
  	 (output.at(1) == Point(9,0)) &&
  	 (output.at(2) == Point(9,6)) &&
  	 (output.at(3) == Point(8,6)) &&
	 (output.at(4) == Point(0,1)) )
      nbok++; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  }

  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing hull functions" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testHullFunctions2D(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
