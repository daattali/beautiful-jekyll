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
 * @file
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2015/06/06
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testPointVector-catch' <p>
 * Aim: simple test of \ref PointVector with Catch unit test framework.
 */
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include <boost/array.hpp>

#include "DGtalCatch.h"

using namespace DGtal;
using namespace std;


TEST_CASE( "Point Vector Unit tests" )
{
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
      REQUIRE( p1 == p1bis );
      REQUIRE( p1 < p2 );
      
      RealPoint realInitializerlist( { 3.5, 4.2, 2.2, 3.2 } );
      REQUIRE( p1 != realInitializerlist );
    }
  
  SECTION("Min/Max of vector components")
    {
      REQUIRE( p3.max() == 2.0 );
      REQUIRE( p3.min() == -2.0 );
      REQUIRE( *p3.maxElement() == 2.0 );
      REQUIRE( *p3.minElement() == -2.0 );
    }

  Point  aPoint;
  aPoint[ 3 ] =  0;
  aPoint[ 2 ] =  2;
  aPoint[ 1 ] = -1;
  aPoint[ 0 ] =  3;

  SECTION("Testing norms")
    {
      RealPoint normalized = aPoint.getNormalized();
      CAPTURE( normalized );
      REQUIRE( aPoint.norm ( Point::L_1 ) == 6 );
      REQUIRE( aPoint.norm ( Point::L_infty ) == 3 );
      REQUIRE( aPoint.squaredNorm() ==  Approx(aPoint.norm()*aPoint.norm()) );
      REQUIRE( normalized[0] == Approx( 0.801784) );
      REQUIRE( normalized[1] == Approx( -0.267261) );
      REQUIRE( normalized[2] == Approx( 0.534522) );
      REQUIRE( normalized[3] == Approx( 0.0) );
    }

  SECTION("PointVector Iterator")
    {
      PointVector<25,int> aPoint25;
      for (unsigned int i=0;i<25;++i)
        aPoint25[i] = i;
      
      int sum = 0;
      for (PointVector<25,int>::ConstIterator it = aPoint25.begin() ;  it != aPoint25.end(); ++it)
        sum += (*it);
      
      CAPTURE(aPoint25);
      CAPTURE(sum);
      REQUIRE( sum == 300 );
    }

  SECTION("Arithmetical Operators")
    {
      REQUIRE( (p1 + p2) == Point(6,6,6,6) );
      REQUIRE( (p1 - p2) == Point(-4,-2,0,2) );
      REQUIRE( (p1*2) == Point(2,4,6,8) );
      REQUIRE( (2*p1) == Point(2,4,6,8) );
      REQUIRE( (-p1) == Point(-1,-2,-3,-4) );
      REQUIRE( p1.inf(p2) == Point(1,2,3,2) );
      REQUIRE( p1.sup(p2) == Point(5,4,3,4) );
      REQUIRE( p1.dot(p2) == 30 );
    }

  
  SECTION("Testing Containers")
  {
    typedef PointVector<3, int, boost::array<int, 3> > PA6;
    PA6 pa(2,3,4);
    CAPTURE(pa);
    
    typedef PointVector<3, int, std::array<int, 3> > PV6;
    PV6 pv(2,3,4);
    CAPTURE(pv) ;
    
  }
}


/** @ingroup Tests **/
