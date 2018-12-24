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
 * @file testExpander.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/11
 *
 * Functions for testing class Expander.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/DomainPredicate.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/kernel/sets/DigitalSetConverter.h"
#include "DGtal/topology/MetricAdjacency.h"
#include "DGtal/topology/DomainMetricAdjacency.h"
#include "DGtal/topology/DomainAdjacency.h"
#include "DGtal/topology/DigitalTopology.h"
#include "DGtal/topology/Object.h"
#include "DGtal/graph/Expander.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

#define INBLOCK_TEST(x) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
         << #x << std::endl;

#define INBLOCK_TEST2(x,y) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
  << y << std::endl;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Expander.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testExpander()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  // ------------------------------ Types ------------------------------
  typedef SpaceND< 3 > Z3;
  typedef Z3::Point Point;
  typedef Point::Coordinate Coordinate;
  typedef HyperRectDomain< Z3 > Domain; 
  typedef Domain::ConstIterator DomainConstIterator; 

  typedef MetricAdjacency< Z3, 1 > MetricAdj6;
  typedef MetricAdjacency< Z3, 2 > MetricAdj18;
  typedef DomainAdjacency< Domain, MetricAdj6 > Adj6;
  typedef DomainAdjacency< Domain, MetricAdj18 > Adj18;
  // typedef MetricAdjacency< Z3, 1 > Adj6;
  // typedef MetricAdjacency< Z3, 2 > Adj18;

  typedef DigitalTopology< Adj6, Adj18 > DT6_18;

  typedef DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
  typedef Object<DT6_18, DigitalSet> ObjectType;
  typedef Expander< ObjectType > ObjectExpander;
  // ----------------------- Domain, Topology ------------------------------
  Point p1( -50, -50, -50 );
  Point p2( 50, 50, 50 );
  Domain domain( p1, p2 );

  MetricAdj6 madj6;
  MetricAdj18 madj18;
  Adj6 adj6( domain, madj6 );
  Adj18 adj18( domain, madj18 );
  // Adj6 adj6;
  // Adj18 adj18;

  DT6_18 dt6_18( adj6, adj18, JORDAN_DT );
  // ------------------------------- Object ------------------------------
  Coordinate r = 49;
  double radius = (double) (r+1);
  Point c( 0, 0 );
  Point l( r, 0 );
  DigitalSet ball_set( domain );
  ostringstream sstr;
  sstr << "Creating 3D ball( r < " << radius << " ) ...";
  trace.beginBlock ( sstr.str() );
  for ( DomainConstIterator it = domain.begin(); 
  it != domain.end();
  ++it )
    {
      if ( (*it - c ).norm() < radius )
  // insertNew is very important for vector container.
  ball_set.insertNew( *it );
    }
  trace.endBlock();

  trace.beginBlock ( "Testing Object instanciation and smart copy  ..." );
  ObjectType ball( dt6_18, ball_set );
  ObjectType ball2( ball );
  INBLOCK_TEST( ball.size() == 523155 );
  trace.info() << "ball.size() = " << ball.size() 
         << " 4/3*pi*r^3 = " << ( 4.0*M_PI*radius*radius*radius/3.0 )
         << endl;
  trace.info() << "ball  = " << ball << endl;
  trace.info() << "ball2 = " << ball2 << endl;
  trace.endBlock();

  trace.beginBlock ( "Testing border extraction ..." );
  ObjectType sphere = ball.border();
  INBLOCK_TEST( sphere.size() == 39546 );
  trace.info() << sphere << endl;
  trace.info() << "sphere.size() = " << sphere.size()
         << " 4*pi*r^2 = " << ( 4.0*M_PI*radius*radius )
         << endl;
  trace.endBlock();

  trace.beginBlock ( "Testing expansion by layers in the ball from center..." );
  ObjectExpander expander( ball, c );
  while ( ! expander.finished() )
    {
      trace.info() << expander << std::endl;
      expander.nextLayer();
    }
  nbok += expander.distance() <= sqrt(3.0)*radius ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "expander.distance() = " << expander.distance()
         << " <= " << sqrt(3.0)*radius << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing expansion by layers on the sphere from a point ..." );
  ObjectExpander expander2( sphere, l );
  while ( ! expander2.finished() )
    {
      trace.info() << expander2 << std::endl;
      expander2.nextLayer();
    }
  nbok += expander2.distance() <= sqrt(2.0)*M_PI*radius ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "expander2.distance() = " << expander2.distance()
         << " <= " << sqrt(2.0)*M_PI*radius << std::endl;
  trace.endBlock();

  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Expander" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testExpander(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
