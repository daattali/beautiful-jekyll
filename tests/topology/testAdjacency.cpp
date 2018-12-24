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
 * @file testAdjacency.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/04
 *
 * Functions for testing class Adjacency.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/topology/MetricAdjacency.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
///////////////////////////////////////////////////////////////////////////////



using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;

/**
 *
 * This file test the standard digital adjacencies, the one based on a
 * metric. We have the classical 4- and 8- adjacencies in 2D, the 6-,
 * 18- and 26- in 3D.
 */

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Adjacency.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testMetricAdjacency()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  typedef SpaceND<3> Space3D;
  typedef Space3D::Point Point;
  typedef Z3i::Adj6 Adj6;
  typedef Z3i::Adj18 Adj18;
  typedef Z3i::Adj26 Adj26;
  Point p( 3, -5, 10 );


  trace.beginBlock ( "Testing neighbors of" );
  Adj6::selfDisplay( trace.info() );
  trace.info() << " p = " << p << std::endl;
  vector<Point> neigh6;
  back_insert_iterator< vector<Point> > bii6( neigh6 );
  Adj6::writeNeighbors( bii6, p );
  nbok += neigh6.size() == 6 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Card(6-neigh): " << neigh6.size() 
         << "== 6 ?" << std::endl;
  trace.beginBlock ( "Enumerating neighbors." );
  unsigned int nb_correct = 0;
  for ( unsigned int i = 0; i < neigh6.size(); ++i )
    {
      if ( Adj6::isProperlyAdjacentTo( p, neigh6[ i ] ) )
  {
    trace.info() << neigh6[ i ] << "* " << std::endl;
    ++nb_correct;
  }
      else
  trace.info() << neigh6[ i ] << "- " << std::endl;
    }
  trace.endBlock();
  nbok += nb_correct == 6 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Within, #proper adjacent : " << nb_correct
         << "== 6 ?" << std::endl;
  trace.endBlock();



  trace.beginBlock ( "Testing neighborhood of" );
  Adj18::selfDisplay( trace.info() );
  trace.info() << " p = " << p << std::endl;
  vector<Point> neigh18;
  back_insert_iterator< vector<Point> > bii18( neigh18 );
  Adj18::writeNeighbors( bii18, p );
  nbok += neigh18.size() == 18 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Card(18-neigh): " << neigh18.size() 
         << "== 18 ?" << std::endl;
  trace.beginBlock ( "Enumerating neighbors." );
  nb_correct = 0;
  for ( unsigned int i = 0; i < neigh18.size(); ++i )
    {
      if ( Adj18::isProperlyAdjacentTo( p, neigh18[ i ] ) )
  {
    trace.info() << neigh18[ i ] << "* " << std::endl;
    ++nb_correct;
  }
      else
  trace.info() << neigh18[ i ] << "- " << std::endl;
    }
  trace.endBlock();
  nbok += nb_correct == 18 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Within, #proper adjacent : " << nb_correct
         << "== 18 ?" << std::endl;
  trace.endBlock();


  trace.beginBlock ( "Testing neighborhood of" );
  Adj26::selfDisplay( trace.info() );
  trace.info() << " p = " << p << std::endl;
  vector<Point> neigh26;
  back_insert_iterator< vector<Point> > bii26( neigh26 );
  Adj26::writeNeighbors( bii26, p );
  nbok += neigh26.size() == 26 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Card(26-neigh): " << neigh26.size() 
         << "== 26 ?" << std::endl;
  trace.beginBlock ( "Enumerating neighbors." );
  nb_correct = 0;
  for ( unsigned int i = 0; i < neigh26.size(); ++i )
    {
      if ( Adj26::isProperlyAdjacentTo( p, neigh26[ i ] ) )
  {
    trace.info() << neigh26[ i ] << "* " << std::endl;
    ++nb_correct;
  }
      else
  trace.info() << neigh26[ i ] << "- " << std::endl;
    }
  trace.endBlock();
  nbok += nb_correct == 26 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Within, #proper adjacent : " << nb_correct
         << "== 26 ?" << std::endl;
  trace.endBlock();

  return nbok == nb;
}


bool testLocalGraphModel()
{
  trace.beginBlock ( "Testing graph model" );
  unsigned int nbok=0,nb=0;

  typedef DGtal::MetricAdjacency<SpaceND<6,int>, 2>  Adj;
  BOOST_CONCEPT_ASSERT(( CUndirectedSimpleLocalGraph<Adj> ));
  
  
  nbok += Adj::bestCapacity() == 72 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "Within, bestCapacity : " << Adj::bestCapacity()
         << "== 72 ?" << std::endl;
  trace.endBlock();

  
  
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Adjacency" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMetricAdjacency() && testLocalGraphModel(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
