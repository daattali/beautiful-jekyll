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
 * @file testPointHashFunctions.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/06/14
 *
 * Functions for testing class PointHashFunctions.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtalCatch.h"

#include "DGtal/kernel/PointVector.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/PointHashFunctions.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;



TEST_CASE("Hash functions on DGtal::Point")
{
  Z3i::Point p(0,0,0);
  Z3i::Point q(10,0,0);
  Z3i::Point p_copy(0,0,0);
  std::hash<Z3i::Point> myhashcpp11;
  
  SECTION("Identity test")
    {
      REQUIRE( myhashcpp11(p) == myhashcpp11(p_copy) );
    }

  
  SECTION("Difference test")
    {
      REQUIRE( myhashcpp11(p) != myhashcpp11(q) );
    }
    
  SECTION("Higher dimension identity test")
    {
      typedef PointVector<26,int> Point26;
      Point26 pp=Point26::diagonal(12),
        qq=(Point26::diagonal(11) + Point26::diagonal(1)),
        rr=Point26::diagonal(13);

      std::hash<Point26> myhash26cpp11;
      
      REQUIRE( myhash26cpp11(pp) == myhash26cpp11(qq) );
      REQUIRE( myhash26cpp11(pp) != myhash26cpp11(rr) );
    }
}
