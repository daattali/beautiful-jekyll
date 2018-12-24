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
 * @author Jérémy Gaillard (\c jeremy.gaillard@insa-lyon.fr )
 * Institut National des Sciences Appliquées - INSA, France
 *
 * @date 2012/07/12
 *
 * Functions for testing class STLMapToVertexMapAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/base/Common.h"
#include "DGtal/graph/CVertexMap.h"
#include "DGtal/graph/STLMapToVertexMapAdapter.h"
#include <map>
///////////////////////////////////////////////////////////////////////////////



using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;

/**
 *
 * This file tests the adaptation of a STL map to a vertex map.
 * 
 */

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Adjacency.
///////////////////////////////////////////////////////////////////////////////

bool testMapToVertexMap()
{
  typedef  Z2i::Point Point;
  typedef  Z2i::Point Vertex;
  typedef int Value;
  typedef map<Vertex, Value> Map;
  typedef STLMapToVertexMapAdapter<Map> VertexMap;
  VertexMap myMap;
  BOOST_CONCEPT_ASSERT((CVertexMap<VertexMap>));
  myMap.setValue(Point(1,1), 10);
  myMap.setValue(Point(2,3), 2);
  
  return (myMap(Point(1,1)) == 10 && myMap(Point(2,3)) == 2);
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class STLMapToVertexMapAdapter" );

  bool res = testMapToVertexMap(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
