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
 * @file testDigitalMetricAdapter.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/07/02
 *
 * Functions for testing class DigitalMetricAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/CDigitalMetricSpace.h"
#include "DGtal/geometry/volumes/distance/DigitalMetricAdapter.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DigitalMetricAdapter.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testConcepts()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef Z2i::L2Metric L2;
  L2 l2;
  typedef DigitalMetricAdapter<L2> Adapted;

  Adapted adapted(l2);
  
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalMetricSpace<Adapted> ));
  
  return nbok == nb;
}/**
 * Example of a test. To be completed.
 *
 */
bool testVal()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef Z2i::L2Metric L2;
  L2 l2;
  typedef DigitalMetricAdapter<L2> Adapted;
  Adapted adapted(l2);

  BOOST_CONCEPT_ASSERT(( concepts::CDigitalMetricSpace<Adapted> ));

  L2::Point a(0,0), b(5,2);

  Adapted::Value d = adapted(a,b);
  trace.info() << "distance= "<< l2(a,b)<< " and adapted= "<< d << std::endl;
  nbok += (d == 6) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << std::endl;
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DigitalMetricAdapter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testConcepts() && testVal(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
