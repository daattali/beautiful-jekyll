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
 * @file testObject.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/08
 *
 * Functions for testing class Object.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cmath>
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
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;

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
// Functions for testing class Object.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testObject()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND< 2 > Z2;
  typedef Z2::Point Point;
  typedef Point::Coordinate Coordinate;
  typedef HyperRectDomain< Z2 > DomainType;
  Point p1(  -449, -449  );
  Point p2( 449, 449  );
  DomainType domain( p1, p2 );

  // typedef DomainMetricAdjacency< DomainType, 1 > Adj4;
  // typedef DomainMetricAdjacency< DomainType, 2 > Adj8;
  typedef MetricAdjacency< Z2, 1 > MetricAdj4;
  typedef MetricAdjacency< Z2, 2 > MetricAdj8;
  typedef DomainAdjacency< DomainType, MetricAdj4 > Adj4;
  typedef DomainAdjacency< DomainType, MetricAdj8 > Adj8;
  typedef DigitalTopology< Adj4, Adj8 > DT48;
  typedef DigitalSetSelector < DomainType, MEDIUM_DS + HIGH_BEL_DS >::Type
  MediumSet;
//   typedef DigitalSetSelector< DomainType, SMALL_DS >::Type
//     MediumSet;
  typedef Object<DT48, MediumSet> ObjectType;
  typedef ObjectType::SmallSet SmallSet;
  typedef Object<DT48, SmallSet> SmallObjectType;
  typedef ObjectType::Size Size;

  // Adj4 adj4( domain );
  // Adj8 adj8( domain );
  MetricAdj4 madj4;
  MetricAdj8 madj8;
  Adj4 adj4( domain, madj4 );
  Adj8 adj8( domain, madj8 );
  DT48 dt48( adj4, adj8, JORDAN_DT );

  Coordinate r = 449;
  double radius = (double) (r + 1);
  Point c(  0, 0  );
  Point l(  r, 0  );
  MediumSet disk( domain );
  ostringstream sstr;
  sstr << "Creating disk( r < " << radius << " ) ...";
  trace.beginBlock ( sstr.str() );
  for ( DomainType::ConstIterator it = domain.begin();
      it != domain.end();
      ++it )
  {
    if ( (*it - c ).norm() < radius ) // 450.0
      // insertNew is very important for vector container.
      disk.insertNew( *it );
  }
  trace.endBlock();

  trace.beginBlock ( "Testing Object instanciation and smart copy  ..." );
  ObjectType disk_object( dt48, disk );
  nbok += disk_object.size() == 636101 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Disk (r=450.0) " << disk_object << std::endl;
  trace.info() << "  size=" << disk_object.size() << std::endl;
  ObjectType disk_object2( disk_object );
  nbok += disk_object2.size() == 636101 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Disk2 (r=450.0) " << disk_object2 << std::endl;
  trace.info() << "  size=" << disk_object2.size() << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing copy on write system ..." );
  trace.info() << "Removing center point in Disk." << std::endl;
  disk_object.pointSet().erase( c );
  disk_object2.pointSet().insert( c );
  nbok += disk_object.size() == 636100 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Disk - c (r=450.0) " << disk_object << std::endl;
  trace.info() << "  size=" << disk_object.size() << std::endl;
  nbok += disk_object2.size() == 636101 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Disk2 + c (r=450.0) " << disk_object2 << std::endl;
  trace.info() << "  size=" << disk_object2.size() << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing neighborhoods ..." );
  Object<DT48, SmallSet> neigh = disk_object.neighborhood( c );
  nbok += neigh.size() == 4 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "N_4(Disk, c).size() = " << neigh.size()
  << " == 4" << std::endl;
  neigh = disk_object.properNeighborhood( l );
  nbok += neigh.size() == 3 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "N*_4(Disk, " << l << ").size() = " << neigh.size()
  << " == 3" << std::endl;
  Size size = disk_object.properNeighborhoodSize( l );
  nbok += size == 3 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "#N*_4(Disk, " << l << ") = " << size
  << " == 3" << std::endl;

  neigh = disk_object2.neighborhood( c );
  nbok += neigh.size() == 5 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "N_4(Disk2, c).size() = " << neigh.size()
  << " == 5" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing set converters ..." );
  DigitalSetConverter<SmallSet>::assign
  ( neigh.pointSet(), disk_object.pointSet() );
  nbok += neigh.size() == 636100 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "neigh = disk_object, size() = " << neigh.size()
  << " == 636100" << std::endl;
  SmallObjectType neigh2 = disk_object2.neighborhood( c );
  DigitalSetConverter<SmallSet>::assign
  ( neigh.pointSet(), neigh2.pointSet() );
  nbok += neigh.size() == 5 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "neigh = N_4(Disk2, c), size() = " << neigh.size()
  << " == 5" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing border extraction ..." );
  ObjectType bdisk = disk_object.border();
  nbok += bdisk.size() == 3372 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Border(Disk, c), size() = " << bdisk.size()
  << " == 3372" << std::endl;
  ObjectType bdisk2 = disk_object2.border();
  nbok += bdisk2.size() == 3364 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Border(Disk2, c), size() = " << bdisk2.size()
  << " == 3364" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing expansion by layers on the boundary ..." );
  typedef Expander< ObjectType > ObjectExpander;
  ObjectExpander expander( bdisk, *(bdisk.pointSet().begin()) );
  while ( ! expander.finished() )
  {
    nbok += expander.layer().size() <= 2 ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << "expander.layer.size() <= 2 "
    << expander << std::endl;
    expander.nextLayer();
  }
  trace.endBlock();

  trace.beginBlock ( "Testing expansion by layers on the disk from center..." );
  ObjectExpander expander2( disk_object2, c );
  while ( ! expander2.finished() )
  {
    trace.info() << expander2 << std::endl;
    expander2.nextLayer();
  }
  nbok += expander2.distance() <= sqrt(2.0) * radius ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "expander.distance() = " << expander2.distance()
  << " <= " << sqrt(2.0)*radius << std::endl;
  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testObject3D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef SpaceND<  3 > Z3;
  typedef MetricAdjacency< Z3, 1 > Adj6;
  typedef MetricAdjacency< Z3, 2 > Adj18;
  typedef DigitalTopology< Adj6, Adj18 > DT6_18;
  typedef Z3::Point Point;
  typedef HyperRectDomain< Z3 > Domain;
  typedef Domain::ConstIterator DomainConstIterator;
  typedef DigitalSetSelector < Domain, BIG_DS + HIGH_BEL_DS >::Type DigitalSet;
  typedef Object<DT6_18, DigitalSet> ObjectType;
  Adj6 adj6;
  Adj18 adj18;
  DT6_18 dt6_18( adj6, adj18, JORDAN_DT );

  Point p1( -50, -50, -50 );
  Point p2( 50, 50, 50 );
  Domain domain( p1, p2 );
  Point c( 0, 0, 0 );
  Point d( 10, 2, 0 );

  trace.beginBlock ( "Testing 3D Object instanciation and smart copy  ..." );
  trace.info() << "Creating diamond (r=45)" << endl;
  // diamond of radius 30
  DigitalSet diamond_set( domain );
  for ( DomainConstIterator it = domain.begin(); it != domain.end(); ++it )
  {
    if ( (*it - c ).norm1() <= 45 )
      diamond_set.insertNew( *it );
  }
  ObjectType diamond( dt6_18, diamond_set );
  trace.info() << "Cloning diamond" << endl;
  // The following line takes almost no time.
  ObjectType diamond_clone( diamond );
  // Since one of the objects is modified, the set is duplicated at the following line
  trace.info() << "Removing two points " << c << " and " << d << endl;
  diamond_clone.pointSet().erase( c );
  diamond_clone.pointSet().erase( d );

  trace.info() << "Inserting into vector<Object>" << endl;
  vector<ObjectType> objects;
  back_insert_iterator< vector< ObjectType > > inserter( objects );
  *inserter++ = diamond;
  *inserter++ = diamond_clone;

  for (  vector<ObjectType>::const_iterator it = objects.begin();
      it != objects.end();
      ++it )
    trace.info() << "- objects[" << (it - objects.begin() ) << "]"
    << " = " << *it << endl;

  INBLOCK_TEST( objects[ 0 ].size() == ( objects[ 1 ].size() + 2 ) );
  INBLOCK_TEST( objects[ 0 ].size() == 125671 );
  trace.endBlock();

  trace.beginBlock ( "Testing connected component extraction  ..." );
  // JOL: do like this for output iterators pointing on the same
  // container as 'this'. Works fine and nearly as fast.
  //
  // ObjectType( objects[ 0 ] ).writeComponents( inserter );

  trace.beginBlock ( "Components of diamond.border()  ..." );
  vector<ObjectType> objects2;
  back_insert_iterator< vector< ObjectType > > inserter2( objects2 );
  unsigned int nbc0 = objects[ 0 ].border().writeComponents( inserter2 );
  INBLOCK_TEST( nbc0 == 1 );
  INBLOCK_TEST( objects[ 0 ].computeConnectedness() == CONNECTED );
  trace.endBlock();

  trace.beginBlock ( "Components of diamond_clone.border()  ..." );
  unsigned int nbc1 = objects[ 1 ].border().writeComponents( inserter2 );
  INBLOCK_TEST( nbc1 == 3 );
  trace.endBlock();
  for (  vector<ObjectType>::const_iterator it = objects2.begin();
      it != objects2.end();
      ++it )
    trace.info() << "- objects2[" << (it - objects2.begin() ) << "]"
    << " = " << *it << endl;
  INBLOCK_TEST( objects2[ 0 ].size() == objects2[ 1 ].size() );
  INBLOCK_TEST( objects2[ 2 ].size() == objects2[ 3 ].size() );
  INBLOCK_TEST( objects2[ 0 ].size() == 15848 );
  INBLOCK_TEST( objects2[ 2 ].size() == 18 );

  trace.endBlock();

  return nbok == nb;

}

