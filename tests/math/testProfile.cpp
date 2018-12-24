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
 * @file testProfile.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/11/08
 *
 * Functions for testing class Profile.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/Profile.h" 
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Profile.
///////////////////////////////////////////////////////////////////////////////

struct LogFct{
  double operator()(const double &a) const {
    return log(a);
  }
};

TEST_CASE( "Testing Profile" )
{
  
  Profile<LogFct> sp(Profile<LogFct>::MEAN);
  sp.init(5);
  
  SECTION("Testing basic add of Profile")
    {
      sp.addValue(0, 10.0);
      sp.addValue(1, 10.0);
      sp.addValue(2, 10.0);
      sp.addValue(3, 10.0);
      sp.addValue(4, 10.0);
      std::vector<double> x;
      std::vector<double> y;
      sp.getProfile(x, y);
      REQUIRE( x[3] == Approx(log(4)) );
      REQUIRE( y[3] == Approx(log(10.0)) );
    }
  
  Profile<> sp2(Profile<>::MAX);
  sp2.init(3, true);

  SECTION("Testing Profile (with max/median)")
    {
      sp2.addValue(0, 1);
      sp2.addValue(0, 3);
      sp2.addValue(0, 2);
      sp2.addValue(1, 13);
      sp2.addValue(1, 2);
      sp2.addValue(1, 1);
      sp2.addValue(2, 4);
      std::vector<double> x;
      std::vector<double> y;
      sp2.getProfile(x, y);
      REQUIRE( x[0] == 1 );
      REQUIRE( y[0] == 3);
      sp2.setType(Profile<>::MIN);
      x.clear();
      y.clear();
      sp2.getProfile(x, y);
      REQUIRE( x[1] == 2 );
      REQUIRE( y[1] == 1);
      sp2.setType(Profile<>::MEDIAN);
      x.clear();
      y.clear();
      sp2.getProfile(x, y);
      REQUIRE( x[0] == 1 );
      REQUIRE( y[0] == 2);
    }

}

/** @ingroup Tests **/
