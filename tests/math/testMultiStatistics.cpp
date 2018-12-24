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
 * @file testMultiStatistics.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/11/10
 *
 * Functions for testing class MultiStatistics.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/MultiStatistics.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MultiStatistics.
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing MultiStatistics" )
{  
  MultiStatistics stats (100, false);
  for(unsigned int i = 0; i< 100; i++)
    {
      for(unsigned int j = 0; j<= i; j++)
        {
          stats.addValue(i, j);
        }
    }
  stats.terminate();
    
  SECTION("Testing multiStatics estimated quantities without saving the data")
    {
      unsigned int val = 50;
      REQUIRE( stats.max(val) == val );      
      REQUIRE( stats.min(val) == 0 );      
      REQUIRE( stats.mean(val) == val/2.0  );      
      val = 31;
      REQUIRE( stats.max(val) == val );      
      REQUIRE( stats.min(val) == 0 );      
      REQUIRE( stats.mean(val) == val/2.0  );      
    }

  MultiStatistics stats2 (100, true);
  for(unsigned int i = 0; i< 100; i++)
    {
      for(unsigned int j = 0; j<= i; j++)
        {
          stats2.addValue(i, j);
        }
    }
  stats2.terminate();

  SECTION("Testing multiStatics estimated quantities with saving the data")
    {
      unsigned int val = 12;
      REQUIRE( stats2.max(val) == val );      
      REQUIRE( stats2.min(val) == 0 );      
      REQUIRE( stats2.mean(val) == val/2.0  );      
      REQUIRE( stats2.median(val) == ((val+1)/2)  );      
      val = 33;
      REQUIRE( stats2.max(val) == val );      
      REQUIRE( stats2.min(val) == 0 );      
      REQUIRE( stats2.mean(val) == val/2.0  );      
      REQUIRE( stats2.median(val) == ((val+1)/2) );            
    }


  MultiStatistics stats3 (100, true);
  for(unsigned int i = 0; i< 100; i++)
    {
      std::vector<double> vectValues; 
      for(unsigned int j = 0; j<= i; j++)
        {
          vectValues.push_back(j);
        }
      stats3.addValues(i, vectValues.begin(), vectValues.end());
    }
  stats3.terminate();

  SECTION("Testing feature math of MultiStatistics with saving data")
    {
      unsigned int val = 12;
      REQUIRE( stats3.max(val) == val );      
      REQUIRE( stats3.min(val) == 0 );      
      REQUIRE( stats3.mean(val) == val/2.0  );      
      REQUIRE( stats3.median(val) == ((val+1)/2)  );      
      val = 33;
      REQUIRE( stats3.max(val) == val );      
      REQUIRE( stats3.min(val) == 0 );      
      REQUIRE( stats3.mean(val) == val/2.0  );      
      REQUIRE( stats3.median(val) == ((val+1)/2) );            
    }


}

/** @ingroup Tests **/