/**
 * Example of a test. To be completed.
 *
 */
bool testSimplePoints3D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef SpaceND< 3 > Z3;
  typedef MetricAdjacency< Z3, 1 > Adj6;
  typedef MetricAdjacency< Z3, 2 > Adj18;
  typedef DigitalTopology< Adj6, Adj18 > DT6_18;
  typedef Z3::Point Point;
  typedef HyperRectDomain< Z3 > Domain;
  typedef Domain::ConstIterator DomainConstIterator;
  typedef DigitalSetSelector < Domain, BIG_DS + HIGH_BEL_DS >::Type DigitalSet;
  typedef Object<DT6_18, DigitalSet> ObjectType;
  typedef Object<DT6_18, DigitalSet>::SmallObject SmallObjectType;
  typedef Object<DT6_18, DigitalSet>::SmallComplementObject SmallComplementObjectType;
  Adj6 adj6;
  Adj18 adj18;
  DT6_18 dt6_18( adj6, adj18, JORDAN_DT );

  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  Domain domain( p1, p2 );
  Point c( 0, 0, 0 );
  Point r( 3, 0, 0 );

  trace.beginBlock ( "Creating Diamond (r=4)" );
  // diamond of radius 4
  DigitalSet diamond_set( domain );
  for ( DomainConstIterator it = domain.begin(); it != domain.end(); ++it )
  {
    if ( (*it - c ).norm1() <= 3 )
      diamond_set.insertNew( *it );
  }
  diamond_set.erase( c );
  ObjectType diamond( dt6_18, diamond_set );
  trace.endBlock();

  trace.beginBlock ( "Geodesic neighborhoods ..." );
  SmallObjectType geoN6_3 = diamond.geodesicNeighborhood( adj6, r, 3 );
  SmallObjectType geoN18_2 = diamond.geodesicNeighborhood( adj18, r, 2 );
  trace.info() << "geoN6_3  = " << geoN6_3 << endl;
  trace.info() << "geoN18_2 = " << geoN18_2 << endl;
  SmallComplementObjectType cgeoN6_3 = diamond.geodesicNeighborhoodInComplement( adj6, r, 3 );
  SmallComplementObjectType cgeoN18_2 = diamond.geodesicNeighborhoodInComplement( adj18, r, 2 );
  trace.info() << "cgeoN6_3  = " << cgeoN6_3 << endl;
  trace.info() << "cgeoN18_2 = " << cgeoN18_2 << endl;
  trace.endBlock();

  trace.beginBlock ( "Simple points ..." );
  for ( DigitalSet::ConstIterator it = diamond.pointSet().begin();
      it != diamond.pointSet().end();
      ++it )
    trace.info() << "- " << *it
    << " " << ( diamond.isSimple( *it ) ? "Simple" : "Not simple" )
    << endl;
  trace.endBlock();


  return nbok == nb;
}


