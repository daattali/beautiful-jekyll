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
 * @file testMeaningfulScaleAnalysis.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/12/28
 *
 * Functions for testing class MeaningfulScaleAnalysis.
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
#include "DGtal/math/MeaningfulScaleAnalysis.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MeaningfulScaleAnalysis.
///////////////////////////////////////////////////////////////////////////////




struct LogFct{
  double operator()(const double &a) const {
    return log(a);
  }
};
  

TEST_CASE( "Testing MeaningfulScaleAnalysis" )
{
  
  Profile<LogFct> sp (Profile<LogFct>::MEAN);
  sp.init(6);
  
  SECTION("Testing noise level detect of Profile")
    {
      sp.addValue(0,22);
      sp.addValue(1,15);
      sp.addValue(2,8);
      sp.addValue(3,17);
      sp.addValue(4,7);
      sp.addValue(5,2);      

      MeaningfulScaleAnalysis<Profile<LogFct>> msa(sp);
      std::vector< std::pair<unsigned int, unsigned int> > interval;      
      msa.computeMeaningfulScales(interval, 1);
      msa.getSlopeFromMeaningfulScales(0,0,2);
      msa.lowerBoundedNoiseLevel(0,10,2,2,2);
      unsigned int n = msa.noiseLevel();
      REQUIRE( interval[0].first == 1 );
      REQUIRE( interval[0].second == 3 );
      REQUIRE( interval[1].first == 4 );
      REQUIRE( n == 1 );
    }



}

/** @ingroup Tests **/
