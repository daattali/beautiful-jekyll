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
 * @file doc-examples/exampleCatch.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/09/20
 *
 * An example file named exampleCatch.
 *
 * This file is part of the DGtal library.
 */
/**
DGtal/Catch examples

@see \ref moduleCatch

\example doc-examples/exampleCatch.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

#include <vector>
#include <list>
#include <set>

//! [exampleCatch-include]
#include "DGtalCatch.h"
//! [exampleCatch-include]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


//! [exampleCatch-example1]
TEST_CASE( "Point Vector Unit tests" )
{

  //Global variables and init for this test case
  typedef PointVector<4, DGtal::int32_t> Point;
  typedef PointVector<4, double> RealPoint;

  DGtal::int32_t t1[] = {1,2,3,4};
  DGtal::int32_t t2[]= {5,4,3,2};
  double t3[]= {1.0,-1.0,2.0,-2.0};

  Point p1( t1 );
  Point p1bis( t1 );
  Point p2( t2 );
  RealPoint p3(t3);

  SECTION("Comparisons")
    {
      REQUIRE( (p1 == p1bis) );
      REQUIRE( p1 < p2 );
    }
  
  SECTION("Min/Max of vector components")
    {
      REQUIRE( (p3.max() == 2.0) );
      REQUIRE( (p3.min() == -2.0) );
      REQUIRE( (*p3.maxElement() == 2.0) );
      REQUIRE( (*p3.minElement() == -2.0) );
    }
  SECTION("Arithmetical Operators")
    {
      REQUIRE( ((p1 + p2) == Point(6,6,6,6)) );
      REQUIRE( ((p1 - p2) == Point(-4,-2,0,2)) );
      REQUIRE( ((p1*2) == Point(2,4,6,8)) );
      REQUIRE( ((2*p1) == Point(2,4,6,8)) );
      REQUIRE( ((-p1) == Point(-1,-2,-3,-4)) );
      REQUIRE( (p1.inf(p2) == Point(1,2,3,2)) );
      REQUIRE( (p1.sup(p2) == Point(5,4,3,4)) );
      REQUIRE( (p1.dot(p2) == 30) );
    }

}
//! [exampleCatch-example1]


//! [exampleCatch-example2]
TEMPLATE_TEST_CASE_3("STL Container test", "Description", T,
                     std::list<int>, std::vector<int>, std::set<int>)
{
  T defaultConstructed;

  SECTION("Size of the default constructed container")
    {
      REQUIRE( ( defaultConstructed.size() == 0 ) ); 
    }

  //Adding a value
  defaultConstructed.insert( defaultConstructed.begin(),  5 );
  
  SECTION("Size after one insert")
    {
      REQUIRE( ( defaultConstructed.size() == 1 ) ); 
    }
}
//! [exampleCatch-example2]


