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
 * @file testMeasure.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/25
 *
 * Functions for testing class Measure.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"

#include "DGtal/geometry/volumes/estimation/Measure.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Measure.
///////////////////////////////////////////////////////////////////////////////

bool testConcept()
{
  
  return true;
}



/**
 * Example of a test. To be completed.
 *
 */
bool testMeasure()
{
  trace.beginBlock ( "Testing Measure ..." );


  Z3i::Point a(0,0);
  Z3i::Point b(64,64,64);
  Z3i::Point c(32,32,32);
  Z3i::Domain domain(a,b);
  Z3i::DigitalSet set(domain);
  
  Shapes<Z3i::Domain>::euclideanShaper( set,
                                        ImplicitBall<Z3i::Space>( c, 10));
  
  Measure< Z3i::DigitalSet> measure;

  trace.info() << "Input set= "<<set<<std::endl;

  trace.info()<<measure<<std::endl;

  
  measure.init(10, set);
  trace.info() << "Volume (h=10) "<<measure.eval()<<std::endl;
  measure.init(100, set);
  trace.info() << "Volume (h=100) "<<measure.eval()<<std::endl;
  
  trace.info()<<measure<<std::endl;

  trace.endBlock();
  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Measure" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testConcept() && testMeasure(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