bool testDraw()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "testDraw(): testing drawing commands." );

  typedef SpaceND<  2 > Z2;
  typedef Z2::Point Point;
  typedef Point::Coordinate Coordinate;
  typedef HyperRectDomain< Z2 > DomainType;
  Point p1(  -10, -10  );
  Point p2( 10, 10  );
  DomainType domain( p1, p2 );

  // typedef DomainMetricAdjacency< DomainType, 1 > Adj4;
  // typedef DomainMetricAdjacency< DomainType, 2 > Adj8;
  typedef MetricAdjacency< Z2, 1 > MetricAdj4;
  typedef MetricAdjacency< Z2, 2 > MetricAdj8;
  typedef DomainAdjacency< DomainType, MetricAdj4 > Adj4;
  typedef DomainAdjacency< DomainType, MetricAdj8 > Adj8;
  typedef DigitalTopology< Adj4, Adj8 > DT48;
  typedef DigitalTopology< Adj8, Adj4 > DT84;
  typedef DigitalSetSelector < DomainType, MEDIUM_DS + HIGH_BEL_DS >::Type
  MediumSet;
//   typedef DigitalSetSelector< DomainType, SMALL_DS >::Type
//     MediumSet;
  typedef Object<DT48, MediumSet> ObjectType;
  typedef Object<DT84, MediumSet> ObjectType84;

  //typedef ObjectType::SmallSet SmallSet;
  //typedef Object<DT48, SmallSet> SmallObjectType;
  //typedef ObjectType::Size Size;

  // Adj4 adj4( domain );
  // Adj8 adj8( domain );
  MetricAdj4 madj4;
  MetricAdj8 madj8;
  Adj4 adj4( domain, madj4 );
  Adj8 adj8( domain, madj8 );
  DT48 dt48( adj4, adj8, JORDAN_DT );
  DT84 dt84( adj8, adj4, JORDAN_DT );

  Coordinate r = 5;
  double radius = (double) (r + 1);
  Point c(  0, 0  );
  Point l(  r, 0  );
  MediumSet disk( domain );
  ostringstream sstr;
  sstr << "Creating disk( r < " << radius << " ) ...";
  trace.beginBlock ( sstr.str() );
  for ( DomainType::ConstIterator it = domain.begin();
      it != domain.end();
      ++it )
  {
    if ( (*it - c ).norm() < radius ) // 450.0
      // insertNew is very important for vector container.
      disk.insertNew( *it );
  }
  trace.endBlock();

  trace.beginBlock ( "Testing Object instanciation and smart copy  ..." );
  ObjectType disk_object( dt48, disk );
  ObjectType84 disk_object2( dt84, disk );
  trace.endBlock();

  trace.beginBlock ( "Testing export as SVG with libboard." );

  Board2D board;
  board.setUnit(Board::UCentimeter);

  board << SetMode( domain.className(), "Grid" ) << domain;
  board << disk_object;

  board.saveSVG("disk-object.svg");

  Board2D board2;
  board2.setUnit(Board::UCentimeter);

  board2 << SetMode( domain.className(), "Grid" ) << domain;
  board2 << SetMode( disk_object.className(), "DrawAdjacencies" ) << disk_object;

  board2.saveSVG("disk-object-adj.svg");

  Board2D board3;
  board3.setUnit( Board::UCentimeter );

  board3 << SetMode( domain.className(), "Grid" ) << domain;
  board3 << SetMode( disk_object2.className(), "DrawAdjacencies" ) << disk_object2;

  board3.saveSVG("disk-object-adj-bis.svg");
  trace.endBlock();

  trace.endBlock();

  return nbok == nb;

}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Object" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testObject() &&
      testObject3D() && testDraw()
      && testSimplePoints3D();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
